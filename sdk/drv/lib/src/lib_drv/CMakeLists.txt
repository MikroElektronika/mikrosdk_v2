## ./drv/lib/src/lib_drv/CMakeLists.txt
mikrosdk_add_interface_library(lib_drv MikroSDK.Driver)

set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "drv_layer")

target_link_libraries(lib_drv INTERFACE
    ${module_list}
)

target_include_directories(lib_drv
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver ../../include/drv_name.h)
