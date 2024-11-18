## ./targets/arm/mikroe/sam/src/uart/CMakeLists.txt

set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)
list(APPEND hal_ll_def_list ${MCU_NAME})
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

## BEGIN UART
list(APPEND hal_ll_def_list "MACRO_USAGE_UART")
foreach(cmakeFile ${CMAKE_FILES})
    include(${cmakeFile})
endforeach()
## END UART

mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
    ${pmc_subimplementation}/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    # BEGIN UART
    ${uart_subimplementation}
    ../../include/uart/hal_ll_uart.h
    ${uart_pin_map}/hal_ll_uart_pin_map.h
    # END UART
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
        ${gpio_subimplementation_include_dir}
        # BEGIN UART
        ../../include/uart
        ${uart_pin_map}
        # END UART
        # BEGIN PMC
        ${pmc_subimplementation}
        # END PMC
    INTERFACE
        # BUILD
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart>
        $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
        $<BUILD_INTERFACE:${pmc_subimplementation}>
        $<BUILD_INTERFACE:${uart_pin_map}>
        # INSTALL
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.UART)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.UART ../../include/uart/hal_ll_uart.h)
