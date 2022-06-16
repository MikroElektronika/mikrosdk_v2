set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
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
if ((${MCU_NAME_LAST_3} MATCHES "J50") OR (${MCU_NAME_LAST_3} MATCHES "J55") OR ((${MCU_NAME_LAST_3} MATCHES "J11") AND ((${MCU_ON_5} MATCHES "8") AND ((${MCU_ON_4} MATCHES "6") OR (${MCU_ON_4} MATCHES "7")))) OR (${MCU_NAME_LAST_5} MATCHES "66J16") OR (${MCU_NAME_LAST_5} MATCHES "86J16"))
    list(APPEND hal_ll_def_list "__hal_ll_gpio_subset_1__")
    set(gpio_implementation "implementation_1")
    set(gpio_subimplementation "subimplementation_2")
elseif (${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__hal_ll_gpio_subset_1__")
    set(gpio_implementation "implementation_1")
    set(gpio_subimplementation "subimplementation_1")
else()
    list(APPEND hal_ll_def_list "__hal_ll_gpio_not_supported__")
endif()

## Specific PIC chips have shared SFR addresses
## Page number 82 -- http://ww1.microchip.com/downloads/en/devicedoc/39775b.pdf
if (${MCU_NAME} MATCHES "(^PIC18F[68][5-7]J5[05]$)")
    list(APPEND hal_ll_def_list "__hal_ll_shared_sfrs__")
endif()
## END GPIO

list(APPEND hal_ll_def_list "MACRO_USAGE_GPIO")

mikrosdk_add_library(lib_hal_ll_gpio MikroSDK.HalLowLevel.GPIO
    ${gpio_implementation}/hal_ll_gpio.c
    ${gpio_implementation}/${gpio_subimplementation}/hal_ll_gpio_port.c
    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
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

install(
    FILES
        ../../include/gpio/hal_ll_gpio.h
        ../../include/gpio/hal_ll_gpio_constants.h
        ../../include/gpio/hal_ll_gpio_port.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
