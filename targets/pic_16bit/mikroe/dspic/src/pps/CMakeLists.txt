## ./mikroe/dspic/src/pps/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if (${MCU_NAME} MATCHES "^(ds)?PIC((24|33)[FH]J?V?.+(K[ALM].+|[69][46]GA0[01][068]$|128GA0.+|[126][245][68]?GP([1367][10].+|[25][01][06]A?$)|MC.+A$|GS.+[068]$)|30F.+)")
    set(pps_connections_path "HAL_LL_PPS_DEFAULT")
else()
    set(pps_connections_path  ${MCU_NAME})
endif()

set(pps_implementation "implementation_1")
list(APPEND hal_ll_def_list "MACRO_USAGE_PPS")

if (${MCU_NAME} MATCHES "(^PIC24FJ(.+)G[AB]6(.+))")
    list(APPEND hal_ll_def_list "__GB610_FAMILY__")
endif()

mikrosdk_add_library(lib_hal_ll_pps MikroSDK.HalLowLevel.PPS
    hal_ll_pps.c
    ${pps_implementation}/hal_ll_pps_port.c

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/pps/hal_ll_pps.h
    ../../include/pps/hal_ll_pps_port.h
    ../../include/pps/hal_ll_pps_defines.h
    ../../include/pps/hal_ll_pps_connection_defs/hal_ll_pps_struct_def.h
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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.PPS ../../include/pps/hal_ll_pps.h ../../include/pps/hal_ll_pps_port.h ../../include/pps/hal_ll_pps_defines.h)
