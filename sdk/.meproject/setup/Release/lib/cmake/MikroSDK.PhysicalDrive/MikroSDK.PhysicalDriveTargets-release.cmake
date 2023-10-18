#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.PhysicalDrive" for configuration "Release"
set_property(TARGET MikroSDK.PhysicalDrive APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.PhysicalDrive PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/physical_drive.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.PhysicalDrive )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.PhysicalDrive "${_IMPORT_PREFIX}/lib/physical_drive.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
