## ./middleware/ssd1312/lvgl/CMakeLists.txt
mikrosdk_add_interface_library(lib_ssd1312_lvgl_common MikroSDK.Ssd1312.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_ssd1312_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.GraphicLibrary
    MikroSDK.Ssd1312
)

target_include_directories(lib_ssd1312_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/ssd1312/lvgl>
)

mikrosdk_install(MikroSDK.Ssd1312.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ssd1312/lvgl MikroSDK.Ssd1312.LVGL.Common include/lvgl_common.h)
