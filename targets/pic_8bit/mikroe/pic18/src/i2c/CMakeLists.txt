## ./targets/pic_8bit/mikroe/pic18/src/i2c/CMakeLists.txt
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

## BEGIN I2C
if ((${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q43"))
    set(i2c_implementation "implementation_2")
else()
    set(i2c_implementation "implementation_1")
endif()

if(${MCU_NAME} MATCHES "^PIC18F47Q10$")
    list(APPEND hal_ll_def_list "_I2C_BRG_FORMULA_ALTERNATE_")
endif()

## Specific PIC chips have shared SFR addresses
## Page number 82 -- http://ww1.microchip.com/downloads/en/devicedoc/39775b.pdf
if (${MCU_NAME} MATCHES "(^PIC18F[68][5-7]J5[05]$)")
    list(APPEND hal_ll_def_list "__hal_ll_shared_sfrs__")
endif()
## END I2C

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
