if(${MCU_NAME} MATCHES "^STM32G483CE$|^STM32G483RE$|^STM32G483ME$|^STM32G483PE$|^STM32G483VE$|^STM32G483QE$")
    set(tim_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_tim.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_86")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_86")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G48xx")
    list(APPEND hal_ll_def_list "STM32G483xx")
    set(tim_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim/hal_ll_tim_pin_map/implementations/doc_ds_86")
endif()
