## ./targets/arm/mikroe/ai_generated/stm32/src/rtc/CMakeLists.txt

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

    ## BEGIN RTC
    list(APPEND hal_ll_def_list "MACRO_USAGE_RTC")

    ## i.e "if (${MCU_NAME} MATCHES "^STM32C011F6$|^STM32C011C6$")"
    ## List all MCUs and or them in the regex
    foreach(cmakeFile ${CMAKE_FILES})
        include(${cmakeFile})
    endforeach()
    ## END RTC

    mikrosdk_add_library(lib_hal_ll_rtc MikroSDK.HalLowLevel.RTC
        ${rtc_subimplementation}
        ../../include/rtc/hal_ll_rtc.h
    )

    target_compile_definitions(lib_hal_ll_rtc PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_rtc PUBLIC
        MikroC.Core
        MikroSDK.HalInterface
        MikroSDK.HalLowLevelCommon
    )

    target_include_directories(lib_hal_ll_rtc
        PRIVATE
            ../../include/rtc/
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/rtc/>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.RTC)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.RTC ../../include/rtc/hal_ll_rtc.h)
endif()
