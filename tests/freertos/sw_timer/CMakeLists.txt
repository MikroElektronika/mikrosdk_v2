## ./tests/freertos/sw_timer/CMakeLists.txt

add_executable(test_default_freertos_sw_timer
    main.c
    callbacks.c
    util.c
)

target_link_libraries(test_default_freertos_sw_timer PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART        
)
