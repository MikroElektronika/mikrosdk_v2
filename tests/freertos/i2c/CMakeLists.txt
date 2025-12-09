## ./tests/freertos/i2c/CMakeLists.txt

add_executable(test_default_freertos_i2c
    main.c
    callbacks.c 
)

if (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_i2c PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_i2c PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board               
    MikroSDK.Driver.GPIO.Out     
    MikroSDK.Driver.GPIO.In     
    MikroSDK.Driver.I2C.Master       
)
