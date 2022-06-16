if (NOT DEFINED MSDK_TFT_TP)
    set(tft_tp_type "__TP_IC_FT5XX6_UNUSED__")
else()
    if (${MSDK_TFT_TP} MATCHES "__TP_FT5XX6__")
        set(tft_tp_type ${MSDK_TFT_TP})
    else()
        set(tft_tp_type "__TP_IC_FT5XX6_UNUSED__")
    endif()
endif()

mikrosdk_add_library(lib_ft5xx6 MikroSDK.Ft5xx6
    src/ft5xx6.c
    
    include/ft5xx6.h
)

target_link_libraries(lib_ft5xx6  PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.I2C.Master
)

target_compile_definitions(lib_ft5xx6 PUBLIC 
    ${tft_tp_type}
)

target_include_directories(lib_ft5xx6
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/middleware/ft5xx6>
)

mikrosdk_install( MikroSDK.Ft5xx6)

install(
    FILES
        include/ft5xx6.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/middleware/ft5xx6
)
