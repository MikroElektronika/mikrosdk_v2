## ./middleware/ethernet/core/CMakeLists.txt
mikrosdk_add_library(lib_eth_transport MikroSDK.Ethernet.Transport
    eth_transport.c
    eth_transport.h
)

target_include_directories(lib_eth_transport
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/middleware/ethernet>
)

target_link_libraries(lib_eth_transport PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.Transport)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ethernet MikroSDK.Ethernet.Transport eth_transport.h)
