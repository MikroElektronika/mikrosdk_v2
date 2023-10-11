## ./tests/rtc/test_example/CMakeLists.txt
add_executable(test_default_rtc
    main.c
    ReadMe.txt
)

############################ test_default_rtc GENERATED CODE START ###########################
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(test_default_rtc PUBLIC MikroSDK.Log)
find_package(MikroSDK.Driver.GPIO.Port REQUIRED)
target_link_libraries(test_default_rtc PUBLIC MikroSDK.Driver.GPIO.Port)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_default_rtc PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_default_rtc PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_default_rtc PUBLIC MikroC.Core)
############################ test_default_rtc GENERATED CODE END ###########################
target_link_libraries(test_default_rtc PUBLIC
    MikroC.Core
    MikroSDK.Driver.RTC
    MikroSDK.Board
    MikroSDK.Log
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
)