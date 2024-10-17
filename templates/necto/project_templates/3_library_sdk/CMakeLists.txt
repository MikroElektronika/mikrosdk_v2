cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(${PROJECT_NAME} LANGUAGES MikroC)
else()
    project(${PROJECT_NAME} LANGUAGES C ASM)
endif()

include(mikroeUtils)

# TODO - Temporary fix, remove with NECTO release 7.0.4+
if (${MIKROSDK_TYPE} STREQUAL "legacy")
    legacy_cmake_path()
endif()

set(PROJECT_TYPE "${PROJECT_TYPE_VALUE}" CACHE STRING "" FORCE)

add_library(${PROJECT_NAME} STATIC lib.c lib.h)
############################ ${PROJECT_NAME} GENERATED CODE START ###########################
############################ ${PROJECT_NAME} GENERATED CODE END ###########################

find_package_me(MikroC.Core REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package_me(MikroC.System REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            MikroC.System
    )
endif()
