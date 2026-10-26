## ./tests/st7525i_lvgl/CMakeLists.txt
add_executable(test_st7525i_lvgl
    main.c
    display_lvgl.c
    display_lvgl.h
    ../resources/mikrosdk_logo_small.c
    ReadMe.txt
)

############################ test_st7525i_lvgl GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_st7525i_lvgl PUBLIC MikroC.Core)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_st7525i_lvgl PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_st7525i_lvgl PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_st7525i_lvgl PUBLIC MikroSDK.GraphicLibrary)
############################ test_st7525i_lvgl GENERATED CODE END ###########################
target_link_libraries(test_st7525i_lvgl PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.St7525i
    MikroSDK.St7525i.LVGL.Common
    MikroSDK.LVGL
)
