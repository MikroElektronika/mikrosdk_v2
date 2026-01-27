## ./tests/freertos/usb/CMakeLists.txt

# Default util for ARM targets
set(TEST_UTIL_SOURCE ${CMAKE_CURRENT_LIST_DIR}/util_arm.c)

# PIC32 ports use Timer1 tick setup
if("${MCU_NAME}" MATCHES "^PIC32(MX|MZ).+$")
    set(TEST_UTIL_SOURCE ${CMAKE_CURRENT_LIST_DIR}/util_pic32.c)
endif()

add_executable(test_default_freertos_usb
    main.c
    callbacks.c
    msc_disk.c
    usb_descriptors.c
    ${TEST_UTIL_SOURCE}
)

target_link_libraries(test_default_freertos_usb PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board              
    MikroSDK.USB.Tiny 
)
