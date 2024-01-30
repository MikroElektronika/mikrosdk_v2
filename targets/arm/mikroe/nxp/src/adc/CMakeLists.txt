## ./targets/arm/mikroe/nxp/src/adc/CMakeLists.txt
set(hal_ll_def_list "")
set(MCU_NAME_FIRST_4 "")
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

# BEGIN ADC
list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")

if(${MCU_NAME} MATCHES "^MKV5(.+)$")
    list(APPEND hal_ll_def_list "MKV5xHSADC")
    set(adc_subimplementation "implementation_2/hal_ll_adc.c")
else()
    set(adc_subimplementation "implementation_1/hal_ll_adc.c")
endif()

if(${MCU_NAME} MATCHES "^MK22(.+)$")
    list(APPEND hal_ll_def_list "MK22")
endif()

set(adc_pin_map "hal_ll_adc_pin_map")
# END ADC

mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
    ${adc_subimplementation}
    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
#BEGINADC
    ../../include/adc/hal_ll_adc.h
    ../../include/adc/${adc_pin_map}/hal_ll_adc_pin_map.h
#ENDADC
)

target_compile_definitions(lib_hal_ll_adc PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_adc PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_adc
    PRIVATE
        ../../include
        ../../include/gpio
        #BEGINADC
        ../../include/adc
        ../../include/adc/${adc_pin_map}
        #ENDADC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc/${adc_pin_map}>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.ADC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.ADC ../../include/adc/hal_ll_adc.h)
