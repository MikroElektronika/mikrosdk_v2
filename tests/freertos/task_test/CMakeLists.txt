## ./tests/freertos/task_test/CMakeLists.txt

add_executable(test_default_freertos_task
    main.c
    util.c        
)

target_link_libraries(test_default_freertos_task PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART         
)