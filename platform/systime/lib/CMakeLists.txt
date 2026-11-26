## ./platform/systime/lib/CMakeLists.txt
## Millisecond time from the core's cycle counter (systime.h).
mikrosdk_add_library(lib_systime MikroSDK.Systime
    src/systime.c
    include/systime.h
)

target_link_libraries(lib_systime PUBLIC
    MikroC.Core
)

target_include_directories(lib_systime
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(MikroSDK.Systime)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Systime include/systime.h)
