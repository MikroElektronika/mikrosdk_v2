## ./api/ethernet/cyclonetcp/CMakeLists.txt
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

## Link MikroE Core library.
target_link_libraries(lib_cyclone_tcp PUBLIC
    MikroC.Core
    MikroSDK.Ethernet.CycloneTCP.Config
    MikroSDK.Ethernet.HW
)

## Include search paths.
target_include_directories(lib_cyclone_tcp
    PRIVATE
        ## Generic root cmake file path included.
        ${CMAKE_CURRENT_SOURCE_DIR}
        ## Generic common file path included.
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ## Generic cyclone tcp root path included.
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp
        ## Source specific paths included.
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/coap
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/core
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dhcp
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dhcpv6
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dns
        ${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dns_sd
        ${CMAKE_CURRENT_SOURCE_DIR}/echo
        ${CMAKE_CURRENT_SOURCE_DIR}/ftp
        ${CMAKE_CURRENT_SOURCE_DIR}/http
        ${CMAKE_CURRENT_SOURCE_DIR}/icecast
        ${CMAKE_CURRENT_SOURCE_DIR}/igmp
        ${CMAKE_CURRENT_SOURCE_DIR}/ipv4
        ${CMAKE_CURRENT_SOURCE_DIR}/ipv6
        ${CMAKE_CURRENT_SOURCE_DIR}/lldp
        ${CMAKE_CURRENT_SOURCE_DIR}/llmnr
        ${CMAKE_CURRENT_SOURCE_DIR}/mdns
        ${CMAKE_CURRENT_SOURCE_DIR}/mibs
        ${CMAKE_CURRENT_SOURCE_DIR}/modbus
        ${CMAKE_CURRENT_SOURCE_DIR}/mqtt
        ${CMAKE_CURRENT_SOURCE_DIR}/mqtt_sn
        ${CMAKE_CURRENT_SOURCE_DIR}/netbios
        ${CMAKE_CURRENT_SOURCE_DIR}/ppp
        ${CMAKE_CURRENT_SOURCE_DIR}/smtp
        ${CMAKE_CURRENT_SOURCE_DIR}/snmp
        ${CMAKE_CURRENT_SOURCE_DIR}/sntp
        ${CMAKE_CURRENT_SOURCE_DIR}/syslog
        ${CMAKE_CURRENT_SOURCE_DIR}/tftp
        ${CMAKE_CURRENT_SOURCE_DIR}/web_socket
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/eth
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/loopback
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/mac
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/pcap
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/phy
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/switch
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/usb_rndis
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/wifi
    INTERFACE
        ## Generic root cmake file path included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ## Generic common file path included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common>
        ## Generic cyclone tcp root path included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp>
        ## Source specific paths included.
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/coap>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dhcp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dhcpv6>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dns>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cyclone_tcp/dns_sd>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/echo>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ftp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/http>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/icecast>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/igmp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ipv4>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ipv6>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lldp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/llmnr>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mdns>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mibs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/modbus>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mqtt>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mqtt_sn>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/netbios>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ppp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/smtp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/snmp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sntp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/syslog>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tftp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/web_socket>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/eth>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/loopback>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/mac>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/pcap>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/phy>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/switch>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/usb_rndis>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers/wifi>
        ## Install interface.
        $<INSTALL_INTERFACE:include/api/cyclonetcp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/common>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/coap>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/core>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/dhcp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/dhcpv6>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/dns>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/dns_sd>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/echo>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/ftp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/http>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/icecast>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/igmp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/ipv4>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/ipv6>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/lldp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/llmnr>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/mdns>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/modbus>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/mqtt>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/mqtt_sn>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/netbios>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/ppp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/sntp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/syslog>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/tftp>
        $<INSTALL_INTERFACE:include/api/cyclonetcp/web_socket>
        # $<INSTALL_INTERFACE:include/api/cyclonetcp/snmp>
        # $<INSTALL_INTERFACE:include/api/cyclonetcp/smtp>
        # $<INSTALL_INTERFACE:include/api/cyclonetcp/mibs>
)

ethernet_get_headers(list_out)
mikrosdk_install(MikroSDK.Ethernet.CycloneTCP)
install_headers(${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp MikroSDK.Ethernet.CycloneTCP "${list_out}")

ethernet_get_mac_headers(header_list)
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/drivers/mac)

ethernet_get_phy_headers(header_list)
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/drivers/phy)

ethernet_get_header_list(header_list "COMMON")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/common)

ethernet_get_header_list(header_list "CORE")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/core)

ethernet_get_header_list(header_list "IPV4")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/coap)

ethernet_get_header_list(header_list "DHCP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/dhcp)

ethernet_get_header_list(header_list "DHCPV6")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/dhcpv6)

ethernet_get_header_list(header_list "DNS")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/dns)

ethernet_get_header_list(header_list "DNS_SD")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/dns_sd)

ethernet_get_header_list(header_list "ECHO")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/echo)

ethernet_get_header_list(header_list "FTP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/ftp)

ethernet_get_header_list(header_list "HTTP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/http)

ethernet_get_header_list(header_list "ICECAST")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/icecast)

ethernet_get_header_list(header_list "IGMP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/igmp)

ethernet_get_header_list(header_list "IPV4")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/ipv4)

ethernet_get_header_list(header_list "IPV6")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/ipv6)

ethernet_get_header_list(header_list "LLDP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/lldp)

ethernet_get_header_list(header_list "LLMNR")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/llmnr)

ethernet_get_header_list(header_list "MDNS")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/mdns)

ethernet_get_header_list(header_list "MODBUS")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/modbus)

ethernet_get_header_list(header_list "MQTT")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/mqtt)

ethernet_get_header_list(header_list "MQTT_SN")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/mqtt_sn)

ethernet_get_header_list(header_list "NETBIOS")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/netbios)

ethernet_get_header_list(header_list "PPP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/ppp)

ethernet_get_header_list(header_list "SNTP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/sntp)

ethernet_get_header_list(header_list "SYSLOG")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/syslog)

ethernet_get_header_list(header_list "TFTP")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/tftp)

ethernet_get_header_list(header_list "WEB_SOCKET")
ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/web_socket)

# ethernet_get_header_list(header_list "MIBS")
# ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/mibs)

# ethernet_get_header_list(header_list "SMTP")
# ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/smtp)

# ethernet_get_header_list(header_list "SNMP")
# ethernet_install_headers("${header_list}" ${CMAKE_INSTALL_PREFIX}/include/api/cyclonetcp/snmp)

add_library(MikroSDK.Ethernet.CycloneTCP ALIAS lib_cyclone_tcp)
