## ./CMakeLists.txt
cmake_minimum_required(VERSION 3.11)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(MikroSDK VERSION 2.7.2 LANGUAGES MikroC)
else()
    project(MikroSDK VERSION 2.7.2 LANGUAGES C ASM)
    find_package(MikroC.Core)
    add_compile_options("-fms-extensions")
endif()

set(CMAKE_STATIC_LIBRARY_PREFIX "")

list(APPEND CMAKE_MODULE_PATH "${MikroSDK_SOURCE_DIR}/cmake")

#Build Tft modules by default if not specified differently
if (NOT DEFINED MSDK_BUILD_TFT_MODULES)
    set(MSDK_BUILD_TFT_MODULES TRUE)
endif()

include(utils)
include(GNUInstallDirs)

add_subdirectory(api)
add_subdirectory(bsp)
add_subdirectory(components)
add_subdirectory(drv)
add_subdirectory(hal)
add_subdirectory(middleware)
add_subdirectory(platform)
add_subdirectory(targets)

if(${MSDK_TEST_EXAMPLES} MATCHES "true")
    add_subdirectory(tests)
endif()
