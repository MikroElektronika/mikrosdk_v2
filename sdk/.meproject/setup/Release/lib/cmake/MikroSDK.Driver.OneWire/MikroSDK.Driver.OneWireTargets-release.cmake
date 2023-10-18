#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.OneWire" for configuration "Release"
set_property(TARGET MikroSDK.Driver.OneWire APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Driver.OneWire PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_drv_one_wire.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.OneWire )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.OneWire "${_IMPORT_PREFIX}/lib/lib_drv_one_wire.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
