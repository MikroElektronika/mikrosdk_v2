if (${TOOLCHAIN_ID} STREQUAL "mikrocpic")
    set(image_mode_only "IMAGE_MODE_ONLY")
endif()

add_executable(test_click_eink290inch
    main.c
    eink_290inch.c

    eink_290inch.h
    eINK_290_display_font.h
    eINK_290_display_image.h
    ../../test_specifics/pin_connections.h
)

target_compile_definitions(test_click_eink290inch PUBLIC
    ${image_mode_only}
)

target_link_libraries(test_click_eink290inch PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver
)

target_include_directories(test_click_eink290inch
PRIVATE
    ../../test_specifics
    ../../../../platform/mikrobus/lib/include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test_specifics>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/mikrobus/lib/include>
)
