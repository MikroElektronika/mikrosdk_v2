<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.14.5`

+ released: 2025-07-03

## Changes

- [`v2.14.5`](#v2145)
  - [Changes](#changes)
    - [New Features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk-1)
    - [NEW HARDWARE](#new-hardware)

### New Features

#### mikroSDK

+ Minor improvements
+ Implemented FT800 library
  + Integrated FT800 graphics controller library into mikroSDK
  + All NECTOStudio Designer widgets are supported
  + Implemented touch recognition using TouchPanel library and FT800 library
  + Added standalone features for FT800 graphics controller using co-processor commands
  + Supports display list management, initialization and touch input handling
  + List of elements is below

|   Element  |   Element    |      Element       |
|:----------:|:------------:|:------------------:|
| Text       | Number       | Button             |
| Clock      | Gauge        | Gradient rectangle |
| Keys       | Progress bar | Slider             |
| Scroll bar | Dial         | Toggle switch      |

### Fixes

#### mikroSDK

+ Fixed analog pin definitions for PIC18FXXJ94 MCUs
+ Other minor fixes

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
