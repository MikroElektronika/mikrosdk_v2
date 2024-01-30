## ./tests/can/can_rx/CMakeLists.txt
add_executable(test_can_rx
    main.c
    ../inc/can_test.h
)

target_include_directories(test_can_rx
PRIVATE
    ../inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
)

target_link_libraries(test_can_rx PUBLIC
    MikroC.Core
    MikroSDK.Driver.CAN
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
)
