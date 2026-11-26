## ./middleware/uc1609c/lib/CMakeLists.txt
mikrosdk_add_library(lib_uc1609c MikroSDK.Uc1609c
    src/uc1609c.c

    include/uc1609c.h
    include/uc1609c_cmd.h
)

target_link_libraries(lib_uc1609c  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_uc1609c
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/uc1609c>
)

mikrosdk_install(MikroSDK.Uc1609c)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/uc1609c MikroSDK.Uc1609c include/uc1609c.h include/uc1609c_cmd.h)
