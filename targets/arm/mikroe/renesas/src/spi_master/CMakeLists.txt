## ./targets/arm/mikroe/renesas/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
set(MCU_NAME_FIRST_7 "")
set(mcu_header_path ${MCU_NAME})

find_cortex(hal_ll_def_list)
string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7})

list(APPEND hal_ll_def_list ${MCU_NAME})
string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7})

if (${CORE_NAME} EQUAL "M4EF")
    list(APPEND hal_ll_def_list "__cortex_m4_fpu__")
else()
    list(APPEND hal_ll_def_list "__cortex_not_supported__")
endif()

# BEGIN SPI
list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")

set(spi_pin_map "hal_ll_spi_master_pin_map/implementation_1")
if ((${MCU_NAME} MATCHES "^R7FA4M1.+") OR (${MCU_NAME} MATCHES "^R7FA4M3.+") OR
    (${MCU_NAME} MATCHES "^R7FA6M3.+") OR (${MCU_NAME} MATCHES "^R7FA6M4.+") OR
    (${MCU_NAME} MATCHES "^R7FA6M5.+") OR (${MCU_NAME} MATCHES "^R7FA2E3.+"))
    set( spi_subimplementation "implementation_1/hal_ll_spi_master.c" )
    set(sci_subimplementation "../sci/implementation_1/hal_ll_sci.c")
elseif ((${MCU_NAME} MATCHES "^R7FA8M1.+"))
    set( spi_subimplementation "implementation_2/hal_ll_spi_master.c" )
    set(sci_subimplementation "../sci/implementation_2/hal_ll_sci.c")
endif()
# END SPI

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_subimplementation}
    ${sci_subimplementation}

    ../../include/hal_ll_target.h
    #  BEGIN SPI
    ../../include/sci/hal_ll_sci.h
    ../../include/sci/hal_ll_sci_spi.h
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
        ../../include/sci
        ../../include/spi_master
        ../../include/spi_master/${spi_pin_map}
    #  END SPI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/sci>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/${spi_pin_map}>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.SPI.Master ../../include/spi_master/hal_ll_spi_master.h ../../include/sci/hal_ll_sci.h ../../include/sci/hal_ll_sci_spi.h)
