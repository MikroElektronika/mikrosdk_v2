## ./tests/file_system/CMakeLists.txt
memory_sdk_test_check(memory_issue 65537 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_fatfs_sdspi)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"file system\" test.")
endif()
