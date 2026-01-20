## ./tests/freertos/spi/CMakeLists.txt

add_executable(test_default_freertos_spi
    main.c
    callbacks.c
    util.c
)

target_link_libraries(test_default_freertos_spi PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board   
    MikroSDK.Driver.SPI.Master        
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.UART         
    MikroSDK.Conversions
)
