## ./middleware/sh1107/lib/CMakeLists.txt
mikrosdk_add_library(lib_sh1107 MikroSDK.Sh1107
    src/sh1107.c

    include/sh1107.h
    include/sh1107_cmd.h
)

target_link_libraries(lib_sh1107  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_sh1107
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/sh1107>
)

mikrosdk_install(MikroSDK.Sh1107)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/sh1107 MikroSDK.Sh1107 include/sh1107.h include/sh1107_cmd.h)
