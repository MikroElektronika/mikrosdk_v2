if(${_MSDK_BOARD_NAME_} STREQUAL "ATSAME70_MOTOR_CONTROL_CARD")
    set(BOARD_PATH "include/boards/board_atsame70_motor_control_card")
    set(MCU_CARD FALSE)
    set(SHIELD FALSE)
    set(DIP_SOCKET FALSE)
endif()
