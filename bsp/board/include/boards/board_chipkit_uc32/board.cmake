if(${_MSDK_BOARD_NAME_} STREQUAL "CHIPKIT_UC32_DEVELOPMENT_BOARD")
    set(BOARD_PATH "include/boards/board_chipkit_uc32")
    set(MCU_CARD FALSE)
    set(SHIELD FALSE)
endif()