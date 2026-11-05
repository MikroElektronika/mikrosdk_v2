## ./middleware/ethernet/core/CMakeLists.txt
mikrosdk_add_library(lib_eth_transport MikroSDK.Ethernet.Transport
    eth_transport.c
    eth_transport.h
)

target_include_directories(lib_eth_transport
    PUBLIC
        .
)

target_link_libraries(lib_eth_transport PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
)
