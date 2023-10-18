## ./drv/lib/src/lib_drv_pwm/CMakeLists.txt
mikrosdk_add_library(lib_drv_pwm MikroSDK.Driver.PWM
    drv_pwm.c

    ../../include/drv_pwm.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_pwm  PUBLIC
    # MikroC.Core
    MikroSDK.Hal.PWM
)

target_include_directories(lib_drv_pwm
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.PWM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.PWM ../../include/drv_pwm.h)
