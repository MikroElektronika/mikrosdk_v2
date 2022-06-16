add_executable(test_default_one_wire
    ./main.c
    ReadMe.txt
)

target_link_libraries(test_default_one_wire PUBLIC
    MikroC.Core
    MikroSDK.Driver.OneWire
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
