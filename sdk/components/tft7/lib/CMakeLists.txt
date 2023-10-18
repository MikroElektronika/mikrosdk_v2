## ./components/tft7/lib/CMakeLists.txt
set(tft7_def_list)

if(${_MSDK_BOARD_NAME_} MATCHES "(^BOARD_EASY((MX(.+)_V7.+$)|(PIC_V[78]$)|(PIC_.+V7$)|(AVR_V[78])))|(^MIKROMEDIAFOR.+$)")
    list(APPEND tft7_def_list "__8_bit_interface__")
    set(tft_pin_map_routine "TFT7_MAP_CTRL_8BIT")
else()
    list(APPEND tft7_def_list "__16_bit_interface__")
    set(tft_pin_map_routine "TFT7_MAP_CTRL_16BIT")
endif()

mikrosdk_add_library(lib_tft7 Components.TftBoard7
    src/tft7.c

    include/tft7.h
)

target_link_libraries(lib_tft7
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.GPIO.Port
        MikroSDK.Ili9341
        MikroSDK.TpMikroe
        MikroSDK.GraphicLibrary
        MikroSDK.Board
)

target_compile_definitions(lib_tft7
    PUBLIC
        ${tft7_def_list}
        "TFT_MAP_PINOUTS=${tft_pin_map_routine}"
)

target_include_directories(lib_tft7
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/components/tft7>
)

mikrosdk_install(Components.TftBoard7)

install(
    FILES
        include/tft7.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/components/tft7
)
