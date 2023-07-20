## ./middleware/tp_mikroe/lib/CMakeLists.txt
set(tp_mikroe_def_list)

set_tp_mikroe_pins(CMAKE_READ_X CMAKE_READ_Y)
list(APPEND tp_mikroe_def_list TP_READ_X_CMAKE=${CMAKE_READ_X})
list(APPEND tp_mikroe_def_list TP_READ_Y_CMAKE=${CMAKE_READ_Y})

if(NOT DEFINED MSDK_TFT_WIDTH)
    set(tft_display_width "0")
else()
    set(tft_display_width ${MSDK_TFT_WIDTH})
endif()
if(NOT DEFINED MSDK_TFT_HEIGHT)
    set(tft_display_height "0")
else()
    set(tft_display_height ${MSDK_TFT_HEIGHT})
endif()
if(NOT DEFINED MSDK_TFT_TP)
    set(tft_tp_type "__TP_IC_MIKROE_UNUSED__")
else()
    if (${MSDK_TFT_TP} MATCHES "__TP_MIKROE__" )
        set(tft_tp_type ${MSDK_TFT_TP})
    else()
        set(tft_tp_type "__TP_IC_MIKROE_UNUSED__")
    endif()
endif()

if((${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIAFORPIC18F[JK]$") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_FUSION_V7"))
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_0=TP_ROTATE_90")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_1=TP_ROTATE_180")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_2=TP_ROTATE_270")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_3=TP_ROTATE_0")
    if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_FUSION_V7")
        list(APPEND tp_mikroe_def_list "ANALOG_IN_VREF_CMAKE=ANALOG_IN_VREF_INTERNAL")
    else()
        list(APPEND tp_mikroe_def_list "ANALOG_IN_VREF_CMAKE=ANALOG_IN_VREF_EXTERNAL")
    endif()
else()
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_0=TP_ROTATE_0")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_1=TP_ROTATE_90")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_2=TP_ROTATE_180")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_ROTATE_CASE_3=TP_ROTATE_270")
    list(APPEND tp_mikroe_def_list "ANALOG_IN_VREF_CMAKE=ANALOG_IN_VREF_EXTERNAL")
    list(APPEND tp_mikroe_def_list "TP_MIKROE_TRANSISTOR_LOGIC")
endif()

mikrosdk_add_library(lib_tp_mikroe MikroSDK.TpMikroe
    src/tp_mikroe.c

    include/tp_mikroe.h
)

target_link_libraries(lib_tp_mikroe  PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.GenericPointer
    MikroSDK.GraphicLibrary
    MikroSDK.TouchPanel
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.ADC
)
target_compile_definitions(lib_tp_mikroe PUBLIC
    ${tft_tp_type}
    TFT_DISPLAY_WIDTH=${tft_display_width}
    TFT_DISPLAY_HEIGHT=${tft_display_height}
)

target_compile_definitions(lib_tp_mikroe
    PUBLIC
        ${tp_mikroe_def_list}
)

target_include_directories(lib_tp_mikroe
PRIVATE
    include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/middleware/tp_mikroe>
)

mikrosdk_install(MikroSDK.TpMikroe)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/tp_mikroe MikroSDK.TpMikroe include/tp_mikroe.h)
