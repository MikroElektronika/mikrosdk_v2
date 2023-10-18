## ./targets/pic_32bit/mikroe/pic32/src/hal_ll/CMakeLists.txt
add_library(lib_hal_ll INTERFACE)

add_library(MikroSDK.HalLowLevel ALIAS lib_hal_ll)

target_link_libraries(lib_hal_ll INTERFACE
    MikroSDK.HalLowLevel.ADC
    MikroSDK.HalLowLevel.GPIO
    MikroSDK.HalLowLevel.I2C.Master
    MikroSDK.HalLowLevel.SPI.Master
    MikroSDK.HalLowLevel.TIM
    MikroSDK.HalLowLevel.UART
    MikroSDK.HalLowLevel.OneWire
)

mikrosdk_install(MikroSDK.HalLowLevel)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel ../../include/hal_ll_target.h ../../include/hal_ll_pin_names.h ../../include/hal_ll_target_names.h)
