## ./bsp/board/CMakeLists.txt
## Default values
set(MCU_CARD  TRUE)
set(DIP_SOCKET  FALSE)
set(MIKROBUS  TRUE)
set(SHIELD FALSE)
set(IS_CUSTOM_BOARD FALSE)
set(PIM_SOCKET FALSE)

include(utils)

# CUSTOM BOARD SETTING
foreach(__CUSTOM_INCLUDE_FILE__ IN LISTS __MSDK_CUSTOM_BOARD_INCLUDES__)
    include("${__CUSTOM_INCLUDE_FILE__}")
endforeach()

## Add all board specific cmake files recursivelly
file(GLOB_RECURSE CMAKE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/board/include/boards *.cmake)
foreach(cmakeFile ${CMAKE_FILES})
    include(${cmakeFile})
endforeach()

if(MCU_CARD)
    string(TOLOWER ${_MSDK_MCU_CARD_NAME_} MSDK_FILTERED_MCU_CARD)
    if(${_MSDK_MCU_CARD_NAME_} STREQUAL "")
        set(BOARD_PATH   "include/boards/board_generic")
        set(MCU_CARD  FALSE)
        set(MIKROBUS  FALSE)
    endif()
elseif(DIP_SOCKET)
    string(TOLOWER ${_MSDK_DIP_SOCKET_TYPE_} MSDK_FILTERED_DIP_SOCKET_TYPE)
    if(${_MSDK_DIP_SOCKET_TYPE_} STREQUAL "")
        set(BOARD_PATH   "include/boards/board_generic")
        set(MCU_CARD  FALSE)
        set(DIP_SOCKET  FALSE)
        set(MIKROBUS  FALSE)
    endif()
endif()

if (NOT DEFINED MSDK_SHIELD)
    set(MSDK_SHIELD "false")
endif()

if (SHIELD)
    string(TOLOWER ${_MSDK_SHIELD_} SHIELD_PATH)
else()
    set(SHIELD_PATH "SHIELD_WRONG_PATH")
endif()

set(MCU_CARD_PATH  "MCU_CARD_WRONG_PATH")
if (SDK_SETUP_BUILD)
    if (MCU_CARD)
        set(MCU_CARD_PATH  ${MSDK_FILTERED_MCU_CARD}/${MCU_NAME})
    endif()
else()
    if (MCU_CARD)
        set(MCU_CARD_PATH  ${MSDK_FILTERED_MCU_CARD})
    endif()
endif()

if (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "(^dip((14$)|(18$)|(20$)|(28$)|(40$)))")
    set(dip_socket_check TRUE)
else()
    set(dip_socket_check FALSE)
endif()

if ((DIP_SOCKET) AND (dip_socket_check))
    set(BOARD_DIP_SOCKET_PATH  ${MSDK_FILTERED_DIP_SOCKET_TYPE})
elseif((DIP_SOCKET) AND (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip.*"))
    set(BOARD_DIP_SOCKET_PATH  "WRONG_DIP_SELECTED")
elseif((DIP_SOCKET) AND NOT (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip.*"))
    set(BOARD_DIP_SOCKET_PATH  "NO_DIP_SELECTED")
endif()

set(HEADERS_LIST ${BOARD_PATH}/board.h)
set(INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH})

if (MCU_CARD)
        list(APPEND HEADERS_LIST include/mcu_cards/${MCU_CARD_PATH}/mcu_card.h)
        list(APPEND INCLUDE_HEADERS_PATH_LIST include/mcu_cards/${MCU_CARD_PATH})
endif()
if(DIP_SOCKET)
        # TODO
        # Add appropriate dip_socket header files per MCU.
        # At the moment all non AVR and dsPIC MCUs take one socket header file.
        # e.g. if DIP40 socket on the board has both A and B sockets, socket B will be taken by default.
        list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH})
        if ((${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip[24][08]$") AND ((${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_V7") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_V8") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC30") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V7_FOR_DSPIC30") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC24_33")))
            list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/dip_sockets)
            if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip20")
                set (BOARD_DIP_SOCKET_PATH dip20b)
                list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip20b/dip_socket.h)
            endif()
            # EasyAVR v7 board has only one dip28 socket.
            if (NOT ${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_V7")
                if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip28")
                    set (BOARD_DIP_SOCKET_PATH dip28b)
                    list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip28b/dip_socket.h)
                endif()
            endif()
            if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip40")
                set (BOARD_DIP_SOCKET_PATH dip40b)
                list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip40b/dip_socket.h)
            endif()
        else()
            list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH}/dip_socket.h)
        endif()
endif()

if (PIM_SOCKET)
    list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/pim_socket)
    list(APPEND HEADERS_LIST ${BOARD_PATH}/pim_socket/pim_socket.h)
endif()

if (SHIELD)
    list(APPEND HEADERS_LIST include/shields/${SHIELD_PATH}/shield.h)
endif()

mikrosdk_add_interface_library(lib_board MikroSDK.Board
    ${HEADERS_LIST}
)

set(package_list "")
set(module_list "")

## TODO - add new modules as implemented
find_include_package(package_list module_list MikroSDK.Driver.ADC)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.In)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.Out)
find_include_package(package_list module_list MikroSDK.Driver.GPIO.Port)
find_include_package(package_list module_list MikroSDK.Driver.I2C.Master)
find_include_package(package_list module_list MikroSDK.Driver.PWM)
find_include_package(package_list module_list MikroSDK.Driver.SPI.Master)
find_include_package(package_list module_list MikroSDK.Driver.UART)
find_include_package(package_list module_list MikroSDK.Driver.OneWire)
find_include_package(package_list module_list MikroSDK.Driver.CAN)
find_include_package(package_list module_list MikroSDK.Driver.DMA)
find_include_package(package_list module_list MikroSDK.Driver.RTC)

foreach(package ${module_list})
    target_compile_definitions(lib_board
        INTERFACE
            ${package}
    )
endforeach()

set(BOARD_PATH_INTERFACE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/")
if(IS_CUSTOM_BOARD)
    set(BOARD_PATH_INTERFACE_INCLUDE "")
endif()

target_include_directories(lib_board
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${BOARD_PATH_INTERFACE_INCLUDE}${BOARD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/shields/${SHIELD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_cards/${MCU_CARD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${BOARD_PATH}/pim_socket>
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/board>
)

target_link_libraries(lib_board INTERFACE
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.MikroBus
)

mikrosdk_install(MikroSDK.Board)
install_headers(${CMAKE_INSTALL_PREFIX}/include/board MikroSDK.Board ${HEADERS_LIST})
