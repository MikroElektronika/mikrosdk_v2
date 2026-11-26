## ./tests/net_web_server/CMakeLists.txt
## Web server on the mikroSDK network layer (MIKROSDK_NET_STACK=LWIP, the default).
add_executable(test_net_web_server
    main.c
    ReadMe.txt
)

target_link_libraries(test_net_web_server PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Net
)

## Network interface chosen in main.c (NET_INTERFACE), shared with net_http_client.
include(${CMAKE_CURRENT_SOURCE_DIR}/../net_common/net_test_interface.cmake)
net_test_link_interface(test_net_web_server ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

target_include_directories(test_net_web_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
