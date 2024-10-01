<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.9.0`

+ released: 2023-10-05

## Changes

+ [`v2.9.0`](#v290)
  + [Changes](#changes)
    + [New Features](#new-features)
    + [Improvements](#improvements)
    + [Fixes](#fixes)
    + [NEW HARDWARE](#new-hardware)

### New Features

+ Added support for USB by implementing an already tested and community driven project - [tinyUSB](https://github.com/hathach/tinyusb)
  + Lightweight and efficient, designed to be small in size and highly efficient in terms of memory and CPU usage
  + All GCC MCUs are supported
    + `STM32`
    + `NXP`
    + `TIVA`
    + `GD32`
  + Following classes added
    + `audio`
    + `bth`
    + `cdc`
    + `dfu`
    + `hid`
    + `midi`
    + `msc`
    + `net`
    + `usbtmc`
    + `vendor`
    + `video`
+ Added support for ETHERNET by implementing an open-source TCP/IP protocol stack library designed for embedded systems and IoT - [CycloneTCP](https://github.com/Oryx-Embedded/CycloneTCP/tree/master)
  + Lightweight and resource-efficient in terms of memory and CPU usage
  + All GCC MCUs are supported
    + `STM32`
    + `NXP`
    + `TIVA`
    + `GD32`
  + Following modules added
    + `coap`
    + `dhcp`
    + `dhcpv6`
    + `dns`
    + `dns_sd`
    + `echo`
    + `ftp`
    + `http`
    + `icecast`
    + `igmp`
    + `ipv4`
    + `ipv6`
    + `lldp`
    + `llmnr`
    + `mdns`
    + `mibs`
    + `modbus`
    + `mqtt`
    + `mqtt_sn`
    + `netbios`
    + `ppp`
    + `smtp`
    + `snmp`
    + `sntp`
    + `syslog`
    + `tftp`
    + `web_socket`
+ Interrupt control added for all architectures and MCUs
+ Added HW initialization sequences for MikroE hardware
  + Sequences added for `USB` and `ETHERNET`
  + Files added as inline interface libraries in `./middleware/hw`
    + **8** files in total for `ETHERNET`
    + **16** files in total for `USB`
+ Added following test examples
  + **USB**
    + `cdc_msc`
    + `hid_generic_inout`
    + `midi`
  + **ETHERNET**
    + `http_client`
    + `ftp_client`

### Improvements

+ SPI low level implementation updated for all architectures
  + Low level `write` and `read` APIs transfer counter changed from `uint16_t` to `size_t`
    + Results in bigger buffers available for single data transfer

### Fixes

+ Fixed pins for USB_UART defined in `dip_socket.h` for packages DIP20 and DIP28 for EasyPIC v8 board
  + `USB_UART_TX` changed from `PC4` to `PC6`
  + `USB_UART_RX` changed from `PC5` to `PC7`
+ Fixed inadequate structure access in following libraries
  + `tft7`
  + `ili9341`
  + `tp_mikroe`

### NEW HARDWARE

+ [SiBRAIN for ATmega2560](https://www.mikroe.com/sibrain-for-atmega2560)
+ [SiBRAIN for ATmega1280](https://www.mikroe.com/sibrain-for-atmega1280)
+ [Clicker 4 for STM32F4](https://www.mikroe.com/clicker-4-for-stm32f4)

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
