if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EVAL_WITH_STM32F303VE_MCU")
    set(BOARD_PATH   "include/boards/board_eval_with_stm32f303ve")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()
