/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable OnixS Software
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

#include <OnixS/B3/BOE/messaging/Time.h>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Tools {

/// Audit Trail Spreadsheet Generator
class ONIXS_B3_BOE_EXPORTED AuditTrailGenerator
{
public:
    /**
    * Constructor.
    *
    * \param fileName A log file file to analyze.
    * \param cmeTradeDayStartTimeUtc Trade day start time in UTC.
    * \param outputFieldDelimiter Output field delimiter.
    * \param outputFilenameExtension Output filename extension.
    */
    AuditTrailGenerator(
        const std::string& fileName
      , const Messaging::Timestamp& cmeTradeDayStartTimeUtc = Messaging::Timestamp(1970, Messaging::Month::January, 1, 0, 0, 0)
      , char outputFieldDelimiter = ','
      , const char* outputFilenameExtension = "csv"
    );

    /**
    * Constructor.
    *
    * \param fileName A log file to analyze.
    * \param outputPath Output file path.
    * \param outputBaseName Output file base name.
    * \param cmeTradeDayStartTimeUtc Trade day start time in UTC.
    * \param outputFieldDelimiter Output field delimiter.
    * \param outputFilenameExtension Output filename extension.
    */
    AuditTrailGenerator(
        const std::string& fileName
        , const std::string& outputPath
        , const std::string& outputBaseName
        , const Messaging::Timestamp& cmeTradeDayStartTimeUtc = Messaging::Timestamp(1970, Messaging::Month::January, 1, 0, 0, 0)
        , char outputFieldDelimiter = ','
        , const char* outputFilenameExtension = "csv"
    );

    /// Generate the output.
    void generate();

    ///
    ~AuditTrailGenerator();

private:
    struct Impl;
    Impl* const impl_;
};

}}}}
