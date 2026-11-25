This example tests the mikroSDK network layer (middleware/net, lwIP). Build mikroSDK with MIKROSDK_NET_STACK=LWIP (GCC for ARM or XC32).

The same web server runs on two kinds of Ethernet, chosen with NET_INTERFACE in main.c:
- NET_IF_SPI (default): an SPI Ethernet controller on mikroBUS (SPI_ETH_CHIP: ENC28J60, W5500/WIZ_IP55, W6100, LAN9250 or LAN8651; LAN9250 by default), the same controllers and setup as the spi_ethernet test.
- NET_IF_PIC32MZ: the on-chip Ethernet of the mikromedia 4/5 for PIC32MZ (LAN8720 PHY).

The board gets its address by DHCP (USE_DHCP = 1, default) or uses the static address in main.c, and prints it on the USB UART terminal.

Test is considered successful if, on the same network:
- the board answers pings (`ping <board IP>`),
- http://<board IP>/ shows the page with the address, uptime and request counter (browser or `curl -v http://<board IP>/`), the counter goes up with every reload,
- http://<board IP>/api/status returns the same as JSON,
- other paths return 404,
- after unplugging and plugging the cable the terminal shows LINK DOWN / LINK UP and the page works again.

NOTE: An Ethernet cable connection to a local network is required. Needs a Cortex-M3 or newer ARM core or a PIC32 (the millisecond clock uses the core's cycle counter) and about 40 KB of RAM.
