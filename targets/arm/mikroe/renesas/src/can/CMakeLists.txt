## ./targets/arm/mikroe/tiva/src/can/CMakeLists.txt
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN CAN
set(can_subimplementation "implementation_1/hal_ll_can.c")
set(can_pin_map "hal_ll_can_pin_map")
## END CAN

mikrosdk_add_library(lib_hal_ll_can MikroSDK.HalLowLevel.CAN
    ${can_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
    #  BEGIN CAN
    ../../include/can/hal_ll_can.h
    ../../include/can/${can_pin_map}/hal_ll_can_pin_map.h
    #  END CAN
)

target_compile_definitions(lib_hal_ll_can PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_can PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_can
    PRIVATE
        ../../include
        ../../include/gpio
        #  BEGIN CAN
        ../../include/can
        ../../include/can/${can_pin_map}
        #  END CAN

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/can/${can_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CAN ../../include/can/hal_ll_can.h)
