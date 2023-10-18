## ./tests/clicks/i2c/CMakeLists.txt

## 32K Flash and 4K RAM minimum for click_6dof_imu_11 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_6dof_imu_11)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_6dof_imu_11\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_altitude_3 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_altitude_3)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_altitude_3\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_color_9 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_color_9)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_color_9\" test.")
endif()

## 32K Flash and 4K RAM minimum for click_light_ranger_2 test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_light_ranger_2)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_light_ranger_2\" test.")
endif()

## TODO - Set adequate Flash and RAM values here if adding custom examples.
memory_sdk_test_check(memory_issue 0 0)

if (${memory_issue} STREQUAL "FALSE")
    # TODO if any issues with custom examples
endif()
