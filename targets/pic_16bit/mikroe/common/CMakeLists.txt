## ./targets/pic_16bit/mikroe/common/CMakeLists.txt

if(${MCU_NAME} MATCHES "(^(ds)?PIC(24|33)(FJ(64GP[57]|128GP[57]|256GP)|EP(256(GU|MU)|512(M[CU]8))).+$|PIC24HJ(64|128|256)GP[56][01][06]A?)|PIC24EP512G[PU]8.+")
    set(can_definitions "include/mcu_definitions/${MCU_NAME}/can_definitions.h")
endif()

mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/flatten_me.h
    include/mcu_definitions/${MCU_NAME}/mcu_definitions.h
    ${can_definitions}
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
        include/mcu_definitions/${MCU_NAME}/mcu_definitions.h
        ${can_definitions}
        include/mcu_reg_addresses/${MCU_NAME}/mcu_reg_addresses.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MEMAKE_MCU_NAME_LOWER}
)
