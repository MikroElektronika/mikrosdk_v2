## ./targets/rl78/mikroe/common/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^R7F100.+$)")
    set(architecture "RL78")
    set(vendor "RENESAS")
endif()

set(header_files "")
get_files(include/mcu_definitions/${vendor}/${MCU_NAME} header_files h)

mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/flatten_me.h
    include/assembly.h
    ${header_files}
    include/mcu_reg_addresses/${vendor}/${MCU_NAME}/mcu_reg_addresses.h
    include/common_macros.h
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_definitions/${vendor}/${MCU_NAME}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_reg_addresses/${vendor}/${MCU_NAME}>
        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevelCommon include/flatten_me.h include/assembly.h include/common_macros.h)


string(TOLOWER ${MCU_NAME} MEMAKE_MCU_NAME_LOWER)
install(
    FILES
        ${header_files}
        include/mcu_reg_addresses/${vendor}/${MCU_NAME}/mcu_reg_addresses.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MEMAKE_MCU_NAME_LOWER}
)
