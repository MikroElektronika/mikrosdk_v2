This example tests the mikroSDK network layer (middleware/net, lwIP). Build mikroSDK with MIKROSDK_NET_STACK=LWIP (GCC for ARM or XC32).

The same web server runs on several kinds of Ethernet, chosen with NET_INTERFACE in main.c:
- NET_IF_SPI (default): an SPI Ethernet controller on mikroBUS (SPI_ETH_CHIP: ENC28J60, W5500/WIZ_IP55, W6100, LAN9250 or LAN8651; LAN9250 by default), the same controllers and setup as the spi_ethernet test.
- NET_IF_PIC32: the on-chip Ethernet of the mikromedia 4/5 for PIC32MZ or of the EasyPIC Fusion v7 ETH MCU card with PIC32MX795F512L (LAN8720 PHY; on that card ERXERR/RB11 must be tied to ground, as for CycloneTCP).
- NET_IF_STM32: the on-chip Ethernet of STM32F107, F2x7, F4x7/F4x9 and F74x-F77x boards and MCU cards (RMII PHY; its 50 MHz clock from MCO1 on PA8 as on the MikroE MCU cards). If net_init fails, the PHY gets no reference clock or does not answer: check mco_div / ref_clock in net_stm32_cfg_t.
- NET_IF_KINETIS: the on-chip ENET of NXP Kinetis MK60/MK61/MK63/MK64/MK65/MK66/MKV58 MCU cards (RMII PHY; its 50 MHz clock into ENET_1588_CLKIN, PTE26).
- NET_IF_TM4C: the on-chip Ethernet of TI TM4C129 MCU cards (integrated PHY, link LEDs on PK5/PK6).

The board gets its address by DHCP (USE_DHCP = 1, default) or uses the static address in main.c, and prints it on the USB UART terminal.

Test is considered successful if, on the same network:
- the board answers pings (`ping <board IP>`),
- http://mikrosdk.local/ (mDNS; works where the PC resolves .local names: macOS, Linux with Avahi, Windows 10+) or http://<board IP>/ shows the page with the address, uptime and request counter (browser or `curl -v http://<board IP>/`), the counter goes up with every reload,
- http://<board IP>/api/status returns the same as JSON,
- other paths return 404,
- after unplugging and plugging the cable the terminal shows LINK DOWN / LINK UP and the page works again.

NOTE: An Ethernet cable connection to a local network is required. Needs a Cortex-M3 or newer ARM core or a PIC32 (the time source, platform/systime, uses the core's cycle counter) and about 40 KB of RAM.
