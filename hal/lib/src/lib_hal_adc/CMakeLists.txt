## ./hal/lib/src/lib_hal_adc/CMakeLists.txt
set(hal_def_list "")

set_resolution(ANALOG_IN_RESOLUTION_CMAKE_VALUE)
list(APPEND hal_def_list HAL_ADC_RESOLUTION_CMAKE=HAL_ADC_${ANALOG_IN_RESOLUTION_CMAKE_VALUE})
message(INFO ":HAL LAYER ADC ${ANALOG_IN_RESOLUTION_CMAKE_VALUE} SET")

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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.ADC ../../include/hal_adc.h)
