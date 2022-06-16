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
    set(tft_tp_type "__TP_IC_TSC2003_UNUSED__")
else()
    if (${MSDK_TFT_TP} MATCHES "__TP_TSC2003__" )
        set(tft_tp_type ${MSDK_TFT_TP})
    else()
        set(tft_tp_type "__TP_IC_TSC2003_UNUSED__")
    endif()
endif()

mikrosdk_add_library(lib_tsc2003 MikroSDK.Tsc2003
    src/tsc2003.c
    include/tsc2003.h
)

target_link_libraries(lib_tsc2003  PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.I2C.Master
)
target_compile_definitions(lib_tsc2003 PUBLIC
    ${tft_tp_type}
    TFT_DISPLAY_WIDTH=${tft_display_width}
    TFT_DISPLAY_HEIGHT=${tft_display_height}
)

target_include_directories(lib_tsc2003
PRIVATE
    include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/middleware/tsc2003>
)

mikrosdk_install(MikroSDK.Tsc2003)

install(
    FILES
        include/tsc2003.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/middleware/tsc2003
)
