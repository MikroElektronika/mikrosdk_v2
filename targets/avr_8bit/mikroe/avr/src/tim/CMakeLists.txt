## ./targets/avr_8bit/mikroe/avr/src/tim/CMakeLists.txt
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

## BEGIN TIM
if (${MCU_NAME} MATCHES "ATX")
    set(tim_implementation "implementation_3")
elseif ( ( ${MCU_NAME} MATCHES "^ATMEGA(32|64|128)4(A|P|PA)?$" ) OR ( ${MCU_NAME} MATCHES "^AT90USB(64|128)[67]$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA(64|128|256)[01]$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA(328)(A|P|PA)?$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA(324|328)PB$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA(32|64)M1$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA(32)U[24]$" ) OR ( ${MCU_NAME} MATCHES "^ATMEGA406$" ) OR ( ${MCU_NAME} MATCHES "^ATTINY16(34|7)$" ) )
    set(tim_implementation "implementation_2")
elseif (${MCU_NAME} MATCHES "AT")
    set(tim_implementation "implementation_1")
else()
    set(tim_implementation "__mcu_not_supported__")
endif()

if (${MCU_NAME} MATCHES "^ATXMEGA(16|32)E5$")
    list(APPEND hal_ll_def_list __hal_ll_tim_subset_atxmega_e5_series__)
endif()
## END TIM

list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${tim_implementation}/hal_ll_tim.c

    ../../include/hal_ll_target.h
    ../../include/tim/hal_ll_tim.h
)

target_compile_definitions(lib_hal_ll_tim PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_tim PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_tim
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/tim
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h ../../include/tim/hal_ll_tim_pin_map.h)
