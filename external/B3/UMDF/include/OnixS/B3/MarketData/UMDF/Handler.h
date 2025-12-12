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

#include <unordered_set>
#include <vector>

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/LogSettings.h>
#include <OnixS/B3/MarketData/UMDF/HandlerStateListener.h>
#include <OnixS/B3/MarketData/UMDF/Replay.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Fields.h>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                namespace Implementation { struct ReplayHelper; }
                class ErrorListener;
                class FeedEngine;
                class WarningListener;
                class MessageListener;
                class OrderBookListener;

                struct HandlerSettings;

                /// B3 Binary UMDF Market Data Handler class.
                class ONIXS_B3_UMDF_MD_API Handler
                {
                    public:
                        /// Performs instance initialization.
                        /// @param settings defines values for various options
                        /// which affect handler behavior like enabling logging
                        /// during execution of the handler.
                        explicit
                        Handler (const HandlerSettings& settings);

                        /// Finalizes the Handler.
                        virtual ~Handler();

                        /// Assigns listener for errors occurred while executing handler.
                        /// It's permissible to change the listener multiple times during
                        /// handler's life-time, but only when it is in disconnected state.
                        /// @throw OperationException if handler not disconnected
                        void registerErrorListener (ErrorListener* listener);

                        /// Assigns listener for warnings occurred while executing handler.
                        /// It's permissible to change the listener multiple times during
                        /// handler's life-time, but only when it is in disconnected state.
                        /// @throw OperationException if handler not disconnected
                        void registerWarningListener (WarningListener* listener);

                        /// Assigns listener for state change events occurred while executing handler.
                        /// It's permissible to change the listener multiple times during
                        /// handler's life-time, but only when it is in disconnected state.
                        /// @throw OperationException if handler not disconnected.
                        void registerHandlerStateListener (HandlerStateListener* listener);

                        /// Assigns listener to receive notifications when market data messages are received while executing handler.
                        /// It's permissible to change the listener multiple times during
                        /// handler's life-time, but only when it is in disconnected state.
                        /// @throw OperationException if handler not disconnected.
                        void registerMessageListener (MessageListener* listener);

                        /// Assigns listener to receive notification about order book states while executing handler.
                        /// It's permissible to change the listener multiple times during
                        /// handler's life-time, but only when it is in disconnected state.
                        /// @throw OperationException if handler not disconnected.
                        void registerOrderBookListener (OrderBookListener* listener);

                        /// Start handler.
                        ///
                        /// @note This action is asynchronous.
                        /// @throw std::exception in case of unable to start.
                        void start ();

                        /// Stop handler.
                        void stop (bool wait);

                        /// Returns handler state.
                        HandlerState::Enum state () const;

                        /// Logs the given user-level message to the handler log.
                        void log (LogLevel::Enum logLevel, const char* logMessage, size_t length);

                        /// Logs the given user-level message to the handler log
                        void log (LogLevel::Enum logLevel, const char* logMessage);

                        /// Logs the given user-level message to the handler log.
                        void log (LogLevel::Enum logLevel, const std::string& str);

                        /// Returns the license expiration date.
                        std::string licenseExpirationDate () const;

                        /// Returns Handler's version.
                        static const char* version ();

                        /// Starts replaying previously logged data.
                        void replayLogs (const ReplayOptions& options);

                        /// Replay pcap files.
                        void replayPcap (const ReplayOptions& options, const FilesList& instrument, const FilesList& snapshot);

                        /// Adds security id to the security filter
                        Handler& subscribe(Messaging::SecurityID securityId);

                        /// Adds a few security ids to the security filter
                        Handler& subscribe(std::initializer_list<Messaging::SecurityID> securityIds);

                        /// Removes security id from the security filter
                        Handler& unsubscribe(Messaging::SecurityID securityId);

                        /// Removes a few security ids from the security filter
                        Handler& unsubscribe(std::initializer_list<Messaging::SecurityID> securityIds);

                    private:
                        Handler (const Handler&); //no implementation
                        Handler& operator = (const Handler&); //no implementation

                    private:
                        friend struct Implementation::ReplayHelper;
                        struct Impl;
                        Impl* impl_;
                };

                /// Replays pcap files.
                ONIXS_B3_UMDF_MD_API
                void replayPcap (const std::vector<Handler*>& handlers, const ReplayOptions& options, const FilesList& instrument, const FilesList& snapshot, bool* stopRequest = nullptr);

                /// Replays log files.
                ONIXS_B3_UMDF_MD_API
                void replayLog (const std::vector<Handler*>& handlers, const ReplayOptions& options, bool* stopRequest = nullptr);
            }
        }
    }
}
