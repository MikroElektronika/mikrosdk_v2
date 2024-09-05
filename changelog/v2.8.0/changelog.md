<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.8.0`

+ released: 2023-07-20

## Changes

- [`v2.8.0`](#v280)
  - [Changes](#changes)
    - [dsPIC](#dspic)
    - [GCC ARM](#gcc-arm)
    - [New Features](#new-features)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>dsPIC</font>

**dsPIC MCUs supported!**

|        MCU         |        MCU         |        MCU         |        MCU         |        MCU         |
| :----------------: | :----------------: | :----------------: | :----------------: | :----------------: |
|    dsPIC30F3012    |   dsPIC30F3012E    |    dsPIC30F3013    |   dsPIC30F3013E    |    dsPIC30F3014    |
|   dsPIC30F3014E    |    dsPIC30F4011    |   dsPIC30F4011E    |    dsPIC30F4012    |   dsPIC30F4012E    |
|    dsPIC30F4013    |   dsPIC30F4013E    |    dsPIC30F5011    |   dsPIC30F5011E    |    dsPIC30F5013    |
|   dsPIC30F5013E    |    dsPIC30F5015    |   dsPIC30F5015E    |    dsPIC30F6010    |   dsPIC30F6010A    |
|    dsPIC30F6011    |   dsPIC30F6011A    |    dsPIC30F6012    |   dsPIC30F6012A    |    dsPIC30F6013    |
|   dsPIC30F6013A    |    dsPIC30F6014    |   dsPIC30F6014A    |    dsPIC30F6015    | dsPIC33EP128GM304  |
| dsPIC33EP128GM306  | dsPIC33EP128GM310  | dsPIC33EP128GM604  | dsPIC33EP128GM706  | dsPIC33EP128GM710  |
| dsPIC33EP128GP502  | dsPIC33EP128GP504  | dsPIC33EP128GP506  | dsPIC33EP128MC202  | dsPIC33EP128MC204  |
| dsPIC33EP128MC206  | dsPIC33EP128MC502  | dsPIC33EP128MC504  | dsPIC33EP128MC506  | dsPIC33EP256GM304  |
| dsPIC33EP256GM306  | dsPIC33EP256GM310  | dsPIC33EP256GM604  | dsPIC33EP256GM706  | dsPIC33EP256GM710  |
| dsPIC33EP256GP502  | dsPIC33EP256GP504  | dsPIC33EP256GP506  | dsPIC33EP256MC202  | dsPIC33EP256MC204  |
| dsPIC33EP256MC206  | dsPIC33EP256MC502  | dsPIC33EP256MC504  | dsPIC33EP256MC506  | dsPIC33EP256MU806  |
| dsPIC33EP256MU810  | dsPIC33EP256MU814  |  dsPIC33EP32GP502  |  dsPIC33EP32GP503  |  dsPIC33EP32GP504  |
|  dsPIC33EP32MC202  |  dsPIC33EP32MC203  |  dsPIC33EP32MC204  |  dsPIC33EP32MC502  |  dsPIC33EP32MC503  |
|  dsPIC33EP32MC504  | dsPIC33EP512GM304  | dsPIC33EP512GM306  | dsPIC33EP512GM310  | dsPIC33EP512GM604  |
| dsPIC33EP512GM706  | dsPIC33EP512GM710  | dsPIC33EP512GP502  | dsPIC33EP512GP504  | dsPIC33EP512GP506  |
| dsPIC33EP512GP806  | dsPIC33EP512MC202  | dsPIC33EP512MC204  | dsPIC33EP512MC206  | dsPIC33EP512MC502  |
| dsPIC33EP512MC504  | dsPIC33EP512MC506  | dsPIC33EP512MC806  | dsPIC33EP512MU810  | dsPIC33EP512MU814  |
|  dsPIC33EP64GP502  |  dsPIC33EP64GP503  |  dsPIC33EP64GP504  |  dsPIC33EP64GP506  |  dsPIC33EP64MC202  |
|  dsPIC33EP64MC203  |  dsPIC33EP64MC204  |  dsPIC33EP64MC206  |  dsPIC33EP64MC502  |  dsPIC33EP64MC503  |
|  dsPIC33EP64MC504  |  dsPIC33EP64MC506  | dsPIC33FJ128GP202  | dsPIC33FJ128GP204  | dsPIC33FJ128GP206  |
| dsPIC33FJ128GP206A | dsPIC33FJ128GP306  | dsPIC33FJ128GP306A | dsPIC33FJ128GP310  | dsPIC33FJ128GP310A |
| dsPIC33FJ128GP706  | dsPIC33FJ128GP706A | dsPIC33FJ128GP708  | dsPIC33FJ128GP708A | dsPIC33FJ128GP710  |
| dsPIC33FJ128GP710A | dsPIC33FJ128GP802  | dsPIC33FJ128GP804  | dsPIC33FJ128MC202  | dsPIC33FJ128MC204  |
| dsPIC33FJ128MC506A | dsPIC33FJ128MC510A | dsPIC33FJ128MC706A | dsPIC33FJ128MC708A | dsPIC33FJ128MC710A |
| dsPIC33FJ128MC802  | dsPIC33FJ128MC804  |  dsPIC33FJ16GP304  |  dsPIC33FJ16MC304  | dsPIC33FJ256GP506  |
| dsPIC33FJ256GP506A | dsPIC33FJ256GP510  | dsPIC33FJ256GP510A | dsPIC33FJ256GP710  | dsPIC33FJ256GP710A |
| dsPIC33FJ256MC510A | dsPIC33FJ256MC710A |  dsPIC33FJ32GP101  |  dsPIC33FJ32GP102  |  dsPIC33FJ32GP104  |
|  dsPIC33FJ32GP202  |  dsPIC33FJ32GP204  |  dsPIC33FJ32GP302  |  dsPIC33FJ32GP304  |  dsPIC33FJ32MC202  |
|  dsPIC33FJ32MC204  |  dsPIC33FJ32MC302  |  dsPIC33FJ32MC304  |  dsPIC33FJ64GP202  |  dsPIC33FJ64GP204  |
|  dsPIC33FJ64GP206  | dsPIC33FJ64GP206A  |  dsPIC33FJ64GP306  | dsPIC33FJ64GP306A  |  dsPIC33FJ64GP310  |
| dsPIC33FJ64GP310A  |  dsPIC33FJ64GP706  | dsPIC33FJ64GP706A  |  dsPIC33FJ64GP708  | dsPIC33FJ64GP708A  |
|  dsPIC33FJ64GP710  | dsPIC33FJ64GP710A  |  dsPIC33FJ64GP802  |  dsPIC33FJ64GP804  |  dsPIC33FJ64MC202  |
|  dsPIC33FJ64MC204  | dsPIC33FJ64MC506A  | dsPIC33FJ64MC508A  | dsPIC33FJ64MC510A  | dsPIC33FJ64MC706A  |
| dsPIC33FJ64MC710A  |  dsPIC33FJ64MC802  |  dsPIC33FJ64MC804  |  PIC24EP128GP202   |  PIC24EP128GP204   |
|  PIC24EP128GP206   |  PIC24EP128MC202   |  PIC24EP128MC204   |  PIC24EP128MC206   |  PIC24EP256GP202   |
|  PIC24EP256GP204   |  PIC24EP256GP206   |  PIC24EP256GU810   |  PIC24EP256GU814   |  PIC24EP256MC202   |
|  PIC24EP256MC204   |  PIC24EP256MC206   |   PIC24EP32GP202   |   PIC24EP32GP203   |   PIC24EP32GP204   |
|   PIC24EP32MC202   |   PIC24EP32MC203   |   PIC24EP32MC204   |  PIC24EP512GP202   |  PIC24EP512GP204   |
|  PIC24EP512GP206   |  PIC24EP512GP806   |  PIC24EP512GU810   |  PIC24EP512GU814   |  PIC24EP512MC202   |
|  PIC24EP512MC204   |  PIC24EP512MC206   |   PIC24EP64GP202   |   PIC24EP64GP203   |   PIC24EP64GP204   |
|   PIC24EP64GP206   |   PIC24EP64MC202   |   PIC24EP64MC203   |   PIC24EP64MC204   |   PIC24EP64MC206   |
|   PIC24F16KA102    |   PIC24F16KA301    |   PIC24F16KA302    |   PIC24F16KA304    |   PIC24F32KA301    |
|   PIC24F32KA302    |   PIC24F32KA304    |  PIC24FJ1024GA606  |  PIC24FJ1024GA610  |  PIC24FJ1024GB606  |
|  PIC24FJ1024GB610  |  PIC24FJ128DA106   |  PIC24FJ128DA110   |  PIC24FJ128DA206   |  PIC24FJ128DA210   |
|  PIC24FJ128GA006   |  PIC24FJ128GA008   |  PIC24FJ128GA010   |  PIC24FJ128GA106   |  PIC24FJ128GA108   |
|  PIC24FJ128GA110   |  PIC24FJ128GA202   |  PIC24FJ128GA204   |  PIC24FJ128GA306   |  PIC24FJ128GA308   |
|  PIC24FJ128GA310   |  PIC24FJ128GA406   |  PIC24FJ128GA410   |  PIC24FJ128GA412   |  PIC24FJ128GA606   |
|  PIC24FJ128GA610   |  PIC24FJ128GA702   |  PIC24FJ128GA704   |  PIC24FJ128GA705   |  PIC24FJ128GB106   |
|  PIC24FJ128GB108   |  PIC24FJ128GB110   |  PIC24FJ128GB202   |  PIC24FJ128GB204   |  PIC24FJ128GB206   |
|  PIC24FJ128GB210   |  PIC24FJ128GB406   |  PIC24FJ128GB410   |  PIC24FJ128GB412   |  PIC24FJ128GB606   |
|  PIC24FJ128GB610   |   PIC24FJ16GA002   |   PIC24FJ16GA004   |  PIC24FJ192GA106   |  PIC24FJ192GA108   |
|  PIC24FJ192GA110   |  PIC24FJ192GB106   |  PIC24FJ192GB108   |  PIC24FJ192GB110   |  PIC24FJ256DA106   |
|  PIC24FJ256DA110   |  PIC24FJ256DA206   |  PIC24FJ256DA210   |  PIC24FJ256GA106   |  PIC24FJ256GA108   |
|  PIC24FJ256GA110   |  PIC24FJ256GA406   |  PIC24FJ256GA410   |  PIC24FJ256GA412   |  PIC24FJ256GA606   |
|  PIC24FJ256GA610   |  PIC24FJ256GA702   |  PIC24FJ256GA704   |  PIC24FJ256GA705   |  PIC24FJ256GB106   |
|  PIC24FJ256GB108   |  PIC24FJ256GB110   |  PIC24FJ256GB206   |  PIC24FJ256GB210   |  PIC24FJ256GB406   |
|  PIC24FJ256GB410   |  PIC24FJ256GB412   |  PIC24FJ256GB606   |  PIC24FJ256GB610   |   PIC24FJ32GA002   |
|   PIC24FJ32GA004   |   PIC24FJ32GA102   |   PIC24FJ32GA104   |   PIC24FJ32GB002   |   PIC24FJ32GB004   |
|   PIC24FJ48GA002   |   PIC24FJ48GA004   |  PIC24FJ512GA606   |  PIC24FJ512GA610   |  PIC24FJ512GB606   |
|  PIC24FJ512GB610   |   PIC24FJ64GA002   |   PIC24FJ64GA004   |   PIC24FJ64GA006   |   PIC24FJ64GA008   |
|   PIC24FJ64GA010   |   PIC24FJ64GA102   |   PIC24FJ64GA104   |   PIC24FJ64GA106   |   PIC24FJ64GA108   |
|   PIC24FJ64GA110   |   PIC24FJ64GA202   |   PIC24FJ64GA204   |   PIC24FJ64GA306   |   PIC24FJ64GA308   |
|   PIC24FJ64GA310   |   PIC24FJ64GA406   |   PIC24FJ64GA410   |   PIC24FJ64GA412   |   PIC24FJ64GA702   |
|   PIC24FJ64GA704   |   PIC24FJ64GA705   |   PIC24FJ64GB002   |   PIC24FJ64GB004   |   PIC24FJ64GB106   |
|   PIC24FJ64GB108   |   PIC24FJ64GB110   |   PIC24FJ64GB202   |   PIC24FJ64GB204   |   PIC24FJ64GB406   |
|   PIC24FJ64GB410   |   PIC24FJ64GB412   |   PIC24FJ96GA006   |   PIC24FJ96GA008   |   PIC24FJ96GA010   |
|   PIC24FV16KA301   |   PIC24FV16KA302   |   PIC24FV16KA304   |   PIC24FV32KA301   |   PIC24FV32KA302   |
|   PIC24FV32KA304   |  PIC24HJ128GP202   |  PIC24HJ128GP204   |  PIC24HJ128GP206   |  PIC24HJ128GP206A  |
|  PIC24HJ128GP210   |  PIC24HJ128GP210A  |  PIC24HJ128GP306   |  PIC24HJ128GP306A  |  PIC24HJ128GP310   |
|  PIC24HJ128GP310A  |  PIC24HJ128GP502   |  PIC24HJ128GP504   |  PIC24HJ128GP506   |  PIC24HJ128GP506A  |
|  PIC24HJ128GP510   |  PIC24HJ128GP510A  |   PIC24HJ16GP304   |  PIC24HJ256GP206   |  PIC24HJ256GP206A  |
|  PIC24HJ256GP210   |  PIC24HJ256GP210A  |  PIC24HJ256GP610   |  PIC24HJ256GP610A  |   PIC24HJ32GP202   |
|   PIC24HJ32GP204   |   PIC24HJ32GP302   |   PIC24HJ32GP304   |   PIC24HJ64GP202   |   PIC24HJ64GP204   |
|   PIC24HJ64GP206   |  PIC24HJ64GP206A   |   PIC24HJ64GP210   |  PIC24HJ64GP210A   |   PIC24HJ64GP502   |
|   PIC24HJ64GP504   |   PIC24HJ64GP506   |  PIC24HJ64GP506A   |   PIC24HJ64GP510   |  PIC24HJ64GP510A   |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ OW (Full module support)

**Files added:**

+ [assembly.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/common/include/assembly.h)
+ [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/CMakeLists.txt)
+ [./common/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/common/CMakeLists.txt)
+ [./core/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/core/CMakeLists.txt)
+ [./dspic/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/CMakeLists.txt)
+ [./dspic/src/adc/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/adc/CMakeLists.txt)
+ [./dspic/src/gpio/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/CMakeLists.txt)
+ [./dspic/src/hal_ll/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/hal_ll/CMakeLists.txt)
+ [./dspic/src/i2c/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/i2c/CMakeLists.txt)
+ [./dspic/src/one_wire/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/one_wire/CMakeLists.txt)
+ [./dspic/src/pps/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/pps/CMakeLists.txt)
+ [./dspic/src/spi_master/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/spi_master/CMakeLists.txt)
+ [./dspic/src/tim/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/tim/CMakeLists.txt)
+ [./dspic/src/uart/CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/uart/CMakeLists.txt)
+ [common_macros.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/common/include/common_macros.h)
+ [hal_ll_adc.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/adc/implementation_1/hal_ll_adc.c)
+ [hal_ll_adc.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/adc/hal_ll_adc.h)
+ [hal_ll_analog_in_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/adc/hal_ll_analog_in_map.h)
+ [hal_ll_bit_control.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/common/include/hal_ll_bit_control.h)
+ [hal_ll_core.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/core/src/hal_ll_core.c)
+ [hal_ll_core.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/core/include/hal_ll_core.h)
+ [hal_ll_core_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/core/include/hal_ll_core_defines.h)
+ [hal_ll_core_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/core/include/hal_ll_core_port.h)
+ [hal_ll_gpio.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c)
+ [hal_ll_gpio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h)
+ [hal_ll_gpio_constants.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_constants.h)
+ [hal_ll_gpio_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)
+ [hal_ll_gpio_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h)
+ [hal_ll_i2c_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/i2c/implementation_1/hal_ll_i2c_master.c)
+ [hal_ll_i2c_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/i2c/hal_ll_i2c_master.h)
+ [hal_ll_i2c_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/i2c/hal_ll_i2c_pin_map.h)
+ [hal_ll_odcon_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/hal_ll_odcon_map.h)
+ [hal_ll_one_wire.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/one_wire/hal_ll_one_wire.c)
+ [hal_ll_one_wire.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/one_wire/hal_ll_one_wire.h)
+ [hal_ll_pin_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/hal_ll_pin_names.h)
+ [hal_ll_pps.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/pps/hal_ll_pps.c)
+ [hal_ll_pps.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps.h)
+ [./HAL_LL_PPS_DEFAULT/hal_ll_pps_connection_defs.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps_connection_defs/HAL_LL_PPS_DEFAULT/hal_ll_pps_connection_defs.h)
+ `./mcu_name/hal_ll_pps_connection_defs.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps_connection_defs/mcu_name/hal_ll_pps_connection_defs.h`
  + Added for MCUs with PPS modules only where mcu_name is actual chip full name, i.e. `dsPIC33EP512MU814` etc.
+ [hal_ll_pps_defines.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps_defines.h)
+ [hal_ll_pps_port.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/pps/implementation_1/hal_ll_pps_port.c)
+ [hal_ll_pps_port.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps_port.h)
+ [hal_ll_pps_struct_def.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/pps/hal_ll_pps_connection_defs/hal_ll_pps_struct_def.h)
+ [hal_ll_slrcon_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/hal_ll_slrcon_map.h)
+ [hal_ll_spi_master.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/spi_master/implementation_1/hal_ll_spi_master.c)
+ [hal_ll_spi_master.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/spi_master/hal_ll_spi_master.h)
+ [hal_ll_spi_master_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/spi_master/hal_ll_spi_master_pin_map.h)
+ [hal_ll_target.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/hal_ll_target.h)
+ [hal_ll_target_names.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/hal_ll_target_names.h)
+ [hal_ll_tim.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/tim/implementation_1/hal_ll_tim.c)
+ [hal_ll_tim.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/tim/hal_ll_tim.h)
+ [hal_ll_tim_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/tim/hal_ll_tim_pin_map.h)
+ [hal_ll_uart.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/uart/implementation_1/hal_ll_uart.c)
+ [hal_ll_uart.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/uart/hal_ll_uart.h)
+ [hal_ll_uart_pin_map.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/uart/hal_ll_uart_pin_map.h)
+ `./mcu_name/mcu_definitions.h` - `https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/common/include/mcu_definitions/mcu_name/mcu_definitions.h`
  + Added for all MCUs in mikroSDK where mcu_name is actual chip full name, i.e. `dsPIC30F4013` etc.

### <font color=red>GCC ARM</font>

+ As of mikroSDK version `2.8.0`, `GCC ARM v10.2` is officially supported.
+ All **`1394`** ARM MCUs can now be used with the GCC toolchain along with full mikroSDK functionality.
+ Linker scripts and startup files are included upon selecting adequate setup for your project so it can be easily edited on the fly.

### New Features

+ Plot logger added
  + User is now able to log data to NECTO chart GUI
+ File System structure added to mikroSDK
  + Module imported from <http://elm-chan.org/fsw/ff/doc/appnote.html>
  + Files added:
    + [00history.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/00history.txt)
    + [00readme.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/00readme.txt)
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/CMakeLists.txt)
    + [dir.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/src/dir.c)
    + [dir.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/include/dir.h)
    + [diskio.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/diskio.h)
    + [fatfs.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/src/fatfs.c)
    + [fatfs.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/include/fatfs.h)
    + [ff.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/ff.c)
    + [ff.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/ff.h)
    + [ff_types.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/include/ff_types.h)
    + [ffconf.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/include/ffconf.h)
    + [ffsystem.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/ffsystem.c)
    + [ffunicode.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/fat/FatFs/ffunicode.c)
    + [file.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/src/file.c)
    + [file.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/include/file.h)
    + [file_system.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/src/file_system.c)
    + [file_system.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/include/file_system.h)
    + [fs_common.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/filesystem/private/include/fs_common.h)
  + Added physical drive with sd spi implementation:
    + [CMakeLists.txt](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/CMakeLists.txt)
    + [pd_common.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/private/include/pd_common.h)
    + [physical_drive.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/src/physical_drive.c)
    + [physical_drive.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/include/physical_drive.h)
    + [sd_common.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/sd/include/sd_common.h)
    + [sdspi_physical_drive.c](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/sd/sdspi/src/sdspi_physical_drive.c)
    + [sdspi_physical_drive.h](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/middleware/physical_drive/sd/sdspi/include/sdspi_physical_drive.h)

### Improvements

+ Plot included implicitly with the LOG library
  + Can be included as a standalone library as well
+ All `DRIVER` and `HAL` close APIs now return an error code
+ Following APIs now return error code:
  + `digital_out_high`
  + `digital_out_low`
  + `digital_out_toggle`
  + `digital_out_write`
  + `port_init`
  + `port_write`
  + `port_read`
+ Added `port_read_input` and `port_read_output` APIs
  + Previous `port_read` is defined as `port_read_output` for backwards compatibility
+ SPI write APIs now have a generic pointer typecast for 8-bit archicecture compatibility
  + ROM and RAM pointers are not the same on 8-bit architectures
+ All `DRIVER` and `HAL` APIs have added checks for passed data validity
+ `./tests/pwm/main.c`
  + PWM test improved with multiple new cases
+ `./tests/CMakeLists.txt`
  + `gl` tests are now included only if setup has a display

### Fixes

+ Fixed PIC32MZ adc low level implementation
  + Setting internal VREF after previously setting external didn't work as bits in appropriate register werent cleared properly
+ Fixed all low level implementations for ARM MCUs to accommodate the release of GCC ARM toolchain
+ Fixed `uart_configure_default` API
  + `stop_bits` previosuly set incorrectly
+ `ring_buf8_init` previously used `sizeof( ring_buf8_t )` as last parameter which would delete all data starting from `buf` address all the way to the `sizeof( ring_buf8_t )` which could produce problems if `buf` was shorter than `sizeof( ring_buf8_t )`
  + Fixed to clear data starting from `buf` all the way up to the `capacity` of `buf`
+ `./targets/arm/mikroe/nxp/src/tim/implementation_1/hal_ll_tim.c`
  + Fixed issue with double frequency setting
    + Frequency is now set adequately
  + Fixed issue with inability to start the signal again after stopping it
+ `./targets/arm/mikroe/nxp/src/uart/implementation_2/hal_ll_uart.c`
  + Fixed adequate error setting when calculated baud difference is 1% or higher
+ `./targets/arm/mikroe/nxp/src/uart/CMakeLists.txt`
  + Adequate UART subimplemntation for `MK8x` MCUs is now propagated
+ `./targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c`
  + GPIO pins used for SWJTAG (debug mode) are now set in release build only, when debug is active these pins are not changed
    + This ensured uninterrupted debugging
+ All modules
  + Clock is now being set everytime before disabling the module and then being disabled again
    + This ensures proper module function without exceptions
+ `./targets/arm/mikroe/tiva/src/uart/implementation_1/hal_ll_uart.c`
  + Data frame is now being checked for errors, i.e. parity errors, data bit error etc.
    + If error is present, read API shall return 0 as actual data
  + Uart module is now disabled completely before changing any register state
+ `./targets/avr_8bit/mikroe/avr/src/tim/implementation_1/hal_ll_tim.c`
  + Fixed issue with inability to start the signal again after stopping it
+ `./targets/avr_8bit/mikroe/avr/src/tim/implementation_2/hal_ll_tim.c`
  + Fixed issue with inability to start the signal again after stopping it
+ `./targets/avr_8bit/mikroe/avr/src/tim/implementation_3/hal_ll_tim.c`
  + Fixed issue with inability to start the signal again after stopping it
+ `./targets/avr_8bit/mikroe/avr/src/uart/implementation_1/hal_ll_uart.c`
  + Fixed adequate error setting when calculated baud difference is 1% or higher
+ `./targets/avr_8bit/mikroe/avr/src/uart/implementation_2/hal_ll_uart.c`
  + Fixed adequate error setting when calculated baud difference is 1% or higher
+ `./targets/avr_8bit/mikroe/avr/src/i2c/implementation_1/hal_ll_i2c_master.c`
  + Fixed function for calculating I2C baud rate
+ `./targets/avr_8bit/mikroe/avr/src/adc/implementation_1/hal_ll_adc.c`
  + Fixed ADC channel selection for channels 8 to 15
+ `./targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c`
  + `hal_ll_gpio_port_index` API now returns adequate value
+ `./targets/riscv/mikroe/gigadevice/src/tim/implementation_1/hal_ll_tim.c`
  + Timer module can now be started again after stopping the signal

### NEW HARDWARE

Support added for following hardware:

+ [Easy24-33 v6](https://www.mikroe.com/easy24-33)
+ [EasyPIC v8 for dsPIC30](https://www.mikroe.com/easypic-v8-for-dspic30)
+ [EasyPIC v8 for PIC24/dsPIC33](https://www.mikroe.com/easypic-v8-for-pic24dspic33)
+ [EasyPIC v7 for dsPIC30](https://www.mikroe.com/easypic-dspic30)
+ [Clicker 2 for PIC24](https://www.mikroe.com/clicker-2-for-pic24)
+ [Clicker 2 for dsPIC33](https://www.mikroe.com/clicker-2-dspic33)
+ [mikromedia for PIC24](https://www.mikroe.com/mikromedia-3-pic24fj)
+ [mikromedia for PIC24EP](https://www.mikroe.com/mikromedia-3-pic24ep)
+ [mikromedia for dsPIC33](https://www.mikroe.com/mikromedia-3-dspic33fj)
+ [mikromedia for dsPIC33EP](https://www.mikroe.com/mikromedia-3-dspic33ep)
+ [Sibrain for dsPIC33EP512MU814](https://www.mikroe.com/sibrain-for-dspic33ep512mu814)
+ [Sibrain for dsPIC33FJ256GP710A](https://www.mikroe.com/sibrain-for-dspic33fj256gp710a)
+ [Sibrain for PIC24EP512GU814](https://www.mikroe.com/sibrain-for-pic24ep512gu814)
+ [Sibrain for PIC24HJ256GP610](https://www.mikroe.com/sibrain-for-pic24hj256gp610)
+ [EasyPIC Fusion v7 MCUcard with dsPIC33EP512MU810](https://www.mikroe.com/easypic-fusion-v7-dspic33ep512mu810)
+ [EasyPIC Fusion v7 MCUcard with dsPIC33FJ256GP710A](https://www.mikroe.com/easypic-fusion-v7-dspic33fj256gp710a)
+ [EasyPIC Fusion v7 MCUcard with PIC24EP512GU810](https://www.mikroe.com/easypic-fusion-v7-pic24ep512gu810)
+ [EasyPIC Fusion v7 MCUcard with PIC24FJ128GA310](https://www.mikroe.com/easypic-fusion-v7-pic24fj128ga310)
+ [PIC24FJ256GA7 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/dm240016)
+ [Curiosity PIC32MZ EF](https://www.microchip.com/en-us/development-tool/dm320209)
+ [Explorer 16/32 Development board](https://www.microchip.com/en-us/development-tool/dm240001-2)
  + [PIC24FJ64GB004 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/ma240019)
  + [PIC24FJ128GA310 PLUG-IN MODULE](https://www.microchip.com/en-us/development-tool/MA240029)
  + [PIC24F32KA304 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240022)
  + [PIC24F16KA102 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240017)
  + [PIC24EP512GU810 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240025-1)
  + [DSPIC33EP512MU810 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA330025-1)
  + [PIC24FJ256GB210 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240021)
  + [PIC24FJ64GB004 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240019)
  + [PIC24FJ64GA004 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240013)
  + [PIC24FJ256GB110 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA240014)
  + [DSPIC33EP256GP506 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA330030)
  + [PIC32MX250F128D PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320011)
  + [PIC32MX270F256D PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320014)
  + [PIC32MX360F512L PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320001)
  + [PIC32MX460F512L PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320002)
  + [PIC32MX795F512L PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320003)
  + [PIC32MX450/470 PLUG-IN-MODULE](https://www.microchip.com/en-us/development-tool/MA320002-2)
  + [PIC32MZ EF PIM](https://www.microchip.com/en-us/development-tool/MA320019)

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
