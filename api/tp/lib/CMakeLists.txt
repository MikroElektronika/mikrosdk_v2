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

mikrosdk_add_library(lib_tp MikroSDK.TouchPanel
    src/tp.c
    include/tp.h
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
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/api/tp>
)

mikrosdk_install(MikroSDK.TouchPanel)

install(
    FILES
        include/tp.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/api/tp
)
