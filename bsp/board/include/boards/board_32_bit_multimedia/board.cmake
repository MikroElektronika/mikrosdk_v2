if(${_MSDK_BOARD_NAME_} STREQUAL "32_BIT_MULTIMEDIA_BOARD")
    set(BOARD_PATH "include/boards/board_32_bit_multimedia")
    set(MCU_CARD FALSE)
    set(SHIELD FALSE)
endif()