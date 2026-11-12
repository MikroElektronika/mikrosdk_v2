<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.20.3`

+ released: 2026-11-17

## Changes

- [`v2.20.3`](#v2203)
  - [Changes](#changes)
    - [TOSHIBA](#toshiba)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>TOSHIBA</font>

**TMPM4L MCUs supported!**

| **TMPM4L1FWAUG** | **TMPM4L1FYAUG** |
| :-----------: | :-----------: |
| **TMPM4L2FWADUG** | **TMPM4L2FWAQG** |
| **TMPM4L2FYADUG** | **TMPM4L2FYAQG** |
| **TMPM4L4FWAUG**  | **TMPM4L4FYAUG** |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

+ Defined all base addresses in `mcu_reg_addresses.h` file for all TOSHIBA devices
  + This makes adding new TOSHIBA devices to SDK easier

### Fixes

+ Fixed SPI Ethernet libraries not showing up in the NECTO Studio Library Manager
  + SPI Ethernet middleware (`MikroSDK.Ethernet.Transport`, `MikroSDK.Ethernet.Spi`, `MikroSDK.Ethernet.Net`) and controller libraries (`MikroSDK.Ethernet.ENC28J60`, `MikroSDK.Ethernet.LAN8651`, `MikroSDK.Ethernet.LAN9250`, `MikroSDK.Ethernet.W5500`, `MikroSDK.Ethernet.W6100`) are now installed with the SDK
+ Fixed SPI Ethernet controller register and protocol bugs
  + W5500 no longer blocks broadcast frames, ARP requests and DHCP replies are received again
  + W6100 now clears the send interrupt through `Sn_IRCLR` and locks the network registers with the documented key, MAC/IP can still be changed after initialization (e.g. after DHCP)
  + ENC28J60 PHY register reads (link status, PHY ID) now return the correct value, PHY duplex now follows the full duplex setting
  + ENC28J60 releases receive buffer space for dropped frames and reports failed transmissions
  + LAN8651 validates the receive footer parity and discards frames marked for dropping
  + LAN9250 received frames no longer include the 4-byte FCS, consistent with the other controllers
+ SPI Ethernet now reports initialization and bus failures
  + Initialization verifies the chip identity and fails if no controller responds, e.g. wrong mikroBUS position
  + Failed SPI transactions and controller timeouts are reported instead of returning success
  + W5500/W6100 transmit waits for free buffer space and reports success only after the frame was sent
  + Corrupt receive headers are recovered from (socket reopen / receive buffer reset) instead of losing synchronization
  + Cached MAC/IP addresses are updated only after the controller accepted them
+ SPI Ethernet network helpers validate received packets
  + New `eth_net_ipv4_payload()` validates IPv4 version, header length, total length and checksum and rejects fragments
  + ICMP echo requests are checked for code and checksum, ARP requests for address sizes
  + DHCP replies are checked for client MAC, server ports, UDP checksum and the selected server
  + `tests/spi_ethernet` uses a per-device DHCP transaction ID, restarts discovery on DHCPNAK and checks TCP segment bounds

> NOTE:
>> SPI Ethernet API changes compared to v2.20.2:
>>
>> + `eth_net_handle_dhcp()` takes the device MAC address as a new third parameter
>> + `W5500_FRAME_SIZE` and `W6100_FRAME_SIZE` are now 1514 (MACRAW frame without FCS)
>> + `W5500_Sn_MR_MF` and `W6100_Sn_MR_MF` corrected to `0x80`, `W6100_PHYSR_RST` replaced by `W6100_PHYSR_CAB` and `W6100_PHYCR1_RST`
>> + LAN9250 `read_packet` returns the frame without FCS (4 bytes shorter)
>> + `eth_transport_t` has a new `bus_error` member

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-11-17](./new_hw/2026-11-17.md)**
+ **[2026-11-18](./new_hw/2026-11-18.md)**
+ **[2026-11-19](./new_hw/2026-11-19.md)**
+ **[2026-11-20](./new_hw/2026-11-20.md)**
+ **[2026-11-23](./new_hw/2026-11-23.md)**
+ **[2026-11-24](./new_hw/2026-11-24.md)**
+ **[2026-11-25](./new_hw/2026-11-25.md)**
+ **[2026-11-26](./new_hw/2026-11-26.md)**
+ **[2026-11-27](./new_hw/2026-11-27.md)**
+ **[2026-11-30](./new_hw/2026-11-30.md)**
+ **[2026-12-01](./new_hw/2026-12-01.md)**
+ **[2026-12-02](./new_hw/2026-12-02.md)**
+ **[2026-12-03](./new_hw/2026-12-03.md)**
+ **[2026-12-04](./new_hw/2026-12-04.md)**
+ **[2026-12-07](./new_hw/2026-12-07.md)**
+ **[2026-12-08](./new_hw/2026-12-08.md)**
+ **[2026-12-09](./new_hw/2026-12-09.md)**
+ **[2026-12-10](./new_hw/2026-12-10.md)**
+ **[2026-12-11](./new_hw/2026-12-11.md)**
+ **[2026-12-14](./new_hw/2026-12-14.md)**
+ **[2026-12-15](./new_hw/2026-12-15.md)**
+ **[2026-12-16](./new_hw/2026-12-16.md)**
+ **[2026-12-17](./new_hw/2026-12-17.md)**
+ **[2026-12-18](./new_hw/2026-12-18.md)**
+ **[2026-12-21](./new_hw/2026-12-21.md)**
+ **[2026-12-22](./new_hw/2026-12-22.md)**
+ **[2026-12-23](./new_hw/2026-12-23.md)**
+ **[2026-12-24](./new_hw/2026-12-24.md)**
+ **[2026-12-25](./new_hw/2026-12-25.md)**
+ **[2026-12-28](./new_hw/2026-12-28.md)**
+ **[2026-12-29](./new_hw/2026-12-29.md)**
+ **[2026-12-30](./new_hw/2026-12-30.md)**
+ **[2026-12-31](./new_hw/2026-12-31.md)**
+ **[2027-01-01](./new_hw/2027-01-01.md)**
+ **[2027-01-04](./new_hw/2027-01-04.md)**
+ **[2027-01-05](./new_hw/2027-01-05.md)**
+ **[2027-01-06](./new_hw/2027-01-06.md)**
+ **[2027-01-07](./new_hw/2027-01-07.md)**
+ **[2027-01-08](./new_hw/2027-01-08.md)**
+ **[2027-01-11](./new_hw/2027-01-11.md)**
+ **[2027-01-12](./new_hw/2027-01-12.md)**
+ **[2027-01-13](./new_hw/2027-01-13.md)**
+ **[2027-01-14](./new_hw/2027-01-14.md)**
+ **[2027-01-15](./new_hw/2027-01-15.md)**
+ **[2027-01-18](./new_hw/2027-01-18.md)**
+ **[2027-01-19](./new_hw/2027-01-19.md)**
+ **[2027-01-20](./new_hw/2027-01-20.md)**
+ **[2027-01-21](./new_hw/2027-01-21.md)**
+ **[2027-01-22](./new_hw/2027-01-22.md)**
+ **[2027-01-25](./new_hw/2027-01-25.md)**
+ **[2027-01-26](./new_hw/2027-01-26.md)**
+ **[2027-01-27](./new_hw/2027-01-27.md)**
+ **[2027-01-28](./new_hw/2027-01-28.md)**
+ **[2027-01-29](./new_hw/2027-01-29.md)**
+ **[2027-02-01](./new_hw/2027-02-01.md)**
+ **[2027-02-02](./new_hw/2027-02-02.md)**
+ **[2027-02-03](./new_hw/2027-02-03.md)**
+ **[2027-02-04](./new_hw/2027-02-04.md)**
+ **[2027-02-05](./new_hw/2027-02-05.md)**
+ **[2027-02-08](./new_hw/2027-02-08.md)**
+ **[2027-02-09](./new_hw/2027-02-09.md)**
+ **[2027-02-10](./new_hw/2027-02-10.md)**
+ **[2027-02-11](./new_hw/2027-02-11.md)**
+ **[2027-02-12](./new_hw/2027-02-12.md)**
+ **[2027-02-15](./new_hw/2027-02-15.md)**
+ **[2027-02-16](./new_hw/2027-02-16.md)**
+ **[2027-02-17](./new_hw/2027-02-17.md)**
+ **[2027-02-18](./new_hw/2027-02-18.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
