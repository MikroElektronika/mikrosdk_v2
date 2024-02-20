## ./targets/pic_32bit/mikroe/pic32/src/pps/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN PPS
if(${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 5 MCU_NAME_FIRST_5)
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    string(SUBSTRING ${MCU_NAME} 0 8 MCU_NAME_FIRST_8)
    string(SUBSTRING ${MCU_NAME} 0 10 MCU_NAME_FIRST_10)

    list(APPEND hal_ll_def_list ${MCU_NAME})
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_5}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_8}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_10}xx)

    list(APPEND hal_ll_def_list "__pic32__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

if(${MCU_NAME} MATCHES "((^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?)$)")
    list(APPEND hal_ll_def_list "HAL_LL_PPS_MX_ENABLE")
endif()

set(pps_subimplementation "implementation_1/hal_ll_pps_port.c")
## END PPS

## BEGIN PMD
if(${MCU_NAME} MATCHES "(^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "HAL_LL_PERIPHERAL_MODULE_DISABLE")
endif()
## END PMD

list(APPEND hal_ll_def_list "MACRO_USAGE_PPS")

mikrosdk_add_library(lib_hal_ll_pps MikroSDK.HalLowLevel.PPS
    hal_ll_pps.c
    ${pps_subimplementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
##  BEGIN PPS
    ../../include/pps/hal_ll_pps.h
    ../../include/pps/hal_ll_pps_port.h
    ../../include/pps/hal_ll_pps_defines.h
    ../../include/pps/hal_ll_pps_connection_defs/${MCU_NAME}/hal_ll_pps_connection_defs.h
##  END PPS
)

target_compile_definitions(lib_hal_ll_pps PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_pps PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_pps
    PRIVATE
        ../../include
        ../../include/gpio
        #BEGINPPS
        ../../include/pps
        ../../include/pps/hal_ll_pps_connection_defs
        ../../include/pps/hal_ll_pps_connection_defs/${MCU_NAME}
        #ENDPPS
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps/hal_ll_pps_connection_defs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pps/hal_ll_pps_connection_defs/${MCU_NAME}>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.PPS)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.PPS ../../include/pps/hal_ll_pps.h ../../include/pps/hal_ll_pps_port.h ../../include/pps/hal_ll_pps_defines.h ../../include/pps/hal_ll_pps_connection_defs/${MCU_NAME}/hal_ll_pps_connection_defs.h)
