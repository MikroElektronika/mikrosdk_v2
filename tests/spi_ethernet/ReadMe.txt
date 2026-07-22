This example is meant for testing the SPI Ethernet communication (ETH Click, ENC28J60) on MikroE boards.

The example initializes SPI, configures the ENC28J60 chip with a static IP and MAC address and waits for the Ethernet link to come up.

Test is considered successful if the board responds to ARP requests and ICMP pings (e.g. `ping 172.20.22.200`) and serves the HTML page when accessing `http://172.20.22.200` from a browser or via `curl -v http://172.20.22.200/` on the same network.

NOTE: An Ethernet cable connection to a local network is required for conducting this test. Test connectivity in normal Run mode, not debug mode, as debug latency can cause the TCP handshake to time out.