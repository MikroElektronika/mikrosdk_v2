## ./middleware/st7735s/lvgl/CMakeLists.txt
mikrosdk_add_interface_library(lib_st7735s_lvgl_common MikroSDK.St7735S.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_st7735s_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.GraphicLibrary
    MikroSDK.St7735S
)

target_include_directories(lib_st7735s_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7735s/lvgl>
)

mikrosdk_install(MikroSDK.St7735S.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7735s/lvgl MikroSDK.St7735S.LVGL.Common include/lvgl_common.h)
