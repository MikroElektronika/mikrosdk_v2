## ./tests/freertos/counting_semaphore/CMakeLists.txt

add_executable(test_default_freertos_counting_semaphore
    main.c
    callbacks.c    
)

if (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_counting_semaphore PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_counting_semaphore PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART         
)
