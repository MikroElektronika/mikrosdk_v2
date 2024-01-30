## ./api/usb/CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

## Initial mikroSDK 2.9.0 release shall only
## have TinyUSB for GNU C compilers.
## In this case all ARM and RISC-V MCUs.
## Support for other architectures is coming
## in a future release.
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    ## USB
    check_usb_components(has_usb has_usb_interrupts usb_module_list)
    if((${has_usb} STREQUAL "true") AND (${has_usb_interrupts} STREQUAL "true"))
        check_usb_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(tinyusb)
        endif()
    endif()
endif()
