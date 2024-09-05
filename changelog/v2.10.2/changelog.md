<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.10.2`

+ released: 2024-02-19

## Changes

- [`v2.10.2`](#v2102)
  - [Changes](#changes)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### Fixes

+ Fixed an issue on TIVA, where the DMA transfer would not be realized, if the source data buffer was stored in flash memory
  + Configured flash memory to allow the DMA access to the whole flash memory space
+ Added guards for **tim_regs_map** array in dsPIC low-level PWM implementation

### Improvements

+ Removed option to choose receive buffer and filter config for FIFO1 in low level implementation for PIC18 CAN implementation
  + Receive buffers are not selectable due to HW restrictions. Filter and mask configuration for FIFO1 is going to be handled once CAN over interrupts is supported
+ Removed **NC** definition for not connected pins from MCU card headers for 61 MCU cards
  + Now user will have compile time error if he tries using pin that is not routed to mikroBUS
+ Added **NC** macro as **HAL_PIN_NC** to 20 PIM MCU card headers that didn't have it
+ Removed display support for **MCU CARD 2 FOR KINETIS** with MK20 MCUs as it doesn't have TFT pins

### NEW HARDWARE

+ [STM32 Nucleo-64 development board with STM32F401RE MCU](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
+ [STM32 Nucleo-64 development board with STM32F030R8 MCU](https://www.st.com/en/evaluation-tools/nucleo-f030r8.html)
+ [STM32 Nucleo-64 development board with STM32L073RZ MCU](https://www.st.com/en/evaluation-tools/nucleo-l073rz.html)
+ [STM32 Nucleo-64 development board with STM32L476RG MCU](https://www.st.com/en/evaluation-tools/nucleo-l476rg.html)
+ [STM32 Nucleo-64 development board with STM32F070RB MCU](https://www.st.com/en/evaluation-tools/nucleo-f070rb.html)
+ [STM32 Nucleo-64 development board with STM32F091RC MCU](https://www.st.com/en/evaluation-tools/nucleo-f091rc.html)
+ [STM32 Nucleo-64 development board with STM32L433RC-P MCU](https://www.st.com/en/evaluation-tools/nucleo-l433rc-p.html)
+ [Click Shield for Nucleo-64](https://www.mikroe.com/click-shield-for-nucleo-64)
+ [STM32 Nucleo-144 development board with STM32L496ZG MCU](https://www.st.com/en/evaluation-tools/nucleo-l496zg.html)
+ [STM32 Nucleo-144 development board with STM32L4R5ZI MCU](https://www.st.com/en/evaluation-tools/nucleo-l4r5zi.html)
+ [STM32 Nucleo-144 development board with STM32F412ZG MCU](https://www.st.com/en/evaluation-tools/nucleo-f412zg.html)

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
