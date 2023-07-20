## ./targets/avr_8bit/mikroe/avr/src/gpio/CMakeLists.txt
set(hal_ll_def_list "")
if((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
    list(APPEND hal_ll_def_list "__avr_8_bit__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)
MATH(EXPR BEGIN_INDEX_4TH "${MEMAKE_MCU_NAME_LENGTH}-4")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_ON_4)
MATH(EXPR BEGIN_INDEX_4TH "${MEMAKE_MCU_NAME_LENGTH}-5")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_ON_5)
MATH(EXPR BEGIN_INDEX_5TH "${MEMAKE_MCU_NAME_LENGTH}-5")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 5 MCU_NAME_LAST_5)

## BEGIN GPIO
if ((${MCU_NAME} MATCHES "AT"))
    set(gpio_implementation "implementation_1")
    set(gpio_subimplementation "subimplementation_1")
else()
    list(APPEND hal_ll_def_list "__hal_ll_gpio_not_supported__")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    ${gpio_implementation}/hal_ll_gpio.c
    ${gpio_implementation}/${gpio_subimplementation}/hal_ll_gpio_port.c
    ../../include/hal_ll_target.h
    ../../include/gpio/hal_ll_gpio.h
    ../../include/gpio/hal_ll_gpio_port.h
    ../../include/gpio/hal_ll_gpio_constants.h
)

target_compile_definitions(lib_hal_ll_gpio PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_gpio PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_gpio
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/adc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.GPIO)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.GPIO ../../include/gpio/hal_ll_gpio.h ../../include/gpio/hal_ll_gpio_constants.h ../../include/gpio/hal_ll_gpio_port.h)
