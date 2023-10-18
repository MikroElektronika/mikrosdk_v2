#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.PhysicalDrive" for configuration "Debug"
set_property(TARGET MikroSDK.PhysicalDrive APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.PhysicalDrive PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/physical_drive.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.PhysicalDrive )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.PhysicalDrive "${_IMPORT_PREFIX}/lib/physical_drive.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
