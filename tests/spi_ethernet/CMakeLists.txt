## ./tests/spi_ethernet/CMakeLists.txt
add_executable(test_spi_ethernet
    main.c
    transport_select.h
    ReadMe.txt
)

## Link only the controller driver selected by SPI_ETH_CHIP in main.c.
## mikroC reserves RAM for every linked driver, so linking all of them
## does not fit on small MCUs. Editing main.c re-runs configure.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/main.c spi_eth_chip_line REGEX "^#define[ \t]+SPI_ETH_CHIP[ \t]+SPI_ETH_CHIP_[A-Z0-9_]+")
string(REGEX MATCH "SPI_ETH_CHIP_([A-Z0-9_]+)" _ "${spi_eth_chip_line}")
set(spi_eth_chip ${CMAKE_MATCH_1})
if (spi_eth_chip STREQUAL "WIZ_IP55")
    set(spi_eth_chip W5500)
endif()
if (NOT TARGET MikroSDK.Ethernet.${spi_eth_chip})
    message(FATAL_ERROR "test_spi_ethernet: unsupported SPI_ETH_CHIP \"${spi_eth_chip}\" in main.c")
endif()

target_link_libraries(test_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Ethernet.Net
    MikroSDK.Ethernet.${spi_eth_chip}
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.UART
    MikroSDK.Board
    MikroSDK.Log
)
