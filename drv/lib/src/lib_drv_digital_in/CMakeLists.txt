## ./drv/lib/src/lib_drv_digital_in/CMakeLists.txt
mikrosdk_add_library(lib_drv_digital_in MikroSDK.Driver.GPIO.In
    drv_digital_in.c

    ../../include/drv_digital_in.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_digital_in  PUBLIC
    MikroC.Core
    MikroSDK.Hal.GPIO
)

target_include_directories(lib_drv_digital_in
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.GPIO.In)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.GPIO.In ../../include/drv_digital_in.h)
