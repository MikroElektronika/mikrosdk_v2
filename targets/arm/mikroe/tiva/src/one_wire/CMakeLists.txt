## ./targets/arm/mikroe/tiva/src/one_wire/CMakeLists.txt
set(hal_ll_def_list "")
list(APPEND hal_ll_def_list "MACRO_USAGE_ONE_WIRE")

mikrosdk_add_library(lib_hal_ll_one_wire MikroSDK.HalLowLevel.OneWire
    hal_ll_one_wire.c

    ../../include/one_wire/hal_ll_one_wire.h)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/one_wire>
        $<INSTALL_INTERFACE:include/hal_ll_port>
)

mikrosdk_install(MikroSDK.HalLowLevel.OneWire)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.OneWire ../../include/one_wire/hal_ll_one_wire.h)
