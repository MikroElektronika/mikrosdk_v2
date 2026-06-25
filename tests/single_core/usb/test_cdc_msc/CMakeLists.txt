cmake_minimum_required(VERSION 3.17)

add_executable(test_cdc_msc
    main.c
    msc_disk.c
    usb_descriptors.c
)

target_link_libraries(test_cdc_msc PUBLIC
    MikroC.Core
    MikroSDK.USB.Tiny
    MikroSDK.Board
)
