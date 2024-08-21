<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.7.1`

+ released: 2022-12-28

## Changes

- [`v2.7.1`](#v271)
  - [Changes](#changes)
    - [New Features](#new-features)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### New Features

+ One Wire implementation for AVR
  + Full module support
+ **ILI9341** TFT implementation added
  + Added 8/16 bit implementation
+ MIKROE Touch Panel implementation added
  + Using transistor logic
+ API layer touch panel has reduced footprint if MIKROE Touch Panel implementation is used
+ Added header generation based on actual library name
  + For example, in order to include `MikroSDK.Driver.OneWire` library header, simply type
    + `#include "MikroSDK.Driver.OneWire"`
  + Implemented for whole SDK project for easier file access

### Improvements

+ Uart write/read APIs changed to use actual byte sized data
+ AVR low level UART IVT
  + Added option to switch between IVT and ORG mapping/access for interrupt service routines
+ Timer/PWM code optimised for AVR MCUs
  + Improved code readability
  + Added check for NULL pointers
  + Surplus code moved to MCU specific definition files
+ AVR ATmega UART implementation optimized for high-speed baud rate settings
  + High-speed mode used if regular speed mode error exceeds 2.5% as defined in documentation
+ `pin_af_t` redefinition issues
  + Reorganized for all ARM and RISC-V MCUs
+ CMake now sets defaults ADC resolution based on specific MCU, not only architecture
+ Added stop bit generation for AVR software I2C implementation

### Fixes

+ Fixed reported [GITHUB ISSUE](https://github.com/MikroElektronika/mikrosdk_v2/issues/4)
  + Instance handler now set correctly
+ `./targets/avr_8bit/mikroe/avr/src/tim`
  + Fixed register addresses
+ `./targets/avr_8bit/mikroe/avr/include`
  + Pin maps are no longer linked as weak
+ Added additional ports and pins to AVR GPIO implementation
+ AVR GPIO implementation now functions correctly for all GPIO ports
  + Previously, all ports after H ( I, J, K ... ) didn't work
+ Removed **14** MCUs from mikroSDK due to insufficient memory issues
  + `ATmega16`
  + `ATmega164A`
  + `ATmega164P`
  + `ATmega164PA`
  + `ATmega168`
  + `ATmega168A`
  + `ATmega168P`
  + `ATmega168PA`
  + `ATmega168PB`
  + `ATmega169A`
  + `ATmega169P`
  + `ATmega169PA`
  + `ATmega16A`
  + `ATmega16U4`
+ IVT redefined properly for ATXmega E5 MCU series
  + Resulted in addition of another USART module (USART2)
+ Opening existing click tests from mikroSDK project for EasyAVR v8 and v7 resulted in error
+ Opening mikroSDK as a project using a designer setup disables the option to switch to a regular type project
  + Now able to switch freely
+ One-Wire implementation for ARM used to overwrite read data bits/bytes
  + Fix implemented for all ARM MCUs
+ Unable to open specific `CMakeLists.txt` files from mikroSDK project

### NEW HARDWARE

Support added for following hardware:

+ [mikromedia for PIC18FJ](https://www.mikroe.com/mikromedia-3-pic18fj)
+ [mikromedia for PIC18FK](https://www.mikroe.com/mikromedia-3-pic18fk)
+ [mikromedia for XMEGA](https://www.mikroe.com/mikromedia-3-xmega)
+ [mikromedia for STM32 M3](https://www.mikroe.com/mikromedia-3-stm32f3)
+ [mikromedia for STM32 M4](https://www.mikroe.com/mikromedia-3-stm32f4)
+ [mikromedia for TIVA C Series](https://www.mikroe.com/mikromedia-3-tiva)
+ [Mikromedia 3 for PIC32MZ Capacitive FPI with Frame](https://www.mikroe.com/mikromedia-3-for-pic32mz-capacitive-fpi-with-frame)
+ [Mikromedia 3 for PIC32MZ Capacitive FPI with Bezel](https://www.mikroe.com/mikromedia-3-for-pic32mz-capacitive-fpi-with-bezel)
+ [Mikromedia 5 for PIC32MZ Capacitive FPI with Bezel](https://www.mikroe.com/mikromedia-5-for-pic32mz-capacitive-fpi-with-bezel)
+ [EasyMX PRO v7a for STM32](https://www.mikroe.com/easymx-pro-v7a-for-stm32)
+ [EasyPIC PRO v7 MCUcard with PIC18F8722](https://www.mikroe.com/easypic-pro-v7-pic18f8722)
+ [EasyPIC PRO v7 MCUcard with PIC18F8520](https://www.mikroe.com/easypic-pro-v7-pic18f8520)

> All new hardware has adequate clock schemes set as well.

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
