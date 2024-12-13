## ./tests/uart/CMakeLists.txt

## 32K Flash and 3K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 3072)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_example)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()
