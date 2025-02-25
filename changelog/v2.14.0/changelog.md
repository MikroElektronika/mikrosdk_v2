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
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk-2)
      + [CORE](#core)
    + [NEW HARDWARE](#new-hardware)

### New Features

#### mikroSDK

+ Added functions to retrieve appropriate pin number and port name based on pin
  + Two functions in total:
    + `hal_gpio_fetch_pin`
    + `hal_gpio_fetch_port`
  + Both functions defined as static inline inside main gpio header file for ease of use
  + For example, pin `GPIO_PC3` can be used to retrieve pin number as `3` and port name as `GPIO_PORT_C`
+ Implemented UART polling mode
  + Introduced UART polling mode as an alternative to the existing interrupt-based approach in the mikroSDK
  + Provides an option for applications that require simpler control and do not rely on interrupt-driven operations

### Improvements

#### mikroSDK

+ Improved low level STM32 PWM implementation
  + Timer modules can now use the same module but different channels without reinitializing the module every time
  + Check [THIS EXAMPLE](../../tests/pwm/multi_channel) to see how it works

### Fixes

#### mikroSDK

+ Corrected UART stop bit configuration for STM32
  + The support for 0.5 and 1.5 stop bits on UART4 and UART5 for certain MCUs was previously overlooked
  + This issue has now been addressed in the code
+ Updated low-level I2C implementation
  + Some of the return value variables were originally declared as 8-bit, but they needed to handle larger values
  + This has now been fixed
+ Updated Clicker 4 board names
  + They have been changed to fit the new naming convention

#### CORE

+ Fixed STM32H7 library
  + Previously initialization process was stuck in infinite loop while waiting for PLL to be enabled
  + In project setup configuration clock settings values are now correct

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
