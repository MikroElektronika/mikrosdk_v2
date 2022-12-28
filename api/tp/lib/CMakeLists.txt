## ./api/tp/lib/CMakeLists.txt
#WIDTH
if(NOT DEFINED _MSDK_TFT_WIDTH_)
    set(tft_display_width "0")
else()
    set(tft_display_width ${_MSDK_TFT_WIDTH_})
endif()
#HEIGHT
if(NOT DEFINED _MSDK_TFT_HEIGHT_)
    set(tft_display_height "0")
else()
    set(tft_display_height ${_MSDK_TFT_HEIGHT_})
endif()

#TP TYPE
if(NOT DEFINED _MSDK_TFT_TP_)
    set(tft_tp_type "__TP_IC_UNDEFINED__")
else()
    set(tft_tp_type ${_MSDK_TFT_TP_})
endif()

if(${_MSDK_TFT_BOARD_} MATCHES "^TFT_BOARD_EASY$")
    set(tp tp_mikroe)
else()
    set(tp tp)
endif()

message(DEBUG ": ${tp} implementation used.")

mikrosdk_add_library(lib_tp MikroSDK.TouchPanel
    src/${tp}/tp.c
    include/${tp}/tp.h
)

target_compile_definitions(lib_tp PUBLIC
    ${tft_tp_type}
    TFT_DISPLAY_WIDTH=${tft_display_width}
    TFT_DISPLAY_HEIGHT=${tft_display_height}
)

target_link_libraries(lib_tp  PUBLIC
    MikroC.Core
)

target_include_directories(lib_tp
PRIVATE
    include/${tp}
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${tp}>
    $<INSTALL_INTERFACE:include/api/tp>
)

mikrosdk_install(MikroSDK.TouchPanel)
install_headers(${CMAKE_INSTALL_PREFIX}/include/api/tp MikroSDK.TouchPanel include/${tp}/tp.h)

