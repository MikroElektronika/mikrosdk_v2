## ./targets/arm/mikroe/ai_generated/stm32/src/one_wire/CMakeLists.txt

## Check if current module is generated or not
set(MODULE_IS_GENERATED true)

## If current MCU has this module, add it
if(MODULE_IS_GENERATED)
    set(hal_ll_def_list "")
    set(mcu_header_path "")

    find_cortex(hal_ll_def_list)
    list(APPEND hal_ll_def_list ${MCU_NAME})
    set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_ID_}${_MSDK_PACKAGE_PIN_COUNT_})

    list(APPEND hal_ll_def_list "MACRO_USAGE_ONE_WIRE")

    mikrosdk_add_library(lib_hal_ll_one_wire MikroSDK.HalLowLevel.OneWire
        hal_ll_one_wire.c
        ../../include/one_wire/hal_ll_one_wire.h
    )

    target_compile_definitions(lib_hal_ll_one_wire PUBLIC
        ${hal_ll_def_list}
    )

    target_link_libraries(lib_hal_ll_one_wire PUBLIC
        MikroC.Core
        MikroSDK.HalLowLevel.GPIO
        MikroSDK.HalLowLevelCommon
    )

    target_include_directories(lib_hal_ll_one_wire
        PRIVATE
            ../../include/one_wire
        INTERFACE
            # BUILD
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/one_wire>
            $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
            # INSTALL
            $<INSTALL_INTERFACE:include/hal_ll_port>
    )

    mikrosdk_install(MikroSDK.HalLowLevel.OneWire)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.OneWire ../../include/one_wire/hal_ll_one_wire.h)
endif()
