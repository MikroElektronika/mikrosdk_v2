
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was ExportConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(CMakeFindDependencyMacro)
find_dependency(MikroSDK.Driver.ADC)
find_dependency(MikroSDK.Driver.GPIO.In)
find_dependency(MikroSDK.Driver.GPIO.Out)
find_dependency(MikroSDK.Driver.GPIO.Port)
find_dependency(MikroSDK.Driver.I2C.Master)
find_dependency(MikroSDK.Driver.PWM)
find_dependency(MikroSDK.Driver.SPI.Master)
find_dependency(MikroSDK.Driver.UART)
find_dependency(MikroSDK.Driver.OneWire)

include("${CMAKE_CURRENT_LIST_DIR}/MikroSDK.DriverTargets.cmake")

check_required_components(MikroSDK.Driver)
