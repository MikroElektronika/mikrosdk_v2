<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.7.0`

+ released: 2022-12-01

## Changes

- [`v2.7.0`](#v270)
  - [Changes](#changes)
    - [AVR](#avr)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)
    - [PLANET DEBUG](#planet-debug)
    - [Collaborators](#collaborators)

### <font color=red>AVR</font>

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

### Improvements

+ Improved `Graphic Library` implementation
  + Improvement for issue of bad conversion for special case
  + Added check if result is `+Inf`, or `-Inf` since cast to integer is undefined
  + Added `max` and `min` int instead
+ Added option to disable/enable whole module based on availability

### Fixes

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

### NEW HARDWARE

Support added for following hardware:

+ [EasyAVR PRO v8](https://www.mikroe.com/easyavr-pro-v8)
+ [SIBRAIN FOR ATMEGA3250](https://www.mikroe.com/sibrain-for-atmega3250)
+ [SIBRAIN FOR ATMEGA6450](https://www.mikroe.com/sibrain-for-atmega6450)
+ [EasyAVR v7](https://www.mikroe.com/easyavr)

### PLANET DEBUG

+ Incoming update with newly released AVR boards

### Collaborators

**We would like to thank the following people for contributing:**

+ **[@Valentin Hubert](https://github.com/vahu72)**
  + **Software I2C** full implementation for AVR
    + **[view files](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/i2c/implementation_3/hal_ll_i2c_master.c)**

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
