if(${MCU_NAME} MATCHES "^STM32L4Q5AG$|^STM32L4Q5CG$|^STM32L4Q5QG$|^STM32L4Q5RG$|^STM32L4Q5VG$|^STM32L4Q5ZG$")
    set(spi_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_spi_master.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_161")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_161")
    list(APPEND hal_ll_def_list "STM32L4xx")
    list(APPEND hal_ll_def_list "STM32L4Qxx")
    list(APPEND hal_ll_def_list "STM32L4Q5xx")
    set(spi_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/hal_ll_spi_master_pin_map/implementations/doc_ds_161")
endif()
