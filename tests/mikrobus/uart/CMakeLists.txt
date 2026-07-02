add_executable(test_mikrobus_uart
    src/main.c
    inc/mikrobus_uart.h
    ReadMe.txt
)

target_compile_definitions(test_mikrobus_uart PRIVATE
    R7FA8D1BHECBD
    R7FA8M1
)

target_compile_options(test_mikrobus_uart PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
)

target_link_options(test_mikrobus_uart PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wl,--gc-sections
)

target_include_directories(test_mikrobus_uart
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_uart PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
)