#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.GPIO.Port" for configuration "Release"
set_property(TARGET MikroSDK.Driver.GPIO.Port APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Driver.GPIO.Port PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_drv_port.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.GPIO.Port )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.GPIO.Port "${_IMPORT_PREFIX}/lib/lib_drv_port.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
