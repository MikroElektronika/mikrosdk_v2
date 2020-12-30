---
# CHANGELOG
*All notable changes to this project shall be documented in this file.*

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
