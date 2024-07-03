## ./deploy/static_naming_convention_f/CMakeLists.txt
include(utils)

add_executable(static_naming_convention_f
    main.c
    ReadMe.txt
)

set(package_list "")
set(module_list "")

## TODO - add new modules as implemented
find_include_package(package_list module_list MikroSDK.Driver.ADC)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.In)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.Out)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.Port)
find_include_package(package_list module_list MikroSDK.Driver.I2C.Master)
find_include_package(package_list module_list MikroSDK.Driver.PWM)
find_include_package(package_list module_list MikroSDK.Driver.SPI.Master)
find_include_package(package_list module_list MikroSDK.Driver.UART)
find_include_package(package_list module_list MikroSDK.Driver.OneWire)
find_include_package(package_list module_list MikroSDK.Driver.CAN)
find_include_package(package_list module_list MikroSDK.Driver.DMA)
find_include_package(package_list module_list MikroSDK.Driver.RTC)

target_link_libraries(static_naming_convention_f
    PUBLIC
        MikroC.Core
        ${package_list}
)

target_compile_definitions(static_naming_convention_f
    PUBLIC
        ${module_list}
)
