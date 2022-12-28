## ./tests/clicks/uart/click_samltouch/CMakeLists.txt
add_executable(test_click_samltouch
    main.c
    samltouch.c

    samltouch.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_samltouch PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
    MikroSDK.GenericPointer
    MikroSDK.Conversions
)

target_include_directories(test_click_samltouch
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
