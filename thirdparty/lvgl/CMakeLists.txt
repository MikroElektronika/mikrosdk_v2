## ./thirdparty/lvgl/CMakeLists.txt
cmake_minimum_required(VERSION 3.12.4)

set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# Option to define LV_LVGL_H_INCLUDE_SIMPLE, default: ON
option(LV_LVGL_H_INCLUDE_SIMPLE "Use #include \"lvgl.h\" instead of #include \"../../lvgl.h\"" ON)

# Option to define LV_CONF_INCLUDE_SIMPLE, default: ON
option(LV_CONF_INCLUDE_SIMPLE "Simple include of \"lv_conf.h\" and \"lv_drv_conf.h\"" ON)

# Option to set LV_CONF_PATH, if set parent path LV_CONF_DIR is added to includes.
option(LV_CONF_PATH "Path defined for lv_conf.h")

# Set path to appropriate "lv_conf.h" file.
has_enough_memory(ENOUGH_MEMORY RAM 131072 FLASH 524288)
if(${ENOUGH_MEMORY})
    # Heavy configuration only if MCU has more than:
    # 128KB RAM
    # 512KB FLASH
    message(INFO "LVGL: HEAVY CONFIGURATION")
    set(LV_CONF_PATH "${CMAKE_CURRENT_LIST_DIR}/lv_conf/heavy/lv_conf.h")
else()
    message(INFO "LVGL: LIGHT CONFIGURATION")
    set(LV_CONF_PATH "${CMAKE_CURRENT_LIST_DIR}/lv_conf/light/lv_conf.h")
endif()

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# Option to build shared libraries (as opposed to static), default: OFF
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SOURCES ${LVGL_ROOT_DIR}/src/*.c)

# If the project has a KEY for including all the header files for LVGL set to "true", add all the LVGL headers.
if(NOT DEFINED LVGL_ADD_ALL_FILES)
    set(LVGL_ADD_ALL_FILES OFF) # OFF or ON as value.
endif()
if(${LVGL_ADD_ALL_FILES})
    file(GLOB_RECURSE HEADERS ${LVGL_ROOT_DIR}/src/*.h)
    list(APPEND HEADERS ${LV_CONF_PATH})
    mikrosdk_add_library(lvgl MikroSDK.LVGL ${SOURCES} ${HEADERS})
else()
    mikrosdk_add_library(lvgl MikroSDK.LVGL ${SOURCES} ${LV_CONF_PATH})
endif()

target_compile_definitions(lvgl
    PUBLIC
        LV_CONF_PATH=${LV_CONF_PATH}
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
