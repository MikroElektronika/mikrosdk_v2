/* Host test only: net_driver_t on a Linux TAP device. */
#ifndef TAP_DRIVER_H
#define TAP_DRIVER_H

#include <stdbool.h>
#include <stdint.h>
#include "net_driver.h"

typedef struct
{
    int fd;
    bool link;              /* reported by link_up(); tests switch it to simulate a cable */
    uint32_t tx_frames;
    uint32_t rx_frames;
} tap_driver_t;

/* Attach to the existing TAP interface @p ifname and fill @p drv. 0 on success. */
int tap_driver_open( tap_driver_t *tap, net_driver_t *drv, const char *ifname );

#endif
