mikrosdk_add_library(lib_w5500 MikroSDK.Ethernet.W5500
    w5500.c
    w5500.h
)

target_include_directories(lib_w5500
    PUBLIC
        .
)

target_link_libraries(lib_w5500 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
