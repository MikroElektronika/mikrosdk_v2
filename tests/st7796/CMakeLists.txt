## ./tests/st7796/CMakeLists.txt
add_executable(test_st7796
    main.c
    ReadMe.txt
)

############################ test_st7796 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_st7796 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_st7796 PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_st7796 PUBLIC MikroSDK.GraphicLibrary)
############################ test_st7796 GENERATED CODE END ###########################
target_link_libraries(test_st7796 PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.St7796
)
