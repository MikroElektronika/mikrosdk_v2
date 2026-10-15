## ./middleware/ssd1312/lib/CMakeLists.txt
mikrosdk_add_library(lib_ssd1312 MikroSDK.Ssd1312
    src/ssd1312.c

    include/ssd1312.h
    include/ssd1312_cmd.h
)

target_link_libraries(lib_ssd1312  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.I2C.Master
)

target_include_directories(lib_ssd1312
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/ssd1312>
)

mikrosdk_install(MikroSDK.Ssd1312)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ssd1312 MikroSDK.Ssd1312 include/ssd1312.h include/ssd1312_cmd.h)
