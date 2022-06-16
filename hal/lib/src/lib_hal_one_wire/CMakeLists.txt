set(hal_def_list "")
mikrosdk_add_library(lib_hal_one_wire MikroSDK.Hal.OneWire
    hal_one_wire.c

    ../../include/hal_one_wire.h
)

if (${CMAKE_C_COMPILER} MATCHES "gcc")
    list(APPEND hal_def_list "TOOLCHAIN_ID_ONE_WIRE_SPECIFICS")
endif()

target_compile_definitions(lib_drv_one_wire  PUBLIC
    ${hal_def_list}
)

target_link_libraries(lib_hal_one_wire  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.OneWire
)

target_include_directories(lib_hal_one_wire
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.OneWire)

install(
    FILES
        ../../include/hal_one_wire.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal
)
