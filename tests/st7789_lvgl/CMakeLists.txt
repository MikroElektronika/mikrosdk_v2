## ./tests/st7789_lvgl/CMakeLists.txt
add_executable(test_st7789_lvgl
    main.c
    display_lvgl.c
    display_lvgl.h
    mikrosdk_logo_mali.c
    ReadMe.txt
)

############################ test_st7789_lvgl GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_st7789_lvgl PUBLIC MikroC.Core)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_st7789_lvgl PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_st7789_lvgl PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_st7789_lvgl PUBLIC MikroSDK.GraphicLibrary)
############################ test_st7789_lvgl GENERATED CODE END ###########################
target_link_libraries(test_st7789_lvgl PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.St7789
    MikroSDK.St7789.LVGL.Common
    MikroSDK.LVGL
)
