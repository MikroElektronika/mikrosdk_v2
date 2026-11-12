mikrosdk_add_library(lib_w6100 MikroSDK.Ethernet.W6100
    w6100.c
    w6100.h
)

target_include_directories(lib_w6100
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/components/ethernet>
)

target_link_libraries(lib_w6100 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.W6100)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ethernet MikroSDK.Ethernet.W6100 w6100.h)
