## ./mikroe/dspic/src/i2c/CMakeLists.txt
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

## BEGIN I2C
if (${MCU_NAME} MATCHES "(ds)?PIC")
    set(i2c_implementation "implementation_1")
endif()
## END I2C

if(${MCU_NAME} MATCHES "PIC24.+G[AB]6[01][06]$")
    list(APPEND hal_ll_def_list "GB610")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")

if (NOT DEFINED _MSDK_TFT_TP_)
    list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
else()
    if (${_MSDK_TFT_TP_} MATCHES "__TP_TSC2003__")
        list(APPEND hal_ll_def_list "__TFT_RESISTIVE_TSC2003__")
    else()
        list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
    endif()
endif()

mikrosdk_add_library(lib_hal_ll_i2c_master MikroSDK.HalLowLevel.I2C.Master
    ${i2c_implementation}/hal_ll_i2c_master.c

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/i2c/hal_ll_i2c_master.h
    ../../include/i2c/hal_ll_i2c_pin_map.h
)

target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_i2c_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevel.PPS
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_i2c_master
    PRIVATE
        ../../include
        ../../include/i2c
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.I2C.Master ../../include/i2c/hal_ll_i2c_master.h ../../include/i2c/hal_ll_i2c_pin_map.h)
