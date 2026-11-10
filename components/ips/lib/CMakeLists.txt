## ./components/ips/lib/CMakeLists.txt
# IPS_DISPLAY_2_CLICK -> MIKROBUS_POSITION_IPSDISPLAY2, IPS_DISPLAY_1_CLICK -> ..._IPSDISPLAY1
# (same rule NECTO uses to name the variable it passes).
string(REGEX REPLACE "_CLICK$" "" _ips_click "${_MSDK_TFT_BOARD_}")
string(REPLACE "_" "" _ips_click "${_ips_click}")
set(_ips_position_var "MIKROBUS_POSITION_${_ips_click}")

ips_lvgl_mikrobus_selection(${CMAKE_CURRENT_BINARY_DIR}/include ips_lvgl_mikrobus.h
                            ${${_ips_position_var}})

mikrosdk_add_library(lib_ips Components.IpsDisplay
    src/ips.c

    include/ips.h
    ${CMAKE_BINARY_DIR}/generated/ips_lvgl_mikrobus.h
)

target_link_libraries(lib_ips
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.SPI.Master
        MikroSDK.ST7789
        MikroSDK.GraphicLibrary
)
target_compile_definitions(lib_ips
    PUBLIC
        "TFT_MAP_PINOUTS=IPS_MAP_PINOUTS"
)

target_include_directories(lib_ips
    PRIVATE
        include
        ${CMAKE_BINARY_DIR}/generated
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include/components/ips>
)

mikrosdk_install(Components.IpsDisplay)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ips Components.IpsDisplay include/ips.h ${CMAKE_BINARY_DIR}/generated/ips_lvgl_mikrobus.h)
