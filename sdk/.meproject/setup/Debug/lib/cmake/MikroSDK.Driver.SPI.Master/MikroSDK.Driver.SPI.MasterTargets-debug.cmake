#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Driver.SPI.Master" for configuration "Debug"
set_property(TARGET MikroSDK.Driver.SPI.Master APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.Driver.SPI.Master PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_drv_spi_master.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.Driver.SPI.Master )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.Driver.SPI.Master "${_IMPORT_PREFIX}/lib/lib_drv_spi_master.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
