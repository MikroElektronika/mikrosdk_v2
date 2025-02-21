## ./tests/pwm/default/CMakeLists.txt
add_executable(test_default_pwm
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_pwm PUBLIC
    MikroC.Core
    MikroSDK.Driver.PWM
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
