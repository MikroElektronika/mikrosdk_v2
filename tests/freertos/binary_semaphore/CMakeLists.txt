## ./tests/freertos/binary_semaphore/CMakeLists.txt

add_executable(test_default_freertos_binary_semaphore
    main.c
    util.c        
)

target_link_libraries(test_default_freertos_binary_semaphore PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.UART         
)
