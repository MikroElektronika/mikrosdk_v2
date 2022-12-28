## ./tests/clicks/pwm/click_dc_motor_8/CMakeLists.txt
add_executable(test_click_dcmotor8
    main.c
    dcmotor8.c

    dcmotor8.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_dcmotor8 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_dcmotor8
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
