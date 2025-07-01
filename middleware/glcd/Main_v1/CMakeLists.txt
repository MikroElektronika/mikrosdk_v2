cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Main_v1 LANGUAGES MikroC)
else()
    project(Main_v1 LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    legacy_cmake_path()
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Main_v1
main.c
glcd_lib_v1.h
)

############################ Main_v1 GENERATED CODE START ###########################
find_package(MikroSDK.Driver.GPIO.Port REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroSDK.Driver.GPIO.Port)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver.GPIO.In REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroSDK.Driver.GPIO.In)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(Main_v1 PUBLIC MikroC.Core)
############################ Main_v1 GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(Main_v1
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Main_v1
        PUBLIC
            MikroC.System
    )
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
