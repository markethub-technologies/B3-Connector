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

#include <OnixS/B3/BOE/ABI.h>

namespace OnixS {
namespace B3 {
namespace BOE {

/// TCP state information.

struct TcpInfo
{
    /// State of the connection
    struct TcpState
    {
        enum Enum
        {
            /// TCP connection is established
            Established = 1,

            /// TCP SYN packet has been sent
            SynSent,

            /// TCP SYN packet has been received
            SynRecv,

            /// TCP connection is in FIN wait state 1
            FinWait1,

            /// TCP connection is in FIN wait state 2
            FinWait2,

            /// TCP connection is in time wait state
            TimeWait,

            /// TCP connection is closing
            Close,

            /// TCP connection is in close wait state
            CloseWait,

            /// Last acknowledgment has been sent
            LastAck,

            /// TCP socket is listening for incoming connections
            Listen,

            /// TCP connection is in closing state
            Closing,

            /// TCP connection has received a new SYN packet
            NewSynRecv
        };
    };

    /// TCP congestion avoidance state
    struct TcpCaState
    {
        enum Enum
        {
            /// TCP congestion avoidance state: open
            Open = 0,

            /// TCP congestion avoidance state: disorder
            Disorder,

            /// TCP congestion avoidance state: congestion window reduced
            Cwr,

            /// TCP congestion avoidance state: recovery
            Recovery,

            /// TCP congestion avoidance state: loss
            Loss
        };
    };

    /// Represents the state of the TCP connection.
    TcpState::Enum state;

    /// Represents the congestion avoidance state of the TCP connection.
    TcpCaState::Enum caState;

    /// Number of retransmitted segments.
    UInt8 retransmits;

    /// Number of probe packets sent.
    UInt8 probes;

    /// Number of times the retransmission timer has been backed off.
    UInt8 backoff;

    /// TCP options (e.g., selective acknowledgments) enabled for the connection.
    UInt8 options;

    /// Sender's and receiver's window scale factors.
    /// Note: Each field is 4 bits wide.
    UInt8 sndWscale : 4, rcvWscale : 4;

    /// Retransmission timeout value in milliseconds.
    UInt32 rto;

    /// Predicted average time in milliseconds between transmission and acknowledgment.
    UInt32 ato;

    /// Maximum segment size (MSS) advertised by the sender.
    UInt32 sndMss;

    /// Maximum segment size (MSS) advertised by the receiver.
    UInt32 rcvMss;

    /// Number of segments sent but not yet acknowledged.
    UInt32 unacked;

    /// Number of selective acknowledgments received.
    UInt32 sacked;

    /// Number of lost segments.
    UInt32 lost;

    /// Number of retransmitted segments.
    UInt32 retrans;

    /// Number of forward acknowledgments (FACKs).
    UInt32 fackets;

    /* Metrics. */
    /// Path Maximum Transmission Unit (PMTU) estimate.
    UInt32 pmtu;

    /// Receiver's slow-start threshold.
    UInt32 rcvSsthresh;

    /// Smoothed round-trip time (RTT) estimate in microseconds.
    UInt32 rtt;

    /// Round-trip time variance estimate in microseconds.
    UInt32 rttvar;

    /// Sender's slow-start threshold.
    UInt32 sndSsthresh;

    /// Sender's congestion window size.
    UInt32 sndCwnd;

    /// Advertised maximum segment size (MSS).
    UInt32 advmss;

    /// Reordering metric.
    UInt32 reordering;

    /// Receiver's smoothed RTT estimate.
    UInt32 rcvRtt;

    /// Available receive buffer space in bytes.
    UInt32 rcvSpace;

    /// Total number of retransmissions.
    UInt32 totalRetrans;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_EXPORTED
    std::string toString() const;
};


}
}
}
