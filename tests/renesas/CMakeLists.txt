## ./tests/renesas/CMakeLists.txt

add_executable(test_renesas
    src/main.c
    ReadMe.txt
)

target_link_libraries(test_renesas  PUBLIC
    MikroC.Core
)
