## ./thirdparty/ethernet/CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

## Initial mikroSDK 2.9.0 release shall only
## have CycloneTCP for GNU C compilers.
## In this case all ARM and RISC-V MCUs.
## Support for other architectures is coming
## in a future release.
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    ## ETH
    check_eth_components(has_eth eth_module_list)
    if(${has_eth} STREQUAL "true")
        check_eth_requirements(memory_requirements_passed)
        if(${memory_requirements_passed} STREQUAL "true")
            add_subdirectory(cyclonetcp)
        endif()
    endif()
endif()
