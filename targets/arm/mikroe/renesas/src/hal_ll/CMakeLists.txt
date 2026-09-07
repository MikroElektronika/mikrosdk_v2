## ./targets/arm/mikroe/renesas/src/hal_ll/CMakeLists.txt
add_library(lib_hal_ll INTERFACE)

add_library(MikroSDK.HalLowLevel ALIAS lib_hal_ll)

# FUNCTION FOR GETTING FAMILY NAMES
function(configure_family_name output_list)
    string(SUBSTRING "${MCU_NAME}" 0 7 _mcu_name_first_7)
    string(SUBSTRING "${MCU_NAME}" 3 2 _mcu_name_series)
    string(SUBSTRING "${MCU_NAME}" 3 4 _mcu_name_family)

    set(_mcu_name_series "R${_mcu_name_series}")
    set(_mcu_name_family "R${_mcu_name_family}")

    # Append definitions to the supplied list
    list(APPEND ${output_list}
        "${MCU_NAME}"
        "${_mcu_name_series}"
        "${_mcu_name_family}"
        "${_mcu_name_first_7}"
    )

    # Return the updated list to the caller
    set(${output_list} "${${output_list}}" PARENT_SCOPE)
endfunction()

set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "hal_ll_layer")

target_link_libraries(lib_hal_ll INTERFACE
    ${module_list}
)

mikrosdk_install(MikroSDK.HalLowLevel)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel ../../include/hal_ll_mstpcr.h ../../include/hal_ll_target.h ../../include/hal_ll_pin_names.h ../../include/hal_ll_target_names.h)
