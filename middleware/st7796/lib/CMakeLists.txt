## ./middleware/st7796/lib/CMakeLists.txt
mikrosdk_add_library(lib_st7796 MikroSDK.St7796
    src/st7796.c

    include/st7796.h
    include/st7796_cmd.h
)

target_link_libraries(lib_st7796  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_st7796
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/st7796>
)

mikrosdk_install(MikroSDK.St7796)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/st7796 MikroSDK.St7796 include/st7796.h include/st7796_cmd.h)
