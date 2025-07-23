## ./middleware/CMakeLists.txt
## Note that DIP packages with less than 40 pins
## do not have pins routed to the TFT connector.
## Make sure to select a DIP40 MCU if using a board
## with DIP sockets.
## Additionally, EasyMx PRO v7 for Tiva C Series MCU card with TM4C123GH6PMI
## and PIC18F45K80 and PIC18F46K80 do not have adequate connections as well.
if(${MSDK_BUILD_TFT_MODULES})
    set(ILI9341_SUPPORT_CHECK FALSE)
    if(DEFINED _MSDK_MCU_CARD_NAME_)
        if( NOT ("${_MSDK_MCU_CARD_NAME_}" STREQUAL ""))
            if( "${_MSDK_MCU_CARD_NAME_}" STREQUAL "EASYMX_PRO_V7_FOR_TIVA_MCU_CARD_WITH_TM4C123GH6PMI" )
                set(ILI9341_SUPPORT_CHECK TRUE)
                set(ERR_MESSAGE "EasyMx PRO v7 for Tiva C Series MCU card with TM4C123GH6PMI does not have necessary ILI9341 connections for selected board! Select a different card.")
            endif()
        endif()
    elseif(DEFINED _MSDK_DIP_SOCKET_TYPE_)
        if( NOT ("${_MSDK_DIP_SOCKET_TYPE_}" STREQUAL ""))
            if( NOT ("${_MSDK_DIP_SOCKET_TYPE_}" STREQUAL "DIP40") )
                set(ILI9341_SUPPORT_CHECK TRUE)
                set(ERR_MESSAGE "${_MSDK_DIP_SOCKET_TYPE_} ${MCU_NAME} does not have necessary ILI9341 connections for selected board! Select a DIP40 package MCU.")
            endif()
        endif()
    endif()

    if(${_MSDK_TFT_BOARD_} MATCHES "^TFT_BOARD_EASY$")
        add_subdirectory(ili9341)
        add_subdirectory(tp_mikroe)
    else()
        add_subdirectory(ssd1963)
        add_subdirectory(ft5xx6)
        add_subdirectory(stmpe811)
        add_subdirectory(tsc2003)
        add_subdirectory(ft800)
    endif()
    add_subdirectory(touch_controller)
endif()

memory_test_check(enough_memory)
if(${enough_memory} STREQUAL "true")
    add_subdirectory(filesystem)
    add_subdirectory(physical_drive)
endif()

## USB and ETHERNET related HW init routines.
add_subdirectory(hw)

## LCD library.
add_subdirectory(lcd)

## GLCD library
add_subdirectory(glcd)
