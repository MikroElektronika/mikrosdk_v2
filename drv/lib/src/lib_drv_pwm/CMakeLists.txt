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

install(
    FILES
        ../../include/drv_pwm.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/drv
)
