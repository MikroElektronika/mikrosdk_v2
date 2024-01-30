## ./targets/arm/mikroe/stm32/src/can/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

set(mcu_header_path ${MCU_NAME})

list(APPEND hal_ll_def_list "MACRO_USAGE_CAN")

mikrosdk_add_library(lib_hal_ll_can MikroSDK.HalLowLevel.CAN
    implementation_1/hal_ll_can.c

    ../../include/hal_ll_rcu.h
    ../../include/hal_ll_target.h
    #  BEGIN CAN
    ../../include/can/hal_ll_can.h
    ../../include/can/hal_ll_can_pin_map/implementation_1/hal_ll_can_pin_map.h
    #  END CAN
)

target_compile_definitions(lib_hal_ll_can PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_can PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_can
    PRIVATE
    ../../include
    ../../include/gpio
    #  BEGIN CAN
    ../../include/can
    ../../include/can/hal_ll_can_pin_map/implementation_1
    #  END CAN

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can/hal_ll_can_pin_map/implementation_1>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can.h)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can_pin_map/implementation_1/hal_ll_can_pin_map.h)
