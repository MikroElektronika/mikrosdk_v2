This example is meant for testing the LAN8651 SPI Ethernet driver with Two-Wire ETH Click and Two-Wire ETH 3 Click (10BASE-T1S) on a single MikroE board, without any external network equipment.

One click (node A) is placed on mikroBUS 1 and the other click (node B) on mikroBUS 5, so the two clicks use different SPI modules (mikroBUS 2 is used if the board has no mikroBUS 5; positions can be changed with MIKROBUS_POSITION_NODE_A/B). The TRX terminals of the two clicks are connected with a twisted pair (N to N, P to P) and the TERM jumpers are placed on both clicks, as they are the two ends of the segment.

The example initializes both clicks and runs the following sequence, logging every step on the USB UART terminal:
- raw frames A -> B and B -> A (short and multi-chunk, up to 1514 bytes),
- ARP request/reply in both directions,
- ICMP ping A -> B and B -> A.
After the sequence, node A keeps pinging node B once per second.

Test is considered successful if the log ends with "TEST PASSED" and the continuous ping reports OK. Disconnecting one wire of the pair must make the ping time out, reconnecting it must make it recover.

NOTE: The default mode is CSMA/CD. Set USE_PLCA to 1 to test PLCA (node A is the coordinator, node B is node 1); in PLCA mode node B reports link up only while it receives beacons from node A.
