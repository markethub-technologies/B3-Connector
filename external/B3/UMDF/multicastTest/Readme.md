### Multicast analyzer.

- Building:

  On Linux:
    Using make: `make`
    Using gcc:  `g++ -D_LINUX -o multicastTest MulticastTest.cpp`

  On Windows:
    `cl /EHsc MulticastTest.cpp`

- Usage information:

  On Linux:
    `./multicastTest --help`
    `./multicastTest --ip <ip> --port <port>`

  On Windows:
    `MulticastTest.exe --help`
    `MulticastTest.exe --ip <ip> --port <port>`

  where
    `--help`       : Print usage information
    `--ip`         : Specifies multicast group host
    `--port`       : Specifies multicast group port

  optional args
    `--verbose`    : Display program progress (this option disables pretty printing)
    `--interface`  : Specifies network interfaces to use while joining the multicast group
    `--timeout`    : Specifies timeout in seconds for receive operation. Default timeout is 30 seconds
    `--udpBuffer`  : Specifies UDP buffer size in bytes for receive operation. Default value defined by OS
    `--binaryFile` : Output file to write multicast binary pitch data to (Optional)
    `--base64File` : Output file to write multicast Base64 pitch data to (Optional)
    `--maxPackets` : Stop processing after maxPackets packets have been received
    `--flush`      : Flush output files for each received packet
    `--delay`      : Delay in milliseconds before each read operation from socket


the command line could be: `./multicastTest --ip 233.252.8.119 --port 20088 --interface enp130s0f1 --udpBuffer 8388608`.
