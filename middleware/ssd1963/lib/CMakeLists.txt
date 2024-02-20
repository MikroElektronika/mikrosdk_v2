## ./middleware/ssd1963/lib/CMakeLists.txt
mikrosdk_add_library(lib_ssd1963 MikroSDK.Ssd1963
    src/ssd1963.c

    include/ssd1963.h
    include/ssd1963_cmd.h
)

target_link_libraries(lib_ssd1963  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
)

target_include_directories(lib_ssd1963
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/ssd1963>
)

mikrosdk_install(MikroSDK.Ssd1963)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ssd1963 MikroSDK.Ssd1963 include/ssd1963.h include/ssd1963_cmd.h)
