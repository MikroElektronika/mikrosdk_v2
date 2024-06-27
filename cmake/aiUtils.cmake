#############################################################################
## Macro to get a list of files in the provided folder and all subfolders
#############################################################################
macro(get_files_recurse search_path file_list extension)
    file(GLOB_RECURSE ${file_list} ${search_path}/*.${extension})
endmacro()

#############################################################################
## Macro to get all subsequent directories for AI generated file and check
## if current module is supported or not.
#############################################################################
macro(check_if_module_is_generated isGenerated fileList)
    ## Set variable as FALSE initially
    set(${isGenerated} false)

    ## Go through all found cmake files
    foreach(CMAKE_FILE ${fileList})
        ## Read the file content
        file(READ ${CMAKE_FILE} CURRENT_CMAKE_FILE_CONTENT)
        ## Search for current MCU in the file
        string(REGEX MATCH ${MCU_NAME} CHECK_IF_SUPPORTED ${CURRENT_CMAKE_FILE_CONTENT})
        ## If the MCU is present in the file
        if(CHECK_IF_SUPPORTED)
            if(${CHECK_IF_SUPPORTED} STREQUAL ${MCU_NAME})
                ## Set the variable to TRUE and exit the loop
                set(${isGenerated} true)
                break()
            endif()
        endif()
    endforeach()

    ## Emit a message if no files were found/generated
    if(NOT ${isGenerated})
        message(STATUS ": NO CMAKE FILES FOUND FOR ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
endmacro()

#############################################################################
## Macro to get all subsequent directories for AI generated file and check
## if current module is supported or not.
#############################################################################
macro(add_module_if_generated searchPath listOut appendIt)
    set(IS_MODULE_GENERATED false)
    get_files_recurse(${searchPath} CMAKE_FILE_LIST cmake)
    if(CMAKE_FILE_LIST)
        check_if_module_is_generated(IS_MODULE_GENERATED "${CMAKE_FILE_LIST}")
    endif()
    if(IS_MODULE_GENERATED)
        list(APPEND ${listOut} ${appendIt})
    else()
        ## Emit a message if no files were found/generated
        message(STATUS ": NO CMAKE FILES FOUND FOR ${CMAKE_CURRENT_SOURCE_DIR}/${appendIt}")
    endif()
endmacro()
