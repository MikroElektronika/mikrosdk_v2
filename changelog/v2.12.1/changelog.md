<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.12.1`

+ released: 2024-12-02

## Changes

+ [`v2.12.1`](#v2121)
  + [Changes](#changes)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk-1)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

**mikroSDK** LVGL now has the option to build either `LIGHT` or `HEAVY` LVGL configurations.

`HEAVY` configuration shall have all features of `LIGHT` configuration, with the addition of below listed features.

Additional options added for `HEAVY` configuration:

+ `CANVAS`
+ `TABLE`
+ `ANIMIMG`
+ `CALENDAR`
+ `CHART`
+ `IMGBTN`
+ `LIST`
+ `MENU`
+ `METER`
+ `MSGBOX`
+ `SPAN`
+ `TABVIEW`
+ `TILEVIEW`
+ `WIN`
+ `FLEX`
+ `GRID`

> Note that this feature is chosen by NECTO based on MCU memory (RAM/FLASH).
>> i.e. if MCU has at least **96K RAM** and **512K FLASH**, heavy configuration will be built.

### Fixes

#### mikroSDK

+ Fixed a stray space character before closing a comment
  + This caused build issues for FS if `FF_USE_LFN` was defined

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
