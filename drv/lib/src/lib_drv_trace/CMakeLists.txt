## ./drv/lib/src/lib_drv_trace/CMakeLists.txt
# Empty firmware trace hooks, shared by the drivers; MikroSDK.Trace replaces them.
mikrosdk_add_library(lib_drv_trace MikroSDK.Driver.Trace
    drv_trace.c

    ../../include/drv_trace.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_trace PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevelCommon
)

target_include_directories(lib_drv_trace
    PRIVATE
        ../../include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.Trace)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.Trace ../../include/drv_trace.h ../../include/drv_name.h)
