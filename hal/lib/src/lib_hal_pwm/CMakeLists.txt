## ./hal/lib/src/lib_hal_pwm/CMakeLists.txt
mikrosdk_add_library(lib_hal_pwm MikroSDK.Hal.PWM
    hal_pwm.c

    ../../include/hal_pwm.h
)

target_link_libraries(lib_hal_pwm  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.TIM
)

target_include_directories(lib_hal_pwm
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.PWM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.PWM ../../include/hal_pwm.h)
