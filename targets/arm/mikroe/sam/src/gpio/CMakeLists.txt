## ./targets/arm/mikroe/sam/src/gpio/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

## BEGIN GPIO
if(${MCU_NAME} MATCHES "^ATSAM[ESV]7.+")
    set(gpio_subimplementation "implementations/implementation_1")
endif()
## END GPIO

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    #  BEGIN GPIO
    hal_ll_gpio.c
    ${gpio_subimplementation}/hal_ll_gpio_port.c
    #  END GPIO
    ../../include/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    #  BEGIN GPIO
    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/${gpio_subimplementation}/hal_ll_gpio_constants.h
    ../../include/gpio/${gpio_subimplementation}/hal_ll_gpio_struct_type.h
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
    ../../include/gpio/${gpio_subimplementation}
    #  END GPIO

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/${gpio_subimplementation}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.GPIO)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.GPIO ../../include/gpio/hal_ll_gpio.h ../../include/gpio/${gpio_subimplementation}/hal_ll_gpio_constants.h ../../include/gpio/${gpio_subimplementation}/hal_ll_gpio_struct_type.h ../../include/gpio/hal_ll_gpio_port.h)
