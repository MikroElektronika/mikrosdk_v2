## ./targets/arm/mikroe/tiva/src/uart/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
endif()

# BEGIN UART
list(APPEND hal_ll_def_list "MACRO_USAGE_UART")
set(uart_subimplementation "implementation_1/hal_ll_uart.c")
set(uart_pin_map "hal_ll_uart_pin_map/implementation_1")
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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.UART ../../include/uart/hal_ll_uart.h)
