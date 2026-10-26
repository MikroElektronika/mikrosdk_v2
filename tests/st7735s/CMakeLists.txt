## ./tests/st7735s/CMakeLists.txt
add_executable(test_st7735s
    main.c
    ReadMe.txt
)

############################ test_st7735s GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_st7735s PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_st7735s PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_st7735s PUBLIC MikroSDK.GraphicLibrary)
############################ test_st7735s GENERATED CODE END ###########################
target_link_libraries(test_st7735s PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.St7735S
)
