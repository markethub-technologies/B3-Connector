/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by ONIX SOLUTIONS LIMITED [ONIXS] and is protected by copyright law
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

#include <string>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {

                /// Log level.
                struct ONIXS_B3_UMDF_MD_API LogLevel
                {
                    enum Enum
                    {
                        Disabled,   /// Logging disabled.
                        Error,      /// Error, cannot continue.
                        Warning,    /// Warning, can continue.
                        Info,       /// Information message.
                        Trace,      /// Used for tracing, usually including functions' names and args.
                        Debug,      /// Used for debugging.
                    };
                };

                /// Returns string representation of ErrorCode value.
                ONIXS_B3_UMDF_MD_API std::string enumToString (LogLevel::Enum);

                /// Logging options.
                struct ONIXS_B3_UMDF_MD_API LogSettings
                {
                    enum Enum
                    {
                        /// Trace to the log file.
                        TraceToFile = 0x01,

                        /// Duplicate log messages to console.
                        /// @note Messages with LogLevel::Trace and LogLevel::Debug are not duplicated to console.
                        TraceToConsole = 0x02,

                        /// Use asynchronous logging
                        Async = 0x4,

                        /// if TraceToConsole is set, then direct output to stderr
                        ConsoleErr = 0x8,

                        /// if TraceToConsole is set, then set up colored output mode
                        ConsoleColored = 0x10,

                        /// if TraceToConsole is set, then append prefix to output
                        ConsoleShowPrefix = 0x20,

                        /// Log binary data of received packets, applied only for Info log level and below.
                        LogPackets = 0x40,

                        /// Log updated order book, applied only for Debug log level.
                        LogBooks = 0x80,

                        /// Default log settings.
                        Default = TraceToFile | LogPackets | LogBooks
                    };
                };

                /// Typed logical operator helper.
                inline LogSettings::Enum operator| (LogSettings::Enum a, LogSettings::Enum b)
                {
                    return LogSettings::Enum ( static_cast<int>(a) | static_cast<int>(b));
                }


                /// Log file read permissions.
                struct ONIXS_B3_UMDF_MD_API LogFilePermission
                {
                    enum Enum
                    {
                        /// read access only for owner of process
                        ReadOwnerOnly = 0x01,

                        /// read access for all
                        ReadAll = 0x02,

                        /// write access only for owner of process
                        WriteOwnerOnly = 0x04,

                        /// write access for all
                        WriteAll = 0x08,

                        /// Default value
                        Default = ReadAll | WriteOwnerOnly
                    };
                };

                /// Typed logical operator helper.
                inline LogFilePermission::Enum operator| (LogFilePermission::Enum a, LogFilePermission::Enum b)
                {
                    return static_cast<LogFilePermission::Enum> (static_cast<int> (a) | static_cast<int> (b) );
                }

                /// Logger-related settings
                struct LoggerSettings
                {
                    /// Constructor.
                    LoggerSettings()
                      : logDirectory("logs")
                      , logFileNamePrefix("B3Umdf")
                      , logSettings(LogSettings::Default)
                      , logLevel(LogLevel::Info)
                      , logFilePermissions(LogFilePermission::Default)
                    {}

                    /// Log files are stored in this directory.
                    std::string logDirectory;

                    /// Template of log file name without extension.
                    std::string logFileNamePrefix;

                    /// Combine LogSettings enum values to configure the logger.
                    LogSettings::Enum logSettings;

                    /// Log verbosity.
                    ///
                    /// @note The default value is LogLevel::Info
                    LogLevel::Enum logLevel;

                    /// Log file permissions.
                    ///
                    /// @note The default value is ReadAll | WriteOwnerOnly
                    LogFilePermission::Enum logFilePermissions;
                };

                ONIXS_B3_UMDF_MD_API std::ostream& operator<<(std::ostream& stream, const LoggerSettings& settings);
            }
        }
    }
}
