if(${MCU_NAME} MATCHES "^STM32G484CE$|^STM32G484ME$|^STM32G484PE$|^STM32G484RE$|^STM32G484QE$|^STM32G484VE$")
    set(dma_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_dma.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_87")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_87")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G48xx")
    list(APPEND hal_ll_def_list "STM32G484xx")
endif()
