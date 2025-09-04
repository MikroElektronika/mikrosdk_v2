## ./tests/CMakeLists.txt
set(tftTests TRUE)
if (${_MSDK_BOARD_NAME_} MATCHES "(^CLICKER(.+)$|^(.+)CLICKER$|^(.+)CURIOSITY(.+)$|^FLIP_AND_CLICK_PIC32MZ$|^GENERIC_BOARD$|^BOARD_PICPLC16_V7$|^(.+)_V7_(.+)$|^(.+)V7$|^BOARD_FLOWPAW$|^BOARD_QUAIL$|^BOARD_MICROMOD(.+))")
    set(tftTests FALSE)
elseif (${MSDK_BUILD_TFT_MODULES} STREQUAL "FALSE")
    set(tftTests FALSE)
endif()

set(clickTests TRUE)
if (${_MSDK_BOARD_NAME_} MATCHES "(^GENERIC_BOARD$)")
    set(clickTests FALSE)
endif()

set(tftJigTest TRUE)
if (${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIA(.+)$")
    set(tftJigTest FALSE)
endif()

add_subdirectory(gpio)
add_subdirectory(button_simulation)

## 8K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 2048)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(adc)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"adc\" test.")
endif()

## 8K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 2048)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(i2c)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"i2c\" test.")
endif()

## 8K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(pwm)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"pwm\" test.")
endif()

## 8K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 2048)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(spi)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"spi\" test.")
endif()

## 8K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(uart)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"uart\" test.")
endif()

if (NOT _MSDK_DIP_SOCKET_TYPE_)
    if (_HAS_MIKROBUS_)
        if (${_HAS_MIKROBUS_} STREQUAL TRUE)
            add_subdirectory(mikrobus)
        endif()
    endif()
endif()

if (${_MSDK_BOARD_NAME_} MATCHES "CLICKER")
    add_subdirectory(clicker_buttons)
endif()

## Initial mikroSDK 2.9.0 release shall only
## have TinyUSB and CycloneTCP for GNU C compilers.
## In this case all ARM and RISC-V MCUs.
## Support for other architectures is coming
## in a future release.
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    ## USB
    check_usb_components(has_usb has_usb_interrupts usb_module_list)
    if((${has_usb} STREQUAL "true") AND (${has_usb_interrupts} STREQUAL "true"))
        check_usb_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(usb)
        endif()
    endif()
endif()

## ETH
if(${TOOLCHAIN_ID} STREQUAL "gcc_arm_none_eabi" OR ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    check_eth_components(has_eth eth_module_list)
    if(${has_eth} STREQUAL "true")
        check_eth_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(ethernet)
        endif()
    endif()
endif()

## 12K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 12288 2048)

find_package(MikroSDK.Driver.CAN)
if(MikroSDK.Driver.CAN\_FOUND)
    if (${memory_issue} STREQUAL "FALSE")
        add_subdirectory(can)
    else()
        message(INFO ": ${MCU_NAME} does not have enough memory for \"can\" test.")
    endif()
endif()

add_subdirectory(one_wire)

add_subdirectory(lcd)

if (_MSDK_TFT_BOARD_)
    ## MikroE GL
    find_package(MikroSDK.GraphicLibrary)
    if (MikroSDK.GraphicLibrary\_FOUND)
        find_package(Components.TftBoard8)
        if (Components.TftBoard8\_FOUND)
            add_subdirectory(gl)
        endif()
    endif()
    ## LVGL
    if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
        add_subdirectory(lvgl)
    endif()
endif()

if (clickTests)
    add_subdirectory(clicks)
endif()

if (tftTests)
    if(tftJigTest)
        add_subdirectory(tft_jig)
    endif()
endif()

## 12K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 12288 2048)

find_package(MikroSDK.Driver.DMA)
if(MikroSDK.Driver.DMA\_FOUND)
    if (${memory_issue} STREQUAL "FALSE")
        add_subdirectory(dma)
    else()
        message(INFO ": ${MCU_NAME} does not have enough memory for \"dma\" test.")
    endif()
endif()

check_rtc(has_rtc)
if(${has_rtc} STREQUAL "true")
    add_subdirectory(rtc)
endif()

memory_test_check(enough_memory)
if(${enough_memory} STREQUAL "true")
    add_subdirectory(file_system)
endif()

add_subdirectory(sprint)
