// Copyright 2005-2012 Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
// and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable ONIXS Software
// Services Agreement (the Agreement) and Customer end user license agreements granting
// a non-assignable, non-transferable and non-exclusive license to use the software
// for it's own data processing purposes under the terms defined in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
// of this source code or associated reference material to any other location for further reproduction
// or redistribution, and any amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in accordance with
// the terms of the Agreement is a violation of copyright law.
//
#pragma once

#include <OnixS/B3/MarketData/UMDF/ABI.h>

#include <vector>
#include <string>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Ordered list of logs to be replayed.
                typedef std::vector<std::string> HandlerLogs;

                /// Read-write iterator over ordered list of logs to be replayed.
                typedef std::vector<std::string>::iterator HandlerLogsEntry;

                /// Listening interface for log replay-related events.
                class ONIXS_B3_UMDF_MD_API ReplayListener
                {
                    public:
                        /// Is called once an error occurs while replaying logs.
                        virtual void onReplayError (const std::string& errorDescription) = 0;

                        /// Is called once all the logs are replayed.
                        virtual void onReplayFinished() = 0;

                    protected:
                        /// Deletion is not supposed
                        /// through interface of this class.
                        virtual ~ReplayListener();
                };

                /// Logging options.
                struct ONIXS_B3_UMDF_MD_API ReplayMode
                {
                    enum Enum
                    {
                        /// The packets are replayed with constant delay, defined by ReplayOptions::packetReplayDelay
                        /// Timestamps from the replayed file are ignored
                        /// ReplayOptions::playSpeedMultiplier is ignored
                        ConstantPacketReplayDelay = 1,

                        /// The packets are replayed with delays as it comes from the replayed file.
                        /// FinalDelay = LogFileDelay * ReplayOptions::playSpeedMultiplier + ReplayOptions::packetReplayDelay
                        NaturalPacketReplayDelay = 2
                    };
                };


                /// @typedef FilesList
                /// Ordered list of files to be replayed.
                typedef std::vector<std::string> FilesList;

                /// Gathers files which are stored in a given folder.
                void ONIXS_B3_UMDF_MD_API gatherFiles(FilesList* gatheredFiles, const std::string& root, const std::string& extension);

                /// Gathers log files which are stored in a given folder.
                inline
                void gatherLogs(FilesList* gatheredLogs, const std::string& root)
                {
                    gatherFiles(gatheredLogs, root, ".log");
                }

                /// Defines params which affect replay.
                struct ReplayOptions
                {
                    /// List of files to be replayed.
                    /// Must be stored in 'oldest to recent' order.
                    FilesList files;

                    /// Instance to notify about replay events.
                    ReplayListener* listener;

                    /// Specifies the time delay (milliseconds) between replayed packets.
                    ///
                    /// @note Ability to control replay rate.
                    unsigned int packetReplayDelay = 0;

                    /// Replay multiplier. Used only in ReplayMode::NaturalPacketReplayDelay
                    float playSpeedMultiplier = 0.0f;

                    /// Replay mode.
                    ReplayMode::Enum replayMode = ReplayMode::ConstantPacketReplayDelay;

                    /// Initializes instance with default values.
                    ReplayOptions()
                      : listener(defaultReplayListener())
                    {
                    }

                    /// Initializes with all the files which are available and stored in a given folder.
                    explicit
                    ReplayOptions (const std::string& filesRoot, const std::string& extension = ".log")
                      : listener(defaultReplayListener())
                    {
                        gatherFiles(&files, filesRoot, extension);
                    }

                private:
                    ONIXS_B3_UMDF_MD_API static ReplayListener* defaultReplayListener();
                };
            }
        }
    }
}
