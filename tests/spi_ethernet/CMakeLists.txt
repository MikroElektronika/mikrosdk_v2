## ./tests/spi_ethernet/CMakeLists.txt
add_executable(test_spi_ethernet
    main.c
    spi_ethernet_select.h
    ReadMe.txt
)

############################ test_spi_ethernet GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver.SPI.Master REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver.SPI.Master)
find_package(MikroSDK.Driver.UART REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver.UART)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Log)
############################ test_spi_ethernet GENERATED CODE END ###########################
target_link_libraries(test_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.Spi
    MikroSDK.Ethernet.ENC28J60
    MikroSDK.Ethernet.LAN9250
    MikroSDK.Ethernet.W5500
    MikroSDK.Ethernet.W6100
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
