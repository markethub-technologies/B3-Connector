#!/bin/bash

export EF_TCP_CLIENT_LOOPBACK=1
export EF_TCP_SERVER_LOOPBACK=1

# The latency profile sets the EF_POLL_USEC=100000 setting the busy-wait spin timeout to 100 milliseconds.
onload --profile=latency ./TCPStandardBenchmark $@
