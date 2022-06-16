add_executable(test_click_magneto
    main.c
    magneto.c

    magneto.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_magneto PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_magneto
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
