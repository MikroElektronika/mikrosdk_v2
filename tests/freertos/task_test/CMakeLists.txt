## ./tests/freertos/task_test/CMakeLists.txt

add_executable(test_default_freertos_task
    main.c
    callbacks.c
)

if( "${MCU_NAME}" MATCHES "^STM32L0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32F0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32G0(.+)$"  OR "${MCU_NAME}" MATCHES "^R7FA2E3(.+)$" OR "${MCU_NAME}" MATCHES "^R7FA4M3(.+)$")
     target_sources(test_default_freertos_task PRIVATE util_without_handler.c)
elseif (MCU_NAME MATCHES "^STM32.+$" OR "${MCU_NAME}" MATCHES "^R7FA.+$")
    target_sources(test_default_freertos_task PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_task PUBLIC
    MikroC.Core
    lib_freertos    
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.UART         
)