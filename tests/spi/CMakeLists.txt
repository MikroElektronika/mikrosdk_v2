## ./tests/spi/CMakeLists.txt
add_executable(test_default_spi
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_spi PUBLIC
    MikroC.Core
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
