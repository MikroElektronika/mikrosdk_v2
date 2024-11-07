<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.11.5`

+ released: 2024-11-01

## Changes

+ [`v2.11.5`](#v2115)
  + [Changes](#changes)
    + [mikroSDK](#mikrosdk)
    + [CORE](#core)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

**New STM32L4 MCUs supported!**

|        MCU        |        MCU       |        MCU        |
| :---------------: | :--------------: | :---------------: |
|    STM32L412C8    |   STM32L412CB    |    STM32L422CB    |
|    STM32L412K8    |   STM32L412KB    |    STM32L422KB    |
|    STM32L412R8    |   STM32L412RB    |    STM32L422RB    |
|    STM32L412T8    |   STM32L412TB    |    STM32L422TB    |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ OW (Full module support)
+ RTC (Full module support)
+ DMA (Full module support)

+ Third party modules supported
  + TinyUSB (An open source cross-platform USB stack for embedded system)
  + FatFs (Generic FAT Filesystem Module)

**Files added:**

+ `./mcu_name/mcu_definitions.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_definitions/STM32/mcu_name/mcu_definitions.h`
+ `./mcu_name/can_definitions.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_definitions/STM32/mcu_name/can_definitions.h`
+ `./mcu_name/dma_definitions.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_definitions/STM32/mcu_name/dma_definitions.h`
  + Added for all new MCUs in mikroSDK where mcu_name is actual chip full name with package, i.e. `STM32L412C8Tx` etc.
+ `./mcu_name/mcu_reg_addresses.h.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_reg_addresses/STM32/mcu_name/mcu_reg_addresses.h`
  + Added for all new MCUs in mikroSDK where mcu_name is actual chip full name, i.e. `STM32L412C8` etc.

#### CORE

+ Added USB Clock schemes for the newly supported STM32L4 MCUs:
  + STM32L412C8
  + STM32L412K8
  + STM32L412R8
  + STM32L412T8
  + STM32L412CB
  + STM32L412KB
  + STM32L412RB
  + STM32L412TB
  + STM32L422CB
  + STM32L422KB
  + STM32L422RB
  + STM32L422TB

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-11-01](./new_hw/2024-11-01.md)**
+ **[2024-11-04](./new_hw/2024-11-04.md)**
+ **[2024-11-05](./new_hw/2024-11-05.md)**
+ **[2024-11-06](./new_hw/2024-11-06.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
