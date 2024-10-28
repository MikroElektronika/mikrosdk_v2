<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.11.4`

+ released: 2024-10-18

## Changes

+ [`v2.11.4`](#v2114)
  + [Changes](#changes)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk)
      + [CORE](#core)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk-1)
      + [CORE](#core-1)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

+ Updated logger library error handling
  + `log_init` now returns an error (`-1`) if any of the configuration API calls used in it failed

#### CORE

+ Removed `READONLY` option from linker scripts for following MCUs (CLANG)
  + `STM32H7S3A8`
  + `STM32H7S3I8`
  + `STM32H7S3L8`
  + `STM32H7S3R8`
  + `STM32H7S3V8`
  + `STM32H7S3Z8`
  + `STM32H7S7A8`
  + `STM32H7S7I8`
  + `STM32H7S7L8`
  + `STM32H7S7Z8`
  + `STM32U083CC`
  + `STM32U083HC`
  + `STM32U083KC`
  + `STM32U083MC`
  + `STM32U083RC`
+ Updated project templates to report better errors
  + Case when openning designer project without a setup with TFT
    + Now reports error in the output

### Fixes

#### mikroSDK

+ Fixed following MCU cards to have correct TFT pinout definitions
  + [mcu_card_3_for_pic32](../../bsp/board/include/mcu_cards/mcu_card_3_for_pic32/mcu_card.h)
  + [mcu_card_4_for_kinetis](../../bsp/board/include/mcu_cards/mcu_card_4_for_kinetis/mcu_card.h)
  + [mcu_card_for_pic32](../../bsp/board/include/mcu_cards/mcu_card_for_pic32/mcu_card.h)
  + [sibrain_for_dspic33ep512mu814](../../bsp/board/include/mcu_cards/sibrain_for_dspic33ep512mu814/mcu_card.h)
  + [sibrain_for_dspic33fj256gp710a](../../bsp/board/include/mcu_cards/sibrain_for_dspic33fj256gp710a/mcu_card.h)
  + [sibrain_for_pic24ep512gu814](../../bsp/board/include/mcu_cards/sibrain_for_pic24ep512gu814/mcu_card.h)
  + [sibrain_for_pic24hj256gp610](../../bsp/board/include/mcu_cards/sibrain_for_pic24hj256gp610/mcu_card.h)

#### CORE

+ Removed `CAN` schema file (clock configuration) for `PIC32MZ1024EFE144`
  + Added by mistake initially

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-10-18](./new_hw/2024-10-18.md)**
+ **[2024-10-21](./new_hw/2024-10-21.md)**
+ **[2024-10-22](./new_hw/2024-10-22.md)**
+ **[2024-10-23](./new_hw/2024-10-23.md)**
+ **[2024-10-24](./new_hw/2024-10-24.md)**
+ **[2024-10-25](./new_hw/2024-10-25.md)**
+ **[2024-10-28](./new_hw/2024-10-28.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
