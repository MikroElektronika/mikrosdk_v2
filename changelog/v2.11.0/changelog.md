<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.11.0`

+ released: 2024-04-02

## Changes

+ [`v2.11.0`](#v2110)
  + [Changes](#changes)
    + [XC32](#xc32)
    + [XC16](#xc16)
    + [XC8](#xc8)
    + [Fixes](#fixes)
    + [Improvements](#improvements)
    + [NEW HARDWARE](#new-hardware)

### <font color=red>XC32</font>

+ As of mikroSDK version `2.11.0`, `XC32 v4.35` is officially supported.
+ All **`187`** PIC32 MCUs can now be used with the XC32 toolchain along with full mikroSDK functionality.
+ Linker scripts are included upon selecting adequate setup for your project so it can be easily edited on the fly.
+ All standard modules supported (GPIO, ADC, I2C, PWM, SPI, UART, OneWire, RTC, CAN, DMA and LCD)
+ Third party modules supported
  + TinyUSB (An open source cross-platform USB stack for embedded system)
  + LVGL (Light and Versatile Embedded Graphics Library)
  + FatFs (Generic FAT Filesystem Module)

### <font color=red>XC16</font>

+ As of mikroSDK version `2.11.0`, `XC16 v2.10` is officially supported.
+ All **`531`** dsPIC/PIC24 MCUs can now be used with the XC16 toolchain along with full mikroSDK functionality.
+ Linker scripts are included upon selecting adequate setup for your project so it can be easily edited on the fly.
+ All standard modules supported (GPIO, ADC, I2C, PWM, SPI, UART, OneWire, CAN and LCD)
+ Third party modules supported
  + FatFs (Generic FAT Filesystem Module)

### <font color=red>XC8</font>

+ As of mikroSDK version `2.11.0`, `XC8 v2.46` is officially supported.
+ Due to the complexity of mikroSDK, only **`PIC18xxQ43`** family of MCUs is supported.
+ All standard modules supported (GPIO, ADC, I2C, PWM, SPI, UART, OneWire, CAN, DMA and LCD)
+ Third party modules supported
  + FatFs (Generic FAT Filesystem Module)

### Fixes

+ Fixed `drv/lib/CMakeLists.txt` to include the appropriate subdirectories.
  + Previously, `lib_drv_i2c_master` and `lib_drv_port` were switched. Now, the inclusion is based on their individual definitions – ensuring that each is included as intended.
+ Fixed all low level implementations for PIC32 MCUs to accommodate the release of XC32 toolchain.
+ Fixed issue with gl_text not drawing correct characters on XC compilers.
+ Fixed issue with tp not detecting TP_EVENT_PRESS_UP on tft7 boards.
+ Fixed wrong LCD_TFT_8BIT_CH0 port name for:
  + [dsPIC33EP512MU810](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_dspic33ep512mu810/mcu_card.h)
  + [PIC24EP512GU810](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_pic24ep512gu810/mcu_card.h)
  + [dsPIC33FJ256GP710A](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_dspic33fj256gp710a/mcu_card.h)
  + [PIC24FJ128GA310](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_pic24fj128ga310/mcu_card.h)
+ Fixed wrong HAL_LL_I2C_MAX_SPEED_VALUE for I2CxBRG register for dsPIC devices.
+ Fixed custom board inclusion into project
  + Custom board is not generated in mikroSDK BSP anymore, but in `MIKROE` app data

### Improvements

+ Added doxy style help generation files for mikroSDK
  + Additionally, a layout file has been added as well
+ Changed directory so it can be built as bare metal
  + Changed following files:
    + [./CMakeLists.txt](./CMakeLists.txt)
    + [./platform/CMakeLists.txt](./platform/CMakeLists.txt)
    + [./platform/conversions/lib/CMakeLists.txt](./platform/conversions/lib/CMakeLists.txt)
      + Changed name to `Generic.Conversions`
+ `delays.h` explicitly included in all files which use any delay API
+ Changed order of variables in ili9341.c for MikroC AI for dsPIC due to issue with W2 register.
+ Changed [./hal_ll_adc.c](./targets/pic_16bit/mikroe/dspic/src/adc/implementation_1/hal_ll_adc.c), added setting of pin analog functionality in hal_ll_adc_read function because of special case in tp_mikroe.c where we constantly change pin configuration.
+ Changed [./tsc2003.h](./middleware/tsc2003/lib/include/tsc2003.h), I2C slave address for touch controller is now defined in database.
+ Updated all tests to build with XC compilers
  + Additinally, added preinit routine to every test as well

### NEW HARDWARE

+ Mikromedia 3 for PIC Resistive
+ Mikromedia 3 for PIC Resistive FPI
+ Mikromedia 3 for STM32 Resistive
+ Mikromedia 3 for STM32 Resistive FPI
+ Mikromedia 4 for kinetis Resistive
+ Mikromedia 4 for kinetis Resistive FPI
+ Mikromedia 4 for STM32 Resistive
+ Mikromedia 4 for STM32f2 Resistive FPI
+ Mikromedia 4 for STM32f4 Resistive FPI
+ Mikromedia 4 for STM32f7 Resistive
+ Mikromedia 5 for kinetis Resistive
+ Mikromedia 5 for kinetis Resistive FPI
+ Mikromedia 5 for STM32 Resistive
+ Mikromedia 5 for STM32f4 Resistive FPI
+ Mikromedia 5 for STM32f7 Resistive
+ Mikromedia 5 for STM32f7 Resistive FPI
+ Mikromedia 7 Resistive
+ Mikromedia 7 Resistive FPI

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
