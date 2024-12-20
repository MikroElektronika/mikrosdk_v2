<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.12.2`

+ released: 2024-12-11

## Changes

+ [`v2.12.2`](#v2122)
  + [Changes](#changes)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk)
    + [New features](#new-features)
      + [mikroSDK](#mikrosdk-1)
      + [CORE](#core)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

**mikroSDK** has been reworked to fit in all SDK supported PIC MCUs for XC8 toolchain.

> In the XC8 compiler, there are some known considerations and potential issues when working with pointers and data widths greater than 8 bits, especially when working on 8-bit microcontrollers like the PIC series.
>> This is why the approach had to be modified. The modified approach bypasses this limitation by
>> splitting complex pieces of code into more simple steps.
>> The simpler steps result in XC8 toolchain generating appropriate assembly
>> instructions and therefore in working pieces of code.

### New features

#### mikroSDK

Added following macro patterns:

+ `GPIO_Pxy`
  + Replaces `Pxy`
+ `GPIO_PIN_x`
  + Replaces `PIN_xy`
+ `GPIO_PORT_x`
  + Replaces `PORT_xy`

All use of the old macros has been changed by new ones. This affects all board and mcu packages as well.

> Note that old macros shall be left in the SDK for a couple of upcoming versions, giving users time to make adequate changes to any code they might have.

#### CORE

All `mcu.h` header file for XC8 supported MCUs have the following change applied:

+ Changed all occurrences of `Pxy` to `_Pxy`
  + Where `x` i a letter from A to Z and `y` is a number from 0 to 9

> Note that these changes shall be reverted once the old pin definitions are removed from the SDK.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-12-11](./new_hw/2024-12-11.md)**
+ **[2024-12-12](./new_hw/2024-12-12.md)**
+ **[2024-12-13](./new_hw/2024-12-13.md)**
+ **[2024-12-16](./new_hw/2024-12-16.md)**
+ **[2024-12-17](./new_hw/2024-12-17.md)**
+ **[2024-12-18](./new_hw/2024-12-18.md)**
+ **[2024-12-19](./new_hw/2024-12-19.md)**
+ **[2024-12-20](./new_hw/2024-12-20.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
