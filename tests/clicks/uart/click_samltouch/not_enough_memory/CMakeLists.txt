## ./tests/clicks/uart/click_samltouch/not_enough_memory/CMakeLists.txt
mikrosdk_add_library(test_click_samltouch)

mikrosdk_install(${MCU_NAME}_Memory_Issue)
