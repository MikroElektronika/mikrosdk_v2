## ./targets/pic_32bit/mikroe/pic32/src/gpio/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN GPIO
if(${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 5 MCU_NAME_FIRST_5)
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    string(SUBSTRING ${MCU_NAME} 0 8 MCU_NAME_FIRST_8)
    string(SUBSTRING ${MCU_NAME} 0 10 MCU_NAME_FIRST_10)

    list(APPEND hal_ll_def_list ${MCU_NAME})
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_5}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_8}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_10}xx)

    list(APPEND hal_ll_def_list "__pic32__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

if(${MCU_NAME} MATCHES "(^PIC32MX[1-7][1-79][045]F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "__hal_ll_gpio_subset_1__")
    set(gpio_implementation "implementation_1/hal_ll_gpio.c")
    set(gpio_subimplementation "implementation_1/subimplementation_1/hal_ll_gpio_port.c")
    # Match PIC32MX MCUs where analog pins are set by clearing respective register bit
    if (${MCU_NAME} MATCHES "(^PIC32MX[34][246][0]F(032|064|128|256|512)[HL]$)|(^PIC32MX[567][3679][45]F(064|128|256|512)[HL]$)")
        list(APPEND hal_ll_def_list "MARK_AS_DIGITAL=set_reg_bit")
        list(APPEND hal_ll_def_list "MARK_AS_ANALOG=clear_reg_bit")
    # Match PIC32MZ and PIC32MX MCUs where analog pins are set by setting respective register bit
    elseif(${MCU_NAME} MATCHES "(^PIC32MX[12][12357][0]F(016|032|064|128|256)[BCD]B?$)|(^PIC32MX[34][357][0]F(064|128|256|512)[HL]B?$)|(^PIC32MX[125][2357][0]F(064|128|256|512)[HL]$)|(^PIC32MZ(0512|1024|2048)EF[E-HKM](064|100|124|144)$)")
        list(APPEND hal_ll_def_list "MARK_AS_DIGITAL=clear_reg_bit")
        list(APPEND hal_ll_def_list "MARK_AS_ANALOG=set_reg_bit")
    endif()
endif()
## END GPIO

## BEGIN PMD
if (${MCU_NAME} MATCHES "(^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "HAL_LL_PERIPHERAL_MODULE_DISABLE")
endif()
## END PMD

list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    ${gpio_implementation}
    ${gpio_subimplementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
##  BEGIN GPIO
    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/hal_ll_gpio_constants.h
##  END GPIO
)

target_compile_definitions(lib_hal_ll_gpio PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_gpio PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_gpio
    PRIVATE
        ../../include
        ../../include/gpio
        #BEGINADC
        ../../include/adc
        #ENDADC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.GPIO)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.GPIO ../../include/gpio/hal_ll_gpio.h ../../include/gpio/hal_ll_gpio_constants.h ../../include/gpio/hal_ll_gpio_port.h)
