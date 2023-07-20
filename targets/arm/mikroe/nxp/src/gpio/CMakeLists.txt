## ./targets/arm/mikroe/nxp/src/gpio/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 4 MCU_NAME_FIRST_4)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_4})

if (${MCU_NAME} MATCHES "^MKV4[246]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV4X_RCC__")
elseif (${MCU_NAME} MATCHES "^MKV5[68]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV5X_RCC__")
elseif (${MCU_NAME} MATCHES "^MK[2568](.+)$")
    list(APPEND hal_ll_def_list "__MKX_RCC__")
endif()

# BEGIN GPIO
list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")
set(gpio_subimplementation "implementation_1/hal_ll_gpio_port.c")
# END GPIO

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    # BEGIN GPIO
    hal_ll_gpio.c
    ${gpio_subimplementation}
    # END GPIO
    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
    # BEGIN GPIO
    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/hal_ll_gpio_constants.h
    # END GPIO
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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.GPIO ../../include/gpio/hal_ll_gpio.h ../../include/gpio/hal_ll_gpio_constants.h ../../include/gpio/hal_ll_gpio_port.h)
