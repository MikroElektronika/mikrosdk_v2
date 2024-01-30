## ./thirdparty/ethernet/cyclonetcp/lib/CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

## Get main source files.
eth_get_main_files(source_list_main header_list_main)

## Get selected MAC PHY source files.
eth_get_files(eth_phy "PHY")

mikrosdk_add_library(lib_cyclone_tcp MikroSDK.Ethernet.CycloneTCP
    ${source_list_main}
    ${header_list_main}
    ${eth_phy}
)

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

## Apply Ethernet module PLDs.
target_compile_definitions(lib_cyclone_tcp
    PUBLIC
        ${ethernet_module_list}
)

## Link needed libraries.
target_link_libraries(lib_cyclone_tcp PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.CycloneTCP.Config
    MikroSDK.Ethernet.HW
)

## Set initial lists for include paths.
set(SUBDIRS_PRIVATE "")
set(BUILD_INTERFACE_DIRS "")
set(INSTALL_INTERFACE_DIRS "")

## Three depths of directories to search for.
## Add them to the private SP list.
SUBDIRLIST(SUBDIRS_PRIVATE ${CMAKE_CURRENT_LIST_DIR} "/*")
SUBDIRLIST(SUBDIRS_PRIVATE ${CMAKE_CURRENT_LIST_DIR} "/**/**")
SUBDIRLIST(SUBDIRS_PRIVATE ${CMAKE_CURRENT_LIST_DIR} "/**/**/**")

## Then add to build and install interface SP lists.
FOREACH(dirCurrent ${SUBDIRS_PRIVATE})
    LIST(APPEND BUILD_INTERFACE_DIRS "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dirCurrent}>")
    if(${dirCurrent} MATCHES "drivers")
        if(${dirCurrent} MATCHES "mac|phy")
            LIST(APPEND INSTALL_INTERFACE_DIRS "$<INSTALL_INTERFACE:include/thirdparty/ethernet/cyclonetcp/lib/${dirCurrent}>")
        endif()
    else()
        LIST(APPEND INSTALL_INTERFACE_DIRS "$<INSTALL_INTERFACE:include/thirdparty/ethernet/cyclonetcp/lib/${dirCurrent}>")
    endif()
ENDFOREACH()

## Include search paths.
target_include_directories(lib_cyclone_tcp
    PRIVATE
        ## Private search path list.
        ${SUBDIRS_PRIVATE}
    INTERFACE
        ## Install interface.
        ${BUILD_INTERFACE_DIRS}
        ## Install interface.
        ${INSTALL_INTERFACE_DIRS}
        $<INSTALL_INTERFACE:include/thirdparty/ethernet/cyclonetcp>
)

install(
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp"
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "drivers" EXCLUDE ## Exclude all drivers here as we install only the ones we actually need.
)

## Install all PHY drivers.
install(
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/cyclone_tcp/drivers/phy"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/cyclone_tcp/drivers"
    FILES_MATCHING
        PATTERN "*.h"
)

## Install all MAC drivers.
install(
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/cyclone_tcp/drivers/mac"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp/lib/cyclone_tcp/drivers"
    FILES_MATCHING
        PATTERN "*.h"
)

## Get relative paths to all headers for installing.
ethernet_get_headers(CYCLONE_TCP_HEADERS_PUBLIC)

## Install the headers.
mikrosdk_install(MikroSDK.Ethernet.CycloneTCP)
install_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/ethernet/cyclonetcp MikroSDK.Ethernet.CycloneTCP "${CYCLONE_TCP_HEADERS_PUBLIC}")

## Add the final library.
add_library(MikroSDK.Ethernet.CycloneTCP ALIAS lib_cyclone_tcp)
