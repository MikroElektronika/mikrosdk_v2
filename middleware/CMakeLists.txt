## ./middleware/CMakeLists.txt

## TCP/IP stack for Ethernet (also read by middleware/hw and thirdparty):
##   CYCLONETCP - on-chip MACs through CycloneTCP (GPL-2.0-or-later), as before.
##   LWIP       - mikroSDK network API (middleware/net) with lwIP (BSD-3-Clause).
##                On-chip MAC drivers for it are not available yet: Ethernet then
##                works through the controllers of middleware/ethernet.
set(MIKROSDK_NET_STACK "CYCLONETCP" CACHE STRING "TCP/IP stack: CYCLONETCP or LWIP")
set_property(CACHE MIKROSDK_NET_STACK PROPERTY STRINGS CYCLONETCP LWIP)
if(NOT MIKROSDK_NET_STACK MATCHES "^(CYCLONETCP|LWIP)$")
    message(FATAL_ERROR "MIKROSDK_NET_STACK must be CYCLONETCP or LWIP, not \"${MIKROSDK_NET_STACK}\".")
endif()

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

## Network API with lwIP (after ethernet: its adapter uses MikroSDK.Ethernet.Transport).
if(MIKROSDK_NET_STACK STREQUAL "LWIP")
    if(${TOOLCHAIN_ID} STREQUAL "gcc_arm_none_eabi" OR ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
        add_subdirectory(net)
    endif()
endif()
