## ./targets/arm/mikroe/ai_generated/sam/src/i2c/CMakeLists.txt

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
    set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

    ## BEGIN I2C
    list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END I2C

    if (NOT DEFINED _MSDK_TFT_TP_)
        list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
    else()
        if (${_MSDK_TFT_TP_} MATCHES "__TP_TSC2003__")
            list(APPEND hal_ll_def_list "__TFT_RESISTIVE_TSC2003__")
        else()
            list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
        endif()
    endif()

    mikrosdk_add_library(lib_hal_ll_i2c_master MikroSDK.HalLowLevel.I2C.Master
        ${pmc_subimplementation}/hal_ll_pmc.h
        ../../include/hal_ll_target.h
        # BEGIN I2C
        ${i2c_subimplementation}
        ../../include/i2c/hal_ll_i2c_master.h
        ${i2c_pin_map}/hal_ll_i2c_pin_map.h
        # END I2C
    )

    target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_i2c_master PUBLIC
        MikroC.Core
        MikroSDK.HalLowLevelCore
        MikroSDK.HalLowLevelCommon
    )

    string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
    target_include_directories(lib_hal_ll_i2c_master
        PRIVATE
            ../../include
            ../../include/gpio
            ${gpio_subimplementation_include_dir}
            # BEGIN I2C
            ../../include/i2c
            ${i2c_pin_map}
            # END I2C
            # BEGIN PMC
            ${pmc_subimplementation}
            # END PMC
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            $<BUILD_INTERFACE:${pmc_subimplementation}>
            $<BUILD_INTERFACE:${i2c_pin_map}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
            $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.I2C.Master ../../include/i2c/hal_ll_i2c_master.h)
endif()
