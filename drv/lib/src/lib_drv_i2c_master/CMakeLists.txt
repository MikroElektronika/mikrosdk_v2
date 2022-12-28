## ./drv/lib/src/lib_drv_i2c_master/CMakeLists.txt
mikrosdk_add_library(lib_drv_i2c_master MikroSDK.Driver.I2C.Master
    drv_i2c_master.c

    ../../include/drv_i2c_master.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_i2c_master  PUBLIC
    MikroC.Core
    MikroSDK.Hal.I2C.Master
)

target_include_directories(lib_drv_i2c_master
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.I2C.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.I2C.Master ../../include/drv_i2c_master.h)
