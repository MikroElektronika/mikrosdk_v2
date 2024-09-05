<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.5.1`

+ released: 2022-03-04

## Changes

- [`v2.5.1`](#v251)
  - [Changes](#changes)
    - [NEW HARDWARE](#new-hardware)
    - [DEVELOPMENT KIT PACKAGE](#development-kit-package)
    - [Improvements](#improvements)
    - [Fixes](#fixes)

### NEW HARDWARE

+ New board definitions added:
  + [Sparkfun MicroMod mikroBUS Carrier Board](https://www.sparkfun.com/products/18710)

**Config files added for adequate `NEW` boards.**

### DEVELOPMENT KIT PACKAGE

+ Updated mikroSDK development kit to conform to newly added hardware stated in last paragraph
  + Added new hardware definitions

### Improvements

*Support added for Enhanced PWM pins in PIC architecture.*

*185* MCU's in total affected by this change.

> You will now be able to utilize pins that are Enhanced PWM capable.
> Some PIC18 family devices have Enhanced Capture/Compare/PWM (ECCP) modules.
> These modules contain a 16-bit register, which can operate as a 16-bit Capture
> register, a 16-bit Compare register or a PWM Master/Slave Duty Cycle register.
> These Enhanced Capture/Compare/PWM modules are upward compatible with
> Standard Capture/Compare/PWM modules.
>> Note that all of this is done by the mikroSDK based on the pin selection.

List of MCU's affected:

|   MCU NAME   |   MCU NAME   |   MCU NAME   |   MCU NAME   |   MCU NAME   |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| PIC18F24J11  | PIC18F24J50  | PIC18F24K50  | PIC18F25J11  | PIC18F25J50  |
| PIC18F25K50  | PIC18F25K80  | PIC18F26J11  | PIC18F26J13  | PIC18F26J50  |
| PIC18F26J53  | PIC18F26K22  | PIC18F26K80  | PIC18F27J13  | PIC18F27J53  |
|  PIC18F4455  |  PIC18F4458  | PIC18F44J11  | PIC18F44J50  |  PIC18F4515  |
|  PIC18F4525  |  PIC18F4550  |  PIC18F4553  |  PIC18F4585  | PIC18F45J11  |
| PIC18F45J50  | PIC18F45K22  | PIC18F45K50  | PIC18F45K80  |  PIC18F4610  |
|  PIC18F4620  |  PIC18F4680  |  PIC18F4682  |  PIC18F4685  | PIC18F46J11  |
| PIC18F46J13  | PIC18F46J50  | PIC18F46J53  | PIC18F46K22  | PIC18F46K80  |
| PIC18F47J13  | PIC18F47J53  |  PIC18F6520  |  PIC18F6525  |  PIC18F6527  |
|  PIC18F6585  | PIC18F65J10  | PIC18F65J11  | PIC18F65J15  | PIC18F65J50  |
| PIC18F65J94  | PIC18F65K22  | PIC18F65K80  | PIC18F65K90  |  PIC18F6620  |
|  PIC18F6621  |  PIC18F6622  |  PIC18F6627  |  PIC18F6628  |  PIC18F6680  |
| PIC18F66J10  | PIC18F66J11  | PIC18F66J15  | PIC18F66J16  | PIC18F66J50  |
| PIC18F66J55  | PIC18F66J60  | PIC18F66J65  | PIC18F66J94  | PIC18F66K22  |
| PIC18F66K80  | PIC18F66K90  |  PIC18F6720  |  PIC18F6722  |  PIC18F6723  |
| PIC18F67J10  | PIC18F67J11  | PIC18F67J50  | PIC18F67J60  | PIC18F67J94  |
| PIC18F67K22  | PIC18F67K90  |  PIC18F8520  |  PIC18F8525  |  PIC18F8527  |
|  PIC18F8585  | PIC18F85J10  | PIC18F85J11  | PIC18F85J15  | PIC18F85J50  |
| PIC18F85J94  | PIC18F85K22  | PIC18F85K90  |  PIC18F8620  |  PIC18F8621  |
|  PIC18F8622  |  PIC18F8627  |  PIC18F8628  |  PIC18F8680  | PIC18F86J10  |
| PIC18F86J11  | PIC18F86J15  | PIC18F86J16  | PIC18F86J50  | PIC18F86J55  |
| PIC18F86J60  | PIC18F86J65  | PIC18F86J94  | PIC18F86K22  | PIC18F86K90  |
|  PIC18F8720  |  PIC18F8722  |  PIC18F8723  | PIC18F87J10  | PIC18F87J11  |
| PIC18F87J50  | PIC18F87J60  | PIC18F87J94  | PIC18F87K22  | PIC18F87K90  |
| PIC18F95J94  | PIC18F96J60  | PIC18F96J65  | PIC18F96J94  | PIC18F97J60  |
| PIC18F97J94  | PIC18LF24J11 | PIC18LF24J50 | PIC18LF24K50 | PIC18LF25J11 |
| PIC18LF25J50 | PIC18LF25K50 | PIC18LF25K80 | PIC18LF26J11 | PIC18LF26J13 |
| PIC18LF26J50 | PIC18LF26J53 | PIC18LF26K22 | PIC18LF26K80 | PIC18LF27J13 |
| PIC18LF27J53 | PIC18LF4455  | PIC18LF4458  | PIC18LF44J11 | PIC18LF44J50 |
| PIC18LF4515  | PIC18LF4525  | PIC18LF4550  | PIC18LF4553  | PIC18LF4585  |
| PIC18LF45J11 | PIC18LF45J50 | PIC18LF45K22 | PIC18LF45K50 | PIC18LF45K80 |
| PIC18LF4610  | PIC18LF4620  | PIC18LF4680  | PIC18LF4682  | PIC18LF4685  |
| PIC18LF46J11 | PIC18LF46J13 | PIC18LF46J50 | PIC18LF46J53 | PIC18LF46K22 |
| PIC18LF46K80 | PIC18LF47J13 | PIC18LF47J53 | PIC18LF6520  | PIC18LF6527  |
| PIC18LF65K80 | PIC18LF6622  | PIC18LF6627  | PIC18LF6628  | PIC18LF66K80 |
| PIC18LF6722  | PIC18LF6723  | PIC18LF8520  | PIC18LF8527  | PIC18LF8622  |
| PIC18LF8627  | PIC18LF8628  | PIC18LF8720  | PIC18LF8722  | PIC18LF8723  |

### Fixes

+ Fixed `mcu_card.h` W/R connection from `PA13` to `PA8`
  + Designer examples dind't work appropriately prior to this fix
  + Cards affected with this change
    + [MCU CARD 29 for STM32 STM32F205RB](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f205rb)
    + [MCU CARD 29 for STM32 STM32F215RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f215re)
    + [MCU CARD 29 for STM32 STM32F405RG](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f405rg)
    + [MCU CARD 29 for STM32 STM32F415RG](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f415rg)
    + [MCU CARD 29 for STM32 STM32F401RB](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f401rb)
    + [MCU CARD 29 for STM32 STM32F411RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f411re)
    + [MCU CARD 29 for STM32 STM32F446RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f446re)
    + [MCU CARD 29 for STM32 STM32F412RE](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f412re)
    + [MCU CARD 29 for STM32 STM32F413RH](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f413rh)
    + [MCU CARD 29 for STM32 STM32F423RH](https://www.mikroe.com/mcu-card-29-for-stm32-stm32f423rh)

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
