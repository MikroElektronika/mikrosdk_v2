## ./tests/mikrobus/blink/CMakeLists.txt
add_executable(test_mikrobus_blink
    src/main.c
    inc/mbus_count.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_blink
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_blink PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
