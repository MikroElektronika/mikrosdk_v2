## ./mikroe/dspic/src/adc/CMakeLists.txt
set(hal_ll_def_list "")

if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN ADC
#change to 16 but it was 12
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_MEMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")

if( ${MCU_NAME} MATCHES "dsPIC30.+" )
    set(adc_implementation "implementation_1")
    list(APPEND hal_ll_def_list "OFFSET=15")
elseif( ${MCU_NAME} MATCHES "(ds)?PIC(24|33)(E[PV]|[FH]J|F)[0-9][1-9][268]?([GM][BCMPU]|KA1|DA|GA[01]).+" )
    set(adc_implementation "implementation_1")
    list(APPEND hal_ll_def_list "OFFSET=15")
    list(APPEND hal_ll_def_list "MORE_REGS")
elseif( ${MCU_NAME} MATCHES "PIC24.+G[AB]6[01][06]$")
    set(adc_implementation "implementation_1")
    list(APPEND hal_ll_def_list "GB610")
    list(APPEND hal_ll_def_list "OFFSET=25")
    list(APPEND hal_ll_def_list "MORE_REGS")
else()
    set(adc_implementation "implementation_1")
    list(APPEND hal_ll_def_list "OFFSET=31")
    list(APPEND hal_ll_def_list "MORE_REGS")
endif()

string(LENGTH ${MCU_NAME} CMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${CMAKE_MCU_NAME_LENGTH}-3")
MATH(EXPR BEGIN_INDEX_5TH "${CMAKE_MCU_NAME_LENGTH}-5")
MATH(EXPR BEGIN_INDEX_4TH "${CMAKE_MCU_NAME_LENGTH}-4")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 1 MCU_NAME_5TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_NAME_4TH_CHAR)
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 5 MCU_NAME_LAST5_CHARS)

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
##Convert MCU_NAME to lower characters.
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
