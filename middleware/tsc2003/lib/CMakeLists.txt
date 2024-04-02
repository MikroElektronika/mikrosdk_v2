## ./middleware/tsc2003/lib/CMakeLists.txt
set(tp_address "TSC2003_I2C_SLAVE_ADDR_NOT_DEFINED")

if(NOT DEFINED _MSDK_TFT_WIDTH_)
    set(tft_display_width "0")
else()
    set(tft_display_width ${_MSDK_TFT_WIDTH_})
endif()
if(NOT DEFINED _MSDK_TFT_HEIGHT_)
    set(tft_display_height "0")
else()
    set(tft_display_height ${_MSDK_TFT_HEIGHT_})
endif()
if(NOT DEFINED _MSDK_TFT_TP_)
    set(tft_tp_type "__TP_IC_TSC2003_UNUSED__")
else()
    if (${_MSDK_TFT_TP_} MATCHES "__TP_TSC2003__" )
        set(tft_tp_type ${_MSDK_TFT_TP_})
        set(tp_address "TSC2003_I2C_SLAVE_ADDR_DB=${_TSC2003_I2C_ADDRESS_}")
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
    ${tp_address}
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
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/tsc2003 MikroSDK.Tsc2003 include/tsc2003.h)
