<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.3.0`

+ released: 2021-10-28

## Changes

- [`v2.3.0`](#v230)
  - [Changes](#changes)
    - [TIVA SDK](#tiva-sdk)
    - [NEW HARDWARE](#new-hardware)
    - [DEVELOPMENT KIT PACKAGE](#development-kit-package)
    - [Added adequate configuration files](#added-adequate-configuration-files)
    - [PLANET DEBUG](#planet-debug)
    - [Recursive build automation](#recursive-build-automation)
    - [Test examples](#test-examples)
    - [Collaborators](#collaborators)

### <font color=red>TIVA SDK</font>

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

### NEW HARDWARE

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

### DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added all 17 new hardware definitions

### Added adequate configuration files

Configuration files for following hardware has been added:

+ [Clicker 2 for PIC18FJ](https://www.mikroe.com/clicker-2-pic18fj)
+ [PIC32MX Clicker](https://www.mikroe.com/clicker-pic32mx)
+ [Clicker 2 for PIC32MZ](https://www.mikroe.com/clicker-2-for-pic32mz)

### PLANET DEBUG

**PLANET DEBUG setups updated with mikroSDK packages.**

*Now, all click examples can be run out of the box on PLANET DEBUG.*

**3 systems have been updated:**

+ `Fusion for TIVA v8 - 1`
+ `Fusion for TIVA v8 - 2`
+ `Fusion for TIVA v8 - 3`

For more information on `PLANET DEBUG` please visit following [LINK](https://www.mikroe.com/planet-debug).

### Recursive build automation

*Updated powershell script for automated recursive `SDK` build.*

Files changed:

+ [ReadMe.md](./scripts/ReadMe.md)
+ [build-hal-recursion-ci.ps1](./scripts/build-hal-recursion-ci.ps1)
+ [utility.ps1](./scripts/utility.ps1)
+ [customParams.json](./scripts/customParams.json)

For more information, please refer to main script [DESCRIPTION](./scripts/ReadMe.md)

### Test examples

*Added following test examples:*

+ `clicks`
  + **SPI**
    + `click_magneto`
  + **UART**
    + `click_samltouch`

Examples are used for testing mikroSDK specific module cases.

### Collaborators

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

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
