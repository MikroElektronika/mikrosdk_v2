# mikroSDK network layer (`MikroSDK.Net`)

A small, stack-independent network API for Ethernet: IPv4 with DHCP or a static address, DNS, TCP client and
server sockets, UDP sockets, an HTTP/1.1 client and server, an SNTP client, an MQTT 3.1.1 client and an mDNS
responder. Behind it runs [lwIP](../../thirdparty/ethernet/lwip/README.md)
(BSD-3-Clause), but applications never include lwIP headers, so the stack can change without breaking them.

> **Status.** The API, lwIP, the HTTP client and server, SNTP, MQTT, mDNS and the driver for the SPI controllers of
> `middleware/ethernet` are done and tested on a host (see [Testing](#testing)). On-chip drivers exist for every MCU
> CycloneTCP supports through CMake (PIC32MX/MZ, STM32F107/F2/F4/F7, Kinetis MK6x/MKV58, TM4C129); they are
> unit-tested against simulated hardware and their register maps checked against the vendors' headers, but they
> have **not yet run on hardware**. It is the default stack (`MIKROSDK_NET_STACK=LWIP`).

## Selecting the stack

The CMake cache variable `MIKROSDK_NET_STACK` selects the stack (`middleware/CMakeLists.txt`):

| Value | Ethernet |
| --- | --- |
| `LWIP` (default) | This library (`MikroSDK.Net` and its drivers) is built; CycloneTCP, `hw_eth` and the CycloneTCP tests are not. |
| `CYCLONETCP` | As before: on-chip MACs through CycloneTCP (GPL-2.0-or-later); projects must accept the GPL themselves. Until 31 December 2026. This library is not built. |

Moving a CycloneTCP project: [MIGRATION.md](MIGRATION.md).

It is built for `gcc_arm_none_eabi` and `mchp_xc32`, on MCUs with at least 32 KB of RAM (the on-chip drivers: 48 KB).

## Files

| File | |
| --- | --- |
| `include/net_api.h` | Interface, DNS, TCP, UDP |
| `include/net_http.h` | HTTP client (built on `net_api.h` only) |
| `include/net_http_server.h` | HTTP server: routes (method + path → handler), query/form parameters, complete or streamed responses, one request at a time from `net_http_server_poll()` (built on `net_api.h` only) |
| `include/net_sntp.h` | SNTP client (RFC 4330): `net_sntp_sync()` once, then `net_sntp_now()` gives UNIX time from the local millisecond clock; replies must echo a random nonce, come from the server asked, be synchronised; kiss-of-death → `NET_REFUSED` (built on `net_api.h` only) |
| `include/net_mqtt.h` | MQTT 3.1.1 client over plain TCP: QoS 0 and 1, subscribe/unsubscribe, last will, user/password, keep-alive, polled from the main loop; messages larger than the buffer are dropped (still acknowledged) and counted (built on `net_api.h` only) |
| `include/net_mdns.h` | mDNS responder (`<name>.local`) with DNS-SD services, on lwIP's `apps/mdns`; probes for name conflicts, follows address and link changes. Started once, no stop (see the header) |
| `include/net_driver.h` | Frame driver interface: what an Ethernet controller driver implements |
| `adapters/eth_transport/net_driver_eth_transport.h` | Driver for the controllers of `middleware/ethernet` (ENC28J60, LAN9250, LAN8651, W5500, W6100); they are used unchanged |
| `drivers/pic32/net_driver_pic32.h` | On-chip Ethernet of PIC32MX 6xx/7xx and PIC32MZ EF (RMII, polled DMA descriptor rings in uncached memory) — `MikroSDK.Net.Pic32` |
| `drivers/kinetis/net_driver_kinetis.h` | ENET of NXP Kinetis MK60/61/63/64/65/66 and MKV58 (RMII, legacy descriptors, pins, RMII clock and system MPU set up by the driver, MKV58 cache maintenance) — `MikroSDK.Net.Kinetis` |
| `drivers/tm4c/net_driver_tm4c.h` | Ethernet of TI TM4C129 with its integrated PHY (clocks, power, resets and LED pins set up by the driver, no TivaWare) — `MikroSDK.Net.Tm4c` |
| `drivers/stm32/net_driver_stm32.h` | On-chip Ethernet of STM32F107, F2x7, F4x7/F4x9, F74x–F77x (RMII, polled DMA rings, pins and PHY clock through the mikroSDK GPIO layer, Cortex-M7 cache maintenance) — `MikroSDK.Net.Stm32`, built only for those MCUs |
| `drivers/phy/net_phy.h` | Generic PHY control over MDIO (IEEE 802.3 clause 22 registers only), for the on-chip drivers — `MikroSDK.Net.Phy` |
| `src/net_lwip.c` | `net_api.h` on lwIP (raw API) |
| `src/net_http.c`, `src/net_http_server.c`, `src/net_sntp.c`, `src/net_mqtt.c`, `src/net_common.c` | Stack-independent parts |
| `src/net_mdns.c` | `net_mdns.h` on lwIP's mDNS responder |

lwIP and mikroSDK both define a type called `err_t`, so no file includes both: `net_lwip.c` includes only lwIP,
the adapters only mikroSDK headers, and the public headers neither.

## Using it

The layer runs without an RTOS: call `net_poll()` every few milliseconds from the main loop. Functions with a
timeout keep polling while they wait.

```c
#include "net_api.h"
#include "net_http.h"
#include "net_driver_eth_transport.h"

static eth_transport_t eth;          // configured and initialised with eth_transport_*()
static net_driver_t drv;

net_driver_eth_transport( &drv, &eth );

net_config_t cfg;
net_config_default( &cfg );          // DHCP
cfg.driver = &drv;
cfg.now_ms = millis;                 // the application's millisecond counter (e.g. SysTick)
cfg.random = hw_rng_read;            // recommended, see below
memcpy( cfg.mac, my_mac, 6 );
net_init( &cfg );

if ( NET_OK == net_wait_ready( 10000 ) )
{
    static char body[ 512 ];
    net_http_request_t req = { .host = "example.com", .path = "/" };
    net_http_response_t resp = { .body = body, .body_size = sizeof( body ) };
    if ( NET_OK == net_http_request( &req, &resp, 5000 ) && 200 == resp.status ) { /* use body */ }
}

for ( ; ; )
{
    net_poll();
    /* application */
}
```

HTTP server:

```c
static void on_status( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    char led[ 8 ];
    if ( net_http_server_param( req->query, "led", led, sizeof( led ) ) >= 0 ) { /* ?led=on */ }
    net_http_server_respond( conn, 200, "application/json", "{\"ok\":true}", 11 );
}
static const net_http_route_t routes[] = { { "GET", "/api/status", on_status } };
static char buffer[ 1024 ];          // one request: header and body
static net_http_server_t server;

net_http_server_start( &server, 80, routes, 1, buffer, sizeof( buffer ) );
for ( ; ; ) { net_poll(); net_http_server_poll( &server ); }
```

Unknown paths get 404, a known path with another method 405, a handler that does not answer 500. Requests that
do not fit the buffer get 413 / 431, malformed ones 400, chunked request bodies 501, clients that stall 408
(`NET_HTTP_SERVER_TIMEOUT_MS`, 3 s). `Expect: 100-continue` is answered.

TCP: `net_tcp_connect()`, `net_tcp_send()`, `net_tcp_receive()`, `net_tcp_listen()`, `net_tcp_accept()`,
`net_close()`. UDP: `net_udp_open()`, `net_udp_send_to()`, `net_udp_receive_from()`. Errors are `net_err_t` values;
functions that return a length return a negative `net_err_t` on failure.

**Random numbers.** TCP sequence numbers and DNS/DHCP transaction IDs must be hard to guess. Set `cfg.random` to
the MCU's hardware RNG where there is one; without it a PRNG seeded from the MAC address and the time is used,
which is predictable.

## Sizes

lwIP's buffers are compiled into the library, so their size is chosen when mikroSDK is configured: the CMake cache
variable `MIKROSDK_NET_PROFILE` (default `AUTO`, by the MCU's RAM). Measured on Cortex-M4 (GCC 13, `-Os`, unused
code removed by the linker) with DHCP, DNS, the HTTP server and mDNS:

| Profile | Chosen for | Receive buffers | lwIP heap | Sockets | TCP window / send buffer | RAM |
| --- | --- | --- | --- | --- | --- | --- |
| `SMALL` | 32–95 KB of RAM | 4 | 6 KB | 3 | 2 × MSS | ~18 KB |
| `MEDIUM` | 96–255 KB | 10 | 10 KB | 4 | 2 × MSS | ~31 KB |
| `LARGE` | 256 KB and more | 16 | 16 KB | 8 | 4 × MSS | ~48 KB |

Flash: about 46 KB, 57 KB with the HTTP server and mDNS, the same for every profile. An on-chip driver adds 15–19 KB
of RAM for its DMA buffers. The host tests pass with each profile. The profile's definitions are `PUBLIC`, so
`net_api.h` sees the same values in the application. Each value can also be set on its own (a mikroSDK build with
the compile definition):

| Definition | Default | |
| --- | --- | --- |
| `NET_MAX_SOCKETS` | 4 | TCP, UDP and listening sockets together |
| `NET_LWIP_MEM_SIZE` | 10240 | lwIP heap (outgoing TCP data) |
| `NET_LWIP_PBUF_POOL_SIZE` | 10 | buffers for received frames |
| `NET_LWIP_TCP_WND`, `NET_LWIP_TCP_SND_BUF` | 2 × MSS | TCP receive window and send buffer |
| `NET_UDP_QUEUE_LEN`, `NET_TCP_BACKLOG` | 4, 2 | queued datagrams / pending connections |
| `NET_HTTP_HEADER_MAX` | 1024 | largest HTTP response header block |
| `NET_LWIP_IPV6` | 0 | IPv6 (not exposed in `net_api.h` yet) |
| `NET_LWIP_MDNS` | 1 | mDNS responder and IGMP; 0 leaves them out (`net_mdns_*` return `NET_ERROR`) |
| `NET_LWIP_TCP_MSS` | 1460 | TCP segment size |
| `NET_MDNS_MAX_SERVICES` | 2 | DNS-SD services |

mDNS takes about 1.2 KB of the lwIP heap once started (host and two services) and up to 1.5 KB more while it
builds an answer; with mDNS, the HTTP server and busy TCP connections together, consider `NET_LWIP_MEM_SIZE=12288`.
The MQTT client needs only its receive buffer (given by the application) and one socket.

**Multicast.** mDNS needs the controller to pass frames for 01:00:5E:00:00:FB. The on-chip drivers accept all
multicast; for an SPI controller it depends on its receive filter in `middleware/ethernet`.

## Example

[tests/net_web_server](../../tests/net_web_server/ReadMe.txt): a web server (HTML page and `/api/status`, mDNS name
`mikrosdk.local`) that runs unchanged on an SPI Ethernet Click (the same controller selection as `tests/spi_ethernet`)
or on the on-chip Ethernet of PIC32, STM32, Kinetis or TM4C129 boards, chosen with `NET_INTERFACE` in `main.c`.
[tests/net_client](../../tests/net_client/ReadMe.txt): HTTP (replacing the CycloneTCP test
`tests/ethernet/test_http_client`), SNTP and MQTT against public servers, on the same interfaces. Both use
`tests/net_common` for the interface setup.

**Time source.** `net_config_default()` sets `now_ms` to `systime_ms` ([platform/systime](../../platform/systime)):
milliseconds from the core's cycle counter, no interrupt or timer needed (Cortex-M3 and newer, PIC32, RISC-V).
On Cortex-M0/M23 set `now_ms` to a millisecond counter of your own.

## PIC32 on-chip Ethernet (PIC32MX 6xx/7xx, PIC32MZ EF)

```c
static net_driver_t drv;
net_pic32_cfg_t eth_cfg;
net_pic32_cfg_setup( &eth_cfg );      // PHY found by scanning MDIO
eth_cfg.phy_reset = ETH_RST;            // mikromedia 4/5 for PIC32MZ: board.h; PIC32MX MCU card: RG7
eth_cfg.pins_init = board_eth_pins;     // ANSELxCLR for the RMII pins of the board
net_driver_pic32( &drv, &eth_cfg );
```

RMII and the Ethernet pin set are device configuration bits (`FMIIEN`, `FETHIO`) of the setup. The driver polls
(no interrupt), keeps `NET_PIC32_RX_BUFFERS` (8) receive buffers of 1536 bytes and one transmit buffer in
uncached memory (XC32 `coherent`), and sets the MAC to the speed and duplex the PHY negotiated. About 15 KB of RAM.
PIC32MX and PIC32MZ have the same controller at different addresses (both from the device's `mcu.h`); the PIC32MX
has no data cache. The example has the pin setup of the mikromedia 4/5 for PIC32MZ (144 pins) and of the EasyPIC
Fusion v7 ETH MCU card with PIC32MX795F512L (as `hw_eth`).

## STM32 on-chip Ethernet

```c
static net_driver_t drv;
net_stm32_cfg_t eth_cfg;
net_stm32_cfg_setup( &eth_cfg );        // wiring and PHY clock of the board the SDK is built for
net_driver_stm32( &drv, &eth_cfg );
```

The defaults follow the MikroE boards and MCU cards (as `middleware/hw/hw_eth` does for CycloneTCP):

| | Default | Option |
| --- | --- | --- |
| RMII pins | PA1 REF_CLK, PA2 MDIO, PA7 CRS_DV, PC1 MDC, PC4/PC5 RXD0/1, PB11/PB12/PB13 TX_EN/TXD0/TXD1 | `tx_pins`: PG11/PG13/PG14 (default on mikromedia 7 / Plus for STM32F4/F7; packages without port G always use PB) |
| PHY 50 MHz clock | MCO1 on PA8: main PLL ÷ `mco_div` (F2 2, F4 3, F7 4); F1: MCO = system clock | `ref_clock = NET_STM32_REF_CLOCK_BOARD` when the board has its own oscillator |
| PHY | found by scanning MDIO, no reset pin | `phy_addr`, `phy_reset` |

Pins are configured through the mikroSDK GPIO layer (`hal_ll_gpio_module_struct_init`), not a vendor HAL. `net_init()`
fails (driver init returns -2) when the DMA cannot leave reset, which means the PHY gives no reference clock: check
`ref_clock` / `mco_div` against the board's clock setup. With the Cortex-M7 data cache on (F7), buffers and descriptors
are cleaned and invalidated as needed. 8 receive and 4 transmit buffers, about 19 KB of RAM.

## Kinetis on-chip Ethernet (MK60, MK61, MK63, MK64, MK65, MK66, MKV58)

```c
static net_driver_t drv;
net_kinetis_cfg_t eth_cfg;
net_kinetis_cfg_setup( &eth_cfg );      // pins and RMII clock of the MCU the SDK is built for
net_driver_kinetis( &drv, &eth_cfg );
```

| | Default | Option |
| --- | --- | --- |
| Pins | RXER PTA5, RXD1/RXD0/CRS_DV/TXEN/TXD0/TXD1 PTA12–PTA17; MDIO/MDC PTB0/PTB1 (MK60/61/63/64) or PTA7/PTA8 (MK65/66, MKV58) | `pins` |
| RMII 50 MHz clock | ENET_1588_CLKIN on PTE26 | `ref_clock = NET_KINETIS_REF_CLOCK_EXTAL` |
| System MPU | switched off (it blocks the ENET DMA from RAM) | `disable_mpu = false` if the application sets up an MPU region itself |
| PHY | found by scanning MDIO, no reset pin | `phy_addr`, `phy_reset` |

The pin control registers are written directly (as `hw_eth` does): the mikroSDK GPIO layer ORs the mux into the
register, which would be wrong for a pin used as GPIO before. MK65 had no pin setup for CycloneTCP and MK61/MK63 none
at all; they use the MK66 / MK60-MK64 wiring. About 19 KB of RAM.

## TM4C129 on-chip Ethernet

```c
static net_driver_t drv;
net_tm4c_cfg_t eth_cfg;
net_tm4c_cfg_setup( &eth_cfg );         // integrated PHY, link LEDs on PK5 / PK6
net_driver_tm4c( &drv, &eth_cfg );
```

The integrated PHY is selected with auto-negotiation and auto-MDIX (`EMACPC`), then MAC and PHY are reset, as
TivaWare does. The MAC and DMA are the same design as in STM32. About 19 KB of RAM.

## Writing a driver

Implement `net_driver_t` (`include/net_driver.h`): `send` one frame, `receive` one frame without blocking,
`link_up`, and optionally `init`. Frames are complete Ethernet frames without the FCS; the controller pads short
frames. A driver must be written from datasheets and vendor reference material, **not** derived from CycloneTCP's
drivers (GPL).

## Testing

`scripts/net_host_test/run.sh` builds this library and lwIP for Linux and runs, with AddressSanitizer and UBSan:
unit tests of `platform/systime` (fake cycle counter), of the PHY code (simulated PHY) and of every on-chip driver
(PIC32, STM32 F1/F2/F4/F7, Kinetis K64/K66/KV58, TM4C129: fake registers, a hardware model, the test playing the DMA
engines), the drivers' register maps compared with ST's, NXP's and TI's device headers, then the network checks against the Linux TCP/IP stack in a
private network namespace (DHCP and DNS from dnsmasq, TCP/UDP echo, HTTP client and server, TCP server mode, link
loss, error cases, SNTP against good and misbehaving servers, MQTT against a scripted broker, mDNS queries and a
name conflict). See [its README](../../scripts/net_host_test/README.md). GitHub Actions runs it
(`.github/workflows/netHostTest.yaml`) on every push that changes the network layer, `platform/systime` or
`thirdparty/`, together with the SBOM check (`scripts/sbom.py --check`).

## Next steps

1. Run `tests/net_web_server` and `tests/net_client` on hardware: an SPI Ethernet Click and one board per on-chip
   controller (PIC32MX, PIC32MZ, STM32 F1/F2/F4/F7, Kinetis K6x and KV58, TM4C129).
2. FTP client (CycloneTCP's FTP client test, `tests/ethernet/test_ftp_client`, moves with it).
3. After 31 December 2026: remove CycloneTCP, `hw_eth`, the CycloneTCP tests and the `MIKROSDK_NET_STACK` option.
