## ./middleware/physical_drive/CMakeLists.txt
set_physical_drive_system_config(library_file_list include_dir_list interface_dir_list install_headers_list)

mikrosdk_add_library(physical_drive MikroSDK.PhysicalDrive
    ${library_file_list}
)

target_link_libraries(physical_drive PUBLIC
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GenericPointer
)

target_include_directories(physical_drive
PRIVATE
    ${include_dir_list}
INTERFACE
     ${interface_dir_list}
)

mikrosdk_install(MikroSDK.PhysicalDrive)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/physical_drive MikroSDK.PhysicalDrive
    ${install_headers_list}
)
