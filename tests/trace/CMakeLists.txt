## ./tests/trace/CMakeLists.txt
add_executable(test_trace
    main.c
    ReadMe.txt
)

target_link_libraries(test_trace PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Trace
)
