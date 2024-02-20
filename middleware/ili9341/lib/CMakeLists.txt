## ./middleware/ili9341/lib/CMakeLists.txt
mikrosdk_add_library(lib_ili9341 MikroSDK.Ili9341
    src/ili9341.c

    include/ili9341.h
    include/ili9341_cmd.h
    include/ili9341_defines.h
)

target_link_libraries(lib_ili9341  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.TouchPanel
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.PWM
    MikroSDK.Driver.ADC
    MikroSDK.Board
    MikroSDK.TpMikroe
)

target_include_directories(lib_ili9341
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/ili9341>
)

mikrosdk_install(MikroSDK.Ili9341)

install(
    FILES
        include/ili9341.h
        include/ili9341_cmd.h
        include/ili9341_defines.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/middleware/ili9341
)
