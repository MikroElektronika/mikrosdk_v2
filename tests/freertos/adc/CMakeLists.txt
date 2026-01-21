## ./tests/freertos/adc/CMakeLists.txt

add_executable(test_default_freertos_adc
    main.c
    callbacks.c
    util.c   
)

target_link_libraries(test_default_freertos_adc PUBLIC
    MikroC.Core
    lib_freertos   
    MikroSDK.Board   
    MikroSDK.Driver.ADC            
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.UART         
    MikroSDK.Conversions
)
