## ./hal/lib/src/lib_hal_gpio/CMakeLists.txt
mikrosdk_add_library(lib_hal_gpio MikroSDK.Hal.GPIO
    hal_gpio.c

    ../../include/hal_gpio.h
)

target_link_libraries(lib_hal_gpio  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.GPIO
)

target_include_directories(lib_hal_gpio
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.GPIO)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.GPIO ../../include/hal_gpio.h)
