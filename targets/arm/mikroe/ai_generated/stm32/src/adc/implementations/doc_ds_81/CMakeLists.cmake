if(${MCU_NAME} MATCHES "^STM32G0C1CC$|^STM32G0C1KC$|^STM32G0C1MC$|^STM32G0C1RC$|^STM32G0C1VC$|^STM32G0C1CE$|^STM32G0C1KE$|^STM32G0C1ME$|^STM32G0C1NE$|^STM32G0C1RE$|^STM32G0C1VE$")
    set(adc_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_adc.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_81")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_81")
    list(APPEND hal_ll_def_list "STM32G0xx")
    list(APPEND hal_ll_def_list "STM32G0Cxx")
    list(APPEND hal_ll_def_list "STM32G0C1xx")
    set(adc_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc/hal_ll_adc_pin_map/implementations/doc_ds_81")
    list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")
endif()
