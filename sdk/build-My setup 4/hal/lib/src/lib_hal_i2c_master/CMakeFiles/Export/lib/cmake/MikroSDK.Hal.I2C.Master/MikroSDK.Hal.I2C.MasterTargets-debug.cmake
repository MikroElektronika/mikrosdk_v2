#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Hal.I2C.Master" for configuration "Debug"
set_property(TARGET MikroSDK.Hal.I2C.Master APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.Hal.I2C.Master PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_hal_i2c_master.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Hal.I2C.Master )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Hal.I2C.Master "${_IMPORT_PREFIX}/lib/lib_hal_i2c_master.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
