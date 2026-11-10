## ./middleware/ethernet/net/CMakeLists.txt
mikrosdk_add_library(lib_eth_net MikroSDK.Ethernet.Net
    eth_net.c
    eth_net.h
)

target_include_directories(lib_eth_net
    PUBLIC
        .
)

## Protocol helpers only use the eth_transport_* API, no bus or controller dependency.
target_link_libraries(lib_eth_net PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
)
