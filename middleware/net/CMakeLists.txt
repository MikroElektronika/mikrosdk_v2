## ./middleware/net/CMakeLists.txt
## mikroSDK network API (net_api.h, net_http.h) with lwIP behind it.
## Built when MIKROSDK_NET_STACK is "LWIP" (the default, see middleware/CMakeLists.txt).

include(${PROJECT_SOURCE_DIR}/thirdparty/ethernet/lwip/lwip_sources.cmake)

## Network layer (about 30 KB of RAM with the defaults, see README.md).
## lwIP is compiled into this library and its headers stay
## private: applications only see net_api.h / net_http.h / net_driver.h.
mikrosdk_add_library(lib_net MikroSDK.Net
    include/net_api.h
    include/net_driver.h
    include/net_http.h
    include/net_http_server.h
    include/net_sntp.h
    include/net_mqtt.h
    include/net_mdns.h
    src/net_common.c
    src/net_http.c
    src/net_http_server.c
    src/net_sntp.c
    src/net_mqtt.c
    src/net_mdns.c
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

## Size profile: lwIP buffers and sockets, compiled into this library. AUTO picks
## it from the MCU's RAM; RAM figures are measured on Cortex-M4 (README.md, Sizes).
##   SMALL   32-95 KB RAM:  4 receive buffers, 6 KB heap, 3 sockets  (~18 KB)
##   MEDIUM  96-255 KB RAM: 10 receive buffers, 10 KB heap, 4 sockets (~31 KB)
##   LARGE   256 KB RAM up: 16 receive buffers, 16 KB heap, 8 sockets, 4-segment TCP window (~48 KB)
## The definitions are PUBLIC: net_api.h (NET_MAX_SOCKETS ...) must see the same values.
set(MIKROSDK_NET_PROFILE "AUTO" CACHE STRING "Network layer size: AUTO, SMALL, MEDIUM or LARGE")
set_property(CACHE MIKROSDK_NET_PROFILE PROPERTY STRINGS AUTO SMALL MEDIUM LARGE)
set(net_profile ${MIKROSDK_NET_PROFILE})
if(net_profile STREQUAL "AUTO")
    if(NOT MCU_RAM)
        set(net_profile MEDIUM)
    elseif(${MCU_RAM} LESS 98304)
        set(net_profile SMALL)
    elseif(${MCU_RAM} LESS 262144)
        set(net_profile MEDIUM)
    else()
        set(net_profile LARGE)
    endif()
endif()
if(net_profile STREQUAL "SMALL")
    target_compile_definitions(lib_net PUBLIC NET_PROFILE_SMALL
        NET_LWIP_PBUF_POOL_SIZE=4 NET_LWIP_MEM_SIZE=6144 NET_MAX_SOCKETS=3 NET_UDP_QUEUE_LEN=2)
elseif(net_profile STREQUAL "LARGE")
    target_compile_definitions(lib_net PUBLIC NET_PROFILE_LARGE
        NET_LWIP_PBUF_POOL_SIZE=16 NET_LWIP_MEM_SIZE=16384 NET_MAX_SOCKETS=8
        NET_LWIP_TCP_WND=5840 NET_LWIP_TCP_SND_BUF=5840)
elseif(net_profile STREQUAL "MEDIUM")
    target_compile_definitions(lib_net PUBLIC NET_PROFILE_MEDIUM)     # lwipopts.h / net_api.h defaults
else()
    message(FATAL_ERROR "MIKROSDK_NET_PROFILE must be AUTO, SMALL, MEDIUM or LARGE, not \"${MIKROSDK_NET_PROFILE}\".")
endif()
message(STATUS "MikroSDK.Net: ${net_profile} profile for ${MCU_NAME}")

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
    include/net_sntp.h
    include/net_mqtt.h
    include/net_mdns.h
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

## On-chip MAC drivers, only for MCUs with an Ethernet controller and 48 KB of RAM
## (their DMA buffers take 15-19 KB next to lwIP; CycloneTCP had the same limit on XC32).
check_eth_components(has_eth eth_module_list)
if(MCU_RAM AND (${MCU_RAM} LESS 49152))
    set(has_eth "false")
endif()
if(${has_eth} STREQUAL "true" AND ${MCU_NAME} MATCHES "^PIC32M[XZ]")   # PIC32MX 6xx/7xx, PIC32MZ EF
    mikrosdk_add_library(lib_net_pic32 MikroSDK.Net.Pic32
        drivers/pic32/net_driver_pic32.h
        drivers/pic32/net_driver_pic32.c
    )

    target_include_directories(lib_net_pic32
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/pic32>
            $<INSTALL_INTERFACE:include/middleware/net>
    )

    target_link_libraries(lib_net_pic32 PUBLIC
        MikroC.Core
        MikroSDK.Net
        MikroSDK.Net.Phy
        MikroSDK.Driver.GPIO.Out
    )

    mikrosdk_install(MikroSDK.Net.Pic32)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Pic32
        drivers/pic32/net_driver_pic32.h
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

## NXP Kinetis MK6x and MKV58 (the MCUs check_eth_components enables). MK61 / MK63
## (K60 / K64 variants, no CycloneTCP pin setup in hw_eth) use the K60/K64 wiring.
if(${has_eth} STREQUAL "true" AND ${MCU_NAME} MATCHES "^MK(6[0-6]|V58)")
    if(${MCU_NAME} MATCHES "^MKV58")
        set(kinetis_variant KV58)
    elseif(${MCU_NAME} MATCHES "^MK6[56]")
        set(kinetis_variant K65_K66)
    else()
        set(kinetis_variant K60_K64)
    endif()
    mikrosdk_add_library(lib_net_kinetis MikroSDK.Net.Kinetis
        drivers/kinetis/net_driver_kinetis.h
        drivers/kinetis/net_driver_kinetis.c
    )

    target_compile_definitions(lib_net_kinetis PRIVATE NET_KINETIS_${kinetis_variant})

    target_include_directories(lib_net_kinetis
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/kinetis>
            $<INSTALL_INTERFACE:include/middleware/net>
    )

    target_link_libraries(lib_net_kinetis PUBLIC
        MikroC.Core
        MikroSDK.Net
        MikroSDK.Net.Phy
        MikroSDK.Driver.GPIO.Out
    )

    mikrosdk_install(MikroSDK.Net.Kinetis)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Kinetis
        drivers/kinetis/net_driver_kinetis.h
    )
endif()

## TI TM4C129 with its integrated PHY (the MCUs check_eth_components enables).
if(${has_eth} STREQUAL "true" AND ${MCU_NAME} MATCHES "^TM4C129")
    mikrosdk_add_library(lib_net_tm4c MikroSDK.Net.Tm4c
        drivers/tm4c/net_driver_tm4c.h
        drivers/tm4c/net_driver_tm4c.c
    )

    target_include_directories(lib_net_tm4c
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/tm4c>
            $<INSTALL_INTERFACE:include/middleware/net>
    )

    target_link_libraries(lib_net_tm4c PUBLIC
        MikroC.Core
        MikroSDK.Net
        MikroSDK.Net.Phy
    )

    mikrosdk_install(MikroSDK.Net.Tm4c)
    install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net.Tm4c
        drivers/tm4c/net_driver_tm4c.h
    )
endif()
