set(hal_ll_def_list "")
set(MCU_NAME_FIRST_4 "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 4 MCU_NAME_FIRST_4)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_4})

if (${MCU_NAME} MATCHES "^MKV4[246]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV4X_RCC__")
elseif (${MCU_NAME} MATCHES "^MKV5[68]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV5X_RCC__")
elseif (${MCU_NAME} MATCHES "^MK[2568](.+)$")
    list(APPEND hal_ll_def_list "__MKX_RCC__")
endif()

# BEGIN UART
list(APPEND hal_ll_def_list "MACRO_USAGE_UART")

if (${MCU_NAME} MATCHES "^MKV(.+)$")
    list(APPEND hal_ll_def_list "HAL_LL_RCC_CLOCK_OUTPUT")
endif()

if (${MCU_NAME} MATCHES "^MK([V]|6[456])(.+)$")
    list(APPEND hal_ll_def_list "UART_STOP_BIT_NUMBER_SELECT")
endif()

if (${MCU_NAME} MATCHES "^MK8[02]FN256XXX15$")
    list(APPEND hal_ll_def_list "MK8xLPUART")
    set(uart_subimplementation "implementation_2/hal_ll_uart.c")
else()
    set(uart_subimplementation "implementation_1/hal_ll_uart.c")
endif()

set(uart_pin_map "hal_ll_uart_pin_map")
# END UART

mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
    ${uart_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
    #  BEGIN UART
    ../../include/uart/hal_ll_uart.h
    ../../include/uart/${uart_pin_map}/hal_ll_uart_pin_map.h
    #  END UART
)

target_compile_definitions(lib_hal_ll_uart PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_uart PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_uart
    PRIVATE
        ../../include
        ../../include/gpio
    #  BEGIN UART
        ../../include/uart
        ../../include/uart/${uart_pin_map}
    #  END UART
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart/${uart_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.UART)

install(
    FILES
        ../../include/uart/hal_ll_uart.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
