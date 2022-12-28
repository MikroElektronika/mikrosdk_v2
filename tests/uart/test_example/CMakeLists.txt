## ./tests/uart/test_example/CMakeLists.txt
add_executable(test_default_uart
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_uart PUBLIC
    MikroC.Core
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
