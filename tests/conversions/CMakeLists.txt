## ./tests/conversions/CMakeLists.txt
add_executable(test_conversions
    main.c
    ReadMe.txt
)

############################ test_conversions GENERATED CODE START ###########################
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroSDK.Log)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.Sprint REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroSDK.Sprint)
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_conversions PUBLIC MikroC.Core)
############################ test_conversions GENERATED CODE END ###########################
target_link_libraries(test_conversions PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Conversions
)
