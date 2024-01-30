#############################################################################
## Function to create interface headers according to lib alias
#############################################################################
macro(dspic_core_generate_macros fileDestination fileList)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set (extra_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_args extra_count)
    if (${extra_count} GREATER 0)
        # Create a list of directives
        set(MACRO_LIST "")
        foreach(ARGUMENT ${extra_args})
            string(APPEND MACRO_LIST "#define ${ARGUMENT}\n")
        endforeach()

        # Generate output file with adequate name and include directive
        configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallHeadersCore.cmake.in ${fileDestination}/${fileList})
    endif ()
endmacro()

#############################################################################
## Function used to set adequate macro values per selected MCU
#############################################################################
function(dspic_core_set_macros core_parameters)
    set(local_list_macros ${core_parameters})

    if(${MCU_NAME} MATCHES "^dsPIC30F.+$")
        ## UART1
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_BIT_TX (10)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_BIT_RX (9)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS0_REG_ADDRESS)")
        ## UART2
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_BIT_TX (9)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_BIT_RX (8)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS1_REG_ADDRESS)")
    elseif(${MCU_NAME} MATCHES "^(dsPIC33|PIC24).+$")
        ## UART1
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_BIT_TX (12)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_BIT_RX (11)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS0_REG_ADDRESS)")
        list(APPEND local_list_macros "UART1_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS0_REG_ADDRESS)")
        ## UART2
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_BIT_TX (15)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_BIT_RX (14)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS1_REG_ADDRESS)")
        list(APPEND local_list_macros "UART2_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS1_REG_ADDRESS)")
        ## UART3
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_BIT_TX (3)")
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_BIT_RX (2)")
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART3_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS5_REG_ADDRESS)")
        ## UART4
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_BIT_TX (9)")
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_BIT_RX (8)")
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS5_REG_ADDRESS)")
        list(APPEND local_list_macros "UART4_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS5_REG_ADDRESS)")
        ## UART5
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_BIT_TX (0)")
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_BIT_RX (15)")
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC7_REG_ADDRESS)")
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC6_REG_ADDRESS)")
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS7_REG_ADDRESS)")
        list(APPEND local_list_macros "UART5_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS6_REG_ADDRESS)")
        ## UART6
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_BIT_TX (3)")
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_BIT_RX (2)")
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC7_REG_ADDRESS)")
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC7_REG_ADDRESS)")
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS7_REG_ADDRESS)")
        list(APPEND local_list_macros "UART6_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS7_REG_ADDRESS)")
    else()
        message(FATAL_ERROR "Core variables not set for ${MCU_NAME}. Set them in ${CMAKE_CURRENT_FUNCTION} function in ${CMAKE_CURRENT_FUNCTION_LIST_FILE}.")
    endif()

    set(${list} ${local_list_macros} PARENT_SCOPE)
endfunction()
