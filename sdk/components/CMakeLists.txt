## ./components/CMakeLists.txt
if (${MSDK_BUILD_TFT_MODULES})
    if(${_MSDK_TFT_BOARD_} MATCHES "^TFT_BOARD_EASY$")
        add_subdirectory(tft7)
    else()
        add_subdirectory(tft8)
    endif()
endif()
