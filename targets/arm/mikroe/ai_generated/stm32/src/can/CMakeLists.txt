## ./targets/arm/mikroe/ai_generated/stm32/src/can/CMakeLists.txt

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
    set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_ID_}${_MSDK_PACKAGE_PIN_COUNT_})

    ## BEGIN CAN
    list(APPEND hal_ll_def_list "MACRO_USAGE_CAN")

    ## i.e "if (${MCU_NAME} MATCHES "^STM32C011F6$|^STM32C011C6$")"
    ## List all MCUs and or them in the regex
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END CAN

    mikrosdk_add_library(lib_hal_ll_can MikroSDK.HalLowLevel.CAN
        ${rcc_subimplementation}/hal_ll_rcc.h
        ../../include/hal_ll_target.h
        # BEGIN CAN
        ${can_subimplementation}
        ../../include/can/hal_ll_can.h
        ${can_pin_map}/hal_ll_can_pin_map.h
        # END CAN
    )

    target_compile_definitions(lib_hal_ll_can PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_can PUBLIC
        MikroC.Core
        MikroSDK.HalLowLevelCommon
    )

    string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
    target_include_directories(lib_hal_ll_can
        PRIVATE
            ../../include
            ../../include/gpio
            ${gpio_subimplementation_include_dir}
            # BEGIN CAN
            ../../include/can
            ${can_pin_map}
            # END CAN
            # BEGIN RCC
            ${rcc_subimplementation}
            # END RCC
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            $<BUILD_INTERFACE:${rcc_subimplementation}>
            $<BUILD_INTERFACE:${can_pin_map}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
            $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.CAN)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can.h)
endif()
