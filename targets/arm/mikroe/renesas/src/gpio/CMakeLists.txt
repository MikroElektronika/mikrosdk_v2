## ./targets/arm/mikroe/renesas/src/gpio/CMakeLists.txt
set(hal_ll_def_list "")
set(MCU_NAME_FIRST_7 "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
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
    ../../include/hal_ll_target.h
    ../../include/hal_ll_pin_names.h
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
