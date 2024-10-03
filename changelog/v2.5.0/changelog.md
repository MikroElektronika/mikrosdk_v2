<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.5.0`

+ released: 2022-02-01

## Changes

+ [`v2.5.0`](#v250)
  + [Changes](#changes)
    + [New Features](#new-features)
    + [Mikromedia shields](#mikromedia-shields)
    + [NEW HARDWARE](#new-hardware)
    + [DEVELOPMENT KIT PACKAGE](#development-kit-package)
    + [Improvements](#improvements)
    + [Test examples](#test-examples)

### New Features

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

### Mikromedia shields

+ Connector definitions for mikromedia shields have been added
  + [mikromedia plus for STM32 Shield](https://www.mikroe.com/mikromedia-4-stm32f4-shield)
  + [mikromedia 7 for STM32 Shield](https://www.mikroe.com/mikromedia-7-for-stm32-shield)

### NEW HARDWARE

+ New board definitions added:
  + [Mikromedia 4 for PIC32MZ Capacitive FPI with frame](https://www.mikroe.com/mikromedia-4-for-pic32mz-capacitive-fpi-with-frame)
  + [Mikromedia 4 for PIC32MZ Capacitive FPI with bezel](https://www.mikroe.com/mikromedia-4-for-pic32mz-capacitive-fpi-with-bezel)
  + [Mikromedia 5 for PIC32MZ Capacitive FPI with frame](https://www.mikroe.com/mikromedia-5-for-pic32mz-capacitive-fpi-with-frame)

**Config files added for adequate `NEW` boards.**

### DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all **3** new hardware definitions

### Improvements

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

### Test examples

+ Added following test examples
  + `one_wire`
    + General One Wire testing
  + `clicks`
    + `one_wire`
      + `thermo_2_click`
        + Test showcases current ambient temperature via UART terminal

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
