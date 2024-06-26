if(${MCU_NAME} MATCHES "^STM32G474CB$|^STM32G474MB$|^STM32G474RB$|^STM32G474VB$|^STM32G474QB$|^STM32G474PB$|^STM32G474CC$|^STM32G474MC$|^STM32G474RC$|^STM32G474VC$|^STM32G474QC$|^STM32G474PC$|^STM32G474CE$|^STM32G474ME$|^STM32G474RE$|^STM32G474VE$|^STM32G474QE$|^STM32G474PE$")
    set(adc_subimplementation "${CMAKE_CURRENT_LIST_DIR}/hal_ll_adc.c")
    set(rcc_subimplementation "${CMAKE_CURRENT_SOURCE_DIR}/../../include/rcc/implementations/doc_ds_85")
    set(gpio_subimplementation_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio/implementations/doc_ds_85")
    list(APPEND hal_ll_def_list "STM32G4xx")
    list(APPEND hal_ll_def_list "STM32G47xx")
    list(APPEND hal_ll_def_list "STM32G474xx")
    set(adc_pin_map "${CMAKE_CURRENT_SOURCE_DIR}/../../include/adc/hal_ll_adc_pin_map/implementations/doc_ds_85")
    list(APPEND hal_ll_def_list "HAL_LL_ADC_RESOLUTION_CMAKE=HAL_LL_ADC_RESOLUTION_12_BIT")
endif()
