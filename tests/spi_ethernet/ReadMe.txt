This example is meant for testing the SPI Ethernet communication on MikroE boards.

The example initializes SPI and the selected Ethernet controller (SPI_ETH_CHIP: ENC28J60, W5500/WIZ_IP55, W6100, LAN9250 or LAN8651, ENC28J60 by default), waits for the Ethernet link to come up and obtains an IP address over DHCP (USE_DHCP = 1, default). If DHCP fails, or with USE_DHCP = 0, the static IP address 172.20.22.200 is used.

Test is considered successful if the board responds to ARP requests and ICMP pings (e.g. `ping <board IP>`) and serves the HTML page when accessing `http://<board IP>` from a browser or via `curl -v http://<board IP>/` on the same network. The board IP is printed on the USB UART terminal.

NOTE: An Ethernet cable connection to a local network is required for conducting this test. Test connectivity in normal Run mode, not debug mode, as debug latency can cause the TCP handshake to time out.
