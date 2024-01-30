## ./targets/pic_8bit/mikroe/pic18/src/can/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## BEGIN CAN
if(${MCU_NAME} MATCHES "PIC18L?F[2468][0-9]K?8[0-9]")
    set(can_implementation "implementation_1/hal_ll_can.c")
endif()

if (${MCU_NAME_LAST_3} MATCHES "K..")
    list(APPEND hal_ll_def_list "PIC18Kxx")
endif()

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
    MikroSDK.HalLowLevel.GPIO
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
