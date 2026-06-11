<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.11`

+ released: 2026-04-09

## Changes

- [`v2.17.11`](#v21711)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [New Features](#new-features)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA6E2 MCUs supported!**

| **R7FA6E2B92CBB** | **R7FA6E2BB2CBB** |
| :-----------: | :-----------: |
| **R7FA6E2B92CBC** | **R7FA6E2BB2CBC** |
| **R7FA6E2B93CBB** | **R7FA6E2BB3CBB** |
| **R7FA6E2B93CBC** | **R7FA6E2BB3CBC** |
| **R7FA6E2B93CFM** | **R7FA6E2BB3CFM** |
| **R7FA6E2B93CNE** | **R7FA6E2BB3CNE** |
| **R7FA6E2B93CNH** | **R7FA6E2BB3CNH** |
|           |            |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### New Features

**1-Wire module supported for:**

1. **STM32C0**

|      MCU       |      MCU       |      MCU       |
| :------------: | :------------: | :------------: |
|   STM32C011F4  |   STM32C031C4  |   STM32C031C6  |
|   STM32C011J4  |   STM32C031F4  |   STM32C031F6  |
|   STM32C011F6  |   STM32C031G4  |   STM32C031G6  |
|   STM32C011J6  |   STM32C031K4  |   STM32C031K6  |
|   STM32C011D6  |                |                |

2. **STM32G0**

|      MCU       |      MCU       |      MCU       |       MCU      |
| :------------: | :------------: | :------------: | :------------: |
|   STM32G051C6  |   STM32G061K6  |   STM32G0B1KC  |   STM32G0C1KC  |
|   STM32G051F6  |   STM32G061C8  |   STM32G0B1MC  |   STM32G0C1MC  |
|   STM32G051G6  |   STM32G061F8  |   STM32G0B1RC  |   STM32G0C1RC  |
|   STM32G051K6  |   STM32G061G8  |   STM32G0B1VC  |   STM32G0C1VC  |
|   STM32G051C8  |   STM32G061K8  |   STM32G0B1CE  |   STM32G0C1CE  |
|   STM32G051F8  |   STM32G0B1CB  |   STM32G0B1KE  |   STM32G0C1KE  |
|   STM32G051G8  |   STM32G0B1KB  |   STM32G0B1ME  |   STM32G0C1ME  |
|   STM32G051K8  |   STM32G0B1MB  |   STM32G0B1NE  |   STM32G0C1NE  |
|   STM32G061C6  |   STM32G0B1RB  |   STM32G0B1RE  |   STM32G0C1RE  |
|   STM32G061F6  |   STM32G0B1VB  |   STM32G0B1VE  |   STM32G0C1VE  |
|   STM32G061G6  |   STM32G0B1CC  |   STM32G0C1CC  |                |

3. **STM32G4**

|      MCU       |      MCU       |      MCU       |       MCU      |
| :------------: | :------------: | :------------: | :------------: |
|   STM32G431C6  |   STM32G473MB  |   STM32G474QB  |   STM32G484ME  |
|   STM32G431K6  |   STM32G473PB  |   STM32G474PB  |   STM32G484PE  |
|   STM32G431R6  |   STM32G473RB  |   STM32G474CC  |   STM32G484RE  |
|   STM32G431V6  |   STM32G473VB  |   STM32G474MC  |   STM32G484QE  |
|   STM32G431M6  |   STM32G473QB  |   STM32G474RC  |   STM32G484VE  |
|   STM32G431C8  |   STM32G473CC  |   STM32G474VC  |   STM32G491CC  |
|   STM32G431K8  |   STM32G473MC  |   STM32G474QC  |   STM32G491KC  |
|   STM32G431R8  |   STM32G473PC  |   STM32G474PC  |   STM32G491RC  |
|   STM32G431V8  |   STM32G473RC  |   STM32G474CE  |   STM32G491VC  |
|   STM32G431M8  |   STM32G473VC  |   STM32G474ME  |   STM32G491MC  |
|   STM32G431CB  |   STM32G473QC  |   STM32G474RE  |   STM32G491CE  |
|   STM32G431KB  |   STM32G473CE  |   STM32G474VE  |   STM32G491KE  |
|   STM32G431RB  |   STM32G473ME  |   STM32G474QE  |   STM32G491RE  |
|   STM32G431VB  |   STM32G473PE  |   STM32G474PE  |   STM32G491VE  |
|   STM32G431MB  |   STM32G473RE  |   STM32G483CE  |   STM32G491ME  |
|   STM32G441CB  |   STM32G473VE  |   STM32G483RE  |   STM32G4A1CE  |
|   STM32G441KB  |   STM32G473QE  |   STM32G483ME  |   STM32G4A1KE  |
|   STM32G441RB  |   STM32G474CB  |   STM32G483PE  |   STM32G4A1ME  |
|   STM32G441MB  |   STM32G474MB  |   STM32G483VE  |   STM32G4A1RE  |
|   STM32G441VB  |   STM32G474RB  |   STM32G483QE  |   STM32G4A1VE  |
|   STM32G473CB  |   STM32G474VB  |   STM32G484CE  |                |

4. **STM32L4**

|      MCU       |      MCU       |      MCU       |       MCU      |
| :------------: | :------------: | :------------: | :------------: |
|   STM32L4P5AE  |   STM32L4P5QG  |   STM32L4P5ZE  |   STM32L4Q5QG  |
|   STM32L4P5AG  |   STM32L4P5RE  |   STM32L4P5ZG  |   STM32L4Q5RG  |
|   STM32L4P5CE  |   STM32L4P5RG  |   STM32L4Q5AG  |   STM32L4Q5VG  |
|   STM32L4P5CG  |   STM32L4P5VE  |   STM32L4Q5CG  |   STM32L4Q5ZG  |
|   STM32L4P5QE  |   STM32L4P5VG  |                |                |

### Improvements

+ Merged the two ADC implementations for Renesas into one
  + Before, the implementation for RA4M1 (14-bit ADC) was separate from the implementation for all other supported Renesas MCUs (12-bit ADC)
  + Now, both implementations are merged into a single one that supports both 12-bit and 14-bit ADCs
  + This change improved the code maintainability and reduced the code size
  + The new approach is more efficient and easier to use

### Fixes

+ Added RESTART condition functionality for `hal_ll_i2c_master_write_then_read()` function
  + Previously, STOP–START sequences were used instead, which are incompatible with certain I2C devices on click boards
+ Fixed SCI SPI configuration for SPI mode 3 for Renesas devices
  + Previously, incorrect configuration caused improper behavior.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-04-09](./new_hw/2026-04-09.md)**
+ **[2026-04-10](./new_hw/2026-04-10.md)**
+ **[2026-04-13](./new_hw/2026-04-13.md)**
+ **[2026-04-14](./new_hw/2026-04-14.md)**
+ **[2026-04-15](./new_hw/2026-04-15.md)**
+ **[2026-04-16](./new_hw/2026-04-16.md)**
+ **[2026-04-17](./new_hw/2026-04-17.md)**
+ **[2026-04-20](./new_hw/2026-04-20.md)**
+ **[2026-04-21](./new_hw/2026-04-21.md)**
+ **[2026-04-22](./new_hw/2026-04-22.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
