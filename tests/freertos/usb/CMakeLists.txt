## ./tests/freertos/usb/CMakeLists.txt

add_executable(test_default_freertos_usb
    main.c
    callbacks.c
    msc_disk.c
    usb_descriptors.c
)

if(MCU_NAME MATCHES "^STM32.+$")
    target_sources(test_default_freertos_usb PRIVATE util.c)
endif()

target_link_libraries(test_default_freertos_usb PUBLIC
    MikroC.Core
    MikroSDK.FreeRTOSKernel      
    MikroSDK.Board              
    MikroSDK.USB.Tiny 
)
