## ./tests/spi_ethernet_two_wire/CMakeLists.txt
add_executable(test_spi_ethernet_two_wire
    main.c
    ReadMe.txt
)

############################ test_spi_ethernet_two_wire GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver.SPI.Master REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Driver.SPI.Master)
find_package(MikroSDK.Driver.UART REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Driver.UART)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(test_spi_ethernet_two_wire PUBLIC MikroSDK.Log)
############################ test_spi_ethernet_two_wire GENERATED CODE END ###########################
target_link_libraries(test_spi_ethernet_two_wire PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Transport
    MikroSDK.Ethernet.Spi
    MikroSDK.Ethernet.Net
    MikroSDK.Ethernet.LAN8651
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
