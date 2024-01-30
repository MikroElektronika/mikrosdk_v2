#############################################################################
## Macro to generate LCD interface header file.
#############################################################################
macro(lcd_generate_drivers fileDestination fileList)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set (extra_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_args extra_count)
    if (${extra_count} GREATER 0)
        # Create a list of directives
        set(INCLUDE_LIST "")

        foreach(ARGUMENT ${extra_args})
            string(APPEND INCLUDE_LIST "${ARGUMENT}\n")
        endforeach()

        # Generate output file with adequate name and include directive
        configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallDriversLcdController.cmake.in ${fileDestination}/${fileList})
    endif ()
endmacro()

#############################################################################
## Function used to get adequate LCD library source/header relative paths.
#############################################################################
function(lcd_generate_driver_list list_out_src list_out_hdr)
    set(list_local_src "")
    set(list_local_hdr "")

    ## Append all controller source/header relative paths.
    list(APPEND list_local_src "src/drivers/controller/hd44780_lcd_controller.c")
    list(APPEND list_local_hdr "include/drivers/controller/hd44780_lcd_controller.h")

    set(${list_out_src} ${list_local_src} PARENT_SCOPE)
    set(${list_out_hdr} ${list_local_hdr} PARENT_SCOPE)
endfunction()

#############################################################################
## Function used to get adequate LCD Controller library source files.
#############################################################################
function(lcd_get_controller_install_list list_out_hdr)
    set(list_local_hdr "")

    ## Append all controller headers.
    list(APPEND list_local_hdr "// Include Hitachi HD44780 LCD controller driver.")
    list(APPEND list_local_hdr "#include \"hd44780_lcd_controller.h\"")

    set(${list_out_hdr} ${list_local_hdr} PARENT_SCOPE)
endfunction()

#############################################################################
## Macro used to install adequate LCD library headers.
#############################################################################
macro(lcd_install_headers list_in destination)
    install(
        FILES
            ${list_in}
        DESTINATION
            ${destination}
    )
endmacro()
