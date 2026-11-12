mikrosdk_add_library(lib_w5500 MikroSDK.Ethernet.W5500
    w5500.c
    w5500.h
)

target_include_directories(lib_w5500
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/components/ethernet>
)

target_link_libraries(lib_w5500 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.GPIO.Out
)

mikrosdk_install(MikroSDK.Ethernet.W5500)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ethernet MikroSDK.Ethernet.W5500 w5500.h)
