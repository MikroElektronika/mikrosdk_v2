## ./targets/arm/mikroe/toshiba/src/i2c/CMakeLists.txt
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
endif()

## BEGIN I2C
list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")
set(i2c_subimplementation "implementation_1/hal_ll_i2c_master.c")
set(i2c_pin_map "hal_ll_i2c_pin_map/implementation_1")
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

    ../../include/hal_ll_cg.h
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
