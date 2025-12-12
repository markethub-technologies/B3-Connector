// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
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

#include <ctime>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#ifdef _WIN32

#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <WS2tcpip.h>

#define IS_INVALID_SOCKET(SOCKETVAR) SOCKETVAR == INVALID_SOCKET

#if (_MSC_VER < 1600)
#define ETIMEDOUT WSAETIMEDOUT
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

typedef int socklen_t;
typedef long ssize_t;

int inet_aton(const char* strptr, struct in_addr* addrptr);
char const* getTextOfLastError();

#define SLEEP(n) Sleep(n)

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>

#define IS_INVALID_SOCKET(SOCKETVAR) SOCKETVAR < 0

char const* getTextOfLastError()
{
    return strerror(errno);
}

#define SLEEP(n) usleep((n*1000))

#endif

bool encode_base64(const void* src_buffer, size_t src_buffer_size, std::string& result);

const char* utcWithMs();

unsigned getSeqNum(const void* buffer);

bool isValidIpAddress(const char* ipAddress);

const char* getInterfaceIpAddress(const char* networkInterface);

void printUsage(const char* prog);

void closeFileWithFlush(FILE* file, bool flush);

const char* getArgs(int index, int size, char** args);

void printStatsHeader(time_t now);

void printStats(time_t now, ssize_t bytes, long numberOfPackets, const void* packet);

int main(int argc, char** argv)
{
    printf("Multicast Test for B3 MDH.\n");

    const int MAX_BUFFER_SIZE = 128 * 1024;
    const int DEFAULT_TIMEOUT = 30;

#ifdef _WIN32
    SOCKET sock = INVALID_SOCKET;
#else
    int sock = 0;

    setvbuf(stdout, NULL, _IOLBF, 0);
#endif

    bool verbose = false;
    const char* ip = NULL;
    u_short port = 0;
    const char* interfaceAddress = NULL;
    int timeoutInSeconds = DEFAULT_TIMEOUT;
    int udpBufferSizeInBytes = -1;
    const char* binaryFileName = NULL;
    const char* base64FileName = NULL;
    long maxPackets = 0;
    bool needFlush = false;
    unsigned int delay = 0;

    // Read command line arguments
    for(int idx = 1; idx < argc; ++idx)
    {
        const char* arg = argv[idx];

        if(strcmp(arg, "--ip") == 0)
        {
            ip = getArgs(++idx, argc, argv);
        }
        else if(strcmp(arg, "--port") == 0)
        {
            port = (u_short)atoi(getArgs(++idx, argc, argv));
        }
        else if(strcmp(arg, "--interface") == 0)
        {
            interfaceAddress = getArgs(++idx, argc, argv);
        }
        else if(strcmp(arg, "--timeout") == 0)
        {
            timeoutInSeconds = atoi(getArgs(++idx, argc, argv));
        }
        else if(strcmp(arg, "--udpBuffer") == 0)
        {
            udpBufferSizeInBytes = atoi(getArgs(++idx, argc, argv));
        }
        else if(strcmp(arg, "--binaryFile") == 0)
        {
            binaryFileName = getArgs(++idx, argc, argv);
        }
        else if(strcmp(arg, "--base64File") == 0)
        {
            base64FileName = getArgs(++idx, argc, argv);
        }
        else if(strcmp(arg, "--maxPackets") == 0)
        {
            maxPackets = atol(getArgs(++idx, argc, argv));
        }
        else if(strcmp(arg, "--flush") == 0)
        {
            needFlush = true;
        }
        else if(strcmp(arg, "--verbose") == 0)
        {
            verbose = true;
        }
        else if(strcmp(arg, "--delay") == 0)
        {
            delay = atoi(getArgs(++idx, argc, argv));
        }
        else
        {
            printUsage(argv[0]);
            return 1;
        }
    }

    if(ip == NULL)
    {
        fprintf(stderr, "\n *** ip not specified\n\n");
        printUsage(argv[0]);
        return 1;
    }

    if(port <= 0)
    {
        fprintf(stderr, "\n *** port is not < 0\n\n");
        printUsage(argv[0]);
        return 1;
    }

    if(timeoutInSeconds < 0)
    {
        fprintf(stderr, "\n *** timeout is not >= 0\n\n");
        printUsage(argv[0]);
        return 1;
    }

    if(maxPackets < 0)
    {
        fprintf(stderr, "\n *** maxPackets is not >= 0\n\n");
        printUsage(argv[0]);
        return 1;
    }

    printf("ip: %s\nport: %i\ninterface: %s\ntimeout: %d\nmaxPackets: %ld\n", ip, port, interfaceAddress ? interfaceAddress : "", timeoutInSeconds, maxPackets);

    // Initialize socket library
#ifdef _WIN32
    int ires;
    WSADATA wsa_data;
    if((ires = WSAStartup(MAKEWORD(2, 0), &wsa_data)) != 0)
    {
        fprintf(stderr, "Error calling WSAStartup: %d\n", ires);
        return 1;
    }
#endif

    // Initialize structures
    sockaddr_in address;
    sockaddr receiveAddress;
    socklen_t receiveLength;
    in_addr addr;
    in_addr interfaceAddr;
    ip_mreq mcastReq;

    memset(&address, 0, sizeof(address));
    memset(&receiveAddress, 0, sizeof(receiveAddress));
    memset(&addr, 0, sizeof(addr));
    memset(&interfaceAddr, 0, sizeof(interfaceAddr));
    memset(&mcastReq, 0, sizeof(mcastReq));

    // Create socket
    if(verbose) printf("Creating socket\n");

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    if(IS_INVALID_SOCKET(sock))
    {
        fprintf(stderr, "Error creating socket: %s\n", getTextOfLastError());
        return 1;
    }

    if(verbose) printf("Setting SO_REUSEADDR\n");

    const int ReuseAddrEnabled = 1;

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&ReuseAddrEnabled, sizeof(ReuseAddrEnabled)) < 0)
    {
        fprintf(stderr, "Error setting SO_REUSEADDR: %s\n", getTextOfLastError());
        return 1;
    }

    if(verbose) printf("Setting SO_RCVTIMEO\n");

#ifdef _WIN32
    DWORD tv = timeoutInSeconds * 1000;
#else
    timeval tv;

    tv.tv_sec = timeoutInSeconds;
    tv.tv_usec = 0;
#endif

    if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(tv)) < 0)
    {
        fprintf(stderr, "Error setting SO_REUSEADDR: %s\n", getTextOfLastError());
        return 1;
    }

    if(udpBufferSizeInBytes >= 0)
    {
        if(verbose) printf("Setting SO_RCVBUF\n");

        if(setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char*)&udpBufferSizeInBytes,
            sizeof(udpBufferSizeInBytes)) < 0)
        {
            fprintf(stderr, "Error setting SO_RCVBUF: %s\n", getTextOfLastError());
            return 1;
        }

        if(verbose) printf("Getting SO_RCVBUF\n");

        int value;
        socklen_t size = sizeof(value);

        if(getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&value, &size) < 0)
        {
            fprintf(stderr, "Error getting SO_RCVBUF: %s\n", getTextOfLastError());
            return 1;
        }

        bool requestedAreEqualToActual =
#if defined(WIN32)
            udpBufferSizeInBytes == value;
#elif defined(_LINUX)
            udpBufferSizeInBytes < 128 ? value == 256 : udpBufferSizeInBytes * 2 == value;
#endif

        if(!requestedAreEqualToActual)
        {
            fprintf(stderr, "Requested UDP buffer size value not equal to actual UDP buffer size value: %d != %d\n",
                udpBufferSizeInBytes, value);
            return 1;
        }

        if(verbose) printf("New value (%d) for SO_RCVBUF is set\n", value);
    }

    // Convert ip
    if(!inet_aton(ip, &addr))
    {
        fprintf(stderr, "Error converting ip to binary data\n");
        return 1;
    }

    // Initialize address
    if(verbose)
    {
        printf("Initializing socket address\n");
    }

    address.sin_family = AF_INET;
#ifdef _WIN32
    address.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    address.sin_addr.s_addr = addr.s_addr;
#endif
    address.sin_port = htons(port);

    // Bind
    if(verbose) printf("Binding\n");

    if(bind(sock, (struct sockaddr*) &address, sizeof(address)) < 0)
    {
        fprintf(stderr, "Error binding: %s\n", getTextOfLastError());
        return 1;
    }

    // Initialize the multicast request
    if(verbose) printf("Initializing the multicast request\n");

    mcastReq.imr_multiaddr.s_addr = addr.s_addr;

    if(interfaceAddress)
    {
        const char* interfaceIpAddress = getInterfaceIpAddress(interfaceAddress);

        if(verbose) printf("Initializing interface address\n");

        // Convert ip
        if(!inet_aton(interfaceIpAddress, &interfaceAddr))
        {
            fprintf(stderr, "Error converting interface to binary data\n");
            return 1;
        }

        mcastReq.imr_interface.s_addr = interfaceAddr.s_addr;
    }
    else
    {
        mcastReq.imr_interface.s_addr = htonl(INADDR_ANY);
    }

    if(verbose) printf("Joining multicast group\n");

    if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mcastReq, sizeof(mcastReq)) < 0)
    {
        fprintf(stderr, "Error joining group: %s\n", getTextOfLastError());
        return 1;
    }

    // Open bin file if specified
    FILE* binaryFile = NULL;

    if(binaryFileName)
    {
        if(verbose) printf("Opening binary file for writing\n");

        binaryFile = fopen(binaryFileName, "wb");

        if(binaryFile == NULL)
        {
            fprintf(stderr, "Error opening file '%s': %s\n", binaryFileName, getTextOfLastError());
            return 1;
        }
    }

    // Open Base64 file(with timestamps) if specified
    FILE* base64File = NULL;

    if(base64FileName)
    {
        if(verbose) printf("Opening Base64 file for writing\n");

        base64File = fopen(base64FileName, "w");

        if(base64File == NULL)
        {
            fprintf(stderr, "Error opening file '%s': %s\n", base64FileName, getTextOfLastError());
            return 1;
        }
    }

    // Test read/update/display loop
    ssize_t totalBytesRead = 0;
    long totalPacketsReceived = 0;
    time_t now = 0;
    time_t lastPrintAt = time(NULL);
    unsigned lastReceivedSeqNum = 0;

    char buffer[MAX_BUFFER_SIZE] = { 0 };

    printStatsHeader(lastPrintAt);

    if(verbose) printf("Entering test loop\n");

    for(;;)
    {
        if(delay != 0)
            SLEEP(delay);

        receiveLength = sizeof(receiveAddress);

        ssize_t bytesRead = recvfrom(sock, buffer, MAX_BUFFER_SIZE, 0, &receiveAddress, &receiveLength);
        const char* const packetTimestamp = utcWithMs();

        if(bytesRead < 0)
        {
#ifdef _WIN32
            const int lastError = WSAGetLastError();
            if(WSAETIMEDOUT == lastError)
#else

            if(errno == EAGAIN || errno == EWOULDBLOCK || errno == ETIMEDOUT)
#endif
            {

                fprintf(stderr, "No data receiving during %d sec.\n", timeoutInSeconds);
                continue;
            }
            else
            {
                fprintf(stderr, "Error reading from socket: %s\n", getTextOfLastError());
                closeFileWithFlush(binaryFile, true);
                closeFileWithFlush(base64File, true);
                return 1;
            }
        }

        const unsigned int currentSeqNum = getSeqNum(buffer);

        if(0 != currentSeqNum && 0 != lastReceivedSeqNum && int(currentSeqNum - lastReceivedSeqNum) > 1)
        {
            printf("%s: Message GAP detected: expected SeqNum=%u, received=%u, %u packets are missed\n",
                packetTimestamp, lastReceivedSeqNum + 1, currentSeqNum, currentSeqNum - lastReceivedSeqNum);
        }

        if(0 != currentSeqNum)
            lastReceivedSeqNum = currentSeqNum;

        now = time(NULL);

        ++totalPacketsReceived;
        totalBytesRead += bytesRead;

        if(difftime(now, lastPrintAt) >= 1)
        {
            printStats(now, totalBytesRead, totalPacketsReceived, buffer);
            lastPrintAt = now;
        }

        // Write to binary file if file is open
        if(binaryFile)
        {
            if(fwrite((void*)buffer, sizeof(unsigned char), bytesRead, binaryFile) != (size_t)bytesRead)
            {
                fprintf(stderr, "Error writing to binary file: %s\n", getTextOfLastError());
                closeFileWithFlush(binaryFile, NULL);
            }
            else if(needFlush)
            {
                fflush(binaryFile);
            }
        }

        if(base64File)
        {
            std::string packetInBase64;

            if(!encode_base64((void*) buffer, bytesRead, packetInBase64))
            {
                fprintf(stderr, "Error encoding packet data to Base64\n");
            }
            else
            {
                std::stringstream ss;

                ss << packetTimestamp << ' ' << packetInBase64 << std::endl;

                if(fputs(ss.str().c_str(), base64File) == EOF)
                {
                    fprintf(stderr, "Error writing to Base64 file: %s\n", getTextOfLastError());
                    closeFileWithFlush(base64File, false);
                }
                else if(needFlush)
                {
                    fflush(base64File);
                }
            }
        }

        if(maxPackets > 0 && totalPacketsReceived > maxPackets)
            break;
    }

    closeFileWithFlush(binaryFile, true);
    closeFileWithFlush(base64File, true);

    return 0;
}

// Base64 helper
const int CHARS_PER_LINE = 65000;

typedef enum
{
    step_A, step_B, step_C
} base64_encodestep;

typedef struct
{
    base64_encodestep step;
    char result;
    int stepcount;
} base64_encodestate;

void base64_init_encodestate(base64_encodestate* state_in)
{
    state_in->step = step_A;
    state_in->result = 0;
    state_in->stepcount = 0;
}

char base64_encode_value(char value_in)
{
    static const char* encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if(value_in > 63) return '=';
    return encoding[(int)value_in];
}

int base64_encode_block(const char* plaintext_in, int length_in, char* code_out, base64_encodestate* state_in)
{
    const char* plainchar = plaintext_in;
    const char* const plaintextend = plaintext_in + length_in;
    char* codechar = code_out;
    char result;
    char fragment;

    result = state_in->result;

    switch(state_in->step)
    {
    for(;;)
    {
    case step_A:
        if(plainchar == plaintextend)
        {
            state_in->result = result;
            state_in->step = step_A;
            return codechar - code_out;
        }
        fragment = *plainchar++;
        result =(fragment & 0x0fc) >> 2;
        *codechar++ = base64_encode_value(result);
        result =(fragment & 0x003) << 4;
    case step_B:
        if(plainchar == plaintextend)
        {
            state_in->result = result;
            state_in->step = step_B;
            return codechar - code_out;
        }
        fragment = *plainchar++;
        result |=(fragment & 0x0f0) >> 4;
        *codechar++ = base64_encode_value(result);
        result =(fragment & 0x00f) << 2;
    case step_C:
        if(plainchar == plaintextend)
        {
            state_in->result = result;
            state_in->step = step_C;
            return codechar - code_out;
        }
        fragment = *plainchar++;
        result |=(fragment & 0x0c0) >> 6;
        *codechar++ = base64_encode_value(result);
        result  =(fragment & 0x03f) >> 0;
        *codechar++ = base64_encode_value(result);

        ++(state_in->stepcount);
        if(state_in->stepcount == CHARS_PER_LINE/4)
        {
            *codechar++ = '\n';
            state_in->stepcount = 0;
        }
    }
    }
    /* control should not reach here */
    return codechar - code_out;
}

int base64_encode_blockend(char* code_out, base64_encodestate* state_in)
{
    char* codechar = code_out;

    switch(state_in->step)
    {
    case step_B:
        *codechar++ = base64_encode_value(state_in->result);
        *codechar++ = '=';
        *codechar++ = '=';
        break;
    case step_C:
        *codechar++ = base64_encode_value(state_in->result);
        *codechar++ = '=';
        break;
    case step_A:
        break;
    }
    *codechar++ = '\n';

    return codechar - code_out;
}

bool encode_base64(const void* src_buffer, size_t src_buffer_size, std::string& result)
{
    if(!src_buffer)
        return false;

    base64_encodestate state;

    base64_init_encodestate(&state);

    size_t saved_result_size = result.size();

    result.resize(saved_result_size + src_buffer_size * 2 + 5);

    int dst_length = base64_encode_block((const char*)src_buffer, src_buffer_size, &result[saved_result_size], &state);

    if(dst_length < 0)
        return false;

    int end_length = base64_encode_blockend(&result [saved_result_size + (size_t)dst_length], &state);

    if(end_length < 0)
        return false;

    result.resize(saved_result_size + (size_t)dst_length + (size_t)end_length);

    if(result[result.size() - 1] == '\n')
        result.resize(result.size() - 1);

    return true;
}

#ifdef _WIN32
int inet_aton(const char* strptr, struct in_addr* addrptr)
{
    if(!addrptr) return 0;

    inet_pton(AF_INET, strptr, &addrptr->s_addr);
    return(addrptr->s_addr != INADDR_NONE) ? 1 : 0;
}

char const* getTextOfLastError()
{
    static char message[1024] = { 0 };
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
        WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)message,
        sizeof(message), NULL);
    return message;
}
#endif


const char* utcWithMs()
{
    const size_t TIMESTAMP_STRING_SIZE = 22;
    static char buffer[TIMESTAMP_STRING_SIZE] = { 0 };

#ifdef _WIN32
    SYSTEMTIME t;
    ::GetSystemTime(&t);
    _snprintf(buffer, TIMESTAMP_STRING_SIZE - 1, "%04i%02i%02i-%02i:%02i:%02i.%03i",
        t.wYear, t.wMonth , t.wDay, t.wHour , t.wMinute , t.wSecond, t.wMilliseconds);
#endif

#ifdef _LINUX
    struct timeval tValue;

    if(0 != ::gettimeofday(&tValue, NULL)) {
        fprintf(stderr, "::gettimeofday() failed: %s\n", getTextOfLastError());
        return "00000000-00:00:00.000";
    }

    struct tm tBr;

    ::gmtime_r(&tValue.tv_sec, &tBr);

    snprintf(buffer, TIMESTAMP_STRING_SIZE - 1, "%04i%02i%02i-%02i:%02i:%02i.%03i",
        tBr.tm_year + 1900, tBr.tm_mon + 1, tBr.tm_mday, tBr.tm_hour, tBr.tm_min, tBr.tm_sec,
       (int)tValue.tv_usec / 1000);

#endif

    return buffer;
}

#pragma pack(push)
#pragma pack(1)
struct PacketHeader
{
    unsigned char channelId;
    unsigned char reserved;
    unsigned short sequenceVersion;
    unsigned int sequenceNumber;
    unsigned long sendingTime;
};
#pragma pack(pop)

unsigned int getSeqNum(const void* buffer)
{
    return reinterpret_cast<const PacketHeader*>(buffer)->sequenceNumber;
}

bool isValidIpAddress(const char* ipAddress)
{
    sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

const char* getInterfaceIpAddress(const char* networkInterface)
{
    if(!networkInterface)
        return "";

#ifdef _WIN32

    return networkInterface;

#else

    if(0 == strlen(networkInterface))
        return networkInterface;

    if(isValidIpAddress(networkInterface))
        return networkInterface;

    const char* retValue = "";
    ifaddrs* ifAddrStruct = NULL;

    if(getifaddrs(&ifAddrStruct) == -1)
        return retValue;

    for(ifaddrs* ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
        {
            if(0 == strcmp(networkInterface, ifa->ifa_name))
            {
                void* tmpAddrPtr = &((sockaddr_in *)ifa->ifa_addr)->sin_addr;
                static char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

                retValue = addressBuffer;
                break;
            }
        }
    }

    if(ifAddrStruct != NULL)
        freeifaddrs(ifAddrStruct);

    return retValue;

#endif
}

void printUsage(const char* prog)
{
    printf("Usage:\n");
    printf("  %s --help\n", prog);
    printf("  %s --ip <ip> --port <port>\n", prog);
    printf("\nwhere\n");
    printf("  --help       : Print usage information\n");
    printf("  --ip         : Specifies multicast group host\n");
    printf("  --port       : Specifies multicast group port\n");
    printf("\noptional args\n");
    printf("  --verbose    : Display program progress (this option disables pretty printing)\n");
    printf("  --interface  : Specifies network interfaces to use while joining the multicast group\n");
    printf("  --timeout    : Specifies timeout in seconds for receive operation. Default timeout is 30 seconds\n");
    printf("  --udpBuffer  : Specifies UDP buffer size in bytes for receive operation. Default value defined by OS\n");
    printf("  --binaryFile : Output file to write multicast binary pitch data to (Optional)\n");
    printf("  --base64File : Output file to write multicast Base64 pitch data to (Optional)\n");
    printf("  --maxPackets : Stop processing after maxPackets packets have been received\n");
    printf("  --flush      : Flush output files for each received packet\n");
    printf("  --delay      : Receive delay in milliseconds\n");
    printf("\n");
}

void closeFileWithFlush(FILE* file, bool flush)
{
    if(file)
    {
        if(flush)
        {
            if(fflush(file) != 0)
            {
                fprintf(stderr, "Error flushing: %s\n", getTextOfLastError());
            }
        }

        fclose(file);
        file = NULL;
    }
}

const char* getArgs(int index, int size, char** args)
{
    if(index < size)
    {
        return args[index];
    }
    else
    {
        fprintf(stderr, "getArgs: Index exceeds args size\n");
        exit(1);
    }
}

void printStatsHeader(time_t now)
{
    static char dateStr[11] = { 0 };
    size_t n = strftime(dateStr, 11, "%m/%d/%Y", localtime(&now));
    dateStr[n] = '\0';

    printf("Date: %s\n", dateStr);
    printf("%17s: %14s%15s%15s\n", "Timestamp", "Bytes", "Packets", "SeqNum");
}

void printStats(time_t now, ssize_t bytes, long numberOfPackets, const void* packet)
{
    static char timestamp[20] = { 0 };
    size_t n = strftime(timestamp, sizeof(timestamp)-1, "%Y%m%d-%H:%M:%S", gmtime(&now));
    timestamp[n] = '\0';

    const PacketHeader* const header = reinterpret_cast<const PacketHeader*>(packet);

    std::cout
        << std::setw(17) << timestamp
        << std::setw(14) << bytes
        << std::setw(15) << numberOfPackets
        << std::setw(15) << header->sequenceNumber
        << std::setw(8) << (int)header->channelId
        << std::setw(8) << header->sequenceVersion;
}
