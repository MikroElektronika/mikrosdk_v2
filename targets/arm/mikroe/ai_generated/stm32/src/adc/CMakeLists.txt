## ./targets/arm/mikroe/ai_generated/stm32/src/adc/CMakeLists.txt

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

    ## BEGIN ADC
    list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")

    ## i.e "if (${MCU_NAME} MATCHES "^STM32C011F6$|^STM32C011C6$")"
    ## List all MCUs and or them in the regex
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END ADC

    mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
        ${rcc_subimplementation}/hal_ll_rcc.h
        ../../include/hal_ll_target.h
        # BEGIN ADC
        ${adc_subimplementation}
        ../../include/adc/hal_ll_adc.h
        ${adc_pin_map}/hal_ll_adc_pin_map.h
        # END ADC
    )

    target_compile_definitions(lib_hal_ll_adc PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_adc PUBLIC
        MikroC.Core
        MikroSDK.HalLowLevelCore
        MikroSDK.HalLowLevelCommon
    )

    string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
    target_include_directories(lib_hal_ll_adc
        PRIVATE
            ../../include
            ../../include/gpio
            ${gpio_subimplementation_include_dir}
            # BEGIN ADC
            ../../include/adc
            ${adc_pin_map}
            # END ADC
            # BEGIN RCC
            ${rcc_subimplementation}
            # END RCC
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            $<BUILD_INTERFACE:${rcc_subimplementation}>
            $<BUILD_INTERFACE:${adc_pin_map}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
            $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.ADC)

    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.ADC ../../include/adc/hal_ll_adc.h)
endif()
