# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/targets/riscv/mikroe/core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/lib_hal_ll_core.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets.cmake"
         "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/CMakeFiles/Export/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/CMakeFiles/Export/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/CMakeFiles/Export/lib/cmake/MikroSDK.HalLowLevelCore/MikroSDK.HalLowLevelCoreTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.HalLowLevelCore" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/MikroSDK.HalLowLevelCoreConfig.cmake"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/riscv/mikroe/core/MikroSDK.HalLowLevelCoreConfigVersion.cmake"
    )
endif()

