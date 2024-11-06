<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.13.0`

+ released: 2024-11-29

## Changes

+ [`v2.13.0`](#v2130)
  + [Changes](#changes)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

**mikroSDK** has been reworked to fit in all SDK supported PIC MCUs for XC8 toolchain.

> In the XC8 compiler, there are some known considerations and potential issues when working with pointers and data widths greater than 8 bits, especially when working on 8-bit microcontrollers like the PIC series.
>> This is why the approach had to be modified. The modified approach bypasses this limitation by
>> splitting complex pieces of code into more simple steps.
>> The simpler steps result in XC8 toolchain generating appropriate assembly
>> instructions and therefore in working pieces of code.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
