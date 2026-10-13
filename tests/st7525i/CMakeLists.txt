## ./tests/st7525i/CMakeLists.txt
add_executable(test_st7525i
    main.c
    ReadMe.txt
)

############################ test_st7525i GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_st7525i PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_st7525i PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_st7525i PUBLIC MikroSDK.GraphicLibrary)
############################ test_st7525i GENERATED CODE END ###########################
target_link_libraries(test_st7525i PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.St7525i
)
