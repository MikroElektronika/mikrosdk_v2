## ./drv/lib/src/lib_drv_digital_out/CMakeLists.txt
mikrosdk_add_library(lib_drv_digital_out MikroSDK.Driver.GPIO.Out
    drv_digital_out.c

    ../../include/drv_digital_out.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_digital_out PUBLIC
    MikroC.Core
    MikroSDK.Hal.GPIO
)

target_include_directories(lib_drv_digital_out
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.GPIO.Out)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.GPIO.Out ../../include/drv_digital_out.h)
