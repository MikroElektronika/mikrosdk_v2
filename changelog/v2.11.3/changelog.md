<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.11.3`

+ released: 2024-10-03

## Changes

+ [`v2.11.3`](#v2113)
  + [Changes](#changes)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk)
      + [CORE](#core)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk-1)
      + [CORE](#core-1)
    + [NEW HARDWARE](#new-hardware)

### Fixes

#### mikroSDK

+ Fixed touch panel implementation and TSC2003 library to recognize touch on TSC2003 RESISTIVE Displays while using LVGL projects
+ Fixed TP_ROTATION value to be "180" for all 4" CAPACITIVE Mikromedia Boards with PIC32MZ so touch position can be detected correctly

#### CORE

+ Fixed legacy setup projects previously not copying libraries to current project folder

### Improvements

#### mikroSDK

+ Updated [CMakeLists.txt](../../bsp/board/CMakeLists.txt) to include MCU Cards headers differently
  + Headers are now included with new path with MCU_NAME
+ Clock schemas added for PIC32 mikromedia boards

#### CORE

+ Added schema files for following HW:
  + Mikromedia 3 for PIC32MZ Capacitive
  + Mikromedia 3 for PIC32MZ Capacitive FPI with frame
  + Mikromedia 3 for PIC32MZ Capacitive FPI with bezel
  + Mikromedia 4 for PIC32MZ Capacitive
  + Mikromedia 4 for PIC32MZ Capacitive FPI with frame
  + Mikromedia 4 for PIC32MZ Capacitive FPI with bezel
  + Mikromedia 5 for PIC32MZ Capacitive
  + Mikromedia 5 for PIC32MZ Capacitive FPI with frame
  + Mikromedia 5 for PIC32MZ Capacitive FPI with bezel
  + Mikromedia 3 for PIC32MZ Resistive
  + Mikromedia 3 for PIC32MZ Resistive FPI with frame
  + Mikromedia 4 for PIC32MZ Resistive
  + Mikromedia 4 for PIC32MZ Resistive FPI with frame
  + Mikromedia 5 for PIC32MZ Resistive
  + Mikromedia 5 for PIC32MZ Resistive FPI with frame

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-10-04](./new_hw/2024-10-04.md)**
+ **[2024-10-07](./new_hw/2024-10-07.md)**
+ **[2024-10-08](./new_hw/2024-10-08.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
