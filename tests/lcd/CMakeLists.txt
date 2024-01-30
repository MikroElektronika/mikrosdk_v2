## ./tests/lcd/CMakeLists.txt
add_executable(test_lcd
    src/main.c
    ReadMe.txt
)

target_compile_definitions(test_lcd PUBLIC
    ${gpio_def_list}
)

target_link_libraries(test_lcd PUBLIC
    MikroC.Core
    MikroSDK.LCD
    MikroSDK.Board
)
