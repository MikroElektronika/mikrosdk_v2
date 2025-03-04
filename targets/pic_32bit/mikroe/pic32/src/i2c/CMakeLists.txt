## ./targets/pic_32bit/mikroe/pic32/src/i2c/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN I2C
if (${MCU_NAME} MATCHES "PIC32" )
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

if(${MCU_NAME} MATCHES "(^PIC32MX[1-7][1-79][045]F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)E[FC][FEHMGK](064|100|124|144)$)")
    set(i2c_implementation "implementation_1/hal_ll_i2c_master.c")
endif()
## END I2C

## BEGIN PMD
if(${MCU_NAME} MATCHES "(^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)E[FC][FEHMGK](064|100|124|144)$)")
    list(APPEND "HAL_LL_PERIPHERAL_MODULE_DISABLE")
endif()
## END PMD

if(${MCU_NAME} MATCHES "^PIC32.+EC.+$")
    list(APPEND hal_ll_def_list "PIC32MZEC")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_I2C")

if (NOT DEFINED _MSDK_TFT_TP_)
    list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
else()
    if(${_MSDK_TFT_TP_} MATCHES "__TP_TSC2003__")
        list(APPEND hal_ll_def_list "__TFT_RESISTIVE_TSC2003__")
    else()
        list(APPEND hal_ll_def_list "__TFT_NON_TSC2003__")
    endif()
endif()

mikrosdk_add_library(lib_hal_ll_i2c_master MikroSDK.HalLowLevel.I2C.Master
    ${i2c_implementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
##  BEGIN I2C
    ../../include/i2c/hal_ll_i2c_master.h
    ../../include/i2c/hal_ll_i2c_pin_map.h
##  END I2C
)

target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_i2c_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_i2c_master
    PRIVATE
        ../../include
        ../../include/gpio
        #BEGINADC
        ../../include/i2c
        #ENDADC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.I2C.Master ../../include/i2c/hal_ll_i2c_master.h ../../include/i2c/hal_ll_i2c_pin_map.h)
