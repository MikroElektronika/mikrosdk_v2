if(${MCU_NAME} MATCHES "^STM32G491CC$|^STM32G491KC$|^STM32G491RC$|^STM32G491VC$|^STM32G491MC$|^STM32G491CE$|^STM32G491KE$|^STM32G491RE$|^STM32G491VE$|^STM32G491ME$")
    set(uart_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_uart.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_88")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_88")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G49xx")
    list(APPEND hal_ll_def_list "STM32G491xx")
    set(uart_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart/hal_ll_uart_pin_map/implementations/doc_ds_88")
endif()
