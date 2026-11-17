## ./CMakeLists.txt
cmake_minimum_required(VERSION 3.11)

if (NOT DEFINED IS_BARE_METAL)
    set(IS_BARE_METAL FALSE)
endif()

if (NOT DEFINED MIKROSDK_CURRENT_VERSION)
    set(MIKROSDK_CURRENT_VERSION 2.0.0)
endif()

if (NOT DEFINED REDUCE_LAYER)
    set(REDUCE_LAYER true)
endif()

if (${IS_BARE_METAL})
    set(PROJECT_NAME_CUSTOM "BareMetal")
else()
    set(PROJECT_NAME_CUSTOM "MikroSDK")
endif()

# Mark specific files as unchanged to avoid accidental commits
execute_process(
    COMMAND git update-index --assume-unchanged
            thirdparty/usb/tinyusb/config/tusb_config.h
            thirdparty/usb/tinyusb/isr/include/usb_isr_routines.h
            thirdparty/usb/tinyusb/isr/src/usb_isr_routines.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    ERROR_QUIET
)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(${PROJECT_NAME_CUSTOM} VERSION ${MIKROSDK_CURRENT_VERSION} LANGUAGES MikroC)
else()
    project(${PROJECT_NAME_CUSTOM} VERSION ${MIKROSDK_CURRENT_VERSION} LANGUAGES C ASM)
    if(NOT ${TOOLCHAIN_ID} STREQUAL "mchp_xc8")
        add_compile_options("-fms-extensions")
    endif()
endif()

# Link MikroC.Core for all toolchains
find_package(MikroC.Core)

set(CMAKE_STATIC_LIBRARY_PREFIX "")

list(APPEND CMAKE_MODULE_PATH "${${PROJECT_NAME_CUSTOM}_SOURCE_DIR}/cmake")

# Build Tft modules by default if not specified differently
if (NOT DEFINED MSDK_BUILD_TFT_MODULES)
    set(MSDK_BUILD_TFT_MODULES TRUE)
endif()

## Note that DIP packages with less than 40 pins
## do not have pins routed to the TFT connector.
## Make sure to select a DIP40 MCU if using a board
## with DIP sockets.
## Additionally, EasyMx PRO v7 for Tiva C Series MCU card with TM4C123GH6PMI
## does not have adequate connections as well.
## In such cases ILI9341/TP_MIKROE pins expand to nothing, so skip TFT modules.
if(${MSDK_BUILD_TFT_MODULES} AND ("${_MSDK_TFT_BOARD_}" MATCHES "^TFT_BOARD_EASY$"))
    set(ILI9341_SUPPORT_CHECK FALSE)
    if(DEFINED _MSDK_MCU_CARD_NAME_ AND NOT ("${_MSDK_MCU_CARD_NAME_}" STREQUAL ""))
        if("${_MSDK_MCU_CARD_NAME_}" STREQUAL "EASYMX_PRO_V7_FOR_TIVA_MCU_CARD_WITH_TM4C123GH6PMI")
            set(ILI9341_SUPPORT_CHECK TRUE)
            set(ERR_MESSAGE "EasyMx PRO v7 for Tiva C Series MCU card with TM4C123GH6PMI does not have necessary ILI9341 connections for selected board! Select a different card.")
        endif()
    elseif(DEFINED _MSDK_DIP_SOCKET_TYPE_ AND NOT ("${_MSDK_DIP_SOCKET_TYPE_}" STREQUAL ""))
        if(NOT ("${_MSDK_DIP_SOCKET_TYPE_}" STREQUAL "DIP40"))
            set(ILI9341_SUPPORT_CHECK TRUE)
            set(ERR_MESSAGE "${_MSDK_DIP_SOCKET_TYPE_} ${MCU_NAME} does not have necessary ILI9341 connections for selected board! Select a DIP40 package MCU.")
        endif()
    endif()

    if(${ILI9341_SUPPORT_CHECK})
        message(WARNING "${ERR_MESSAGE} TFT modules will not be built.")
        set(MSDK_BUILD_TFT_MODULES FALSE)
    endif()
endif()

include(utils)
include(mikroeUtils)
include(GNUInstallDirs)

add_subdirectory(platform)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(api)
    add_subdirectory(bsp)
    add_subdirectory(components)
    add_subdirectory(drv)
    add_subdirectory(hal)
    add_subdirectory(middleware)
    add_subdirectory(targets)
    add_subdirectory(thirdparty)
endif()

if(${MSDK_TEST_EXAMPLES} MATCHES "true")
    add_subdirectory(tests)
endif()

## Deploy build is used for testing compiler specific issues.
if (NOT ${IS_BARE_METAL})
    if($ENV{IS_DOCKER_CONTAINER} MATCHES "true")
        add_subdirectory(deploy)
    endif()
endif()

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.meproject)
                fetch_linker_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject linkerName)
                add_ld_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${linkerName})
            endif()
        endif()
    endif()
endif()
