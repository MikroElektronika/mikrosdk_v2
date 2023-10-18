## ./tests/clicks/pwm/CMakeLists.txt

## 32K Flash and 4K RAM minimum for click_brushless test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_brushless)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_brushless\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_button_y test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_button_y)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_button_y\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_dc_motor_8 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_dc_motor_8)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_dc_motor_8\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_led_driver_6 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_led_driver_6)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_led_driver_6\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_stspin250 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_stspin250)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_stspin250\" test.")
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
