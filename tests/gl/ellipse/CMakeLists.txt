# ./tests/gl/ellipse/CMakeLists.txt
add_executable(test_gl_ellipse
    main.c
    ReadMe.txt
)

find_package(Components.TftBoard8 REQUIRED)
target_link_libraries(test_gl_ellipse PUBLIC Components.TftBoard8)
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_gl_ellipse PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_gl_ellipse PUBLIC MikroSDK.Board)

target_link_libraries(test_gl_ellipse
PUBLIC
    Components.TftBoard8
    MikroC.Core
    MikroSDK.Board
)
