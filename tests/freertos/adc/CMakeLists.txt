## ./tests/freertos/adc/CMakeLists.txt

add_executable(test_default_freertos_adc
    main.c
    callbacks.c    
)

if( "${MCU_NAME}" MATCHES "^STM32L0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32F0(.+)$"  OR "${MCU_NAME}" MATCHES "^STM32G0(.+)$" )
     target_sources(test_default_freertos_adc PRIVATE util_without_handler.c)
elseif (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_adc PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_adc PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board   
    MikroSDK.Driver.ADC            
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.UART         
    MikroSDK.Conversions
)
