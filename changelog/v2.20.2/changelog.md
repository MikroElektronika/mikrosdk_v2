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
+ **[2026-11-17](./new_hw/2026-11-17.md)**
+ **[2026-11-18](./new_hw/2026-11-18.md)**
+ **[2026-11-19](./new_hw/2026-11-19.md)**
+ **[2026-11-20](./new_hw/2026-11-20.md)**
+ **[2026-11-23](./new_hw/2026-11-23.md)**
+ **[2026-11-24](./new_hw/2026-11-24.md)**
+ **[2026-11-25](./new_hw/2026-11-25.md)**
+ **[2026-11-26](./new_hw/2026-11-26.md)**
+ **[2026-11-27](./new_hw/2026-11-27.md)**
+ **[2026-11-30](./new_hw/2026-11-30.md)**
+ **[2026-12-01](./new_hw/2026-12-01.md)**
+ **[2026-12-02](./new_hw/2026-12-02.md)**
+ **[2026-12-03](./new_hw/2026-12-03.md)**
+ **[2026-12-04](./new_hw/2026-12-04.md)**
+ **[2026-12-07](./new_hw/2026-12-07.md)**
+ **[2026-12-08](./new_hw/2026-12-08.md)**
+ **[2026-12-09](./new_hw/2026-12-09.md)**
+ **[2026-12-10](./new_hw/2026-12-10.md)**
+ **[2026-12-11](./new_hw/2026-12-11.md)**
+ **[2026-12-14](./new_hw/2026-12-14.md)**
+ **[2026-12-15](./new_hw/2026-12-15.md)**
+ **[2026-12-16](./new_hw/2026-12-16.md)**
+ **[2026-12-17](./new_hw/2026-12-17.md)**
+ **[2026-12-18](./new_hw/2026-12-18.md)**
+ **[2026-12-21](./new_hw/2026-12-21.md)**
+ **[2026-12-22](./new_hw/2026-12-22.md)**
+ **[2026-12-23](./new_hw/2026-12-23.md)**
+ **[2026-12-24](./new_hw/2026-12-24.md)**
+ **[2026-12-25](./new_hw/2026-12-25.md)**
+ **[2026-12-28](./new_hw/2026-12-28.md)**
+ **[2026-12-29](./new_hw/2026-12-29.md)**
+ **[2026-12-30](./new_hw/2026-12-30.md)**
+ **[2026-12-31](./new_hw/2026-12-31.md)**
+ **[2027-01-01](./new_hw/2027-01-01.md)**
+ **[2027-01-04](./new_hw/2027-01-04.md)**
+ **[2027-01-05](./new_hw/2027-01-05.md)**
+ **[2027-01-06](./new_hw/2027-01-06.md)**
+ **[2027-01-07](./new_hw/2027-01-07.md)**
+ **[2027-01-08](./new_hw/2027-01-08.md)**
+ **[2027-01-11](./new_hw/2027-01-11.md)**
+ **[2027-01-12](./new_hw/2027-01-12.md)**
+ **[2027-01-13](./new_hw/2027-01-13.md)**
+ **[2027-01-14](./new_hw/2027-01-14.md)**
+ **[2027-01-15](./new_hw/2027-01-15.md)**
+ **[2027-01-18](./new_hw/2027-01-18.md)**
+ **[2027-01-19](./new_hw/2027-01-19.md)**
+ **[2027-01-20](./new_hw/2027-01-20.md)**
+ **[2027-01-21](./new_hw/2027-01-21.md)**
+ **[2027-01-22](./new_hw/2027-01-22.md)**
+ **[2027-01-25](./new_hw/2027-01-25.md)**
+ **[2027-01-26](./new_hw/2027-01-26.md)**
+ **[2027-01-27](./new_hw/2027-01-27.md)**
+ **[2027-01-28](./new_hw/2027-01-28.md)**
+ **[2027-01-29](./new_hw/2027-01-29.md)**
+ **[2027-02-01](./new_hw/2027-02-01.md)**
+ **[2027-02-02](./new_hw/2027-02-02.md)**
+ **[2027-02-03](./new_hw/2027-02-03.md)**
+ **[2027-02-04](./new_hw/2027-02-04.md)**
+ **[2027-02-05](./new_hw/2027-02-05.md)**
+ **[2027-02-08](./new_hw/2027-02-08.md)**
+ **[2027-02-09](./new_hw/2027-02-09.md)**
+ **[2027-02-10](./new_hw/2027-02-10.md)**
+ **[2027-02-11](./new_hw/2027-02-11.md)**
+ **[2027-02-12](./new_hw/2027-02-12.md)**
+ **[2027-02-15](./new_hw/2027-02-15.md)**
+ **[2027-02-16](./new_hw/2027-02-16.md)**
+ **[2027-02-17](./new_hw/2027-02-17.md)**
+ **[2027-02-18](./new_hw/2027-02-18.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
