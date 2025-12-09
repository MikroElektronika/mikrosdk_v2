## ./tests/freertos/sw_timer/CMakeLists.txt

add_executable(test_default_freertos_sw_timer
    main.c
    callbacks.c
)

if (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_sw_timer PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_sw_timer PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART        
)
