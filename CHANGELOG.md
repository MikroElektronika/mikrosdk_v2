# CHANGELOG
*All notable changes to this project shall be documented in this file.*

---
## `v2.0.3` - released: 2021-02-01

### Changes:
- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**
- Updated **SPI**, **I2C** and **PPS** libraries

**Curiosity HPC** is now supported in mikroSDK 2.0.
**Clicker 2 for STM32/PIC18FJ/PIC18FK** is now supported in mikroSDK 2.0.

Added support for **PIC18F47Q10** chip.

**Added** adequate board definition files for **Curiosity HPC board**.
**Added** adequate board definition files for **Clicker 2 for STM32**.
**Added** adequate board definition files for **Clicker 2 for PIC18FJ**.
**Added** adequate board definition files for **Clicker 2 for PIC18FK**.

**Config files added for adequate `NEW` boards.**

Updated **mikroSDK development kit** to follow added hardware.

- **Curiosity HPC** - [official page](https://www.microchip.com/Developmenttools/ProductDetails/DM164136)
- **Clicker 2 for STM32** - [official page](https://www.mikroe.com/clicker-2-stm32f4)
- **Clicker 2 for PIC18FJ** - [official page](https://www.mikroe.com/clicker-2-pic18fj)
- **Clicker 2 for PIC18FK** - [official page](https://www.mikroe.com/clicker-2-pic18fk)

### Fixes
- `low level PPS implementation` ( PIC chips )
    - Applies to all PIC chips
    - Updated map sizes to 2 bytes
    - Some chips have more than 255 PPS pin functionalities, hence the map needs to be bigger

**NOTE**: PPS wasn't being set correctly for PIC18xxxK40 chips. Applied PPS fix covers this issue.

### Improvements:
- `low level SPI implementation` ( PIC chips )
	- **Setting SCK pin as both digital input/output is required**
	- [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 444 for more information
		- In Master mode the clock signal output to the SCK pin is also the clock signal input to the
		  peripheral. The pin selected for output with the RxyPPS register must also be selected as the peripheral input with the SSPxCLKPPS register. The pin that is selected using the SSPxCLKPPS register should also be made a digital I/O. This is done by clearing the corresponding ANSEL bit.

- `low level I2C implementation` ( PIC chips )
	- **Bidirectional pins**
	- [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 289 for more information
		- PPS selections for peripherals with bidirectional signals on a single pin must be made so that
		  the PPS input and PPS output select the same pin

---
## `v2.0.2` - released: 2020-12-30

### Changes:
- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**

**Clicker 4 for STM32** is now supported in mikroSDK 2.0.

**Added** adequate board definition files for **Clicker 4 for STM32**.

Updated **mikroSDK development kit** to follow added hardware.

- **Clicker 4 for STM32** - [official page](https://www.mikroe.com/clicker-4-for-stm32)

### Fixes:
- `mcu_definitions` ( PIC chips )
	- **Setting pins as digital/analog**
	- [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/30000575C.pdf) page 431 is at fault
		- Changed setting ANCONx register bits appropriately
			- RA4 pin ( ANCON1 bit 4, not ANCON1 bit 6 )
			- RA5 pin ( ANCON1 bit 5, not ANCON1 bit 4 )
			- RF2 pin ( ANCON1 bit 6, not ANCON1 bit 7 )
			- RF5 pin ( ANCON2 bit 1, not ANCON2 bit 2 )
			- RF6 pin ( ANCON2 bit 2, not ANCON2 bit 3 )
			- RG4 pin ( ANCON2 bit 7, not ANCON3 bit 0 )

Fix applied to following chips:

- PIC18F97J94
- PIC18F87J94
- PIC18F67J94
- PIC18F96J94
- PIC18F86J94
- PIC18F66J94
- PIC18F95J94
- PIC18F85J94
- PIC18F65J94

---
## `v2.0.1` - released: 2020-12-11

### Changes:
- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**

**MCU CARD 11 FOR PIC** is now supported in **mikroSDK 2.0**.

**Added** following **PIC chips**:

- `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
- `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

**Added** adequate board definition files for **MCU CARD 11 FOR PIC**.

Updated **mikroSDK development kit** to follow added hardware.

- `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
- `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

### Fixes:
- HAL GPIO low level ( PIC chips )
	- **HAL GPIO low level PIC** implementation now doesn't change previous state of **LATCH** registers.

---
## `v2.0.0` - released: 2020-10-02

**`INITIAL RELEASE.`**

---
