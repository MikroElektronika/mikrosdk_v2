## ./middleware/net/CMakeLists.txt
## mikroSDK network API (net_api.h, net_http.h) with lwIP behind it.
## Built when MIKROSDK_NET_STACK is "LWIP" (see middleware/CMakeLists.txt).

include(${PROJECT_SOURCE_DIR}/thirdparty/ethernet/lwip/lwip_sources.cmake)

## Network layer (about 30 KB of RAM with the defaults, see README.md).
## lwIP is compiled into this library and its headers stay
## private: applications only see net_api.h / net_http.h / net_driver.h.
mikrosdk_add_library(lib_net MikroSDK.Net
    include/net_api.h
    include/net_driver.h
    include/net_http.h
    include/net_http_server.h
    src/net_common.c
    src/net_http.c
    src/net_http_server.c
    src/net_lwip.c
    ${LWIP_SOURCES}
)

target_include_directories(lib_net
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/net>
    PRIVATE
        ${LWIP_INCLUDE_DIRS}
)

## Sizes (sockets, lwIP memory) can be tuned with compile definitions, e.g.
## -DNET_MAX_SOCKETS=6 or -DNET_LWIP_MEM_SIZE=16384 (see lwipopts.h, net_api.h).
target_link_libraries(lib_net PUBLIC
    MikroC.Core
)

## Default time source (net_config_t.now_ms) where the core has a cycle counter.
if (TARGET MikroSDK.Systime)
    target_link_libraries(lib_net PUBLIC MikroSDK.Systime)
    target_compile_definitions(lib_net PRIVATE NET_HAVE_SYSTIME)
endif()

mikrosdk_install(MikroSDK.Net)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net
    include/net_api.h
    include/net_driver.h
    include/net_http.h
    include/net_http_server.h
)

## Driver for the controllers of middleware/ethernet (eth_transport_* API).
mikrosdk_add_library(lib_net_eth_transport MikroSDK.Net.EthTransport
    adapters/eth_transport/net_driver_eth_transport.h
    adapters/eth_transport/net_driver_eth_transport.c
)

target_include_directories(lib_net_eth_transport
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/adapters/eth_transport>
        $<INSTALL_INTERFACE:include/middleware/net>
)

target_link_libraries(lib_net_eth_transport PUBLIC
    MikroC.Core
    MikroSDK.Net
    MikroSDK.Ethernet.Transport
)

mikrosdk_install(MikroSDK.Net.EthTransport)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.EthTransport
    adapters/eth_transport/net_driver_eth_transport.h
)

## Generic clause 22 PHY control over MDIO, used by the on-chip MAC drivers.
mikrosdk_add_library(lib_net_phy MikroSDK.Net.Phy
    drivers/phy/net_phy.h
    drivers/phy/net_phy.c
)

target_include_directories(lib_net_phy
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/phy>
        $<INSTALL_INTERFACE:include/middleware/net>
)

target_link_libraries(lib_net_phy PUBLIC
    MikroC.Core
)

mikrosdk_install(MikroSDK.Net.Phy)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Phy
    drivers/phy/net_phy.h
)

## On-chip MAC drivers, only for MCUs with an Ethernet controller.
check_eth_components(has_eth eth_module_list)
if(${has_eth} STREQUAL "true" AND ${MCU_NAME} MATCHES "^PIC32MZ")
    mikrosdk_add_library(lib_net_pic32mz MikroSDK.Net.Pic32mz
        drivers/pic32mz/net_driver_pic32mz.h
        drivers/pic32mz/net_driver_pic32mz.c
    )

    target_include_directories(lib_net_pic32mz
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/pic32mz>
            $<INSTALL_INTERFACE:include/middleware/net>
    )

    target_link_libraries(lib_net_pic32mz PUBLIC
        MikroC.Core
        MikroSDK.Net
        MikroSDK.Net.Phy
        MikroSDK.Driver.GPIO.Out
    )

    mikrosdk_install(MikroSDK.Net.Pic32mz)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Pic32mz
        drivers/pic32mz/net_driver_pic32mz.h
    )
endif()

## STM32F107, F2x7, F4x7/F4x9, F74x-F77x (the MCUs check_eth_components enables).
if(${has_eth} STREQUAL "true" AND ${MCU_NAME} MATCHES "^STM32F[1247]")
    string(SUBSTRING ${MCU_NAME} 6 1 stm32_family)    # STM32F4... -> 4
    mikrosdk_add_library(lib_net_stm32 MikroSDK.Net.Stm32
        drivers/stm32/net_driver_stm32.h
        drivers/stm32/net_driver_stm32.c
    )

    target_compile_definitions(lib_net_stm32 PRIVATE NET_STM32_F${stm32_family})
    ## Boards with TX_EN/TXD0/TXD1 on PG11/PG13/PG14 (as for CycloneTCP, cmake/ethUtils.cmake).
    if("${_MSDK_BOARD_NAME_}" MATCHES "^MIKROMEDIA(7|PLUS)FORSTM32(F4|F7)?")
        target_compile_definitions(lib_net_stm32 PRIVATE NET_STM32_TX_PG)
    endif()

    target_include_directories(lib_net_stm32
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/stm32>
            $<INSTALL_INTERFACE:include/middleware/net>
    )

    target_link_libraries(lib_net_stm32 PUBLIC
        MikroC.Core
        MikroSDK.Net
        MikroSDK.Net.Phy
        MikroSDK.Driver.GPIO.Out
        MikroSDK.HalLowLevel.GPIO
    )

    mikrosdk_install(MikroSDK.Net.Stm32)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Stm32
        drivers/stm32/net_driver_stm32.h
    )
endif()
