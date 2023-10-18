## ./tests/clicker_buttons/CMakeLists.txt
add_executable(test_clicker_buttons
    src/main.c
    inc/clicker_buttons.h
    ReadMe.txt
)

target_include_directories(test_clicker_buttons
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_clicker_buttons PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
