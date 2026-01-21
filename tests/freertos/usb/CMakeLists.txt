## ./tests/freertos/usb/CMakeLists.txt

add_executable(test_default_freertos_usb
    main.c
    callbacks.c
    msc_disk.c
    usb_descriptors.c
    util.c
)

target_link_libraries(test_default_freertos_usb PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board              
    MikroSDK.USB.Tiny 
)
