add_executable(test_tft_jig
    src/main.c

    inc/tft_defines.h
    inc/tft_connections.h

    ReadMe.txt
)

set(tft_list "")

if ( ${_MSDK_BOARD_NAME_} MATCHES "(^BOARD(.+)(FUSION|PRO)(.+)V8$)|(^MIKROMEDIA(.+)$)" )
    list(APPEND tft_list "__SSD1963__")
elseif( ${_MSDK_BOARD_NAME_} MATCHES "(^BOARD(.+)(FUSION|PRO)(.+)V8$)|(^MIKROMEDIA(.+)$)" )
    list(APPEND tft_list "__ILI9341__")
else()
    list(APPEND tft_list "__TFT_NOT_SUPPORTED__")
endif()

if ( ${_MSDK_BOARD_NAME_} MATCHES "MIKROMEDIA3(.+)" )
    list(APPEND tft_list "__8_bit_interface__")
elseif( ${_MSDK_BOARD_NAME_} MATCHES "MIKROMEDIA[45](.+)" )
    list(APPEND tft_list "__16_bit_interface__")
elseif( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_STM32$)" )
    if ( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_STM32$)|(^MCU_CARD_((4)|(([1][123457])|([2][02345678])|([3][12])))_FOR_STM32$)" )
        list(APPEND tft_list "__16_bit_interface__")
    else()
        list(APPEND tft_list "__8_bit_interface__")
    endif()
elseif( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC$)" )
    if ( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(([247])|(10))_FOR_PIC$)" )
        list(APPEND tft_list "__8_bit_interface__")
    else()
        list(APPEND tft_list "__16_bit_interface__")
    endif()
elseif( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC32$)" )
    if ( ${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_PIC32$)" )
        list(APPEND tft_list "__8_bit_interface__")
    else()
        list(APPEND tft_list "__16_bit_interface__")
    endif()
else()
    list(APPEND tft_list "__8_bit_interface__") # by default select 8-bit port
endif()
# TODO -- add 24-bit

target_compile_definitions(test_tft_jig PUBLIC
    ${tft_list}
)

target_link_libraries(test_tft_jig PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)

target_include_directories(test_tft_jig
PRIVATE
    inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)
