#############################################################################
## Checks if selected MCU has rtc
#############################################################################
function(check_rtc has_rtc)
    set(has_rtc "false" PARENT_SCOPE)

    if(${MCU_NAME} MATCHES "^STM32.+")
        set(has_rtc "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^TM4C.+")
        if(${MCU_NAME} MATCHES "^TM4C129.+")
            set(has_rtc "true" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "TM4C123[137BG].+")
            set(has_rtc "true" PARENT_SCOPE)
        endif()
    elseif(${MCU_NAME} MATCHES "^MK[0-9].+")
            set(has_rtc "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+")
        set(has_rtc "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^PIC32.+")
        set(has_rtc "true" PARENT_SCOPE)
    endif()

endfunction()