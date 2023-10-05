## ./tests/ethernet/CMakeLists.txt

## 32K Flash and 8K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_http_client)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()

## 32K Flash and 8K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_ftp_client)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()
