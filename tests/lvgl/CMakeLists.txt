## ./tests/lvgl/CMakeLists.txt

# TODO: this test is compatible with LVGL v8.3.5, but not with the version of LVGL v9.4.0 that's currently in mikroSDK, so it is disabled for now.
# ## 330K Flash and 70K RAM minimum for lvgl_button test.
# memory_sdk_test_check(memory_issue 337920 71680)

# if (${memory_issue} STREQUAL "FALSE")
#     add_subdirectory(lvgl_button)
# else()
#     message(INFO ": ${MCU_NAME} does not have enough memory for \"lvgl_button\" test.")
# endif()

## 430K Flash and 76K RAM minimum for lvgl_button_grid test.
memory_sdk_test_check(memory_issue 435864 76152)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(lvgl_button_grid)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for \"lvgl_button_grid\" test.")
endif()
