## ./tests/spi_ethernet/CMakeLists.txt
add_executable(test_spi_ethernet
    main.c
    transport_select.h
    ReadMe.txt
)

target_link_libraries(test_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Ethernet.Net
    MikroSDK.Ethernet.ENC28J60
    MikroSDK.Ethernet.LAN8651
    MikroSDK.Ethernet.LAN9250
    MikroSDK.Ethernet.W5500
    MikroSDK.Ethernet.W6100
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.UART
    MikroSDK.Board
    MikroSDK.Log
)
