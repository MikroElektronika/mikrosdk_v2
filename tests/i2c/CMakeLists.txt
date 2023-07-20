## ./tests/i2c/CMakeLists.txt
add_executable(test_default_i2c
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_i2c PUBLIC
    MikroC.Core
    MikroSDK.Driver.I2C.Master
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.In
    MikroSDK.Board
)
