## ./middleware/ethernet/spi/CMakeLists.txt
mikrosdk_add_library(lib_eth_bus_spi MikroSDK.Ethernet.Spi
    eth_bus_spi.c
    eth_bus_spi.h
)

target_include_directories(lib_eth_bus_spi
    PUBLIC
        .
)

target_link_libraries(lib_eth_bus_spi PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
