## ./tests/spi_ethernet_two_wire/CMakeLists.txt
add_executable(test_spi_ethernet_two_wire
    main.c
    ReadMe.txt
)

target_link_libraries(test_spi_ethernet_two_wire PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Ethernet.Net
    MikroSDK.Ethernet.LAN8651
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.UART
    MikroSDK.Board
    MikroSDK.Log
)
