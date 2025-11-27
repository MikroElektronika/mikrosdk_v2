<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.2`

+ released: 2025-12-04

## Changes

- [`v2.17.2`](#v2172)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA4M3 MCUs supported!**

|       MCU       |
|  :------------: |
|  R7FA4M3AD2CBM  |
|  R7FA4M3AD2CBQ  |
|  R7FA4M3AD3CBM  |
|  R7FA4M3AD3CBQ  |
|  R7FA4M3AD3CFB  |
|  R7FA4M3AE2CBM  |
|  R7FA4M3AE2CBQ  |
|  R7FA4M3AE3CBM  |
|  R7FA4M3AE3CBQ  |
|  R7FA4M3AE3CFB  |
|  R7FA4M3AE3CFM  |
|  R7FA4M3AE3CFP  |
|  R7FA4M3AF2CBM  |
|  R7FA4M3AF2CBQ  |
|  R7FA4M3AF3CBM  |
|  R7FA4M3AF3CBQ  |
|  R7FA4M3AF3CFB  |
|  R7FA4M3AF3CFM  |
|  R7FA4M3AF3CFP  |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Fixes

#### mikroSDK

+ Changed type of `one_wire_handle.input` for Renesas OW implementation from *uint32_t* to *uint16_t*
  + The function now works properly when setting pin as input as register access is now correct
+ Removed hard-coded array size for GPIO Ports in low-level GPIO implementation
  + All GPIO ports are now conditionally included based on macro definitions, and undefined ports are filled with 0
+ Fixed type of `gpio_data_value` in GPIO reading functions from *uint8_t* to *uint16_t*
  + Now data being read correctly for upper nibble GPIO pins

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2025-12-04](./new_hw/2025-12-04.md)**
+ **[2025-12-05](./new_hw/2025-12-05.md)**
+ **[2025-12-08](./new_hw/2025-12-08.md)**
+ **[2025-12-09](./new_hw/2025-12-09.md)**
+ **[2025-12-10](./new_hw/2025-12-10.md)**
+ **[2025-12-11](./new_hw/2025-12-11.md)**
+ **[2025-12-12](./new_hw/2025-12-12.md)**
+ **[2025-12-15](./new_hw/2025-12-15.md)**
+ **[2025-12-16](./new_hw/2025-12-16.md)**
+ **[2025-12-17](./new_hw/2025-12-17.md)**
+ **[2025-12-18](./new_hw/2025-12-18.md)**
+ **[2025-12-19](./new_hw/2025-12-19.md)**
+ **[2025-12-22](./new_hw/2025-12-22.md)**
+ **[2025-12-23](./new_hw/2025-12-23.md)**
+ **[2025-12-24](./new_hw/2025-12-24.md)**
+ **[2025-12-25](./new_hw/2025-12-25.md)**
+ **[2025-12-26](./new_hw/2025-12-26.md)**
+ **[2025-12-29](./new_hw/2025-12-29.md)**
+ **[2025-12-30](./new_hw/2025-12-30.md)**
+ **[2025-12-31](./new_hw/2025-12-31.md)**
+ **[2026-01-01](./new_hw/2026-01-01.md)**
+ **[2026-01-02](./new_hw/2026-01-02.md)**
+ **[2026-01-05](./new_hw/2026-01-05.md)**
+ **[2026-01-06](./new_hw/2026-01-06.md)**
+ **[2026-01-07](./new_hw/2026-01-07.md)**
+ **[2026-01-08](./new_hw/2026-01-08.md)**
+ **[2026-01-09](./new_hw/2026-01-09.md)**
+ **[2026-01-12](./new_hw/2026-01-12.md)**
+ **[2026-01-13](./new_hw/2026-01-13.md)**
+ **[2026-01-14](./new_hw/2026-01-14.md)**
+ **[2026-01-15](./new_hw/2026-01-15.md)**
+ **[2026-01-16](./new_hw/2026-01-16.md)**
+ **[2026-01-19](./new_hw/2026-01-19.md)**
+ **[2026-01-20](./new_hw/2026-01-20.md)**
+ **[2026-01-21](./new_hw/2026-01-21.md)**
+ **[2026-01-22](./new_hw/2026-01-22.md)**
+ **[2026-01-23](./new_hw/2026-01-23.md)**
+ **[2026-01-26](./new_hw/2026-01-26.md)**
+ **[2026-01-27](./new_hw/2026-01-27.md)**
+ **[2026-01-28](./new_hw/2026-01-28.md)**
+ **[2026-01-29](./new_hw/2026-01-29.md)**
+ **[2026-01-30](./new_hw/2026-01-30.md)**
+ **[2026-02-02](./new_hw/2026-02-02.md)**
+ **[2026-02-03](./new_hw/2026-02-03.md)**
+ **[2026-02-04](./new_hw/2026-02-04.md)**
+ **[2026-02-05](./new_hw/2026-02-05.md)**
+ **[2026-02-06](./new_hw/2026-02-06.md)**
+ **[2026-02-09](./new_hw/2026-02-09.md)**
+ **[2026-02-10](./new_hw/2026-02-10.md)**
+ **[2026-02-11](./new_hw/2026-02-11.md)**
+ **[2026-02-12](./new_hw/2026-02-12.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
