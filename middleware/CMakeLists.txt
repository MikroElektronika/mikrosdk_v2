## ./middleware/CMakeLists.txt
if(${MSDK_BUILD_TFT_MODULES})
    if(${_MSDK_TFT_BOARD_} MATCHES "^TFT_BOARD_EASY$")
        add_subdirectory(ili9341)
        add_subdirectory(tp_mikroe)
    else()
        add_subdirectory(ssd1963)
        add_subdirectory(ft5xx6)
        add_subdirectory(stmpe811)
        add_subdirectory(tsc2003)
        add_subdirectory(st7789)
        if(NOT(${TOOLCHAIN_ID} STREQUAL "mikrocavr"))
            add_subdirectory(ft800)
        endif()
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

## GLCD library.
add_subdirectory(glcd)

# Ethernet library.
add_subdirectory(ethernet)
