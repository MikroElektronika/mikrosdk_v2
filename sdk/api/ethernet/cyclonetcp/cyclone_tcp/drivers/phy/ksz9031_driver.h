/**
 * @file ksz9031_driver.h
 * @brief KSZ9031 Gigabit Ethernet PHY driver
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2023 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.3.0
 **/

#ifndef _KSZ9031_DRIVER_H
#define _KSZ9031_DRIVER_H

//Dependencies
#include "core/nic.h"

//PHY address
#ifndef KSZ9031_PHY_ADDR
   #define KSZ9031_PHY_ADDR 7
#elif (KSZ9031_PHY_ADDR < 0 || KSZ9031_PHY_ADDR > 31)
   #error KSZ9031_PHY_ADDR parameter is not valid
#endif

//KSZ9031 PHY registers
#define KSZ9031_BMCR                                                 0x00
#define KSZ9031_BMSR                                                 0x01
#define KSZ9031_PHYID1                                               0x02
#define KSZ9031_PHYID2                                               0x03
#define KSZ9031_ANAR                                                 0x04
#define KSZ9031_ANLPAR                                               0x05
#define KSZ9031_ANER                                                 0x06
#define KSZ9031_ANNPR                                                0x07
#define KSZ9031_ANLPNPR                                              0x08
#define KSZ9031_GBCR                                                 0x09
#define KSZ9031_GBSR                                                 0x0A
#define KSZ9031_MMDACR                                               0x0D
#define KSZ9031_MMDAADR                                              0x0E
#define KSZ9031_GBESR                                                0x0F
#define KSZ9031_RLB                                                  0x11
#define KSZ9031_LINKMD                                               0x12
#define KSZ9031_DPMAPCSS                                             0x13
#define KSZ9031_RXERCTR                                              0x15
#define KSZ9031_ICSR                                                 0x1B
#define KSZ9031_AUTOMDI                                              0x1C
#define KSZ9031_PHYCON                                               0x1F

//KSZ9031 MMD registers
#define KSZ9031_AN_FLP_BURST_TRANSMIT_LO                             0x00, 0x03
#define KSZ9031_AN_FLP_BURST_TRANSMIT_HI                             0x00, 0x04
#define KSZ9031_1000BASE_T_LINK_UP_TIME_CTRL                         0x01, 0x5A
#define KSZ9031_COMMON_CTRL                                          0x02, 0x00
#define KSZ9031_STRAP_STAT                                           0x02, 0x01
#define KSZ9031_OP_MODE_STRAP_OVERRIDE                               0x02, 0x02
#define KSZ9031_OP_MODE_STRAP_STAT                                   0x02, 0x03
#define KSZ9031_RGMII_CTRL_SIGNAL_PAD_SKEW                           0x02, 0x04
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW                               0x02, 0x05
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW                               0x02, 0x06
#define KSZ9031_GMII_CLK_PAD_SKEW                                    0x02, 0x08
#define KSZ9031_WOL_CTRL                                             0x02, 0x10
#define KSZ9031_WOL_MAGIC_PKT_MAC_DA0                                0x02, 0x11
#define KSZ9031_WOL_MAGIC_PKT_MAC_DA1                                0x02, 0x12
#define KSZ9031_WOL_MAGIC_PKT_MAC_DA2                                0x02, 0x13
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_CRC0                            0x02, 0x14
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_CRC1                            0x02, 0x15
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_CRC0                            0x02, 0x16
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_CRC1                            0x02, 0x17
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_CRC0                            0x02, 0x18
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_CRC1                            0x02, 0x19
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_CRC0                            0x02, 0x1A
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_CRC1                            0x02, 0x1B
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_MASK0                           0x02, 0x1C
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_MASK1                           0x02, 0x1D
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_MASK2                           0x02, 0x1E
#define KSZ9031_WOL_CUSTOM_PKT_TYPE0_MASK3                           0x02, 0x1F
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_MASK0                           0x02, 0x20
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_MASK1                           0x02, 0x21
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_MASK2                           0x02, 0x22
#define KSZ9031_WOL_CUSTOM_PKT_TYPE1_MASK3                           0x02, 0x23
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_MASK0                           0x02, 0x24
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_MASK1                           0x02, 0x25
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_MASK2                           0x02, 0x26
#define KSZ9031_WOL_CUSTOM_PKT_TYPE2_MASK3                           0x02, 0x27
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_MASK0                           0x02, 0x28
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_MASK1                           0x02, 0x29
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_MASK2                           0x02, 0x2A
#define KSZ9031_WOL_CUSTOM_PKT_TYPE3_MASK3                           0x02, 0x2B
#define KSZ9031_ANALOG_CTRL4                                         0x1C, 0x04
#define KSZ9031_EDPD_CTRL                                            0x1C, 0x23

//Basic Control register
#define KSZ9031_BMCR_RESET                                           0x8000
#define KSZ9031_BMCR_LOOPBACK                                        0x4000
#define KSZ9031_BMCR_SPEED_SEL_LSB                                   0x2000
#define KSZ9031_BMCR_AN_EN                                           0x1000
#define KSZ9031_BMCR_POWER_DOWN                                      0x0800
#define KSZ9031_BMCR_ISOLATE                                         0x0400
#define KSZ9031_BMCR_RESTART_AN                                      0x0200
#define KSZ9031_BMCR_DUPLEX_MODE                                     0x0100
#define KSZ9031_BMCR_SPEED_SEL_MSB                                   0x0040

//Basic Status register
#define KSZ9031_BMSR_100BT4                                          0x8000
#define KSZ9031_BMSR_100BTX_FD                                       0x4000
#define KSZ9031_BMSR_100BTX_HD                                       0x2000
#define KSZ9031_BMSR_10BT_FD                                         0x1000
#define KSZ9031_BMSR_10BT_HD                                         0x0800
#define KSZ9031_BMSR_EXTENDED_STATUS                                 0x0100
#define KSZ9031_BMSR_NO_PREAMBLE                                     0x0040
#define KSZ9031_BMSR_AN_COMPLETE                                     0x0020
#define KSZ9031_BMSR_REMOTE_FAULT                                    0x0010
#define KSZ9031_BMSR_AN_CAPABLE                                      0x0008
#define KSZ9031_BMSR_LINK_STATUS                                     0x0004
#define KSZ9031_BMSR_JABBER_DETECT                                   0x0002
#define KSZ9031_BMSR_EXTENDED_CAPABLE                                0x0001

//PHY Identifier 1 register
#define KSZ9031_PHYID1_PHY_ID_MSB                                    0xFFFF
#define KSZ9031_PHYID1_PHY_ID_MSB_DEFAULT                            0x0022

//PHY Identifier 2 register
#define KSZ9031_PHYID2_PHY_ID_LSB                                    0xFC00
#define KSZ9031_PHYID2_PHY_ID_LSB_DEFAULT                            0x1400
#define KSZ9031_PHYID2_MODEL_NUM                                     0x03F0
#define KSZ9031_PHYID2_MODEL_NUM_DEFAULT                             0x0220
#define KSZ9031_PHYID2_REVISION_NUM                                  0x000F

//Auto-Negotiation Advertisement register
#define KSZ9031_ANAR_NEXT_PAGE                                       0x8000
#define KSZ9031_ANAR_REMOTE_FAULT                                    0x2000
#define KSZ9031_ANAR_PAUSE                                           0x0C00
#define KSZ9031_ANAR_100BT4                                          0x0200
#define KSZ9031_ANAR_100BTX_FD                                       0x0100
#define KSZ9031_ANAR_100BTX_HD                                       0x0080
#define KSZ9031_ANAR_10BT_FD                                         0x0040
#define KSZ9031_ANAR_10BT_HD                                         0x0020
#define KSZ9031_ANAR_SELECTOR                                        0x001F
#define KSZ9031_ANAR_SELECTOR_DEFAULT                                0x0001

//Auto-Negotiation Link Partner Ability register
#define KSZ9031_ANLPAR_NEXT_PAGE                                     0x8000
#define KSZ9031_ANLPAR_ACK                                           0x4000
#define KSZ9031_ANLPAR_REMOTE_FAULT                                  0x2000
#define KSZ9031_ANLPAR_PAUSE                                         0x0C00
#define KSZ9031_ANLPAR_100BT4                                        0x0200
#define KSZ9031_ANLPAR_100BTX_FD                                     0x0100
#define KSZ9031_ANLPAR_100BTX_HD                                     0x0080
#define KSZ9031_ANLPAR_10BT_FD                                       0x0040
#define KSZ9031_ANLPAR_10BT_HD                                       0x0020
#define KSZ9031_ANLPAR_SELECTOR                                      0x001F
#define KSZ9031_ANLPAR_SELECTOR_DEFAULT                              0x0001

//Auto-Negotiation Expansion register
#define KSZ9031_ANER_PAR_DETECT_FAULT                                0x0010
#define KSZ9031_ANER_LP_NEXT_PAGE_ABLE                               0x0008
#define KSZ9031_ANER_NEXT_PAGE_ABLE                                  0x0004
#define KSZ9031_ANER_PAGE_RECEIVED                                   0x0002
#define KSZ9031_ANER_LP_AN_ABLE                                      0x0001

//Auto-Negotiation Next Page register
#define KSZ9031_ANNPR_NEXT_PAGE                                      0x8000
#define KSZ9031_ANNPR_MSG_PAGE                                       0x2000
#define KSZ9031_ANNPR_ACK2                                           0x1000
#define KSZ9031_ANNPR_TOGGLE                                         0x0800
#define KSZ9031_ANNPR_MESSAGE                                        0x07FF

//Link Partner Next Page Ability register
#define KSZ9031_ANLPNPR_NEXT_PAGE                                    0x8000
#define KSZ9031_ANLPNPR_ACK                                          0x4000
#define KSZ9031_ANLPNPR_MSG_PAGE                                     0x2000
#define KSZ9031_ANLPNPR_ACK2                                         0x1000
#define KSZ9031_ANLPNPR_TOGGLE                                       0x0800
#define KSZ9031_ANLPNPR_MESSAGE                                      0x07FF

//1000BASE-T Control register
#define KSZ9031_GBCR_TEST_MODE                                       0xE000
#define KSZ9031_GBCR_MS_MAN_CONF_EN                                  0x1000
#define KSZ9031_GBCR_MS_MAN_CONF_VAL                                 0x0800
#define KSZ9031_GBCR_PORT_TYPE                                       0x0400
#define KSZ9031_GBCR_1000BT_FD                                       0x0200
#define KSZ9031_GBCR_1000BT_HD                                       0x0100

//1000BASE-T Status register
#define KSZ9031_GBSR_MS_CONF_FAULT                                   0x8000
#define KSZ9031_GBSR_MS_CONF_RES                                     0x4000
#define KSZ9031_GBSR_LOCAL_RECEIVER_STATUS                           0x2000
#define KSZ9031_GBSR_REMOTE_RECEIVER_STATUS                          0x1000
#define KSZ9031_GBSR_LP_1000BT_FD                                    0x0800
#define KSZ9031_GBSR_LP_1000BT_HD                                    0x0400
#define KSZ9031_GBSR_IDLE_ERR_COUNT                                  0x00FF

//MMD Access Control register
#define KSZ9031_MMDACR_FUNC                                          0xC000
#define KSZ9031_MMDACR_FUNC_ADDR                                     0x0000
#define KSZ9031_MMDACR_FUNC_DATA_NO_POST_INC                         0x4000
#define KSZ9031_MMDACR_FUNC_DATA_POST_INC_RW                         0x8000
#define KSZ9031_MMDACR_FUNC_DATA_POST_INC_W                          0xC000
#define KSZ9031_MMDACR_DEVAD                                         0x001F

//Extended Status register
#define KSZ9031_GBESR_1000BX_FD                                      0x8000
#define KSZ9031_GBESR_1000BX_HD                                      0x4000
#define KSZ9031_GBESR_1000BT_FD                                      0x2000
#define KSZ9031_GBESR_1000BT_HD                                      0x1000

//Remote Loopback register
#define KSZ9031_RLB_REMOTE_LOOPBACK                                  0x0100

//LinkMD Cable Diagnostic register
#define KSZ9031_LINKMD_TEST_EN                                       0x8000
#define KSZ9031_LINKMD_PAIR                                          0x3000
#define KSZ9031_LINKMD_PAIR_A                                        0x0000
#define KSZ9031_LINKMD_PAIR_B                                        0x1000
#define KSZ9031_LINKMD_PAIR_C                                        0x2000
#define KSZ9031_LINKMD_PAIR_D                                        0x3000
#define KSZ9031_LINKMD_STATUS                                        0x0300
#define KSZ9031_LINKMD_STATUS_NORMAL                                 0x0000
#define KSZ9031_LINKMD_STATUS_OPEN                                   0x0100
#define KSZ9031_LINKMD_STATUS_SHORT                                  0x0200
#define KSZ9031_LINKMD_FAULT_DATA                                    0x00FF

//Digital PMA/PCS Status register
#define KSZ9031_DPMAPCSS_1000BT_LINK_STATUS                          0x0004
#define KSZ9031_DPMAPCSS_100BTX_LINK_STATUS                          0x0002

//Interrupt Control/Status register
#define KSZ9031_ICSR_JABBER_IE                                       0x8000
#define KSZ9031_ICSR_RECEIVE_ERROR_IE                                0x4000
#define KSZ9031_ICSR_PAGE_RECEIVED_IE                                0x2000
#define KSZ9031_ICSR_PAR_DETECT_FAULT_IE                             0x1000
#define KSZ9031_ICSR_LP_ACK_IE                                       0x0800
#define KSZ9031_ICSR_LINK_DOWN_IE                                    0x0400
#define KSZ9031_ICSR_REMOTE_FAULT_IE                                 0x0200
#define KSZ9031_ICSR_LINK_UP_IE                                      0x0100
#define KSZ9031_ICSR_JABBER_IF                                       0x0080
#define KSZ9031_ICSR_RECEIVE_ERROR_IF                                0x0040
#define KSZ9031_ICSR_PAGE_RECEIVED_IF                                0x0020
#define KSZ9031_ICSR_PAR_DETECT_FAULT_IF                             0x0010
#define KSZ9031_ICSR_LP_ACK_IF                                       0x0008
#define KSZ9031_ICSR_LINK_DOWN_IF                                    0x0004
#define KSZ9031_ICSR_REMOTE_FAULT_IF                                 0x0002
#define KSZ9031_ICSR_LINK_UP_IF                                      0x0001

//Auto MDI/MDI-X register
#define KSZ9031_AUTOMDI_MDI_SET                                      0x0080
#define KSZ9031_AUTOMDI_SWAP_OFF                                     0x0040

//PHY Control register
#define KSZ9031_PHYCON_INT_LEVEL                                     0x4000
#define KSZ9031_PHYCON_JABBER_EN                                     0x0200
#define KSZ9031_PHYCON_SPEED_1000BT                                  0x0040
#define KSZ9031_PHYCON_SPEED_100BTX                                  0x0020
#define KSZ9031_PHYCON_SPEED_10BT                                    0x0010
#define KSZ9031_PHYCON_DUPLEX_STATUS                                 0x0008
#define KSZ9031_PHYCON_1000BT_MS_STATUS                              0x0004
#define KSZ9031_PHYCON_LINK_STATUS_CHECK_FAIL                        0x0001

//1000BASE-T Link-Up Time Control register
#define KSZ9031_1000BASE_T_LINK_UP_TIME_CTRL_1000BASE_T_LINK_UP_TIME 0x000E

//Common Control register
#define KSZ9031_COMMON_CTRL_LED_MODE_OVERRIDE                        0x0010
#define KSZ9031_COMMON_CTRL_LED_MODE                                 0x0008
#define KSZ9031_COMMON_CTRL_CLK125_EN_STATUS                         0x0002

//Strap Status register
#define KSZ9031_STRAP_STAT_LED_MODE_STARP_IN_STATUS                  0x0080
#define KSZ9031_STRAP_STAT_CLK125_EN_STRAP_IN_STATUS                 0x0020
#define KSZ9031_STRAP_STAT_PHYAD_STRAP_IN_VALUE                      0x0007

//Operation Mode Strap Override register
#define KSZ9031_OP_MODE_STRAP_OVERRIDE_PME_N2_OUT_EN                 0x0400
#define KSZ9031_OP_MODE_STRAP_OVERRIDE_PME_N1_OUT_EN                 0x0100
#define KSZ9031_OP_MODE_STRAP_OVERRIDE_CHIP_PD_OVERRIDE              0x0080
#define KSZ9031_OP_MODE_STRAP_OVERRIDE_NAND_TREE_OVERRIDE            0x0010
#define KSZ9031_OP_MODE_STRAP_OVERRIDE_GMII_MII_OVERRIDE             0x0002

//Operation Mode Strap Status register
#define KSZ9031_OP_MODE_STRAP_STAT_CHIP_PD_STRAP_IN_STATUS           0x0080
#define KSZ9031_OP_MODE_STRAP_STAT_NAND_TREE_STRAP_IN_STATUS         0x0010
#define KSZ9031_OP_MODE_STRAP_STAT_GMII_MII_STRAP_IN_STATUS          0x0002

//RGMII Control Signal Pad Skew register
#define KSZ9031_RGMII_CTRL_SIGNAL_PAD_SKEW_RX_DV                     0x00F0
#define KSZ9031_RGMII_CTRL_SIGNAL_PAD_SKEW_RX_DV_DEFAULT             0x0070
#define KSZ9031_RGMII_CTRL_SIGNAL_PAD_SKEW_TX_EN                     0x000F
#define KSZ9031_RGMII_CTRL_SIGNAL_PAD_SKEW_TX_EN_DEFAULT             0x0007

//RGMII RX Data Pad Skew register
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD3                          0xF000
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD3_DEFAULT                  0x7000
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD2                          0x0F00
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD2_DEFAULT                  0x0700
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD1                          0x00F0
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD1_DEFAULT                  0x0070
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD0                          0x000F
#define KSZ9031_RGMII_RX_DATA_PAD_SKEW_RXD0_DEFAULT                  0x0007

//RGMII TX Data Pad Skew register
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD3                          0xF000
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD3_DEFAULT                  0x7000
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD2                          0x0F00
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD2_DEFAULT                  0x0700
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD1                          0x00F0
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD1_DEFAULT                  0x0070
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD0                          0x000F
#define KSZ9031_RGMII_TX_DATA_PAD_SKEW_TXD0_DEFAULT                  0x0007

//GMII Clock Pad Skew register
#define KSZ9031_GMII_CLK_PAD_SKEW_GTX_CLK                            0x03E0
#define KSZ9031_GMII_CLK_PAD_SKEW_GTX_CLK_DEFAULT                    0x01E0
#define KSZ9031_GMII_CLK_PAD_SKEW_RX_CLK                             0x001F
#define KSZ9031_GMII_CLK_PAD_SKEW_RX_CLK_DEFAULT                     0x000F

//Wake-On-LAN Control register
#define KSZ9031_WOL_CTRL_PME_OUT_SEL                                 0xC000
#define KSZ9031_WOL_CTRL_MAGIC_PKT_DETECT_EN                         0x0040
#define KSZ9031_WOL_CTRL_CUSTOM_PKT_TYPE_3_DETECT_EN                 0x0020
#define KSZ9031_WOL_CTRL_CUSTOM_PKT_TYPE_2_DETECT_EN                 0x0010
#define KSZ9031_WOL_CTRL_CUSTOM_PKT_TYPE_1_DETECT_EN                 0x0008
#define KSZ9031_WOL_CTRL_CUSTOM_PKT_TYPE_0_DETECT_EN                 0x0004
#define KSZ9031_WOL_CTRL_LINK_DOWN_DETECT_EN                         0x0002
#define KSZ9031_WOL_CTRL_LINK_UP_DETECT_EN                           0x0001

//Analog Control 4 register
#define KSZ9031_ANALOG_CTRL4_10BASE_TE_MODE                          0x0400

//EDPD Control register
#define KSZ9031_EDPD_CTRL_EDPD_MODE_EN                               0x0001

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//KSZ9031 Ethernet PHY driver
extern const PhyDriver ksz9031PhyDriver;

//KSZ9031 related functions
error_t ksz9031Init(NetInterface *interface);
void ksz9031InitHook(NetInterface *interface);

void ksz9031Tick(NetInterface *interface);

void ksz9031EnableIrq(NetInterface *interface);
void ksz9031DisableIrq(NetInterface *interface);

void ksz9031EventHandler(NetInterface *interface);

void ksz9031WritePhyReg(NetInterface *interface, uint8_t address,
   uint16_t data);

uint16_t ksz9031ReadPhyReg(NetInterface *interface, uint8_t address);

void ksz9031DumpPhyReg(NetInterface *interface);

void ksz9031WriteMmdReg(NetInterface *interface, uint8_t devAddr,
   uint16_t regAddr, uint16_t data);

uint16_t ksz9031ReadMmdReg(NetInterface *interface, uint8_t devAddr,
   uint16_t regAddr);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
