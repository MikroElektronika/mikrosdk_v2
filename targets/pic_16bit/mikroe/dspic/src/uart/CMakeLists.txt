## ./mikroe/dspic/src/uart/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## BEGIN UART
set(uart_implementation "implementation_1")
## END UART

if (${MCU_NAME} MATCHES "(^PIC24FJ(.+)G[AB]([467](.+)|20[24]$))")
    list(APPEND hal_ll_def_list "__INTERRUPT__=iv")
else()
    list(APPEND hal_ll_def_list "__INTERRUPT__=org")
endif()

mikrosdk_add_library(lib_hal_ll_uart MikroSDK.HalLowLevel.UART
    ${uart_implementation}/hal_ll_uart.c

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/uart/hal_ll_uart.h
    ../../include/uart/hal_ll_uart_pin_map.h
)

target_compile_definitions(lib_hal_ll_uart PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_uart PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevel.PPS
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

list(APPEND hal_ll_def_list "MACRO_USAGE_UART")

mikrosdk_install(MikroSDK.HalLowLevel.UART)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.UART ../../include/uart/hal_ll_uart.h ../../include/uart/hal_ll_uart_pin_map.h)
