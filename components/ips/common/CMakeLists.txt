## ./components/ips/common/CMakeLists.txt
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(_MSDK_TFT_BOARD_)
        if(${_MSDK_TFT_BOARD_} MATCHES "^IPS_DISPLAY_[12]_CLICK$")
            add_subdirectory(st7789)
        endif()
    endif()
endif()
