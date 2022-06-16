set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")
find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

## BEGIN GPIO
if(${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F1")
    list(APPEND hal_ll_def_list __hal_ll_gpio_subset_2__)
    set(gpio_subimplementation "implementation_2/hal_ll_gpio_port.c")
else()
    list(APPEND hal_ll_def_list __hal_ll_gpio_subset_1__)
    set(gpio_subimplementation "implementation_1/hal_ll_gpio_port.c")
endif()
## END GPIO

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    #  BEGIN GPIO
    hal_ll_gpio.c
    ${gpio_subimplementation}
    #  END GPIO
    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
    #  BEGIN GPIO
    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/hal_ll_gpio_constants.h
    #  END GPIO

)

target_compile_definitions(lib_hal_ll_gpio PUBLIC
    ${hal_ll_def_list}
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
    #  BEGIN GPIO
    ../../include/gpio
    #  END GPIO

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
