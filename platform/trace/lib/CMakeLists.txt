mikrosdk_add_library(lib_trace MikroSDK.Trace
    src/trace.c
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

mikrosdk_install(MikroSDK.Trace)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Trace include/trace.h)
