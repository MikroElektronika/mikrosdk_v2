## ./tests/glcd/CMakeLists.txt
add_executable(test_glcd
    src/main.c
    ReadMe.txt
)


target_link_libraries(test_glcd PUBLIC
    MikroC.Core
    MikroSDK.GLCD
    MikroSDK.Board
)
