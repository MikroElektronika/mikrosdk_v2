## ./targets/arm/mikroe/nxp/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
set(MCU_NAME_FIRST_4 "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 4 MCU_NAME_FIRST_4)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_4})

if (${MCU_NAME} MATCHES "^MKV4[246]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV4X_RCC__")
elseif (${MCU_NAME} MATCHES "^MKV5[68]F(.+)$")
    list(APPEND hal_ll_def_list "__MKV5X_RCC__")
elseif (${MCU_NAME} MATCHES "^MK[2568](.+)$")
    list(APPEND hal_ll_def_list "__MKX_RCC__")
endif()

# BEGIN SPI
list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")

if (${MCU_NAME} MATCHES "^MKV(.+)$")
    list(APPEND hal_ll_def_list "HAL_LL_RCC_CLOCK_OUTPUT")
endif()

set( spi_subimplementation "implementation_1/hal_ll_spi_master.c" )
set( spi_pin_map "hal_ll_spi_master_pin_map" )
# END SPI

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_subimplementation}

    ../../include/hal_ll_rcc.h
    ../../include/hal_ll_target.h
    #  BEGIN SPI
    ../../include/spi_master/hal_ll_spi_master.h
    ../../include/spi_master/${spi_pin_map}/hal_ll_spi_master_pin_map.h
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
    #  BEGIN SPI
        ../../include/spi_master
        ../../include/spi_master/${spi_pin_map}
    #  END SPI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/${spi_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.SPI.Master ../../include/spi_master/hal_ll_spi_master.h)
