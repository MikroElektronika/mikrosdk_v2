## ./tests/clicks/pwm/click_button_y/CMakeLists.txt
add_executable(test_click_buttonlibrary
    main.c
    buttonlibrary.c

    buttonlibrary.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_buttonlibrary PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_buttonlibrary
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
