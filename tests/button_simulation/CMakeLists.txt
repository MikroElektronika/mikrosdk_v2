## ./tests/button_simulation/CMakeLists.txt
add_executable(test_button_simulation
    main.c
    ReadMe.txt
)

target_link_libraries(test_button_simulation PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Simulation.Button
)
