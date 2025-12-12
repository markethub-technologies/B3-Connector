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

#include "stdafx.h"

//! [SbeLogDecoderSample]
namespace
{
    struct MessagePrinter
    {
        MessagePrinter(ofstream& outFile, StrRef prefix)
            : outFile_(outFile)
            , prefix_(prefix)
        {}

        template <typename MessageType>
        void operator()(const MessageType& msg) const
        {
            outFile_ << prefix_ << msg << endl << endl;

            std::cout << prefix_ << msg << endl << endl;
        }

        ofstream& outFile_;
        const StrRef prefix_;
    };

    std::string getOutputFileName(const std::string& entryName)
    {
        const char * const DecodedSummaryFileExtension = ".txt";
        return entryName.substr(0, entryName.find_last_of(".")) + DecodedSummaryFileExtension;
    }

    size_t decodeSbeLogFile(const string& summaryFileName)
    {
        const std::string outputFileName = getOutputFileName(summaryFileName);
        ofstream decoded(outputFileName.c_str());

        if (!decoded)
            throw runtime_error("Cannot create file: '" + outputFileName + "'");

        ifstream file(summaryFileName.c_str());

        if (!file)
            throw runtime_error("Cannot open " + summaryFileName + " log file.");

        const size_t LogLinePrefixSize = 32;

        string line;
        ByteArray buffer;
        size_t messageCounter = 0;

        while (getline(file, line))
        {
            try
            {
                const StrRef Prefix(line.data(), LogLinePrefixSize);
                const StrRef Base64SbeMessage(line.data() + LogLinePrefixSize, line.size() - LogLinePrefixSize);

                Base64Encoding::decode(buffer, Base64SbeMessage);

                if (buffer.empty())
                    throw runtime_error("Cannot decode an empty message");

                const bool sofhDetected =
                    buffer.size() >= sizeof(SimpleOpenFramingHeader) &&
                    reinterpret_cast<const SimpleOpenFramingHeader*>(&buffer[0])->encoding() == B3BOESbeEncodingType;

                SbeMessage message;
                if(sofhDetected)
                    message = NetworkMessage(&buffer[0], static_cast<MessageSize>(buffer.size())).message();
                else
                    message = SbeMessage(&buffer[0], static_cast<MessageSize>(buffer.size()));

                assert(message.valid());

                if (!processTypified(message, MessagePrinter(decoded, Prefix)))
                    throw runtime_error("Unknown message type");

                ++messageCounter;
            }
            catch (...)
            {
                cerr << "Cannot decode '" << line << "'" << endl;
                throw;
            }
        }

        return messageCounter;
    }

    void gatherFiles(std::vector<std::string>& gatheredFiles, const std::string& root)
    {
        if(OnixS::B3::BOE::Filesystem::isDirectory(root))
            OnixS::B3::BOE::Filesystem::gatherFiles(&gatheredFiles, root, ".summary");
        else
            gatheredFiles.push_back(root);
    }

    class FileDecoder
    {
    public:
        FileDecoder()
            : messagesCount_(0)
            , filesCount_(0)
        {
        }

        void operator()(const std::string& name)
        {
            messagesCount_ += decodeSbeLogFile(name);
            ++filesCount_;
        }

        size_t messagesCount() const
        {
            return messagesCount_;
        }

        size_t filesCount() const
        {
             return filesCount_;
        }

    private:
        size_t messagesCount_;
        size_t filesCount_;
    };
}

void usage()
{
    cerr << "usage: SbeLogDecoder [SummaryFileName|DirectoryName]" << endl;
}

int main(int argc, char* argv[])
{
    clog << "B3 BOE SBE Log Decoder Sample." << endl << endl;

    string arg;

    if (argc >= 2)
        arg = argv[1];

    if (arg.empty())
    {
        usage();
        return 1;
    }

    if(!OnixS::B3::BOE::Filesystem::exist(arg))
    {
        cerr << "'" + arg + "'" + " does not exist.";
        return 1;
    }

    std::vector<std::string> inputFiles;
    gatherFiles(inputFiles, arg);

    const FileDecoder decoder =
        std::for_each(inputFiles.begin(), inputFiles.end(), FileDecoder());

    clog << decoder.messagesCount() << " messages in " << decoder.filesCount() << " file(s) are decoded." << endl << endl;

    return 0;
}
//! [SbeLogDecoderSample]
