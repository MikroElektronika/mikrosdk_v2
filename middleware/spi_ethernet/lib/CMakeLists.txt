## ./middleware/spi_ethernet/lib/CMakeLists.txt
mikrosdk_add_library(lib_spi_ethernet MikroSDK.SpiEthernet
    src/spi_ethernet.c
    src/spi_ethernet_enc28j60.c

    include/spi_ethernet.h
    include/spi_ethernet_enc28j60.h
)

target_link_libraries(lib_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_spi_ethernet
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/spi_ethernet>
)

mikrosdk_install( MikroSDK.SpiEthernet)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/spi_ethernet MikroSDK.SpiEthernet include/spi_ethernet.h)
