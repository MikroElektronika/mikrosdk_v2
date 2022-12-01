add_library(lib_hal_ll INTERFACE)
add_library(MikroSDK.HalLowLevel ALIAS lib_hal_ll)

set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "hal_ll_layer")

target_link_libraries(lib_hal_ll INTERFACE
    ${module_list}
)

mikrosdk_install(MikroSDK.HalLowLevel)

install(
    FILES
        ../../include/hal_ll_target.h
        ../../include/hal_ll_pin_names.h
        ../../include/hal_ll_target_names.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
