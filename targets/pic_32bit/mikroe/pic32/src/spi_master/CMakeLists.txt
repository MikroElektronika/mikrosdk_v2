set(hal_ll_def_list "")

## BEGIN I2C
if(${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 5 MCU_NAME_FIRST_5)
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    string(SUBSTRING ${MCU_NAME} 0 8 MCU_NAME_FIRST_8)
    string(SUBSTRING ${MCU_NAME} 0 10 MCU_NAME_FIRST_10)

    list(APPEND hal_ll_def_list ${MCU_NAME})
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_5}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_8}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_10}xx)

    list(APPEND hal_ll_def_list "__pic32__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

## BEGIN SPI
if(${MCU_NAME} MATCHES "(^PIC32MX[1-7][1-79][045]F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    set(spi_master_implementation "implementation_1/hal_ll_spi_master.c")
endif()
    ## Match group of PIC32MX MCU's which utilize SPIxBRG<12:0> register bits.
    ## 1st datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX1XX2XX%20283644-PIN_Datasheet_DS60001168L.pdf
if(${MCU_NAME} MATCHES "(^PIC32MX[12][12357][0]F(016|032|064|128|256)[BCD]B?$)")
    list(APPEND hal_ll_def_list "SPI_BAUD_REG_13_BIT_RESOLUTION")
    ## Match group of PIC32MX MCU's which utilize SPIxBRG<8:0> register bits.
    ## 2nd datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX330350370430450470_Datasheet_DS60001185H.pdf
    ## 3rd datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/61143H.pdf
    ## 4th datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX5XX6XX7XX_Family)Datasheet_DS60001156K.pdf
    ## 5th datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX1XX2XX5XX%2064100-PIN_Family_60001290F.pdf
elseif(${MCU_NAME} MATCHES "(^PIC32MX[34][357][0]F(064|128|256|512)[HL]B?$)|(^PIC32MX[34][246][0]F(032|064|128|256|512)[HL]$)|(^PIC32MX[567][3679][45]F(064|128|256|512)[HL]$)|(^PIC32MX[125][2357][0]F(064|128|256|512)[HL]$)")
    list(APPEND hal_ll_def_list "SPI_BAUD_REG_9_BIT_RESOLUTION")
    ## Match group of PIC32MZ MCU's which utilize both SPIxBRG<8:0> and SPIxBRG<12:0> register bits.
    ## 6th datasheet -> https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MZ%20EF%20Family%20Datasheet_DS60001320G.pdf
elseif(${MCU_NAME} MATCHES "(^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "SPI_BAUD_REG_9_AND_13_BIT_RESOLUTION_MZ")
endif()
## END SPI

## BEGIN PMD
if(${MCU_NAME} MATCHES "(^PIC32MX([12][0-9]{2}|330|350|370|430|450|470|530|550|570)F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
    list(APPEND hal_ll_def_list "HAL_LL_PERIPHERAL_MODULE_DISABLE")
endif()
## END PMD

list(APPEND hal_ll_def_list "MACRO_USAGE_SPI")

mikrosdk_add_library(lib_hal_ll_spi_master MikroSDK.HalLowLevel.SPI.Master
    ${spi_master_implementation}

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
##  BEGIN SPI
    ../../include/spi_master/hal_ll_spi_master.h
    ../../include/spi_master/hal_ll_spi_master_pin_map.h
##  END SPI
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

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_spi_master
    PRIVATE
    ../../include
    ../../include/gpio
##  BEGIN SPI
    ../../include/spi_master
##  END SPI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.SPI.Master)

install(
    FILES
        ../../include/spi_master/hal_ll_spi_master.h
        ../../include/spi_master/hal_ll_spi_master_pin_map.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/hal_ll_port
)
