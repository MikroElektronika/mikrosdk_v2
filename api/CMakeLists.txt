## ./api/CMakeLists.txt
if(${MSDK_BUILD_TFT_MODULES})
    add_subdirectory(gl)
    add_subdirectory(tp)
    add_subdirectory(vtft)
endif()

add_subdirectory(log)

## Initial mikroSDK 2.9.0 release shall only
## have TinyUSB and CycloneTCP for GNU C compilers.
## In this case all ARM and RISC-V MCUs.
## Support for other architectures is coming
## in a future release.
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    ## USB
    check_usb_components(has_usb has_usb_interrupts usb_module_list)
    if((${has_usb} STREQUAL "true") AND (${has_usb_interrupts} STREQUAL "true"))
        check_usb_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(usb)
        endif()
    endif()
    ## ETH
    check_eth_components(has_eth eth_module_list)
    if(${has_eth} STREQUAL "true")
        check_eth_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(ethernet)
        endif()
    endif()
endif()
