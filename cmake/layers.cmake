function(resolve_compiler_definitions drv_to_hal)
    ## Find the list of targets defined in the current directory.
    get_directory_property(TARGETS_LIST DIRECTORY ${CMAKE_CURRENT_LIST_DIR} BUILDSYSTEM_TARGETS)

    ## We assume that there's only one target in this directory.
    foreach(target IN LISTS TARGETS_LIST)
        ## Perform operations only if the target is a library.
        get_target_property(TYPE ${target} TYPE)
        if(TYPE STREQUAL "STATIC_LIBRARY" OR TYPE STREQUAL "SHARED_LIBRARY" OR TYPE STREQUAL "OBJECT_LIBRARY")
            message(STATUS "Resolving compiler definitions for target: ${target}")
            ## By default, set it to DRV->HAL->HAL_LL
            ## Backward compatibility.
            if(NOT ${drv_to_hal})
                message(INFO ":All layers included.")
                target_compile_definitions(${target} PUBLIC
                    "DRV_TO_HAL=1"
                )
            else()
                message(INFO ":HAL layer skipped.")
                target_compile_definitions(${target} PUBLIC
                    "DRV_TO_HAL=0"
                )
            endif()
        endif()
    endforeach()
endfunction()
