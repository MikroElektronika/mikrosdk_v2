mikrosdk_add_library(lib_enc28j60 MikroSDK.Ethernet.ENC28J60
    enc28j60.c
    enc28j60.h
)

target_include_directories(lib_enc28j60
    PUBLIC
        .
)

target_link_libraries(lib_enc28j60 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
