cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(${PROJECT_NAME} LANGUAGES MikroC)
else()
    project(${PROJECT_NAME} LANGUAGES C ASM)
endif()

include(mikroeUtils)
include(${CMAKE_CURRENT_SOURCE_DIR}/1ms_timer/TimerHeaderConfig.cmake)

set(PROJECT_TYPE "${PROJECT_TYPE_VALUE}" CACHE STRING "" FORCE)

add_executable(${PROJECT_NAME}
    driver/display_lvgl.h
    driver/lv_port_indev.h
    driver/display_lvgl.c
    driver/lv_port_indev.c
    1ms_Timer.h
    resource.mres
    main_screen.mscr
    main_screen.c
    main_screen.h
    main.c
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS resource.mres)
############################ ${PROJECT_NAME} GENERATED CODE START ###########################
############################ ${PROJECT_NAME} GENERATED CODE END ###########################


find_package_me(MikroSDK.LVGL.Common REQUIRED)
find_package_me(MikroSDK.GraphicLibrary REQUIRED)
find_package_me(MikroC.Core REQUIRED)
find_package_me(MikroSDK.LVGL)

lvgl_designer_generator(${PROJECT_NAME} resource.mres main_screen.mscr)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        MikroC.Core
        MikroSDK.LVGL
        MikroSDK.LVGL.Common
        MikroSDK.GraphicLibrary
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    ${tim_list}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        driver
        1ms_timer
        .
)

if((${MCU_FLASH} LESS 184320) OR (${MCU_RAM} LESS 24576)) ## 180KB Flash / 24KB RAM recommended.
    message(FATAL_ERROR ": ${MCU_NAME} does not have recommended memory for this example.")
endif()

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.meproject)
                fetch_startup_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject startupName)
                if(startupName)
                    add_startup_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${startupName})
                endif()
                fetch_linker_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject linkerName)
                if(linkerName)
                    add_ld_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${linkerName})
                endif()
            endif()
        endif()
    endif()
endif()
