## ./middleware/glcd/lib/CMakeLists.txt
cmake_minimum_required(VERSION 3.11)

## Add GLCD as a library.
mikrosdk_add_library(lib_glcd MikroSDK.GLCD
    ## Common.
    src/glcd.c
    include/glcd.h
)

## Link MikroE Core, Board and GPIO Out libraries.
target_link_libraries(lib_glcd PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
)

## Include search paths.
target_include_directories(lib_glcd
    PRIVATE
        include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/middleware/glcd>
)

## Then generate library with `MikroSDK.GLCD` alias and generic `glcd.h` header file.
mikrosdk_install(MikroSDK.GLCD)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/glcd MikroSDK.GLCD include/glcd.h)

## END ##
