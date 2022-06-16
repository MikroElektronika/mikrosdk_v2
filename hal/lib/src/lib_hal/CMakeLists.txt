add_library(lib_hal INTERFACE)
add_library(MikroSDK.Hal  ALIAS lib_hal)

target_link_libraries(lib_hal  INTERFACE
    MikroSDK.Hal.ADC
    MikroSDK.Hal.GPIO
    MikroSDK.Hal.I2C.Master
    MikroSDK.Hal.PWM
    MikroSDK.Hal.SPI.Master
    MikroSDK.Hal.UART
    MikroSDK.Hal.OneWire
)
