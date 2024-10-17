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

### Improvements

#### mikroSDK

+ Updated logger library error handling
  + `log_init` now returns an error (`-1`) if any of the configuration API calls used in it failed

#### CORE

+ Removed `READONLY` option from linker scripts for following MCUs (CLANG)
  + `stm32h7s3a8.ld`
  + `stm32h7s3i8.ld`
  + `stm32h7s3l8.ld`
  + `stm32h7s3r8.ld`
  + `stm32h7s3v8.ld`
  + `stm32h7s3z8.ld`
  + `stm32h7s7a8.ld`
  + `stm32h7s7i8.ld`
  + `stm32h7s7l8.ld`
  + `stm32h7s7z8.ld`
  + `stm32u083cc.ld`
  + `stm32u083hc.ld`
  + `stm32u083kc.ld`
  + `stm32u083mc.ld`
  + `stm32u083rc.ld`
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

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
