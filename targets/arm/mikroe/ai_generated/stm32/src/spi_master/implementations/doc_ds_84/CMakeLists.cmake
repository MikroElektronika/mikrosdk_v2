if(${MCU_NAME} MATCHES "^STM32G473CB$|^STM32G473MB$|^STM32G473PB$|^STM32G473RB$|^STM32G473VB$|^STM32G473QB$|^STM32G473CC$|^STM32G473MC$|^STM32G473PC$|^STM32G473RC$|^STM32G473VC$|^STM32G473QC$|^STM32G473CE$|^STM32G473ME$|^STM32G473PE$|^STM32G473RE$|^STM32G473VE$|^STM32G473QE$")
    set(spi_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_spi_master.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_84")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_84")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G47xx")
    list(APPEND hal_ll_def_list "STM32G473xx")
    set(spi_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/spi_master/hal_ll_spi_master_pin_map/implementations/doc_ds_84")
endif()
