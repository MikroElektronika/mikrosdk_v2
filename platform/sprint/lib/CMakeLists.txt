## ./platform/sprint/lib/CMakeLists.txt
mikrosdk_add_library(lib_sprint MikroSDK.Sprint
    src/sprint.c
    include/sprint.h
)

target_link_libraries(lib_sprint
    PUBLIC
        MikroC.Core
        MikroSDK.Conversions
)

target_include_directories(lib_sprint
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/platform>
)

# Workaround for Segger support for Renesas
if (${MCU_NAME} MATCHES "^R7FA.+")
    set_source_files_properties(src/sprint.c
            PROPERTIES COMPILE_FLAGS "-g0")
endif()

mikrosdk_install(MikroSDK.Sprint)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Sprint include/sprint.h)

