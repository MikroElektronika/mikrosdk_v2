## ./thirdparty/CMakeLists.txt
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(NOT AI_GENERATED_SDK)
        if(NOT(${TOOLCHAIN_ID} STREQUAL "mchp_xc16"))
            if(${MSDK_BUILD_TFT_MODULES})
                add_subdirectory(lvgl)
            endif()
        endif()
        add_subdirectory(usb)
    endif()
endif()

if(${TOOLCHAIN_ID} STREQUAL "gcc_arm_none_eabi" OR ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    if(NOT AI_GENERATED_SDK)
        check_eth_components(has_eth eth_module_list)
        if(${has_eth} STREQUAL "true")
            check_eth_requirements(memory_requirements_passed)
            if(${memory_requirements_passed} STREQUAL "true")
                add_subdirectory(ethernet)
            else()
                message(WARNING "${MCU_NAME} does not have enough memory for CycloneTCP")
            endif()
        endif()
    endif()
endif()

# ---------------------------------------------------------
# FreeRTOS kernel – for now only for gcc_arm_none_eabi,
# port = portable/GCC/ARM_CM4F (STM32F429ZI, Cortex-M4F)
# ---------------------------------------------------------

if(NOT AI_GENERATED_SDK)
    if(${TOOLCHAIN_ID} STREQUAL "gcc_arm_none_eabi")
        if(${MCU_NAME} STREQUAL "STM32F429ZI")
            add_subdirectory(FreeRTOS)
        endif()
    endif()
endif()
