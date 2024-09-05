<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.0.1`

+ released: 2020-12-11

## Changes

- [`v2.0.1`](#v201)
  - [Changes](#changes)
    - [General](#general)
    - [Fixes](#fixes)

### General

+ Added support for **new hardware**
+ Updated relevant **manifest files**
+ Updated relevant **development kit package**

**MCU CARD 11 FOR PIC** is now supported in **mikroSDK 2.0**.

**Added** following **PIC chips**:

+ `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
+ `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

**Added** adequate board definition files for **MCU CARD 11 FOR PIC**.

Updated **mikroSDK development kit** to follow added hardware.

+ `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
+ `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

### Fixes

+ HAL GPIO low level ( PIC chips )
  + **HAL GPIO low level PIC** implementation now doesn't change previous state of **LATCH** registers.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
