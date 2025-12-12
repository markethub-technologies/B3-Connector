#!/bin/bash

#LD_LIBRARY_PATH=$(pwd)
#export LD_LIBRARY_PATH

# specify interface name
ZF_ATTR="interface=xxxyyyzzz0;log_level=0xFF"
#ZF_ATTR="interface=xxxyyyzzz0;log_level=0xFFFFFFFF"

export ZF_ATTR

# specify marketSegmentId host port
./TCPDirectBenchmark 54 192.168.0.1 20054

#./zf_debug ./TCPDirectBenchmark 54 192.168.0.1 20054
