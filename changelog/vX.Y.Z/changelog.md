<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `vX.Y.Z`

+ released: YYYY-MM-DD

## Changes

- [`vX.Y.Z`](#vxyz)
  - [Changes](#changes)
    - [Fixes](#fixes)

### Fixes

+ Fixed IPS Display Click (first variant) using the wrong mikroBUS socket with the Graphic Library / Visual TFT
  + The build now reads the `MIKROBUS_POSITION_IPSDISPLAY` setting for this board, instead of `MIKROBUS_POSITION_IPSDISPLAY1`, which is never set
  + IPS Display 2 Click is not affected

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
