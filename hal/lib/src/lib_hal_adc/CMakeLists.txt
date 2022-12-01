set(hal_def_list "")

if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC18(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC32MZ(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC32MX(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_10_BIT)
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^TM(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^GD32(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^ATXMEGA(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^AT(.+)$)")
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_10_BIT)
else()
    list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_RESOLUTION_NOT_SET)
endif()

mikrosdk_add_library(lib_hal_adc MikroSDK.Hal.ADC
    hal_adc.c

    ../../include/hal_adc.h
)

target_link_libraries(lib_hal_adc  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.ADC
)
target_compile_definitions(lib_hal_adc
 PUBLIC
    ${hal_def_list}
)

target_include_directories(lib_hal_adc
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.ADC)

install(
    FILES
        ../../include/hal_adc.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal
)
