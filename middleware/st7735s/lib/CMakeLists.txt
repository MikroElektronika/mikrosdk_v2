## ./middleware/st7735s/lib/CMakeLists.txt
mikrosdk_add_library(lib_st7735s MikroSDK.St7735S
    src/st7735s.c

    include/st7735s.h
    include/st7735s_cmd.h
)

target_link_libraries(lib_st7735s  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_st7735s
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7735s>
)

mikrosdk_install(MikroSDK.St7735S)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7735s MikroSDK.St7735S include/st7735s.h include/st7735s_cmd.h)
