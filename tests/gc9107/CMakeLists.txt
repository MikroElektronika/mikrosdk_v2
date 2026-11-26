## ./tests/gc9107/CMakeLists.txt
add_executable(test_gc9107
    main.c
)

############################ test_gc9107 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_gc9107 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_gc9107 PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_gc9107 PUBLIC MikroSDK.GraphicLibrary)
############################ test_gc9107 GENERATED CODE END ###########################
target_link_libraries(test_gc9107 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.GC9107
)
