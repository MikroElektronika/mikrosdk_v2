if(${MCU_NAME} MATCHES "^STM32G431C6$|^STM32G431K6$|^STM32G431R6$|^STM32G431V6$|^STM32G431M6$|^STM32G431C8$|^STM32G431K8$|^STM32G431R8$|^STM32G431V8$|^STM32G431M8$|^STM32G431CB$|^STM32G431KB$|^STM32G431RB$|^STM32G431VB$|^STM32G431MB$")
    set(uart_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_uart.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_82")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_82")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G43xx")
    list(APPEND hal_ll_def_list "STM32G431xx")
    set(uart_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/uart/hal_ll_uart_pin_map/implementations/doc_ds_82")
endif()
