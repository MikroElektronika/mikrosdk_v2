## ./targets/avr_8bit/mikroe/avr/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
if((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
    list(APPEND hal_ll_def_list "__avr_8_bit__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()
list(APPEND hal_ll_def_list ${MCU_NAME})

set(spi_master_implementation "implementation_1") # SPI implementation.

if ((${MCU_NAME} MATCHES "ATX"))
    list(APPEND hal_ll_def_list __hal_ll_spi_master_subset_atxmega__)
elseif ((${MCU_NAME} MATCHES "AT"))
    list(APPEND hal_ll_def_list __hal_ll_spi_master_subset_atmega__)
    list(APPEND hal_ll_def_list "HAL_LL_SPI0_CTRL_REG_ADDRESS=HAL_LL_SPI0_SPCR_REG_ADDRESS")
    list(APPEND hal_ll_def_list "HAL_LL_SPI0_STATUS_REG_ADDRESS=HAL_LL_SPI0_SPSR_REG_ADDRESS")
    list(APPEND hal_ll_def_list "HAL_LL_SPI0_DATA_REG_ADDRESS=HAL_LL_SPI0_SPDR_REG_ADDRESS")
    list(APPEND hal_ll_def_list "HAL_LL_SPI1_CTRL_REG_ADDRESS=HAL_LL_SPI1_SPCR_REG_ADDRESS")
    list(APPEND hal_ll_def_list "HAL_LL_SPI1_STATUS_REG_ADDRESS=HAL_LL_SPI1_SPSR_REG_ADDRESS")
    list(APPEND hal_ll_def_list "HAL_LL_SPI1_DATA_REG_ADDRESS=HAL_LL_SPI1_SPDR_REG_ADDRESS")
else()
    set(spi_master_implementation "__mcu_not_supported__")
    list(APPEND hal_ll_def_list __hal_ll_spi_master_subset_atmega__)
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_master_implementation}/hal_ll_spi_master.c
    ../../include/hal_ll_target.h
# ::  BEGIN SPI
    ../../include/spi_master/hal_ll_spi_master.h
    ../../include/spi_master/hal_ll_spi_master_pin_map.h
# ::  END SPI
)

target_compile_definitions(lib_hal_ll_spi_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_spi_master PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_spi_master
    PRIVATE
        ../../include
        ../../include/gpio
        ../../include/spi_master
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.SPI.Master ../../include/spi_master/hal_ll_spi_master.h ../../include/spi_master/hal_ll_spi_master_pin_map.h)
