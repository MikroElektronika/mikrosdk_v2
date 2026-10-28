mikrosdk_add_library(lib_lan9250 MikroSDK.Ethernet.LAN9250
    lan9250.c
    lan9250.h
)

target_include_directories(lib_lan9250
    PUBLIC
        .
)

target_link_libraries(lib_lan9250 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
