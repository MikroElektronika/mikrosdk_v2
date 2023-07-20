## ./tests/clicks/adc/CMakeLists.txt

## 32K Flash and 8K RAM minimum for click_ambient_7 test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_ambient_7)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_ambient_7\" test.")
endif()

## 32K Flash and 8K RAM minimum for click_force test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_force)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_force\" test.")
endif()

## 32K Flash and 8K RAM minimum for click_hall_current_5 test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_hall_current_5)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_hall_current_5\" test.")
endif()

## 32K Flash and 8K RAM minimum for click_pressure_12 test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_pressure_12)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_pressure_12\" test.")
endif()

## 32K Flash and 8K RAM minimum for click_slider_2 test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_slider_2)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_slider_2\" test.")
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
