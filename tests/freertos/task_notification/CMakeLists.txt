## ./tests/freertos/task_notification/CMakeLists.txt

add_executable(test_default_freertos_task_notification
    main.c
    callbacks.c
    util.c
)

target_link_libraries(test_default_freertos_task_notification PUBLIC
    MikroC.Core
    lib_freertos   
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART        
)
