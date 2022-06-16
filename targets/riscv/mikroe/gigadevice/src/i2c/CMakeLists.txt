set(hal_ll_def_list "")
set(mcu_header_path "")

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN I2C
set(mcu_header_path ${MCU_NAME})
set(i2c_subimplementation "implementation_1/hal_ll_i2c_master.c")
set(i2c_pin_map "hal_ll_i2c_pin_map/implementation_1")
# END I2C

mikrosdk_add_library(lib_hal_ll_i2c_master MikroSDK.HalLowLevel.I2C.Master
    ${i2c_subimplementation}

    ../../include/hal_ll_rcu.h
    ../../include/hal_ll_target.h

    ../../include/i2c/hal_ll_i2c_master.h
    ../../include/i2c/${i2c_pin_map}/hal_ll_i2c_pin_map.h
)

target_compile_definitions(lib_hal_ll_i2c_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_i2c_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_i2c_master
    PRIVATE
    ../../include
    ../../include/gpio

    ../../include/i2c
    ../../include/i2c/${i2c_pin_map}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c/${i2c_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.I2C.Master)

install(
    FILES
        ../../include/i2c/hal_ll_i2c_master.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
