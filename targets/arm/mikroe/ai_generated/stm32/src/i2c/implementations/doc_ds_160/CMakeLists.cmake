if(${MCU_NAME} MATCHES "^STM32L4P5AE$|^STM32L4P5AG$|^STM32L4P5CE$|^STM32L4P5CG$|^STM32L4P5QE$|^STM32L4P5QG$|^STM32L4P5RE$|^STM32L4P5RG$|^STM32L4P5VE$|^STM32L4P5VG$|^STM32L4P5ZE$|^STM32L4P5ZG$")
    set(i2c_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_i2c_master.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_160")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_160")
    list(APPEND hal_ll_def_list "STM32L4xx")
    list(APPEND hal_ll_def_list "STM32L4Pxx")
    list(APPEND hal_ll_def_list "STM32L4P5xx")
    set(i2c_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/i2c/hal_ll_i2c_pin_map/implementations/doc_ds_160")
endif()
