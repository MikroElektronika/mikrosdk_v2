## ./tests/conversions/CMakeLists.txt
add_executable(test_conversions
    main.c
    ReadMe.txt
)

find_package(MikroC.Core REQUIRED)
find_package(MikroSDK.Board REQUIRED)
find_package(MikroSDK.Conversions REQUIRED)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
find_package(MikroSDK.Log REQUIRED)

target_link_libraries(test_conversions PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Conversions
)
