## ./targets/arm/mikroe/sam/src/adc/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

##BEGIN ADC
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")

if (${MCU_NAME} MATCHES "^ATSAME7.+")
    set(adc_subimplementation "implementations/implementation_1")
endif()
##END ADC

mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
    ${adc_subimplementation}/hal_ll_adc.c
    ../../include/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    #BEGIN ADC
    ../../include/adc/hal_ll_adc.h
    ../../include/adc/hal_ll_adc_pin_map/${adc_subimplementation}/hal_ll_adc_pin_map.h
    #END ADC
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
        ../../include/gpio/${adc_subimplementation}
        #BEGIN ADC
        ../../include/adc
        ../../include/adc/hal_ll_adc_pin_map/${adc_subimplementation}
        #END ADC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/${adc_subimplementation}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc/hal_ll_adc_pin_map/${adc_subimplementation}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.ADC)

install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.ADC ../../include/adc/hal_ll_adc.h)
