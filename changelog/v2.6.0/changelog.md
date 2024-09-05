<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.6.0`

+ released: 2022-06-16

## Changes

- [`v2.6.0`](#v260)
  - [Changes](#changes)
    - [RISC-V SDK](#risc-v-sdk)
    - [New Features](#new-features)
    - [NEW HARDWARE](#new-hardware)
    - [PLANET DEBUG](#planet-debug)
    - [DEVELOPMENT KIT PACKAGE](#development-kit-package)
    - [Test examples](#test-examples)

### <font color=red>RISC-V SDK</font>

**RISV-V MCU architecture supported!**

|      MCU      |      MCU      |
| :-----------: | :-----------: |
| GD32VF103C4T6 | GD32VF103C6T6 |
| GD32VF103C8T6 | GD32VF103CBT6 |
| GD32VF103R4T6 | GD32VF103R6T6 |
| GD32VF103R8T6 | GD32VF103RBT6 |
| GD32VF103T4U6 | GD32VF103T6U6 |
| GD32VF103T8U6 | GD32VF103TBU6 |
| GD32VF103V8T6 | GD32VF103VBT6 |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)

**Files added:**

+ [assembly.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/assembly.h)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/adc/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/hal_ll/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/i2c/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/one_wire/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/spi_master/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/tim/CMakeLists.txt)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/uart/CMakeLists.txt)
+ [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/common_macros.h)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/adc/implementation_1/hal_ll_adc.c)
+ [hal_ll_adc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/adc/hal_ll_adc.h)
+ [hal_ll_adc_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/adc/hal_ll_adc_pin_map/implementation_1/hal_ll_adc_pin_map.h)
+ [hal_ll_bit_control.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/hal_ll_bit_control.h)
+ [hal_ll_core.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/src/hal_ll_core.c)
+ [hal_ll_core.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core.h)
+ [hal_ll_core_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core_defines.h)
+ [hal_ll_core_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/src/gigadevice/bumblebee/hal_ll_core_port.c)
+ [hal_ll_core_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/core/include/hal_ll_core_port.h)
+ [hal_ll_gpio.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c)
+ [hal_ll_gpio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h)
+ [hal_ll_gpio_constants.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_constants.h)
+ [hal_ll_gpio_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c)
+ [hal_ll_gpio_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/i2c/implementation_1/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/i2c/hal_ll_i2c_master.h)
+ [hal_ll_i2c_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/i2c/hal_ll_i2c_pin_map/implementation_1/hal_ll_i2c_pin_map.h)
+ [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/one_wire/hal_ll_one_wire.c)
+ [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/one_wire/hal_ll_one_wire.h)
+ [hal_ll_pin_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_pin_names.h)
+ [hal_ll_rcu.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_rcu.h)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/spi_master/implementation_1/hal_ll_spi_master.c)
+ [hal_ll_spi_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/spi_master/hal_ll_spi_master.h)
+ [hal_ll_spi_master_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/spi_master/hal_ll_spi_master_pin_map/implementation_1/hal_ll_spi_master_pin_map.h)
+ [hal_ll_target.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_target.h)
+ [hal_ll_target_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/hal_ll_target_names.h)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/tim/implementation_1/hal_ll_tim.c)
+ [hal_ll_tim.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/tim/hal_ll_tim.h)
+ [hal_ll_tim_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/tim/hal_ll_tim_pin_map/implementation_1/hal_ll_tim_pin_map.h)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/uart/implementation_1/hal_ll_uart.c)
+ [hal_ll_uart.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/uart/hal_ll_uart.h)
+ [hal_ll_uart_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/uart/hal_ll_uart_pin_map/implementation_1/hal_ll_uart_pin_map.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C4T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C6T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103C8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103CBT6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R4T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R6T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103R8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103RBT6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T4U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T6U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103T8U6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103TBU6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103V8T6/mcu_definitions.h)
+ [mcu_definitions.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/common/include/mcu_definitions/GIGADEVICE/GD32VF103VBT6/mcu_definitions.h)

### New Features

+ CMake build system with automated functionalities:
  + Adding files
  + Removing files
  + Renaming files for the CMake project
  + Adding/removing libraries from the CMake project

**With the addition of `touch_controller` libs, it is now possible to switch**
**mid DESIGNER project to any of the supported displays. There is no need**
**to create a new project. mikroSDK will take care of that for you.**

Files added:

+ ./middleware/touch_controller/CMakeLists.txt
+ ./middleware/touch_controller/lib/CMakeLists.txt
+ ./middleware/touch_controller/lib/src/touch_controller.c
+ ./middleware/touch_controller/lib/include/touch_controller.h

### NEW HARDWARE

Support added for following hardware:

+ [UNI-DS v8](https://www.mikroe.com/uni-ds-v8)
+ [SIBRAIN FOR PIC24HJ256GP610](https://www.mikroe.com/sibrain-for-pic24hj256gp610)
+ [SIBRAIN FOR DSPIC33FJ256GP710A](https://www.mikroe.com/sibrain-for-dspic33fj256gp710a)
+ [SIBRAIN FOR PIC24EP512GU814](https://www.mikroe.com/sibrain-for-pic24ep512gu814)
+ [SIBRAIN FOR DSPIC33EP512MU814](https://www.mikroe.com/sibrain-for-dspic33ep512mu814)
+ [EasyPIC FUSION v7 MCUcard with PIC24FJ128GA310](https://www.mikroe.com/easypic-fusion-v7-pic24fj128ga310)
+ [EasyPIC FUSION v7 MCUcard with PIC24EP512GU810](https://www.mikroe.com/easypic-fusion-v7-pic24ep512gu810)
+ [EasyPIC FUSION v7 MCUcard with dsPIC33FJ256GP710A](https://www.mikroe.com/easypic-fusion-v7-dspic33fj256gp710a)
+ [EasyPIC FUSION v7 MCUcard with dsPIC33EP512MU810](https://www.mikroe.com/easypic-fusion-v7-dspic33ep512mu810)
+ [Discovery kit with STM32L4R9AI MCU](https://www.st.com/en/evaluation-tools/32l4r9idiscovery.html)

### PLANET DEBUG

+ All 80 PD systems updated
  + New setups added with CMake
  + Each PD system now has two separate setups
    + One for older NECTO Studio versions
    + One for NECTO Studio v2 and up

### DEVELOPMENT KIT PACKAGE

+ With the introduction of CMake build system in NECTO Studio, there is no need for the development kit anymore
+ Removed from repository

### Test examples

**All test examples have been revamped to work with CMake build system.**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
