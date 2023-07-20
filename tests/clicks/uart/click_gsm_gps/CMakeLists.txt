## ./tests/clicks/uart/click_gsmgps/CMakeLists.txt
add_executable(test_click_gsmgps
    main.c
    gsmgps.c

    gsmgps.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_gsmgps PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
    MikroSDK.Conversions
)

target_include_directories(test_click_gsmgps
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
