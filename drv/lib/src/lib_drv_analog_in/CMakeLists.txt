set(drv_def_list "")

if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC18(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC32MZ(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^PIC32MX(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_10_BIT)
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^TM(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
elseif(${MCU_NAME} MATCHES "(^GD32(.+)$)")
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_12_BIT)
else()
    list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_RESOLUTION_NOT_SET)
endif()

mikrosdk_add_library(lib_drv_adc MikroSDK.Driver.ADC
    drv_analog_in.c

    ../../include/drv_analog_in.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_adc  PUBLIC
    MikroC.Core
    MikroSDK.Hal.ADC
)
target_compile_definitions(lib_drv_adc
 PUBLIC
    ${drv_def_list}
)

target_include_directories(lib_drv_adc
PRIVATE
    ../../include
INTERFACE
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.ADC)

install(
    FILES
        ../../include/drv_analog_in.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/drv
)
