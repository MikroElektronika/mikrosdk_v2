set(gpio_def_list "")

string(SUBSTRING ${MCU_NAME} 0 2 MCU_NAME_FIRST_2)
string(SUBSTRING ${MCU_NAME} 0 4 MCU_NAME_FIRST_4)
string(SUBSTRING ${MCU_NAME} 0 5 MCU_NAME_FIRST_5)
string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)

if ( ( ${MCU_NAME_FIRST_7} STREQUAL "PIC32MZ" ) OR ( ${MCU_NAME_FIRST_7} STREQUAL "PIC32MX" ) OR ( ${MCU_NAME_FIRST_5} STREQUAL "STM32" ) OR ( ${MCU_NAME} MATCHES "GD32VF103" ) )
    list(APPEND gpio_def_list "port_count_size=16")
elseif( ( ${MCU_NAME_FIRST_5} STREQUAL "PIC18" ) OR ( ${MCU_NAME_FIRST_4} STREQUAL "TM4C" ) )
    list(APPEND gpio_def_list "port_count_size=8")
elseif( ${MCU_NAME_FIRST_2} STREQUAL "MK" )
    list(APPEND gpio_def_list "port_count_size=32")
endif()

add_executable(test_default_gpio
    src/main.c
    ReadMe.txt
)

target_compile_definitions(test_default_gpio PUBLIC
    ${gpio_def_list}
)

target_link_libraries(test_default_gpio  PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
)
