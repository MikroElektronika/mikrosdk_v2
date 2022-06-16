if(${_MSDK_TFT_TP_} MATCHES "^__TP_FT5XX6__$")
    set(touch_controller_lib "MikroSDK.Ft5xx6")
    set(touch_ic "ft5xx6")
    set(touch_ic_cfg_setup_param "&touch_ic_cfg,&${_MSDK_TFT_TP_CONTROLLER_}")
elseif(${_MSDK_TFT_TP_} MATCHES "^__TP_STMPE811__$")
    set(touch_controller_lib "MikroSDK.Stmpe811")
    set(touch_ic "stmpe811")
    set(touch_ic_cfg_setup_param "&touch_ic_cfg")
elseif(${_MSDK_TFT_TP_} MATCHES "^__TP_TSC2003__$")
    set(touch_controller_lib "MikroSDK.Tsc2003")
    set(touch_ic "tsc2003")
    set(touch_ic_cfg_setup_param "&touch_ic_cfg")
else()
    message(FATAL_ERROR "No compatible touch panel available!")
endif()

string(TOUPPER ${touch_ic} touch_ic_upper)
set(PROJECT_TYPE "designer" CACHE STRING "" FORCE)

mikrosdk_add_library(lib_touch_controller MikroSDK.TouchController
    src/touch_controller.c
    include/touch_controller.h
)

target_link_libraries(lib_touch_controller  PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.I2C.Master
    MikroSDK.Board
    Components.TftBoard8
    ${touch_controller_lib}
)

target_compile_definitions(lib_touch_controller
    PUBLIC
        TFT8_MAP_PINOUTS=${tft_pin_map_routine}
        _TFT_BOARD_=${_MSDK_TFT_BOARD_}
        _TFT_TP_ROTATE_=${_MSDK_TFT_TP_ROTATE_}
        _TFT_WIDTH_=${_MSDK_TFT_WIDTH_}
        _TFT_HEIGHT_=${_MSDK_TFT_HEIGHT_}
        ${touch_ic}
        touch_ic_cfg_def=${touch_ic}_cfg_t
        touch_ic_cfg_setup=${touch_ic}_cfg_setup
        touch_ic_cfg_setup_param=${touch_ic_cfg_setup_param}
        touch_ic_context_def=${touch_ic}_t
        touch_ic_default_cfg=${touch_ic}_default_cfg
        touch_ic_init=${touch_ic}_init
        touch_ic_map_pins=${touch_ic_upper}_MAP_PINS
)

target_include_directories(lib_touch_controller
PRIVATE
    include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/middleware/touch_controller>
)

mikrosdk_install(MikroSDK.TouchController)

install(
    FILES
        include/touch_controller.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/middleware/touch_controller
)
