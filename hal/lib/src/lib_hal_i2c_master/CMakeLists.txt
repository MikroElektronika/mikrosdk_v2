mikrosdk_add_library(lib_hal_i2c_master MikroSDK.Hal.I2C.Master
    hal_i2c_master.c

    ../../include/hal_i2c_master.h
)

target_link_libraries(lib_hal_i2c_master  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.I2C.Master
)

target_include_directories(lib_hal_i2c_master
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.I2C.Master)

install(
    FILES
        ../../include/hal_i2c_master.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal
)
