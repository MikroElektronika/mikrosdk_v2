if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAPLUSFORSTM32")
    set(BOARD_PATH   "include/boards/mikromedia_plus_stm32")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()
