## ./targets/avr_8bit/mikroe/avr/src/adc/CMakeLists.txt
set(hal_ll_def_list "")

if((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
    list(APPEND hal_ll_def_list "__avr_8_bit__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

if (${MCU_NAME} MATCHES "^ATXMEGA(.+)$")
    set(adc_subimplementation "implementation_2/hal_ll_adc.c")
elseif (${MCU_NAME} MATCHES "^AT([^X])(.+)$")
    set(adc_subimplementation "implementation_1/hal_ll_adc.c")
else()
    message(FATAL_ERROR "MCU not supported")
endif()

mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
    ${adc_subimplementation}
    ../../include/hal_ll_target.h
# BEGIN ADC
    ../../include/adc/hal_ll_adc.h
    ../../include/adc/${adc_pin_map}/hal_ll_analog_in_map.h
# END ADC
)

list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_10_BIT")

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
MATH(EXPR BEGIN_INDEX_5TH "${MEMAKE_MCU_NAME_LENGTH}-5")
MATH(EXPR BEGIN_INDEX_4TH "${MEMAKE_MCU_NAME_LENGTH}-4")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 1 MCU_NAME_5TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_NAME_4TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 5 MCU_NAME_LAST5_CHARS)

list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")

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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.ADC ../../include/adc/hal_ll_adc.h ../../include/adc/hal_ll_analog_in_map.h)
