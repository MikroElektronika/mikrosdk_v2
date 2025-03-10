## ./components/tft7/common/ili9341/CMakeLists.txt
mikrosdk_add_interface_library(lib_lvgl_common MikroSDK.LVGL.Common
    include/lvgl_common.h
)

target_link_libraries(lib_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.TouchController
    MikroSDK.Ili9341
)

target_include_directories(lib_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/components/ili9341>
)

mikrosdk_install(MikroSDK.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ili9341 MikroSDK.LVGL.Common include/lvgl_common.h)
