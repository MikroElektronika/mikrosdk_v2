set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

##BEGINADC
list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")
string(SUBSTRING ${MCU_NAME} 0 8 MEMAKE_MCU_NAME_FIRST_8)

if ((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F2") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F4") OR
    (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F7"))
    set(adc_subimplementation "implementation_1/subimplementation_1/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_1/subimplementation_1")
elseif (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L4")
    set(adc_subimplementation "implementation_1/subimplementation_2/hal_ll_adc.c")
    set(adc_pin_map  "hal_ll_adc_pin_map/implementation_1/subimplementation_2")
elseif ((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F1") OR (${MEMAKE_MCU_NAME_FIRST_8} MATCHES "STM32F37"))
    set(adc_subimplementation "implementation_4/subimplementation_1/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_4/subimplementation_1")
elseif (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F3")
    set(adc_subimplementation "implementation_1/subimplementation_3/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_1/subimplementation_3")
elseif (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32H7")
    set(adc_subimplementation "implementation_2/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_2")
elseif ((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F0") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L0"))
    set(adc_subimplementation "implementation_3/subimplementation_1/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_3/subimplementation_1")
elseif (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32G0")
    set(adc_subimplementation "implementation_3/subimplementation_2/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_3/subimplementation_2")
elseif (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L1")
    set(adc_subimplementation "implementation_4/subimplementation_2/hal_ll_adc.c")
    set(adc_pin_map "hal_ll_adc_pin_map/implementation_4/subimplementation_2")
endif()
##ENDADC

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

install(
    FILES
        ../../include/adc/hal_ll_adc.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
