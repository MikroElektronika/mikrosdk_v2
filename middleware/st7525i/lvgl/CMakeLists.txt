## ./middleware/st7525i/lvgl/CMakeLists.txt
mikrosdk_add_interface_library(lib_st7525i_lvgl_common MikroSDK.St7525i.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_st7525i_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.GraphicLibrary
    MikroSDK.St7525i
)

target_include_directories(lib_st7525i_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7525i/lvgl>
)

mikrosdk_install(MikroSDK.St7525i.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7525i/lvgl MikroSDK.St7525i.LVGL.Common include/lvgl_common.h)
