This example tests the network clients of the mikroSDK network layer (middleware/net, lwIP): HTTP and FTP (they replace the CycloneTCP tests tests/ethernet/test_http_client and test_ftp_client), SNTP and MQTT. Build mikroSDK with MIKROSDK_NET_STACK=LWIP (the default; GCC for ARM or XC32).

Choose the Ethernet interface with NET_INTERFACE in main.c, as for the net_web_server test (an SPI Ethernet Click, or the on-chip Ethernet of PIC32, STM32, Kinetis or TM4C129; see net_web_server/ReadMe.txt for the boards).

The board gets an address by DHCP and checks, against public servers:
- DNS: httpbin.org resolves,
- HTTP: GET and POST to http://httpbin.org/anything come back echoed, http://httpbin.org/status/404 returns 404,
- SNTP: pool.ntp.org gives a plausible UTC time,
- MQTT: on test.mosquitto.org it subscribes to mikrosdk/test/<its MAC>, publishes "ping" there with QoS 1 and receives it back,
- FTP: on test.rebex.net (public read-only demo account, user demo / password) it logs in, gets the size of readme.txt, downloads it completely and lists the root directory.

Test is considered successful if the USB UART terminal shows "PASS" for every check and ends with "RESULT PASS".

NOTE: Needs an Ethernet connection to a network with Internet access (DHCP, DNS, outgoing TCP 80, 1883 and 21 plus FTP passive data ports, UDP 123). Needs a Cortex-M3 or newer ARM core or a PIC32 and about 40 KB of RAM.
