<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.14.0`

+ released: 2025-03-11

## Changes

+ [`v2.14.0`](#v2140)
  + [Changes](#changes)
    + [New Features](#new-features)
      + [mikroSDK](#mikrosdk)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk-1)
    + [NEW HARDWARE](#new-hardware)

### New Features

#### mikroSDK

+ Added functions to retrieve appropriate pin number and port name based on pin
  + Two functions in total:
    + `hal_gpio_fetch_pin`
    + `hal_gpio_fetch_port`
  + Both functions defined as static inline inside main gpio header file for ease of use
  + For example, pin `GPIO_PC3` can be used to retrieve pin number as `3` and prot name as `GPIO_PORT_C`

### Improvements

#### mikroSDK

+ Improved low level STM32 PWM implementation
  + Timer modules can now use the same module but different channels without reinitializing the module every time
  + Check [THIS EXAMPLE](../../tests/pwm/multi_channel) to see how it works

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
