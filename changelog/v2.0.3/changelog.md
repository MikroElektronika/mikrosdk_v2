<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.0.3`

+ released: 2021-01-28

## Changes

+ [`v2.0.3`](#v203)
  + [Changes](#changes)
    + [General](#general)
    + [Fixes](#fixes)
    + [Improvements](#improvements)

### General

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

### Fixes

+ `UNI Clicker` renamed to follow naming convention
+ `low level PPS implementation` ( PIC chips )
  + Applies to all PIC chips
  + Updated map sizes to 2 bytes
  + Some chips have more than 255 PPS pin functionalities, hence the map needs to be bigger

**NOTE**: PPS wasn't being set correctly for PIC18xxxK40 chips. Applied PPS fix covers this issue.

### Improvements

+ `low level SPI implementation` ( PIC chips )
  + **Setting SCK pin as both digital input/output is required**
  + [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 444 for more information
  + In Master mode the clock signal output to the SCK pin is also the clock signal input to the
  peripheral. The pin selected for output with the RxyPPS register must also be selected as the peripheral input with the SSPxCLKPPS register. The pin that is selected using the SSPxCLKPPS register should also be made a digital I/O. This is done by clearing the corresponding ANSEL bit.

+ `low level I2C implementation` ( PIC chips )
  + **Bidirectional pins**
  + [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 289 for more information
    + PPS selections for peripherals with bidirectional signals on a single pin must be made so that the PPS input and PPS output select the same pin

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
