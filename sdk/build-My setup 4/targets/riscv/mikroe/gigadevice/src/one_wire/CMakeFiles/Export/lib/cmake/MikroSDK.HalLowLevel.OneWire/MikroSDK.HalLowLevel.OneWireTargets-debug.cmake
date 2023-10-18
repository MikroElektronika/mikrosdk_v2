#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.HalLowLevel.OneWire" for configuration "Debug"
set_property(TARGET MikroSDK.HalLowLevel.OneWire APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.HalLowLevel.OneWire PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_hal_ll_one_wire.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.HalLowLevel.OneWire )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.HalLowLevel.OneWire "${_IMPORT_PREFIX}/lib/lib_hal_ll_one_wire.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
