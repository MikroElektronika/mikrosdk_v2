## ./tests/clicks/i2c/click_6dof_imu_11/CMakeLists.txt
add_executable(test_click_c6dofimu11
    main.c
    c6dofimu11.c

    c6dofimu11.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_c6dofimu11 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_c6dofimu11
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
