# CHANGELOG

*All notable changes to this project shall be documented in this file.*

**VERSIONS:**

+ **[v2.7.1](#v271)**
+ **[v2.7.0](#v270)**
+ **[v2.6.0](#v260)**
+ **[v2.5.1](#v251)**
+ **[v2.5.0](#v250)**
+ **[v2.4.0](#v240)**
+ **[v2.3.0](#v230)**
+ **[v2.2.0](#v220)**
+ **[v2.1.1](#v211)**
+ **[v2.1.0](#v210)**
+ **[v2.0.3](#v203)**
+ **[v2.0.2](#v202)**
+ **[v2.0.1](#v201)**
+ **[v2.0.0](#v200)**

---
---
---

## `v2.7.1`

+ released: 2022-12-01

### `2.7.1` Changes

1. **[New Features](#271-new-features)**
2. **[Improvements](#271-improvements)**
3. **[Fixes](#271-fixes)**
4. **[NEW HARDWARE](#271-new-hardware)**

#### `2.7.1` New Features

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

#### `2.7.1` Improvements

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

#### `2.7.1` Fixes

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

#### `2.7.1` NEW HARDWARE

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
**[BACK TO TOP OF 2.7.1](#v271)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.7.0`

+ released: 2022-12-01

### `2.7.0` Changes

1. **[AVR low level hal support](#font-colorredavrfont)**
2. **[Improvements](#270-improvements)**
3. **[Fixes](#270-fixes)**
4. **[NEW HARDWARE](#270-new-hardware)**
5. **[PLANET DEBUG](#270-planet-debug)**
6. **[Collaborators](#270-collaborators)**

#### <font color=red>AVR</font>

**AVR MCUs supported!**

|      MCU      |      MCU       |      MCU      |
| :-----------: | :------------: | :-----------: |
|  AT90USB1286  |  AT90USB1287   |  AT90USB646   |
|  AT90USB647   |   ATmega128    |  ATmega1280   |
|  ATmega1281   |   ATmega1284   |  ATmega1284P  |
|  ATmega128A   |    ATmega16    |  ATmega164A   |
|  ATmega164P   |  ATmega164PA   |   ATmega168   |
|  ATmega168A   |   ATmega168P   |  ATmega168PA  |
|  ATmega168PB  |   ATmega16A    |  ATmega16U4   |
|  ATmega2560   |   ATmega2561   |   ATmega32    |
|  ATmega324A   |   ATmega324P   |  ATmega324PA  |
|  ATmega324PB  |   ATmega328    |   ATmega32A   |
|  ATmega32U4   |    ATmega64    |   ATmega640   |
|   ATmega644   |   ATmega644A   |  ATmega644P   |
|  ATmega644PA  |   ATmega64A    | ATxmega128A1U |
| ATxmega128A3  | ATxmega128A3U  | ATxmega128A4U |
| ATxmega128B1  |  ATxmega128B3  | ATxmega128D3  |
| ATxmega128D4  |  ATxmega16A4   | ATxmega16A4U  |
|  ATxmega16D4  |  ATxmega16E5   | ATxmega192A3  |
| ATxmega192A3U |  ATxmega192D3  | ATxmega256A3  |
| ATxmega256A3B | ATxmega256A3BU | ATxmega256A3U |
| ATxmega256D3  |  ATxmega32A4   | ATxmega32A4U  |
|  ATxmega32D3  |  ATxmega32D4   |  ATxmega32E5  |
| ATxmega384D3  |  ATxmega64A1U  |  ATxmega64A3  |
| ATxmega64A3U  |  ATxmega64A4U  |  ATxmega64B1  |
|  ATxmega64B3  |  ATxmega64D3   |  ATxmega64D4  |
|  ATmega328PB  |   ATmega169A   |  ATmega169P   |
|  ATmega169PA  |   ATmega325    |  ATmega3250   |
|  ATmega3250A  |  ATmega3250P   | ATmega3250PA  |
|  ATmega325A   |   ATmega325P   |  ATmega325PA  |
|   ATmega329   |   ATmega3290   |  ATmega3290A  |
|  ATmega3290P  |   ATmega329A   |  ATmega329P   |
|  ATmega329PA  |   ATmega645    |  ATmega6450   |
|  ATmega6450A  |  ATmega6450P   |  ATmega645A   |
|  ATmega645P   |   ATmega649    |  ATmega6490   |
|  ATmega6490A  |  ATmega6490P   |  ATmega649A   |
|  ATmega649P   |

**Supported modules:**

+ **NEW** Software I2C implemention for AVR MCUs
+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)

**Files added:**

+ [assembly.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/common/include/assembly.h)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/hal_ll/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/adc/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/hal_ll/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/one_wire/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/spi_master/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/tim/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/uart/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/common/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/core/CMakeLists.txt)
+ [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/common/include/common_macros.h)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/adc/implementation_1/hal_ll_adc.c)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/adc/implementation_2/hal_ll_adc.c)
+ [hal_ll_adc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/adc/hal_ll_adc.h)
+ [hal_ll_analog_in_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/adc/hal_ll_analog_in_map.h)
+ [hal_ll_bit_control.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/common/include/hal_ll_bit_control.h)
+ [hal_ll_core.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/core/src/hal_ll_core.c)
+ [hal_ll_core.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/core/include/hal_ll_core.h)
+ [hal_ll_core_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/core/include/hal_ll_core_defines.h)
+ [hal_ll_core_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/core/include/hal_ll_core_port.h)
+ [hal_ll_gpio.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/hal_ll_gpio.c)
+ [hal_ll_gpio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio.h)
+ [hal_ll_gpio_constants.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_constants.h)
+ [hal_ll_gpio_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)
+ [hal_ll_gpio_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/implementation_1/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/implementation_2/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/implementation_3/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/i2c/hal_ll_i2c_master.h)
+ [hal_ll_i2c_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/i2c/hal_ll_i2c_pin_map.h)
+ [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/one_wire/hal_ll_one_wire.c)
+ [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/one_wire/hal_ll_one_wire.h)
+ [hal_ll_pin_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/hal_ll_pin_names.h)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/spi_master/implementation_1/hal_ll_spi_master.c)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/spi_master/implementation_2/hal_ll_spi_master.c)
+ [hal_ll_spi_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/spi_master/hal_ll_spi_master.h)
+ [hal_ll_spi_master_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/spi_master/hal_ll_spi_master_pin_map.h)
+ [hal_ll_target.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/hal_ll_target.h)
+ [hal_ll_target_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/hal_ll_target_names.h)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/tim/implementation_1/hal_ll_tim.c)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/tim/implementation_2/hal_ll_tim.c)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/tim/implementation_3/hal_ll_tim.c)
+ [hal_ll_tim.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/tim/hal_ll_tim.h)
+ [hal_ll_tim_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/tim/hal_ll_tim_pin_map.h)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/uart/implementation_1/hal_ll_uart.c)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/uart/implementation_2/hal_ll_uart.c)
+ [hal_ll_uart.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/uart/hal_ll_uart.h)
+ [hal_ll_uart_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/uart/hal_ll_uart_pin_map.h)

#### `2.7.0` Improvements

+ Improved `Graphic Library` implementation
  + Improvement for issue of bad conversion for special case
  + Added check if result is `+Inf`, or `-Inf` since cast to integer is undefined
  + Added `max` and `min` int instead
+ Added option to disable/enable whole module based on availability

#### `2.7.0` Fixes

+ Fixed VTFT imlplementation for `PIC18F57Q43`
  + API now returns adequate active instance for further use
+ Fixed `I2C` implementation 2 for PIC 8bit devices
  + Restart signal is now generated adequatelly
  + Fix impacts following devices:
    + `PIC18F25K42`
    + `PIC18F26K42`
    + `PIC18F27K42`
    + `PIC18F45K42`
    + `PIC18F46K42`
    + `PIC18F47K42`
    + `PIC18F55K42`
    + `PIC18F56K42`
    + `PIC18F57K42`
    + `PIC18LF25K42`
    + `PIC18LF26K42`
    + `PIC18LF27K42`
    + `PIC18LF45K42`
    + `PIC18LF46K42`
    + `PIC18LF47K42`
    + `PIC18LF55K42`
    + `PIC18LF56K42`
    + `PIC18LF57K42`
    + `PIC18F57Q43`
+ Fixed `GPIO` implementation for `RISC-V` devices
  + Unlock routine fixed for SWJ pins
  + User is now available to use SWJ pins
  + Affects all `GIGADEVICE` MCUs
+ Fixed TFT port setting for:
  + `MCU CARD 11 FOR PIC`
    + Set to adequate 8bit port
+ Fixed inclusion of adequate `mcu_definitions` header file for following MCUs:
  + `STM32L100C6_AUx`
  + `STM32L100R8_ATx`
  + `STM32L100RB_ATx`
  + `STM32L151C6_ATx`
  + `STM32L151C6_AUx`
  + `STM32L151C8_ATx`
  + `STM32L151C8_AUx`
  + `STM32L151CB_ATx`
  + `STM32L151CB_AUx`
  + `STM32L151R6_AHx`
  + `STM32L151R6_ATx`
  + `STM32L151R8_AHx`
  + `STM32L151R8_ATx`
  + `STM32L151RB_AHx`
  + `STM32L151RB_ATx`
  + `STM32L151RC_ATx`
  + `STM32L151V8_AHx`
  + `STM32L151V8_ATx`
  + `STM32L151VB_AHx`
  + `STM32L151VB_ATx`
  + `STM32L151VC_ATx`
  + `STM32L152C6_ATx`
  + `STM32L152C6_AUx`
  + `STM32L152C8_ATx`
  + `STM32L152C8_AUx`
  + `STM32L152CB_ATx`
  + `STM32L152CB_AUx`
  + `STM32L152R6_AHx`
  + `STM32L152R6_ATx`
  + `STM32L152R8_AHx`
  + `STM32L152R8_ATx`
  + `STM32L152RB_AHx`
  + `STM32L152RB_ATx`
  + `STM32L152RC_ATx`
  + `STM32L152V8_AHx`
  + `STM32L152V8_ATx`
  + `STM32L152VB_AHx`
  + `STM32L152VB_ATx`
  + `STM32L152VC_ATx`
  + `STM32L162RC_ATx`
  + `STM32L162VC_ATx`

#### `2.7.0` NEW HARDWARE

Support added for following hardware:

+ [EasyAVR PRO v8](https://www.mikroe.com/easyavr-pro-v8)
+ [SIBRAIN FOR ATMEGA3250](https://www.mikroe.com/sibrain-for-atmega3250)
+ [SIBRAIN FOR ATMEGA6450](https://www.mikroe.com/sibrain-for-atmega6450)
+ [EasyAVR v7](https://www.mikroe.com/easyavr)

#### `2.7.0` PLANET DEBUG

+ Incoming update with newly released AVR boards

#### `2.7.0` Collaborators

**We would like to thank the following people for contributing:**

+ **[@Valentin Hubert](https://github.com/vahu72)**
  + **Software I2C** full implementation for AVR
    + **[view files](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/implementation_3/hal_ll_i2c_master.c)**

---
**[BACK TO TOP OF 2.7.0](#v270)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.6.0`

+ released: 2022-06-16

### `2.6.0` Changes

1. **[RISC-V low level hal support](#font-colorredrisc-v-sdkfont)**
2. **[New Features](#260-new-features)**
3. **[NEW HARDWARE](#260-new-hardware)**
4. **[PLANET DEBUG](#260-planet-debug)**
5. Updated relevant **[development kit package](#260-development-kit-package)**
6. **[Test examples](#260-test-examples)**

#### <font color=red>RISC-V SDK</font>

**RISV-V MCU architecture supported!**

|      MCU      |      MCU      |
| :-----------: | :-----------: |
| GD32VF103C4T6 | GD32VF103C6T6 |
| GD32VF103C8T6 | GD32VF103CBT6 |
| GD32VF103R4T6 | GD32VF103R6T6 |
| GD32VF103R8T6 | GD32VF103RBT6 |
| GD32VF103T4U6 | GD32VF103T6U6 |
| GD32VF103T8U6 | GD32VF103TBU6 |
| GD32VF103V8T6 | GD32VF103VBT6 |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)

**Files added:**

+ [assembly.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/assembly.h)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/adc/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/hal_ll/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/i2c/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/one_wire/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/spi_master/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/tim/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/uart/CMakeLists.txt)
+ [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/common_macros.h)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/adc/implementation_1/hal_ll_adc.c)
+ [hal_ll_adc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/adc/hal_ll_adc.h)
+ [hal_ll_adc_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/adc/hal_ll_adc_pin_map/implementation_1/hal_ll_adc_pin_map.h)
+ [hal_ll_bit_control.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/hal_ll_bit_control.h)
+ [hal_ll_core.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/src/hal_ll_core.c)
+ [hal_ll_core.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core.h)
+ [hal_ll_core_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core_defines.h)
+ [hal_ll_core_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/src/gigadevice/bumblebee/hal_ll_core_port.c)
+ [hal_ll_core_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core_port.h)
+ [hal_ll_gpio.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c)
+ [hal_ll_gpio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h)
+ [hal_ll_gpio_constants.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_constants.h)
+ [hal_ll_gpio_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c)
+ [hal_ll_gpio_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/i2c/implementation_1/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/i2c/hal_ll_i2c_master.h)
+ [hal_ll_i2c_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/i2c/hal_ll_i2c_pin_map/implementation_1/hal_ll_i2c_pin_map.h)
+ [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/one_wire/hal_ll_one_wire.c)
+ [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/one_wire/hal_ll_one_wire.h)
+ [hal_ll_pin_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_pin_names.h)
+ [hal_ll_rcu.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_rcu.h)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/spi_master/implementation_1/hal_ll_spi_master.c)
+ [hal_ll_spi_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/spi_master/hal_ll_spi_master.h)
+ [hal_ll_spi_master_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/spi_master/hal_ll_spi_master_pin_map/implementation_1/hal_ll_spi_master_pin_map.h)
+ [hal_ll_target.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_target.h)
+ [hal_ll_target_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_target_names.h)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/tim/implementation_1/hal_ll_tim.c)
+ [hal_ll_tim.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/tim/hal_ll_tim.h)
+ [hal_ll_tim_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/tim/hal_ll_tim_pin_map/implementation_1/hal_ll_tim_pin_map.h)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/uart/implementation_1/hal_ll_uart.c)
+ [hal_ll_uart.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/uart/hal_ll_uart.h)
+ [hal_ll_uart_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/uart/hal_ll_uart_pin_map/implementation_1/hal_ll_uart_pin_map.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C4T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C6T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103CBT6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R4T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R6T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103RBT6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T4U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T6U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T8U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103TBU6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103V8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103VBT6/mcu_definitions.h)

#### `2.6.0` New Features

+ CMake build system with automated functionalities:
  + Adding files
  + Removing files
  + Renaming files for the CMake project
  + Adding/removing libraries from the CMake project

**With the addition of `touch_controller` libs, it is now possible to switch**
**mid DESIGNER project to any of the supported displays. There is no need**
**to create a new project. mikroSDK will take care of that for you.**

Files added:

+ ./middleware/touch_controller/CMakeLists.txt
+ ./middleware/touch_controller/lib/CMakeLists.txt
+ ./middleware/touch_controller/lib/src/touch_controller.c
+ ./middleware/touch_controller/lib/include/touch_controller.h

#### `2.6.0` NEW HARDWARE

Support added for following hardware:

+ [UNI-DS v8](https://www.mikroe.com/uni-ds-v8)
+ [SIBRAIN FOR PIC24HJ256GP610](https://www.mikroe.com/sibrain-for-pic24hj256gp610)
+ [SIBRAIN FOR DSPIC33FJ256GP710A](https://www.mikroe.com/sibrain-for-dspic33fj256gp710a)
+ [SIBRAIN FOR PIC24EP512GU814](https://www.mikroe.com/sibrain-for-pic24ep512gu814)
+ [SIBRAIN FOR DSPIC33EP512MU814](https://www.mikroe.com/sibrain-for-dspic33ep512mu814)
+ [EasyPIC FUSION v7 MCUcard with PIC24FJ128GA310](https://www.mikroe.com/easypic-fusion-v7-pic24fj128ga310)
+ [EasyPIC FUSION v7 MCUcard with PIC24EP512GU810](https://www.mikroe.com/easypic-fusion-v7-pic24ep512gu810)
+ [EasyPIC FUSION v7 MCUcard with dsPIC33FJ256GP710A](https://www.mikroe.com/easypic-fusion-v7-dspic33fj256gp710a)
+ [EasyPIC FUSION v7 MCUcard with dsPIC33EP512MU810](https://www.mikroe.com/easypic-fusion-v7-dspic33ep512mu810)
+ [Discovery kit with STM32L4R9AI MCU](https://www.st.com/en/evaluation-tools/32l4r9idiscovery.html)

#### `2.6.0` PLANET DEBUG

+ All 80 PD systems updated
  + New setups added with CMake
  + Each PD system now has two separate setups
    + One for older NECTO Studio versions
    + One for NECTO Studio v2 and up

#### `2.6.0` DEVELOPMENT KIT PACKAGE

+ With the introduction of CMake build system in NECTO Studio, there is no need for the development kit anymore
+ Removed from repository

#### `2.6.0` Test examples

**All test examples have been revamped to work with CMake build system.**

---
**[BACK TO TOP OF 2.6.0](#v260)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.5.1`

+ released: 2022-03-04

### `2.5.1` Changes

1. **[NEW HARDWARE](#251-new-hardware)**
2. Updated relevant **[development kit package](#251-development-kit-package)**
3. **[Improvements](#251-improvements)**
4. **[Fixes](#251-fixes)**

#### `2.5.1` NEW HARDWARE

+ New board definitions added:
  + [Sparkfun MicroMod mikroBUS Carrier Board](https://www.sparkfun.com/products/18710)

**Config files added for adequate `NEW` boards.**

#### `2.5.1` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added new hardware definitions

#### `2.5.1` Improvements

*Support added for Enhanced PWM pins in PIC architecture.*

*185* MCU's in total affected by this change.

> You will now be able to utilize pins that are Enhanced PWM capable.
> Some PIC18 family devices have Enhanced Capture/Compare/PWM (ECCP) modules.
> These modules contain a 16-bit register, which can operate as a 16-bit Capture
> register, a 16-bit Compare register or a PWM Master/Slave Duty Cycle register.
> These Enhanced Capture/Compare/PWM modules are upward compatible with
> Standard Capture/Compare/PWM modules.
>> Note that all of this is done by the mikroSDK based on the pin selection.

List of MCU's affected:

|   MCU NAME   |   MCU NAME   |   MCU NAME   |   MCU NAME   |   MCU NAME   |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| PIC18F24J11  | PIC18F24J50  | PIC18F24K50  | PIC18F25J11  | PIC18F25J50  |
| PIC18F25K50  | PIC18F25K80  | PIC18F26J11  | PIC18F26J13  | PIC18F26J50  |
| PIC18F26J53  | PIC18F26K22  | PIC18F26K80  | PIC18F27J13  | PIC18F27J53  |
|  PIC18F4455  |  PIC18F4458  | PIC18F44J11  | PIC18F44J50  |  PIC18F4515  |
|  PIC18F4525  |  PIC18F4550  |  PIC18F4553  |  PIC18F4585  | PIC18F45J11  |
| PIC18F45J50  | PIC18F45K22  | PIC18F45K50  | PIC18F45K80  |  PIC18F4610  |
|  PIC18F4620  |  PIC18F4680  |  PIC18F4682  |  PIC18F4685  | PIC18F46J11  |
| PIC18F46J13  | PIC18F46J50  | PIC18F46J53  | PIC18F46K22  | PIC18F46K80  |
| PIC18F47J13  | PIC18F47J53  |  PIC18F6520  |  PIC18F6525  |  PIC18F6527  |
|  PIC18F6585  | PIC18F65J10  | PIC18F65J11  | PIC18F65J15  | PIC18F65J50  |
| PIC18F65J94  | PIC18F65K22  | PIC18F65K80  | PIC18F65K90  |  PIC18F6620  |
|  PIC18F6621  |  PIC18F6622  |  PIC18F6627  |  PIC18F6628  |  PIC18F6680  |
| PIC18F66J10  | PIC18F66J11  | PIC18F66J15  | PIC18F66J16  | PIC18F66J50  |
| PIC18F66J55  | PIC18F66J60  | PIC18F66J65  | PIC18F66J94  | PIC18F66K22  |
| PIC18F66K80  | PIC18F66K90  |  PIC18F6720  |  PIC18F6722  |  PIC18F6723  |
| PIC18F67J10  | PIC18F67J11  | PIC18F67J50  | PIC18F67J60  | PIC18F67J94  |
| PIC18F67K22  | PIC18F67K90  |  PIC18F8520  |  PIC18F8525  |  PIC18F8527  |
|  PIC18F8585  | PIC18F85J10  | PIC18F85J11  | PIC18F85J15  | PIC18F85J50  |
| PIC18F85J94  | PIC18F85K22  | PIC18F85K90  |  PIC18F8620  |  PIC18F8621  |
|  PIC18F8622  |  PIC18F8627  |  PIC18F8628  |  PIC18F8680  | PIC18F86J10  |
| PIC18F86J11  | PIC18F86J15  | PIC18F86J16  | PIC18F86J50  | PIC18F86J55  |
| PIC18F86J60  | PIC18F86J65  | PIC18F86J94  | PIC18F86K22  | PIC18F86K90  |
|  PIC18F8720  |  PIC18F8722  |  PIC18F8723  | PIC18F87J10  | PIC18F87J11  |
| PIC18F87J50  | PIC18F87J60  | PIC18F87J94  | PIC18F87K22  | PIC18F87K90  |
| PIC18F95J94  | PIC18F96J60  | PIC18F96J65  | PIC18F96J94  | PIC18F97J60  |
| PIC18F97J94  | PIC18LF24J11 | PIC18LF24J50 | PIC18LF24K50 | PIC18LF25J11 |
| PIC18LF25J50 | PIC18LF25K50 | PIC18LF25K80 | PIC18LF26J11 | PIC18LF26J13 |
| PIC18LF26J50 | PIC18LF26J53 | PIC18LF26K22 | PIC18LF26K80 | PIC18LF27J13 |
| PIC18LF27J53 | PIC18LF4455  | PIC18LF4458  | PIC18LF44J11 | PIC18LF44J50 |
| PIC18LF4515  | PIC18LF4525  | PIC18LF4550  | PIC18LF4553  | PIC18LF4585  |
| PIC18LF45J11 | PIC18LF45J50 | PIC18LF45K22 | PIC18LF45K50 | PIC18LF45K80 |
| PIC18LF4610  | PIC18LF4620  | PIC18LF4680  | PIC18LF4682  | PIC18LF4685  |
| PIC18LF46J11 | PIC18LF46J13 | PIC18LF46J50 | PIC18LF46J53 | PIC18LF46K22 |
| PIC18LF46K80 | PIC18LF47J13 | PIC18LF47J53 | PIC18LF6520  | PIC18LF6527  |
| PIC18LF65K80 | PIC18LF6622  | PIC18LF6627  | PIC18LF6628  | PIC18LF66K80 |
| PIC18LF6722  | PIC18LF6723  | PIC18LF8520  | PIC18LF8527  | PIC18LF8622  |
| PIC18LF8627  | PIC18LF8628  | PIC18LF8720  | PIC18LF8722  | PIC18LF8723  |

#### `2.5.1` Fixes

+ Fixed `mcu_card.h` W/R connection from `PA13` to `PA8`
  + Designer examples dind't work appropriately prior to this fix
  + Cards affected with this change
    + [MCU CARD 29 for STM32 STM32F205RB](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f205rb)
    + [MCU CARD 29 for STM32 STM32F215RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f215re)
    + [MCU CARD 29 for STM32 STM32F405RG](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f405rg)
    + [MCU CARD 29 for STM32 STM32F415RG](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f415rg)
    + [MCU CARD 29 for STM32 STM32F401RB](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f401rb)
    + [MCU CARD 29 for STM32 STM32F411RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f411re)
    + [MCU CARD 29 for STM32 STM32F446RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f446re)
    + [MCU CARD 29 for STM32 STM32F412RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f412re)
    + [MCU CARD 29 for STM32 STM32F413RH](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f413rh)
    + [MCU CARD 29 for STM32 STM32F423RH](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f423rh)

---
**[BACK TO TOP OF 2.5.1](#v251)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.5.0`

+ released: 2022-02-01

### `2.5.0` Changes

1. **[New Features](#250-new-features)**
2. **[Mikromedia shields](#250-mikromedia-shields)**
3. **[NEW HARDWARE](#250-new-hardware)**
4. Updated relevant **[development kit package](#250-development-kit-package)**
5. **[Improvements](#250-improvements)**
6. **[Test examples](#250-test-examples)**

#### `2.5.0` New Features

**Support added for One Wire protocol**

> 1-Wire protocol utilizes only a single data line for communication,
> so don�t you worry about cluttering your project (your MCU as well) with multiple
> pins (Mikroe�s Click boards that are 1-Wire capable are predominately using PWM pin for this action).
> Devices that are 1-Wire capable have something unique to themselves � ROM address � which, in its core,
> is a 64-bit number, helping product designers create hardware products with `serial numbers` embedded in them,
> replacing traditional physical labels for product�s serial number.

+ Files added
  + [drv_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_one_wire.h)
  + [drv_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_one_wire/drv_one_wire.c)
  + [hal_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_one_wire.h)
  + [hal_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_one_wire/hal_one_wire.c)
  + [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/one_wire/hal_ll_one_wire.c)
  + [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/one_wire/hal_ll_one_wire.c)
  + [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/one_wire/hal_ll_one_wire.h)
  + [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/one_wire/hal_ll_one_wire.h)
  + [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/one_wire/hal_ll_one_wire.c)
  + [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/one_wire/hal_ll_one_wire.c)
  + [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/one_wire/hal_ll_one_wire.c)
  + [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/one_wire/hal_ll_one_wire.h)
  + [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/one_wire/hal_ll_one_wire.h)
  + [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/one_wire/hal_ll_one_wire.h)
  + [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/common_macros.h)
  + [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/common/include/common_macros.h)
  + [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/common/include/common_macros.h)
  + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/one_wire/main.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/one_wire/memake.txt)
  + [ReadMe.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/one_wire/ReadMe.txt)
  + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/clicks/one_wire/click_thermo_2/main.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/clicks/one_wire/memake.txt)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/clicks/one_wire/click_thermo_2/memake.txt)
  + [thermo_2.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/clicks/one_wire/click_thermo_2/thermo_2.c)
  + [thermo_2.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/clicks/one_wire/click_thermo_2/thermo_2.h)

#### `2.5.0` Mikromedia shields

+ Connector definitions for mikromedia shields have been added
  + [mikromedia plus for STM32 Shield](https://www.mikroe.com/mikromedia-4-stm32f4-shield)
  + [mikromedia 7 for STM32 Shield](https://www.mikroe.com/mikromedia-7-for-stm32-shield)

#### `2.5.0` NEW HARDWARE

+ New board definitions added:
  + [Mikromedia 4 for PIC32MZ Capacitive FPI with frame](https://www.mikroe.com/mikromedia-4-for-pic32mz-capacitive-fpi-with-frame)
  + [Mikromedia 4 for PIC32MZ Capacitive FPI with bezel](https://www.mikroe.com/mikromedia-4-for-pic32mz-capacitive-fpi-with-bezel)
  + [Mikromedia 5 for PIC32MZ Capacitive FPI with frame](https://www.mikroe.com/mikromedia-5-for-pic32mz-capacitive-fpi-with-frame)

**Config files added for adequate `NEW` boards.**

#### `2.5.0` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all **3** new hardware definitions

#### `2.5.0` Improvements

+ Added following calculated delays
  + `5 us`
  + `6 us`
  + `9 us`
  + `10 us`
  + `55 us`
  + `60 us`
  + `64 us`
  + `70 us`
  + `410 us`
  + `480 us`
+ Added `common_macros.h` header file
  + All macros shall be declared in one file

#### `2.5.0` Test examples

+ Added following test examples
  + `one_wire`
    + General One Wire testing
  + `clicks`
    + `one_wire`
      + `thermo_2_click`
        + Test showcases current ambient temperature via UART terminal

**[BACK TO TOP OF 2.5.0](#v250)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.4.0`

+ released: 2021-12-28

### `2.4.0` Changes

1. **[Resistive displays](#240-resistive-displays)**
2. **[Middleware](#240-middleware)**
   1. **[STMPE811](#stmpe811)**
   2. **[STMPE810](#stmpe810)**
   3. **[STMPE610](#stmpe610)**
   4. **[TSC2003](#tsc2003)**
3. **[Mikromedia shields](#240-mikromedia-shields)**
4. **[NEW HARDWARE](#240-new-hardware)**
5. Updated relevant **[development kit package](#240-development-kit-package)**
6. **[Fixes](#240-fixes)**
7. **[Improvements](#240-improvements)**
8. **[Recursive build automation](#240-recursive-build-automation)**
9. **[Test examples](#240-test-examples)**
10. **[Collaborators](#240-collaborators)**

#### `2.4.0` Resistive displays

Support added for 4 resistive displays.

+ Displays added:
  + **[TFT Board 3 Resistive](https://www.mikroe.com/tft-board-3-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-3-resisitive-schematic.pdf)
  + **[TFT Board 4 Resistive](https://www.mikroe.com/tft-board-4-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-4-resisitive-schematic.pdf)
  + **[TFT Board 5 Resistive](https://www.mikroe.com/tft-board-5-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-5-resisitive-schematic.pdf)
  + **[TFT Board 7 Resistive](https://www.mikroe.com/tft-board-7-resistive)**
    + [SCHEMATIC](https://download.mikroe.com/tft_board_resistive/tft-board-7-resisitive-schematic.pdf)

Displays have SSD1963 controller, which is already supported, and `STMPE811` touch controller.

#### `2.4.0` Middleware

##### STMPE811

+ Files added:
  + [stmpe811.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/include/stmpe811.h)
  + [stmpe811.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/src/stmpe811.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/stmpe811/lib/memake.txt)

[STMPE811 Datasheet](https://datasheetspdf.com/pdf-file/633509/STMicroelectronics/STMPE811/1).

##### STMPE810

Added `STMPE811` library is compatible with `STMPE810`.

For the sake of simplicity, `STMPE810` devices will use `STMPE811` library.

Please refer to [STMPE811](#stmpe811).

##### STMPE610

Added `STMPE811` library is compatible with `STMPE610`.

For the sake of simplicity, `STMPE610` devices will use `STMPE811` library.

Please refer to [STMPE811](#stmpe811).

##### TSC2003

Support added for TI's `TSC2003` touch controller.

+ Files added:
  + [tsc2003.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/include/tsc2003.h)
  + [tsc2003.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/src/tsc2003.c)
  + [memake.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/tsc2003/lib/memake.txt)

> Note:
>> Library is functional, but will be officialy added in Necto later.

#### `2.4.0` Mikromedia shields

+ Connector definitions for mikromedia shields have been added
  + [Mikromedia 3 Capacitive shield](https://www.mikroe.com/mikromedia-3-capacitive-shield)
  + [Mikromedia 4 Capacitive shield](https://www.mikroe.com/mikromedia-4-capacitive-shield)
  + [Mikromedia 5 Capacitive shield](https://www.mikroe.com/mikromedia-5-capacitive-shield)
  + [Mikromedia 7 Capacitive shield](https://www.mikroe.com/mikromedia-7-capacitive-shield)

#### `2.4.0` NEW HARDWARE

+ New board definitions added:
  + [TFT Board 3 Resistive](https://www.mikroe.com/tft-board-3-resistive)
  + [TFT Board 4 Resistive](https://www.mikroe.com/tft-board-4-resistive)
  + [TFT Board 5 Resistive](https://www.mikroe.com/tft-board-5-resistive)
  + [TFT Board 7 Resistive](https://www.mikroe.com/tft-board-7-resistive)
  + [Mikromedia 3 for PIC Capacitive FPI with bezel](https://www.mikroe.com/mikromedia-3-for-pic-capacitive-fpi-with-bezel)
  + [Mikromedia 3 for PIC Capacitive FPI with frame](https://www.mikroe.com/mikromedia-3-for-pic-capacitive-fpi-with-frame)
  + [Mikromedia Plus for PIC32MX7](https://www.mikroe.com/mikromedia-4-pic32mx7)
  + [Mikromedia Plus for STM32](https://www.mikroe.com/mikromedia-4-stm32f4)
  + [Mikromedia Plus for STM32F7](https://www.mikroe.com/mikromedia-4-stm32f7)
  + [Mikromedia 7 for STM32F4](https://www.mikroe.com/mikromedia-7-stm32f4)
  + [Mikromedia 7 for STM32F7](https://www.mikroe.com/mikromedia-7-stm32f7)

**Config files added for adequate `NEW` boards.**

#### `2.4.0` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all **11** new hardware definitions

#### `2.4.0` Fixes

+ Fixed inadequate UART alternate function setting for STM32F1x chips
  + Inadequate alternate function setting for certain pins
+ Fixed all baud rate calculation return values
  + `HAL_LL` functions for calculating baud rates now all return actual baud set on hardware
+ Some `MK22x` chips didn't have all NVIC defined
  + 20 files in total
+ Fixed all issues with inadequate pin checking types
  + e.g trying to place a word value in a byte variable
+ Updated low level UART impelementations
  + Adequately sets stop bits, data bits and parity settings

#### `2.4.0` Improvements

+ NXP High Speed ADC
  + All `MKV5x` chips now have a fully supported HSADC module
  + Results in High speed ADC (HSADC) adds faster and more precise measurements to any project
+ Touch Panel library no longer requires constant values for screen width and height
  + Done by memake python automation
+ The addition of shields for Mikromedia boards now allows for Click example building and testing
+ Removed unnecessary handle checking in low level implementations
  + Results in quicker code execution
+ Changed board macro naming convention for DIP connections

#### `2.4.0` Recursive build automation

*Updated powershell script for automated recursive `SDK` build.*

*Script now writes adequate progress level based on run settings.*

Files changed:

+ [build-hal-recursion-ci.ps1](./scripts/build-hal-recursion-ci.ps1)
+ [utility.ps1](./scripts/utility.ps1)

For more information, please refer to main script [DESCRIPTION](./scripts/ReadMe.md)

#### `2.4.0` Test examples

*Updated `tft_touch_panel` test example.*

**Example is updated to work with new resistive displays and touch controllers.**

#### `2.4.0` Collaborators

**We would like to thank the following people for contributing:**

+ **[@NikolaDucak](https://github.com/NikolaDucak)**
  + **STMPE811 library** full implementation
    + **[view files](./middleware/stmpe811)**

**[BACK TO TOP OF 2.4.0](#v240)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.3.0`

+ released: 2021-10-28

### `2.3.0` Changes

1. **[TIVA low level hal support](#tiva-sdk)**
2. **[NEW HARDWARE](#230-new-hardware)**
3. Updated relevant **manifest files**
4. Updated relevant **[development kit package](#230-development-kit-package)**
5. **[Added adequate configuration files](#230-added-adequate-configuration-files)**
6. **[PLANET DEBUG](#230-planet-debug)**
7. **[Recursive build automation](#230-recursive-build-automation)**
8. **[Test examples](#230-test-examples)**
9. **[Collaborators](#230-collaborators)**

#### <font color=red>TIVA SDK</font>

+ **Support added for 71 Texas Instruments TIVA MCU's**

| CHIP NAME     | CHIP NAME     | CHIP NAME     |
| ------------- | ------------- | ------------- |
| TM4C1230C3PM  | TM4C1230D5PM  | TM4C1230E6PM  |
| TM4C1230H6PM  | TM4C1231C3PM  | TM4C1231D5PM  |
| TM4C1231D5PZ  | TM4C1231E6PM  | TM4C1231E6PZ  |
| TM4C1231H6PGE | TM4C1231H6PM  | TM4C1231H6PZ  |
| TM4C1232C3PM  | TM4C1232D5PM  | TM4C1232E6PM  |
| TM4C1232H6PM  | TM4C1233C3PM  | TM4C1233D5PM  |
| TM4C1233D5PZ  | TM4C1233E6PM  | TM4C1233E6PZ  |
| TM4C1233H6PGE | TM4C1233H6PM  | TM4C1233H6PZ  |
| TM4C1236D5PM  | TM4C1236E6PM  | TM4C1236H6PM  |
| TM4C1237D5PM  | TM4C1237D5PZ  | TM4C1237E6PM  |
| TM4C1237E6PZ  | TM4C1237H6PGE | TM4C1237H6PM  |
| TM4C1237H6PZ  | TM4C123AE6PM  | TM4C123AH6PM  |
| TM4C123BE6PM  | TM4C123BE6PZ  | TM4C123BH6PGE |
| TM4C123BH6PM  | TM4C123BH6PZ  | TM4C123BH6ZRB |
| TM4C123FE6PM  | TM4C123FH6PM  | TM4C123GE6PM  |
| TM4C123GE6PZ  | TM4C123GH6PGE | TM4C123GH6PM  |
| TM4C123GH6PZ  | TM4C123GH6ZRB | TM4C123GH6ZXR |
| TM4C1290NCPDT | TM4C1290NCZAD | TM4C1292NCPDT |
| TM4C1292NCZAD | TM4C1294KCPDT | TM4C1294NCPDT |
| TM4C1294NCZAD | TM4C1297NCZAD | TM4C1299KCZAD |
| TM4C1299NCZAD | TM4C129CNCPDT | TM4C129CNCZAD |
| TM4C129DNCPDT | TM4C129DNCZAD | TM4C129EKCPDT |
| TM4C129ENCPDT | TM4C129ENCZAD | TM4C129LNCZAD |
| TM4C129XKCZAD | TM4C129XNCZAD |

**Supported modules:**

1. **ADC**
   + Full module support
2. **SPI**
   + Full module support
3. **UART**
   + Full module support
   + Implemented using interrupts
4. **I2C**
   + Full module support
5. **PWM**
   + Full module support
6. **GPIO**
   + Full module support

#### `2.3.0` NEW HARDWARE

+ **[Fusion for TIVA v8](https://www.mikroe.com/fusion-for-tiva)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyMX Pro v7 for TIVA](https://www.mikroe.com/easymx-pro-tiva)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C129XNCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c129xnczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C1294NCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c1294nczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C129XKCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c129xkczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C129LNCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c129lnczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C129ENCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c129enczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C1299KCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c1299kczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR TIVA TM4C1299NCZAD](https://www.mikroe.com/mcu-card-for-tiva-tm4c1299nczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 2 FOR TIVA TM4C123GH6PZ](https://www.mikroe.com/mcu-card-2-for-tiva-tm4c123gh6pz)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 FOR TIVA TM4C1294KCPDT](https://www.mikroe.com/mcu-card-3-for-tiva-tm4c1294kcpdt)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 FOR TIVA TM4C1294NCPDT](https://www.mikroe.com/mcu-card-3-for-tiva-tm4c1294ncpdt)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 FOR TIVA TM4C129EKCPDT](https://www.mikroe.com/mcu-card-3-for-tiva-tm4c129ekcpdt)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 FOR TIVA TM4C129ENCPDT](https://www.mikroe.com/mcu-card-3-for-tiva-tm4c129encpdt)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyMx PRO v7 for Tiva MCU card with TM4C123GH6PMI](https://www.mikroe.com/easymx-pro-v7-tiva-tm4c123gh6pmi)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyMx PRO v7 for Tiva MCU card with TM4C123GH6PZL](https://www.mikroe.com/easymx-pro-v7-tiva-tm4c123gh6pzl)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyMx PRO v7 for Tiva MCU card with TM4C129XNCZAD](https://www.mikroe.com/easymx-pro-v7-tiva-tm4c129xnczad)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated

**Config files added for adequate `NEW` boards.**

#### `2.3.0` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all 17 new hardware definitions

#### `2.3.0` Added adequate configuration files

Configuration files for following hardware has been added:

+ [Clicker 2 for PIC18FJ](https://www.mikroe.com/clicker-2-pic18fj)
+ [PIC32MX Clicker](https://www.mikroe.com/clicker-pic32mx)
+ [Clicker 2 for PIC32MZ](https://www.mikroe.com/clicker-2-for-pic32mz)

#### `2.3.0` PLANET DEBUG

**PLANET DEBUG setups updated with mikroSDK packages.**

*Now, all click examples can be run out of the box on PLANET DEBUG.*

**3 systems have been updated:**

+ `Fusion for TIVA v8 - 1`
+ `Fusion for TIVA v8 - 2`
+ `Fusion for TIVA v8 - 3`

For more information on `PLANET DEBUG` please visit following [LINK](https://www.mikroe.com/planet-debug).

#### `2.3.0` Recursive build automation

*Updated powershell script for automated recursive `SDK` build.*

Files changed:

+ [ReadMe.md](./scripts/ReadMe.md)
+ [build-hal-recursion-ci.ps1](./scripts/build-hal-recursion-ci.ps1)
+ [utility.ps1](./scripts/utility.ps1)
+ [customParams.json](./scripts/customParams.json)

For more information, please refer to main script [DESCRIPTION](./scripts/ReadMe.md)

#### `2.3.0` Test examples

*Added following test examples:*

+ `clicks`
  + **SPI**
    + `click_magneto`
  + **UART**
    + `click_samltouch`

Examples are used for testing mikroSDK specific module cases.

#### `2.3.0` Collaborators

**We would like to thank the following people for contributing:**

+ **[@vladarcv](https://github.com/vladarcv)**
  + **ADC library** all supported TIVA chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/adc/implementation_1/hal_ll_adc.c)**
  + **UART library** all supported TIVA chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/uart/implementation_1/hal_ll_uart.c)**
+ **[@predragcurcic](https://github.com/predragcurcic)**
  + **I2C library** all supported TIVA chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/i2c/implementation_1/hal_ll_i2c_master.c)**
+ **[@tbiocanin](https://github.com/tbiocanin)**
  + **SPI library** all supported TIVA chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/spi_master/implementation_1/hal_ll_spi_master.c)**
+ **[@NovakovicA](https://github.com/NovakovicA)**
  + **TIM/PWM library** all supported TIVA chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/tim/implementation_1/hal_ll_tim.c)**
+ **[@theo-violleau](https://github.com/theo-violleau)**
  + Helped out on generating adequate **mcu_definitions** files for TIVA chips

**[BACK TO TOP OF 2.3.0](#v230)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.2.0`

+ released: 2021-09-30

### `2.2.0` Changes

1. **[NXP low level hal support](#nxp-kinetis-sdk)**
2. **[NEW HARDWARE](#220-new-hardware)**
3. Updated relevant **manifest files**
4. Updated relevant **[development kit package](#220-development-kit-package)**
5. **[PLANET DEBUG](#220-planet-debug)**
6. **[Improvements](#220-improvements)**
7. **[Fixes](#220-fixes)**
8. **[GIT relevant updates](#220-git-relevant-updates)**
9. **[Test examples](#220-test-examples)**
10. **[Collaborators](#220-collaborators)**

#### <font color=red>NXP KINETIS SDK</font>

+ **Support added for 147 NXP Kinetis MCU's**

| CHIP NAME       | CHIP NAME       | CHIP NAME       | CHIP NAME       | CHIP NAME       |
| --------------- | --------------- | --------------- | --------------- | --------------- |
| MK20DN128VFM5   | MK20DN128VFT5   | MK20DN128VLF5   | MK20DN128VLH5   | MK20DN128VMP5   |
| MK20DN32VFM5    | MK20DN32VFT5    | MK20DN32VLF5    | MK20DN32VLH5    | MK20DN32VMP5    |
| MK20DN64VFM5    | MK20DN64VFT5    | MK20DN64VLF5    | MK20DN64VLH5    | MK20DN64VMP5    |
| MK20DX128VFM5   | MK20DX128VFT5   | MK20DX128VLF5   | MK20DX128VLH5   | MK20DX32VFM5    |
| MK20DX32VFT5    | MK20DX32VLF5    | MK20DX32VLH5    | MK20DX32VMP5    | MK20DX64VFM5    |
| MK20DX64VFT5    | MK20DX64VLF5    | MK20DX64VLH5    | MK20DX64VMP5    | MK22FN128CAH12  |
| MK22FN128VDC10  | MK22FN128VLH10  | MK22FN128VLL10  | MK22FN128VMP10  | MK22FN1M0AVLH12 |
| MK22FN1M0AVLK12 | MK22FN1M0AVLL12 | MK22FN1M0AVLQ12 | MK22FN1M0AVMC12 | MK22FN1M0AVMD12 |
| MK22FN1M0VLH12  | MK22FN1M0VLK12  | MK22FN1M0VLL12  | MK22FN1M0VLQ12  | MK22FN1M0VMC12  |
| MK22FN1M0VMD12  | MK22FN256CAH12  | MK22FN256VDC12  | MK22FN256VLH12  | MK22FN256VLL12  |
| MK22FN256VMP12  | MK22FN512CAP12  | MK22FN512VDC12  | MK22FN512VFX12  | MK22FN512VLH12  |
| MK22FN512VLL12  | MK22FN512VMP12  | MK22FX512AVLH12 | MK22FX512AVLK12 | MK22FX512AVLL12 |
| MK22FX512AVLQ12 | MK22FX512AVMC12 | MK22FX512AVMD12 | MK22FX512VLH12  | MK22FX512VLK12  |
| MK22FX512VLL12  | MK22FX512VLQ12  | MK22FX512VMC12  | MK22FX512VMD12  | MK51DN256CLQ10  |
| MK51DN256CMD10  | MK51DN512CLL10  | MK51DN512CLQ10  | MK51DN512CMC10  | MK51DN512CMD10  |
| MK51DX256CLK10  | MK51DX256CLL10  | MK51DX256CMC10  | MK53DN512CLQ10  | MK53DN512CMD10  |
| MK53DX256CLQ10  | MK53DX256CMD10  | MK60DN256VLL10  | MK60DN256VLQ10  | MK60DN256VMC10  |
| MK60DN256VMD10  | MK60DN512VLL10  | MK60DN512VLQ10  | MK60DN512VMC10  | MK60DN512VMD10  |
| MK60DX256VLL10  | MK60DX256VLQ10  | MK60DX256VMC10  | MK60DX256VMD10  | MK64FN1M0CAJ12  |
| MK64FN1M0VDC12  | MK64FN1M0VLL12  | MK64FN1M0VLQ12  | MK64FN1M0VMD12  | MK64FX512VDC12  |
| MK64FX512VLL12  | MK64FX512VLQ12  | MK64FX512VMD12  | MK65FN2M0CAC18  | MK65FN2M0VMI18  |
| MK65FX1M0CAC18  | MK65FX1M0VMI18  | MK66FN2M0VLQ18  | MK66FN2M0VMD18  | MK66FX1M0VLQ18  |
| MK66FX1M0VMD18  | MK80FN256VDC15  | MK80FN256VLL15  | MK80FN256VLQ15  | MK82FN256VDC15  |
| MK82FN256VLL15  | MK82FN256VLQ15  | MKV42F128VLF16  | MKV42F128VLH16  | MKV42F128VLL16  |
| MKV42F256VLH16  | MKV42F256VLL16  | MKV42F64VLF16   | MKV42F64VLH16   | MKV44F128VLF16  |
| MKV44F128VLH16  | MKV44F128VLL16  | MKV44F256VLH16  | MKV44F256VLL16  | MKV44F64VLF16   |
| MKV44F64VLH16   | MKV46F128VLH16  | MKV46F128VLL16  | MKV46F256VLH16  | MKV46F256VLL16  |
| MKV56F1M0VLL24  | MKV56F1M0VLQ24  | MKV56F1M0VMD24  | MKV56F512VLL24  | MKV56F512VLQ24  |
| MKV56F512VMD24  | MKV58F1M0VLL24  | MKV58F1M0VLQ24  | MKV58F1M0VMD24  | MKV58F512VLL24  |
| MKV58F512VLQ24  | MKV58F512VMD24  |

**Supported modules:**

1. **ADC**
   + Full module support
2. **SPI**
   + Full module support
3. **UART**
   + Full module support
   + Implemented using interrupts
4. **I2C**
   + Full module support
5. **PWM**
   + Full module support
6. **GPIO**
   + Full module support

#### `2.2.0` NEW HARDWARE

+ **[Fusion for KINETIS v8](https://www.mikroe.com/fusion-for-kinetis)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyPIC v7a](https://www.mikroe.com/easypic-v7a)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[EasyPIC PRO v7a](https://www.mikroe.com/easypic-pro-v7a)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Kinetis Clicker](https://www.mikroe.com/clicker-kinetis)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Clicker 2 for Kinetis](https://www.mikroe.com/clicker-2-kinetis)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Hexiwear Workstation](https://www.mikroe.com/hexiwear-workstation)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Hexiwear Docking Station](https://www.mikroe.com/hexiwear-docking-station)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Hexiwear Battery Pack](https://www.mikroe.com/hexiwear-battery-pack)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Quail](https://www.mikroe.com/quail)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[FlowPaw](https://www.mikroe.com/flowpaw-kit)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for Kinetis Capacitive](https://www.mikroe.com/mikromedia-3-for-kinetis-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for Kinetis Capacitive FPI with Frame](https://www.mikroe.com/mikromedia-3-for-kinetis-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for Kinetis Capacitive FPI with Bezel](https://www.mikroe.com/mikromedia-3-for-kinetis-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for Kinetis Capacitive](https://www.mikroe.com/mikromedia-4-for-kinetis-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for Kinetis Capacitive FPI with Frame](https://www.mikroe.com/mikromedia-4-for-kinetis-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for Kinetis Capacitive FPI with Bezel](https://www.mikroe.com/mikromedia-4-for-kinetis-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for Kinetis Capacitive](https://www.mikroe.com/mikromedia-5-for-kinetis-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for Kinetis Capacitive FPI with Frame](https://www.mikroe.com/mikromedia-5-for-kinetis-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for Kinetis Capacitive FPI with Bezel](https://www.mikroe.com/mikromedia-5-for-kinetis-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR KINETIS MK64FN1M0VDC12](https://www.mikroe.com/mcu-card-for-kinetis-mk64fn1m0vdc12)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD FOR KINETIS MK64FX512VDC12](https://www.mikroe.com/mcu-card-for-kinetis-mk64fx512vdc12)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 2 FOR KINETIS MK20DN128VFM5](https://www.mikroe.com/mcu-card-2-for-kinetis-mk20dn128vfm5)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 2 FOR KINETIS MK20DX128VFM5](https://www.mikroe.com/mcu-card-2-for-kinetis-mk20dx128vfm5)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 FOR KINETIS MKV58F1M0VLQ24](https://www.mikroe.com/mcu-card-3-for-kinetis-mkv58f1m0vlq24)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 4 FOR KINETIS MK51DN512CLQ10](https://www.mikroe.com/mcu-card-4-for-kinetis-mk51dn512clq10)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 5 FOR KINETIS MKV42F64VLH16](https://www.mikroe.com/mcu-card-5-for-kinetis-mkv42f64vlh16)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 10 FOR KINETIS MK60DN512VLQ10](https://www.mikroe.com/mcu-card-10-for-kinetis-mk60dn512vlq10)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated

**Config files added for adequate `NEW` boards.**

#### `2.2.0` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all 27 new hardware definitions

### `2.2.0` PLANET DEBUG

**PLANET DEBUG setups updated with mikroSDK packages.**

*Now, all click examples can be run out of the box on PLANET DEBUG.*

**5 systems have been updated:**

+ `Fusion for KINETIS v8 - 1`
+ `Fusion for KINETIS v8 - 2`
+ `Fusion for KINETIS v8 - 3`
+ `Fusion for KINETIS v8 - 4`
+ `Fusion for ARM v8 - 5`

For more information on `PLANET DEBUG` please visit following [LINK](https://www.mikroe.com/planet-debug).

### `2.2.0` Improvements

+ Added `STM32G071R6Tx` to mikroSDK
  + Full mikroBUS module support
+ Static global handler initial value added
  + SPI module; `STM32` implementation
+ Added guard for `HAL_PIN_NC` pins
  + Code exits faster in case of undeclared pins
  + Implemented for 46 source files
+ Added definitions for `USB_UART_TX` and `USB_UART_RX` pins
  + Added for every board
  + All examples can now be successfuly built

### `2.2.0` Fixes

+ Removed following chips from mikroSDK
  + `STM32H743AGIx`
  + `STM32H743VGHx`
  + `STM32L082KBTx`
  + `STM32L082KBUx`

Chips were initially added by mistake.

They aren't supported in `mikroC AI for ARM` toolchain.

+ Added CPP guards to all `board.h` files

#### `2.2.0` Git relevant updates

**Workflow added.**

1. **Automatic response to contribution;**
2. **Automatic response to issue creation.**

#### `2.2.0` Test examples

*Added following test examples:*

+ `mikrobus`
  + `adc`
    + Reads raw adc data and outputs it via UART
  + `gpio`
    + Sets all mikroBUS pins as digital outputs and toggles them in defined interval
  + `i2c`
    + Writes data to EEPROM click, reads it and compares it
  + `spi`
    + Writes data to SRAM click, reads it and compares it
  + `pwm`
    + Tests all mikroBUS PWM pins by toggling duty cycle from max to min in defined steps
  + `uart`
    + Test all mikroBUS pins using a simple echo example

All examples test all mikroBUS pins defined in adequate `board.h` file.

Each example can be used to test a single pin/module as well.

For more information, please refer to each example and adequate `ReadMe.txt` file.

#### `2.2.0` Collaborators

**We would like to thank the following people for contributing:**

+ **[@niksicesma](https://github.com/niksicesma)**
  + **ADC library** initial version for NXP Kinetis chips
    + **[implementation_2](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/adc/implementation_2/hal_ll_adc.c)**
  + **I2C library** initial version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/i2c/implementation_1/hal_ll_i2c_master.c)**
  + **UART library** initial version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/uart/implementation_1/hal_ll_uart.c)**
    + **[implementation_2](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/uart/implementation_2/hal_ll_uart.c)**
+ **[@MasaKilibarda](https://github.com/MasaKilibarda)**
  + **SPI library** initial version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/spi_master/implementation_1/hal_ll_spi_master.c)**
+ **[@milan265](https://github.com/milan265)**
  + **TIM/PWM library** initial version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/tim/implementation_1/hal_ll_tim.c)**
  + **SPI library** final version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/spi_master/implementation_1/hal_ll_spi_master.c)**
+ **[@Nebojsa-B](https://github.com/Nebojsa-B)**
  + **ADC library** initial version for NXP Kinetis chips
    + **[implementation_1](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/adc/implementation_1/hal_ll_adc.c)**
+ **[@LouisDurand02](https://github.com/LouisDurand02)**
  + Helped out on generating adequate **mcu_definitions** files for NXP chips

**[BACK TO TOP OF 2.2.0](#v220)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.1.1`

+ released: 2021-08-24

### `2.1.1` Changes

#### `2.1.1` NEW HARDWARE

+ **[Fusion for PIC v8](https://www.mikroe.com/fusion-for-pic-v8)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[PICPLC16 v7a](https://www.mikroe.com/picplc16-v7a)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for PIC Capacitive](https://www.mikroe.com/mikromedia-3-for-pic-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for PIC32MZ Capacitive](https://www.mikroe.com/mikromedia-3-for-pic32mz-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for PIC32MZ Capacitive](https://www.mikroe.com/mikromedia-4-for-pic32mz-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for PIC32MZ Capacitive](https://www.mikroe.com/mikromedia-5-for-pic32mz-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for STM32F2 Capacitive](https://www.mikroe.com/mikromedia-3-for-stm32f2-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for STM32F2 Capacitive FPI Frame](https://www.mikroe.com/mikromedia-3-for-stm32f2-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 3 for STM32F2 Capacitive FPI Bezel](https://www.mikroe.com/mikromedia-3-for-stm32f2-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for STM32F2 Capacitive FPI Frame](https://www.mikroe.com/mikromedia-4-for-stm32f2-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 4 for STM32F2 Capacitive FPI Bezel](https://www.mikroe.com/mikromedia-4-for-stm32f2-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for STM32F7 Capacitive](https://www.mikroe.com/mikromedia-5-for-stm32f7-capacitive)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for STM32F7 Capacitive FPI Frame](https://www.mikroe.com/mikromedia-5-for-stm32f7-capacitive-fpi-with-frame)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[Mikromedia 5 for STM32F7 Capacitive FPI Bezel](https://www.mikroe.com/mikromedia-5-for-stm32f7-capacitive-fpi-with-bezel)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[PIC Clicker](https://www.mikroe.com/clicker-pic18fj)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[6LoWPAN Clicker](https://www.mikroe.com/clicker-6lowpan)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[STM32 M4 Clicker](https://www.mikroe.com/clicker-stm32f4)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[SIBRAIN FOR PIC32MZ1024EFK144](https://www.mikroe.com/sibrain-for-pic32mz1024efk144)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[SIBRAIN FOR PIC32MZ1024EFF144](https://www.mikroe.com/sibrain-for-pic32mz1024eff144)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[SIBRAIN FOR PIC32MZ1024EFE144](https://www.mikroe.com/sibrain-for-pic32mz1024efe144)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 13 for STM32 STM32L162ZE](https://www.mikroe.com/mcu-card-13-for-stm32-stm32l162ze)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 13 for STM32 STM32L151ZD](https://www.mikroe.com/mcu-card-13-for-stm32-stm32l151zd)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 13 for STM32 STM32L152ZD](https://www.mikroe.com/mcu-card-13-for-stm32-stm32l152zd)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for STM32 STM32F215ZG](https://www.mikroe.com/mcu-card-for-stm32-stm32f215zg)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for STM32 STM32F405ZG](https://www.mikroe.com/mcu-card-for-stm32-stm32f405zg)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for STM32 STM32F415ZG](https://www.mikroe.com/mcu-card-for-stm32-stm32f415zg)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 11 for STM32 STM32F303VE](https://www.mikroe.com/mcu-card-11-for-stm32-stm32f303ve)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for STM32 STM32F446ZE](https://www.mikroe.com/mcu-card-for-stm32-stm32f446ze)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for STM32 STM32F746ZG](https://www.mikroe.com/mcu-card-for-stm32-stm32f746zg)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD 3 for PIC PIC18F96J65](https://www.mikroe.com/mcu-card-3-for-pic-pic18f96j65)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated
+ **[MCU CARD for PIC PIC18F96J94](https://www.mikroe.com/mcu-card-for-pic-pic18f96j94)**
  + Added adequate board definition files
  + Updated adequate manifest files
  + Configuration files updated

#### `2.1.1` DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all 31 new hardware definitions

### `2.1.1` Fixes

+ Designer projects did not work for 8-bit data ports with higher nibble connections
  + e.g -> data port is PORTE pins 8:15
+ Added adequate defenders for SPI and ADC low level implementation for PIC devices
+ mikroSDK build tool description spelling fixed
+ PIC `Q10` chips I2C baud rate setting
  + Sets correct baud rates now
  + Before the fix, setting 400K would result in 100K on HW
+ I2C busy bit was always high after clock init
  + Affects `STM32F101` and `STM32F103` series of chips
  + [ERRATA](https://www.st.com/resource/en/errata_sheet/cd00273032-stm32f101xfg-and-stm32f103xfg-xldensity-device-limitations-stmicroelectronics.pdf) page `23`, paragraph `2.12.7`
+ PIC32 Logger issue
  + Sending data immediatelly after logger initialization resulted in lost data
+ STM32 M7 Uart fix
  + Sending/receiving large amounts of data resulted in register overflow
+ Missing function declaration for PIC 8-bit chips
  + `hal_ll_spi_master_hw_init` added
+ Unable to edit `ANCON3` register values for some PIC 8-bit chips if PPS Lock bit is set
+ UART general issue
  + Implemented waiting for buffers to be empty before reinitializing the module
  + UART now returns `0` if no data hs been written/read
    + Previously it returned `-1`
+ Fixed structure data access
  + Changed `->` to `.` where necessary
+ Fixed pin check result variable size
+ Fixed setting pins as digital input for 50 PIC32MX chips
  + Fixed analog maps
+ STM32LxSy chips GPIO fix
  + PORTG pins didn't work as expected
+ Designer code generation was wrong for 4 inch bezel mikromedia boards
  + Touchpanel orientation was required

### `2.1.1` Improvements

+ Libraries are now separated per module
  + More efficient
  + Conserves memory
  + No need to include all libraries
    + Include only the one you need
+ Implemented selection per module
  + Now, if same set of pins is available on a different module, that module will be mapped
+ Implemented graphic library port mask selection
+ Designer template now depends on `memake` file and has unified code for TFT manipulation
+ SPI for PIC 8-bit chips now sets baud rate more precisely
  + Previously implemented by using hardware module dividers(2,4,8...)
+ Implemented adequate slew rate setting for PIC32 chips
  + Affects SPI module specifically
+ Removed slew rate setting for 8-bit PIC chips which don't need it
  + Code optimized further
+ SPI click board templates now include data sampling selection
  + 8-bit PIC chips
    + e.g middle,end...
+ SPI initial SCK line glitch on PIC32 chips fixed
+ Unified unused register naming in all low level sources
+ Removed excess verifications
  + Excess `NULL` pointer check
  + Excess `pin name` checks
+ Shared registers for some PIC 8-bit chips
  + Implemented for following chips
    + `PIC18F65J50`
    + `PIC18F66J50`
    + `PIC18F66J55`
    + `PIC18F67J50`
    + `PIC18F85J50`
    + `PIC18F86J50`
    + `PIC18F86J55`
    + `PIC18F87J50`
+ Added nibble control macros for all architectures
  + See following files for more details:
    + [ARM](./targets/arm/mikroe/common/include/hal_ll_bit_control.h)
    + [PIC32](./targets/pic_32bit/mikroe/common/include/hal_ll_bit_control.h)
    + [PIC18](./targets/pic_8bit/mikroe/common/include/hal_ll_bit_control.h)
+ Added mikromedia support for PIC 32-bit chips
+ Added mikromedia support for PIC 8-bit chips

#### Git relevant updates

+ Added following files:
  + List of [Requirements](./REQUIREMENTS.md)
  + List of all supported chips; click [HERE](./SUPPORTED_CHIP_LIST.md) for the list
+ Added workflows ( CI/CD ):
  + Automated response to issue creation
  + Automated response to first contribution

#### `2.1.1` Test examples

*Added following test examples:*

+ `adc`
  + Outputs AD conversion result on diodes or UART terminal
+ `clicker_buttons`
  + Defined test for MikroE&trade; clicker boards
+ `gpio`
  + Tests all GPIO functions
+ `i2c`
  + Tests all I2C functions
+ `mikrobus`
  + Tests all MikroE&trade; development board MikroBUS&trade; connections
+ `pwm`
  + Tests all PWM/TIM functions
+ `spi`
  + Tests all SPI functions
+ `tft_jig`
  + Test all TFT panel connections
+ `tft_touch_panel`
  + Tests TFT Touch panel with basic example
+ `uart`
  + Tests all UART functions
+ `clicks`
  + Tests all modules on specifically selected click boards
    + `adc`
      + `click_ambient_7`
      + `click_force`
      + `click_hall_current_5`
      + `click_pressure_12`
      + `click_slider_2`
    + `gpio`
      + `click_4x4_rgb`
      + `click_cap_touch`
      + `click_opto_encoder_3`
      + `click_pll`
      + `click_sht1x`
      + `click_vibra_sense`
    + `i2c`
      + `click_6dof_imu_11`
      + `click_altitude_3`
      + `click_color_9`
      + `click_ecg_6`
      + `click_light_ranger_2`
    + `pwm`
      + `click_brushless`
      + `click_button_y`
      + `click_dc_motor_8`
      + `click_led_driver_6`
      + `click_stspin250`
    + `spi`
      + `click_bee`
      + `click_ccrf_2`
      + `click_eink_290_inch`
      + `click_magneto_2`
      + `click_oledc`
    + `uart`
      + `click_barcode`
      + `click_ble_8`
      + `click_fingerprint_2`
      + `click_iqrf_2`
      + `click_lte_iot_2`

All examples have a minimum memory requirement, which is handled in each `memake.txt` file
separately.

For more information, please refer to each example and a `ReadMe.txt` if existant.

#### `2.1.1` Recursive build automation

*Added powershell script for automated recursive `SDK` build.*

Files added:

+ [ReadMe.md](./scripts/ReadMe.md)
+ [build-hal-recursion-ci.ps1](./scripts/build-hal-recursion-ci.ps1)
+ [utility.ps1](./scripts/utility.ps1)
+ [customRun.bat](./scripts/customRun.bat)
+ [customRun.sh](./scripts/customRun.sh)
+ [customParams.json](./scripts/customParams.json)

For more information, please refer to main script [DESCRIPTION](./scripts/ReadMe.md)

**[BACK TO TOP OF 2.1.1](#v211)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.1.0`

+ released: 2021-04-29

### `2.1.0` Changes

1. **[PIC32 low level hal support](#pic32-sdk)**
2. **[NEW HARDWARE](#210-new-hardware)**
3. Updated relevant **manifest files**
4. Updated relevant **[development kit package](#210-development-kit-package)**
5. **[Fixes](#210-fixes)**
6. **[Improvements](#210-improvements)**
7. **[GIT relevant updates](#210-git-relevant-updates)**
8. **[Collaborators](#210-collaborators)**

#### <font color=red>PIC32 SDK</font>

+ **Support added for 163 PIC32 MCU's**

**MX CHIPS:**

| CHIP NAME       | CHIP NAME        | CHIP NAME       | CHIP NAME        | CHIP NAME       |
| --------------- | ---------------- | --------------- | ---------------- | --------------- |
| PIC32MX110F016B | PIC32MX210F016B  | PIC32MX320F032H | PIC32MX440F256H  | PIC32MX570F512L |
| PIC32MX110F016C | PIC32MX210F016C  | PIC32MX320F064H | PIC32MX440F512H  | PIC32MX575F256H |
| PIC32MX110F016D | PIC32MX210F016D  | PIC32MX320F128H | PIC32MX450F128H  | PIC32MX575F256L |
| PIC32MX120F032B | PIC32MX220F032B  | PIC32MX320F128L | PIC32MX450F128L  | PIC32MX575F512H |
| PIC32MX120F032C | PIC32MX220F032C  | PIC32MX330F064H | PIC32MX450F256H  | PIC32MX575F512L |
| PIC32MX120F032D | PIC32MX220F032D  | PIC32MX330F064L | PIC32MX450F256HB | PIC32MX664F064H |
| PIC32MX120F064H | PIC32MX230F064B  | PIC32MX340F128H | PIC32MX450F256L  | PIC32MX664F064L |
| PIC32MX130F064B | PIC32MX230F064C  | PIC32MX340F128L | PIC32MX460F256L  | PIC32MX664F128H |
| PIC32MX130F064C | PIC32MX230F064D  | PIC32MX340F256H | PIC32MX460F512L  | PIC32MX664F128L |
| PIC32MX130F064D | PIC32MX230F128H  | PIC32MX340F512H | PIC32MX470F512H  | PIC32MX675F256H |
| PIC32MX130F128H | PIC32MX230F128L  | PIC32MX350F128H | PIC32MX470F512L  | PIC32MX675F256L |
| PIC32MX130F128L | PIC32MX230F256B  | PIC32MX350F128L | PIC32MX470F512LB | PIC32MX675F512H |
| PIC32MX130F256B | PIC32MX230F256D  | PIC32MX350F256H | PIC32MX530F128H  | PIC32MX675F512L |
| PIC32MX130F256D | PIC32MX250F128B  | PIC32MX350F256L | PIC32MX530F128L  | PIC32MX695F512H |
| PIC32MX150F128B | PIC32MX250F128C  | PIC32MX360F256L | PIC32MX534F064H  | PIC32MX695F512L |
| PIC32MX150F128C | PIC32MX250F128D  | PIC32MX360F512L | PIC32MX534F064L  | PIC32MX764F128H |
| PIC32MX150F128D | PIC32MX250F256H  | PIC32MX370F512H | PIC32MX550F256H  | PIC32MX764F128L |
| PIC32MX150F256H | PIC32MX250F256L  | PIC32MX370F512L | PIC32MX550F256L  | PIC32MX775F256H |
| PIC32MX150F256L | PIC32MX270F256B  | PIC32MX420F032H | PIC32MX564F064H  | PIC32MX775F256L |
| PIC32MX170F256B | PIC32MX270F256D  | PIC32MX430F064H | PIC32MX564F064L  | PIC32MX775F512H |
| PIC32MX170F256D | PIC32MX270F256DB | PIC32MX430F064L | PIC32MX564F128H  | PIC32MX775F512L |
| PIC32MX170F512H | PIC32MX270F512H  | PIC32MX440F128H | PIC32MX564F128L  | PIC32MX795F512H |
| PIC32MX170F512L | PIC32MX270F512L  | PIC32MX440F128L | PIC32MX570F512H  | PIC32MX795F512L |

**MZ CHIPS:**

| CHIP NAME         | CHIP NAME         | CHIP NAME         | CHIP NAME         |
| ----------------- | ----------------- | ----------------- | ----------------- |
| PIC32MZ0512EFE064 | PIC32MZ1024EFE064 | PIC32MZ1024EFH064 | PIC32MZ2048EFG064 |
| PIC32MZ0512EFE100 | PIC32MZ1024EFE100 | PIC32MZ1024EFH100 | PIC32MZ2048EFG100 |
| PIC32MZ0512EFE124 | PIC32MZ1024EFE124 | PIC32MZ1024EFH124 | PIC32MZ2048EFG124 |
| PIC32MZ0512EFE144 | PIC32MZ1024EFE144 | PIC32MZ1024EFH144 | PIC32MZ2048EFG144 |
| PIC32MZ0512EFF064 | PIC32MZ1024EFF064 | PIC32MZ1024EFK064 | PIC32MZ2048EFH064 |
| PIC32MZ0512EFF100 | PIC32MZ1024EFF100 | PIC32MZ1024EFK100 | PIC32MZ2048EFH100 |
| PIC32MZ0512EFF124 | PIC32MZ1024EFF124 | PIC32MZ1024EFK124 | PIC32MZ2048EFH124 |
| PIC32MZ0512EFF144 | PIC32MZ1024EFF144 | PIC32MZ1024EFK144 | PIC32MZ2048EFH144 |
| PIC32MZ0512EFK064 | PIC32MZ1024EFG064 | PIC32MZ1024EFM064 | PIC32MZ2048EFM064 |
| PIC32MZ0512EFK100 | PIC32MZ1024EFG100 | PIC32MZ1024EFM100 | PIC32MZ2048EFM100 |
| PIC32MZ0512EFK124 | PIC32MZ1024EFG124 | PIC32MZ1024EFM124 | PIC32MZ2048EFM124 |
| PIC32MZ0512EFK144 | PIC32MZ1024EFG144 | PIC32MZ1024EFM144 | PIC32MZ2048EFM144 |

**Supported modules:**

1. **ADC**
   + Full module support
   + Note --> PIC32 MX chips have a fixed resolution of 10-bit (hw specific)
2. **SPI**
   + Full module support
3. **UART**
   + Full module support
   + Implemented using interrupts
4. **I2C**
   + Full module support
5. **PWM**
   + Full module support
6. **GPIO**
   + Full module support

#### `2.1.0` NEW HARDWARE

1. **[Fusion for PIC32 v8](https://www.mikroe.com/fusion-for-pic32)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
2. **[EasyPIC Fusion v7](https://www.mikroe.com/easypic-fusion)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
3. **[PIC32MX Clicker](https://www.mikroe.com/clicker-pic32mx)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
4. **[PIC32MZ Clicker](https://www.mikroe.com/pic32mz-clicker)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
5. **[Clicker 2 for PIC32MX](https://www.mikroe.com/clicker-2-pic32mx)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
6. **[Clicker 2 for PIC32MZ](https://www.mikroe.com/clicker-2-for-pic32mz)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated
7. **[Flip&Click PIC32MZ](https://www.mikroe.com/flipclick-pic32mz)**
   + Added adequate board definition files
   + Updated adequate manifest files
   + Configuration files updated

**Config files added for adequate `NEW` boards.**

#### `2.1.0` DEVELOPMENT KIT PACKAGE

Updated **[mikroSDK development kit](./development/readme.md)** to follow added hardware.

### `2.1.0` Fixes

1. **`hal_ll_bit_control.h`**
   + Implemented guard for unintentional bit manipulation using expressions
   + Changed files:
      + **[PIC file](./targets/pic_8bit/mikroe/common/include/hal_ll_bit_control.h)**
      + **[PIC32 file](./targets/pic_32bit/mikroe/common/include/hal_ll_bit_control.h)**
      + **[STM32 file](./targets/arm/mikroe/common/include/hal_ll_bit_control.h)**

### `2.1.0` Improvements

1. Updated all ADC memake files
   + Default resolution is now dependent on adequate python regex
2. Clicker 2 for PIC18FK
   + Default UART board pins changed to USB connector
   + Pins are now `RC0` and `RC1`
3. All ADC module resolutions are now set to hardware specific values
   + For example, `PIC32MX` chips have a default value of `10bit`, `STM32` have a default value of `12bit` etc.
   + Relevant files:
      + Driver layer:
         + **[memake.txt](./drv/lib/memake.txt)**
         + **[drv_analog_in.h](./drv/lib/include/drv_analog_in.h)**
      + HAL layer:
         + **[memake.txt](./hal/lib/memake.txt)**
         + **[hal_adc.h](./hal/lib/include/hal_adc.h)**
      + Targets layer:
         + **[PIC memake.txt](./targets/pic_8bit/mikroe/pic18/memake.txt)**
         + **[PIC hal_ll_adc.h](./targets/pic_8bit/mikroe/pic18/include/adc/hal_ll_adc.h)**
         + **[PIC32 memake.txt](./targets/pic_32bit/mikroe/pic32/memake.txt)**
         + **[PIC32 hal_ll_adc.h](./targets/pic_32bit/mikroe/pic32/include/adc/hal_ll_adc.h)**
         + **[STM32 memake.txt](./targets/arm/mikroe/stm32/memake.txt)**
         + **[STM32 hal_ll_adc.h](./targets/arm/mikroe/stm32/include/adc/hal_ll_adc.h)**

#### `2.1.0` Git relevant updates

1. **[CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md)** added
2. **[CONTRIBUTING.md](./CONTRIBUTING.md)** added
3. **[AUTHORS.md](./AUTHORS.md)** updated( added contributors )
4. **Templates** added
   + **[Pull request](./.github/pull_request_template.md)**
   + **[Bug report](./.github/ISSUE_TEMPLATE/bug_report.md)**
   + **[Feature request](./.github/ISSUE_TEMPLATE/feature_request.md)**

#### `2.1.0` Collaborators

**We would like to thank the following people for contributing:**

+ **[@sofijaf](https://github.com/sofijaf)**
  + **[CORE library](./targets/pic_32bit/mikroe/core/src/hal_ll_core.c)** for PIC32 chips
  + **[UART library](./targets/pic_32bit/mikroe/pic32/src/uart/implementation_1/hal_ll_uart.c)** for PIC32MX and PIC32MZ chips
    + Implemented using interrupts
+ **[@sanjamandic](https://github.com/sanjamandic)**
  + **GPIO library** initial version for PIC32 chips
    + **[implementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/hal_ll_gpio.c)**
      + **[subimplementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)**
  + **ADC library** initial version for PIC32MX chips
    + **[implemetation_1](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_1/hal_ll_adc.c)**
+ **[@mkovacevic95](https://github.com/mkovacevic95)**
  + Board def for **[EasyPIC Fusion v7](./bsp/board/include/boards/easypic_fusion_v7/board.h)**
  + MCU Card defs:
    + **[EasyPIC Fusion v7 ETH MCU Card with PIC32MX460F512L](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_pic32mx460f512l/mcu_card.h)**
    + **[EasyPIC Fusion v7 ETH MCU Card with PIC32MX795F512L](./bsp/board/include/mcu_cards/easypic_fusion_v7_eth_mcucard_with_pic32mx795f512l/mcu_card.h)**
    + **[EasyPIC Fusion v7 ETH MCU Card with PIC32MMZ2048EFH144](./bsp/board/include/mcu_cards/easypic_fusion_v7_eth_mcucard_with_pic32mz2048efh144/mcu_card.h)**
  + **[I2C library](./targets/pic_32bit/mikroe/pic32/src/i2c/implementation_1/hal_ll_i2c_master.c)** for PIC32MX and PIC32MZ chips
+ **[@NikolaDucak](https://github.com/NikolaDucak)**
  + **GPIO library** improvements for PIC32 chips
    + **[implementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/hal_ll_gpio.c)**
    + **[subimplementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)**
  + **ADC library** for PIC32MX and PIC32MZ chips
    + **[implemetation_1](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_1/hal_ll_adc.c)** -- PIC32MX
    + **[implemetation_2](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_2/hal_ll_adc.c)** -- PIC32MZ

**[BACK TO TOP OF 2.1.0](#v210)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.3`

+ released: 2021-01-28

### `2.0.3` Changes

+ Added support for **new hardware**
+ Updated relevant **manifest files**
+ Updated relevant **development kit package**
+ Updated **SPI**, **I2C** and **PPS** libraries

**Curiosity HPC** is now supported in mikroSDK 2.0.
**Clicker 2 for STM32/PIC18FJ/PIC18FK** is now supported in mikroSDK 2.0.

Added support for **PIC18F47Q10** chip.

**Added** adequate board definition files for **Curiosity HPC board**.
**Added** adequate board definition files for **Clicker 2 for STM32**.
**Added** adequate board definition files for **Clicker 2 for PIC18FJ**.
**Added** adequate board definition files for **Clicker 2 for PIC18FK**.

**Config files added for adequate `NEW` boards.**

Updated **mikroSDK development kit** to follow added hardware.

+ **Curiosity HPC** - [official page](https://www.microchip.com/Developmenttools/ProductDetails/DM164136)
+ **Clicker 2 for STM32** - [official page](https://www.mikroe.com/clicker-2-stm32f4)
+ **Clicker 2 for PIC18FJ** - [official page](https://www.mikroe.com/clicker-2-pic18fj)
+ **Clicker 2 for PIC18FK** - [official page](https://www.mikroe.com/clicker-2-pic18fk)

### `2.0.3` Fixes

+ `UNI Clicker` renamed to follow naming convention
+ `low level PPS implementation` ( PIC chips )
  + Applies to all PIC chips
  + Updated map sizes to 2 bytes
  + Some chips have more than 255 PPS pin functionalities, hence the map needs to be bigger

**NOTE**: PPS wasn't being set correctly for PIC18xxxK40 chips. Applied PPS fix covers this issue.

### `2.0.3` Improvements

+ `low level SPI implementation` ( PIC chips )
  + **Setting SCK pin as both digital input/output is required**
  + [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 444 for more information
  + In Master mode the clock signal output to the SCK pin is also the clock signal input to the
  peripheral. The pin selected for output with the RxyPPS register must also be selected as the peripheral input with the SSPxCLKPPS register. The pin that is selected using the SSPxCLKPPS register should also be made a digital I/O. This is done by clearing the corresponding ANSEL bit.

+ `low level I2C implementation` ( PIC chips )
  + **Bidirectional pins**
  + [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 289 for more information
    + PPS selections for peripherals with bidirectional signals on a single pin must be made so that the PPS input and PPS output select the same pin

**[BACK TO TOP OF 2.0.3](#v203)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.2`

+ released: 2020-12-30

### `2.0.2` Changes

+ Added support for **new hardware**
+ Updated relevant **manifest files**
+ Updated relevant **development kit package**

**Clicker 4 for STM32** is now supported in mikroSDK 2.0.

**Added** adequate board definition files for **Clicker 4 for STM32**.

Updated **mikroSDK development kit** to follow added hardware.

+ **Clicker 4 for STM32** - [official page](https://www.mikroe.com/clicker-4-for-stm32)

### `2.0.2` Fixes

+ `mcu_definitions` ( PIC chips )
  + **Setting pins as digital/analog**
  + [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/30000575C.pdf) page 431 is at fault
  + Changed setting ANCONx register bits appropriately
    + RA4 pin ( ANCON1 bit 4, not ANCON1 bit 6 )
    + RA5 pin ( ANCON1 bit 5, not ANCON1 bit 4 )
    + RF2 pin ( ANCON1 bit 6, not ANCON1 bit 7 )
    + RF5 pin ( ANCON2 bit 1, not ANCON2 bit 2 )
    + RF6 pin ( ANCON2 bit 2, not ANCON2 bit 3 )
    + RG4 pin ( ANCON2 bit 7, not ANCON3 bit 0 )

Fix applied to following chips:

+ PIC18F97J94
+ PIC18F87J94
+ PIC18F67J94
+ PIC18F96J94
+ PIC18F86J94
+ PIC18F66J94
+ PIC18F95J94
+ PIC18F85J94
+ PIC18F65J94

**[BACK TO TOP OF 2.0.2](#v202)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.1`

+ released: 2020-12-11

### `2.0.1` Changes

+ Added support for **new hardware**
+ Updated relevant **manifest files**
+ Updated relevant **development kit package**

**MCU CARD 11 FOR PIC** is now supported in **mikroSDK 2.0**.

**Added** following **PIC chips**:

+ `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
+ `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

**Added** adequate board definition files for **MCU CARD 11 FOR PIC**.

Updated **mikroSDK development kit** to follow added hardware.

+ `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
+ `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

### `2.0.1` Fixes

+ HAL GPIO low level ( PIC chips )
  + **HAL GPIO low level PIC** implementation now doesn't change previous state of **LATCH** registers.

**[BACK TO TOP OF 2.0.1](#v201)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.0`

+ released: 2020-10-02

**`INITIAL RELEASE.`**

---

**[BACK TO TOP](#changelog)**

---
