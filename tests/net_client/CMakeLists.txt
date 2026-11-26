## ./tests/net_client/CMakeLists.txt
## HTTP, SNTP and MQTT clients on the mikroSDK network layer (MIKROSDK_NET_STACK=LWIP);
## replaces the CycloneTCP HTTP client test (tests/ethernet/test_http_client).
add_executable(test_net_client
    main.c
    ReadMe.txt
)

target_link_libraries(test_net_client PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Net
)

## Network interface chosen in main.c (NET_INTERFACE), shared with net_web_server.
include(${CMAKE_CURRENT_SOURCE_DIR}/../net_common/net_test_interface.cmake)
net_test_link_interface(test_net_client ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
