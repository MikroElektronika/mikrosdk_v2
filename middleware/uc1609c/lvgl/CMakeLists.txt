## ./middleware/uc1609c/lvgl/CMakeLists.txt
mikrosdk_add_interface_library(lib_uc1609c_lvgl_common MikroSDK.Uc1609c.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_uc1609c_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.GraphicLibrary
    MikroSDK.Uc1609c
)

target_include_directories(lib_uc1609c_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/uc1609c/lvgl>
)

mikrosdk_install(MikroSDK.Uc1609c.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/uc1609c/lvgl MikroSDK.Uc1609c.LVGL.Common include/lvgl_common.h)
