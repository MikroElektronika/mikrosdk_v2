if(${_MSDK_BOARD_NAME_} STREQUAL "EXPLORER_16_DEVELOPMENT_BOARD")
    set(BOARD_PATH "include/boards/board_explorer_16_development")
    set(PIM_SOCKET TRUE)
    set(SHIELD FALSE)
    set(DIP_SOCKET FALSE)
endif()
