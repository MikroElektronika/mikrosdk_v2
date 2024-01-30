## ./components/tft7/common/CMakeLists.txt
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(_MSDK_TFT_BOARD_)
        if(${_MSDK_TFT_BOARD_} STREQUAL "TFT_BOARD_EASY")
            add_subdirectory(ili9341)
        endif()
    endif()
endif()
