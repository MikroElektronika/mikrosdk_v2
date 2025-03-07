##########################################################################################
## Function to check if the selected MCU requires errata functions due to known issues.
##########################################################################################
function(errata_check mcu_name errata_def_list)
    set(include_errata_functions ${errata_def_list})

    if(${mcu_name} MATCHES "^PIC32.+EC.+$")
        list(APPEND include_errata_functions PIC32MZxEC_ERRATA)
    endif()

    set(${errata_check} ${include_errata_functions} PARENT_SCOPE)
endfunction()
