## ./tests/net_common/net_test_interface.cmake
## Shared by the network layer tests: links the network interface chosen in a
## test's main.c (NET_INTERFACE, and SPI_ETH_CHIP for NET_IF_SPI); the C side is
## net_test_interface.h.
##   include(${CMAKE_CURRENT_SOURCE_DIR}/../net_common/net_test_interface.cmake)
##   net_test_link_interface(<target> ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

set(NET_TEST_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR})

function(net_test_link_interface target main_c)
    ## The interface (NET_INTERFACE) and the SPI controller (SPI_ETH_CHIP) are chosen
    ## in main.c; link only what they need. Editing main.c re-runs configure.
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${main_c})
    file(STRINGS ${main_c} net_if_line REGEX "^#define[ \t]+NET_INTERFACE[ \t]+NET_IF_[A-Z0-9_]+")
    string(REGEX MATCH "NET_IF_([A-Z0-9_]+)" _ "${net_if_line}")
    set(net_if ${CMAKE_MATCH_1})

    if (net_if STREQUAL "SPI")
        file(STRINGS ${main_c} spi_eth_chip_line REGEX "^#define[ \t]+SPI_ETH_CHIP[ \t]+SPI_ETH_CHIP_[A-Z0-9_]+")
        string(REGEX MATCH "SPI_ETH_CHIP_([A-Z0-9_]+)" _ "${spi_eth_chip_line}")
        set(spi_eth_chip ${CMAKE_MATCH_1})
        if (spi_eth_chip STREQUAL "WIZ_IP55")
            set(spi_eth_chip W5500)
        endif()
        if (NOT TARGET MikroSDK.Ethernet.${spi_eth_chip})
            message(FATAL_ERROR "${target}: unsupported SPI_ETH_CHIP \"${spi_eth_chip}\" in main.c")
        endif()
        target_link_libraries(${target} PUBLIC
            MikroSDK.Net.EthTransport
            MikroSDK.Ethernet.Transport
            MikroSDK.Ethernet.Spi
            MikroSDK.Ethernet.${spi_eth_chip}
            MikroSDK.Driver.GPIO.Out
            MikroSDK.Driver.SPI.Master
        )
        ## transport_select.h is shared with the eth_net test.
        target_include_directories(${target} PRIVATE ${NET_TEST_COMMON_DIR}/../spi_ethernet)
    elseif (net_if STREQUAL "PIC32")
        if (NOT TARGET MikroSDK.Net.Pic32)
            message(FATAL_ERROR "${target}: NET_IF_PIC32 needs a PIC32MX/MZ with Ethernet (${MCU_NAME})")
        endif()
        target_link_libraries(${target} PUBLIC
            MikroSDK.Net.Pic32
        )
        if (${MCU_NAME} MATCHES "^PIC32MX")
            target_compile_definitions(${target} PRIVATE NET_EXAMPLE_PIC32MX)
        elseif (${MCU_NAME} MATCHES "^PIC32MZ.+(124|144)$")
            target_compile_definitions(${target} PRIVATE NET_EXAMPLE_PIC32MZ_144)
        endif()
    elseif (net_if STREQUAL "STM32")
        if (NOT TARGET MikroSDK.Net.Stm32)
            message(FATAL_ERROR "${target}: NET_IF_STM32 needs an STM32 with Ethernet (${MCU_NAME})")
        endif()
        target_link_libraries(${target} PUBLIC
            MikroSDK.Net.Stm32
        )
    elseif (net_if STREQUAL "KINETIS")
        if (NOT TARGET MikroSDK.Net.Kinetis)
            message(FATAL_ERROR "${target}: NET_IF_KINETIS needs a Kinetis MK6x / MKV58 (${MCU_NAME})")
        endif()
        target_link_libraries(${target} PUBLIC
            MikroSDK.Net.Kinetis
        )
    elseif (net_if STREQUAL "TM4C")
        if (NOT TARGET MikroSDK.Net.Tm4c)
            message(FATAL_ERROR "${target}: NET_IF_TM4C needs a TM4C129 (${MCU_NAME})")
        endif()
        target_link_libraries(${target} PUBLIC
            MikroSDK.Net.Tm4c
        )
    else()
        message(FATAL_ERROR "${target}: unknown NET_INTERFACE \"${net_if}\" in main.c")
    endif()

    target_include_directories(${target} PRIVATE ${NET_TEST_COMMON_DIR})
endfunction()
