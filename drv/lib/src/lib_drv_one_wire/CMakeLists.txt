mikrosdk_add_library(lib_drv_one_wire MikroSDK.Driver.OneWire
    drv_one_wire.c

    ../../include/drv_one_wire.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_one_wire  PUBLIC
    MikroC.Core
    MikroSDK.Hal.OneWire
)

target_include_directories(lib_drv_one_wire
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.OneWire)

install(
    FILES
        ../../include/drv_one_wire.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/drv
)
