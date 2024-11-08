## ./tests/clicks/spi/CMakeLists.txt

## 32K Flash and 4K RAM minimum for click_bee test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_bee)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_bee\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_ccrf_2 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_ccrf_2)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_ccrf_2\" test.")
endif()

## 64K Flash and 8K RAM minimum for click_eink_290_inch test.
memory_sdk_test_check(memory_issue 65536 8192)

if (NOT ${_MSDK_MCU_CARD_NAME_} MATCHES "(.+PIC(24|33)E.+)")
    if (NOT ${_MSDK_BOARD_NAME_} MATCHES "(.+PIC(24|33)E.+)")
        if (${memory_issue} STREQUAL "FALSE")
            add_subdirectory(click_eink_290_inch)
        else()
            message(INFO ": ${MCU_NAME} does not have enough memory for \"click_eink_290_inch\" test.")
        endif()
    endif()
endif()

## 32K Flash and 4K RAM minimum for click_magneto test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_magneto)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_magneto\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_magneto test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_magneto_2)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_magneto_2\" test.")
endif()

## 64K Flash and 4K RAM minimum for click_oledc test.
memory_sdk_test_check(memory_issue 65536 3072)

if (NOT ${_MSDK_MCU_CARD_NAME_} MATCHES "(.+PIC(24|33)E.+)")
    if (NOT ${_MSDK_BOARD_NAME_} MATCHES "(.+PIC(24|33)E.+)")
        if (${memory_issue} STREQUAL "FALSE")
            add_subdirectory(click_oledc)
        else()
            message(INFO ": ${MCU_NAME} does not have enough memory for \"click_oledc\" test.")
        endif()
    endif()
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
