## ./tests/freertos/spi/CMakeLists.txt

add_executable(test_default_freertos_spi
    main.c
    callbacks.c
)

if (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_spi PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_spi PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board   
    MikroSDK.Driver.SPI.Master        
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.UART         
    MikroSDK.Conversions
)
