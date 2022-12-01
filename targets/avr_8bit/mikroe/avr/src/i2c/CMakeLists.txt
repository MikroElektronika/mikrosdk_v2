set(hal_ll_def_list "")
if((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
    list(APPEND hal_ll_def_list "__avr_8_bit__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if ((${MCU_NAME} MATCHES "^ATMEGA(16|32|64)9[AP]?0?[AP]?$") OR (${MCU_NAME} MATCHES "^ATMEGA(16|32|64)[MU][12]$") OR (${MCU_NAME} MATCHES "^ATMEGA(32|64)5[0]?(PA|A|P)?$"))
    set(i2c_implementation "implementation_3/hal_ll_i2c_master.c")
elseif (${MCU_NAME} MATCHES "^ATXMEGA(.+)$")
    set(i2c_implementation "implementation_2/hal_ll_i2c_master.c")
elseif (${MCU_NAME} MATCHES "^AT([^X])(.+)$")
    set(i2c_implementation "implementation_1/hal_ll_i2c_master.c")
else()
    message(FATAL_ERROR "MCU not supported")
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
    ${i2c_implementation}

    ../../include/hal_ll_target.h
    ../../include/i2c/hal_ll_i2c_master.h
    ../../include/i2c/hal_ll_i2c_pin_map.h
)

target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_i2c_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_i2c_master
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/i2c
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)

install(
    FILES
        ../../include/i2c/hal_ll_i2c_master.h
        ../../include/i2c/hal_ll_i2c_pin_map.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
