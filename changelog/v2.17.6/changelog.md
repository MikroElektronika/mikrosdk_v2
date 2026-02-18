<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.6`

+ released: 2026-02-03

## Changes

- [`v2.17.6`](#v2176)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA6M5 MCUs supported!**

|            |            |            |
| :-----------: | :-----------: | :-----------: |
| R7FA6M5AH2CBG | R7FA6M5AG3CFP | R7FA6M5BG3CBM |
| R7FA6M5AH3CFC | R7FA6M5BH2CBG | R7FA6M5BG3CFB |
| R7FA6M5AH2CBM | R7FA6M5BH3CFC | R7FA6M5BG3CAG |
| R7FA6M5AH3CBM | R7FA6M5BH2CBM | R7FA6M5BG3CFP |
| R7FA6M5AH3CFB | R7FA6M5BH3CBM | R7FA6M5BF2CBG |
| R7FA6M5AH3CFP | R7FA6M5BH3CFB | R7FA6M5BF3CFC |
| R7FA6M5AG2CBG | R7FA6M5BH3CAG | R7FA6M5BF2CBM |
| R7FA6M5AG3CFC | R7FA6M5BH3CFP | R7FA6M5BF3CBM |
| R7FA6M5AG2CBM | R7FA6M5BG2CBG | R7FA6M5BF3CFB |
| R7FA6M5AG3CBM | R7FA6M5BG3CFC | R7FA6M5BF3CAG |
| R7FA6M5AG3CFB | R7FA6M5BG2CBM | R7FA6M5BF3CFP |
|            |            |            |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

- Implemented I2C speed calculation for Renesas MCUs based on the peripheral source clock
  - Previously it was hardcoded only for default peripheral clock values

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-02-02](./new_hw/2026-02-02.md)**
+ **[2026-02-03](./new_hw/2026-02-03.md)**
+ **[2026-02-04](./new_hw/2026-02-04.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
