set(hal_ll_def_list "")
if (${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if (${MCU_NAME} MATCHES "(^PIC18.+[24].+J1[13]$)|(^PIC18.+[24].+J5[03]$)|(^PIC18.+J94$)|(^PIC18.+K4[02]$)|(^PIC18.+Q43$)|(^PIC18.+Q10$)")
    if (${MCU_NAME_LAST_3} MATCHES "J94")
        list(APPEND hal_ll_def_list "__hal_ll_pps_lock_unlock_case_1__")
    elseif ((${MCU_NAME_LAST_3} MATCHES "K40") OR (${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q43") OR (${MCU_NAME_LAST_3} MATCHES "Q10"))
        list(APPEND hal_ll_def_list "__hal_ll_pps_lock_unlock_case_2__")
    else()
        list(APPEND hal_ll_def_list "__hal_ll_pps_lock_unlock_case_3__")
    endif()
    set(pps_connections_path ${MCU_NAME})
else()
    list(APPEND hal_ll_def_list "__hal_ll_pps_lock_unlock_case_4__")
    set(pps_connections_path "HAL_LL_PPS_DEFAULT")
endif() 

if (${MCU_NAME} MATCHES "(^PIC18(.+)K4[0]$)|(^PIC18(.+)Q10$)")
    if (${MCU_NAME_LAST_3} MATCHES "Q10")
        list(APPEND hal_ll_def_list "__hal_ll_pps_i2c_in_out__")
        list(APPEND hal_ll_def_list "__hal_ll_pps_spi_in_out__")
    elseif (${MCU_NAME_LAST_3} MATCHES "K40")
        list(APPEND hal_ll_def_list "__hal_ll_pps_i2c_in_out__")
    endif()
endif()

set(pps_implementation "implementation_1")
list(APPEND hal_ll_def_list "MACRO_USAGE_PPS")

mikrosdk_add_library(lib_hal_ll_pps MikroSDK.HalLowLevel.PPS
    hal_ll_pps.c
    ${pps_implementation}/hal_ll_pps_port.c

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/pps/hal_ll_pps.h
    ../../include/pps/hal_ll_pps_port.h
    ../../include/pps/hal_ll_pps_defines.h
    ../../include/pps/hal_ll_pps_connection_defs/${pps_connections_path}/hal_ll_pps_connection_defs.h
)

target_compile_definitions(lib_hal_ll_pps PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_pps PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_pps
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/pps
        ../../include/pps/hal_ll_pps_connection_defs
        ../../include/pps/hal_ll_pps_connection_defs/${pps_connections_path}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps/hal_ll_pps_connection_defs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps/hal_ll_pps_connection_defs/${pps_connections_path}>

        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
)

mikrosdk_install(MikroSDK.HalLowLevel.PPS)

install(
    FILES
        ../../include/pps/hal_ll_pps.h
        ../../include/pps/hal_ll_pps_port.h
        ../../include/pps/hal_ll_pps_defines.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
