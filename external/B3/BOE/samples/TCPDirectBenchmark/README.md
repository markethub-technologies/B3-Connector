# TCPDirectBenchmark Sample

This sample shows how to measure latency on TCPDirect sessions and use the warm-up feature.

## Using TCPDirect Network Stack

[TCPDirect](https://www.openonload.org/) is part of Solarflare’s suite of network acceleration technologies.

The TCP loopback is not supported by TCPDirect technology, so the emulator should be started on a remote host
(or on a different physically connected card with a configured route to it).

For developing/debugging purposes, the OnixS B3 BOE SDK provides TCPDirect-mode emulation for Windows over usual sockets,
so TCPDirect Benchmark can be run in loopback mode under Windows.
