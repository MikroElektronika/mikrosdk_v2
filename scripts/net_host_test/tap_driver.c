/*
 * Host test only: net_driver_t on a Linux TAP device, standing in for an
 * Ethernet controller. Not part of mikroSDK builds.
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>

#include "tap_driver.h"

static int32_t tap_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    tap_driver_t *tap = ( tap_driver_t * )ctx;
    tap->tx_frames++;
    return ( write( tap->fd, frame, len ) == ( ssize_t )len ) ? 0 : -1;
}

static int32_t tap_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    tap_driver_t *tap = ( tap_driver_t * )ctx;
    ssize_t n = read( tap->fd, buf, size );
    if ( n < 0 )
    {
        return ( EAGAIN == errno || EWOULDBLOCK == errno ) ? 0 : -1;
    }
    tap->rx_frames++;
    return ( int32_t )n;
}

static bool tap_link_up( void *ctx )
{
    return ( ( tap_driver_t * )ctx )->link;
}

int tap_driver_open( tap_driver_t *tap, net_driver_t *drv, const char *ifname )
{
    memset( tap, 0, sizeof( *tap ) );
    tap->fd = open( "/dev/net/tun", O_RDWR | O_NONBLOCK );
    if ( tap->fd < 0 )
    {
        return -1;
    }
    struct ifreq ifr;
    memset( &ifr, 0, sizeof( ifr ) );
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy( ifr.ifr_name, ifname, IFNAMSIZ - 1 );
    if ( ioctl( tap->fd, TUNSETIFF, &ifr ) < 0 )
    {
        close( tap->fd );
        return -1;
    }
    tap->link = true;
    drv->ctx = tap;
    drv->init = NULL;
    drv->send = tap_send;
    drv->receive = tap_receive;
    drv->link_up = tap_link_up;
    return 0;
}
