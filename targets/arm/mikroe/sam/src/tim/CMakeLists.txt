## ./targets/arm/mikroe/sam/src/tim/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

## BEGIN TIM
if (${MCU_NAME} MATCHES "^ATSAME7.+")
    set(tim_subimplementation "implementations/implementation_1")
endif()
## END TIM

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${tim_subimplementation}/hal_ll_tim.c

    ../../include/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    #  BEGIN TIM
    ../../include/tim/hal_ll_tim.h
    ../../include/tim/hal_ll_tim_pin_map/${tim_subimplementation}/hal_ll_tim_pin_map.h
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
    ../../include/gpio/${tim_subimplementation}
    #  BEGIN TIM
    ../../include/tim
    ../../include/tim/hal_ll_tim_pin_map/${tim_subimplementation}
    #  END TIM

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/${tim_subimplementation}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim/${tim_subimplementation}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h)
