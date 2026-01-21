## ./tests/freertos/queue/CMakeLists.txt

add_executable(test_default_freertos_queue
    main.c
    callbacks.c
    util.c
)

target_link_libraries(test_default_freertos_queue PUBLIC
    MikroC.Core
    lib_freertos 
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART         
)
