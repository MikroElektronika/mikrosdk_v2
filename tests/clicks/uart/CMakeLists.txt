## ./tests/clicks/uart/CMakeLists.txt

## 32K Flash and 4K RAM minimum for click_barcode test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_barcode)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_barcode\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_gps test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_gps)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_gps\" test.")
endif()

## 64K Flash and 4K RAM minimum for click_rfid test.
memory_sdk_test_check(memory_issue 65537 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_rfid)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_rfid\" test.")
endif()

## 64K Flash and 4K RAM minimum for click_gsm_gps test.
memory_sdk_test_check(memory_issue 65537 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_gsm_gps)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_gsm_gps\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_samltouch test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_samltouch)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_samltouch\" test.")
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
