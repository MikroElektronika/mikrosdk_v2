## ./components/tft8/common/ssd1963/CMakeLists.txt
mikrosdk_add_interface_library(lib_lvgl_common MikroSDK.LVGL.Common
    include/lvgl_common.h
)

# add fix to have proper tft data port passed on
if(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA(.+)$")
    target_compile_definitions(lib_lvgl_common
        INTERFACE
            "TFT_LCD_PORT_UNDEFINED_TEMP_FIX"
    )
endif()

target_link_libraries(lib_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.TouchController
    MikroSDK.Ssd1963
)

target_include_directories(lib_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/components/ssd1963>
)

mikrosdk_install(MikroSDK.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ssd1963 MikroSDK.LVGL.Common include/lvgl_common.h)
