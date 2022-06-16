add_executable(test_default_adc
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_adc PUBLIC
    MikroC.Core
    MikroSDK.Driver.ADC
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
    MikroSDK.Conversions
)
