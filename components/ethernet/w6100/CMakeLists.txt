mikrosdk_add_library(lib_w6100 MikroSDK.Ethernet.W6100
    w6100.c
    w6100.h
)

target_include_directories(lib_w6100
    PUBLIC
        .
)

target_link_libraries(lib_w6100 PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Spi
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
)
