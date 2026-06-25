## ./tests/clicks/i2c/click_altitude_3/CMakeLists.txt
add_executable(test_click_altitude3
    main.c
    altitude3.c

    altitude3.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_altitude3 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

if (${CMAKE_C_COMPILER} MATCHES "gcc")
    target_link_libraries(test_click_altitude3 PUBLIC
        m # Link GCC math library.
    )  
endif()

target_include_directories(test_click_altitude3
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
