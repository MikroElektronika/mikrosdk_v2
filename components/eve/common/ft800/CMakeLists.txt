## ./components/eve/common/ft800/CMakeLists.txt
mikrosdk_add_interface_library(lib_lvgl_common MikroSDK.LVGL.Common
    include/lvgl_common.h
    ${CMAKE_BINARY_DIR}/generated/eve_mikrobus.h
)

target_link_libraries(lib_lvgl_common INTERFACE
    MikroC.Core
    MikroSDK.TouchController
    MikroSDK.Ft800
    MikroSDK.Board
)

target_include_directories(lib_lvgl_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include/components/ft800>
)

mikrosdk_install(MikroSDK.LVGL.Common)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ft800 MikroSDK.LVGL.Common include/lvgl_common.h ${CMAKE_BINARY_DIR}/generated/eve_mikrobus.h)
