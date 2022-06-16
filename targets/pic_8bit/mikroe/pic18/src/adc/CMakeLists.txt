set(hal_ll_def_list "")

if(${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN ADC
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
MATH(EXPR BEGIN_INDEX_5TH "${MEMAKE_MCU_NAME_LENGTH}-5")
MATH(EXPR BEGIN_INDEX_4TH "${MEMAKE_MCU_NAME_LENGTH}-4")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 1 MCU_NAME_5TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_NAME_4TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 5 MCU_NAME_LAST5_CHARS)

if (${MCU_NAME_LAST_3} MATCHES "J94")
    set(adc_implementation "implementation_1")
elseif ((${MCU_NAME_LAST_3} MATCHES "K50") OR (${MCU_NAME} MATCHES "(^PIC18(((.+)4[56]K22$)|((.+)26K22$)))"))
    set(adc_implementation "implementation_2/subimplementation_2")
elseif ((${MCU_NAME_LAST_3} MATCHES "K22") OR (${MCU_NAME_LAST_3} MATCHES "K80") OR (${MCU_NAME_LAST_3} MATCHES "K90"))
    set(adc_implementation "implementation_2/subimplementation_1")
elseif ((${MCU_NAME_LAST_3} MATCHES "K40") OR (${MCU_NAME_LAST_3} MATCHES "Q10"))
    set(adc_implementation "implementation_3/subimplementation_1")
elseif ((${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q43"))
    set(adc_implementation "implementation_3/subimplementation_2")
elseif ((${MCU_NAME_LAST_3} MATCHES "J50") OR (${MCU_NAME_LAST_3} MATCHES "J55") OR ((${MCU_NAME_LAST_3} MATCHES "J11") AND (${MCU_NAME_5TH_CHAR} MATCHES "8") AND ((${MCU_NAME_4TH_CHAR} MATCHES "6") OR (${MCU_NAME_4TH_CHAR} MATCHES "7"))) OR (${MCU_NAME_LAST5_CHARS} MATCHES "66J16") OR (${MCU_NAME_LAST5_CHARS} MATCHES "86J16"))
    set(adc_implementation "implementation_4")
elseif (((${MCU_NAME_LAST_3} MATCHES "J13") OR (${MCU_NAME_LAST_3} MATCHES "J53")) AND ((${MCU_NAME_5TH_CHAR} MATCHES "2") OR (${MCU_NAME_5TH_CHAR} MATCHES "4")))
    set(adc_implementation "implementation_5/subimplementation_1")
elseif (${MCU_NAME_LAST_3} MATCHES "J11")
    set(adc_implementation "implementation_5/subimplementation_2")
else()
    set(adc_implementation "implementation_2/subimplementation_3")
endif()
## END ADC

list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")

mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
    ${adc_implementation}/hal_ll_adc.c
    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/adc/hal_ll_adc.h
    ../../include/adc/hal_ll_analog_in_map.h

)

target_compile_definitions(lib_hal_ll_adc PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_adc PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_adc
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/adc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.ADC)

install(
    FILES
        ../../include/adc/hal_ll_adc.h
        ../../include/adc/hal_ll_analog_in_map.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
