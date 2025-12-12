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
#include <OnixS/B3/MarketData/UMDF/Integral.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>
#include <OnixS/B3/MarketData/UMDF/WatchService.h>
#include <OnixS/B3/MarketData/UMDF/LogSettings.h>

#include <string>
#include <vector>
#include <cassert>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                namespace System
                {
                    /// Current thread related tasks.
                    class ONIXS_B3_UMDF_MD_API ThisThread
                    {
                    public:
                        /// Sets the processor affinity mask for the current thread.
                        static void affinity(const System::ThreadAffinity&);
                        static void affinity(System::CpuIndex);

#if defined (_WIN32)
                        typedef unsigned int ThreadId;
#else
                        typedef pthread_t ThreadId;
#endif

                        static ThreadId threadId();
                    };
                }

                /// Designed to reflect various aspects of feed engine processing flow.
                class NetFeedEngineProcessResult
                {
                public:
                    /// Aliases integral type whose bits are used to indicate flag presence.
                    typedef UInt32 Flags;

                    ///
                    explicit NetFeedEngineProcessResult(UInt32 flags) ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        value_.raw_ = flags;
                    }

                    /// Indicates whether feed-related events like data reception or absence have been dispatched.
                    bool eventsDispatched() const ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        return 0 != value_.bits_.eventsDispatched_;
                    }

                    /// Indicates whether feed-related events like data reception or absence have been dispatched.
                    void eventsDispatched(bool state) ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        value_.bits_.eventsDispatched_ = state ? 1 : 0;
                    }

                    /// Indicates whether processing had to sleep in kernel while checking data availability.
                    bool ioWaited() const ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        return 0 != value_.bits_.ioWaited_;
                    }

                    /// Indicates whether processing had to sleep in kernel while checking data availability.
                    void ioWaited(bool state) ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        value_.bits_.ioWaited_ = state ? 1 : 0;
                    }

                    /// Reserved (unused) flags.
                    Flags reserved() const ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        return value_.bits_.reserved_;
                    }

                    /// Reserved (unused) flags.
                    void reserved(Flags flags) ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        value_.bits_.reserved_ = flags;
                    }

                private:
                    struct Bitset
                    {
                        Flags eventsDispatched_ : 1;
                        Flags ioWaited_         : 1;
                        Flags reserved_         : 30;
                    };

                    union Value
                    {
                        Bitset bits_;
                        Flags raw_;
                    };

                    Value value_;
                };

                /// The Feed Engine machinery
                class ONIXS_B3_UMDF_MD_API FeedEngine
                {
                public:
                    /// Provides information about the actual implementation of the feed engine.
                    std::string info();

                    ///
                    virtual ~FeedEngine();

                protected:
                    explicit FeedEngine(void* impl);

                protected:
                    FeedEngine(const FeedEngine&) =delete;
                    FeedEngine& operator=(const FeedEngine&) =delete;

                    void* const impl_;
                    friend struct FeHelper;
                };

                /// The given class implements feed engine concept using pool of working threads and standard socket API.
                class ONIXS_B3_UMDF_MD_API SocketFeedEngine : public FeedEngine
                {
                public:
                    /// Constructor
                    /// \param loggerSettings Defines feed engine logging settings.
                    /// \param socketBufferSize Defines size of receiving buffer in bytes for sockets.
                    /// \param dataWaitTime Defines amount of time Feed Engine spends on
                    /// waiting for I/O while running master processing loop. Time is measured in milliseconds.
                    ///
                    /// \param watch Watch service to be used by Feed Engine.
                    ///
                    /// Watch is used by Feed Engine to assign time
                    /// points to packets received from the feeds.
                    ///
                    /// @note By default, Utc watch service is used.
                    SocketFeedEngine(
                        const LoggerSettings& loggerSettings, UInt32 dataWaitTime = 10,
                        UInt32 socketBufferSize = 8 * 1024 * 1024, WatchService& watch = UtcWatch::service());

                    ///
                    explicit SocketFeedEngine(UInt32 dataWaitTime = 10, UInt32 socketBufferSize = 8 * 1024 * 1024,
                        WatchService& watch = UtcWatch::service());

                    /// Carries out pending actions like data retrieval and event dispatching.
                    /// This function must be invoked after each handler-associated action (i.e., start, stop).
                    NetFeedEngineProcessResult process();

                    ///
                    ~SocketFeedEngine() ONIXS_B3_UMDF_MD_OVERRIDE;
                };

                /// The given class implements feed engine concept.
                /// \note No external thread is allowed.
                class ONIXS_B3_UMDF_MD_API SingleThreadedSocketFeedEngine : public FeedEngine
                {
                public:
                    /// Constructor
                    /// \param loggerSettings Defines feed engine logging settings.
                    /// \param socketBufferSize Defines size of receiving buffer in bytes for sockets.
                    SingleThreadedSocketFeedEngine(
                        const LoggerSettings& loggerSettings,
                        UInt32 socketBufferSize = 8 * 1024 * 1024);

                    ///
                    /// \param socketBufferSize Defines size of receiving buffer in bytes for sockets.
                    explicit SingleThreadedSocketFeedEngine(UInt32 socketBufferSize = 8 * 1024 * 1024);

                    /// Carries out pending actions like data retrieval and event dispatching.
                    /// This function must be invoked after each handler-associated action (i.e., start, stop).
                    /// \note This function must not be invoked concurrently.
                    NetFeedEngineProcessResult process()
                    {
                        assert(threadId_ == System::ThisThread::threadId() && "External thread is detected.");
                        return processImpl();
                    }

                    ///
                    ~SingleThreadedSocketFeedEngine() override;

                private:
                    NetFeedEngineProcessResult processImpl();
                    const System::ThisThread::ThreadId threadId_ = System::ThisThread::threadId();
                };

                /// The given class implements feed engine concept.
                /// \note No external thread is allowed.
                class ONIXS_B3_UMDF_MD_API SingleThreadedHardwareTimestampSocketFeedEngine : public FeedEngine
                {
                public:
                    /// Constructor
                    /// \param loggerSettings Defines feed engine logging settings.
                    /// \param socketBufferSize Defines size of receiving buffer in bytes for sockets.
                    SingleThreadedHardwareTimestampSocketFeedEngine(
                        const LoggerSettings& loggerSettings,
                        UInt32 socketBufferSize = 8 * 1024 * 1024);

                    ///
                    /// \param socketBufferSize Defines size of receiving buffer in bytes for sockets.
                    explicit SingleThreadedHardwareTimestampSocketFeedEngine(UInt32 socketBufferSize = 8 * 1024 * 1024);

                    /// Carries out pending actions like data retrieval and event dispatching.
                    /// This function must be invoked after each handler-associated action (i.e., start, stop).
                    /// \note This function must not be invoked concurrently.
                    NetFeedEngineProcessResult process()
                    {
                        assert(threadId_ == System::ThisThread::threadId() && "External thread is detected.");
                        return processImpl();
                    }

                    ///
                    ~SingleThreadedHardwareTimestampSocketFeedEngine() override;

                private:
                    NetFeedEngineProcessResult processImpl();
                    const System::ThisThread::ThreadId threadId_ = System::ThisThread::threadId();
                };

                /// The given class implements the Feed Engine concept using the Solarlfare ef_vi SDK.
                /// \note VLAN is not supported.
                class ONIXS_B3_UMDF_MD_API EfViFeedEngine : public FeedEngine
                {
                public:
                    /// Constructor
                    /// \param loggerSettings Defines feed engine logging settings.
                    /// \param receiveRingSize Number of buffers in a virtual interface receive ring.
                    /// Single buffer is used for a single network packet.
                    /// Thus the receive ring must be capacious enough to
                    /// place incoming packets during market data bursts.
                    ///
                    /// \param watch Watch service to be used by Feed Engine.
                    ///
                    /// Watch is used by Feed Engine to assign time
                    /// points to packets received from the feeds.
                    ///
                    /// @note By default, NIC watch service is used.
                    EfViFeedEngine(const LoggerSettings& loggerSettings,
                        UInt32 receiveRingSize = 4095, WatchService& watch = NicWatch::service());

                    ///
                    explicit EfViFeedEngine(UInt32 receiveRingSize = 4095, WatchService& watch = NicWatch::service());

                    /// Carries out pending actions like data retrieval and event dispatching.
                    /// This function must be invoked after each handler-associated action (i.e., start, stop).
                    NetFeedEngineProcessResult process();

                    ///
                    ~EfViFeedEngine() ONIXS_B3_UMDF_MD_OVERRIDE;
                };

                /// The given class implements feed engine concept using the Solarlfare ef_vi SDK.
                /// \note No external thread is allowed.
                /// \note Sufficient amount of huge pages must be enabled.
                /// \note VLAN is not supported.
                /// \note Network interface card must be synchronized with the host's clock.
                /// \note Root permissions ir required.
                class ONIXS_B3_UMDF_MD_API SingleThreadedEfViFeedEngine : public FeedEngine
                {
                public:
                    /// Constructor
                    /// \param loggerSettings Defines feed engine logging settings.
                    /// \param ifName Network interface card name.
                    /// \param receiveRingSize Number of buffers in a virtual interface receive ring.
                    /// Single buffer is used for a single network packet. The receive ring must be capacious enough to
                    /// place incoming packets during market data bursts.
                    /// \param memregSize Size of allocated memory *in the number of 2Mb pages*, each page can fit 1024 packets
                    /// This memory is used to store packets during packet ordering and recovery for all the client handlers.
                    SingleThreadedEfViFeedEngine(const LoggerSettings& loggerSettings, const std::string& ifName, UInt16 memregSize = 512, UInt32 receiveRingSize = 1024);

                    /// Constructor
                    /// \param ifName Network interface card name.
                    /// \param receiveRingSize Number of buffers in a virtual interface receive ring.
                    /// Single buffer is used for a single network packet. The receive ring must be capacious enough to
                    /// place incoming packets during market data bursts.
                    /// \param memregSize Size of allocated memory *in the number of 2Mb pages*, each page can fit 1024 packets
                    /// This memory is used to store packets during packet ordering and recovery for all the client handlers.
                    explicit SingleThreadedEfViFeedEngine(const std::string& ifName, UInt16 memregSize = 512, UInt32 receiveRingSize = 1024);

                    /// Carries out pending actions like data retrieval and event dispatching.
                    /// This function must be invoked after each handler-associated action (i.e., start, stop).
                    /// \note This function must not be invoked concurrently.
                    /// \note This function must not be invoked as frequent as possible.
                    NetFeedEngineProcessResult process()
                    {
                        assert(threadId_ == System::ThisThread::threadId() && "External thread is detected.");
                        return processImpl();
                    }

                    ///
                    ~SingleThreadedEfViFeedEngine() override;

                private:
                    NetFeedEngineProcessResult processImpl();
                    const System::ThisThread::ThreadId threadId_ = System::ThisThread::threadId();
                };

                /// Carries out pending actions like data retrieval and event dispatching.
                /// The returned value indicates whether any events have been handled by the engine.
                template <typename EngineT>
                typename std::enable_if<std::is_base_of<FeedEngine, EngineT>::value, bool>::type
                process(EngineT& engine)
                {
                    return engine.process().eventsDispatched();
                }

                template <typename EngineT, typename... T>
                bool process(EngineT& engine, T &&... args)
                {
                    return process(engine) + process(args...);
                }

                /// Identifies reasons feed engine threads becomes idle.
                struct FeedEngineThreadIdle
                {
                    enum Reason
                    {
                        /// Thread waited for incoming data using corresponding
                        /// I/O operations (like 'select') and exited waiting with
                        /// no data availability signs.
                        DataWaitTimeout,

                        /// Thread entered idle state due to absence of any data and
                        /// while other threads are waiting for new incoming data.
                        Redundant
                    };
                };

                /// Settings for a thread pool executing feed engine tasks.
                struct FeedEngineThreadPoolSettings
                {
                    FeedEngineThreadPoolSettings()
                      : threadAffinity_()
                      , spinBeforeIdleTime_(1)
                      , threadCount_(1)
                    {
                    }

                    /// Defines set of CPUs allowed for each working thread
                    /// to be executed on while processing market data by Handlers
                    /// bound to Feed Engine instance which is configured by given
                    /// settings.
                    ///
                    /// @note By default set is empty thus allowing threads
                    /// to be executed on any CPU available in the system.
                    const System::ThreadAffinity& threadAffinity() const
                    {
                        return threadAffinity_;
                    }

                    /// Defines set of CPUs allowed for each working thread
                    /// to be executed on while processing market data by Handlers
                    /// bound to Feed Engine instance which is configured by given
                    /// settings.
                    ///
                    /// @note By default set is empty thus allowing threads
                    /// to be executed on any CPU available in the system.
                    System::ThreadAffinity& threadAffinity()
                    {
                        return threadAffinity_;
                    }

                    /// Number of working threads to be used by feed engine.
                    ///
                    /// @note Default value is '1'.
                    UInt32 threadCount() const
                    {
                        return threadCount_;
                    }

                    /// Sets threadsCount. @see threadsCount.
                    void threadCount(UInt32 value)
                    {
                        threadCount_ = value;
                    }

                    /// Defines amount of time Feed Engine keeps cycling before
                    /// going to sleep when no useful activity can be done.
                    ///
                    /// Time is measured in milliseconds.
                    ///
                    /// @note Default value is '1'.
                    ///
                    /// @warning Given parameter has direct influence onto CPU load!
                    UInt32 spinBeforeIdleTime() const
                    {
                        return spinBeforeIdleTime_;
                    }

                    /// Sets redundancySpinTime. @see redundancySpinTime.
                    void spinBeforeIdleTime(UInt32 value)
                    {
                        spinBeforeIdleTime_ = value;
                    }

                private:
                    System::ThreadAffinity threadAffinity_;
                    UInt32 spinBeforeIdleTime_;
                    UInt32 threadCount_;
                };

                class ONIXS_B3_UMDF_MD_API FeedEngineThreadPool;

                /// Listener for thread-related events.
                ///
                /// Members of this classes are invoked to reflect
                /// various life-time events of threads spawned and
                /// used by the feed engine while processing market data.
                struct ONIXS_B3_UMDF_MD_API FeedEngineThreadPoolListener
                {
                    /// Member invoked by feed engine when
                    /// a new processing thread is spawned.
                    ///
                    /// @note Invocation is done within newly
                    /// started thread.
                    virtual void onFeedEngineThreadBegin(const FeedEngineThreadPool&) {}

                    /// Member is invoked by feed engine when
                    /// processing thread is about to end.
                    ///
                    /// @note Invocation is done within the
                    /// thread that is about to end.
                    virtual void onFeedEngineThreadEnd(const FeedEngineThreadPool&) {}

                    /// Is called when feed engine's thread is idle.
                    ///
                    /// Integer parameter-variable defines amount of time feed engine
                    /// suggest for thread to sleep in kernel after invoking given member.
                    virtual void onFeedEngineThreadIdle(const FeedEngineThreadPool&, FeedEngineThreadIdle::Reason, UInt32&) {}

                    ///
                    virtual ~FeedEngineThreadPoolListener() = 0;
                };

                /// A pool of threads executing feed engine tasks.
                class ONIXS_B3_UMDF_MD_API FeedEngineThreadPool
                {
                public:
                    FeedEngineThreadPool(
                        const FeedEngineThreadPoolSettings&, FeedEngine*, FeedEngineThreadPoolListener* = ONIXS_B3_UMDF_MD_NULLPTR);

                    FeedEngineThreadPool(
                        const FeedEngineThreadPoolSettings&, const std::vector<FeedEngine*>&, FeedEngineThreadPoolListener* = ONIXS_B3_UMDF_MD_NULLPTR);

                    ~FeedEngineThreadPool();

                    const FeedEngineThreadPoolSettings& settings() const;

                private:
                    FeedEngineThreadPool(const FeedEngineThreadPool&);
                    FeedEngineThreadPool& operator=(const FeedEngineThreadPool&);

                    const FeedEngineThreadPoolSettings settings_;
                    class FeedEngineThreadPoolImpl;
                    FeedEngineThreadPoolImpl* const impl_;
                };
            }
        }
    }
}
