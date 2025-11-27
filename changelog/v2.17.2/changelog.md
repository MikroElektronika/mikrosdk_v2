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

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
