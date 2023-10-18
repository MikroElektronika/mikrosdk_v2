#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.FileSystem" for configuration "Release"
set_property(TARGET MikroSDK.FileSystem APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.FileSystem PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/file_system.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.FileSystem )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.FileSystem "${_IMPORT_PREFIX}/lib/file_system.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
