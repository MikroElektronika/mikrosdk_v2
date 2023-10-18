#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Log" for configuration "Debug"
set_property(TARGET MikroSDK.Log APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.Log PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_log.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Log )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Log "${_IMPORT_PREFIX}/lib/lib_log.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
