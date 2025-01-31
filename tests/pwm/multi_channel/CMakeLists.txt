## ./tests/pwm/multi_channel/CMakeLists.txt
add_executable(test_multi_channel_pwm
    main.c
    ReadMe.txt
)

target_link_libraries(test_multi_channel_pwm PUBLIC
    MikroC.Core
    MikroSDK.Driver.PWM
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
