<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.15.1`

+ released: 2025-08-21

## Changes

- [`v2.15.1`](#v2151)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)

### <font color=red>RENESAS</font>

**RA6M3 MCUs supported!**

|       MCU       |
|  :------------: |
|  R7FA6M3AF2CBG  |
|  R7FA6M3AF2CLK  |
|  R7FA6M3AF3CBG  |
|  R7FA6M3AF3CFB  |
|  R7FA6M3AF3CFC  |
|  R7FA6M3AF3CFP  |
|  R7FA6M3AF3CLK  |
|  R7FA6M3AH2CBG  |
|  R7FA6M3AH2CLK  |
|  R7FA6M3AH3CBG  |
|  R7FA6M3AH3CFB  |
|  R7FA6M3AH3CFC  |
|  R7FA6M3AH3CFP  |
|  R7FA6M3AH3CLK  |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

#### mikroSDK

- Enhanced GPIO library for Renesas MCUs
  - Expanded range of GPIO configuration options now available
- SPI bit rate handling refined
  - Calculations now adapt more effectively across different clock speeds
- Core updates for UART
  - Improved interrupt handling for more reliable communication

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
