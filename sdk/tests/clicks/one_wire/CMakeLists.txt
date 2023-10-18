## ./tests/clicks/one_wire/CMakeLists.txt

## 8K Flash and 2K RAM minimum for click_thermo_2 test.
memory_sdk_test_check(memory_issue 8192 2048)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(click_thermo_2)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"click_thermo_2\" test.")
endif()
