## ./components/tft8/common/CMakeLists.txt
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(_MSDK_TFT_BOARD_)
        if(${_MSDK_TFT_BOARD_} MATCHES "(TFT_BOARD_[3457]_(CAPACITIVE|RESISTIVE))|(^MIKROMEDIA(.+)$)")
            add_subdirectory(ssd1963)
        endif()
    endif()
endif()
