## ./targets/pic_8bit/mikroe/pic18/src/spi_master/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()
list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if ((${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q(43|8[34])"))
    set(spi_master_implementation "implementation_2")
else()
    set(spi_master_implementation "implementation_1")
endif()

## SPI baud rate implementations. ##
## Baud rate implementation 1 utilizes SPIxCON1 register and three possible prescalers (Fosc/4, Fosc/16 and Fosc/64).
if (${MCU_NAME} MATCHES "(^PIC18L?F(([24]455)|([24]550))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(([24]458)|([24]553))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[24]((4|5|6))J11$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(24|25|26|44|45|46)J50$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(([24]515)|([24]610))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(([24]525)|([24]620))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(((2|4)585)|(2|4)680)$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[246](5|6)K80$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?L?F(([24]682)|([24]685))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F[24]6K20$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18((F[68](520|620|720))|(LF[68](520))|(LF[8](720)))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F(([68]525)|([68]621))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(([68][56]27)|([68][67]22))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F(([68]585)|([68]680))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F((6(5|6)J15)|(8(5|6)J15)|((6|8)(5|6|7)J10))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[68](3|4|5|6|7)J11$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F[68](((6)J55)|((5|6|7)J50))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F(([68]628)|(([68])723))$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[68]6J16$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F[689](6|7)J(60|65)$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F[6,8]((5|6|7))J90$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F[68]((6|7))J93$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "(^PIC18F8[67]J72$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1")

## Baud rate implementation 2 utilizes SPIxCON1 register and four possible prescalers (Fosc/4, Fosc/8, Fosc/16 and Fosc/64).
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[42][67]J[15][3]$)|(^PIC18F[68][567]K(22|90)$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_2")
## Baud rate implementation 3 utilizes SPIxCON1 register (clock selection) and 8-bits of prescaling resolution register (SSPxADD).
elseif (${MCU_NAME} MATCHES "PIC18L?F2(4K(22|40|50)|5K(22|40|50)|6K(22|40)|7K(40))")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
elseif (${MCU_NAME} MATCHES "PIC18L?F4(5K(22|40|50)|6K(22|40)|7K(40))")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
elseif (${MCU_NAME} MATCHES "PIC18L?F6(5K(40)|6K(40)|7K(40))")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
elseif (${MCU_NAME} MATCHES "PIC18F[24][4567]Q10")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
elseif (${MCU_NAME} MATCHES "PIC18F[689][567]J94")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
elseif (${MCU_NAME} MATCHES "PIC18L?F[246][567]K40$")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3")
## Baud rate implementation 4 utilizes SPIxCLK register and 8-bits of prescaling resolution register (SPIxBAUD).
elseif (${MCU_NAME} MATCHES "(^PIC18L?F[245][567]K42$)|(^PIC18.+Q(43|8[34])$)")
    list(APPEND hal_ll_def_list "HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_4")
else()
    list(APPEND hal_ll_def_list "__mcu_not_supported__")
endif()
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
# ::  END SPI
)

target_compile_definitions(lib_hal_ll_spi_master PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_spi_master
PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
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
