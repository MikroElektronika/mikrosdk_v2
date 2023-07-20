## ./targets/riscv/mikroe/common/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^GD32VF103[CRTV](.+)6$)")
    set(architecture "RISCV")
    set(vendor "GIGADEVICE")
    set(mcu_header_path ${MCU_NAME})
endif()

set(mcu_header_path ${MCU_NAME})

mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/assembly.h
    include/mcu_definitions/${vendor}/${mcu_header_path}/mcu_definitions.h
    include/common_macros.h
    include/common_types.h
)

target_compile_definitions(lib_hal_ll_common
    INTERFACE
       ${architecture}
       ${vendor}
)

target_link_libraries(lib_hal_ll_common
    INTERFACE
        MikroC.Core
)

target_include_directories(lib_hal_ll_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_definitions/${vendor}/${mcu_header_path}>
        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevelCommon include/hal_ll_bit_control.h include/assembly.h include/common_macros.h include/common_types.h)


string(TOLOWER ${MCU_NAME} MEMAKE_MCU_NAME_LOWER)
install(
    FILES
        include/mcu_definitions/${vendor}/${mcu_header_path}/mcu_definitions.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MEMAKE_MCU_NAME_LOWER}
)
