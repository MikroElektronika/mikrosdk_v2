mikrosdk_add_library(lib_gc9107 MikroSDK.GC9107
    src/gc9107.c

    include/gc9107.h
    include/gc9107_cmd.h
)

target_link_libraries(lib_gc9107 PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_gc9107
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/gc9107>
)

mikrosdk_install(MikroSDK.GC9107)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/gc9107 MikroSDK.GC9107 include/gc9107.h include/gc9107_cmd.h)