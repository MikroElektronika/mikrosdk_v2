## ./middleware/filesystem/CMakeLists.txt
set_file_system_config(library_file_list include_dir_list interface_dir_list install_headers_list)

mikrosdk_add_library(file_system MikroSDK.FileSystem
    ${library_file_list}
)

if (${MCU_NAME} MATCHES "PIC18")
    target_compile_definitions(file_system PRIVATE FILE_SYSTEM_PIC18_VECTOR_TABLE)
endif()

target_link_libraries(file_system PUBLIC
    MikroSDK.GenericPointer
    MikroSDK.PhysicalDrive
)

target_include_directories(file_system
PRIVATE
    ${include_dir_list}
INTERFACE
    ${interface_dir_list}
)

mikrosdk_install(MikroSDK.FileSystem)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/filesystem MikroSDK.FileSystem
    ${install_headers_list}
)
