## ./tests/clicks/gpio/CMakeLists.txt

## 32K Flash and 4K RAM minimum for click_cap_touch test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_cap_touch)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_cap_touch\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_opto_encoder_3 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_opto_encoder_3)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_opto_encoder_3\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_pll test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_pll)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_pll\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_vibra_sense test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_vibra_sense)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_vibra_sense\" test.")
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
