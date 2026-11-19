<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.21.1`

+ released: TBD

## Changes

- [`v2.21.1`](#v2211)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)

### RENESAS

**RX66T MCUs supported!**

**About the MCU:**

The RX66T is a 32-bit MCU family built around the RXv3 core, aimed at motor control and power conversion applications such as inverters, industrial drives and home appliances.

+ RXv3 CPU with FPU, up to 160MHz
+ Up to 1MB Flash, 128KB SRAM and 32KB Data Flash
+ 2.7V to 5.5V operating voltage
+ Available in 48-pin, 64-pin, 80-pin, 100-pin, 112-pin and 144-pin packages

| **R5F566TAADFF** | **R5F566TAEGFN** | **R5F566TEEDFM** | **R5F566TFFDFP** |
| :-----------: | :-----------: | :-----------: | :-----------: |
| **R5F566TAADFH** | **R5F566TAEGFP** | **R5F566TEEDFN** | **R5F566TFFGFP** |
| **R5F566TAADFM** | **R5F566TAFDFL** | **R5F566TEEDFP** | **R5F566TFGDFB** |
| **R5F566TAADFN** | **R5F566TAFDFP** | **R5F566TEEGFF** | **R5F566TFGDFP** |
| **R5F566TAADFP** | **R5F566TAFGFL** | **R5F566TEEGFH** | **R5F566TFGGFB** |
| **R5F566TAAGFF** | **R5F566TAFGFP** | **R5F566TEEGFM** | **R5F566TFGGFP** |
| **R5F566TAAGFH** | **R5F566TEADFF** | **R5F566TEEGFN** | **R5F566TKADFP** |
| **R5F566TAAGFM** | **R5F566TEADFH** | **R5F566TEEGFP** | **R5F566TKAGFP** |
| **R5F566TAAGFN** | **R5F566TEADFM** | **R5F566TEFDFL** | **R5F566TKBDFP** |
| **R5F566TAAGFP** | **R5F566TEADFN** | **R5F566TEFDFP** | **R5F566TKBGFP** |
| **R5F566TABDFL** | **R5F566TEADFP** | **R5F566TEFGFL** | **R5F566TKCDFB** |
| **R5F566TABDFP** | **R5F566TEAGFF** | **R5F566TEFGFP** | **R5F566TKCDFP** |
| **R5F566TABGFL** | **R5F566TEAGFH** | **R5F566TFADFP** | **R5F566TKCGFB** |
| **R5F566TABGFP** | **R5F566TEAGFM** | **R5F566TFAGFP** | **R5F566TKCGFP** |
| **R5F566TAEDFF** | **R5F566TEAGFN** | **R5F566TFBDFP** | **R5F566TKEDFP** |
| **R5F566TAEDFH** | **R5F566TEAGFP** | **R5F566TFBGFP** | **R5F566TKEGFP** |
| **R5F566TAEDFM** | **R5F566TEBDFL** | **R5F566TFCDFB** | **R5F566TKFDFP** |
| **R5F566TAEDFN** | **R5F566TEBDFP** | **R5F566TFCDFP** | **R5F566TKFGFP** |
| **R5F566TAEDFP** | **R5F566TEBGFL** | **R5F566TFCGFB** | **R5F566TKGDFB** |
| **R5F566TAEGFF** | **R5F566TEBGFP** | **R5F566TFCGFP** | **R5F566TKGDFP** |
| **R5F566TAEGFH** | **R5F566TEEDFF** | **R5F566TFEDFP** | **R5F566TKGGFB** |
| **R5F566TAEGFM** | **R5F566TEEDFH** | **R5F566TFEGFP** | **R5F566TKGGFP** |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

+ RX low level drivers now support multiple RX families
  + SCI interrupt group routing (vector, enable and status register) is now defined per MCU in `mcu_definitions.h`
  + GPIO port and pin names extended with ports `C`, `F`, `G`, `H` and `K`, all ports are now ordered alphabetically
  + PWM support extended to GPTW channels 8 and 9

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
