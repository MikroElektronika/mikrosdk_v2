## ./tests/spi_ethernet/CMakeLists.txt
add_executable(test_spi_ethernet
    main.c
    ReadMe.txt
)

############################ test_spi_ethernet GENERATED CODE START ###########################
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Log)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroSDK.Driver)
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_spi_ethernet PUBLIC MikroC.Core)
############################ test_spi_ethernet GENERATED CODE END ###########################
target_link_libraries(test_spi_ethernet PUBLIC
    MikroC.Core
    MikroSDK.SpiEthernet
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
