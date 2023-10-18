#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.USB.Tiny" for configuration "Debug"
set_property(TARGET MikroSDK.USB.Tiny APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.USB.Tiny PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_tinyusb.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.USB.Tiny )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.USB.Tiny "${_IMPORT_PREFIX}/lib/lib_tinyusb.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
