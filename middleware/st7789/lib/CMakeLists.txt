## ./middleware/st7789/lib/CMakeLists.txt
mikrosdk_add_library(lib_st7789 MikroSDK.ST7789
    src/st7789.c

    include/st7789.h
)

target_link_libraries(lib_st7789  PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.In
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

mikrosdk_install(MikroSDK.ST7789)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7789 MikroSDK.ST7789 include/st7789.h)
