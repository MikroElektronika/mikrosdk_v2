## ./targets/arm/mikroe/nxp/src/i2c/CMakeLists.txt
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
endif()

## BEGIN I2C
list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")
set(i2c_subimplementation "implementation_1/hal_ll_i2c_master.c")
set(i2c_pin_map "hal_ll_i2c_pin_map")

if (${MCU_NAME} MATCHES "^MKV(.+)$")
    list(APPEND hal_ll_def_list "HAL_LL_RCC_CLOCK_OUTPUT")
endif()
if (${MCU_NAME} MATCHES "^MK([V]|6[456])(.+)$")
    list(APPEND hal_ll_def_list "I2C_MASTER_CHIP_SELECT")
endif()
if (${MCU_NAME} MATCHES "^MK64(.+)$")
    list(APPEND hal_ll_def_list "I2C_MASTER_CHIP_SELECT_MK64")
endif()

## END I2C

# TSC2003 Special case
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
    ${i2c_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
#  BEGIN I2C
    ../../include/i2c/hal_ll_i2c_master.h
    ../../include/i2c/${i2c_pin_map}/hal_ll_i2c_pin_map.h
#  END I2C
)

target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_i2c_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_i2c_master
    PRIVATE
        ../../include
        ../../include/gpio
        #  BEGIN I2C
        ../../include/i2c
        ../../include/i2c/${i2c_pin_map}
        #  END I2C

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c/${i2c_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
    )

mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.I2C.Master ../../include/i2c/hal_ll_i2c_master.h)
