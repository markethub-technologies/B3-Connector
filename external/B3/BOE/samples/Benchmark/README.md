# Benchmark Sample

This sample shows how to measure latency and use the warm-up feature.

## Using OpenOnload® Network Stack

[OpenOnload](https://www.openonload.org/) is part of Solarflare’s suite of network acceleration technologies.

To achieve better results, use the `latency` profile. For example:

    ./run-under-onload.sh 54 192.168.28.1 20054 1 2

### TCP Loopback Acceleration

The TCP loopback acceleration is turned **off** by default. It is configured via the environment variables `EF_TCP_CLIENT_LOOPBACK`
and `EF_TCP_SERVER_LOOPBACK`.

#### Activate

    export EF_TCP_CLIENT_LOOPBACK=1
    export EF_TCP_SERVER_LOOPBACK=1

#### Verify

    echo $EF_TCP_CLIENT_LOOPBACK
    echo $EF_TCP_SERVER_LOOPBACK
