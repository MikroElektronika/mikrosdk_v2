## ./middleware/ft800/lib/CMakeLists.txt
mikrosdk_add_library(lib_ft800 MikroSDK.Ft800
    src/ft800.c
    src/ft800_designer.c
    src/ft800_cmd.c
    include/ft800.h
    include/ft800_cmd.h
    include/ft800_reg.h
    include/ft800_struct.h
    include/ft800_const.h
)

target_link_libraries(lib_ft800 PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.MikroBus
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Driver.SPI.Master
)

target_include_directories(lib_ft800
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/ft800>
)

mikrosdk_install(MikroSDK.Ft800)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/ft800 MikroSDK.Ft800 \
include/ft800.h include/ft800_cmd.h include/ft800_reg.h include/ft800_struct.h \
include/ft800_const.h)
