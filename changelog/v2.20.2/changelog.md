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
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### New features

### Added SPI Ethernet library

Added a new SPI Ethernet library to mikroSDK.

+ Introduces a generic SPI Ethernet middleware layer for MCU networking use cases.
+ Includes driver support for multiple SPI Ethernet controllers: ENC28J60, LAN8651, LAN9250, W5500, and W6100.
+ Provides a common API for initialization, packet send/receive, link status, and MAC/IP configuration.
+ Adds protocol helpers for ARP, ICMP, and basic TCP frame handling.
+ Integrates the library into the SDK build and includes a dedicated validation test under `tests/spi_ethernet`.
+ Broadly validated across supported toolchains and target devices.

### Fixes

+ Fixed ST7789 display driver not drawing anything when used with the Graphic Library / Visual TFT (IPS Display Click and IPS Display 2 Click)
  + Driver now registers its drawing functions (fill, begin frame, frame data, end frame) and display dimensions with the Graphic Library
  + Pixel data is now sent in the byte order the display is configured for, fixing incorrect colors
  + Driver now uses the opened SPI object directly instead of a copy of it
  + Fixed type incompatibilities that caused build failures on some architectures (e.g. PIC)
+ Fixed Graphic Library gradients rendering as repeating color bands or stripes when built with mikroC
  + Color component macros (`GL_RED_OF`, `GL_GREEN_OF`, `GL_BLUE_OF`) now mask out neighbouring color bits, which also fixes `GL_LUMA_OF`

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
+ **[2027-02-19](./new_hw/2027-02-19.md)**
+ **[2027-02-22](./new_hw/2027-02-22.md)**
+ **[2027-02-23](./new_hw/2027-02-23.md)**
+ **[2027-02-24](./new_hw/2027-02-24.md)**
+ **[2027-02-25](./new_hw/2027-02-25.md)**
+ **[2027-02-26](./new_hw/2027-02-26.md)**
+ **[2027-03-01](./new_hw/2027-03-01.md)**
+ **[2027-03-02](./new_hw/2027-03-02.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
