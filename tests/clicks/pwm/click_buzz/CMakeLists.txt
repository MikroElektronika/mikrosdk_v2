## ./tests/clicks/pwm/click_buzz/CMakeLists.txt
add_executable(test_click_buzz
    main.c
    buzz.c

    buzz.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_buzz PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_buzz
    PRIVATE
        ../../test_specifics
        ../../../../platform/mikrobus/lib/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
