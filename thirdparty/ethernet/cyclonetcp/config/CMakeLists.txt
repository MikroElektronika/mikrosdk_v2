## ./thirdparty/ethernet/cyclonetcp/config/CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

## Get current MCU specific source files.
ethernet_get_device_lib_files(source_list_device header_list_device)

## Get current MCU specific include directories
ethernet_get_device_lib_include_directories(include_directories_private "PRIVATE")
ethernet_get_device_lib_include_directories(include_directories_interface "INTERFACE")

## Set active driver header.
set_active_driver(${CMAKE_CURRENT_SOURCE_DIR} eth_driver.h)

mikrosdk_add_library(lib_cyclone_tcp_config MikroSDK.Ethernet.CycloneTCP.Config
    ./eth_driver.h
    ./net_config.h
    ./os_port_config.h
    ${source_list_device}
    ${header_list_device}
)

## Get additional PLDs if needed.
get_plds(additional_plds)

## Append MikroE MikroSDK macro if this project is built.
if(DEFINED CMAKE_PROJECT_NAME)
    if(${CMAKE_PROJECT_NAME} STREQUAL "MikroSDK")
        list(APPEND ethernet_module_list "__PROJECT_MIKROSDK_MIKROE__")
        ## Accept GPL license.
        list(APPEND ethernet_module_list "GPL_LICENSE_TERMS_ACCEPTED")
        ## NOTE - MikroE implementation doesn't use an OS.
        list(APPEND ethernet_module_list "NET_RTOS_SUPPORT=DISABLED")
        ## MikroE implementation uses printf_me for debug purposes.
        list(APPEND ethernet_module_list "TRACE_INFO=printf_me")
        list(APPEND ethernet_module_list "TRACE_ERROR=printf_me")
        list(APPEND ethernet_module_list "TRACE_DEBUG=printf_me")
    endif()
endif()

## Check if selected setup has adequate PHY chip.
## TODO - When database parsing is added, use this logic.
# if(NOT _MSDK_ETH_PHY_CHIP_)
#     ## If it doesn't, set it as NULL.
#     set(_MSDK_ETH_PHY_CHIP_ "NULL")
# endif()
## In the meantime, get PHY chip from CMake macro.
get_eth_phy_chip(_MSDK_ETH_PHY_CHIP_CMAKE_)

## Info about selected PHY chip.
message(INFO ":_MSDK_ETH_PHY_CHIP_CMAKE_ expands to \"${_MSDK_ETH_PHY_CHIP_CMAKE_}\".")

## Apply Ethernet module PLDs.
target_compile_definitions(lib_cyclone_tcp_config
    PUBLIC
        ${additional_plds}
        ${ethernet_module_list}
        ## _MSDK_ETH_PHY_CHIP_ provided by NECTO database if it exists.
        ## TODO - When database parsing is added, use this logic.
        # "ETHERNET_PHY_CHIP=${_MSDK_ETH_PHY_CHIP_}"
        "ETHERNET_PHY_CHIP=${_MSDK_ETH_PHY_CHIP_CMAKE_}"
)

## Link MikroE Core library.
target_link_libraries(lib_cyclone_tcp_config PUBLIC
    MikroC.Core
)

## Include search paths.
target_include_directories(lib_cyclone_tcp_config
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ## Generic root cmake file path included.
        ${include_directories_private}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ## Generic root cmake file path included.
        ${include_directories_interface}
        ## Install interface.
        $<INSTALL_INTERFACE:include/thirdparty/ethernet/cyclonetcp/lib>
        $<INSTALL_INTERFACE:include/thirdparty/ethernet/cyclonetcp/lib/config>
)

mikrosdk_install(MikroSDK.Ethernet.CycloneTCP.Config)

ethernet_get_header_list(header_list "MIKROE_CONFIG")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/config)

###################################################################################################
## Only for TIVA MCUs
###################################################################################################
ethernet_get_ti_headers(header_list "DRIVERLIB")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/driverlib)

ethernet_get_ti_headers(header_list "INC")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/inc)
###################################################################################################

ethernet_install_legacy_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/config/Legacy)

add_library(MikroSDK.Ethernet.CycloneTCP.Config ALIAS lib_cyclone_tcp_config)
