## ./tests/net_web_server/CMakeLists.txt
## Web server on the mikroSDK network layer (MIKROSDK_NET_STACK=LWIP).
add_executable(test_net_web_server
    main.c
    ReadMe.txt
)

## The interface (NET_INTERFACE) and the SPI controller (SPI_ETH_CHIP) are chosen
## in main.c; link only what they need. Editing main.c re-runs configure.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/main.c net_if_line REGEX "^#define[ \t]+NET_INTERFACE[ \t]+NET_IF_[A-Z0-9_]+")
string(REGEX MATCH "NET_IF_([A-Z0-9_]+)" _ "${net_if_line}")
set(net_if ${CMAKE_MATCH_1})

target_link_libraries(test_net_web_server PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Net
)

if (net_if STREQUAL "SPI")
    file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/main.c spi_eth_chip_line REGEX "^#define[ \t]+SPI_ETH_CHIP[ \t]+SPI_ETH_CHIP_[A-Z0-9_]+")
    string(REGEX MATCH "SPI_ETH_CHIP_([A-Z0-9_]+)" _ "${spi_eth_chip_line}")
    set(spi_eth_chip ${CMAKE_MATCH_1})
    if (spi_eth_chip STREQUAL "WIZ_IP55")
        set(spi_eth_chip W5500)
    endif()
    if (NOT TARGET MikroSDK.Ethernet.${spi_eth_chip})
        message(FATAL_ERROR "test_net_web_server: unsupported SPI_ETH_CHIP \"${spi_eth_chip}\" in main.c")
    endif()
    target_link_libraries(test_net_web_server PUBLIC
        MikroSDK.Net.EthTransport
        MikroSDK.Ethernet.Transport
        MikroSDK.Ethernet.Spi
        MikroSDK.Ethernet.${spi_eth_chip}
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.SPI.Master
    )
    ## transport_select.h is shared with the eth_net test.
    target_include_directories(test_net_web_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../spi_ethernet)
elseif (net_if STREQUAL "PIC32MZ")
    if (NOT TARGET MikroSDK.Net.Pic32mz)
        message(FATAL_ERROR "test_net_web_server: NET_IF_PIC32MZ needs a PIC32MZ with Ethernet (${MCU_NAME})")
    endif()
    target_link_libraries(test_net_web_server PUBLIC
        MikroSDK.Net.Pic32mz
    )
elseif (net_if STREQUAL "STM32")
    if (NOT TARGET MikroSDK.Net.Stm32)
        message(FATAL_ERROR "test_net_web_server: NET_IF_STM32 needs an STM32 with Ethernet (${MCU_NAME})")
    endif()
    target_link_libraries(test_net_web_server PUBLIC
        MikroSDK.Net.Stm32
    )
else()
    message(FATAL_ERROR "test_net_web_server: unknown NET_INTERFACE \"${net_if}\" in main.c")
endif()

target_include_directories(test_net_web_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
