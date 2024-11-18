## ./targets/arm/mikroe/sam/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")
set(mcu_header_path ${MCU_NAME}/${_MSDK_PACKAGE_NAME_}${_MSDK_PACKAGE_PIN_COUNT_})

if (${MCU_NAME} MATCHES "^ATSAME7.+")
    set(spi_subimplementation "implementations/implementation_1")
endif()

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_subimplementation}/hal_ll_spi_master.c

    ../../include/hal_ll_pmc.h
    ../../include/hal_ll_target.h
    #  BEGIN SPI
    ../../include/spi_master/hal_ll_spi_master.h
    ../../include/spi_master/hal_ll_spi_master_pin_map/${spi_subimplementation}/hal_ll_spi_master_pin_map.h
    #  END SPI
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
    ../../include/gpio/${spi_subimplementation}
    #  BEGIN SPI
    ../../include/spi_master
    ../../include/spi_master/hal_ll_spi_master_pin_map/${spi_subimplementation}
    #  END SPI

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/${spi_subimplementation}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/${spi_subimplementation}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.SPI.Master ../../include/spi_master/hal_ll_spi_master.h)
