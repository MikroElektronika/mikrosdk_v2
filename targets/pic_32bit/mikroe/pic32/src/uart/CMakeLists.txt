set(hal_ll_def_list "")

## BEGIN UART
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
    set(uart_implementation "implementation_1/hal_ll_uart.c")
endif()

if(${MCU_NAME} MATCHES "(^PIC32MX[34][246][0]F(032|064|128|256|512)[HL]$)")
    list(APPEND hal_ll_def_list "interrupt_case_1")
elseif(${MCU_NAME} MATCHES "(^PIC32MX(.+)$)")
    list(APPEND hal_ll_def_list "interrupt_case_2")
endif()
## END UART

## BEGIN PMD
if(${MCU_NAME} MATCHES "(^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "HAL_LL_PERIPHERAL_MODULE_DISABLE")
endif()
## END PMD

list(APPEND hal_ll_def_list "MACRO_USAGE_UART")

mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
    ${uart_implementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
##  BEGIN UART
    ../../include/uart/hal_ll_uart.h
    ../../include/uart/hal_ll_uart_pin_map.h
##  END UART
)

target_compile_definitions(lib_hal_ll_uart PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_uart PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevel.PPS
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_uart
    PRIVATE
    ../../include
##  BEGIN UART
    ../../include/uart
##  END UART
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.UART)

install(
    FILES
        ../../include/uart/hal_ll_uart.h
        ../../include/uart/hal_ll_uart_pin_map.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
