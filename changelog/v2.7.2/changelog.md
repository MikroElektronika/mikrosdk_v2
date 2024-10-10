<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.7.2`

+ released: 2023-03-08

## Changes

+ [`v2.7.2`](#v272)
  + [Changes](#changes)
    + [New Features](#new-features)
    + [Improvements](#improvements)
    + [Fixes](#fixes)
    + [NEW HARDWARE](#new-hardware)

### New Features

+ mikroSDK logger modified
  + Added implementation for standard output to terminal
+ mikroSDK modified to include custom boards
  + Feature now allows users to add their own board definitions to mikroSDK seamlessly
  + [Modified file](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/bsp/board/CMakeLists.txt)
+ Graphic library improved
  + Ellipse added to draw objects

### Improvements

+ **ILI9341** setup build improved
  + Setup will now be buildable only for devices which have adequate pin connections

### Fixes

+ Fixed HAL layer array initialization for 8-bit architectures
  + Previously, MCUs with only one pin per module didn't function correctly
  + Fixed for following modules:
    + ADC
    + I2C
    + PWM
    + SPI
    + UART

### NEW HARDWARE

Support added for following hardware:

+ [ATmega328P](https://www.microchip.com/en-us/product/ATmega328P)
  + Fully supported in mikroSDK
+ [Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3)
  + Fully supported in mikroSDK
  + Added shield definitions for mikroBUS
    + [Arduino UNO click shield](https://www.mikroe.com/arduino-uno-click-shield)
+ [UNI Clicker](https://www.mikroe.com/uni-clicker) added to AVR mikroSDK

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
