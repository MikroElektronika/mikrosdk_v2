## ./targets/pic_16bit/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")

## Generate dsPIC specific IVT/IRQ control macros.
dspic_core_set_macros(coreParameters)
dspic_core_generate_macros(${CMAKE_CURRENT_SOURCE_DIR}/include hal_ll_core_macros.h ${coreParameters})

if (${MCU_NAME} MATCHES "^(ds)?PIC(24|30|33).*")
    set(hal_ll_core_source "hal_ll_core.c")
    list(APPEND hal_ll_core_def_list "__dspic__")
else()
    set(hal_ll_core_def_list "__family_not_supported__")
endif()

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/${hal_ll_core_source}

    include/hal_ll_core_defines.h
    include/hal_ll_core_macros.h
    include/hal_ll_core_port.h
    include/hal_ll_core.h
)

target_compile_definitions(lib_hal_ll_core
    PUBLIC
        ${hal_ll_core_def_list}
)

target_link_libraries(lib_hal_ll_core PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCommon
)

target_include_directories(lib_hal_ll_core
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCore)
