#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.HalLowLevel.RTC" for configuration "Debug"
set_property(TARGET MikroSDK.HalLowLevel.RTC APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MikroSDK.HalLowLevel.RTC PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lib_hal_ll_rtc.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MikroSDK.HalLowLevel.RTC )
list(APPEND _IMPORT_CHECK_FILES_FOR_MikroSDK.HalLowLevel.RTC "${_IMPORT_PREFIX}/lib/lib_hal_ll_rtc.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
