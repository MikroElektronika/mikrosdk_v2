<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.1`

+ released: 2025-11-20

## Changes

- [`v2.17.1`](#v2171)
  - [Changes](#changes)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk-1)
    - [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

- In the SPI implementation for Toshiba, replaced `DR`, `SR`, and `ERR` struct member access with offset-based macros
  - `HAL_LL_SPI_DR`, `HAL_LL_SPI_SR`, `HAL_LL_SPI_ERR` now handle register access
  - Reduces memory usage while preserving correct register mapping
- Implemented a timeout mechanism for UART polling write for all architectures
  - Ensures transmission terminates if peripheral becomes unresponsive
- Improved Renesas pins and register addresses definition approach
  - Added guards for all peripheral pins in `mcu_definitions.h` files
  - Defined all used register base addresses in `mcu_reg_addresses.h`

### Fixes

#### mikroSDK

- Changed return type of `hal_ll_gpio_get_port_number` from *uint32_t* to *uint8_t*
  - The function now returns *0xFF* instead of *-1* to signal an error
  - This change applies to the static implementations for Toshiba and Renesas
- Added missing pins for TOSHIBA TMPM4 MCU family
  - Updated `mcu_definitions.h` files with the pins that were missing
  - Added guards for all peripheral pins in `mcu_definitions.h` files
  - Updated `pin_maps` headers with the pins that were missing

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
