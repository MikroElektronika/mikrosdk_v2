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
| `harness.py` | Creates `tap0` (192.168.77.1/24), runs dnsmasq (DHCP, DNS) and the servers (TCP echo 7007, UDP echo 7008, HTTP 8000), pings the stack and connects to its TCP server |
| `CMakeLists.txt` | Host build: `-Dcode=` as in every mikroSDK library, AddressSanitizer and UBSan (fatal), strict warnings for the mikroSDK files |
| `test_phy.c` | Unit test of `drivers/phy` with a simulated PHY: address scan, reset, latched link bit, negotiated mode |
| `test_pic32mz.c`, `fakes/pic32mz/` | Unit test of the PIC32MZ driver with fake registers and a simulated LAN8720; the test fills the receive descriptors like the DMA controller. Tests the driver logic and descriptor format, not the silicon |

What is checked: init errors, DHCP and static addresses, ping, address parsing, DNS (found, not found, literal),
300 KB TCP echo through small windows, refused and timed-out connections, UDP echo and timeout, socket limits and
invalid handles, HTTP GET/POST/chunked/404/truncated/close-delimited/malformed responses and header injection,
TCP server mode (accept, peer address, peer close) and link loss with DHCP recovery.
