# Network layer host test

Builds the mikroSDK network layer (`middleware/net`) with lwIP for Linux and tests it against the Linux TCP/IP
stack. Not part of mikroSDK builds or of `mikrosdk.7z` (`scripts/` is not packaged).

```sh
scripts/net_host_test/run.sh            # CMAKE=/path/to/cmake if cmake is not on PATH
```

Needs gcc, cmake, python3, dnsmasq, ping and iproute2, and a Linux that allows unprivileged user namespaces with
`/dev/net/tun`. No root and no network access: `run.sh` starts `harness.py` with `unshare -rn`, a private network
namespace, so the TAP device, dnsmasq and the servers exist only there.

| File | |
| --- | --- |
| `test_net.c` | The checks (run twice: DHCP with the built-in PRNG, static address with a random-number hook) |
| `tap_driver.c` | `net_driver_t` on a Linux TAP device |
| `harness.py` | Creates `tap0` (192.168.77.1/24, plus .2 and .3 for misbehaving SNTP servers), runs dnsmasq (DHCP, DNS) and the servers (TCP echo 7007, UDP echo 7008, HTTP 8000, SNTP 123, a scripted MQTT 3.1.1 broker on 1883, an mDNS peer on 224.0.0.251:5353), pings the stack, connects to its TCP and HTTP servers and sends it mDNS queries |
| `CMakeLists.txt` | Host build: `-Dcode=` as in every mikroSDK library, AddressSanitizer and UBSan (fatal), strict warnings for the mikroSDK files |
| `test_systime.c` | Unit test of `platform/systime` with a fake cycle counter: exact milliseconds across counter wraps |
| `test_phy.c` | Unit test of `drivers/phy` with a simulated PHY: address scan, reset, latched link bit, negotiated mode |
| `test_stm32.c`, `fakes/stm32/` | Unit test of the STM32 driver, built once per family (F1, F2, F4, F7): fake registers, a hardware model (DMA reset only with a reference clock, MDIO transfers to a simulated LAN8720, FIFO flush), the test playing both DMA engines; pins, clocks, RMII mode, MCO, MAC/DMA setup, rings, receive/transmit, link modes, Cortex-M7 cache maintenance, failures |
| `stm32_regmap_*.c`, `stm32_regmap.h` | The STM32 driver's register offsets and bits compared with ST's CMSIS device headers (F107, F207, F407, F746), where the repository has them; `stm32_regmap_main.c` is the comparison program for all register map checks |
| `test_kinetis.c`, `kinetis_regmap_*.c` | Kinetis ENET driver per pin variant (K64, K66, KV58): fake registers, hardware model (reset, MDIO frames), the test playing the DMA; register map against NXP's headers (MK60, MK64, MK65, MK66, MKV58) |
| `test_tm4c.c`, `tm4c_regmap_*.c` | TM4C129 driver: fake registers, hardware model (clock/power ready, resets, MDIO to the integrated PHY), the test playing the DMA; register map against TI's headers |
| `fakes/cmsis/` | CMSIS core and system header stubs, so ST's and NXP's device headers can be read for the register map checks |
| `test_pic32.c`, `fakes/pic32/` | Unit test of the PIC32 (MX/MZ) driver with fake registers and a simulated LAN8720; the test fills the receive descriptors like the DMA controller. Tests the driver logic and descriptor format, not the silicon |

What is checked: init errors, DHCP and static addresses, ping, address parsing, DNS (found, not found, literal),
300 KB TCP echo through small windows, refused and timed-out connections, UDP echo and timeout, socket limits and
invalid handles, HTTP GET/POST/chunked/404/truncated/close-delimited/malformed responses and header injection,
TCP server mode (accept, peer address, peer close), link loss with DHCP recovery, the HTTP server against raw
requests from the harness (routes, query decoding, POST echo, 30 KB streamed body, 404/405/500, 400 for garbage and
lowercase methods, 413/431 for oversize requests, 501 for chunked bodies, `Expect: 100-continue`, 408 for a stalled
client and service afterwards), SNTP (time within 2 s of the host, by name, kiss-of-death refused, wrong nonce and
unsynchronised answers ignored), MQTT (connect by name with credentials and generated client id, refused connect,
no broker, no CONNACK, subscribe/refused subscribe, QoS 0/1 both ways, empty and retained messages, PUBACK with a
wrong id, a message too large for the buffer dropped but acknowledged, keep-alive pings, last will on a lost
connection, unsubscribe, unanswered ping, malformed remaining length, broker closing; the broker checks the packets
it got) and mDNS (probing and announcement, A queries multicast/unicast/any case, service enumeration, PTR, SRV,
TXT, silence for other names, a truncated query answered late, removing a service, a name conflict and renaming,
probing again after a link change).

Mutation checks (a deliberate bug in the code under test, the suite must fail) were run for the SNTP nonce,
leap/kiss-of-death handling, MQTT acknowledgements, keep-alive, remaining length limit, flags, and the mDNS name
check, TXT items, conflict report, IGMP flag, status callbacks and service slots.
