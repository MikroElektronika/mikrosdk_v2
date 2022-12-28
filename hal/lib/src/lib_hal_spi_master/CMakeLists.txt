## ./hal/lib/src/lib_hal_spi_master/CMakeLists.txt
mikrosdk_add_library(lib_hal_spi_master MikroSDK.Hal.SPI.Master
    hal_spi_master.c

    ../../include/hal_spi_master.h
)

target_link_libraries(lib_hal_spi_master  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.SPI.Master
    MikroSDK.Hal.GPIO
)

target_include_directories(lib_hal_spi_master
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.SPI.Master ../../include/hal_spi_master.h)
