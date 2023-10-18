## ./tests/rtc/test_example/CMakeLists.txt
add_executable(test_default_rtc
    main.c
    ReadMe.txt
)

target_link_libraries(test_default_rtc PUBLIC
    MikroC.Core
    MikroSDK.Driver.RTC
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
)