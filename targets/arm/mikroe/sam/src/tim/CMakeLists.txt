## ./targets/arm/mikroe/sam/src/tim/CMakeLists.txt

set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)
list(APPEND hal_ll_def_list ${MCU_NAME})
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

## BEGIN TIM
list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")
foreach(cmakeFile ${CMAKE_FILES})
    include(${cmakeFile})
endforeach()
## END TIM

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${pmc_subimplementation}/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    # BEGIN TIM
    ${tim_subimplementation}
    ../../include/tim/hal_ll_tim.h
    ${tim_pin_map}/hal_ll_tim_pin_map.h
    # END TIM
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
        ${gpio_subimplementation_include_dir}
        # BEGIN TIM
        ../../include/tim
        ${tim_pin_map}
        # END TIM
        # BEGIN PMC
        ${pmc_subimplementation}
        # END PMC
    INTERFACE
        # BUILD
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<BUILD_INTERFACE:${gpio_subimplementation_include_dir}>
        $<BUILD_INTERFACE:${pmc_subimplementation}>
        $<BUILD_INTERFACE:${tim_pin_map}>
        # INSTALL
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h)
