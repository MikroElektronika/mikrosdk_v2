## ./api/usb/tinyusb/CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

## Generate source file and header first.
usb_generate_isr_source(${CMAKE_CURRENT_SOURCE_DIR}/isr/src usb_isr_routines.c)
usb_generate_isr_header(${CMAKE_CURRENT_SOURCE_DIR}/isr/include usb_isr_routines.h)

## Get USB module list for PLDs.
check_usb_components(has_usb has_usb_interrupts usb_module_list)

## Get current MCU host source files.
if("__HAS_HOST__" IN_LIST usb_module_list)
    usb_get_sources_host(source_list_host)
endif()

## Get current MCU device source files.
if("__HAS_DEVICE__" IN_LIST usb_module_list)
    usb_get_sources_device(source_list_device)
endif()

## Get current MCU source files.
usb_get_device_lib_files(source_list header_list)

## Generate adequate USB config file for selected MCU.
usb_get_mcu_opt(USB_TINY_OPT_MCU)
usb_generate_config(${CMAKE_CURRENT_SOURCE_DIR}/config tusb_config.h ${USB_TINY_OPT_MCU})

## Add tinyusb as a library.
mikrosdk_add_library(lib_tinyusb MikroSDK.USB.Tiny
    ## Common.
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/tusb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_fifo.c
    ## Typec.
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/typec/usbc.c
    ## Device.
    ${source_list_device}
    ## Host.
    ${source_list_host}
    ## Device specific implementations.
    ${source_list}
    ${header_list}
    ## MikroE default weak callback routines.
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/callbacks_default.c
    ## MikroE default interrupt service routines.
    ${CMAKE_CURRENT_SOURCE_DIR}/isr/src/usb_isr_routines.c
    ${CMAKE_CURRENT_SOURCE_DIR}/isr/include/usb_isr_routines.h
)

## Append MikroE MikroSDK macro if this project is built.
if(DEFINED CMAKE_PROJECT_NAME)
    if(${CMAKE_PROJECT_NAME} STREQUAL "MikroSDK")
        list(APPEND usb_module_list "__PROJECT_MIKROSDK_MIKROE__")
    endif()
endif()

## Apply USB module PLDs.
target_compile_definitions(lib_tinyusb
    PUBLIC
        ${usb_module_list}
)

## Link MikroE Core library.
target_link_libraries(lib_tinyusb PUBLIC
    MikroC.Core
    MikroSDK.USB.HW
)

## Generic configuration file path included.
add_compile_definitions(CFG_TUSB_CONFIG_FILE=${CMAKE_CURRENT_SOURCE_DIR}/config/)

## Include search paths.
target_include_directories(lib_tinyusb
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/host
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/device
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/networking
        ## Generic configuration file path included.
        ${CMAKE_CURRENT_SOURCE_DIR}/config
        ## MikroE default interrupt service routines path included.
        ${CMAKE_CURRENT_SOURCE_DIR}/isr/include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/host>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/device>
        ## Generic configuration file path included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config>
        ## ISR header file path included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/isr/include>
        $<INSTALL_INTERFACE:include/thirdparty/usb/tinyusb>
)

## First generate library with `MikroSDK.USB.Tiny` alias and generis `tusb.h` header file.
mikrosdk_install(MikroSDK.USB.Tiny)
install_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb MikroSDK.USB.Tiny isr/include/usb_isr_routines.h config/tusb_config.h lib/tusb.h)

## TODO - Add library definitions here as needed.
## TODO - If cases for inclusion - only include if user selects it.
## Then install additional header files required by library.
usb_get_header_list(header_list "COMMON")
usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/common)

usb_get_header_list(header_list "OSAL")
usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/osal)

if("__HAS_HOST__" IN_LIST usb_module_list)
    usb_get_header_list(header_list "HOST")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/host)
endif()

if("__HAS_DEVICE__" IN_LIST usb_module_list)
    usb_get_header_list(header_list "DEVICE")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/device)

    usb_get_header_list(header_list "CLASS_HID")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/hid)

    usb_get_header_list(header_list "CLASS_MIDI")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/midi)

    usb_get_header_list(header_list "CLASS_AUDIO")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/audio)

    usb_get_header_list(header_list "CLASS_BTH")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/bth)

    usb_get_header_list(header_list "CLASS_CDC")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/cdc)

    usb_get_header_list(header_list "CLASS_DFU")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/dfu)

    usb_get_header_list(header_list "CLASS_MSC")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/msc)

    usb_get_header_list(header_list "CLASS_NET")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/net)

    usb_get_header_list(header_list "CLASS_USBTMC")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/usbtmc)

    usb_get_header_list(header_list "CLASS_VENDOR")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/vendor)

    usb_get_header_list(header_list "CLASS_VIDEO")
    usb_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/usb/tinyusb/class/video)
endif()

## END ##
