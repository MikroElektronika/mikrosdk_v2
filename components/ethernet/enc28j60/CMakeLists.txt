mikrosdk_add_library(lib_enc28j60 MikroSDK.Ethernet.ENC28J60
    enc28j60.c
    enc28j60.h
)

target_include_directories(lib_enc28j60
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/components/ethernet>
)

target_link_libraries(lib_enc28j60 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.ENC28J60)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ethernet MikroSDK.Ethernet.ENC28J60 enc28j60.h)
