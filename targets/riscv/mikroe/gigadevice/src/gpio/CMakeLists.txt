set(hal_ll_def_list "")
set(mcu_header_path "")

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN GPIO
set(mcu_header_path ${MCU_NAME})
set(gpio_subimplementation "implementation_1/hal_ll_gpio_port.c")
## END GPIO

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    hal_ll_gpio.c
    ${gpio_subimplementation}

    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/hal_ll_gpio_constants.h

    ../../include/hal_ll_rcu.h
    ../../include/hal_ll_target.h
    ../../include/hal_ll_pin_names.h
    ../../include/hal_ll_target_names.h
)

target_link_libraries(lib_hal_ll_gpio PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_gpio
    PRIVATE
        ../../include
        ../../include/gpio
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.GPIO)

install(
    FILES
        ../../include/gpio/hal_ll_gpio.h
        ../../include/gpio/hal_ll_gpio_constants.h
        ../../include/gpio/hal_ll_gpio_port.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
