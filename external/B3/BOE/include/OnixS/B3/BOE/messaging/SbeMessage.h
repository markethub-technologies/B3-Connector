// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is
// protected by copyright law and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable
// OnixS Software Services Agreement (the Agreement) and Customer end user license
// agreements granting a non-assignable, non-transferable and non-exclusive license
// to use the software for it's own data processing purposes under the terms defined
// in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or
// reproduction of any part of this source code or associated reference material
// to any other location for further reproduction or redistribution, and any
// amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in
// accordance with the terms of the Agreement is a violation of copyright law.
//

#pragma once

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/messaging/Aliases.h>
#include <OnixS/B3/BOE/messaging/StrRef.h>
#include <OnixS/B3/BOE/messaging/Memory.h>
#include <OnixS/B3/BOE/messaging/Composites.h>
#include <OnixS/B3/BOE/messaging/SchemaTraits.h>
#include <OnixS/B3/BOE/messaging/MaxMessageSize.h>
#include <OnixS/B3/BOE/messaging/ExceptionHelpers.h>

#include <cassert>
#include <limits>
#include <stdexcept>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Message type (template) identification.
typedef
MessageHeader::TemplateId MessageTemplateId;

/// \private
template<typename Message> inline
void checkBinaryLength(const Message&, MessageSize length, MessageSize minimalRequiredLength)
{
    if ONIXS_B3_BOE_UNLIKELY(length < minimalRequiredLength)
        throwBinaryBlockIsTooSmall(length, minimalRequiredLength, Message::className());
}

/// \private
ONIXS_B3_BOE_LTWT_CLASS BinaryBlockBase
{
protected:
    ~BinaryBlockBase() ONIXS_B3_BOE_DEFAULT;
};

/// Services to access fields stored
/// in an SBE-encoded block of fixed-length fields.
///
/// The given class represents an abstraction to be used
/// by descendants as a base class with static polymorphism.
template < class Container, class BlockLength >
ONIXS_B3_BOE_LTWT_CLASS BinaryBlock : public BinaryBlockBase
{
    /// \return The block container that provides access to the encoded data.
    const Container& container() const ONIXS_B3_BOE_NOTHROW
    {
        return *static_cast <const Container*> (this);
    }

protected:
    /// Initializes a blank instance.
    BinaryBlock() ONIXS_B3_BOE_DEFAULT;

    ~BinaryBlock() ONIXS_B3_BOE_DEFAULT;

    /// \return the field value.
    template < class Value > ONIXS_B3_BOE_HOTPATH
    Value ordinary(BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        assert(container().blockLength() >= (offset + size<Value>()) &&
            "The requested field exceeds provided block boundaries.");

        const void* const location = advanceByBytes(container().block(), offset);
        return getValue<Value>(location);
    }

    /// \return constant reference to the field value.
    template < class Value > ONIXS_B3_BOE_HOTPATH
    const Value& accessOrdinary(BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        assert(container().blockLength() >= (offset + size<Value>()) &&
            "The requested field exceeds provided block boundaries.");

        const void* location = advanceByBytes(container().block(), offset);
        const Value* valuePtr = static_cast<const Value*>(location);
        return *valuePtr;
    }

    /// \return reference to the field value.
    template < class Value > ONIXS_B3_BOE_HOTPATH
    Value& accessOrdinary(BlockLength offset) ONIXS_B3_BOE_NOTHROW
    {
        return const_cast<Value&>(static_cast<const BinaryBlock<Container, BlockLength> &>(*this).accessOrdinary<Value>(offset));
    }

    /// Provides access to an optional field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template <class Value, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool ordinary(Value& value, BlockLength offset, NullValue null) const ONIXS_B3_BOE_NOTHROW
    {
        value = ordinary<Value>(offset);

        return (null != value);
    }

    /// Provides access to an optional field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template < class Value, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool ordinary(Value& value, BlockLength offset, NullValue null, SchemaVersion since) const ONIXS_B3_BOE_NOTHROW
    {
        return (since <= container().version()  && ordinary (value, offset, null ) );
    }

    /// \return the field value.
    template < class Enumeration > ONIXS_B3_BOE_HOTPATH
    typename Enumeration::Enum enumeration(BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        typedef typename Enumeration::Base Base;
        typedef typename Enumeration::Enum Enum;

        return static_cast<Enum>(ordinary<Base>(offset));
    }

    /// Provides access to an optional field value.
    template < class Enumeration, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool enumeration(typename Enumeration::Enum& value, BlockLength offset, NullValue null) const ONIXS_B3_BOE_NOTHROW
    {
        typedef typename Enumeration::Base Base;
        typedef typename Enumeration::Enum Enum;

        value = static_cast <Enum>(ordinary<Base>(offset));
        return null != value;
    }

    /// Provides access to an optional field value.
    template < class Enumeration, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool enumeration(typename Enumeration::Enum& value, BlockLength offset, NullValue null, SchemaVersion since) const ONIXS_B3_BOE_NOTHROW
    {
        return (since <= container().version() && enumeration<Enumeration>(value, offset, null) );
    }

    /// \return a Decimal field value.
    template < class Value > ONIXS_B3_BOE_HOTPATH
    Value decimal(BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        return ordinary<Value>(offset);
    }

    /// \return an optional Decimal field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template < class Value, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool decimal(Value& value, BlockLength offset, NullValue null) const ONIXS_B3_BOE_NOTHROW
    {
        value = ordinary<Value>(offset);
        return null != value;
    }

    /// \return an optional Decimal field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template < class Value, class NullValue > ONIXS_B3_BOE_HOTPATH
    bool decimal(Value& value, BlockLength offset, NullValue null, SchemaVersion since) const ONIXS_B3_BOE_NOTHROW
    {
        return (since <= container().version() && decimal(value, offset, null));
    }

    /// Provides access to a string field value.
    template < BlockLength Length > ONIXS_B3_BOE_HOTPATH
    StrRef fixedStr(BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        assert(container().blockLength() >= (offset + Length) && "The requested field exceeds provided block boundaries.");

        const Char* const text = reinterpret_cast <const Char*> (advanceByBytes(container().block(), offset));

        return StrRef(text, strnlen(text, Length));
    }

    /// Provides access to an optional string field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template<BlockLength Length> ONIXS_B3_BOE_HOTPATH
    bool fixedStr(StrRef& value, BlockLength offset) const ONIXS_B3_BOE_NOTHROW
    {
        value = fixedStr<Length>(offset);
        return !value.empty();
    }

    /// Provides access to an optional string field value.
    ///
    /// \return `true` if the field is present in the field block and its value was copied,
    /// otherwise - `false`.
    template<BlockLength Length> ONIXS_B3_BOE_HOTPATH
    bool fixedStr(StrRef& value, BlockLength offset, SchemaVersion since) const ONIXS_B3_BOE_NOTHROW
    {
        return (since <= container().version() && fixedStr<Length>(value, offset));
    }
};

/// Base services to access fields stored in an SBE-encoded block of memory.
///
/// This class represents an abstraction to be used
/// by descendants as a base class with static polymorphism.
template <class Container, class BlockLength >
ONIXS_B3_BOE_LTWT_CLASS SbeFields : public BinaryBlock<Container, BlockLength>
{
public:
    /// \return The block container that provides access to the encoded data.
    Container& container() ONIXS_B3_BOE_NOTHROW
    {
        return *static_cast<Container*>(this);
    }

    /// If specified, the extra space is padded at the end of each entry and should be set to zeroes by encoders.
    ONIXS_B3_BOE_HOTPATH
    void zeroPaddingBytes(BlockLength offset) ONIXS_B3_BOE_NOTHROW
    {
        const BlockLength encodedBlockLength = container().blockLength();

        assert(encodedBlockLength >= offset);

        const size_t paddingLength = encodedBlockLength - offset;
        std::memset(advanceByBytes(container().block(), offset), 0, paddingLength);
    }

    /// Sets the field value.
    template<class FieldValue> ONIXS_B3_BOE_HOTPATH
    void setOrdinary(BlockLength offset, FieldValue value) ONIXS_B3_BOE_NOTHROW
    {
        assert(container().blockLength() >= (offset + size<FieldValue>()) && "The requested field exceeds provided block boundaries.");

        void* const fieldPos = advanceByBytes(container().block(), offset);
        setValue(fieldPos, value);
    }

    /// Sets the field value.
    template<class FieldValue> ONIXS_B3_BOE_HOTPATH
    void setOrdinary(BlockLength offset, FieldValue value, SchemaVersion since)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > container().version())
            throwDisallowedField();

        setOrdinary(offset, value);
    }

    /// Sets the field value.
    template<class Enumeration> ONIXS_B3_BOE_HOTPATH
    void setEnumeration(BlockLength offset, typename Enumeration::Enum value) ONIXS_B3_BOE_NOTHROW
    {
        typedef typename Enumeration::Base Base;
        setOrdinary<Base>(offset, static_cast<Base>(value));
    }

    /// Sets the field value.
    template<class Enumeration> ONIXS_B3_BOE_HOTPATH
    void setEnumeration(BlockLength offset, typename Enumeration::Enum value, SchemaVersion since)
    {
        typedef typename Enumeration::Base Base;
        setOrdinary(offset, static_cast<Base>(value), since);
    }

    /// Sets the field value.
    template<BlockLength Size> ONIXS_B3_BOE_HOTPATH
    void setFixedStr(BlockLength offset, StrRef value) ONIXS_B3_BOE_NOTHROW
    {
        assert(container().blockLength() >= (offset + Size) && "The requested field exceeds provided block boundaries.");
        assert(value.size() <= Size && "The string is truncated.");

        void* const fieldPos = advanceByBytes(container().block(), offset);
        const size_t sizeToCopy = (std::min)(Size, static_cast<BlockLength>(value.size()));

        if(sizeToCopy > 0)
            std::memcpy(fieldPos, value.data(), sizeToCopy);

        std::memset(advanceByBytes(fieldPos, sizeToCopy), 0, Size - sizeToCopy);
    }

    /// Sets the field value.
    template<BlockLength Size> ONIXS_B3_BOE_HOTPATH
    void setFixedStr(BlockLength offset, StrRef value, SchemaVersion since)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > container().version())
            throwDisallowedField();

        setFixedStr<Size>(offset, value);
    }

protected:
    /// Initializes a blank instance.
    SbeFields() ONIXS_B3_BOE_DEFAULT;

    ~SbeFields() ONIXS_B3_BOE_DEFAULT;
};

/// Operations over a repeating group instance.
template <class BodySizeType>
ONIXS_B3_BOE_LTWT_CLASS SbeGroupEntry : public SbeFields<SbeGroupEntry<BodySizeType>, BodySizeType>
{
public:
    /// Type to present the length of binary data of the repeating group entry.
    typedef BodySizeType BlockLength;

    /// Initializes a blank instance.
    SbeGroupEntry()
        : encoded_(ONIXS_B3_BOE_NULLPTR)
        , size_(0)
        , version_(0)
    {
    }

    /// Initializes the instance from the memory block of the encoded message.
    ONIXS_B3_BOE_HOTPATH
    SbeGroupEntry(void* encoded, BlockLength size, SchemaVersion version)
        : encoded_(encoded)
        , size_(size)
        , version_(version)
    {
        assert(encoded);
    }

    /// \return `true` if the instance refers to a valid content, otherwise - `false`.
    bool valid() const ONIXS_B3_BOE_NOTHROW
    {
        return (encoded_ != ONIXS_B3_BOE_NULLPTR);
    }

    /// \return the beginning of the group entry body.
    const void* encoded() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return encoded_;
    }

    /// \return the beginning of the group entry body.
    void* encoded() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return encoded_;
    }

    /// \return the pointer to the block containing fixed-length fields.
    const void* block() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return encoded_;
    }

    /// \return the pointer to the block containing fixed-length fields.
    void* block() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return encoded_;
    }

    /// \return Block length.
    BlockLength blockLength() const ONIXS_B3_BOE_NOTHROW
    {
        return size_;
    }

    /// \return SBE Schema version.
    SchemaVersion version() const ONIXS_B3_BOE_NOTHROW
    {
        return version_;
    }

    private:
    void* encoded_;
    BodySizeType size_;
    SchemaVersion version_;
};

/// Operations over SBE-encoded repeating group entries.
template <class EntryType, class BlockLength, class NumInGroup, class Length >
ONIXS_B3_BOE_LTWT_CLASS SbeGroupEntries
{
public:
    /// The length of the binary data occupied by the group entries.
    typedef Length EncodedLength;

    /// The type of the repeating group entry.
    typedef EntryType Entry;

    /// Number of entries in the collection.
    typedef NumInGroup Size;

    /// An iterator over SBE-encoded group entries.
    ONIXS_B3_BOE_LTWT_CLASS Iterator
    {
    public:
        typedef EntryType Entry;
        typedef Entry value_type;

        typedef Entry* pointer;
        typedef Entry& reference;

        typedef ptrdiff_t difference_type;

        typedef std::random_access_iterator_tag iterator_category;

        /// Initializes the instance that refers to nothing.
        Iterator() ONIXS_B3_BOE_NOTHROW
            : entry_(ONIXS_B3_BOE_NULLPTR)
            , size_(0)
            , version_(0)
        {
        }

        /// Initializes the instance to the given repeating group.
        ONIXS_B3_BOE_HOTPATH
        Iterator(void* entry, EncodedLength size, SchemaVersion version) ONIXS_B3_BOE_NOTHROW
            : entry_(entry)
            , size_(size)
            , version_(version)
        {
            assert(valid());
        }

        /// \return `true` if the instance is valid, otherwise - `false`.
        bool valid() const ONIXS_B3_BOE_NOTHROW
        {
            return (entry_ != ONIXS_B3_BOE_NULLPTR);
        }

        /// \return the repeating group entry.
        ONIXS_B3_BOE_HOTPATH
        Entry get() const
        {
            assert(valid());

            return Entry(entry_, size_, version_);
        }

        /// \return the repeating group entry.
        Entry operator *() const
        {
            return get();
        }

        /// Compares iterators.
        bool operator == (const Iterator& other) const ONIXS_B3_BOE_NOTHROW
        {
            return entry_ == other.entry_;
        }

        /// Compares iterators.
        bool operator !=(const Iterator& other) const ONIXS_B3_BOE_NOTHROW
        {
            return entry_ != other.entry_;
        }

        /// Established the order between two iterators.
        bool operator < (const Iterator& other) const ONIXS_B3_BOE_NOTHROW
        {
            return entry_ < other.entry_;
        }

        /// Established the order between two iterators.
        bool operator > (const Iterator& other) const ONIXS_B3_BOE_NOTHROW
        {
            return entry_ > other.entry_;
        }

        /// Advances the next repeating group entry.
        Iterator& operator ++()
        {
            assert(valid());

            entry_ = advanceByBytes(entry_, size_);

            return *this;
        }

        /// Advances to the previous repeating group entry.
        Iterator& operator --()
        {
            assert(valid());

            entry_ = advanceBackByBytes(entry_, size_);

            return *this;
        }

        /// Advances by given number of entries.
        ONIXS_B3_BOE_HOTPATH
        Iterator operator +(difference_type distance) const
        {
            assert(valid());

            return Iterator(advanceByBytes(entry_, distance * size_), size_, version_);
        }

        /// Advances back by given number of entries.
        ONIXS_B3_BOE_HOTPATH
        Iterator operator - (difference_type distance) const
        {
            assert(valid());

            return Iterator(advanceBackByBytes(entry_, distance * size_), size_, version_);
        }

        private:
        void* entry_;
        EncodedLength size_;
        SchemaVersion version_;
    };

    /// Initializes a blank instance referencing to nothing.
    SbeGroupEntries() ONIXS_B3_BOE_NOTHROW
        : encoded_(ONIXS_B3_BOE_NULLPTR)
        , blockLength_(0)
        , size_(0)
        , version_(0)
    {
    }

    /// Initializes the instance referencing to data.
    SbeGroupEntries(void* encoded, BlockLength blockLength, Size groupSize, SchemaVersion version) ONIXS_B3_BOE_NOTHROW
        : encoded_(encoded)
        , blockLength_(blockLength)
        , size_(groupSize)
        , version_(version)
    {
        assert(encoded_);
        assert(blockLength > 0);
        assert(version != 0);
    }

    /// \return `true` if the instance refers to a valid repeating group, otherwise - `false`.
    bool valid() const ONIXS_B3_BOE_NOTHROW
    {
        return (ONIXS_B3_BOE_NULLPTR != encoded_);
    }

    /// \return `true` if the referenced repeating group is empty, otherwise - `false`.
    bool empty() const ONIXS_B3_BOE_NOTHROW
    {
        return (0 == size_);
    }

    /// \return number of blocks.
    Size size() const ONIXS_B3_BOE_NOTHROW
    {
        return size_;
    }

    /// \return the iterator pointing to the first repeating group entry.
    Iterator begin() const
    {
        return Iterator(encoded(), blockLength_, version_);
    }

    /// Returns the iterator pointing to the entry behind the end of the group.
    Iterator end() const
    {
        return Iterator(advanceByBytes(encoded(), encodedLength()), blockLength_, version_);
    }

    /// Provides access to the group entry by its index in the repeating group.
    ///
    /// \note Index validness is not checked due to performance considerations.
    Entry operator [](Size index) const
    {
        assert(index < size_);
        assert(encoded_);

        return Entry(advanceByBytes(encoded_, static_cast<ptrdiff_t>(index) * blockLength_), blockLength_, version_);
    }

    /// \return Binary data occupied by the group entries.
    void* encoded() const ONIXS_B3_BOE_NOTHROW
    {
        return encoded_;
    }

    /// \return the length of the binary data occupied by the group entries.
    EncodedLength encodedLength() const ONIXS_B3_BOE_NOTHROW
    {
        return (static_cast<EncodedLength>(blockLength_) * static_cast<EncodedLength>(size_) );
    }

    /// Copy constructor.
    template<class OtherEntry, class OtherBlockLength, class OtherNumInGroup, class OtherLength >
    SbeGroupEntries(const SbeGroupEntries<OtherEntry, OtherBlockLength, OtherNumInGroup, OtherLength >& other) ONIXS_B3_BOE_NOTHROW
        : encoded_(other.encoded_)
        , blockLength_(other.blockLength_)
        , size_(other.size_)
        , version_(other.version_)
    {
        // Dimension types may vary for the different instantiations of the template.
        // Therefore, truncation of the dimensions must be avoided.

        assert(blockLength_ == other.blockLength_);
        assert(size_ == other.size_);
    }

    template <class OtherEntry, class OtherBlockLength, class OtherNumInGroup, class OtherLength>
    SbeGroupEntries& operator = (const SbeGroupEntries <OtherEntry, OtherBlockLength, OtherNumInGroup, OtherLength>& other) ONIXS_B3_BOE_NOTHROW
    {
        encoded_ = other.encoded_;

        blockLength_ = other.blockLength_;

        assert(blockLength_ == other.blockLength_);

        size_ = other.size_;

        assert(size_ == other.size_);

        version_ = other.version_;

        return *this;
    }

private:
    // Allows coping and cloning for different instantiations.
    template <class OtherEntry, class OtherBlockLength, class OtherNumInGroup, class OtherLength> friend class SbeGroupEntries;

    void* encoded_;
    BlockLength blockLength_;
    NumInGroup size_;
    SchemaVersion version_;
};

/// SBE-encoded repeating group.
template < class EntryType, class DimensionType, class GroupSizeType >
ONIXS_B3_BOE_LTWT_CLASS SbeGroup
{
public:
    /// Repeating group dimension type.
    typedef DimensionType Dimension;

    /// Length of group data.
    typedef GroupSizeType BinarySize;

    /// Length of an empty group.
    enum { EmptySize = Dimension::Size };

    /// Length of group entry data.
    typedef typename DimensionType::BlockLength EntrySize;

    /// Binary group blocks.
    typedef SbeGroupEntries <EntryType, typename Dimension::BlockLength, typename Dimension::NumInGroup, GroupSizeType > Entries;

    /// The iterator type for group entries.
    typedef typename Entries::Iterator Iterator;

    /// Group entry type.
    typedef typename Entries::Entry Entry;

    /// Number of entries in the group.
    typedef typename Entries::Size Size;

    /// Initializes a blank instance referencing to nothing.
    SbeGroup()
        ONIXS_B3_BOE_NOTHROW
        : header_(ONIXS_B3_BOE_NULLPTR)
        , entries_(ONIXS_B3_BOE_NULLPTR)
        , version_(0)
    {
    }

    /// Initializes an instance referencing to a valid group of a given message.
    ONIXS_B3_BOE_HOTPATH
    SbeGroup(void* data, ONIXS_B3_BOE_UNUSED BinarySize size, SchemaVersion version) ONIXS_B3_BOE_NOTHROW
        : header_(static_cast <Dimension*>(data))
        , entries_(advanceByBytes(data, Dimension::Size))
        , version_(version)
    {
        ONIXS_B3_BOE_ASSERT(size >= Dimension::Size);
        assert(header_);
        assert(entries_);

        assert(valid());
    }

    /// \return `true` if the instance refers to a valid repeating group, otherwise - `false`.
    bool valid() const ONIXS_B3_BOE_NOTHROW
    {
        return (entries_ != ONIXS_B3_BOE_NULLPTR);
    }

    /// \return `true` if the repeating group is empty, otherwise - `false`.
    bool empty() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return 0 == size();
    }

    /// \return the number of entries in the repeating group.
    ONIXS_B3_BOE_HOTPATH
    Size size() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());
        assert(header_);

        const Dimension* const group = static_cast<const Dimension*>(header_);

        return group->numInGroup();
    }

    /// \return an iterator pointing to the first repeating group entry.
    ONIXS_B3_BOE_HOTPATH
    Iterator begin() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return Iterator(entries_, numericCast<EntrySize>(entrySize()), version_);
    }

    /// \return an iterator pointing to the entry behind the end of the group.
    ONIXS_B3_BOE_HOTPATH
    Iterator end() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return Iterator(advanceByBytes(binary(), binarySize()), numericCast<EntrySize>(entrySize()), version_);
    }

    /// Provides access to a repeating group entry by the given index.
    ///
    /// \note Index validness is not checked due to performance considerations.
    ONIXS_B3_BOE_HOTPATH
    Entry operator [](Size index) const
    {
        assert(valid());
        assert(index < size());

        return Entry(advanceByBytes(entries_, static_cast<ptrdiff_t>(index) * entrySize()), entrySize(), version_);
    }

    /// \return Repeating group entries.
    ONIXS_B3_BOE_NODISCARD
    Entries entries() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());
        assert(header_);

        return Entries (entries_, header_->blockLength(), header_->numInGroup(), version_);
    }

    /// \return SBE-encoded data that represents the repeating group.
    const void* encoded() const ONIXS_B3_BOE_NOTHROW
    {
        return header_;
    }

    /// \return  the end of SBE-encoded data that represents the repeating group.
    const void* tail() const ONIXS_B3_BOE_NOTHROW
    {
        return advanceByBytes(toByteBlock(encoded()), binarySize());
    }

    /// \return SBE-encoded data that represents the repeating group.
    ONIXS_B3_BOE_HOTPATH
    void* binary() const ONIXS_B3_BOE_NOTHROW
    {
        return header_;
    }

    /// \return the size of SBE-encoded data that represents the repeating group.
    ONIXS_B3_BOE_HOTPATH
    BinarySize binarySize() const ONIXS_B3_BOE_NOTHROW
    {
        return Dimension::Size + (static_cast<BinarySize>(entrySize()) * static_cast<BinarySize>(size()));
    }

    /// \return the size of a single repeating group entry.
    ONIXS_B3_BOE_HOTPATH
    EntrySize entrySize() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());
        assert(header_);

        Dimension* const group = static_cast<Dimension*>(header_);
        return group->blockLength();
    }

private:
    /// Resets the group to the initial state, must be invoked only during the message construction.
    void init(EntrySize entrySize) ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());
        assert(header_);

        Dimension* const group = static_cast<Dimension*>(header_);
        group->setBlockLength(entrySize);
        group->setNumInGroup(0);
    }

    /// Allocates a group.
    Size allocate(Size entryCount, const void* messageTail, const void* blockEnd)
    {
        assert(valid());
        assert(blockEnd);
        assert(messageTail);

        Dimension* const group = static_cast<Dimension*>(header_);

        const EntrySize entrySize = group->blockLength();

        if ONIXS_B3_BOE_UNLIKELY(
            entrySize < EntryType::blockLength(version_))
        {
            throwBadBinaryBlock();
        }

        const Size oldEntryCount = group->numInGroup();

        if(oldEntryCount == entryCount)
            return entryCount;

        const ptrdiff_t memShift =
            (entryCount - oldEntryCount) * static_cast<ptrdiff_t>(entrySize);

        const void* const newMessageTail =
            advanceByBytes(messageTail, memShift);

        if ONIXS_B3_BOE_UNLIKELY(byteDistance(blockEnd, newMessageTail) < 0)
            throwNotEnoughSpace();

        const void* const oldEndOfGroup =
            advanceByBytes(entries_, static_cast<ptrdiff_t>(entrySize) * oldEntryCount);

        void* const newEndGroup =
            advanceByBytes(entries_, static_cast<ptrdiff_t>(entrySize) * entryCount);

        std::memmove(
            newEndGroup,
            oldEndOfGroup,
            byteDistance(messageTail, oldEndOfGroup));

        group->setNumInGroup(entryCount);

        return oldEntryCount;
    }

    /// Sets up the group.
    ONIXS_B3_BOE_HOTPATH
    void setup(Size entryCount, const void* messageTail, const void* blockEnd)
    {
        assert(valid());
        assert(blockEnd);
        assert(messageTail);

        const Size oldEntryCount = allocate(entryCount, messageTail, blockEnd);

        for(Size index = oldEntryCount; index < entryCount; ++index)
            zeroPaddingBytes((*this)[index].resetVariableFields());
    }

    /// Sets up the group, sets all optional fields to `null`.
    ONIXS_B3_BOE_HOTPATH
    void construct(Size entryCount, const void* messageTail, const void* blockEnd)
    {
        assert(valid());
        assert(blockEnd);
        assert(messageTail);

        const Size oldEntryCount = allocate(entryCount, messageTail, blockEnd);

        for(Size index = oldEntryCount; index < entryCount; ++index)
            zeroPaddingBytes((*this)[index].reset());
    }

    ONIXS_B3_BOE_HOTPATH
    static void zeroPaddingBytes(Entry& entry)
    {
        assert(entry.valid());
        entry.zeroPaddingBytes(EntryType::minimalBlockLength(entry.version()));
    }

private:
    Dimension* header_;
    void* entries_;
    SchemaVersion version_;

    friend class SbeMessage;
};

/// Variable-length fields list.
template < class BinarySize >
ONIXS_B3_BOE_LTWT_CLASS SbeVariableLengthFieldList
{
public:
    /// Initializes the list over the given memory block.
    ONIXS_B3_BOE_HOTPATH
    SbeVariableLengthFieldList(void* binary, BinarySize size, SchemaVersion version) ONIXS_B3_BOE_NOTHROW
        : binary_(binary)
        , size_(size)
        , version_(version)
    {
    }

    /// \return `true` if the list is empty, otherwise - `false.
    bool empty() const ONIXS_B3_BOE_NOTHROW
    {
        return (0 == size_);
    }

    /// \return the head of the list.
    template<class BinaryVariableLengthFieldType>
    BinaryVariableLengthFieldType& head() const ONIXS_B3_BOE_NOTHROW
    {
        return *static_cast<BinaryVariableLengthFieldType*>(binary_);
    }

    /// \return the list of variable-length fields following the head.
    template<class BinaryVariableLengthFieldType> ONIXS_B3_BOE_HOTPATH
    SbeVariableLengthFieldList tail() const ONIXS_B3_BOE_NOTHROW
    {
        assert(!empty());

        const BinarySize headSize = head<BinaryVariableLengthFieldType>().binarySize();

        assert(headSize <= size_);

        return SbeVariableLengthFieldList(advanceByBytes( binary_, headSize), size_ - headSize, version_);
    }

    /// Checks the variable-length field list consistency.
    ///
    /// \return the list of fields following the head.
    template<class BinaryVariableLengthFieldType> ONIXS_B3_BOE_HOTPATH
    SbeVariableLengthFieldList checkTail() const
    {
        if ONIXS_B3_BOE_UNLIKELY(empty() || (size_ < BinaryVariableLengthFieldType::Size))
        {
            throwBadBinaryBlock();
        }

        const BinarySize headSize = head<BinaryVariableLengthFieldType>().binarySize();

        if ONIXS_B3_BOE_UNLIKELY(headSize > size_)
        {
            throwBadBinaryBlock();
        }

        return SbeVariableLengthFieldList(advanceByBytes(binary_, headSize), size_ - headSize, version_);
    }

    private:
    void* binary_;
    BinarySize size_;
    SchemaVersion version_;

};

/// Groups list.
template  <class BinarySize>
ONIXS_B3_BOE_LTWT_CLASS SbeGroupList
{
public:
    /// Initializes the list over the memory block.
    ONIXS_B3_BOE_HOTPATH
    SbeGroupList(void* binary, BinarySize size, SchemaVersion version) ONIXS_B3_BOE_NOTHROW
        : binary_(binary)
        , size_(size)
        , version_(version)
    {
    }

    /// \return `true` if the list is empty, otherwise - `false`.
    bool empty() const ONIXS_B3_BOE_NOTHROW
    {
        return (0 == size_);
    }

    /// \return the head group.
    template<class Group> ONIXS_B3_BOE_HOTPATH
    Group head() const ONIXS_B3_BOE_NOTHROW
    {
        assert(!empty());

        return Group(binary_, size_, version_);
    }

    /// \return the list of groups that follow the head.
    template<class Group> ONIXS_B3_BOE_HOTPATH
    SbeGroupList tail() const ONIXS_B3_BOE_NOTHROW
    {
        assert(!empty());

        const BinarySize headSize = head<Group>().binarySize();

        assert(headSize <= size_);

        return SbeGroupList(advanceByBytes(binary_, headSize), size_ - headSize, version_);
    }

    /// \return variable length fields.
    template <class Group> ONIXS_B3_BOE_HOTPATH
    SbeVariableLengthFieldList<BinarySize> variableLengthFields() const ONIXS_B3_BOE_NOTHROW
    {
        assert(!empty());

        const BinarySize headSize = head<Group>().binarySize();

        assert(headSize <= size_);

        return SbeVariableLengthFieldList<BinarySize>(advanceByBytes(binary_, headSize), size_ - headSize, version_);
    }

    /// Checks the list consistency.
    ///
    /// \return the list of groups that follow the head.
    template<class Group> ONIXS_B3_BOE_HOTPATH
    SbeGroupList checkTail() const
    {
        const BinarySize headSize = checkHead<Group>();

        return SbeGroupList(advanceByBytes(binary_, headSize), size_ - headSize, version_);
    }

   /// Checks the variable length fields list consistency.
    ///
    /// \return the list of fields that follow the head.
    template <class Group> ONIXS_B3_BOE_HOTPATH
    SbeVariableLengthFieldList<BinarySize> checkVariableLengthFields() const
    {
        const BinarySize headSize = checkHead<Group>();

        return SbeVariableLengthFieldList<BinarySize>(advanceByBytes(binary_, headSize), size_ - headSize, version_);
    }

private:
    template<class Group>
    BinarySize checkHead() const
    {
        if ONIXS_B3_BOE_UNLIKELY(size_ < Group::Dimension::Size)
        {
            throwBadBinaryBlock();
        }

        const Group group = head<Group>();

        const BinarySize headSize = group.binarySize();

        if ONIXS_B3_BOE_UNLIKELY(headSize > size_)
        {
            throwBadBinaryBlock();
        }

        if(!group.empty())
        {
            const BinarySize entrySize = group.entrySize();
            const BinarySize expectedEntrySize = Group::Entry::minimalBlockLength(version_);

            if ONIXS_B3_BOE_UNLIKELY(entrySize < expectedEntrySize)
            {
                throwBadBinaryBlock();
            }
        }

        return headSize;
    }

    void* binary_;
    BinarySize size_;
    SchemaVersion version_;
};

/// Checks the compatibility with the provided SBE Schema version.
template<typename Traits>
void checkVersion(SchemaVersion version)
{
    if ONIXS_B3_BOE_UNLIKELY(version < Traits::MinimalVersion)
    {
        throwBadMessageVersion(version, Traits::MinimalVersion);
    }
}

/// Checks the compatibility with the provided SBE Schema version.
template<typename Traits>
void checkVersion(SchemaVersion since, SchemaVersion version)
{
    checkVersion<Traits>(version);

    if ONIXS_B3_BOE_UNLIKELY(version < since)
    {
        throwBadMessageVersion(version, since);
    }
}

/// Checks the compatibility with the provided SBE Schema ID.
template<typename Traits>
void checkSchemaId(SchemaId id)
{
    if ONIXS_B3_BOE_UNLIKELY(id != Traits::Id)
    {
        throwBadSchemaId(Traits::Id, id);
    }
}

/// Checks the compatibility with the provided SBE Schema version.
template<typename Traits>
void checkSchema(SchemaId id, SchemaVersion version)
{
    checkSchemaId<Traits>(id);
    checkVersion<Traits>(version);
}

/// SBE-encoded message.
ONIXS_B3_BOE_LTWT_CLASS SbeMessage : public SbeFields<Messaging::SbeMessage, MessageSize>
{
public:
    /// For tagged constructors
    struct NoFieldsInit{};
    struct NoInit{};
    struct NoCheck{};

    /// Length of the message binary data.
    typedef MessageSize EncodedLength;

    /// Length of the message body representing a block of fixed-length fields.
    typedef MessageSize BlockLength;

    /// Initializes a blank instance.
    SbeMessage() ONIXS_B3_BOE_NOTHROW
        : header_(ONIXS_B3_BOE_NULLPTR)
        , size_(0)
    {
    }

    /// Initializes the instance over the given memory block.
    ONIXS_B3_BOE_HOTPATH
    SbeMessage(void* data, MessageSize size, SchemaVersion version)
        : header_(static_cast<MessageHeader*>(data))
        , size_(size)
    {
        assert(data);
        assert(size <= MaxB3BOEMessageSize);

        if ONIXS_B3_BOE_UNLIKELY(size < MessageHeader::Size)
            throwBinaryBlockIsTooSmall(size, MessageHeader::Size);

        this->version(version);
    }

    /// Initializes the instance over the given memory block.
    ONIXS_B3_BOE_HOTPATH
    SbeMessage(void* data, MessageSize size)
        : header_(static_cast<MessageHeader*>(data))
        , size_(size)
    {
        assert(data);
        assert(size <= MaxB3BOEMessageSize);

        if ONIXS_B3_BOE_UNLIKELY(size < MessageHeader::Size)
            throwBinaryBlockIsTooSmall(size, MessageHeader::Size);

        // Now it is safe to read header_.
        if ONIXS_B3_BOE_UNLIKELY(size < (MessageHeader::Size + header_->blockLength()))
            throwBinaryBlockIsTooSmall(size, MessageHeader::Size + header_->blockLength());
    }

    /// Initializes the instance over the given memory block.
    ///
    /// \note Performs no check of the data consistency
    ONIXS_B3_BOE_HOTPATH
    SbeMessage(void* data, MessageSize size, NoCheck) ONIXS_B3_BOE_NOTHROW
        : header_(static_cast<MessageHeader*>(data))
        , size_(size)
    {
        assert(data);
        assert(size <= MaxB3BOEMessageSize);

        assert(size >= MessageHeader::Size);
        assert(size >= MessageHeader::Size + header_->blockLength());
    }

    /// Blank the instance.
    void clear() ONIXS_B3_BOE_NOTHROW
    {
        *this = SbeMessage();
        assert(!valid());
    }

    /// \return `true` if the instance refers to a valid message, otherwise - `false`.
    bool valid() const ONIXS_B3_BOE_NOTHROW
    {
        return (ONIXS_B3_BOE_NULLPTR != header_);
    }

    /// \return SBE Template identifier.
    MessageTemplateId templateId() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_->templateId();
    }

    /// \return SBE Schema version.
    SchemaVersion version() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_->version();
    }

    /// \return SBE Schema ID.
    SchemaId schemaId() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_->schemaId();
    }

    /// \return SBE-encoded message content.
    const void* binary() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_;
    }

    /// \return SBE-encoded message content.
    void* binary() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_;
    }

    // \return the end of the memory block.
    const void* blockEnd() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return advanceByBytes(header_, size_);
    }

    // \return the end of the memory block.
    const void* blockEnd() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return advanceByBytes(header_, size_);
    }

    /// \return the size of the message buffer.
    MessageSize bufferSize() const ONIXS_B3_BOE_NOTHROW
    {
        return size_;
    }

     /// \return the beginning of the message body.
    void* body() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return advanceByBytes(header_, MessageHeader::Size);
    }

    /// \return the size of the message body in bytes.
    BlockLength blockLength() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return header_->blockLength();
    }

    /// \return the beginning of the message body.
    const void* block() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return advanceByBytes(header_, MessageHeader::Size);
    }

    /// \return the beginning of the message body.
    void* block() ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        return advanceByBytes(header_, MessageHeader::Size);
    }

protected:
    /// Binary group list instantiation.
    typedef SbeGroupList<MessageSize> GroupList;

    /// Sets the SBE Schema version.
    SbeMessage& version(SchemaVersion version) ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

        header_->setVersion(version);

        return *this;
    }

    /// \return the list of repeating groups
    ONIXS_B3_BOE_HOTPATH
    GroupList groups() ONIXS_B3_BOE_NOTHROW
    {
        assert(header_);

        void* list = advanceByBytes<void>(body(), blockLength());

        const MessageSize listSize = size_ - MessageHeader::Size - header_->blockLength();

        return GroupList(list, listSize, header_->version());
    }

    /// \return the list of repeating groups
    ONIXS_B3_BOE_HOTPATH
    GroupList groups() const ONIXS_B3_BOE_NOTHROW
    {
        assert(header_);

        const void* list = advanceByBytes(block(), blockLength());

        const MessageSize listSize = size_ - MessageHeader::Size - header_->blockLength();

        return GroupList(const_cast<void*>(list), listSize, header_->version());
    }

    /// Resets the group to the initial state.
    template<typename Group>
    ONIXS_B3_BOE_HOTPATH
    void initGroup(Group& group, typename Group::EntrySize entrySize) ONIXS_B3_BOE_NOTHROW
    {
        assert(group.valid());
        group.init(entrySize);
    }

    /// Initializes the group header.
    template<typename Group>
    ONIXS_B3_BOE_HOTPATH
    void setupGroup(Group& group, typename Group::Size entryCount, const void* messageTail)
    {
        assert(messageTail);
        assert(group.valid());
        group.setup(entryCount, messageTail, blockEnd());
    }

    /// Initializes the group header, sets all optional fields to `null`.
    template<typename Group>
    ONIXS_B3_BOE_HOTPATH
    void constructGroup(Group& group, typename Group::Size entryCount, const void* messageTail)
    {
        assert(messageTail);
        assert(group.valid());
        group.construct(entryCount, messageTail, blockEnd());
    }

    /// Sets the variable length field value.
    template<typename DATA>
    void setVarDataField(DATA& data, StrRef value, const void* oldMessageTail)
    {
        assert(oldMessageTail);

        const ptrdiff_t lengthChange = static_cast<ptrdiff_t>(value.length() - data.length());

        const void* const newMessageTail = advanceByBytes(oldMessageTail, lengthChange);

        if ONIXS_B3_BOE_UNLIKELY(byteDistance(blockEnd(), newMessageTail) < 0)
            throwNotEnoughSpace();

        const void* const oldEndOfData = advanceByBytes(data.varData().data(), data.varData().size());

        void* const newEndOfData = toOpaquePtr(advanceByBytes(&data, value.length() + DATA::Size));

        std::memmove(newEndOfData, oldEndOfData, byteDistance(oldMessageTail, oldEndOfData));

        data.varData(value);
    }

    /// Binary group list instantiation.
    typedef SbeVariableLengthFieldList<MessageSize> VariableLengthFieldList;

    /// \return the list of variable-length fields.
    ONIXS_B3_BOE_HOTPATH
    VariableLengthFieldList variableLengthFields() ONIXS_B3_BOE_NOTHROW
    {
        assert(header_);

        void* list = advanceByBytes<void>(body(), blockLength());

        const MessageSize listSize = size_ - MessageHeader::Size - header_->blockLength();

        return VariableLengthFieldList(list, listSize, header_->version());
    }

    /// \return the list of variable-length fields.
    ONIXS_B3_BOE_HOTPATH
    VariableLengthFieldList variableLengthFields() const ONIXS_B3_BOE_NOTHROW
    {
        assert(header_);

        const void* list = advanceByBytes(block(), blockLength());

        const MessageSize listSize = size_ - MessageHeader::Size - header_->blockLength();

        return VariableLengthFieldList(const_cast<void*>(list), listSize, header_->version());
    }

    ONIXS_B3_BOE_HOTPATH
    void init(
        MessageHeader::TemplateId value,
        MessageHeader::BlockLength minimalBlockLength,
        MessageHeader::BlockLength blockLength,
        SchemaId id) ONIXS_B3_BOE_NOTHROW
    {
        assert(header_);
        assert(blockLength >= minimalBlockLength);

        header_->setTemplateId(value);
        header_->setBlockLength(blockLength);
        header_->setSchemaId(id);

        zeroPaddingBytes(minimalBlockLength);
    }

    ONIXS_B3_BOE_HOTPATH
    MessageSize calculateBinarySize(const void* tail) const ONIXS_B3_BOE_NOTHROW
    {
        assert(tail);

        const ptrdiff_t distance = byteDistance(tail, binary());

        assert(distance > 0);

        assert(distance <= (std::numeric_limits<MessageSize>::max)());

        const MessageSize size = static_cast<MessageSize>(distance);

        assert(size <= size_);

        return size;
    }

    /// Sets the value of the variable length field.
    template<class Callable, class Owner>
    void setVariableLengthField(Callable callable, StrRef value, Owner& owner)
    {
        setVarDataField(callable(owner), value, owner.tail());
    }

    /// Sets the value of the variable length field.
    template<class Callable, class Owner>
    void setVariableLengthField(Callable callable, StrRef value, SchemaVersion since, Owner& owner)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            throwDisallowedField();

        setVariableLengthField(callable, value, owner);
    }

    /// \return the value of the variable length field.
    template<class Callable, class Owner>
    StrRef getVariableLengthField(Callable callable, const Owner& owner) const ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CHECK_NOTHROW(callable(owner));
        return callable(owner).varData();
    }

    /// \return the value of the variable length field.
    template<class Callable, class Owner>
    StrRef getVariableLengthField(Callable callable, SchemaVersion since, Owner& owner) const ONIXS_B3_BOE_NOTHROW
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return StrRef();

        return getVariableLengthField(callable, owner);
    }

    /// Resets the variable length field.
    template<class Callable, class Owner>
    void setVariableLengthFieldToNull(Callable callable, Owner& owner) ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CHECK_NOTHROW(callable(owner));
        callable(owner).length(0);
    }

    /// Sets the group to the initial state.
    template<class Group, class Callable, class Owner>
    void resetGroup(Callable callable, Owner& owner) ONIXS_B3_BOE_NOTHROW
    {
        const typename Group::EntrySize entrySize = Group::Entry::blockLength(version());

        Group grp = callable(owner);

        initGroup(grp, entrySize);
    }

    /// Sets the variable length field to `null`.
    template<class Callable, class Owner>
    void setVariableLengthFieldToNull(Callable callable, SchemaVersion since, Owner& owner) ONIXS_B3_BOE_NOTHROW
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return;

        setVariableLengthFieldToNull(callable, owner);
    }

    /// Resets the repeating group.
    template<class Group, class Callable, class Owner>
    void resetGroup(Callable callable, SchemaVersion since, Owner& owner)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return;

        resetGroup<Group>(callable, owner);
    }

    /// \return the repeating group.
    template<class Group, class Callable, class Owner>
    Group getGroup(Callable callable, Owner& owner) const ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CHECK_NOTHROW(callable(owner));
        return callable(owner);
    }

    /// \return the repeating group.
    template<class Group, class Callable, class Owner>
    Group getGroup(Callable callable, SchemaVersion since, Owner& owner) const ONIXS_B3_BOE_NOTHROW
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return Group();

        return getGroup<Group>(callable, owner);
    }

    /// Creates a repeating group with the given number of entries, sets all optional fields of the group entries to null.
    template<class Group, class Callable, class Owner>
    Group constructGroup(Callable callable, typename Group::Size length, SchemaVersion since, Owner& owner)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return Group();

        return constructGroup<Group>(callable, length, owner);
    }

    /// Creates a repeating group with the given number of entries, sets all optional fields of the group entries to null.
    template<class Group, class Callable, class Owner>
    Group constructGroup(Callable callable, typename Group::Size length, Owner& owner)
    {
        Group group = callable(owner);

        constructGroup(group, length, owner.tail());

        return group;
    }

    /// Setups the repeating group with the given number of entries.
    template<class Group, class Callable, class Owner>
    Group setupGroup(Callable callable, typename Group::Size length, SchemaVersion since, Owner& owner)
    {
        if ONIXS_B3_BOE_UNLIKELY(since > version())
            return Group();

        return setupGroup<Group>(callable, length, owner);
    }

    /// Setups the repeating group with the given number of entries.
    template<class Group, class Callable, class Owner>
    Group setupGroup(Callable callable, typename Group::Size length, Owner& owner)
    {
        Group group = callable(owner);

        setupGroup(group, length, owner.tail());

        return group;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static MessageSize getMaxMessageSize() ONIXS_B3_BOE_NOTHROW
    {
        return
            MaxB3BOEMessageSize;
    }

private:
    MessageHeader* header_;
    MessageSize size_;
};

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
