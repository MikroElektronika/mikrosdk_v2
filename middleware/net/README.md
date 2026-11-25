# mikroSDK network layer (`MikroSDK.Net`)

A small, stack-independent network API for Ethernet: IPv4 with DHCP or a static address, DNS, TCP client and
server sockets, UDP sockets and an HTTP/1.1 client. Behind it runs [lwIP](../../thirdparty/ethernet/lwip/README.md)
(BSD-3-Clause), but applications never include lwIP headers, so the stack can change without breaking them.

> **Status: first step.** The API, lwIP, the HTTP client and the driver for the controllers of
> `middleware/ethernet` are done and tested on a host (see [Testing](#testing)). Drivers for on-chip MACs
> (PIC32MZ, STM32, TM4C129, Kinetis) do not exist yet; until they do, on-chip Ethernet stays on CycloneTCP.

## Selecting the stack

The CMake cache variable `MIKROSDK_NET_STACK` selects the stack (`middleware/CMakeLists.txt`):

| Value | Ethernet |
| --- | --- |
| `CYCLONETCP` (default) | As before: on-chip MACs through CycloneTCP (GPL-2.0-or-later). This library is not built. |
| `LWIP` | This library (`MikroSDK.Net`, `MikroSDK.Net.EthTransport`) is built; CycloneTCP, `hw_eth` and the CycloneTCP tests are not. |

It is built for `gcc_arm_none_eabi` and `mchp_xc32`.

## Files

| File | |
| --- | --- |
| `include/net_api.h` | Interface, DNS, TCP, UDP |
| `include/net_http.h` | HTTP client (built on `net_api.h` only) |
| `include/net_driver.h` | Frame driver interface: what an Ethernet controller driver implements |
| `adapters/eth_transport/net_driver_eth_transport.h` | Driver for the controllers of `middleware/ethernet` (ENC28J60, LAN9250, LAN8651, W5500, W6100) |
| `src/net_lwip.c` | `net_api.h` on lwIP (raw API) |
| `src/net_http.c`, `src/net_common.c` | Stack-independent parts |

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

TCP: `net_tcp_connect()`, `net_tcp_send()`, `net_tcp_receive()`, `net_tcp_listen()`, `net_tcp_accept()`,
`net_close()`. UDP: `net_udp_open()`, `net_udp_send_to()`, `net_udp_receive_from()`. Errors are `net_err_t` values;
functions that return a length return a negative `net_err_t` on failure.

**Random numbers.** TCP sequence numbers and DNS/DHCP transaction IDs must be hard to guess. Set `cfg.random` to
the MCU's hardware RNG where there is one; without it a PRNG seeded from the MAC address and the time is used,
which is predictable.

## Sizes

Defaults use about 30 KB of RAM (lwIP heap 10 KB, 10 packet buffers of ~1.5 KB, 4 sockets). Override with compile
definitions:

| Definition | Default | |
| --- | --- | --- |
| `NET_MAX_SOCKETS` | 4 | TCP, UDP and listening sockets together |
| `NET_LWIP_MEM_SIZE` | 10240 | lwIP heap (outgoing TCP data) |
| `NET_LWIP_PBUF_POOL_SIZE` | 10 | buffers for received frames |
| `NET_LWIP_TCP_WND`, `NET_LWIP_TCP_SND_BUF` | 2 × MSS | TCP receive window and send buffer |
| `NET_UDP_QUEUE_LEN`, `NET_TCP_BACKLOG` | 4, 2 | queued datagrams / pending connections |
| `NET_HTTP_HEADER_MAX` | 1024 | largest HTTP response header block |
| `NET_LWIP_IPV6` | 0 | IPv6 (not exposed in `net_api.h` yet) |

## Writing a driver

Implement `net_driver_t` (`include/net_driver.h`): `send` one frame, `receive` one frame without blocking,
`link_up`, and optionally `init`. Frames are complete Ethernet frames without the FCS; the controller pads short
frames. A driver must be written from datasheets and vendor reference material, **not** derived from CycloneTCP's
drivers (GPL).

## Testing

`scripts/net_host_test/run.sh` builds this library and lwIP for Linux and runs 84 checks against the Linux TCP/IP
stack in a private network namespace (DHCP and DNS from dnsmasq, TCP/UDP echo, HTTP server, TCP server mode, link
loss, error cases), with AddressSanitizer and UBSan. See [its README](../../scripts/net_host_test/README.md).

## Next steps

1. On-chip MAC drivers: PIC32MZ + LAN8720 first (the PHY the mikromedia 4/5 for PIC32MZ boards declare), then
   STM32F4/F7, TM4C129, Kinetis.
2. Examples and tests for MCUs (`tests/net`), and migrating the CycloneTCP tests.
3. FTP client if needed, IPv6 in `net_api.h`.
4. Once the drivers exist: make `LWIP` the default and deprecate CycloneTCP.
