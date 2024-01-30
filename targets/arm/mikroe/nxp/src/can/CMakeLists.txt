## ./targets/arm/mikroe/nxp/src/can/CMakeLists.txt
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 4 MCU_NAME_FIRST_4)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_4})

if (${MCU_NAME} MATCHES "^MKV4[246]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV4X_RCC__")
elseif (${MCU_NAME} MATCHES "^MKV5[68]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV5X_RCC__")
elseif (${MCU_NAME} MATCHES "^MK[2568](.+)$")
    list(APPEND hal_ll_def_list "__MKX_RCC__")
    list(APPEND hal_ll_def_list "__MKX_CHIPS__")
endif()

## BEGIN CAN
if(${MCU_NAME} MATCHES "(^MK(V(4|5[68]F[15][1M][02]VL)|6(4F(N1M0V|X5)|0D(N[25][15][26]V[LM][DQ]|X256V[LM][QD])|6)).+$)")
    set(can_subimplementation "implementation_1/hal_ll_can.c")
    set(can_pin_map "hal_ll_can_pin_map")
endif()

if (${MCU_NAME} MATCHES "^MKV(.+)$")
    list(APPEND hal_ll_def_list "HAL_LL_RCC_CLOCK_OUTPUT")
endif()
## END CAN

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
    MikroSDK.HalLowLevelCore
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
