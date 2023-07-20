## ./tests/clicks/one_wire/click_thermo_2/CMakeLists.txt
add_executable(test_click_thermo_2
    main.c
    thermo_2.c

    thermo_2.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_thermo_2 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
    MikroSDK.Conversions
)

target_include_directories(test_click_thermo_2
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
