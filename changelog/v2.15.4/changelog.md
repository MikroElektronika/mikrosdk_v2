<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.15.4`

+ released: 2025-09-18

## Changes

- [`v2.15.4`](#v2154)
  - [Changes](#changes)
    - [New features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk-1)

### New features

#### mikroSDK

- Added GLCD library to mikroSDK
  - Provides a comprehensive set of graphics functions for graphical LCD modules
  - Supported across multiple toolchains, including GCC, Clang and XC32
  - Drawing primitives available, such as lines, rectangles and circles
  - Filled shapes also supported: rectangles, circles, and ellipses
  - Supports writing text on the display with built-in font handling

### Fixes

#### mikroSDK

- Corrected TFT pin definitions for EasyPIC Fusion v7 board
- Corrected TFT pin definitions for EasyPIC v8 for PIC24/dsPIC33 board
- Added polling-based write and read functions to low-level AI-generated UART implementations
  - Fixed build issues caused by missing functions
- Added `mcu_reg_addresses.h` include for 5 PIC18FxQ MCUs
  - Ensures correct register definitions in the SDK

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
