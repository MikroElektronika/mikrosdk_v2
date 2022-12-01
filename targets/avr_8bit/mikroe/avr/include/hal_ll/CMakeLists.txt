add_library(lib_hal_ll INTERFACE)

add_library(MikroSDK.HalLowLevel  ALIAS lib_hal_ll)

target_link_libraries(lib_hal_ll  INTERFACE
    MikroSDK.HalLowLevel.ADC
    MikroSDK.HalLowLevel.GPIO
    MikroSDK.HalLowLevel.I2C.Master
    MikroSDK.HalLowLevel.SPI.Master
    MikroSDK.HalLowLevel.TIM
    MikroSDK.HalLowLevel.UART
    # MikroSDK.HalLowLevel.OneWire TODO
)

mikrosdk_install(MikroSDK.HalLowLevel)

install(
    FILES
        ../../include/hal_ll_target.h
        ../../include/hal_ll_pin_names.h
        ../../include/hal_ll_target_names.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
