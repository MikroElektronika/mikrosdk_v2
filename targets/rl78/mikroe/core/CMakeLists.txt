## ./targets/rl78/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")
if(${MCU_NAME} MATCHES "^R7F100.*")
    set(chip_vendor "renesas")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    string(SUBSTRING ${MCU_NAME} 0 9 STRIPED_MCU_NAME)
    list(APPEND hal_ll_core_def_list ${STRIPED_MCU_NAME})
    set(hal_ll_core_source "rl78")
    list(APPEND hal_ll_core_def_list __core_rl78__)
else()
    list(hal_ll_core_def_list __vendor_not_supported__)
endif()

core_implementation_select(${MCU_NAME} core_implementation)

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
