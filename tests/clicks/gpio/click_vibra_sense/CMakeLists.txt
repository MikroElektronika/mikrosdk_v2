## ./tests/clicks/gpio/click_vibra_sense/CMakeLists.txt
add_executable(test_click_vibrasense
    main.c
    vibrasense.c

    vibrasense.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_vibrasense PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_vibrasense
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
