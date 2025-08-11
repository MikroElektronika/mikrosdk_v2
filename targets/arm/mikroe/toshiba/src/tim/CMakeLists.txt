## ./targets/arm/mikroe/toshiba/src/tim/CMakeLists.txt
set(hal_ll_def_list "")
set(MCU_NAME_FIRST_7 "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
endif()

# BEGIN TIM
list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")
set( tim_subimplementation "implementation_1/hal_ll_tim.c" )
set( tim_pin_map "hal_ll_tim_pin_map/implementation_1" )
# END TIM

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${tim_subimplementation}

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
    #  BEGIN TIM
        ../../include/tim
        ../../include/tim/${tim_pin_map}
    #  END TIM
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim/${tim_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h)
