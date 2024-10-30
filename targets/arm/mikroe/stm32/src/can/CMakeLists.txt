## ./targets/arm/mikroe/stm32/src/can/CMakeLists.txt
set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

if(${MCU_NAME} MATCHES "(^STM32(F(0([47](2|8G)|9[18])|10[357]|2[01]|3[023579][2-9]|4[0-467][2-9]|7[2-7])|L4[3-9A-Z]).+$)")
    set(can_subimplementation "implementation_1/hal_ll_can.c")
    set(can_pin_map "hal_ll_can_pin_map")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_CAN")

mikrosdk_add_library(lib_hal_ll_can MikroSDK.HalLowLevel.CAN
    ${can_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
#  BEGIN CAN
    ../../include/can/hal_ll_can.h
    ../../include/can/${can_pin_map}/hal_ll_can_pin_map.h
#  END CAN
)

target_compile_definitions(lib_hal_ll_can PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_can PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_can
    PRIVATE
        ../../include
        ../../include/gpio
        #  BEGIN CAN
        ../../include/can
        ../../include/can/${can_pin_map}
        #  END CAN

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can/${can_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can.h)
