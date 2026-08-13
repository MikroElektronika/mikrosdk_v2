## ./middleware/ethernet/spi/CMakeLists.txt
mikrosdk_add_library(lib_spi_ethernet MikroSDK.Ethernet.Spi
    spi_ethernet.c
    spi_ethernet.h
)

target_include_directories(lib_spi_ethernet
    PUBLIC
        .
)

target_link_libraries(lib_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
