## ./thirdparty/lvgl/CMakeLists.txt
cmake_minimum_required(VERSION 3.12.4)

set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# Option to define LV_LVGL_H_INCLUDE_SIMPLE, default: ON
option(LV_LVGL_H_INCLUDE_SIMPLE "Use #include \"lvgl.h\" instead of #include \"../../lvgl.h\"" ON)

# Option to define LV_CONF_INCLUDE_SIMPLE, default: ON
option(LV_CONF_INCLUDE_SIMPLE "Simple include of \"lv_conf.h\" and \"lv_drv_conf.h\"" ON)

# Option to set LV_CONF_PATH, if set parent path LV_CONF_DIR is added to includes.
option(LV_CONF_PATH "Path defined for lv_conf.h")
get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# Option to build shared libraries (as opposed to static), default: OFF
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SOURCES ${LVGL_ROOT_DIR}/src/*.c)

mikrosdk_add_library(lvgl MikroSDK.LVGL ${SOURCES})

target_compile_definitions(lvgl 
    PUBLIC 
        $<$<BOOL:${LV_LVGL_H_INCLUDE_SIMPLE}>:LV_LVGL_H_INCLUDE_SIMPLE>
        $<$<BOOL:${LV_CONF_INCLUDE_SIMPLE}>:LV_CONF_INCLUDE_SIMPLE>
)

# Lbrary and headers can be installed to system using make install.
file(GLOB LVGL_PUBLIC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h" "${CMAKE_CURRENT_SOURCE_DIR}/lvgl.h")

target_include_directories(lvgl
    PUBLIC
        $<BUILD_INTERFACE:${LVGL_ROOT_DIR}>
        $<BUILD_INTERFACE:${LV_CONF_DIR}>
        $<INSTALL_INTERFACE:include/thirdparty/lvgl>
)

mikrosdk_install(MikroSDK.LVGL)

install(
    DIRECTORY "${LVGL_ROOT_DIR}/src"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thirdparty/lvgl/"
    FILES_MATCHING
        PATTERN "*.h"
)

install_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/lvgl MikroSDK.LVGL ${LVGL_PUBLIC_HEADERS})
