## ./middleware/ethernet/spi/CMakeLists.txt
mikrosdk_add_library(lib_eth_bus_spi MikroSDK.Ethernet.Spi
    eth_bus_spi.c
    eth_bus_spi.h
)

target_include_directories(lib_eth_bus_spi
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/middleware/ethernet>
)

target_link_libraries(lib_eth_bus_spi PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.Spi)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ethernet MikroSDK.Ethernet.Spi eth_bus_spi.h)
