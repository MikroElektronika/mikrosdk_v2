## ./components/tft8/common/ssd1963/CMakeLists.txt
# Static library (was header-only): the shared display/touch state lives in
# src/lvgl_common.c so that every source file including lvgl_common.h uses the
# same pins and handles.
mikrosdk_add_library(lib_lvgl_common MikroSDK.LVGL.Common
    src/lvgl_common.c
    include/lvgl_common.h
)

target_link_libraries(lib_lvgl_common PUBLIC
    MikroC.Core
    MikroSDK.TouchController
    MikroSDK.Ssd1963
)

target_include_directories(lib_lvgl_common
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/components/ssd1963>
)

mikrosdk_install(MikroSDK.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ssd1963 MikroSDK.LVGL.Common include/lvgl_common.h)
