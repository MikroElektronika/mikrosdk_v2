## ./tests/sh1107/CMakeLists.txt
add_executable(test_sh1107
    main.c
    ReadMe.txt
)

############################ test_sh1107 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_sh1107 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_sh1107 PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_sh1107 PUBLIC MikroSDK.GraphicLibrary)
############################ test_sh1107 GENERATED CODE END ###########################
target_link_libraries(test_sh1107 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.Sh1107
)
