cmake_minimum_required(VERSION 3.17)

add_executable(test_hid_generic_inout
    main.c
    usb_descriptors.c
)

target_link_libraries(test_hid_generic_inout PUBLIC
    MikroC.Core
    MikroSDK.USB.Tiny
    MikroSDK.Board
)
