<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.14.3`

+ released: 2025-03-28

## Changes

+ [`v2.14.3`](#v2143)
  + [Changes](#changes)
    + [New features](#new-features)
      + [mikroSDK](#mikrosdk)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk-1)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk-2)
    + [NEW HARDWARE](#new-hardware)

### New features

#### mikroSDK

+ Button simulation library
  + Implemented a useful new library, especially handy while using a remote setup on Planet Debug
  + The library includes various button-handling simulation functions, enabling a range of applications

### Improvements

#### mikroSDK

+ Added `digital_out_read` function to the driver level
  + Allows reading the output value of a pin, which is required by some architectures
  + Complements the existing `digital_in_read` function

### Fixes

#### mikroSDK

+ Updated the delay function calls in the PIC32 `hal_ll_errata.c` file to fit the requirements of all adequate compilers
+ Eliminated wrong symbols from LCD
  + LCD used to show "garbage" symbols regardless of achitecture
+ Added missing LCD pin definitions for certain v7 boards
  + Some v7 boards with an LCD socket lacked the necessary pin definitions for the LCD library
+ Updated Clicker 4 board names
  + They have been changed to fit the new naming convention

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2025-03-28](./new_hw/2025-03-28.md)**
+ **[2025-03-31](./new_hw/2025-03-31.md)**
+ **[2025-04-01](./new_hw/2025-04-01.md)**
+ **[2025-04-02](./new_hw/2025-04-02.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
