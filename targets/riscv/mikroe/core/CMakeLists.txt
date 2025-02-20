## ./targets/riscv/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")
if(${MCU_NAME} MATCHES "^GD32VF.*")
    set(chip_vendor "gigadevice")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    string(SUBSTRING ${MCU_NAME} 0 9 STRIPED_MCU_NAME)
    list(APPEND hal_ll_core_def_list ${STRIPED_MCU_NAME})
    set(hal_ll_core_source "bumblebee")
    list(APPEND hal_ll_core_def_list __core_bumblebee__)
else()
    list(hal_ll_core_def_list __vendor_not_supported__)
endif()

if(${MCU_NAME} MATCHES "^GD32VF.*")
    set(core_implementation "implementation_1/hal_ll_core.c")
else()
    set(core_implementation "implementation_2/hal_ll_core.c")
endif()

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/${core_implementation}
    src/${chip_vendor}/${hal_ll_core_source}/hal_ll_core_port.c

    include/hal_ll_core_defines.h
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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CORE include/hal_ll_core.h)
