## ./tests/freertos/queue/CMakeLists.txt

add_executable(test_default_freertos_queue
    main.c
    callbacks.c
)

if( "${MCU_NAME}" MATCHES "^STM32L0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32F0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32G0(.+)$" )
     target_sources(test_default_freertos_queue PRIVATE util_without_handler.c)
elseif (MCU_NAME MATCHES "^STM32.+$" OR "${MCU_NAME}" MATCHES "^R7FA.+$")
    target_sources(test_default_freertos_queue PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_queue PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART         
)
