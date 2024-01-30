## ./targets/pic_16bit/mikroe/dspic/src/can/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN CAN
if(${MCU_NAME} MATCHES "(^(ds)?PIC(24|33)(FJ(64GP[57]|128GP[57]|256GP)|EP(256(GU|MU)|512(M[CU]8))).+$|PIC24HJ(64|128|256)GP[56][01][06]A?)|PIC24EP512G[PU]8.+")
    set(can_implementation "implementation_1/hal_ll_can.c")
endif()

if(${MCU_NAME} MATCHES "(ds)?PIC(24|33)[FH].+")
    list(APPEND hal_ll_def_list "dsPIC33FJ_FAMILY")
elseif(${MCU_NAME} MATCHES "(ds)?PIC(24|33)E.+")
    list(APPEND hal_ll_def_list "dsPIC33EP_FAMILY")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_CAN")

mikrosdk_add_library(lib_hal_ll_can MikroSDK.HalLowLevel.CAN
    ${can_implementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/can/hal_ll_can.h
    ../../include/can/hal_ll_can_pin_map.h
)

target_compile_definitions(lib_hal_ll_can PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_can PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevel.PPS
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_can
    PRIVATE
        ../../include
        ../../include/can
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can.h ../../include/can/hal_ll_can_pin_map.h)
