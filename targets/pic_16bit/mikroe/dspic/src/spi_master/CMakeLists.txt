## ./mikroe/dspic/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})
if(${MCU_NAME} MATCHES "dsPIC30F.+")
    list(APPEND hal_ll_def_list "dsPIC30F")
endif()

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if(${MCU_NAME} MATCHES "^PIC24F[01][68]K[LM][1234]0[012]$")
    set(spi_master_implementation "implementation_2")
else()
    set(spi_master_implementation "implementation_1")
endif()

## SPI baud rate implementations. ##
list(APPEND hal_ll_def_list "__mcu_not_supported__")
## EOF SPI baud rate implementations. ##
## END SPI

list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_master_implementation}/hal_ll_spi_master.c
    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
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
    MikroSDK.HalLowLevel.PPS
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
