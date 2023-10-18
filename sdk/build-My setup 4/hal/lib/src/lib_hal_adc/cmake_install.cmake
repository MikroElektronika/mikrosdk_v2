# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/hal/lib/src/lib_hal_adc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/NECTOStudio/NECTOStudio/compilers/RISCV/xpack-riscv-none-embed-gcc/bin/riscv-none-embed-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/lib_hal_adc.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets.cmake"
         "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/CMakeFiles/Export/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/CMakeFiles/Export/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/CMakeFiles/Export/lib/cmake/MikroSDK.Hal.ADC/MikroSDK.Hal.ADCTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.Hal.ADC" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/MikroSDK.Hal.ADCConfig.cmake"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/lib/src/lib_hal_adc/MikroSDK.Hal.ADCConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/hal/hal_adc.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/hal" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/hal/lib/src/lib_hal_adc/../../include/hal_adc.h")
endif()

