<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.13.0`

+ released: 2024-12-24

## Changes

+ [`v2.13.0`](#v2130)
  + [Changes](#changes)
    + [SAM](#sam)
    + [NEW HARDWARE](#new-hardware)

### <font color=red>SAM</font>

**SAM MCUs supported!**

|       MCU      |       MCU      |       MCU      |
| :------------: | :------------: | :------------: |
|  ATSAME70J19A  |  ATSAMS70J21A  |  ATSAMV70Q19A  |
|  ATSAME70J19B  |  ATSAMS70J21B  |  ATSAMV70Q19B  |
|  ATSAME70J20A  |  ATSAMS70N19A  |  ATSAMV70Q20A  |
|  ATSAME70J20B  |  ATSAMS70N19B  |  ATSAMV70Q20B  |
|  ATSAME70J21A  |  ATSAMS70N20A  |  ATSAMV71J19A  |
|  ATSAME70J21B  |  ATSAMS70N20B  |  ATSAMV71J19B  |
|  ATSAME70N19A  |  ATSAMS70N21A  |  ATSAMV71J20A  |
|  ATSAME70N19B  |  ATSAMS70N21B  |  ATSAMV71J20B  |
|  ATSAME70N20A  |  ATSAMS70Q19A  |  ATSAMV71J21A  |
|  ATSAME70N20B  |  ATSAMS70Q19B  |  ATSAMV71J21B  |
|  ATSAME70N21A  |  ATSAMS70Q20A  |  ATSAMV71N19A  |
|  ATSAME70N21B  |  ATSAMS70Q20B  |  ATSAMV71N19B  |
|  ATSAME70Q19A  |  ATSAMS70Q21A  |  ATSAMV71N20A  |
|  ATSAME70Q19B  |  ATSAMS70Q21B  |  ATSAMV71N20A  |
|  ATSAME70Q20A  |  ATSAMV70J19A  |  ATSAMV71N21A  |
|  ATSAME70Q20B  |  ATSAMV70J19B  |  ATSAMV71N21B  |
|  ATSAME70Q21A  |  ATSAMV70J20A  |  ATSAMV71Q19A  |
|  ATSAME70Q21B  |  ATSAMV70J20B  |  ATSAMV71Q19B  |
|  ATSAMS70J19A  |  ATSAMV70N19A  |  ATSAMV71Q20A  |
|  ATSAMS70J19B  |  ATSAMV70N19B  |  ATSAMV71Q20B  |
|  ATSAMS70J20A  |  ATSAMV70N20A  |  ATSAMV71Q21A  |
|  ATSAMS70J20B  |  ATSAMV70N20B  |  ATSAMV71Q21B  |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ OW (Full module support)

**Files updated:**

+ Updated due to SAM inclusion in all ARM-related CMake files
  + [utils.cmake](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/cmake/utils.cmake)
  + [interface/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/interface/CMakeLists.txt)
  + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/CMakeLists.txt)
  + [common/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/CMakeLists.txt)
  + [core/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/core/CMakeLists.txt)
+ Updated with more register handling macros for ARM architectures
  + [hal_ll_bit_control.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/hal_ll_bit_control.h)
+ Updated with IRQ handling macros and regicters for SAM MCUs
  + [hal_ll_core_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/core/include/hal_ll_core_defines.h)

**Files added:**

+ [hal_ll_adc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/adc/hal_ll_adc.h)
+ [hal_ll_adc_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/adc/hal_ll_adc_pin_map/implementations/implementation_1/hal_ll_adc_pin_map.h)
+ [hal_ll_gpio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h)
+ [hal_ll_gpio_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h)
+ [hal_ll_gpio_struct_type.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/implementations/implementation_1/hal_ll_gpio_struct_type.h)
+ [hal_ll_pin_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/hal_ll_pin_names.h)
+ [hal_ll_target.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/hal_ll_target.h)
+ [hal_ll_target_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/hal_ll_target_names.h)
+ [hal_ll_i2c_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/i2c/hal_ll_i2c_master.h)
+ [hal_ll_i2c_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/i2c/hal_ll_i2c_pin_map/implementations/implementation_1/hal_ll_i2c_pin_map.h)
+ [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/one_wire/implementations/implementation_1/hal_ll_one_wire.h)
+ [hal_ll_spi_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/spi_master/hal_ll_spi_master.h)
+ [hal_ll_spi_master_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/spi_master/hal_ll_spi_master_pin_map/implementations/implementation_1/hal_ll_spi_master_pin_map.h)
+ [hal_ll_tim.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/tim/hal_ll_tim.h)
+ [hal_ll_tim_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/tim/hal_ll_tim_pin_map/implementations/implementation_1/hal_ll_tim_pin_map.h)
+ [hal_ll_uart.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/uart/hal_ll_uart.h)
+ [hal_ll_uart_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/uart/hal_ll_uart_pin_map/implementations/implementation_1/hal_ll_uart_pin_map.h)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/adc/implementations/implementation_1/hal_ll_adc.c)
+ [hal_ll_gpio.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c)
+ [hal_ll_gpio_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/i2c/implementations/implementation_1/hal_ll_i2c_master.c)
+ [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/one_wire/implementations/implementation_1/hal_ll_one_wire.c)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/spi_master/implementations/implementation_1/hal_ll_spi_master.c)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/tim/implementations/implementation_1/hal_ll_tim.c)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/uart/implementations/implementation_1/hal_ll_uart.c)
+ [hal_ll_core_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/core/src/sam/m7/hal_ll_core_port.c)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/CMakeLists.txt)
+ [hal_ll/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/hal_ll/CMakeLists.txt)
+ [adc/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/adc/CMakeLists.txt)
+ [gpio/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/CMakeLists.txt)
+ [i2c/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/i2c/CMakeLists.txt)
+ [one_wire/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/one_wire/CMakeLists.txt)
+ [spi_master/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/spi_master/CMakeLists.txt)
+ [tim/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/tim/CMakeLists.txt)
+ [uart/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/uart/CMakeLists.txt)
+ `./mcu_name/mcu_package/mcu_definitions.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_definitions/SAM/mcu_name/mcu_package/mcu_definitions.h`
  > + Added for all MCUs in mikroSDK where mcu_name is actual chip full name, i.e. `ATSAME70Q21B` etc. and mcu_package is actual package, i.e. `LQFP64` etc.
+ `./mcu_name/mcu_package/mcu_reg_addresses.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/common/include/mcu_definitions/SAM/mcu_name/mcu_package/mcu_reg_addresses.h`
  > + Added for all MCUs in mikroSDK where mcu_name is actual chip full name, i.e. `ATSAME70Q21B` etc. and mcu_package is actual package, i.e. `LQFP64` etc.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-12-24](./new_hw/2024-12-24.md)**
+ **[2024-12-25](./new_hw/2024-12-25.md)**
+ **[2024-12-26](./new_hw/2024-12-26.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
