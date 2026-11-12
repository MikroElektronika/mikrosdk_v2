mikrosdk_add_library(lib_lan9250 MikroSDK.Ethernet.LAN9250
    lan9250.c
    lan9250.h
)

target_include_directories(lib_lan9250
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/components/ethernet>
)

target_link_libraries(lib_lan9250 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.LAN9250)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ethernet MikroSDK.Ethernet.LAN9250 lan9250.h)
