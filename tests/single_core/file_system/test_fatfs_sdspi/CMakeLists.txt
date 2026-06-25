## ./tests/file_system/test_fatfs_sdspi/CMakeLists.txt
add_executable(test_fatfs_sdspi
    main.c
)

target_link_libraries(test_fatfs_sdspi PUBLIC
    MikroSDK.Board
    MikroSDK.PhysicalDrive
    MikroSDK.FileSystem
    MikroSDK.Log
)
