if(${_MSDK_BOARD_NAME_} STREQUAL "PIC32_BLUETOOTH_AUDIO_DEVELOPMENT_KIT")
    set(BOARD_PATH "include/boards/board_development_kit_pic32_bluetooth_audio")
    set(PIM_SOCKET TRUE)
    set(SHIELD FALSE)
    set(DIP_SOCKET FALSE)
endif()
