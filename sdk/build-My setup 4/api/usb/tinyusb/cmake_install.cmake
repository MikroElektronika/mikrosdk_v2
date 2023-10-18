# Install script for directory: D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/lib_tinyusb.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets.cmake"
         "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/CMakeFiles/Export/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/CMakeFiles/Export/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/CMakeFiles/Export/lib/cmake/MikroSDK.USB.Tiny/MikroSDK.USB.TinyTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MikroSDK.USB.Tiny" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/MikroSDK.USB.TinyConfig.cmake"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/build-My setup 4/api/usb/tinyusb/MikroSDK.USB.TinyConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/usb_isr_routines.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/tusb_config.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/tusb.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/isr/include/usb_isr_routines.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/config/tusb_config.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/tusb.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_option.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_common.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_mcu.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_fifo.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_compiler.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_verify.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_types.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_debug.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common/tusb_config.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/common" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/tusb_option.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_common.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_mcu.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_fifo.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_compiler.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_verify.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_types.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/common/tusb_debug.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/config/tusb_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/osal/osal.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/osal/osal_none.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/osal" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/osal/osal.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/osal/osal_none.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/device/dcd.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/device/usbd.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/device" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/device/dcd.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/device/usbd.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/hid/hid.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/hid/hid_host.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/hid/hid_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/hid" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/hid/hid.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/hid/hid_host.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/hid/hid_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/midi/midi.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/midi/midi_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/midi" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/midi/midi.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/midi/midi_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/audio/audio.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/audio/audio_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/audio" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/audio/audio.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/audio/audio_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/bth/bth_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/bth" TYPE FILE FILES "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/bth/bth_device.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc/cdc.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc/cdc_device.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc/cdc_host.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc/cdc_rndis.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc/cdc_rndis_host.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/cdc" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/cdc/cdc.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/cdc/cdc_device.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/cdc/cdc_host.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/cdc/cdc_rndis.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/cdc/cdc_rndis_host.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/dfu/dfu.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/dfu/dfu_device.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/dfu/dfu_rt_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/dfu" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/dfu/dfu.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/dfu/dfu_device.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/dfu/dfu_rt_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/msc/msc.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/msc/msc_device.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/msc/msc_host.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/msc" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/msc/msc.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/msc/msc_device.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/msc/msc_host.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/net/ncm.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/net/net_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/net" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/net/ncm.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/net/net_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/usbtmc/usbtmc.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/usbtmc/usbtmc_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/usbtmc" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/usbtmc/usbtmc.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/usbtmc/usbtmc_device.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/vendor/vendor_device.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/vendor/vendor_host.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/vendor" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/vendor/vendor_device.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/vendor/vendor_host.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/video/video.h;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/video/video_device.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/install/include/api/tinyusb/class/video" TYPE FILE FILES
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/video/video.h"
    "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/api/usb/tinyusb/lib/class/video/video_device.h"
    )
endif()

