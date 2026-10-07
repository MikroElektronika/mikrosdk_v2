## ./middleware/st7789/lib/CMakeLists.txt
mikrosdk_add_library(lib_st7789 MikroSDK.St7789
    src/st7789.c

    include/st7789.h
    include/st7789_cmd.h
)

target_link_libraries(lib_st7789  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_st7789
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7789>
)

mikrosdk_install(MikroSDK.St7789)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7789 MikroSDK.St7789 include/st7789.h include/st7789_cmd.h)
