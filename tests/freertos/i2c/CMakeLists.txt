## ./tests/freertos/i2c/CMakeLists.txt

add_executable(test_default_freertos_i2c
    main.c
    callbacks.c 
    util.c
)

target_link_libraries(test_default_freertos_i2c PUBLIC
    MikroC.Core
    lib_freertos      
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.I2C.Master       
)
