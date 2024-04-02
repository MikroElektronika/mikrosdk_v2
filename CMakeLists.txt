## ./CMakeLists.txt
cmake_minimum_required(VERSION 3.11)

if (NOT DEFINED IS_BARE_METAL)
    set(IS_BARE_METAL false)
endif()

if (${IS_BARE_METAL})
    set(PROJECT_NAME_CUSTOM "BareMetal")
else()
    set(PROJECT_NAME_CUSTOM "MikroSDK")
endif()

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(${PROJECT_NAME_CUSTOM} VERSION 2.11.0 LANGUAGES MikroC)
else()
    project(${PROJECT_NAME_CUSTOM} VERSION 2.11.0 LANGUAGES C ASM)
    if(NOT ${TOOLCHAIN_ID} STREQUAL "mchp_xc8")
        add_compile_options("-fms-extensions")
    endif()
endif()

# Link MikroC.Core for all toolchains
find_package(MikroC.Core)

set(CMAKE_STATIC_LIBRARY_PREFIX "")

list(APPEND CMAKE_MODULE_PATH "${${PROJECT_NAME_CUSTOM}_SOURCE_DIR}/cmake")

# Build Tft modules by default if not specified differently
if (NOT DEFINED MSDK_BUILD_TFT_MODULES)
    set(MSDK_BUILD_TFT_MODULES TRUE)
endif()

include(utils)
include(GNUInstallDirs)

add_subdirectory(platform)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(api)
    add_subdirectory(bsp)
    add_subdirectory(components)
    add_subdirectory(drv)
    add_subdirectory(hal)
    add_subdirectory(middleware)
    add_subdirectory(targets)
    add_subdirectory(thirdparty)
endif()

if(${MSDK_TEST_EXAMPLES} MATCHES "true")
    add_subdirectory(tests)
endif()
