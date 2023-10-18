## ./targets/arm/mikroe/stm32/src/tim/CMakeLists.txt
set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

## BEGIN TIM
if ((${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32L1") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F2") OR
    (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F4") OR (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32F7") OR
    (${MEMAKE_MCU_NAME_FIRST_7} MATCHES "STM32H7"))
    set(tim_subimplementation "implementation_1/hal_ll_tim.c")
    set(tim_pin_map "hal_ll_tim_pin_map/implementation_1")
else()
    set(tim_subimplementation "implementation_2/hal_ll_tim.c")
    set(tim_pin_map "hal_ll_tim_pin_map/implementation_2")
endif()
## END TIM

list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${tim_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
#  BEGIN TIM
    ../../include/tim/hal_ll_tim.h
    ../../include/tim/${tim_pin_map}/hal_ll_tim_pin_map.h
#  END TIM
)

target_compile_definitions(lib_hal_ll_tim PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_tim PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_tim
    PRIVATE
    ../../include
    ../../include/gpio
::  BEGIN TIM
    ../../include/tim
    ../../include/tim/${tim_pin_map}
::  END TIM

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim/${tim_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h)
