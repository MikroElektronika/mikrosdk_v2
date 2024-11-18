## ./targets/arm/mikroe/sam/src/one_wire/CMakeLists.txt
set(hal_ll_def_list)
set(mcu_header_path "")

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_ONE_WIRE")
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

if(${MCU_NAME} MATCHES "^ATSAME7.+")
    set(ow_subimplementation "implementations/implementation_1")
endif()

mikrosdk_add_library(lib_hal_ll_one_wire MikroSDK.HalLowLevel.OneWire
    ${ow_subimplementation}/hal_ll_one_wire.c

    ../../include/one_wire/${ow_subimplementation}/hal_ll_one_wire.h
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
        ../../include/gpio
        ../../include/gpio/${ow_subimplementation}
        ../../include/one_wire/${ow_subimplementation}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/${ow_subimplementation}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/one_wire/${ow_subimplementation}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
)

mikrosdk_install(MikroSDK.HalLowLevel.OneWire)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.OneWire ../../include/one_wire/${ow_subimplementation}/hal_ll_one_wire.h)
