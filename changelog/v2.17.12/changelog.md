<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.12`

+ released: 2026-04-23

## Changes

- [`v2.17.12`](#v21712)
  - [Changes](#changes)
    - [Improvements](#improvements)
    - [New Features](#new-features)
    - [NEW HARDWARE](#new-hardware)

### Improvements

+ Reduced the amount of `#ifdef` conditionals and regular expressions in various low-level implementations for Renesas MCUs
  + Simplified conditional compilation and regex usage
  + Improved readability and maintainability across affected modules

### New Features

+ AGT module support for Renesas devices
  + Implemented PWM mode for the AGT module
  + Expands available PWM output pins (previously only GPT module was supported)
  + Automatic module selection based on pin configuration is transparent to users

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
