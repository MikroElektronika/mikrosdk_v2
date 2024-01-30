## ./targets/arm/mikroe/common/CMakeLists.txt
set(mcu_regs_path ${MCU_NAME})
if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    set(architecture "STM32")
    set(mcu_header_path ${MCU_NAME}${_MSDK_PACKAGE_NAME_})
    string(SUBSTRING ${mcu_regs_path} 0 11 STRIPPED_MCU_REGS_PATH)
    set(mcu_regs_path ${STRIPPED_MCU_REGS_PATH})
    set(dma_definition "include/mcu_definitions/${architecture}/${mcu_header_path}/dma_definitions.h")
    if(${MCU_NAME} MATCHES "(^STM32(.+)_[AX]$)")
        string(SUBSTRING ${mcu_header_path} 0 13 STRIPPED_MCU_HEADER_PATH)
        set(mcu_header_path ${STRIPPED_MCU_HEADER_PATH}${_MSDK_PACKAGE_NAME_})
        string(SUBSTRING ${mcu_regs_path} 0 13 STRIPPED_MCU_REGS_PATH)
    else()
        string(SUBSTRING ${mcu_header_path} 0 11 STRIPPED_MCU_HEADER_PATH)
        set(mcu_header_path ${STRIPPED_MCU_HEADER_PATH}${_MSDK_PACKAGE_NAME_})
    endif()
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    set(architecture "NXP")
    set(mcu_header_path ${MCU_NAME})
    set(dma_definition "include/mcu_definitions/${architecture}/${mcu_header_path}/dma_definitions.h")
elseif(${MCU_NAME} MATCHES "(^TM4C1(.+)$)")
    set(architecture "TIVA")
    set(mcu_header_path ${MCU_NAME})
    set(dma_definition "")
endif()


mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/assembly.h
    include/flatten_me.h
    include/mcu_definitions/${architecture}/${mcu_header_path}/mcu_definitions.h
    include/mcu_definitions/${architecture}/${mcu_header_path}/can_definitions.h
    ${dma_definition}
    include/mcu_reg_addresses/${architecture}/${mcu_regs_path}/mcu_reg_addresses.h
    include/common_macros.h
    include/common_types.h
)

target_compile_definitions(lib_hal_ll_common
    INTERFACE
       ${architecture}
)
target_link_libraries(lib_hal_ll_common
    INTERFACE
        MikroC.Core
)
target_include_directories(lib_hal_ll_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_definitions/${architecture}/${mcu_header_path}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_reg_addresses/${architecture}/${mcu_regs_path}>
        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevelCommon include/hal_ll_bit_control.h include/assembly.h include/flatten_me.h include/common_macros.h include/common_types.h)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)

install(
    FILES
        include/mcu_definitions/${architecture}/${mcu_header_path}/mcu_definitions.h
        include/mcu_definitions/${architecture}/${mcu_header_path}/can_definitions.h
        ${dma_definition}
        include/mcu_reg_addresses/${architecture}/${mcu_regs_path}/mcu_reg_addresses.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MCU_HEADER_PATH_LOWER}
)
