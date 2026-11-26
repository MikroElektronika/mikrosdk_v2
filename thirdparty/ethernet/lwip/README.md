# lwIP (third-party component)

This folder contains **lwIP**, the lightweight TCP/IP stack, used by the mikroSDK network layer
([middleware/net](../../../middleware/net/README.md)) when `MIKROSDK_NET_STACK` is `LWIP`. It is not covered by the
mikroSDK licence.

| | |
| --- | --- |
| Upstream | <https://github.com/lwip-tcpip/lwip> ([savannah](https://savannah.nongnu.org/projects/lwip/)) |
| Version | 2.2.1 (tag `STABLE-2_2_1_RELEASE`, commit recorded in [UPSTREAM.json](UPSTREAM.json)) |
| Copyright | Swedish Institute of Computer Science and the lwIP contributors |
| Licence | `BSD-3-Clause`, see [COPYING](COPYING) |

The BSD licence lets lwIP be used in closed-source and commercial firmware. Its one condition for binary
distribution: the copyright notice, the conditions and the disclaimer in [COPYING](COPYING) must be reproduced in
the documentation or other materials provided with the firmware.

## What is here

| Path | What | Origin |
| --- | --- | --- |
| `src/core`, `src/core/ipv4`, `src/core/ipv6`, `src/netif/ethernet.c`, `src/apps/mdns`, `src/include` | lwIP sources used by mikroSDK (`src/apps/mdns`: the mDNS responder behind `net_mdns.h`) | upstream, imported by `scripts/import_lwip.py` |
| `COPYING` | lwIP licence | upstream |
| `UPSTREAM.json` | tag, commit, every imported file with the SHA-256 of the upstream file and whether MIKROE changed it | generated on import |
| `port/lwipopts.h`, `port/arch/cc.h` | configuration and architecture port for mikroSDK | MIKROE |
| `lwip_sources.cmake` | list of sources and include paths, used by `middleware/net/CMakeLists.txt` | MIKROE |

Not imported: the sequential and socket APIs (`src/api`, mikroSDK runs without an RTOS), PPP, 6LoWPAN, SLIP and
the other applications in `src/apps` (the HTTP, SNTP and MQTT clients of `middleware/net` are MIKROE's own, built
on `net_api.h`).

## Known upstream issues

- **mDNS, use after free when a netif is removed (2.2.1).** `mdns_resp_remove_netif()` frees the responder but
  leaves its timers queued; they dereference the freed state when they fire. Upstream fixed most of it after 2.2.1
  (commit `07de8c5`, "mdns: Cancel timeouts when netif removed"), but not the timer of a delayed answer to a
  truncated query (`mdns_handle_tc_question`), which any host on the LAN can trigger. `net_mdns.h` therefore has no
  stop and never calls `mdns_resp_remove_netif()`; renaming and removing services are safe. Keep it so until lwIP
  fixes both; then a `net_mdns_stop()` can be added.

## Changes made by MIKROE

Every mikroSDK library is compiled with `code=` (an empty macro: `code` is a reserved word in the mikroC compilers),
which would erase lwIP's fields named `code` (ICMP headers). `scripts/import_lwip.py` therefore renames the
identifier `code` to `_code` outside comments and strings. The 13 files it changes start with a notice saying so
and are marked `"modified": true` in `UPSTREAM.json`. Nothing else in the upstream files is changed.

## Updating lwIP

```sh
git clone --depth 1 --branch STABLE-2_2_x_RELEASE https://github.com/lwip-tcpip/lwip.git /tmp/lwip
python3 scripts/import_lwip.py /tmp/lwip
scripts/net_host_test/run.sh          # the host tests must pass
```

Then check `git diff` (new or removed source files go into `lwip_sources.cmake`), update the version above, review
[Known upstream issues](#known-upstream-issues) and note the update in the changelog. Watch lwIP's releases and security advisories: under the EU Cyber Resilience Act
a vulnerability in lwIP is a vulnerability in mikroSDK.
