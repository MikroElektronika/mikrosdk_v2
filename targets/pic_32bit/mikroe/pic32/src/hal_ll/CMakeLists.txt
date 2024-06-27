## ./targets/pic_32bit/mikroe/pic32/src/hal_ll/CMakeLists.txt
add_library(lib_hal_ll INTERFACE)

add_library(MikroSDK.HalLowLevel ALIAS lib_hal_ll)

set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "hal_ll_layer")

target_link_libraries(lib_hal_ll INTERFACE
    ${module_list}
)

mikrosdk_install(MikroSDK.HalLowLevel)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel ../../include/hal_ll_target.h ../../include/hal_ll_pin_names.h ../../include/hal_ll_target_names.h)
