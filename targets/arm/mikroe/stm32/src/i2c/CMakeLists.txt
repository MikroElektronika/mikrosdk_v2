set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)
## BEGIN I2C
list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")

if((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F1") OR
(${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L1") OR
(${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F2") OR
(${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F4"))
    set(i2c_subimplementation "implementation_1/hal_ll_i2c_master.c")
    set(i2c_pin_map "hal_ll_i2c_pin_map/implementation_1")
else()
    set(i2c_subimplementation "implementation_2/hal_ll_i2c_master.c")
    set(i2c_pin_map "hal_ll_i2c_pin_map/implementation_2")
endif()

if (${MCU_NAME} MATCHES "(^STM32F10[13](.+)$)")
    list(APPEND hal_ll_def_list __STM32F101_103_ERRATA__)
endif()

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

install(
    FILES
        ../../include/i2c/hal_ll_i2c_master.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
