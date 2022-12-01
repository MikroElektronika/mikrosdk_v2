set(tft8_def_list)

if(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA3(.+)$")
    list(APPEND tft8_def_list "__8_bit_interface__")
elseif(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA[45](.+)$")
    if(${_MSDK_BOARD_NAME_} MATCHES "^(.+)PIC32MZ(.+)$")
        list(APPEND tft8_def_list "__8_bit_interface__")
    else()
        list(APPEND tft8_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA(PLUS|7FOR)(.+)$")
    if(${_MSDK_BOARD_NAME_} MATCHES "^(.+)PIC32MX(.+)$")
        list(APPEND tft8_def_list "__8_bit_interface__")
    else()
        list(APPEND tft8_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_STM32$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_STM32$)|(^MCU_CARD_((4)|(([1][123457])|([2][02345678])|([3][12])))_FOR_STM32$)")
        list(APPEND tft8_def_list "__16_bit_interface__")
    else()
        list(APPEND tft8_def_list "__8_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(([247])|([1][01]))_FOR_PIC$)")
        list(APPEND tft8_def_list "__8_bit_interface__")
    else()
        list(APPEND tft8_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC32$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_PIC32$)|(^MCU_CARD_3_FOR_PIC32$)")
        list(APPEND tft8_def_list "__8_bit_interface__")
    else()
        list(APPEND tft8_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_KINETIS$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_5_FOR_KINETIS$)")
        list(APPEND tft8_def_list "__8_bit_interface__")
    else()
        list(APPEND tft8_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)TIVA$)")
    list(APPEND tft8_def_list "__16_bit_interface__")
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)RISC_V$)")
    list(APPEND tft8_def_list "__8_bit_interface__")
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^SIBRAIN_FOR_ATMEGA$)")
    list(APPEND tft8_def_list "__16_bit_interface__")
else()
    list(APPEND tft8_def_list "__16_bit_interface__")  ## by default select 16-bit port
endif()

if("__16_bit_interface__" IN_LIST tft8_def_list)
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_16BIT")
elseif("__8_bit_interface__" IN_LIST tft8_def_list)
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_8BIT")
else()
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_NOT_DEFINED")
endif()

if (NOT DEFINED _MSDK_TFT_TYPE_)
    list(APPEND tft8_def_list "__tft_not_selected__")
else()
    if (${_MSDK_TFT_TYPE_} MATCHES "__TFT_RESISTIVE__")
        list(APPEND tft8_def_list "__resistive__")
    elseif(${_MSDK_TFT_TYPE_} MATCHES "__TFT_CAPACITIVE__")
        list(APPEND tft8_def_list "__capacitive__")
    endif()
endif()

mikrosdk_add_library(lib_tft8 Components.TftBoard8
    src/tft8.c

    include/tft8.h
)

target_link_libraries(lib_tft8
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.GPIO.Port
        MikroSDK.Ssd1963
        MikroSDK.GraphicLibrary
)
target_compile_definitions(lib_tft8
    PUBLIC
        ${tft8_def_list}
        "TFT8_MAP_PINOUTS=${tft_pin_map_routine}"
)

target_include_directories(lib_tft8
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/components/tft8>
)

mikrosdk_install(Components.TftBoard8)

install(
    FILES
        include/tft8.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/components/tft8
)
