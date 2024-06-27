## ./targets/avr_8bit/mikroe/common/CMakeLists.txt
set(header_files "")
get_files(include/mcu_definitions/${architecture}/${MCU_NAME} header_files h)

mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/flatten_me.h
    ${header_files}
    include/mcu_reg_addresses/${MCU_NAME}/mcu_reg_addresses.h
    include/common_macros.h
    include/assembly.h
)

target_link_libraries(lib_hal_ll_common
    INTERFACE
        MikroC.Core
)
target_include_directories(lib_hal_ll_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_definitions/${MCU_NAME}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_reg_addresses/${MCU_NAME}>
        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevelCommon include/hal_ll_bit_control.h include/common_macros.h include/assembly.h include/flatten_me.h)


string(TOLOWER ${MCU_NAME} MEMAKE_MCU_NAME_LOWER)

install(
    FILES
        ${header_files}
        include/mcu_reg_addresses/${MCU_NAME}/mcu_reg_addresses.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MEMAKE_MCU_NAME_LOWER}
)
