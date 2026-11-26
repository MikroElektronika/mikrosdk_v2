# CycloneTCP (third-party component)

This folder contains **CycloneTCP Open** by **Oryx Embedded SARL**. It is **not** covered by the mikroSDK licence.

> **Not the default any more.** mikroSDK's Ethernet support uses lwIP (BSD-3-Clause, `middleware/net`) by default.
> CycloneTCP is built only when a build selects it with `-DMIKROSDK_NET_STACK=CYCLONETCP`, and only until
> 31 December 2026, when it is removed. Moving to the network layer: `middleware/net/MIGRATION.md`.

| | |
| --- | --- |
| Upstream | <https://github.com/Oryx-Embedded/CycloneTCP> (`lib/cyclone_tcp`) and <https://github.com/Oryx-Embedded/Common> (`lib/common`, a subset) |
| Version | 2.3.0 (tag `v2.3.0` of both repositories) |
| Copyright | Copyright (C) 2010-2023 Oryx Embedded SARL |
| Licence | GNU General Public License, version 2 or (at your option) any later version (`GPL-2.0-or-later`), see [LICENSE](LICENSE) |
| Imported | mikroSDK 2.10.0 (2024-01-30) |

## What the licence means for your firmware

CycloneTCP Open is licensed under the GPL. If your firmware uses mikroSDK's Ethernet support, it includes CycloneTCP,
and the firmware as a whole is subject to the GPL (version 2 or later), whichever mikroSDK licence you use. If you
cannot meet the GPL's terms, for example because your firmware is closed source, you need a commercial licence for
CycloneTCP from Oryx Embedded: <https://www.oryx-embedded.com>.

You, not MIKROE, are responsible for meeting the terms of the GPL (or of your commercial licence) for the firmware
you build and distribute.

### Accepting the GPL in your project

CycloneTCP refuses to compile unless `GPL_LICENSE_TERMS_ACCEPTED` is defined. mikroSDK defines it only to build its
own Ethernet libraries; it does **not** pass it on to your project. A project that uses Ethernet support (includes
`hw_eth.h` or any CycloneTCP header) stops with an error until you accept the GPL for that project:

```cmake
# CMakeLists.txt of your project
target_compile_definitions(<your target> PRIVATE GPL_LICENSE_TERMS_ACCEPTED)
```

Defining it in your project is your statement that the firmware will be distributed under the GPL's terms. If you
hold a commercial CycloneTCP licence from Oryx Embedded, define it as well: it only switches the check off, and your
commercial licence applies instead.

Do not define it in mikroSDK's own files (`config/net_config.h`, `config/os_port_config.h`) or its CMake files: that
would accept the GPL for every project built with that mikroSDK installation.

## Changes made by MIKROE

Every changed file says so in its header (GPL-2.0, section 2(a)).

In this repository:

| File | Change |
| --- | --- |
| `lib/cyclone_tcp/drivers/mac/mkv5x_eth_driver.c` | 2024-01-30: RMII mode enabled when built for mikroSDK |
| `lib/cyclone_tcp/drivers/mac/mpc5748_eth1_driver.c`, `mpc5748_eth2_driver.c` | 2024-01-30: interrupts set up through the S32 SDK interrupt manager (`INT_SYS_*`) |
| `lib/common/compiler_port.h` | 2024-06-27: XC32 handling for mikroSDK builds |
| `lib/common/debug.h` | 2024-06-27: trace output through the mikroSDK logger |
| `config/net_config.h`, `config/os_port_config.h`, `config/fs_port_config.h` | 2024-01-30: CycloneTCP configuration templates adapted for mikroSDK; 2024-06-27: trace levels off (`net_config.h`); 2026-11-25: check that the project accepted the GPL (`net_config.h`) |

Only part of the upstream `Common` repository is included (the RTOS ports mikroSDK does not use are left out).

At release time, `scripts/keyword_replace.py` renames the identifier `code` to `_code` in the `.c` and `.h` files
(`code` is a reserved word in the mikroC compilers) and adds a dated notice at the top of every file it changes.

## Other files in this folder

These are not part of CycloneTCP and keep their own licences (see each file's header):

- `lib/cyclone_tcp/drivers/mac/stm32f4xx_hal_cortex.c` / `.h`: from STMicroelectronics' STM32CubeF4 HAL.
- `config/arm/`: device and CMSIS headers used by the MAC drivers: Arm CMSIS-Core(M) (`Apache-2.0`),
  STMicroelectronics STM32 device headers and HAL files, NXP Kinetis device headers (`BSD-3-Clause`) and Texas
  Instruments TivaWare driverlib (`BSD-3-Clause`).
- `CMakeLists.txt` files: written by MIKROE for the mikroSDK build (they define `GPL_LICENSE_TERMS_ACCEPTED` only
  privately, to build the libraries, see above).

See [THIRD_PARTY_NOTICES.md](../../../THIRD_PARTY_NOTICES.md) for all third-party components in mikroSDK.
