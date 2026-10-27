## ./tests/ssd1312_lvgl/CMakeLists.txt
add_executable(test_ssd1312_lvgl
    main.c
    display_lvgl.c
    display_lvgl.h
    ../resources/mikrosdk_logo_small.c
    ReadMe.txt
)

############################ test_ssd1312_lvgl GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_ssd1312_lvgl PUBLIC MikroC.Core)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_ssd1312_lvgl PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_ssd1312_lvgl PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_ssd1312_lvgl PUBLIC MikroSDK.GraphicLibrary)
############################ test_ssd1312_lvgl GENERATED CODE END ###########################
target_link_libraries(test_ssd1312_lvgl PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.Ssd1312
    MikroSDK.Ssd1312.LVGL.Common
    MikroSDK.LVGL
)
