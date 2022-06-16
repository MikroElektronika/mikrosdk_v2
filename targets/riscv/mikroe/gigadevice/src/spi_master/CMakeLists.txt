set(hal_ll_def_list "")
set(mcu_header_path "")

list(APPEND hal_ll_def_list ${MCU_NAME})

## BEGIN SPI
set(mcu_header_path ${MCU_NAME})
set(spi_subimplementation "implementation_1/hal_ll_spi_master.c")
set(spi_pin_map "hal_ll_spi_master_pin_map/implementation_1")
## END SPI

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_subimplementation}

    ../../include/hal_ll_rcu.h
    ../../include/hal_ll_target.h

    ../../include/spi_master/hal_ll_spi_master.h
    ../../include/spi_master/${spi_pin_map}/hal_ll_spi_master_pin_map.h
)

target_compile_definitions(lib_hal_ll_spi_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_spi_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_spi_master
    PRIVATE
        ../../include
        ../../include/gpio

        ../../include/spi_master
        ../../include/spi_master/${spi_pin_map}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/${spi_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)

install(
    FILES
        ../../include/spi_master/hal_ll_spi_master.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
