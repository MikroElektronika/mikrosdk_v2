#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.GPIO.In" for configuration "Debug"
set_property(TARGET MikroSDK.Driver.GPIO.In APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.Driver.GPIO.In PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_drv_digital_in.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.GPIO.In )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.GPIO.In "${_IMPORT_PREFIX}/lib/lib_drv_digital_in.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
