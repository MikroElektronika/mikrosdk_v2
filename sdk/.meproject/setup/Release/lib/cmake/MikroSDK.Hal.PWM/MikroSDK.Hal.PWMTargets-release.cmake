#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Hal.PWM" for configuration "Release"
set_property(TARGET MikroSDK.Hal.PWM APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Hal.PWM PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_hal_pwm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Hal.PWM )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Hal.PWM "${_IMPORT_PREFIX}/lib/lib_hal_pwm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
