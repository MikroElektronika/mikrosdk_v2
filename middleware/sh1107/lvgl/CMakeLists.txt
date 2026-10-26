## ./middleware/sh1107/lvgl/CMakeLists.txt
mikrosdk_add_interface_library(lib_sh1107_lvgl_common MikroSDK.Sh1107.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_sh1107_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.GraphicLibrary
    MikroSDK.Sh1107
)

target_include_directories(lib_sh1107_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/sh1107/lvgl>
)

mikrosdk_install(MikroSDK.Sh1107.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/sh1107/lvgl MikroSDK.Sh1107.LVGL.Common include/lvgl_common.h)
