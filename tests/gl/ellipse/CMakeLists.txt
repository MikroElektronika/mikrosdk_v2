## ./tests/gl/ellipse/CMakeLists.txt
add_executable(test_gl_ellipse
    main.c
    ReadMe.txt
)

target_link_libraries(test_gl_ellipse
    PUBLIC
        Components.TftBoard8
        MikroC.Core
        MikroSDK.Board
)

set(ellipse_def_list)

if(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA3(.+)$")
    list(APPEND ellipse_def_list "__8_bit_interface__")
elseif(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA[45](.+)$")
    if(${_MSDK_BOARD_NAME_} MATCHES "^(.+)PIC32MZ(.+)$")
        list(APPEND ellipse_def_list "__8_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA(PLUS|7FOR)(.+)$")
    if(${_MSDK_BOARD_NAME_} MATCHES "^(.+)PIC32MX(.+)$")
        list(APPEND ellipse_def_list "__8_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_STM32$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_STM32$)|(^MCU_CARD_((4)|(([1][123457])|([2][02345678])|([3][12])))_FOR_STM32$)")
        list(APPEND ellipse_def_list "__16_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__8_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(([247])|([1][01]))_FOR_PIC$)")
        list(APPEND ellipse_def_list "__8_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_PIC32$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_FOR_PIC32$)|(^MCU_CARD_3_FOR_PIC32$)")
        list(APPEND ellipse_def_list "__8_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)_KINETIS$)")
    if(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_5_FOR_KINETIS$)")
        list(APPEND ellipse_def_list "__8_bit_interface__")
    else()
        list(APPEND ellipse_def_list "__16_bit_interface__")
    endif()
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)TIVA$)")
    list(APPEND ellipse_def_list "__16_bit_interface__")
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^MCU_CARD_(.+)RISC_V$)")
    list(APPEND ellipse_def_list "__8_bit_interface__")
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^SIBRAIN_FOR_ATMEGA$)")
    list(APPEND ellipse_def_list "__16_bit_interface__")
elseif(${_MSDK_MCU_CARD_NAME_} MATCHES "(^SIBRAIN_FOR_([D].PIC|PIC[2])(.+)$)")
    list(APPEND ellipse_def_list "__8_bit_interface__")
else()
    list(APPEND ellipse_def_list "__16_bit_interface__")  ## by default select 16-bit port
endif()

if("__16_bit_interface__" IN_LIST ellipse_def_list)
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_16BIT")
elseif("__8_bit_interface__" IN_LIST ellipse_def_list)
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_8BIT")
else()
    set(tft_pin_map_routine "TFT8_MAP_PINOUTS_NOT_DEFINED")
endif()

target_compile_definitions(test_gl_ellipse PRIVATE
    "TFT_BOARD_DRIVER=${_MSDK_TFT_BOARD_}"
    "TFT_MAP_PINOUTS=${tft_pin_map_routine}"
)
