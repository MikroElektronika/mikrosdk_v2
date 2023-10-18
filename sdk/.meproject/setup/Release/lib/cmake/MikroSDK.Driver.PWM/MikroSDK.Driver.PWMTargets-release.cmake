#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.PWM" for configuration "Release"
set_property(TARGET MikroSDK.Driver.PWM APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Driver.PWM PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_drv_pwm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.PWM )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.PWM "${_IMPORT_PREFIX}/lib/lib_drv_pwm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
