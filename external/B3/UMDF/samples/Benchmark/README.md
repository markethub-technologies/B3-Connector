Benchmark Sample
===================================================================

This sample measures the execution time of API functionality within a library. It provides two measurement modes:

1. Packet Reception to The First Callback (Messaging):
   Measures the time elapsed from receiving a data packet through a multicast socket to invocating the first callback for a message within that packet.

   ./Benchmark --channel 80 --packetsCount 10000 --connectivity ../Settings/config.Prod.xml --ifA n1 --ifB n2


2. Atomic Order Book Update Time:
   Measures the time required for an atomic update of the order book. Specifically, it tracks the duration from receiving an order change message
   within a packet to when the callback confirms that the message has been applied (OrderBookListener::onOrderBookChanged is called).

   ./Benchmark --channel 80 --measureBookChanges --chunksAmount 10000 --packetsCount 10000 --connectivity ../Settings/config.Prod.xml --ifA n1 --ifB n2
   
This sample helps analyze the performance of API calls related to market data processing.

To get all other command line parameters:

   ./Benchmark --help
