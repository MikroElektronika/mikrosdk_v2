## ./drv/lib/src/lib_drv_port/CMakeLists.txt
mikrosdk_add_library(lib_drv_port MikroSDK.Driver.GPIO.Port
    drv_port.c

    ../../include/drv_port.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_port PUBLIC
    MikroC.Core
    MikroSDK.Hal.GPIO
)

target_include_directories(lib_drv_port
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.GPIO.Port)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.GPIO.Port ../../include/drv_port.h)
