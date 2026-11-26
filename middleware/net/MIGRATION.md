# Moving from CycloneTCP to the mikroSDK network layer

From this release mikroSDK builds Ethernet on **lwIP** behind its own network API (`net_api.h`, this folder) instead
of CycloneTCP. CycloneTCP can still be selected until **31 December 2026**; after that it is removed. This page is for
projects that used CycloneTCP (`hw_eth.h`, `core/net.h`, `http/http_client.h`, ...) on an on-chip Ethernet MAC.

| | Before (CycloneTCP) | Now (network layer) |
| --- | --- | --- |
| Licence of the stack | GPL-2.0-or-later: your firmware falls under the GPL | BSD-3-Clause: closed source allowed, keep lwIP's notice ([COPYING](../../thirdparty/ethernet/lwip/COPYING)) |
| CMake | `MikroSDK.Ethernet.CycloneTCP` | `MikroSDK.Net` + one driver library (table below) |
| Threads / timers | SysTick interrupt, `netTask()` | none: call `net_poll()` from the main loop |
| SPI Ethernet Clicks | separate stack (`middleware/ethernet`) | the same API as on-chip MACs (`MikroSDK.Net.EthTransport`) |
| IPv6, TLS, FTP client | available in CycloneTCP | not yet (FTP client planned) |

## Option 1: keep CycloneTCP for now

Configure mikroSDK with `-DMIKROSDK_NET_STACK=CYCLONETCP`. Your project must then **accept the GPL itself**, or it
stops with a compile error:

```cmake
target_compile_definitions(<your target> PRIVATE GPL_LICENSE_TERMS_ACCEPTED)
```

That definition is your statement that the firmware is distributed under the GPL (or that you hold a commercial
CycloneTCP licence from Oryx Embedded); see [thirdparty/ethernet/cyclonetcp/README.md](../../thirdparty/ethernet/cyclonetcp/README.md).
This option ends with 2026.

## Option 2: move to the network layer

### 1. CMake

```cmake
target_link_libraries(<your target> PUBLIC
    MikroSDK.Net
    MikroSDK.Net.Stm32       # the driver of your MCU, see below
)
```

| Ethernet | Library | Header | Driver setup |
| --- | --- | --- | --- |
| STM32F107, F2x7, F4x7/F4x9, F74x–F77x | `MikroSDK.Net.Stm32` | `net_driver_stm32.h` | `net_stm32_cfg_setup()`, `net_driver_stm32()` |
| PIC32MX 6xx/7xx, PIC32MZ EF | `MikroSDK.Net.Pic32` | `net_driver_pic32.h` | `net_pic32_cfg_setup()`, `net_driver_pic32()` |
| Kinetis MK60–MK66, MKV58 | `MikroSDK.Net.Kinetis` | `net_driver_kinetis.h` | `net_kinetis_cfg_setup()`, `net_driver_kinetis()` |
| TM4C129 | `MikroSDK.Net.Tm4c` | `net_driver_tm4c.h` | `net_tm4c_cfg_setup()`, `net_driver_tm4c()` |
| SPI Click (ENC28J60, W5500, W6100, LAN9250, LAN8651) | `MikroSDK.Net.EthTransport` | `net_driver_eth_transport.h` | `net_driver_eth_transport()` on an initialised `eth_transport_t` |

The drivers set up the pins, the PHY and its reference clock as wired on MikroE boards; `hw_eth.h` and the SysTick
setup of the CycloneTCP examples are not needed. Complete programs for every driver: `tests/net_web_server` and
`tests/net_client` (with `tests/net_common/net_test_interface.h`).

### 2. Start-up

```c
// Before
netInit();
interface = &netInterface[ 0 ];
netSetHostname( interface, "my-board" );
netSetMacAddr( interface, &macAddr );
netSetDriver( interface, &ETHERNET_DRIVER_HANDLER );
netSetPhyDriver( interface, ETHERNET_PHY_CHIP );
netConfigInterface( interface );
netStartInterface( interface );
dhcpClientGetDefaultSettings( &dhcpSettings ); /* ... */ dhcpClientInit( &dhcpContext, &dhcpSettings ); dhcpClientStart( &dhcpContext );

// Now
static net_driver_t driver;
net_stm32_cfg_t eth_cfg;
net_stm32_cfg_setup( &eth_cfg );
net_driver_stm32( &driver, &eth_cfg );

net_config_t cfg;
net_config_default( &cfg );              // DHCP on, time from platform/systime
cfg.driver = &driver;
cfg.hostname = "my-board";
memcpy( cfg.mac, my_mac, 6 );
// cfg.random = my_hw_rng;               // recommended: the MCU's hardware RNG
net_init( &cfg );
net_wait_ready( 10000 );                 // link up and address assigned
for ( ; ; ) { net_poll(); /* ... */ }
```

Static address: `cfg.use_dhcp = false;` and set `cfg.ip`, `cfg.netmask`, `cfg.gateway`, `cfg.dns` (`net_ip4( 192, 168, 1, 10 )`).

### 3. Equivalents

| CycloneTCP | Network layer |
| --- | --- |
| `getHostByName()` | `net_resolve( host, &ip, timeout_ms )` |
| `ipv4StringToAddr()`, `ipv4AddrToString()` | `net_ip4_from_string()`, `net_ip4_to_string()` |
| `socketOpen( SOCKET_TYPE_STREAM )` + `socketConnect()` | `net_tcp_connect( &sock, &ip, port, timeout_ms )` |
| `socketSend()`, `socketReceive()` | `net_tcp_send()`, `net_tcp_receive()` (timeouts per call) |
| `socketBind()` + `socketListen()` + `socketAccept()` | `net_tcp_listen()`, `net_tcp_accept()` |
| `socketOpen( SOCKET_TYPE_DGRAM )`, `socketSendTo()`, `socketReceiveFrom()` | `net_udp_open()`, `net_udp_send_to()`, `net_udp_receive_from()` |
| `socketClose()` | `net_close()` |
| `httpClientInit()` ... `httpClientReadBody()` | one `net_http_request( &req, &resp, timeout_ms )` ([net_http.h](include/net_http.h)) |
| `httpServerInit()` + `httpServerStart()` | `net_http_server_start()` + `net_http_server_poll()` with a route table ([net_http_server.h](include/net_http_server.h)) |
| `sntpClientInit()` ... `sntpClientGetTimestamp()` | `net_sntp_sync()`, `net_sntp_now()` ([net_sntp.h](include/net_sntp.h)) |
| `mqttClientInit()` ... `mqttClientTask()` | `net_mqtt_connect()`, `net_mqtt_publish()`, `net_mqtt_subscribe()`, `net_mqtt_poll()` ([net_mqtt.h](include/net_mqtt.h)) |
| `mdnsResponderInit()` ... | `net_mdns_start()`, `net_mdns_add_service()` ([net_mdns.h](include/net_mdns.h)) |
| `netTask()` / SysTick | `net_poll()` |
| `error_t` (`NO_ERROR`, `ERROR_TIMEOUT`, ...) | `net_err_t` (`NET_OK`, `NET_TIMEOUT`, ...); lengths are negative on error |

Functions with a timeout keep calling `net_poll()` while they wait, so a simple sequential program works as before.

### 4. Memory

The size of the network layer is chosen from the MCU's RAM when mikroSDK is configured (`MIKROSDK_NET_PROFILE`,
see [README.md](README.md#sizes)): about 18 KB of RAM on MCUs with less than 96 KB, 31 KB up to 256 KB, 48 KB above,
plus 15–19 KB for an on-chip driver's DMA buffers, and about 57 KB of Flash. MCUs with less than 32 KB of RAM keep
the SPI stack of `middleware/ethernet`.

## Not available yet

IPv6, TLS (HTTPS, MQTTS) and the FTP client (planned). If you need them before they arrive, keep CycloneTCP
(option 1) until the end of 2026.
