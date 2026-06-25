## ./tests/sprint/CMakeLists.txt
add_executable(test_sprint
    main.c
    ReadMe.txt
)

target_link_libraries(test_sprint PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Sprint
)
