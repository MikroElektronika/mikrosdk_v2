## ./targets/avr_8bit/mikroe/avr/src/uart/CMakeLists.txt
set(hal_ll_def_list "")
if((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
    list(APPEND hal_ll_def_list "__avr_8_bit__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

## Uncomment if you want to map interrupt routines using
## actual interrupt address. By default, interrupt vector
## approach is used.
# list(APPEND hal_ll_def_list "__MIKROSDK_AVR_IVT_ADDRESSES__")

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## BEGIN UART
if ( (${MCU_NAME} MATCHES "^ATXMEGA(.+)$") )
    set(uart_implementation "implementation_2")
    list(APPEND hal_ll_def_list "__ATXMEGA__")
elseif (${MCU_NAME} MATCHES "^AT(.+)$")
    set(uart_implementation "implementation_1")
    list(APPEND hal_ll_def_list "__ATMEGA__")
else()
    set(uart_implementation "__mcu_not_supported__")
endif()
## END UART

mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
    ${uart_implementation}/hal_ll_uart.c

    ../../include/hal_ll_target.h
    ../../include/uart/hal_ll_uart.h
    ../../include/uart/hal_ll_uart_pin_map.h
)

target_compile_definitions(lib_hal_ll_uart PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_uart PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_uart
    PRIVATE
    ../../include
    ../../include/gpio
#  BEGIN UART
    ../../include/uart
    ../../include/uart/${uart_pin_map}
#  END UART

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.UART)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.UART ../../include/uart/hal_ll_uart.h ../../include/uart/hal_ll_uart_pin_map.h)
