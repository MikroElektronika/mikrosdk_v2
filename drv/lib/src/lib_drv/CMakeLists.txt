mikrosdk_add_interface_library(lib_drv MikroSDK.Driver)

target_link_libraries(lib_drv  INTERFACE
    MikroSDK.Driver.ADC
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Driver.I2C.Master
    MikroSDK.Driver.PWM
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.UART
    MikroSDK.Driver.OneWire
)

target_include_directories(lib_drv
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver)

install(
    FILES
        ../../include/drv_name.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/drv
)
