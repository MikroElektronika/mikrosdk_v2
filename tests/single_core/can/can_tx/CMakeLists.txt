## ./tests/can/can_tx/CMakeLists.txt
add_executable(test_can_tx
    main.c
    ../inc/can_test.h
)

target_include_directories(test_can_tx
PRIVATE
    ../inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
)

target_link_libraries(test_can_tx PUBLIC
    MikroC.Core
    MikroSDK.Driver.CAN
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
)
