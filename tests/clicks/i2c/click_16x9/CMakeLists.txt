## ./tests/clicks/i2c/click_16x9/CMakeLists.txt
add_executable(test_click_16x9
    main.c
    c16x9.c

    c16x9.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_16x9 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_16x9
    PRIVATE
        ../../test_specifics
        ../../../../platform/mikrobus/lib/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
