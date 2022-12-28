## ./tests/clicks/uart/click_barcode/not_enough_memory/CMakeLists.txt
mikrosdk_add_library(test_click_barcode)

mikrosdk_install(${MCU_NAME}_Memory_Issue)
