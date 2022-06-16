set(memory_issue_click_ambient_7 "")
set(memory_issue_click_force "")
set(memory_issue_click_hall_current_5 "")
set(memory_issue_click_pressure_12 "")
set(memory_issue_click_slider_2 "")
set(memory_issue "")

set(click_pic18_regex "(^PIC18F2455$|^PIC18F2458$|^PIC18F24J11$|^PIC18F24J50$|^PIC18F24K50$|^PIC18F2515$|^PIC18F2525$|^PIC18F2550$|^PIC18F2553$|^PIC18F2585$|^PIC18F25J11$|^PIC18F25J50$|^PIC18F25K40$|^PIC18F25K42$|^PIC18F25K50$|^PIC18F25K80$|^PIC18F2680$|^PIC18F2682$|^PIC18F2685$|^PIC18F26J11$|^PIC18F26J13$|^PIC18F26J50$|^PIC18F26J53$|^PIC18F26K40$|^PIC18F26K42$|^PIC18F4455$|^PIC18F4458$|^PIC18F44J11$|^PIC18F44J50$|^PIC18F4515$|^PIC18F4525$|^PIC18F4550$|^PIC18F4553$|^PIC18F4585$|^PIC18F45J11$|^PIC18F45J50$|^PIC18F45K22$|^PIC18F45K40$|^PIC18F45K42$|^PIC18F45K50$|^PIC18F45K80$|^PIC18F4680$|^PIC18F4682$|^PIC18F4685$|^PIC18F46J11$|^PIC18F46J13$|^PIC18F46J50$|^PIC18F46J53$|^PIC18F46K40$|^PIC18F46K42$|^PIC18F47Q10$|^PIC18F55K42$|^PIC18F56K42$|^PIC18F6520$|^PIC18F6525$|^PIC18F6527$|^PIC18F6585$|^PIC18F65J10$|^PIC18F65J11$|^PIC18F65J15$|^PIC18F65J50$|^PIC18F65J90$|^PIC18F65J94$|^PIC18F65K22$|^PIC18F65K40$|^PIC18F65K80$|^PIC18F65K90$|^PIC18F6680$|^PIC18F66J10$|^PIC18F66J94$|^PIC18F66K40$|^PIC18F67K40$|^PIC18F8520$|^PIC18F8525$|^PIC18F8527$|^PIC18F8585$|^PIC18F85J10$|^PIC18F85J11$|^PIC18F85J15$|^PIC18F85J50$|^PIC18F85J90$|^PIC18F85J94$|^PIC18F85K22$|^PIC18F85K90$|^PIC18F8680$|^PIC18F86J10$|^PIC18F86J94$|^PIC18F95J94$|^PIC18F96J94$|^PIC18LF2455$|^PIC18LF2458$|^PIC18LF24J11$|^PIC18LF24J50$|^PIC18LF24K50$|^PIC18LF2515$|^PIC18LF2525$|^PIC18LF2550$|^PIC18LF2553$|^PIC18LF2585$|^PIC18LF25J11$|^PIC18LF25J50$|^PIC18LF25K40$|^PIC18LF25K42$|^PIC18LF25K50$|^PIC18LF25K80$|^PIC18LF2680$|^PIC18LF2682$|^PIC18LF2685$|^PIC18LF26J11$|^PIC18LF26J13$|^PIC18LF26J50$|^PIC18LF26J53$|^PIC18LF26K40$|^PIC18LF26K42$|^PIC18LF4455$|^PIC18LF4458$|^PIC18LF44J11$|^PIC18LF44J50$|^PIC18LF4515$|^PIC18LF4525$|^PIC18LF4550$|^PIC18LF4553$|^PIC18LF4585$|^PIC18LF45J11$|^PIC18LF45J50$|^PIC18LF45K22$|^PIC18LF45K40$|^PIC18LF45K42$|^PIC18LF45K50$|^PIC18LF45K80$|^PIC18LF4680$|^PIC18LF4682$|^PIC18LF4685$|^PIC18LF46J11$|^PIC18LF46J13$|^PIC18LF46J50$|^PIC18LF46J53$|^PIC18LF46K40$|^PIC18LF46K42$|^PIC18LF55K42$|^PIC18LF56K42$|^PIC18LF6520$|^PIC18LF6527$|^PIC18LF65K40$|^PIC18LF65K80$|^PIC18LF66K40$|^PIC18LF67K40$|^PIC18LF8520$|^PIC18LF8527$|^PIC18LF8720$)")

# Ambient 7 Click
## ambient 7 click memory regex definitions by chip core
set(click_ambient_7_regex_stm32_m0 "(^STM32(([FGL]0(.+)[346])|(L072VZ)|(L073[RC][BZ])|(L073V[8BZ])|(L081[CK]Z))$)")
set(click_ambient_7_regex_stm32_m3 "(^STM32F10[0-3](.+)$)")
set(click_ambient_7_regex_stm32_m4 "(^STM32F(.+)[46]$)")
set(click_ambient_7_regex_stm32_m7 "(^ALL$)") ## All chips have enough memory
## EOF ambient 7 click memory regex definitions by chip core

## ambient 7 click memory issue boolean variable population
if ( ( ${MCU_NAME} MATCHES ${click_pic18_regex} ) OR ( ${MCU_NAME} MATCHES ${click_ambient_7_regex_stm32_m0} ) OR ( ${MCU_NAME} MATCHES ${click_ambient_7_regex_stm32_m3} ) OR ( ${MCU_NAME} MATCHES ${click_ambient_7_regex_stm32_m4} ) OR ( ${MCU_NAME} MATCHES ${click_ambient_7_regex_stm32_m7} ) )
    set(memory_issue_click_ambient_7 TRUE)
else()
    set(memory_issue_click_ambient_7 FALSE)
endif()
## EOF ambient 7 click memory issue boolean variable population
# EOF Ambient 7 Click

# Force Click
## force click memory regex definitions by chip core
set(click_force_regex_stm32_m0 "(^STM32(([FGL]0(.+)[346])|(L072VZ)|(L073[RC][BZ])|(L073V[8BZ])|(L081[CK]Z))$)")
set(click_force_regex_stm32_m3 "(^STM32F10[0-3](.+)$)")
set(click_force_regex_stm32_m4 "(^STM32F(.+)[46]$)")
set(click_force_regex_stm32_m7 "(^ALL$)") ## All chips have enough memory
## force click memory regex definitions by chip core

## force click memory issue boolean variable population
if ( ( ${MCU_NAME} MATCHES ${click_pic18_regex} ) OR ( ${MCU_NAME} MATCHES ${click_force_regex_stm32_m0} ) OR ( ${MCU_NAME} MATCHES ${click_force_regex_stm32_m3} ) OR ( ${MCU_NAME} MATCHES ${click_force_regex_stm32_m4} ) OR ( ${MCU_NAME} MATCHES ${click_force_regex_stm32_m7} ) )
    set(memory_issue_click_force TRUE)
else()
    set(memory_issue_click_force FALSE)
endif()
## EOF force memory issue boolean variable population
# EOF Force Click

# Hall Current 5 Click
## hall current 5 click memory regex definitions by chip core
set(click_hall_current_5_regex_stm32_m0 "(^STM32(([FGL]0(.+)[346])|(L072VZ)|(L073[RC][BZ])|(L073V[8BZ])|(L081[CK]Z))$)")
set(click_hall_current_5_regex_stm32_m3 "(^STM32F10[0-3](.+)$)")
set(click_hall_current_5_regex_stm32_m4 "(^STM32F(.+)[46]$)")
set(click_hall_current_5_regex_stm32_m7 "(^ALL$)") ## All chips have enough memory
## EOF hall current 5 click memory regex definitions by chip core

## hall current 5 click memory issue boolean variable population
if ( ( ${MCU_NAME} MATCHES ${click_pic18_regex} ) OR ( ${MCU_NAME} MATCHES ${click_hall_current_5_regex_stm32_m0} ) OR ( ${MCU_NAME} MATCHES ${click_hall_current_5_regex_stm32_m3} ) OR ( ${MCU_NAME} MATCHES ${click_hall_current_5_regex_stm32_m4} ) OR ( ${MCU_NAME} MATCHES ${click_hall_current_5_regex_stm32_m7} ) )
    set(memory_issue_click_hall_current_5 TRUE)
else()
    set(memory_issue_click_hall_current_5 FALSE)
endif()
## EOF hall current 5 click memory issue boolean variable population
# EOF Hall Current 5 Click

# Pressure 12 Click
## pressure 12 click memory regex definitions by chip core
set(click_pressure_12_regex_stm32_m0 "(^STM32(([FGL]0(.+)[346])|(L072VZ)|(L073[RC][BZ])|(L073V[8BZ])|(L081[CK]Z))$)")
set(click_pressure_12_regex_stm32_m3 "(^STM32F10[0-3](.+)$)")
set(click_pressure_12_regex_stm32_m4 "(^STM32F(.+)[46]$)")
set(click_pressure_12_regex_stm32_m7 "(^ALL$)") ## All chips have enough memory
## EOF pressure 12 click memory regex definitions by chip core

## pressure 12 click memory issue boolean variable population
if ( ( ${MCU_NAME} MATCHES ${click_pic18_regex} ) OR ( ${MCU_NAME} MATCHES ${click_pressure_12_regex_stm32_m0} ) OR ( ${MCU_NAME} MATCHES ${click_pressure_12_regex_stm32_m3} ) OR ( ${MCU_NAME} MATCHES ${click_pressure_12_regex_stm32_m4} ) OR ( ${MCU_NAME} MATCHES ${click_pressure_12_regex_stm32_m7} ) )
    set(memory_issue_click_pressure_12 TRUE)
else()
    set(memory_issue_click_pressure_12 FALSE)
endif()
## EOF pressure 12 click memory issue boolean variable population
# EOF Pressure 12 Click

# Slider 2 Click
## slider 2 click memory regex definitions by chip core
set(click_slider_2_regex_stm32_m0 "(^STM32(([FGL]0(.+)[346])|(L072VZ)|(L073[RC][BZ])|(L073V[8BZ])|(L081[CK]Z))$)")
set(click_slider_2_regex_stm32_m3 "(^STM32F10[0-3](.+)$)")
set(click_slider_2_regex_stm32_m4 "(^STM32F(.+)[46]$)")
set(click_slider_2_regex_stm32_m7 "(^ALL$)") ## All chips have enough memory
## EOF slider 2 memory regex definitions by chip core

## slider 2 click memory issue boolean variable population
if ( ( ${MCU_NAME} MATCHES ${click_pic18_regex} ) OR ( ${MCU_NAME} MATCHES ${click_slider_2_regex_stm32_m0} ) OR ( ${MCU_NAME} MATCHES ${click_slider_2_regex_stm32_m3} ) OR ( ${MCU_NAME} MATCHES ${click_slider_2_regex_stm32_m4} ) OR ( ${MCU_NAME} MATCHES ${click_slider_2_regex_stm32_m7} ) )
    set(memory_issue_click_slider_2 TRUE)
else()
    set(memory_issue_click_slider_2 FALSE)
endif()
## EOF slider 2 click memory issue boolean variable population
# EOF Slider 2 Click

## CUSTOM EXAMPLES
if ( ${MCU_NAME} MATCHES "TODO" )
    set(memory_issue TRUE)
else()
    set(memory_issue FALSE)
endif()
## EOF CUSTOM EXAMPLES

if (${memory_issue_click_ambient_7} STREQUAL "FALSE")
    add_subdirectory(click_ambient_7)
else()
    add_subdirectory(click_ambient_7/not_enough_memory)
endif()

if (${memory_issue_click_force} STREQUAL "FALSE")
    add_subdirectory(click_force)
else()
    add_subdirectory(click_force/not_enough_memory)
endif()

if (${memory_issue_click_hall_current_5} STREQUAL "FALSE")
    add_subdirectory(click_hall_current_5)
else()
    add_subdirectory(click_hall_current_5/not_enough_memory)
endif()

if (${memory_issue_click_pressure_12} STREQUAL "FALSE")
    add_subdirectory(click_pressure_12)
else()
    add_subdirectory(click_pressure_12/not_enough_memory)
endif()

if (${memory_issue_click_slider_2} STREQUAL "FALSE")
    add_subdirectory(click_slider_2)
else()
    add_subdirectory(click_slider_2/not_enough_memory)
endif()

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
