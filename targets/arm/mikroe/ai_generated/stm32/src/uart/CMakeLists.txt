## ./targets/arm/mikroe/ai_generated/stm32/src/uart/CMakeLists.txt

## Check if current module is generated or not
set(MODULE_IS_GENERATED false)
get_files_recurse(${CMAKE_CURRENT_LIST_DIR}/implementations CMAKE_FILES cmake)
check_if_module_is_generated(MODULE_IS_GENERATED "${CMAKE_FILES}")

## If current MCU has this module, add it
if(MODULE_IS_GENERATED)
    set(hal_ll_def_list "")
    set(mcu_header_path "")

    find_cortex(hal_ll_def_list)
    list(APPEND hal_ll_def_list ${MCU_NAME})
    set(mcu_header_path ${MCU_NAME}_${_MSDK_PACKAGE_ID_})

    ## BEGIN UART
    list(APPEND hal_ll_def_list "MACRO_USAGE_UART")

    ## i.e "if (${MCU_NAME} MATCHES "^STM32C011F6$|^STM32C011C6$")"
    ## List all MCUs and or them in the regex
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END UART

    mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
        ${rcc_subimplementation}/hal_ll_rcc.h
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
            # BEGIN RCC
            ${rcc_subimplementation}
            # END RCC
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            $<BUILD_INTERFACE:${rcc_subimplementation}>
            $<BUILD_INTERFACE:${uart_pin_map}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
            $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.UART)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.UART ../../include/uart/hal_ll_uart.h)
endif()
