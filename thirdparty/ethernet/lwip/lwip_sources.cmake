## ./thirdparty/ethernet/lwip/lwip_sources.cmake
## lwIP sources and include paths used by the mikroSDK network layer (middleware/net).
## lwIP is compiled into MikroSDK.Net itself, so its headers stay private to that library
## (lwIP and mikroSDK both define a type called err_t).
##
## Sets:
##   LWIP_SOURCES       lwIP .c files (IPv4/IPv6 core, Ethernet/ARP, mDNS responder)
##   LWIP_INCLUDE_DIRS  lwIP headers and the mikroSDK port (lwipopts.h, arch/cc.h)

set(LWIP_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(LWIP_SOURCES
    ${LWIP_ROOT}/src/core/def.c
    ${LWIP_ROOT}/src/core/dns.c
    ${LWIP_ROOT}/src/core/inet_chksum.c
    ${LWIP_ROOT}/src/core/init.c
    ${LWIP_ROOT}/src/core/ip.c
    ${LWIP_ROOT}/src/core/mem.c
    ${LWIP_ROOT}/src/core/memp.c
    ${LWIP_ROOT}/src/core/netif.c
    ${LWIP_ROOT}/src/core/pbuf.c
    ${LWIP_ROOT}/src/core/raw.c
    ${LWIP_ROOT}/src/core/stats.c
    ${LWIP_ROOT}/src/core/sys.c
    ${LWIP_ROOT}/src/core/tcp.c
    ${LWIP_ROOT}/src/core/tcp_in.c
    ${LWIP_ROOT}/src/core/tcp_out.c
    ${LWIP_ROOT}/src/core/timeouts.c
    ${LWIP_ROOT}/src/core/udp.c
    ${LWIP_ROOT}/src/core/ipv4/acd.c
    ${LWIP_ROOT}/src/core/ipv4/autoip.c
    ${LWIP_ROOT}/src/core/ipv4/dhcp.c
    ${LWIP_ROOT}/src/core/ipv4/etharp.c
    ${LWIP_ROOT}/src/core/ipv4/icmp.c
    ${LWIP_ROOT}/src/core/ipv4/igmp.c
    ${LWIP_ROOT}/src/core/ipv4/ip4.c
    ${LWIP_ROOT}/src/core/ipv4/ip4_addr.c
    ${LWIP_ROOT}/src/core/ipv4/ip4_frag.c
    ${LWIP_ROOT}/src/core/ipv6/dhcp6.c
    ${LWIP_ROOT}/src/core/ipv6/ethip6.c
    ${LWIP_ROOT}/src/core/ipv6/icmp6.c
    ${LWIP_ROOT}/src/core/ipv6/inet6.c
    ${LWIP_ROOT}/src/core/ipv6/ip6.c
    ${LWIP_ROOT}/src/core/ipv6/ip6_addr.c
    ${LWIP_ROOT}/src/core/ipv6/ip6_frag.c
    ${LWIP_ROOT}/src/core/ipv6/mld6.c
    ${LWIP_ROOT}/src/core/ipv6/nd6.c
    ${LWIP_ROOT}/src/netif/ethernet.c
    ${LWIP_ROOT}/src/apps/mdns/mdns.c
    ${LWIP_ROOT}/src/apps/mdns/mdns_domain.c
    ${LWIP_ROOT}/src/apps/mdns/mdns_out.c
)

set(LWIP_INCLUDE_DIRS
    ${LWIP_ROOT}/port
    ${LWIP_ROOT}/src/include
)
