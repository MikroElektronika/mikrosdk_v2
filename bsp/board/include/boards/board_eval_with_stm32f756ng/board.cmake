if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EVAL_WITH_STM32F756NG_MCU")
    set(BOARD_PATH   "include/boards/board_eval_with_stm32f756ng")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()
