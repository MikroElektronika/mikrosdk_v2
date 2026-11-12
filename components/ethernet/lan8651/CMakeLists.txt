mikrosdk_add_library(lib_lan8651 MikroSDK.Ethernet.LAN8651
    lan8651.c
    lan8651.h
)

target_include_directories(lib_lan8651
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/components/ethernet>
)

target_link_libraries(lib_lan8651 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.LAN8651)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ethernet MikroSDK.Ethernet.LAN8651 lan8651.h)
