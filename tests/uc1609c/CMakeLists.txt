## ./tests/uc1609c/CMakeLists.txt
add_executable(test_uc1609c
    main.c
    ReadMe.txt
)

############################ test_uc1609c GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(test_uc1609c PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(test_uc1609c PUBLIC MikroSDK.Board)
find_package(MikroSDK.GraphicLibrary REQUIRED)
target_link_libraries(test_uc1609c PUBLIC MikroSDK.GraphicLibrary)
############################ test_uc1609c GENERATED CODE END ###########################
target_link_libraries(test_uc1609c PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GraphicLibrary
    MikroSDK.Uc1609c
)
