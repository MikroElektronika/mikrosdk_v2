add_executable(test_mikrobus_uart
    src/main.c
    inc/mikrobus_uart.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_uart
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_uart PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
)
