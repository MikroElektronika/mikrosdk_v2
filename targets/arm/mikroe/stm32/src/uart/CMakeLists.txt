set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

## BEGIN UART
if ((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F1") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L1") OR
    (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F2") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F4"))
    set(uart_subimplementation "implementation_1/hal_ll_uart.c")
    set(uart_pin_map "hal_ll_uart_pin_map/implementation_1")
else()
    set(uart_subimplementation "implementation_2/hal_ll_uart.c")
    set(uart_pin_map "hal_ll_uart_pin_map/implementation_2")
endif()
## END UART

list(APPEND hal_ll_def_list "MACRO_USAGE_UART")

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
