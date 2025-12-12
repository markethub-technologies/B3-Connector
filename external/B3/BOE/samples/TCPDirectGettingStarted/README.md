# TCPDirect Getting Started Sample Project

This sample shows how to connect TCPDirect session to the pre-defined host and port.

When the session is established, the `'SingleOrder - New'(MsgType='D')` message is sent to the
counterparty.

## Using TCPDirect Network Stack

[TCPDirect](https://www.openonload.org/) is part of Solarflare�s suite of network acceleration technologies.

The TCP loopback is not supported by TCPDirect technology, so the emulator should be started on a remote host
(or on a different physically connected card with a configured route to it).

For developing/debugging purposes, the OnixS B3 BOE SDK provides TCPDirect emulation for Windows over usual sockets,
so the TCPDirect Getting Started sample can be run in loopback mode under Windows.
