## ./middleware/st7525i/lib/CMakeLists.txt
mikrosdk_add_library(lib_st7525i MikroSDK.St7525i
    src/st7525i.c

    include/st7525i.h
    include/st7525i_cmd.h
)

target_link_libraries(lib_st7525i  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_st7525i
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7525i>
)

mikrosdk_install(MikroSDK.St7525i)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7525i MikroSDK.St7525i include/st7525i.h include/st7525i_cmd.h)
