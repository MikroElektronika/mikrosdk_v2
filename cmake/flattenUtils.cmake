#############################################################################
## Macro to generate flatten level header file according to selected options.
#############################################################################
macro(flatten_code_level_selection fileDestination fileList)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set (extra_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_args extra_count)
    if(${extra_count} GREATER 0)
        # Create a list of directives.
        set(MACRO_LIST1 "")
        set(MACRO_LIST2 "")

        list(GET extra_args 0 FLATTEN_ME)
        list(GET extra_args 1 FLATTEN_LEVEL)

        if(${FLATTEN_ME} STREQUAL "false")
            string(APPEND MACRO_LIST1 "#undef FLATTEN_ME\n")
        else()
            string(APPEND MACRO_LIST1 "#define FLATTEN_ME\n\n")
            string(APPEND MACRO_LIST2 "// Flatten level selection.\n")
            string(APPEND MACRO_LIST2 "#define FLATTEN_ME_LEVEL ${FLATTEN_LEVEL}\n")
        endif()

        # Generate output file with adequate name and include directive.
        configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallHeadersFlatten.cmake.in ${fileDestination}/${fileList})
    endif()
endmacro()
