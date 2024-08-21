<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.11.1`

+ released: 2024-06-27

## Changes

- [`v2.11.1`](#v2111)
  - [Changes](#changes)
    - [STM32](#stm32)
    - [XC16 USB](#xc16-usb)
    - [XC32 ETHERNET](#xc32-ethernet)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>STM32</font>

**STM32 MCUs supported!**

|        MCU         |        MCU         |        MCU         |        MCU         |        MCU         |
| :----------------: | :----------------: | :----------------: | :----------------: | :----------------: |
|    STM32C011D6     |    STM32C011F6     |    STM32L4P5ZG     |    STM32G431RB     |     STM32C011J6    |
|    STM32C011F4     |    STM32C011J4     |    STM32L4P5AE     |    STM32L4P5AG     |     STM32L4P5CE    |
|    STM32L4P5QE     |    STM32L4P5QG     |    STM32L4P5RE     |    STM32L4P5RG     |     STM32L4P5VE    |
|    STM32L4P5ZE     |    STM32G431C6     |    STM32G431C8     |    STM32G431CB     |     STM32G431K6    |
|    STM32G431KB     |    STM32G431M6     |    STM32G431M8     |    STM32G431MB     |     STM32G431R6    |
|    STM32G431V6     |    STM32G431V8     |    STM32G431VB     |    STM32G441CB     |     STM32G441KB    |
|    STM32G441RB     |    STM32G441VB     |    STM32G473CB     |    STM32G473CC     |     STM32G473CE    |
|    STM32G473MC     |    STM32G473ME     |    STM32G473PB     |    STM32G473PC     |     STM32G473PE    |
|    STM32G473QC     |    STM32G473QE     |    STM32G473RB     |    STM32G473RC     |     STM32G473RE    |
|    STM32G473VC     |    STM32G473VE     |    STM32G474CB     |    STM32G474CC     |     STM32G474CE    |
|    STM32G474MC     |    STM32G474ME     |    STM32G474PB     |    STM32G474PC     |     STM32G474PE    |
|    STM32G474QC     |    STM32G474QE     |    STM32G474RB     |    STM32G474RC     |     STM32G474RE    |
|    STM32G474VC     |    STM32G474VE     |    STM32G483CE     |    STM32G483ME     |     STM32G483PE    |
|    STM32G483RE     |    STM32G483VE     |    STM32G484CE     |    STM32G484ME     |     STM32G484PE    |
|    STM32G484RE     |    STM32G484VE     |    STM32G491CC     |    STM32G491CE     |     STM32G491KC    |
|    STM32G491MC     |    STM32G491ME     |    STM32G491RC     |    STM32G491RE     |     STM32G491VC    |
|    STM32G4A1CE     |    STM32G4A1KE     |    STM32G4A1ME     |    STM32G4A1RE     |     STM32G4A1VE    |
|    STM32L4Q5CG     |    STM32L4Q5QG     |    STM32L4Q5RG     |    STM32L4Q5VG     |     STM32L4Q5ZG    |
|    STM32C031C6     |    STM32C031F4     |    STM32C031F6     |    STM32C031G4     |     STM32C031G6    |
|    STM32C031K6     |    STM32G051C6     |    STM32G051C8     |    STM32G051F6     |     STM32G051F8    |
|    STM32G051G8     |    STM32G051K6     |    STM32G051K8     |    STM32G061C6     |     STM32G061C8    |
|    STM32G061F8     |    STM32G061G6     |    STM32G061G8     |    STM32G061K6     |     STM32G061K8    |
|    STM32G0B1CC     |    STM32G0B1CE     |    STM32G0B1KB     |    STM32G0B1KC     |     STM32G0B1KE    |
|    STM32G0B1MC     |    STM32G0B1ME     |    STM32G0B1NE     |    STM32G0B1RB     |     STM32G0B1RC    |
|    STM32G0B1VB     |    STM32G0B1VC     |    STM32G0B1VE     |    STM32G0C1CC     |     STM32G0C1CE    |
|    STM32G0C1KE     |    STM32G0C1MC     |    STM32G0C1ME     |    STM32G0C1NE     |     STM32G0C1RC    |
|    STM32G0C1VC     |    STM32G0C1VE     |    STM32L4P5CG     |    STM32L4P5VG     |     STM32G431K8    |
|    STM32G431R8     |    STM32G441MB     |    STM32G473MB     |    STM32G473QB     |     STM32G473VB    |
|    STM32G474MB     |    STM32G474QB     |    STM32G474VB     |    STM32G483QE     |     STM32G484QE    |
|    STM32G491KE     |    STM32G491VE     |    STM32L4Q5AG     |    STM32C031C4     |     STM32C031K4    |
|    STM32G051G6     |    STM32G061F6     |    STM32G0B1CB     |    STM32G0B1MB     |     STM32G0B1RE    |
|    STM32G0C1KC     |    STM32G0C1RE     |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ OW (Full module support)
+ DMA (Full module support)
+ CAN (Full module support)

### <font color=red>XC16 USB</font>

+ Third party modules supported
  + TinyUSB (An open source cross-platform USB stack for embedded systems)

### <font color=red>XC32 ETHERNET</font>

+ Third party modules supported
  + CycloneTCP (An open source cross-platform USB stack for embedded systems)
  + Support added for XC32 compiler

### Fixes

+ Added PD0 and PD1 pins connection for all GD32VF103 MCUs
+ Fixed pin configuration for pins with indexes below 8 in `hal_ll_one_wire.c` implementation for GD32VF103 MCUs
+ Set default CAN baudrate to 125K for all architectures that have CAN module supported
+ Modified error handling in ADC implementation for MKV58x MCUs to detect and notify when an unsupported resolution is attempted to be set
+ Modified low-level GPIO implementation for STM32 so now PORT G pins on STM32L4Rxx MCUs can be set as inputs or outputs
+ Resistive mikromedias naming fixed according to the product names
  + `Mikromedia 3 for STM32 Resistive` changed to `Mikromedia 3 for STM32F4 Resistive`
  + `Mikromedia 3 for STM32 Resistive FPI` changed to `Mikromedia 3 for STM32F4 Resistive FPI`
  + `Mikromedia 4 for STM32 Resistive` changed to `Mikromedia 4 for STM32F4 Resistive`
  + `Mikromedia 5 for STM32 Resistive` changed to `Mikromedia 5 for STM32F4 Resistive`
+ Fixed values for display configuration so now it is configured as an 800x480 display istead of 480x800
  + `Mikromedia 5 for Kinetis Resistive`
  + `Mikromedia 5 for Kinetis Resistive FPI`
+ Fixed regex for including an appropriate dip28 header files for the boards that have this socket

### Improvements

+ Added helper function in [./tp.c](./api/tp/lib/src/tp/tp.c) for simplifying code operations on PIC architecture.
+ Added default CAN receive FIFO number and default filter bank number for all architectures that have CAN module supported
+ Added CAN_RX and CAN_TX pins for `EasyPIC v8`, `EasyPIC v8 for dsPIC30` and `EasyPIC v8 for PIC24/dsPIC33` boards
+ Added mapping for LCD pins in board.h, lcd.h now uses these pins instead of TFT
+ Changed the approach to adding new BSP
  + BSP files are now included as separate cmake files per board
+ Implemented an option to add all header files that are used in LVGL project into the LVGL library
+ Structure typecast for GPIO changed to match other architectures

### NEW HARDWARE

Support added for following hardware:

+ [EasyAVR v8](https://www.mikroe.com/easyavr-v8)
+ [Mikromedia 3 for Kinetis Resistive](https://www.mikroe.com/mikromedia-3-for-kinetis-resistive)
+ [Mikromedia 3 for STM32F2 Resistive](https://www.mikroe.com/mikromedia-3-for-stm32f2-resistive)

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
