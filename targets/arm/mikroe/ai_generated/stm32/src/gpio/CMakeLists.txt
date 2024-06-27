## ./targets/arm/mikroe/ai_generated/stm32/src/gpio/CMakeLists.txt

## Check if current module is generated or not
set(MODULE_IS_GENERATED false)
get_files_recurse(${CMAKE_CURRENT_LIST_DIR}/implementations CMAKE_FILES cmake)
check_if_module_is_generated(MODULE_IS_GENERATED "${CMAKE_FILES}")

## If current MCU has this module, add it
if(MODULE_IS_GENERATED)
    set(hal_ll_def_list "")
    set(MEMAKE_MCU_NAME_FIRST_7 "")
    set(mcu_header_path "")

    find_cortex(hal_ll_def_list)
    list(APPEND hal_ll_def_list ${MCU_NAME})
    set(mcu_header_path ${MCU_NAME}_${_MSDK_PACKAGE_ID_})

    ## BEGIN GPIO
    list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")

    ## i.e "if (${MCU_NAME} MATCHES "^STM32C011F6$|^STM32C011C6$")"
    ## List all MCUs and or them in the regex
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END GPIO

    mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
        ${rcc_subimplementation}/hal_ll_rcc.h
        ../../include/hal_ll_target.h
        # BEGIN GPIO
        hal_ll_gpio.c
        ${gpio_subimplementation}
        ../../include/gpio/hal_ll_gpio.h
        ../../include/gpio/hal_ll_gpio_port.h
        ${gpio_subimplementation_include_dir}/hal_ll_gpio_constants.h
        ${gpio_subimplementation_include_dir}/hal_ll_gpio_struct_type.h
        # END GPIO

    )

    target_compile_definitions(lib_hal_ll_gpio PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_gpio PUBLIC
        MikroC.Core
        MikroSDK.HalLowLevelCore
        MikroSDK.HalLowLevelCommon
    )

    string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
    target_include_directories(lib_hal_ll_gpio
        PRIVATE
            ../../include
            # BEGIN GPIO
            ../../include/gpio
            ${gpio_subimplementation_include_dir}
            # END GPIO
            # BEGIN RCC
            ${rcc_subimplementation}
            # END RCC
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            $<BUILD_INTERFACE:${rcc_subimplementation}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
            $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.GPIO)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.GPIO ../../include/gpio/hal_ll_gpio.h ${gpio_subimplementation_include_dir}/hal_ll_gpio_constants.h ${gpio_subimplementation_include_dir}/hal_ll_gpio_struct_type.h ../../include/gpio/hal_ll_gpio_port.h)
endif()
