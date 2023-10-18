#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.I2C.Master" for configuration "Release"
set_property(TARGET MikroSDK.Driver.I2C.Master APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Driver.I2C.Master PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_drv_i2c_master.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.I2C.Master )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.I2C.Master "${_IMPORT_PREFIX}/lib/lib_drv_i2c_master.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
