## ./tests/mikrobus/CMakeLists.txt

add_subdirectory(blink)

## 8K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(i2c)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"mikrobus/i2c\" test.")
endif()

## 8K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 8192 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(pwm)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"mikrobus/pwm\" test.")
endif()

## 32K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(adc)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"mikrobus/adc\" test.")
endif()

## 32K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(uart)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"mikrobus/uart\" test.")
endif()

## 32K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(spi)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"mikrobus/spi\" test.")
endif()
