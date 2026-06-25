# For dual-core MCUs CORE_NAME macro is not defined in the database
if(DEFINED CORE_NAME)
    add_subdirectory(single_core)
else()
    add_subdirectory(multi_core)
endif()