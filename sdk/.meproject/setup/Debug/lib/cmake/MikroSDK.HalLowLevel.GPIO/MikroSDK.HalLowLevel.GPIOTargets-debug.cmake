#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.HalLowLevel.GPIO" for configuration "Debug"
set_property(TARGET MikroSDK.HalLowLevel.GPIO APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.HalLowLevel.GPIO PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_hal_ll_gpio.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.HalLowLevel.GPIO )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.HalLowLevel.GPIO "${_IMPORT_PREFIX}/lib/lib_hal_ll_gpio.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
