## ./middleware/net/CMakeLists.txt
## mikroSDK network API (net_api.h, net_http.h) with lwIP behind it.
## Built when MIKROSDK_NET_STACK is "LWIP" (see middleware/CMakeLists.txt).

include(${PROJECT_SOURCE_DIR}/thirdparty/ethernet/lwip/lwip_sources.cmake)

## Network layer. lwIP is compiled into this library and its headers stay
## private: applications only see net_api.h / net_http.h / net_driver.h.
mikrosdk_add_library(lib_net MikroSDK.Net
    include/net_api.h
    include/net_driver.h
    include/net_http.h
    src/net_common.c
    src/net_http.c
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

mikrosdk_install(MikroSDK.Net)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/net MikroSDK.Net
    include/net_api.h
    include/net_driver.h
    include/net_http.h
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
