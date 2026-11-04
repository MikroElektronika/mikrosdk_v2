## ./components/CMakeLists.txt
if (${MSDK_BUILD_TFT_MODULES})
    if(${_MSDK_TFT_BOARD_} MATCHES "^TFT_BOARD_EASY$")
        add_subdirectory(tft7)
    elseif( ${_MSDK_TFT_BOARD_} MATCHES "^IPS_DISPLAY_[12]_CLICK$" )
        add_subdirectory(ips)
    elseif( ${_MSDK_TFT_BOARD_} MATCHES "^EVE_CLICK$" )
        add_subdirectory(eve)
    else()
        add_subdirectory(tft8)
    endif()
endif()

# Ethernet components.
add_subdirectory(ethernet)
