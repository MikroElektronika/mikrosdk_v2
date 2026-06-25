cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lvgl_button LANGUAGES MikroC)
else()
    project(lvgl_button LANGUAGES C ASM)
endif()

include(mikroeUtils)

set(PROJECT_TYPE "designer" CACHE STRING "" FORCE)

add_executable(lvgl_button
    src/main.c
    src/driver/display_lvgl.c
    include/systick.h
    include/driver/display_lvgl.h
    include/driver/lv_port_indev.h
    src/driver/lv_port_indev.c
)

find_package(MikroSDK.LVGL.Common REQUIRED)
find_package(MikroSDK.GraphicLibrary REQUIRED)
find_package(MikroC.Core REQUIRED)
find_package(MikroSDK.LVGL)

target_link_libraries(lvgl_button
    PUBLIC
        MikroC.Core
        MikroSDK.LVGL
        MikroSDK.LVGL.Common
        MikroSDK.GraphicLibrary
)

target_include_directories(lvgl_button
    PUBLIC
        include
        include/driver
)
