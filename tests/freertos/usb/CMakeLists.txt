## ./tests/freertos/usb/CMakeLists.txt

add_executable(test_default_freertos_usb
    main.c
    callbacks.c
    msc_disk.c
    usb_descriptors.c
)

if( "${MCU_NAME}" MATCHES "^STM32L0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32F0(.+)$" OR "${MCU_NAME}" MATCHES "^STM32G0(.+)$" )
     target_sources(test_default_freertos_usb PRIVATE util_without_handler.c)
elseif (MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_usb PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_usb PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board              
    MikroSDK.USB.Tiny 
)
