## ./platform/trace/lib/CMakeLists.txt
mikrosdk_add_library(lib_trace MikroSDK.Trace
    src/trace.c
    src/trace_port.h
    include/trace.h
)

target_link_libraries(lib_trace
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.I2C.Master
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.GPIO.In
        MikroSDK.Driver.SPI.Master
        MikroSDK.Driver.UART
)

target_include_directories(lib_trace
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/platform>
)

# Linking the library is all an application needs. Nothing calls into it (the drivers only have
# weak hooks), so with GNU ld its object is pulled into the link by name; the mikroC linker takes
# the strong hooks by itself. The flattened GPIO macros need MIKROSDK_TRACE in the application.
if (NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    target_link_options(lib_trace INTERFACE "LINKER:--undefined=trace_init")
endif()
target_compile_definitions(lib_trace INTERFACE MIKROSDK_TRACE)

mikrosdk_install(MikroSDK.Trace)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Trace include/trace.h)
