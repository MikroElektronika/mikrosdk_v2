## ./drv/lib/src/lib_drv_spi_master/CMakeLists.txt
mikrosdk_add_library(lib_drv_spi_master MikroSDK.Driver.SPI.Master
    drv_spi_master.c

    ../../include/drv_spi_master.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_spi_master  PUBLIC
    MikroC.Core
    MikroSDK.Hal.SPI.Master
)

target_include_directories(lib_drv_spi_master
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.SPI.Master ../../include/drv_spi_master.h)
