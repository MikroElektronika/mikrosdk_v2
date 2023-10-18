## ./tests/usb/CMakeLists.txt

## 32K Flash and 4K RAM minimum for this test.
memory_sdk_test_check(memory_issue 32768 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_hid_generic_inout)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()

## 80K Flash and 8K RAM minimum for this test.
memory_sdk_test_check(memory_issue 81920 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_midi)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()

## 80K Flash and 8K RAM minimum for this test.
memory_sdk_test_check(memory_issue 81920 8192)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_cdc_msc)
else()
    get_filename_component(test_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    message(INFO ": ${MCU_NAME} does not have enough memory for \"${test_name}\" test.")
endif()
