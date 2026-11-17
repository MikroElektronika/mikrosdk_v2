## ./middleware/ethernet/net/CMakeLists.txt
mikrosdk_add_library(lib_eth_net MikroSDK.Ethernet.Net
    eth_net.c
    eth_net.h
)

target_include_directories(lib_eth_net
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/middleware/ethernet>
)

## Protocol helpers only use the eth_transport_* API, no bus or controller dependency.
target_link_libraries(lib_eth_net PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
)

mikrosdk_install(MikroSDK.Ethernet.Net)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ethernet MikroSDK.Ethernet.Net eth_net.h)
