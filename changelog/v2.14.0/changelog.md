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
    + [PIC18xx (Q10 | Q43| Q83 | Q84) and PIC32MZ EC (ECH | ECM | ECH)](#pic18xx-q10--q43-q83--q84-and-pic32mz-ec-ech--ecm--ech)
    + [New Features](#new-features)
      + [mikroSDK](#mikrosdk)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk-1)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk-2)
      + [CORE](#core)
    + [NEW HARDWARE](#new-hardware)

### <font color=red>PIC18xx (Q10 | Q43| Q83 | Q84) and PIC32MZ EC (ECH | ECM | ECH)</font>

**PIC18xQ and PIC32MZ EC MCUs supported!**

|      MCU       |      MCU       |         MCU         |         MCU        |          MCU        |
| :------------: | :------------: |    :------------:   |   :------------:   |    :------------:   |
|  PIC18F24Q10   |  PIC18F46Q43   |     PIC18F26Q84     | PIC32MZ1024ECH064  |  PIC32MZ2048ECG124  |
|  PIC18F25Q10   |  PIC18F47Q43   |     PIC18F27Q84     | PIC32MZ1024ECH100  |  PIC32MZ2048ECG144  |
|  PIC18F26Q10   |  PIC18F55Q43   |     PIC18F46Q84     | PIC32MZ1024ECH124  |  PIC32MZ2048ECH064  |
|  PIC18F27Q10   |  PIC18F56Q43   |     PIC18F47Q84     | PIC32MZ1024ECH144  |  PIC32MZ2048ECH100  |
|  PIC18F45Q10   |  PIC18F26Q83   |     PIC18F56Q84     | PIC32MZ1024ECM064  |  PIC32MZ2048ECH124  |
|  PIC18F46Q10   |  PIC18F27Q83   |     PIC18F57Q84     | PIC32MZ1024ECM100  |  PIC32MZ2048ECH144  |
|  PIC18F25Q43   |  PIC18F46Q83   |  PIC32MZ1024ECG064  | PIC32MZ1024ECM124  |  PIC32MZ2048ECM064  |
|  PIC18F26Q43   |  PIC18F47Q83   |  PIC32MZ1024ECG100  | PIC32MZ1024ECM144  |  PIC32MZ2048ECM100  |
|  PIC18F27Q43   |  PIC18F56Q83   |  PIC32MZ1024ECG124  | PIC32MZ2048ECG064  |  PIC32MZ2048ECM124  |
|  PIC18F45Q43   |  PIC18F57Q83   |  PIC32MZ1024ECG144  | PIC32MZ2048ECG100  |  PIC32MZ2048ECM144  |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ OW (Full module support)

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
+ Added LCD_TFT macros into headers for all Mikromedias that don't use SIBRAIN socket the same way it is implemented for MCU Cards
  + Previously LCD_TFT macros were defined in CMakeLists.txt for TFTs
+ Added `errata` section in PIC32 low level implementation
  + Workarounds from the errata are now grouped and clearly marked for easier reference and maintenance

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
