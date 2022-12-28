## ./tests/clicks/spi/click_ccrf_2/not_enough_memory/CMakeLists.txt
mikrosdk_add_library(test_click_ccrf2 _Memory_Issue)

mikrosdk_install(${MCU_NAME}_Memory_Issue)
