## ./tests/can/CMakeLists.txt

## 12K Flash and 2K RAM minimum for this test.
memory_sdk_test_check(memory_issue 12288 2048)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(can_loopback)
    add_subdirectory(can_tx)
    add_subdirectory(can_rx)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()
