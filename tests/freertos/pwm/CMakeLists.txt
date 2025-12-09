## ./tests/freertos/pwm/CMakeLists.txt

add_executable(test_default_freertos_pwm
    main.c
    callbacks.c      
)

if (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_pwm PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_pwm PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.PWM     
)
