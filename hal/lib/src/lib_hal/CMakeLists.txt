## ./hal/lib/src/lib_hal/CMakeLists.txt
add_library(lib_hal INTERFACE)
add_library(MikroSDK.Hal ALIAS lib_hal)

set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "hal_layer")

target_link_libraries(lib_hal INTERFACE
    ${module_list}
)
