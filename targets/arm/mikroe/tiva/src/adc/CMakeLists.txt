set(hal_ll_def_list "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
endif()

# BEGIN ADC
list(APPEND hal_ll_def_list "MACRO_USAGE_ADC")
list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")
set(adc_subimplementation "implementation_1/hal_ll_adc.c")
set(adc_pin_map "hal_ll_adc_pin_map/implementation_1")
# END ADC

mikrosdk_add_library(lib_hal_ll_adc MikroSDK.HalLowLevel.ADC
    ${adc_subimplementation}
    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
#BEGIN ADC
    ../../include/adc/hal_ll_adc.h
    ../../include/adc/${adc_pin_map}/hal_ll_adc_pin_map.h
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
