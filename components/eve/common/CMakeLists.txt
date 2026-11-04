## ./components/eve/common/CMakeLists.txt
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(_MSDK_TFT_BOARD_)
        if(${_MSDK_TFT_BOARD_} MATCHES "^EVE_CLICK$")
            add_subdirectory(ft800)
        endif()
    endif()
endif()
