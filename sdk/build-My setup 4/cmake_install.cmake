# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/bsp/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/components/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/hal/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/middleware/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/platform/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/targets/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
