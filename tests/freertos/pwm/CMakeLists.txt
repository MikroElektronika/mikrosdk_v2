## ./tests/freertos/pwm/CMakeLists.txt

add_executable(test_default_freertos_pwm
    main.c
    callbacks.c
    util.c   
)

target_link_libraries(test_default_freertos_pwm PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.PWM     
)
