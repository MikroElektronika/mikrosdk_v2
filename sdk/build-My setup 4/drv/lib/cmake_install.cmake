# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/drv/lib

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
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_analog_in/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_digital_in/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_digital_out/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_i2c_master/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_port/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_pwm/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_spi_master/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_uart/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_one_wire/cmake_install.cmake")
  include("D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/drv/lib/src/lib_drv_rtc/cmake_install.cmake")

endif()

