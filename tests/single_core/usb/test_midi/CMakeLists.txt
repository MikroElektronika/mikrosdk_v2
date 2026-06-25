cmake_minimum_required(VERSION 3.17)

add_executable(test_midi
    main.c
    usb_descriptors.c
)

target_link_libraries(test_midi PUBLIC
    MikroC.Core
    MikroSDK.USB.Tiny
    MikroSDK.Board
)
