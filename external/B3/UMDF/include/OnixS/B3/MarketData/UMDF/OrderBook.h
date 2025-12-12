/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable ONIXS Software
* Services Agreement (the Agreement) and Customer end user license agreements granting
* a non-assignable, non-transferable and non-exclusive license to use the software
* for it's own data processing purposes under the terms defined in the Agreement.
*
* Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
* of this source code or associated reference material to any other location for further reproduction
* or redistribution, and any amendments to this copyright notice, are expressly prohibited.
*
* Any reproduction or redistribution for sale or hiring of the Software not in accordance with
* the terms of the Agreement is a violation of copyright law.
*/
#pragma once

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Composites.h>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Settings for the `OrderBookPool`.
                ///
                /// To improve performance, the OrderBook keeps some of its internals in the preallocated
                /// memory areas (chunks).
                ///
                /// The chunks are initially owned by the OrderBookPool object. The `OrderBookPool` object
                /// is shared between the `OrderBook`s (and can be shared between several instances of the handlers).
                ///
                /// When a chunk is taken from the pool, it is not shared between the other order books,
                /// so the number of the chunks must be at least equal to the number of order books.
                /// A single order book can use from 1 to 255 chunks if necessary.
                ///
                /// The number of books equals the number of securities on a channel or the size of the security filter (if used).
                ///
                /// Placing the order book's internals into a single chunk improves data locality
                /// and can thus improve performance, so the chunk must be sufficient to fit the book content.
                /// On the other hand, making a chunk too big can lead to excessive memory consumption.
                struct OrderBookPoolSettings
                {
                    /// Amount of order book objects.
                    size_t orderBooksAmount = 500;

                    /// Amount of memory chunks.
                    /// @note If the pool is exhausted, the chunks are allocated dynamically, and a warning is raised.
                    size_t chunksAmount = 1000;

                    /// Length of a chunk.
                    /// The maximum chunk length should not be much more than the size of memory necessary to store all orders for security.
                    /// @note The minimal value is 4*1024.
                    size_t chunkLength = 512 * 1024;

                    /// Use Huge pages for chunk allocation.
                    /// @note Takes effect on Linux only.
                    /// @note Huge pages must be enabled on the system level.
                    bool preferHugePage = false;

                    /// Defines growth policy
                    struct GrowthPolicy
                    {
                        enum Policy
                        {
                            ///
                            Addition,

                            ///
                            Multiplication
                        };

                        Policy policy;

                        /// Argument
                        double arg;
                    };

                    GrowthPolicy growthPolicy = {GrowthPolicy::Addition, 1.0f};
                };

                /// A shared memory pool for building order books.
                class ONIXS_B3_UMDF_MD_API OrderBookPool
                {
                public:
                    ///
                    explicit OrderBookPool(const OrderBookPoolSettings&);

                    ///
                    ~OrderBookPool();

                    struct Statistic
                    {
                        ///
                        int64_t maxChunksCountInUse_ = 0;
                    };

                    ///
                    const Statistic& statistic() const noexcept
                    {
                        return statistic_;
                    }

                private:
                    OrderBookPool(const OrderBookPool&) = delete;
                    OrderBookPool& operator=(const OrderBookPool&) = delete;

                    friend struct OrderBookPoolHelper;
                    Statistic statistic_;
                    void* const impl_;

                    // for testing only
                    OrderBookPool(const OrderBookPoolSettings& settings, NoCheck);
                    friend struct TestOrdBookPoolCreator;
                };

                /// Alias for Instrument Id type.
                typedef UInt64 InstrumentId;

                /// Alias for Order Id type.
                typedef UInt64 OrderId;

                /// Alias for Quantity type.
                typedef Int64 Quantity;

                /// Alias for Price type (4 decimal places)
                typedef Messaging::PriceOptional Price;

                /// Order information
                struct Order
                {
                    /// Initializes the instances according to specified attributes.
                    Order(OrderId orderId, Price price, Quantity quantity) ONIXS_B3_UMDF_MD_NOTHROW;

                    /// Returns string representation of the instance.
                    std::string toString() const;

                    /// Appends representation of the instance to the string.
                    ONIXS_B3_UMDF_MD_API
                    void toString(std::string&) const;

                    /// Order Id
                    OrderId orderId() const ONIXS_B3_UMDF_MD_NOTHROW { return orderId_; };

                    /// Price
                    Price price() const ONIXS_B3_UMDF_MD_NOTHROW { return price_; };

                    /// Quantity
                    Quantity quantity() const ONIXS_B3_UMDF_MD_NOTHROW { return quantity_; };

                    /// Indicates whether the order is the market order.
                    bool marketOrder() const { return price_.isNull(); }

                private:
                    OrderId orderId_;
                    Price price_;
                    Quantity quantity_;
                };

                /// compare
                bool operator==(const Order& l, const Order& r) ONIXS_B3_UMDF_MD_NOTHROW;

                ///
                ONIXS_B3_UMDF_MD_API
                std::ostream& operator<<(std::ostream& stream, const Order& value);

                /// \private
                namespace Implementation
                {
                    class InstrumentRepository;
                    class OrderStorage;
                    struct ONIXS_B3_UMDF_MD_ALIGNAS(1) BookOrderId { char _[3]; };
                    typedef const BookOrderId* OrdersIterator;
                };

                /// STL-like iterator over OrderBook levels
                class OrdersIterator
                {
                public:
                    typedef std::random_access_iterator_tag iterator_category;
                    typedef const Order value_type;
                    typedef ptrdiff_t difference_type;
                    typedef value_type* pointer;
                    typedef value_type& reference;

                    ///
                    OrdersIterator(const OrdersIterator& r) =default;

                    OrdersIterator& operator=(const OrdersIterator& r) noexcept
                    {
                        OrdersIterator tmp(r);
                        tmp.swap(*this);
                        return *this;
                    }

                    void swap(OrdersIterator& other) noexcept
                    {
                        std::swap(storage_, other.storage_);
                        std::swap(pos_, other.pos_);
                    }

                    ONIXS_B3_UMDF_MD_API reference operator*() const noexcept;
                    ONIXS_B3_UMDF_MD_API pointer operator->() const noexcept;
                    ONIXS_B3_UMDF_MD_API reference operator[] (difference_type n) const noexcept;

                    OrdersIterator operator++(int) noexcept { return {storage_, pos_++}; }
                    OrdersIterator& operator++() noexcept { ++pos_; return *this; }
                    OrdersIterator operator+ (difference_type v) const noexcept { return {storage_, pos_ + v};}
                    OrdersIterator operator+= (difference_type v) noexcept { return {storage_, pos_ += v};}

                    OrdersIterator operator--(int) noexcept { return {storage_, pos_--}; }
                    OrdersIterator& operator--() noexcept { --pos_; return *this; }
                    OrdersIterator operator- (difference_type v) const noexcept { return {storage_, pos_ - v};}
                    OrdersIterator operator-= (difference_type v) noexcept { return {storage_, pos_ -= v};}

                    bool operator==(const OrdersIterator& rhs) const noexcept { return pos_ == rhs.pos_; }
                    bool operator!=(const OrdersIterator& rhs) const noexcept { return pos_ != rhs.pos_; }

                    friend OrdersIterator::difference_type operator-(const OrdersIterator& l, const OrdersIterator& r) noexcept
                    {
                        return l.pos_ - r.pos_;
                    }

                private:
                    friend class ConstOrdersRange;
                    OrdersIterator(const Implementation::OrderStorage* storage, Implementation::OrdersIterator pos) noexcept
                      : storage_(storage)
                      , pos_(pos)
                    {
                    }

                private:
                    const Implementation::OrderStorage* storage_{};
                    Implementation::OrdersIterator pos_{};
                };

                /// A range of orders
                class ConstOrdersRange
                {
                public:
                    OrdersIterator begin() const noexcept
                    {
                        return cbegin();
                    }

                    OrdersIterator end() const noexcept
                    {
                        return cend();
                    }

                    OrdersIterator cbegin() const noexcept
                    {
                        return {storage_, begin_};
                    }

                    OrdersIterator cend() const noexcept
                    {
                        return {storage_, end_};
                    }

                    bool empty() const noexcept
                    {
                        return begin_ == end_;
                    }

                    size_t size() const noexcept
                    {
                        return static_cast<size_t>(std::distance(begin_, end_));
                    }

                    const Order& operator[](size_t idx) const noexcept
                    {
                        assert(idx < size());
                        return begin().operator[](idx);
                    }

                private:
                    friend class OrderBook;
                    ConstOrdersRange(Implementation::OrdersIterator begin, Implementation::OrdersIterator end, const Implementation::OrderStorage* storage) noexcept
                      : begin_(begin)
                      , end_(end)
                      , storage_(storage)
                    {}

                private:
                    Implementation::OrdersIterator begin_;
                    Implementation::OrdersIterator end_;
                    const Implementation::OrderStorage* storage_;
                };

                /// Order Book.
                /// A set of bid and ask orders for the given
                /// security (bids are descending and asks are ascending).
                class ONIXS_B3_UMDF_MD_API OrderBook
                {
                public:
                    /// Instrument Id
                    inline InstrumentId instrumentId() const ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        return id_;
                    }

                    /// Indicates whether book has no bids & asks.
                    bool empty() const noexcept;

                    /// Returns a set of descending ask prices for the given security.
                    ConstOrdersRange asks() const noexcept;

                    /// Returns a set of ascending bid prices for the given security.
                    ConstOrdersRange bids() const noexcept;

                    /// Returns the last processed packet sequence number of the incremental channel
                    Messaging::SeqNum lastMessageSeqNumApplied() const noexcept;

                    /// Returns the last processed RptSeq (sequence number per instrument update) for this instrument.
                    Messaging::RptSeq lastRptSeq() const noexcept;

                    /// String presentation of the book.
                    std::string toString() const;

                    /// String presentation of the book.
                    void toString(std::string&) const;

                    /// Returns brief book info.
                    std::string toShortString() const;

                    /// Appends brief book info to the string.
                    void toShortString(std::string&) const;

                    /// Returns formatted presentation of the book.
                    std::string toFormattedString() const;

                    /// Appends Formatted presentation of the book.
                    void toFormattedString (std::string&) const;

                    ///
                    OrderBook(const OrderBook&) = delete;
                    OrderBook(OrderBook&&) = delete;
                    OrderBook& operator=(const OrderBook&) = delete;

                protected:
                    OrderBook(size_t depth, const Implementation::InstrumentRepository* instrumentRepository, InstrumentId id);
                    ~OrderBook();

                    const size_t depth_;
                    const InstrumentId id_;
                    const Implementation::InstrumentRepository* const instrumentRepository_;

                private:
                    const Implementation::OrderStorage* getStorage() const noexcept;
                };

                /// For testing only.
                ONIXS_B3_UMDF_MD_API
                void validate(const OrderBook&);

                inline Order::Order(OrderId orderId, Price price, Quantity quantity) ONIXS_B3_UMDF_MD_NOTHROW
                  : orderId_(orderId)
                  , price_(price)
                  , quantity_(quantity)
                {
                }

                inline bool operator==(const Order& l, const Order& r) ONIXS_B3_UMDF_MD_NOTHROW
                {
                    return (l.orderId() == r.orderId()) && (l.price().mantissa() == r.price().mantissa()) && (l.quantity() == r.quantity());
                }

                inline std::string Order::toString() const
                {
                    std::string str;
                    toString(str);
                    return str;
                }

            }
        }
    }
}
