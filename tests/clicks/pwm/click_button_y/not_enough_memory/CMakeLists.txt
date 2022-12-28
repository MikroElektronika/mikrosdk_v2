## ./tests/clicks/pwm/click_button_y/not_enough_memory/CMakeLists.txt
mikrosdk_add_library(test_click_buttonlibrary)

mikrosdk_install(${MCU_NAME}_Memory_Issue)
