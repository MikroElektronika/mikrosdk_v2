<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.12`

+ released: 2026-04-23

## Changes

- [`v2.17.12`](#v21712)
  - [Changes](#changes)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### Fixes

+ Fixed setting of interrupt priority for the M23 core
  + Manifested as UART receive interrupt issues on Renesas RA2 devices
  + Incorrect interrupt priority register index and bit-shift calculation corrected in `hal_ll_core_port_nvic_set_priority_irq`

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
