<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.10.0`

+ released: 2024-01-30

## Changes

- [`v2.10.0`](#v2100)
  - [Changes](#changes)
    - [New Features](#new-features)
    - [Tiva](#tiva)
    - [RISC-V SDK](#risc-v-sdk)
    - [Kinetis SDK](#kinetis-sdk)
    - [PIC32 SDK](#pic32-sdk)
    - [STM32 SDK](#stm32-sdk)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)
    - [Collaborators](#collaborators)

### New Features

**Support for DMA module!**

> Direct Memory Access (DMA) is a module that allows peripherals,
> to directly transfer data to or from memory without the constant involvement of the processor.
> This enhances the efficiency and speed of data handling in embedded applications,
> allowing for more real-time processing and reducing processor workload.

+ Files added
  + Common files
    + [drv_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_dma/CMakeLists.txt)
    + [drv_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_dma/drv_dma.c)
    + [hal_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_dma/CMakeLists.txt)
    + [hal_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_dma/hal_dma.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/dma/test_dma_m2m/main.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/dma/test_dma_m2m_p2p_2dmas/main.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/dma/test_dma_m2p_uart/main.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/dma/test_dma_p2p_uart_echo/main.c)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/dma/CMakeLists.txt)
  + STM32
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/dma/implementation_1/hal_ll_dma.c)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/dma/implementation_2/hal_ll_dma.c)
  + NXP
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/dma/implementation_1/hal_ll_dma.c)
  + TIVA
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/dma/implementation_1/hal_ll_dma.c)
  + Gigadevice
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/dma/implementation_1/hal_ll_dma.c)
  + PIC-8bit
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/dma/implementation_1/hal_ll_dma.c)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/dma/implementation_2/hal_ll_dma.c)
  + PIC-32bit
    + [hal_ll_dma.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/dma/hal_ll_dma.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/dma/CMakeLists.txt)
    + [hal_ll_dma.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/dma/implementation_1/hal_ll_dma.c)

**Support added for CAN protocol!**

> Controller Area Network (CAN) is a robust and widely used communication
> protocol in the field of automotive and industrial applications. CAN protocol
> is designed for high-speed, reliable communication between electronic
> control units in a network without a host computer. It enables real-time data
> exchange among different components of a system such as microcontrollers.

+ Files added
  + Common files
    + [drv_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_can.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_can/CMakeLists.txt)
    + [drv_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_can/drv_can.c)
    + [hal_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_can.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_can/CMakeLists.txt)
    + [hal_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_can/hal_can.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/can/can_loopback/main.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/can/can_rx/main.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/can/can_tx/main.c)
    + [can_test.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/can/inc/can_test.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/can/CMakeLists.txt)
  + STM32
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/can/hal_ll_can_pin_map/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/can/implementation_1/hal_ll_can.c)
  + NXP
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/can/hal_ll_can_pin_map/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/can/implementation_1/hal_ll_can.c)
  + TIVA
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/can/hal_ll_can_pin_map/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/can/implementation_1/hal_ll_can.c)
  + Gigadevice
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/can/hal_ll_can_pin_map/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/can/implementation_1/hal_ll_can.c)
  + PIC-8bit
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/can/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/can/implementation_1/hal_ll_can.c)
  + PIC-16bit
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/can/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/can/implementation_1/hal_ll_can.c)
  + PIC-32bit
    + [hal_ll_can.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/can/hal_ll_can.h)
    + [hal_ll_can_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/can/hal_ll_can_pin_map.h)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/can/CMakeLists.txt)
    + [hal_ll_can.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/can/implementation_1/hal_ll_can.c)

**Support added for RTC!**

+ RTC implementation
  + Supported architectures
    + `STM32`
    + `NXP`
    + `TIVA`
    + `GD32`
    + `PIC32`
+ Included API's:
  + `rtc_init` Initialize the RTC counter.
  + `rtc_start` Continue the RTC module count from the stored value in the count register.
  + `rtc_stop` Stop the RTC module count from the stored value in the count register.
  + `rtc_restart` Reset the RTC counter to the default values for the time and date registers.
  + `rtc_set_time` Configure the date and time of the RTC.
  + `rtc_get_time` Get RTC counter register value.
  + `rtc_system_reset` Resets the core and all on-chip peripherals except the Debug interface.

  + Files added:
    + [drv_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_rtc.h)
    + [drv_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_rtc/drv_rtc.c)
    + [hal_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_target.h)
    + [hal_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_rtc/hal_rtc.c)
    + [./nxp/include/hal_ll_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/rtc/hal_ll_rtc.h)
    + [./nxp/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/rtc/implementation_1/hal_ll_rtc.c)
    + [./tiva/include/hal_ll_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/rtc/hal_ll_rtc.h)
    + [./tiva/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/rtc/implementation_1/hal_ll_rtc.c)
    + [./tiva/src/rtc/implementation_2/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/rtc/implementation_2/hal_ll_rtc.c)
    + [./stm32/include/hal_ll_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/rtc/hal_ll_rtc.h)
    + [./stm32/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_1/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_2/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_2/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_3/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_3/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_4/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_4/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_5/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_5/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_6/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_6/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_7/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_7/hal_ll_rtc.c)
    + [./stm32/src/rtc/implementation_8/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_8/hal_ll_rtc.c)
    + [./pic32/include/hal_ll_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/rtc/hal_ll_rtc.h)
    + [./pic32/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/rtc/implementation_1/hal_ll_rtc.c)
    + [./gigadevice/include/hal_ll_rtc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/rtc/hal_ll_rtc.h)
    + [./gigadevice/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/rtc/implementation_1/hal_ll_rtc.c)
    + [main.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/tests/rtc/main.c)

### <font color=red>Tiva</font>

**Module supported for:**

1. **RTC**

|      MCU       |      MCU       |      MCU       |
| :------------: | :------------: | :------------: |
| TM4C1231C3PM   | TM4C1231D5PM   | TM4C1231D5PZ   |
| TM4C1231E6PM   | TM4C1231E6PZ   | TM4C1231H6PGE  |
| TM4C1231H6PM   | TM4C1231H6PZ   | TM4C1233C3PM   |
| TM4C1233D5PM   | TM4C1233D5PZ   | TM4C1233E6PM   |
| TM4C1233E6PZ   | TM4C1233H6PGE  | TM4C1233H6PM   |
| TM4C1233H6PZ   | TM4C1237D5PM   | TM4C1237D5PZ   |
| TM4C1237E6PM   | TM4C1237E6PZ   | TM4C1237H6PGE  |
| TM4C1237H6PM   | TM4C1237H6PZ   | TM4C123BH6PGE  |
| TM4C123BE6PM   | TM4C123BE6PZ   | TM4C123BH6ZRB  |
| TM4C123BH6PM   | TM4C123BH6PZ   | TM4C123GH6PGE  |
| TM4C123GE6PM   | TM4C123GE6PZ   | TM4C123GH6ZRB  |
| TM4C123GH6PM   | TM4C123GH6PZ   | TM4C1290NCZAD  |
| TM4C123GH6ZXR  | TM4C1290NCPDT  | TM4C1294KCPDT  |
| TM4C1292NCPDT  | TM4C1292NCZAD  | TM4C1297NCZAD  |
| TM4C1294NCPDT  | TM4C1294NCZAD  | TM4C129CNCPDT  |
| TM4C1299KCZAD  | TM4C1299NCZAD  | TM4C129DNCZAD  |
| TM4C129CNCZAD  | TM4C129DNCPDT  | TM4C129ENCZAD  |
| TM4C129EKCPDT  | TM4C129ENCPDT  | TM4C129XNCZAD  |
| TM4C129LNCZAD  | TM4C129XKCZAD  |

---

### <font color=red>RISC-V SDK</font>

**Module supported for:**

1. **RTC**

|      MCU      |      MCU      |
| :-----------: | :-----------: |
| GD32VF103C4T6 | GD32VF103C6T6 |
| GD32VF103C8T6 | GD32VF103CBT6 |
| GD32VF103R4T6 | GD32VF103R6T6 |
| GD32VF103R8T6 | GD32VF103RBT6 |
| GD32VF103T4U6 | GD32VF103T6U6 |
| GD32VF103T8U6 | GD32VF103TBU6 |
| GD32VF103V8T6 | GD32VF103VBT6 |

---

### <font color=red>Kinetis SDK</font>

**Module supported for:**

1. **RTC**

|        MCU        |        MCU        |        MCU        |        MCU        |        MCU        |
| :---------------: | :---------------: | :---------------: | :---------------: | :---------------: |
|   MK20DN128VFM5   |   MK20DN64VFM5    |   MK20DX32VFM5    |   MK20DX64VFM5    |   MK20DX128VFM5   |
|   MK20DN128VFT5   |   MK20DN32VLF5    |   MK20DX32VLF5    |   MK20DN64VLF5    |   MK20DX64VLF5    |
|   MK20DN128VLF5   |   MK20DX128VLF5   |   MK20DN32VFT5    |   MK20DX32VFT5    |   MK20DN64VFT5    |
|   MK20DX64VFT5    |   MK20DX128VFT5   |   MK20DN128VLH5   |   MK20DN32VLH5    |   MK20DX32VLH5    |
|   MK20DN64VLH5    |   MK20DX64VLH5    |   MK20DX128VLH5   |   MK20DN32VMP5    |   MK20DX32VMP5    |
|   MK20DN64VMP5    |   MK20DX64VMP5    |   MK20DN128VMP5   |   MK20DN32VFM5    |   MK22FN128CAH12  |
|   MK22FN128VDC10  |   MK22FN128VLL10  |   MK22FN128VMP10  |   MK22FN128VLH10  |   MK22FN1M0AVLH12 |
|   MK22FX512AVLH12 |   MK22FN1M0AVLK12 |   MK22FX512AVLK12 |   MK22FN1M0AVLL12 |   MK22FX512AVLL12 |
|   MK22FN1M0AVLQ12 |   MK22FX512AVLQ12 |   MK22FX512AVMD12 |   MK22FN1M0AVMD12 |   MK22FN1M0AVMC12 |
|   MK22FX512AVMC12 |   MK22FN1M0VLH12  |   MK22FX512VLH12  |   MK22FN1M0VLK12  |   MK22FX512VLK12  |
|   MK22FN1M0VLL12  |   MK22FX512VLL12  |   MK22FN1M0VLQ12  |   MK22FX512VLQ12  |   MK22FX512VMD12  |
|   MK22FN1M0VMD12  |   MK22FN1M0VMC12  |   MK22FX512VMC12  |   MK22FN256CAH12  |   MK22FN256VDC12  |
|   MK22FN256VLL12  |   MK22FN256VMP12  |   MK22FN256VLH12  |   MK22FN512CAP12  |   MK22FN512VDC12  |
|   MK22FN512VLL12  |   MK22FN512VLH12  |   MK22FN512VMP12  |   MK22FN512VFX12  |   MK51DN256CLQ10  |
|   MK51DN256CMD10  |   MK51DN512CLQ10  |   MK51DN512CMD10  |   MK51DN512CLL10  |   MK51DX256CLL10  |
|   MK51DN512CMC10  |   MK51DX256CMC10  |   MK51DX256CLK10  |   MK53DN512CLQ10  |   MK53DN512CMD10  |
|   MK53DX256CLQ10  |   MK53DX256CMD10  |   MK60DN256VLL10  |   MK60DX256VLL10  |   MK60DN512VLL10  |
|   MK60DN256VLQ10  |   MK60DX256VLQ10  |   MK60DN512VLQ10  |   MK60DN256VMD10  |   MK60DX256VMD10  |
|   MK60DN512VMD10  |   MK60DN256VMC10  |   MK60DX256VMC10  |   MK60DN512VMC10  |   MK64FN1M0CAJ12  |
|   MK64FN1M0VDC12  |   MK64FN1M0VLL12  |   MK64FN1M0VLQ12  |   MK64FN1M0VMD12  |   MK64FX512VDC12  |
|   MK64FX512VLL12  |   MK64FX512VLQ12  |   MK64FX512VMD12  |   MK65FN2M0CAC18  |   MK65FX1M0CAC18  |
|   MK65FN2M0VMI18  |   MK65FX1M0VMI18  |   MK66FN2M0VLQ18  |   MK66FN2M0VMD18  |   MK66FX1M0VMD18  |
|   MK66FX1M0VLQ18  |   MK80FN256VDC15  |   MK80FN256VLL15  |   MK80FN256VLQ15  |   MK82FN256VDC15  |
|   MK82FN256VLL15  |   MK82FN256VLQ15  |

---

### <font color=red>PIC32 SDK</font>

**Module supported for:**

1. **RTC**

|        MCU        |        MCU         |        MCU         |        MCU         |        MCU         |
| :---------------: | :----------------: | :----------------: | :----------------: | :----------------: |
| PIC32MX110F016B   |  PIC32MX110F016C   |  PIC32MX110F016D   |  PIC32MX120F032B   |  PIC32MX120F032C   |
| PIC32MX120F032D   |  PIC32MX120F064H   |  PIC32MX130F064B   |  PIC32MX130F064C   |  PIC32MX130F064D   |
| PIC32MX130F128H   |  PIC32MX130F128L   |  PIC32MX130F256B   |  PIC32MX130F256D   |  PIC32MX150F128B   |
| PIC32MX150F128C   |  PIC32MX150F128D   |  PIC32MX150F256H   |  PIC32MX150F256L   |  PIC32MX170F256B   |
| PIC32MX170F256D   |  PIC32MX170F512H   |  PIC32MX170F512L   |  PIC32MX210F016B   |  PIC32MX210F016C   |
| PIC32MX210F016D   |  PIC32MX220F032B   |  PIC32MX220F032C   |  PIC32MX220F032D   |  PIC32MX230F064B   |
| PIC32MX230F064C   |  PIC32MX230F064D   |  PIC32MX230F128H   |  PIC32MX230F128L   |  PIC32MX230F256B   |
| PIC32MX230F256D   |  PIC32MX250F128B   |  PIC32MX250F128C   |  PIC32MX250F128D   |  PIC32MX250F256H   |
| PIC32MX250F256L   |  PIC32MX270F256B   |  PIC32MX270F256D   |  PIC32MX270F256DB  |  PIC32MX270F512H   |
| PIC32MX270F512L   |  PIC32MX320F032H   |  PIC32MX320F064H   |  PIC32MX320F128H   |  PIC32MX320F128L   |
| PIC32MX330F064H   |  PIC32MX330F064L   |  PIC32MX340F128H   |  PIC32MX340F128L   |  PIC32MX340F256H   |
| PIC32MX340F512H   |  PIC32MX350F128H   |  PIC32MX350F128L   |  PIC32MX350F256H   |  PIC32MX350F256L   |
| PIC32MX360F256L   |  PIC32MX360F512L   |  PIC32MX370F512H   |  PIC32MX370F512L   |  PIC32MX420F032H   |
| PIC32MX430F064H   |  PIC32MX430F064L   |  PIC32MX440F128H   |  PIC32MX440F128L   |  PIC32MX440F256H   |
| PIC32MX440F512H   |  PIC32MX450F128H   |  PIC32MX450F128L   |  PIC32MX450F256H   |  PIC32MX450F256HB  |
| PIC32MX450F256L   |  PIC32MX460F256L   |  PIC32MX460F512L   |  PIC32MX470F512H   |  PIC32MX470F512L   |
| PIC32MX470F512LB  |  PIC32MX530F128H   |  PIC32MX530F128L   |  PIC32MX534F064H   |  PIC32MX534F064L   |
| PIC32MX550F256H   |  PIC32MX550F256L   |  PIC32MX564F064H   |  PIC32MX564F064L   |  PIC32MX564F128H   |
| PIC32MX564F128L   |  PIC32MX570F512H   |  PIC32MX570F512L   |  PIC32MX575F256H   |  PIC32MX575F256L   |
| PIC32MX575F512H   |  PIC32MX575F512L   |  PIC32MX664F064H   |  PIC32MX664F064L   |  PIC32MX664F128H   |
| PIC32MX664F128L   |  PIC32MX675F256H   |  PIC32MX675F256L   |  PIC32MX675F512H   |  PIC32MX675F512L   |
| PIC32MX695F512H   |  PIC32MX695F512L   |  PIC32MX764F128H   |  PIC32MX764F128L   |  PIC32MX775F256H   |
| PIC32MX775F256L   |  PIC32MX775F512H   |  PIC32MX775F512L   |  PIC32MX795F512H   |  PIC32MX795F512L   |
| PIC32MZ0512EFE064 |  PIC32MZ0512EFE100 |  PIC32MZ0512EFE124 |  PIC32MZ0512EFE144 |  PIC32MZ0512EFF064 |
| PIC32MZ0512EFF100 |  PIC32MZ0512EFF124 |  PIC32MZ0512EFF144 |  PIC32MZ0512EFK064 |  PIC32MZ0512EFK100 |
| PIC32MZ0512EFK124 |  PIC32MZ0512EFK144 |  PIC32MZ1024ECG064 |  PIC32MZ1024ECG100 |  PIC32MZ1024ECG124 |
| PIC32MZ1024ECG144 |  PIC32MZ1024ECH064 |  PIC32MZ1024ECH100 |  PIC32MZ1024ECH124 |  PIC32MZ1024ECH144 |
| PIC32MZ1024ECM064 |  PIC32MZ1024ECM100 |  PIC32MZ1024ECM124 |  PIC32MZ1024ECM144 |  PIC32MZ1024EFE064 |
| PIC32MZ1024EFE100 |  PIC32MZ1024EFE124 |  PIC32MZ1024EFE144 |  PIC32MZ1024EFF064 |  PIC32MZ1024EFF100 |
| PIC32MZ1024EFF124 |  PIC32MZ1024EFF144 |  PIC32MZ1024EFG064 |  PIC32MZ1024EFG100 |  PIC32MZ1024EFG124 |
| PIC32MZ1024EFG144 |  PIC32MZ1024EFH064 |  PIC32MZ1024EFH100 |  PIC32MZ1024EFH124 |  PIC32MZ1024EFH144 |
| PIC32MZ1024EFK064 |  PIC32MZ1024EFK100 |  PIC32MZ1024EFK124 |  PIC32MZ1024EFK144 |  PIC32MZ1024EFM064 |
| PIC32MZ1024EFM100 |  PIC32MZ1024EFM124 |  PIC32MZ1024EFM144 |  PIC32MZ2048ECG064 |  PIC32MZ2048ECG100 |
| PIC32MZ2048ECG124 |  PIC32MZ2048ECG144 |  PIC32MZ2048ECH064 |  PIC32MZ2048ECH100 |  PIC32MZ2048ECH124 |
| PIC32MZ2048ECH144 |  PIC32MZ2048ECM064 |  PIC32MZ2048ECM100 |  PIC32MZ2048ECM124 |  PIC32MZ2048ECM144 |
| PIC32MZ2048EFG064 |  PIC32MZ2048EFG100 |  PIC32MZ2048EFG124 |  PIC32MZ2048EFG144 |  PIC32MZ2048EFH064 |
| PIC32MZ2048EFH100 |  PIC32MZ2048EFH124 |  PIC32MZ2048EFH144 |  PIC32MZ2048EFM064 |  PIC32MZ2048EFM100 |
| PIC32MZ2048EFM124 |  PIC32MZ2048EFM144 |

---

### <font color=red>STM32 SDK</font>

**Module supported for:**

1. **RTC**

|        MCU        |        MCU        |        MCU        |        MCU        |        MCU        |
| :---------------: | :---------------: | :---------------: | :---------------: | :---------------: |
|    STM32L4S9ZI    |    STM32L4S9VI    |    STM32L4S9AI    |    STM32L4S7ZI    |    STM32L4S7VI    |
|    STM32L4S7AI    |    STM32L4S5ZI    |    STM32L4S5VI    |    STM32L4S5QI    |    STM32L4S5AI    |
|    STM32L4R9ZI    |    STM32L4R9ZG    |    STM32L4R9VI    |    STM32L4R9VG    |    STM32L4R9AI    |
|    STM32L4R9AG    |    STM32L4R7ZI    |    STM32L4R7VI    |    STM32L4R7AI    |    STM32L4R5ZI    |
|    STM32L4R5ZG    |    STM32L4R5VI    |    STM32L4R5VG    |    STM32L4R5QI    |    STM32L4R5QG    |
|    STM32L4R5AI    |    STM32L4R5AG    |    STM32L4A6ZG    |    STM32L4A6VG    |    STM32L4A6RG    |
|    STM32L4A6QG    |    STM32L4A6AG    |    STM32L496ZG    |    STM32L496ZE    |    STM32L496VG    |
|    STM32L496VE    |    STM32L496RG    |    STM32L496RE    |    STM32L496QG    |    STM32L496QE    |
|    STM32L496AG    |    STM32L496AE    |    STM32L486ZG    |    STM32L486VG    |    STM32L486RG    |
|    STM32L486QG    |    STM32L486JG    |    STM32L476ZG    |    STM32L476ZE    |    STM32L476VG    |
|    STM32L476VE    |    STM32L476VC    |    STM32L476RG    |    STM32L476RE    |    STM32L476RC    |
|    STM32L476QG    |    STM32L476QE    |    STM32L476MG    |    STM32L476ME    |    STM32L476JG    |
|    STM32L476JE    |    STM32L475VG    |    STM32L475VE    |    STM32L475VC    |    STM32L475RG    |
|    STM32L475RE    |    STM32L475RC    |    STM32L471ZG    |    STM32L471ZE    |    STM32L471VG    |
|    STM32L471VE    |    STM32L471RG    |    STM32L471RE    |    STM32L471QG    |    STM32L471QE    |
|    STM32L462VE    |    STM32L462RE    |    STM32L462CE    |    STM32L452VE    |    STM32L452VC    |
|    STM32L452RE    |    STM32L452RC    |    STM32L452CE    |    STM32L452CC    |    STM32L451VE    |
|    STM32L451VC    |    STM32L451RE    |    STM32L451RC    |    STM32L451CE    |    STM32L451CC    |
|    STM32L443VC    |    STM32L443RC    |    STM32L443CC    |    STM32L442KC    |    STM32L433VC    |
|    STM32L433RC    |    STM32L433RB    |    STM32L433CC    |    STM32L433CB    |    STM32L432KC    |
|    STM32L432KB    |    STM32L431VC    |    STM32L431RC    |    STM32L431RB    |    STM32L431KC    |
|    STM32L431KB    |    STM32L431CC    |    STM32L431CB    |    STM32L162ZE    |    STM32L162ZD    |
|    STM32L162VE    |    STM32L162VD    |    STM32L162VC_A  |    STM32L162VC    |    STM32L162RE    |
|    STM32L162RD    |    STM32L162RC_A  |    STM32L162RC    |    STM32L162QD    |    STM32L152ZE    |
|    STM32L152ZD    |    STM32L152ZC    |    STM32L152VE    |    STM32L152VD_X  |    STM32L152VD    |
|    STM32L152VC_A  |    STM32L152VC    |    STM32L152VB_A  |    STM32L152VB    |    STM32L152V8_A  |
|    STM32L152V8    |    STM32L152RE    |    STM32L152RD    |    STM32L152RC_A  |    STM32L152RC    |
|    STM32L152RB_A  |    STM32L152RB    |    STM32L152R8_A  |    STM32L152R8    |    STM32L152R6_A  |
|    STM32L152R6    |    STM32L152QE    |    STM32L152QD    |    STM32L152QC    |    STM32L152CC    |
|    STM32L152CB_A  |    STM32L152CB    |    STM32L152C8_A  |    STM32L152C8    |    STM32L152C6_A  |
|    STM32L152C6    |    STM32L151ZE    |    STM32L151ZD    |    STM32L151ZC    |    STM32L151VE    |
|    STM32L151VD_X  |    STM32L151VD    |    STM32L151VC_A  |    STM32L151VC    |    STM32L151VB_A  |
|    STM32L151VB    |    STM32L151V8_A  |    STM32L151V8    |    STM32L151UC    |    STM32L151RE    |
|    STM32L151RD    |    STM32L151RC_A  |    STM32L151RC    |    STM32L151RB_A  |    STM32L151RB    |
|    STM32L151R8_A  |    STM32L151R8    |    STM32L151R6_A  |    STM32L151R6    |    STM32L151QE    |
|    STM32L151QD    |    STM32L151QC    |    STM32L151CC    |    STM32L151CB_A  |    STM32L151CB    |
|    STM32L151C8_A  |    STM32L151C8    |    STM32L151C6_A  |    STM32L151C6    |    STM32L100RC    |
|    STM32L100RB_A  |    STM32L100RB    |    STM32L100R8_A  |    STM32L100R8    |    STM32L100C6_A  |
|    STM32L100C6    |    STM32L083VZ    |    STM32L083VB    |    STM32L083V8    |    STM32L083RZ    |
|    STM32L083RB    |    STM32L083CZ    |    STM32L083CB    |    STM32L082KZ    |    STM32L082CZ    |
|    STM32L081KZ    |    STM32L081CZ    |    STM32L073VZ    |    STM32L073VB    |    STM32L073V8    |
|    STM32L073RZ    |    STM32L073RB    |    STM32L073CZ    |    STM32L073CB    |    STM32L072VZ    |
|    STM32L072VB    |    STM32L072V8    |    STM32L072RZ    |    STM32L072RB    |    STM32L072KZ    |
|    STM32L072KB    |    STM32L072CZ    |    STM32L072CB    |    STM32L071VZ    |    STM32L071VB    |
|    STM32L071V8    |    STM32L071RZ    |    STM32L071RB    |    STM32L071KZ    |    STM32L071KB    |
|    STM32L071K8    |    STM32L071CZ    |    STM32L071CB    |    STM32L071C8    |    STM32L063R8    |
|    STM32L063C8    |    STM32L062K8    |    STM32L053R8    |    STM32L053R6    |    STM32L053C8    |
|    STM32L053C6    |    STM32L052T8    |    STM32L052T6    |    STM32L052R8    |    STM32L052R6    |
|    STM32L052K8    |    STM32L052K6    |    STM32L052C8    |    STM32L052C6    |    STM32L051T8    |
|    STM32L051T6    |    STM32L051R8    |    STM32L051R6    |    STM32L051K8    |    STM32L051K6    |
|    STM32L051C8    |    STM32L051C6    |    STM32L041K6    |    STM32L041G6    |    STM32L041F6    |
|    STM32L041E6    |    STM32L041C6    |    STM32L031K6    |    STM32L031K4    |    STM32L031G6    |
|    STM32L031G4    |    STM32L031F6    |    STM32L031F4    |    STM32L031E6    |    STM32L031E4    |
|    STM32L031C6    |    STM32L031C4    |    STM32L021K4    |    STM32L021G4    |    STM32L021F4    |
|    STM32L021D4    |    STM32L011K4    |    STM32L011K3    |    STM32L011G4    |    STM32L011G3    |
|    STM32L011F4    |    STM32L011F3    |    STM32L011E4    |    STM32L011E3    |    STM32L011D4    |
|    STM32L011D3    |    STM32H753ZI    |    STM32H753XI    |    STM32H753VI    |    STM32H753II    |
|    STM32H753BI    |    STM32H753AI    |    STM32H750XB    |    STM32H750VB    |    STM32H750IB    |
|    STM32H743ZI    |    STM32H743XI    |    STM32H743VI    |    STM32H743II    |    STM32H743BI    |
|    STM32H743AI    |    STM32G081RB    |    STM32G081KB    |    STM32G081GB    |    STM32G081EB    |
|    STM32G081CB    |    STM32G071RB    |    STM32G071R8    |    STM32G071R6    |    STM32G071KB    |
|    STM32G071K8    |    STM32G071K6    |    STM32G071GB    |    STM32G071G8    |    STM32G071G6    |
|    STM32G071EB    |    STM32G071CB    |    STM32G071C8    |    STM32G071C6    |    STM32G070RB    |
|    STM32G070KB    |    STM32G070CB    |    STM32G041Y8    |    STM32G041K8    |    STM32G041K6    |
|    STM32G041J6    |    STM32G041G8    |    STM32G041G6    |    STM32G041F8    |    STM32G041F6    |
|    STM32G041C8    |    STM32G041C6    |    STM32G031Y8    |    STM32G031K8    |    STM32G031K6    |
|    STM32G031K4    |    STM32G031J6    |    STM32G031J4    |    STM32G031G8    |    STM32G031G6    |
|    STM32G031G4    |    STM32G031F8    |    STM32G031F6    |    STM32G031F4    |    STM32G031C8    |
|    STM32G031C6    |    STM32G031C4    |    STM32G030K8    |    STM32G030K6    |    STM32G030J6    |
|    STM32G030F6    |    STM32G030C8    |    STM32G030C6    |    STM32F779NI    |    STM32F779II    |
|    STM32F779BI    |    STM32F779AI    |    STM32F777ZI    |    STM32F777VI    |    STM32F777NI    |
|    STM32F777II    |    STM32F777BI    |    STM32F769NI    |    STM32F769NG    |    STM32F769II    |
|    STM32F769IG    |    STM32F769BI    |    STM32F769BG    |    STM32F769AI    |    STM32F767ZI    |
|    STM32F767ZG    |    STM32F767VI    |    STM32F767VG    |    STM32F767NI    |    STM32F767NG    |
|    STM32F767II    |    STM32F767IG    |    STM32F767BI    |    STM32F767BG    |    STM32F765ZI    |
|    STM32F765ZG    |    STM32F765VI    |    STM32F765VG    |    STM32F765NI    |    STM32F765NG    |
|    STM32F765II    |    STM32F765IG    |    STM32F765BI    |    STM32F765BG    |    STM32F756ZG    |
|    STM32F756VG    |    STM32F756NG    |    STM32F756IG    |    STM32F756BG    |    STM32F746ZG    |
|    STM32F746ZE    |    STM32F746VG    |    STM32F746VE    |    STM32F746NG    |    STM32F746NE    |
|    STM32F746IG    |    STM32F746IE    |    STM32F746BG    |    STM32F746BE    |    STM32F745ZG    |
|    STM32F745ZE    |    STM32F745VG    |    STM32F745VE    |    STM32F745IG    |    STM32F745IE    |
|    STM32F733ZE    |    STM32F733VE    |    STM32F733IE    |    STM32F732ZE    |    STM32F732VE    |
|    STM32F732RE    |    STM32F732IE    |    STM32F723ZE    |    STM32F723ZC    |    STM32F723VE    |
|    STM32F723IE    |    STM32F723IC    |    STM32F722ZE    |    STM32F722ZC    |    STM32F722VE    |
|    STM32F722VC    |    STM32F722RE    |    STM32F722RC    |    STM32F722IE    |    STM32F722IC    |
|    STM32F479ZI    |    STM32F479ZG    |    STM32F479VI    |    STM32F479VG    |    STM32F479NI    |
|    STM32F479NG    |    STM32F479II    |    STM32F479IG    |    STM32F479BI    |    STM32F479BG    |
|    STM32F479AI    |    STM32F479AG    |    STM32F469ZI    |    STM32F469ZG    |    STM32F469ZE    |
|    STM32F469VI    |    STM32F469VG    |    STM32F469VE    |    STM32F469NI    |    STM32F469NG    |
|    STM32F469NE    |    STM32F469II    |    STM32F469IG    |    STM32F469IE    |    STM32F469BI    |
|    STM32F469BG    |    STM32F469BE    |    STM32F469AI    |    STM32F469AG    |    STM32F469AE    |
|    STM32F446ZE    |    STM32F446ZC    |    STM32F446VE    |    STM32F446VC    |    STM32F446RE    |
|    STM32F446RC    |    STM32F446ME    |    STM32F446MC    |    STM32F439ZI    |    STM32F439ZG    |
|    STM32F439VI    |    STM32F439VG    |    STM32F439NI    |    STM32F439NG    |    STM32F439II    |
|    STM32F439IG    |    STM32F439BI    |    STM32F439BG    |    STM32F439AI    |    STM32F437ZI    |
|    STM32F437ZG    |    STM32F437VI    |    STM32F437VG    |    STM32F437II    |    STM32F437IG    |
|    STM32F437AI    |    STM32F429ZI    |    STM32F429ZG    |    STM32F429ZE    |    STM32F429VI    |
|    STM32F429VG    |    STM32F429VE    |    STM32F429NI    |    STM32F429NG    |    STM32F429NE    |
|    STM32F429II    |    STM32F429IG    |    STM32F429IE    |    STM32F429BI    |    STM32F429BG    |
|    STM32F429BE    |    STM32F429AI    |    STM32F429AG    |    STM32F427ZI    |    STM32F427ZG    |
|    STM32F427VI    |    STM32F427VG    |    STM32F427II    |    STM32F427IG    |    STM32F427AI    |
|    STM32F427AG    |    STM32F423ZH    |    STM32F423VH    |    STM32F423RH    |    STM32F423MH    |
|    STM32F423CH    |    STM32F417ZG    |    STM32F417ZE    |    STM32F417VG    |    STM32F417VE    |
|    STM32F417IG    |    STM32F417IE    |    STM32F415ZG    |    STM32F415VG    |    STM32F415RG    |
|    STM32F415OG    |    STM32F413ZH    |    STM32F413ZG    |    STM32F413VH    |    STM32F413VG    |
|    STM32F413RH    |    STM32F413RG    |    STM32F413MH    |    STM32F413MG    |    STM32F413CH    |
|    STM32F413CG    |    STM32F412ZG    |    STM32F412ZE    |    STM32F412VG    |    STM32F412VE    |
|    STM32F412RG    |    STM32F412RE    |    STM32F412CG    |    STM32F412CE    |    STM32F411VE    |
|    STM32F411VC    |    STM32F411RE    |    STM32F411RC    |    STM32F411CE    |    STM32F411CC    |
|    STM32F410TB    |    STM32F410T8    |    STM32F410RB    |    STM32F410R8    |    STM32F410CB    |
|    STM32F410C8    |    STM32F407ZG    |    STM32F407ZE    |    STM32F407VG    |    STM32F407VE    |
|    STM32F407IG    |    STM32F407IE    |    STM32F405ZG    |    STM32F405VG    |    STM32F405RG    |
|    STM32F405OG    |    STM32F405OE    |    STM32F401VE    |    STM32F401VD    |    STM32F401VC    |
|    STM32F401VB    |    STM32F401RE    |    STM32F401RD    |    STM32F401RC    |    STM32F401RB    |
|    STM32F401CE    |    STM32F401CD    |    STM32F401CC    |    STM32F401CB    |    STM32F398VE    |
|    STM32F378VC    |    STM32F378RC    |    STM32F378CC    |    STM32F373VC    |    STM32F373VB    |
|    STM32F373V8    |    STM32F373RC    |    STM32F373RB    |    STM32F373R8    |    STM32F373CC    |
|    STM32F373CB    |    STM32F373C8    |    STM32F358VC    |    STM32F358RC    |    STM32F358CC    |
|    STM32F334R8    |    STM32F334R6    |    STM32F334K8    |    STM32F334K6    |    STM32F334K4    |
|    STM32F334C8    |    STM32F334C6    |    STM32F334C4    |    STM32F328C8    |    STM32F318K8    |
|    STM32F318C8    |    STM32F303ZE    |    STM32F303ZD    |    STM32F303VE    |    STM32F303VD    |
|    STM32F303VC    |    STM32F303VB    |    STM32F303RE    |    STM32F303RD    |    STM32F303RC    |
|    STM32F303RB    |    STM32F303R8    |    STM32F303R6    |    STM32F303K8    |    STM32F303K6    |
|    STM32F303CC    |    STM32F303CB    |    STM32F303C8    |    STM32F303C6    |    STM32F302ZE    |
|    STM32F302ZD    |    STM32F302VE    |    STM32F302VD    |    STM32F302VC    |    STM32F302VB    |
|    STM32F302RE    |    STM32F302RD    |    STM32F302RC    |    STM32F302RB    |    STM32F302R8    |
|    STM32F302R6    |    STM32F302K8    |    STM32F302K6    |    STM32F302CC    |    STM32F302CB    |
|    STM32F302C8    |    STM32F302C6    |    STM32F301R8    |    STM32F301R6    |    STM32F301K8    |
|    STM32F301K6    |    STM32F301C8    |    STM32F301C6    |    STM32F217ZG    |    STM32F217ZE    |
|    STM32F217VG    |    STM32F217VE    |    STM32F217IG    |    STM32F217IE    |    STM32F215ZG    |
|    STM32F215ZE    |    STM32F215VG    |    STM32F215VE    |    STM32F215RG    |    STM32F215RE    |
|    STM32F207ZG    |    STM32F207ZF    |    STM32F207ZE    |    STM32F207ZC    |    STM32F207VG    |
|    STM32F207VF    |    STM32F207VE    |    STM32F207VC    |    STM32F207IG    |    STM32F207IF    |
|    STM32F207IE    |    STM32F207IC    |    STM32F205ZG    |    STM32F205ZF    |    STM32F205ZE    |
|    STM32F205ZC    |    STM32F205VG    |    STM32F205VF    |    STM32F205VE    |    STM32F205VC    |
|    STM32F205VB    |    STM32F205RG    |    STM32F205RF    |    STM32F205RE    |    STM32F205RC    |
|    STM32F205RB    |    STM32F107VC    |    STM32F107VB    |    STM32F107RC    |    STM32F107RB    |
|    STM32F105VC    |    STM32F105VB    |    STM32F105V8    |    STM32F105RC    |    STM32F105RB    |
|    STM32F105R8    |    STM32F103ZG    |    STM32F103ZF    |    STM32F103ZE    |    STM32F103ZD    |
|    STM32F103ZC    |    STM32F103VG    |    STM32F103VF    |    STM32F103VE    |    STM32F103VD    |
|    STM32F103VC    |    STM32F103VB    |    STM32F103V8    |    STM32F103TB    |    STM32F103T8    |
|    STM32F103T6    |    STM32F103T4    |    STM32F103RG    |    STM32F103RF    |    STM32F103RE    |
|    STM32F103RD    |    STM32F103RC    |    STM32F103RB    |    STM32F103R8    |    STM32F103R6    |
|    STM32F103R4    |    STM32F103CB    |    STM32F103C8    |    STM32F103C6    |    STM32F103C4    |
|    STM32F102RB    |    STM32F102R8    |    STM32F102R6    |    STM32F102R4    |    STM32F102CB    |
|    STM32F102C8    |    STM32F102C6    |    STM32F102C4    |    STM32F101ZG    |    STM32F101ZF    |
|    STM32F101ZE    |    STM32F101ZD    |    STM32F101ZC    |    STM32F101VG    |    STM32F101VF    |
|    STM32F101VE    |    STM32F101VD    |    STM32F101VC    |    STM32F101VB    |    STM32F101V8    |
|    STM32F101TB    |    STM32F101T8    |    STM32F101T6    |    STM32F101T4    |    STM32F101RG    |
|    STM32F101RF    |    STM32F101RE    |    STM32F101RD    |    STM32F101RC    |    STM32F101RB    |
|    STM32F101R8    |    STM32F101R6    |    STM32F101R4    |    STM32F101CB    |    STM32F101C8    |
|    STM32F101C6    |    STM32F101C4    |    STM32F100ZE    |    STM32F100ZD    |    STM32F100ZC    |
|    STM32F100VE    |    STM32F100VD    |    STM32F100VC    |    STM32F100VB    |    STM32F100V8    |
|    STM32F100RE    |    STM32F100RD    |    STM32F100RC    |    STM32F100RB    |    STM32F100R8    |
|    STM32F100R6    |    STM32F100R4    |    STM32F100CB    |    STM32F100C8    |    STM32F100C6    |
|    STM32F100C4    |    STM32F098VC    |    STM32F098RC    |    STM32F098CC    |    STM32F091VC    |
|    STM32F091VB    |    STM32F091RC    |    STM32F091RB    |    STM32F091CC    |    STM32F091CB    |
|    STM32F078VB    |    STM32F078RB    |    STM32F078CB    |    STM32F072VB    |    STM32F072V8    |
|    STM32F072RB    |    STM32F072R8    |    STM32F072CB    |    STM32F072C8    |    STM32F071VB    |
|    STM32F071V8    |    STM32F071RB    |    STM32F071CB    |    STM32F071C8    |    STM32F070RB    |
|    STM32F070F6    |    STM32F070CB    |    STM32F070C6    |    STM32F058T8    |    STM32F058R8    |
|    STM32F058C8    |    STM32F051T8    |    STM32F051R8    |    STM32F051R6    |    STM32F051R4    |
|    STM32F051K8    |    STM32F051K6    |    STM32F051K4    |    STM32F051C8    |    STM32F051C6    |
|    STM32F051C4    |    STM32F048T6    |    STM32F048G6    |    STM32F048C6    |    STM32F042T6    |
|    STM32F042K6    |    STM32F042K4    |    STM32F042G6    |    STM32F042G4    |    STM32F042F6    |
|    STM32F042F4    |    STM32F042C6    |    STM32F042C4    |    STM32F038K6    |    STM32F038G6    |
|    STM32F038F6    |    STM32F038E6    |    STM32F038C6    |    STM32F031K6    |    STM32F031K4    |
|    STM32F031G6    |    STM32F031G4    |    STM32F031F6    |    STM32F031F4    |    STM32F031E6    |
|    STM32F031C6    |    STM32F031C4    |    STM32F030RC    |    STM32F030R8    |    STM32F030K6    |
|    STM32F030F4    |    STM32F030CC    |    STM32F030C8    |    STM32F030C6    |

+ LVGL added to mikroSDK
  + A little something about LVGL:
    + Light and Versatile Graphics Library, is an open-source embedded graphics library designed to create high-quality, graphical user interfaces for various embedded systems and microcontrollers. It is actively maintained by a global community of developers and has gained popularity for its versatility and performance
  + Structure added to `thirdparty` directory in mikroSDK root
  + Intermediate applicative layer added for hardware related settings and configuration
    + Layer located in:
      + `./components/tft7/common`
      + `./components/tft8/common`
    + The layer contains routines for HW specific initialization and handling needed by LVGL
  + Project templates updated for NECTO studio as well
+ Added RTC (Real Time Clock) library support
  + Following APIs now supported
    + `rtc_init`
    + `rtc_start`
    + `rtc_stop`
    + `rtc_reset`
    + `rtc_set_time`
    + `rtc_get_time`
    + `software_reset`
+ Added LCD (Liquid-crystal display) library support
  + Following APIs now supported
    + `lcd_configure_default`
    + `lcd_configure`
    + `lcd_init`
    + `lcd_write`
    + `lcd_write_text`
    + `lcd_shift_right`
    + `lcd_shift_left`
    + `lcd_set_row`
    + `lcd_turn_on`
    + `lcd_turn_off`
    + `lcd_clear`
    + `lcd_cursor_move_home`
    + `lcd_cursor_move_left`
    + `lcd_cursor_move_right`
    + `lcd_cursor_off`
    + `lcd_cursor_on`
    + `lcd_backlight_off`
    + `lcd_backlight_on`
+ Added following test examples
  + `lcd`
+ SSD1963 now exports command header file to setup as well
  + File exported: `ssd1963_cmd.h`

### Improvements

+ GPIO `DRV/HAL/HAL_LL` implementations can now be flattened
  + Effectively, this means that GPIO related code execution is around **3 times faster**
  + Note that flatten shall be set to level `NONE` by default, unless changed by NECTO setup
    + User can also change this manually in `./targets/CMakeLists.txt`
  + Code flatten levels:
    + HIGH (Flattens all levels)
    + MID (Flattens `HAL` and `HAL_LL` code)
    + LOW (Flattens only `HAL_LL` code)
    + NONE (No flatten done - Default setting for backwards compatible code)
+ SPI hal level implementation updated
  + Speed value checking has been added to function `hal_spi_master_set_speed`, returning error if zero
+ `TinyUSB` and `CycloneTCP` moved from `API` layer to `Third-party`
  + All future non-mikroe developed libraries shall be added here
+ GPIO module for TIVA MCUs updated
  + GPIO_PCTL register bits are now cleared when pin is initialized

### Fixes

+ Fixed STM32 PWM low level implementation 2
  + `_hal_ll_tim_get_clock_speed` function call in `_hal_ll_tim_hw_init` function was getting base address instead of module index
+ Fixed all low level PWM implementations for PIC MCUs
  + `_hal_ll_tim_set_module_state` function calls in `hal_ll_tim_close` function were getting module index instead of map structure pointer
+ Fixed enabling clock for ADC1 module for MK22 MCUs
  + Previous implementation caused general exception
+ `MikroC.Core` library is now linked for both MikroC and GCC compilers in MikroSDK project
  + Previously only linked for GCC resulting in `MikroC.Core` header files not being included adequately
  + Headers such as `delays.h`, `interrupts.h`, etc. can now be included
+ SPI NXP implementation now sets delay prescalers and scalers based on current clock
  + Values set:
    + `PCS to SCK Delay Scaler`
    + `After SCK Delay Scaler`
    + `Delay After Transfer Scaler`
  + Fix was manifested by frequently changing data before sending it while using SPI modes 1 and 3
+ SPI implementation for TIVA MCUs can now apply baud rate values lower than 2MHz
  + Previously the lowest possible value could be set to 2MHz
+ Fixed default ADC resolution for all PIC18FxxJ11 MCUs to be always 10 bit
  + Previously for PIC18F86J11 and PIC18F87J11 it was set to 12 bit
+ Fixed GPIO initialization issue for TIVA MCUs
  + GPIO_PCTL register retained a non-zero value after a reset, causing misconfiguration
    of user-set alternate functions for certain pins
+ Fixed `mcu_card.h` for **MCU card for PIC32** and **MCU card 10 for Kinetis**
  + `RIGHT_CN_PIN_043` and `RIGHT_CN_PIN_044` were defined as `NC` but they have actual pins routed

### NEW HARDWARE

+ [STM32F4 Discovery Shield](https://www.mikroe.com/stm32f4-discovery-click-shield)
+ [Discovery kit with STM32F407VG MCU](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)
+ [STM32F3 Discovery Shield](https://www.mikroe.com/stm32f3-discovery-click-shield)
+ [Discovery kit with STM32F303VC MCU](https://www.st.com/en/evaluation-tools/stm32f3discovery.html)
+ [Clicker 4 for PIC18F](https://www.mikroe.com/clicker-4-for-pic18f)
+ [Click shield for Arduino MEGA](https://www.mikroe.com/click-shield-for-arduino-mega)
+ [Arduino Mega 2560 Rev3](https://store.arduino.cc/products/arduino-mega-2560-rev3)
+ [Click Shield for Nucleo-144](https://www.mikroe.com/click-shield-for-nucleo-144)
+ [STM32 Nucleo-144 development board with STM32F722ZE MCU](https://www.st.com/en/evaluation-tools/nucleo-f722ze.html)
+ [STM32 Nucleo-144 development board with STM32F413ZH MCU](https://www.st.com/en/evaluation-tools/nucleo-f413zh.html)
+ [STM32 Nucleo-144 development board with STM32F446ZE MCU](https://www.st.com/en/evaluation-tools/nucleo-f446ze.html)
+ [STM32 Nucleo-144 development board with STM32H743ZI MCU](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html)
+ [CURIOSITY NANO BASE FOR CLICK BOARDS™](https://www.microchip.com/en-us/development-tool/ac164162)
+ [PIC18F47K42 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/dm182028)
+ [PIC18F57Q43 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/dm164150)
+ [PIC18F47Q10 CURIOSITY NANO](https://www.microchip.com/en-us/development-tool/dm182029)

### Collaborators

**We would like to thank the following people for contributing:**

+ **[@huchonar](https://github.com/huchonar)**
  + [./tiva/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/rtc/implementation_1/hal_ll_rtc.c)
  + [./tiva/src/rtc/implementation_2/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/rtc/implementation_2/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_7/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_7/hal_ll_rtc.c)

+ **[@juickar‌](http://github.com/juickar‌)**
  + [./pic32/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/rtc/implementation_1/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_1/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_2/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_2/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_3/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_3/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_4/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_4/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_5/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_5/hal_ll_rtc.c)

+ **[@viziergr](https://www.github.com/viziergr)**
  + [./gigadevice/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/rtc/implementation_1/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_6/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_6/hal_ll_rtc.c)

+ **[@aymericbiard](https://github.com/aymericbiard)**
  + [./nxp/src/rtc/implementation_1/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/rtc/implementation_1/hal_ll_rtc.c)
  + [./stm32/src/rtc/implementation_8/hal_ll_rtc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/rtc/implementation_8/hal_ll_rtc.c)

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
