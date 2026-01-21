## ./tests/freertos/uart/CMakeLists.txt

add_executable(test_default_freertos_uart
    main.c
    callbacks.c
    util.c
)

target_link_libraries(test_default_freertos_uart PUBLIC
    MikroC.Core
    lib_freertos    
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART   
)
