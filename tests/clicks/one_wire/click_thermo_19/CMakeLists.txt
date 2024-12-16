## ./tests/clicks/one_wire/click_thermo_19/CMakeLists.txt
add_executable(test_click_thermo_19
    main.c
    thermo19.c

    thermo19.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_thermo_19 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
    MikroSDK.Conversions
)

target_include_directories(test_click_thermo_19
    PRIVATE
        ../../test_specifics
        ../../../../platform/mikrobus/lib/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
