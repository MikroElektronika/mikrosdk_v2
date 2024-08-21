<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---

# `v2.10.1`

+ released: 2024-02-02

## Changes

- [`v2.10.1`](#v2101)
  - [Changes](#changes)
    - [Fixes](#fixes)

### Fixes

+ Fixed shield.h for shield_curiosity_nano_base_for_click_boards
  + Resolved macros mismatch with board.h
+ Fixed baud rate settings in low level CAN implementation for NXP
  + Default baud rate changed from 500k to 125k
  + Added checking in hal_ll_can_bit_timing() API if configured baud rate is the same as requested
+ Fixed guards for CAN PPS pins on PIC32
  + Resolved the problem where certain pins were unreachable due to undefined macros in `ifdef`
+ Transmit FIFO initialization for CAN on PIC32 moved from `hal_ll_can_filter_init` to `hal_ll_can_module_init`
  + Since filters are not needed for transmitting this change makes using CAN easier and more intuitive
+ Fixed `mcu_card.h` for **MCU card 3 for PIC32**
  + `RIGHT_CN_PIN_043` and `RIGHT_CN_PIN_044` were defined as `NC` but they have actual pins routed

---

**[BACK TO MAIN FILE](../../CHANGELOG.md)**

---
