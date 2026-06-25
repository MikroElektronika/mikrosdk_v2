## ./tests/lvgl/CMakeLists.txt

## 330K Flash and 70K RAM minimum for lvgl_button test.
memory_sdk_test_check(memory_issue 337920 71680)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(lvgl_button)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"lvgl_button\" test.")
endif()
