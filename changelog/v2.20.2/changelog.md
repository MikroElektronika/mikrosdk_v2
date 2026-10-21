<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.20.2`

+ released: 2026-11-03

## Changes

- [`v2.20.2`](#v2202)
  - [Changes](#changes)
    - [New features](#new-features)
    - [Added SPI Ethernet library](#added-spi-ethernet-library)
    - [NEW HARDWARE](#new-hardware)

### New features

### Added SPI Ethernet library

Added a new SPI Ethernet library to mikroSDK.

+ Introduces a generic SPI Ethernet middleware layer for MCU networking use cases.
+ Includes driver support for multiple SPI Ethernet controllers: ENC28J60, LAN9250, W5500, and W6100.
+ Provides a common API for initialization, packet send/receive, link status, and MAC/IP configuration.
+ Adds protocol helpers for ARP, ICMP, and basic TCP frame handling.
+ Integrates the library into the SDK build and includes a dedicated validation test under `tests/spi_ethernet`.
+ Broadly validated across supported toolchains and target devices.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-11-03](./new_hw/2026-11-03.md)**
+ **[2026-11-04](./new_hw/2026-11-04.md)**
+ **[2026-11-05](./new_hw/2026-11-05.md)**
+ **[2026-11-06](./new_hw/2026-11-06.md)**
+ **[2026-11-09](./new_hw/2026-11-09.md)**
+ **[2026-11-10](./new_hw/2026-11-10.md)**
+ **[2026-11-11](./new_hw/2026-11-11.md)**
+ **[2026-11-12](./new_hw/2026-11-12.md)**
+ **[2026-11-13](./new_hw/2026-11-13.md)**
+ **[2026-11-16](./new_hw/2026-11-16.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
