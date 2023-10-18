## ./tests/clicks/spi/click_oledc/CMakeLists.txt
add_executable(test_click_oledc
    main.c
    oledc.c

    oledc.h
    oledc_font.h
    oledc_image.h
    ../../test_specifics/pin_connections.h
)

target_link_libraries(test_click_oledc PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_oledc
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
