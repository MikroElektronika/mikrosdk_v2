if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    set(architecture "STM32")
    set(mcu_header_path ${MCU_NAME}${_MSDK_PACKAGE_NAME_})
    if(${MCU_NAME} MATCHES "(^STM32(.+)_[AX]$)")
        string(SUBSTRING ${mcu_header_path} 0 13 STRIPED_MCU_HEADER_PATH)
        set(mcu_header_path ${STRIPED_MCU_HEADER_PATH}${_MSDK_PACKAGE_NAME_})
    else()
        string(SUBSTRING ${mcu_header_path} 0 11 STRIPED_MCU_HEADER_PATH)
        set(mcu_header_path ${STRIPED_MCU_HEADER_PATH}${_MSDK_PACKAGE_NAME_})
    endif()
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    set(architecture "NXP")
    set(mcu_header_path ${MCU_NAME})
elseif(${MCU_NAME} MATCHES "(^TM4C1(.+)$)")
    set(architecture "TIVA")
    set(mcu_header_path ${MCU_NAME})
endif()

mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/assembly.h
    include/mcu_definitions/${architecture}/${mcu_header_path}/mcu_definitions.h
    include/common_macros.h
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
    $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)

install(
    FILES
        include/hal_ll_bit_control.h
        include/assembly.h
        include/common_macros.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)

install(
    FILES
        include/mcu_definitions/${architecture}/${mcu_header_path}/mcu_definitions.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MCU_HEADER_PATH_LOWER}
)
