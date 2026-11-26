## ./tests/uc1609c_lvgl/CMakeLists.txt
add_executable(test_uc1609c_lvgl
    main.c
    display_lvgl.c
    display_lvgl.h
    ../resources/mikrosdk_logo_small.c
    ReadMe.txt
)

############################ test_uc1609c_lvgl GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_uc1609c_lvgl PUBLIC MikroC.Core)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_uc1609c_lvgl PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_uc1609c_lvgl PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_uc1609c_lvgl PUBLIC MikroSDK.GraphicLibrary)
############################ test_uc1609c_lvgl GENERATED CODE END ###########################
target_link_libraries(test_uc1609c_lvgl PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.Uc1609c
    MikroSDK.Uc1609c.LVGL.Common
    MikroSDK.LVGL
)
