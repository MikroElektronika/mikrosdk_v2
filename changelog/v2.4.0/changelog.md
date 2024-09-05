<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.4.0`

+ released: 2021-12-28

## Changes

- [`v2.4.0`](#v240)
  - [Changes](#changes)
    - [Resistive displays](#resistive-displays)
    - [Middleware](#middleware)
      - [STMPE811](#stmpe811)
      - [STMPE810](#stmpe810)
      - [STMPE610](#stmpe610)
      - [TSC2003](#tsc2003)
    - [Mikromedia shields](#mikromedia-shields)
    - [NEW HARDWARE](#new-hardware)
    - [DEVELOPMENT KIT PACKAGE](#development-kit-package)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [Recursive build automation](#recursive-build-automation)
    - [Test examples](#test-examples)
    - [Collaborators](#collaborators)

### Resistive displays

Support added for 4 resistive displays.

+ Displays added:
  + **[TFT Board 3 Resistive](https://www.mikroe.com/tft-board-3-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-3-resisitive-schematic.pdf)
  + **[TFT Board 4 Resistive](https://www.mikroe.com/tft-board-4-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-4-resisitive-schematic.pdf)
  + **[TFT Board 5 Resistive](https://www.mikroe.com/tft-board-5-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-5-resisitive-schematic.pdf)
  + **[TFT Board 7 Resistive](https://www.mikroe.com/tft-board-7-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-7-resisitive-schematic.pdf)

Displays have SSD1963 controller, which is already supported, and `STMPE811` touch controller.

### Middleware

#### STMPE811

+ Files added:
  + [stmpe811.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/include/stmpe811.h)
  + [stmpe811.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/src/stmpe811.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/memake.txt)

[STMPE811 Datasheet](https://datasheetspdf.com/pdf-file/633509/STMicroelectronics/STMPE811/1).

#### STMPE810

Added `STMPE811` library is compatible with `STMPE810`.

For the sake of simplicity, `STMPE810` devices will use `STMPE811` library.

Please refer to [STMPE811](#stmpe811).

#### STMPE610

Added `STMPE811` library is compatible with `STMPE610`.

For the sake of simplicity, `STMPE610` devices will use `STMPE811` library.

Please refer to [STMPE811](#stmpe811).

#### TSC2003

Support added for TI's `TSC2003` touch controller.

+ Files added:
  + [tsc2003.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/include/tsc2003.h)
  + [tsc2003.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/src/tsc2003.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/memake.txt)

> Note:
>> Library is functional, but will be officialy added in Necto later.

### Mikromedia shields

+ Connector definitions for mikromedia shields have been added
  + [Mikromedia 3 Capacitive shield](https://www.mikroe.com/mikromedia-3-capacitive-shield)
  + [Mikromedia 4 Capacitive shield](https://www.mikroe.com/mikromedia-4-capacitive-shield)
  + [Mikromedia 5 Capacitive shield](https://www.mikroe.com/mikromedia-5-capacitive-shield)
  + [Mikromedia 7 Capacitive shield](https://www.mikroe.com/mikromedia-7-capacitive-shield)

### NEW HARDWARE

+ New board definitions added:
  + [TFT Board 3 Resistive](https://www.mikroe.com/tft-board-3-resistive)
  + [TFT Board 4 Resistive](https://www.mikroe.com/tft-board-4-resistive)
  + [TFT Board 5 Resistive](https://www.mikroe.com/tft-board-5-resistive)
  + [TFT Board 7 Resistive](https://www.mikroe.com/tft-board-7-resistive)
  + [Mikromedia 3 for PIC Capacitive FPI with bezel](https://www.mikroe.com/mikromedia-3-for-pic-capacitive-fpi-with-bezel)
  + [Mikromedia 3 for PIC Capacitive FPI with frame](https://www.mikroe.com/mikromedia-3-for-pic-capacitive-fpi-with-frame)
  + [Mikromedia Plus for PIC32MX7](https://www.mikroe.com/mikromedia-4-pic32mx7)
  + [Mikromedia Plus for STM32](https://www.mikroe.com/mikromedia-4-stm32f4)
  + [Mikromedia Plus for STM32F7](https://www.mikroe.com/mikromedia-4-stm32f7)
  + [Mikromedia 7 for STM32F4](https://www.mikroe.com/mikromedia-7-stm32f4)
  + [Mikromedia 7 for STM32F7](https://www.mikroe.com/mikromedia-7-stm32f7)

**Config files added for adequate `NEW` boards.**

### DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all **11** new hardware definitions

### Fixes

+ Fixed inadequate UART alternate function setting for STM32F1x chips
  + Inadequate alternate function setting for certain pins
+ Fixed all baud rate calculation return values
  + `HAL_LL` functions for calculating baud rates now all return actual baud set on hardware
+ Some `MK22x` chips didn't have all NVIC defined
  + 20 files in total
+ Fixed all issues with inadequate pin checking types
  + e.g trying to place a word value in a byte variable
+ Updated low level UART impelementations
  + Adequately sets stop bits, data bits and parity settings

### Improvements

+ NXP High Speed ADC
  + All `MKV5x` chips now have a fully supported HSADC module
  + Results in High speed ADC (HSADC) adds faster and more precise measurements to any project
+ Touch Panel library no longer requires constant values for screen width and height
  + Done by memake python automation
+ The addition of shields for Mikromedia boards now allows for Click example building and testing
+ Removed unnecessary handle checking in low level implementations
  + Results in quicker code execution
+ Changed board macro naming convention for DIP connections

### Recursive build automation

*Updated powershell script for automated recursive `SDK` build.*

*Script now writes adequate progress level based on run settings.*

Files changed:

+ [build-hal-recursion-ci.ps1](./scripts/build-hal-recursion-ci.ps1)
+ [utility.ps1](./scripts/utility.ps1)

For more information, please refer to main script [DESCRIPTION](./scripts/ReadMe.md)

### Test examples

*Updated `tft_touch_panel` test example.*

**Example is updated to work with new resistive displays and touch controllers.**

### Collaborators

**We would like to thank the following people for contributing:**

+ **[@NikolaDucak](https://github.com/NikolaDucak)**
  + **STMPE811 library** full implementation
    + **[view files](./middleware/stmpe811)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
