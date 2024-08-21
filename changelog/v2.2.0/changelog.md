<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.2.0`

+ released: 2021-09-30

## Changes

- [`v2.2.0`](#v220)
  - [Changes](#changes)
    - [NXP KINETIS SDK](#nxp-kinetis-sdk)
    - [NEW HARDWARE](#new-hardware)
    - [DEVELOPMENT KIT PACKAGE](#development-kit-package)
  - [PLANET DEBUG](#planet-debug)
  - [Improvements](#improvements)
  - [Fixes](#fixes)
    - [Git relevant updates](#git-relevant-updates)
    - [Test examples](#test-examples)
    - [Collaborators](#collaborators)

### <font color=red>NXP KINETIS SDK</font>

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

### NEW HARDWARE

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

### DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all 27 new hardware definitions

## PLANET DEBUG

**PLANET DEBUG setups updated with mikroSDK packages.**

*Now, all click examples can be run out of the box on PLANET DEBUG.*

**5 systems have been updated:**

+ `Fusion for KINETIS v8 - 1`
+ `Fusion for KINETIS v8 - 2`
+ `Fusion for KINETIS v8 - 3`
+ `Fusion for KINETIS v8 - 4`
+ `Fusion for ARM v8 - 5`

For more information on `PLANET DEBUG` please visit following [LINK](https://www.mikroe.com/planet-debug).

## Improvements

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

## Fixes

+ Removed following chips from mikroSDK
  + `STM32H743AGIx`
  + `STM32H743VGHx`
  + `STM32L082KBTx`
  + `STM32L082KBUx`

Chips were initially added by mistake.

They aren't supported in `mikroC AI for ARM` toolchain.

+ Added CPP guards to all `board.h` files

### Git relevant updates

**Workflow added.**

1. **Automatic response to contribution;**
2. **Automatic response to issue creation.**

### Test examples

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

### Collaborators

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

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
