# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/middleware/physical_drive

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/physical_drive.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets.cmake"
         "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/CMakeFiles/Export/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/CMakeFiles/Export/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/CMakeFiles/Export/lib/cmake/MikroSDK.PhysicalDrive/MikroSDK.PhysicalDriveTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.PhysicalDrive" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/MikroSDK.PhysicalDriveConfig.cmake"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/physical_drive/MikroSDK.PhysicalDriveConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/middleware/physical_drive/physical_drive.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/middleware/physical_drive/sdspi_physical_drive.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/middleware/physical_drive" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/middleware/physical_drive/include/physical_drive.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/middleware/physical_drive/sd/sdspi/include/sdspi_physical_drive.h"
    )
endif()

