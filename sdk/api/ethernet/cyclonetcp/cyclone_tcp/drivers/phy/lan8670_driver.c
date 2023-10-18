/**
 * @file lan8670_driver.c
 * @brief LAN8670 10Base-T1S Ethernet PHY driver
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

//Switch to the appropriate trace level
#define TRACE_LEVEL NIC_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "drivers/phy/lan8670_driver.h"
#include "debug.h"


/**
 * @brief LAN8670 Ethernet PHY driver
 **/

const PhyDriver lan8670PhyDriver =
{
   lan8670Init,
   lan8670Tick,
   lan8670EnableIrq,
   lan8670DisableIrq,
   lan8670EventHandler
};


/**
 * @brief LAN8670 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t lan8670Init(NetInterface *interface)
{
   //Debug message
   TRACE_INFO("Initializing LAN8670...\r\n");

   //Undefined PHY address?
   if(interface->phyAddr >= 32)
   {
      //Use the default address
      interface->phyAddr = LAN8670_PHY_ADDR;
   }

   //Initialize serial management interface
   if(interface->smiDriver != NULL)
   {
      interface->smiDriver->init();
   }

   //Initialize external interrupt line driver
   if(interface->extIntDriver != NULL)
   {
      interface->extIntDriver->init();
   }

   //Dump PHY registers for debugging purpose
   lan8670DumpPhyReg(interface);

   //Configure PHY transceiver
   lan8670ModifyMmdReg(interface, 0x1F, 0x00D0, 0x0E03, 0x0002);
   lan8670ModifyMmdReg(interface, 0x1F, 0x00D1, 0x0300, 0x0000);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0084, 0xFFC0, 0x3380);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0085, 0x000F, 0x0006);
   lan8670ModifyMmdReg(interface, 0x1F, 0x008A, 0xF800, 0xC000);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0087, 0x801C, 0x801C);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0088, 0x1FFF, 0x033F);
   lan8670ModifyMmdReg(interface, 0x1F, 0x008B, 0xFFFF, 0x0404);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0080, 0x0600, 0x0600);
   lan8670ModifyMmdReg(interface, 0x1F, 0x00F1, 0x7F00, 0x2400);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0096, 0x2000, 0x2000);
   lan8670ModifyMmdReg(interface, 0x1F, 0x0099, 0xFFFF, 0x7F80);

#if (LAN8670_PLCA_SUPPORT == ENABLED)
   //Set PLCA burst
   lan8670WriteMmdReg(interface, LAN8670_PLCA_BURST,
      LAN8670_PLCA_BURST_MAXBC_DISABLED | LAN8670_PLCA_BURST_BTMR_DEFAULT);

   //Set PLCA node count and local ID
   lan8670WriteMmdReg(interface, LAN8670_PLCA_CTRL1,
      ((LAN8670_NODE_COUNT << 8) & LAN8670_PLCA_CTRL1_NCNT) |
      (LAN8670_LOCAL_ID & LAN8670_PLCA_CTRL1_ID));

   //Enable PLCA
   lan8670WriteMmdReg(interface, LAN8670_PLCA_CTRL0, LAN8670_PLCA_CTRL0_EN);
#else
   //Disable PLCA
   lan8670WriteMmdReg(interface, LAN8670_PLCA_CTRL0, 0);
#endif

   //Perform custom configuration
   lan8670InitHook(interface);

   //Force the TCP/IP stack to poll the link state at startup
   interface->phyEvent = TRUE;
   //Notify the TCP/IP stack of the event
   osSetEvent(&netEvent);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief LAN8670 custom configuration
 * @param[in] interface Underlying network interface
 **/

__weak_func void lan8670InitHook(NetInterface *interface)
{
}


/**
 * @brief LAN8670 timer handler
 * @param[in] interface Underlying network interface
 **/

void lan8670Tick(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

   //No external interrupt line driver?
   if(interface->extIntDriver == NULL)
   {
#if (LAN8670_PLCA_SUPPORT == ENABLED)
      //Read PLCA status register
      value = lan8670ReadMmdReg(interface, LAN8670_PLCA_STS);

      //The PST field indicates that the PLCA reconciliation sublayer is active
      //and a BEACON is being regularly transmitted or received
      linkState = (value & LAN8670_PLCA_STS_PST) ? TRUE : FALSE;
#else
      //Link status indication is not supported
      linkState = TRUE;
#endif

      //Link up event?
      if(linkState && !interface->linkState)
      {
         //Set event flag
         interface->phyEvent = TRUE;
         //Notify the TCP/IP stack of the event
         osSetEvent(&netEvent);
      }
      //Link down event?
      else if(!linkState && interface->linkState)
      {
         //Set event flag
         interface->phyEvent = TRUE;
         //Notify the TCP/IP stack of the event
         osSetEvent(&netEvent);
      }
   }
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void lan8670EnableIrq(NetInterface *interface)
{
   //Enable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
   {
      interface->extIntDriver->enableIrq();
   }
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void lan8670DisableIrq(NetInterface *interface)
{
   //Disable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
   {
      interface->extIntDriver->disableIrq();
   }
}


/**
 * @brief LAN8670 event handler
 * @param[in] interface Underlying network interface
 **/

void lan8670EventHandler(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

#if (LAN8670_PLCA_SUPPORT == ENABLED)
   //Read PLCA status register
   value = lan8670ReadMmdReg(interface, LAN8670_PLCA_STS);

   //The PST field indicates that the PLCA reconciliation sublayer is active
   //and a BEACON is being regularly transmitted or received
   linkState = (value & LAN8670_PLCA_STS_PST) ? TRUE : FALSE;
#else
   //Link status indication is not supported
   linkState = TRUE;
#endif

   //Link is up?
   if(linkState)
   {
      //The PHY is only able to operate in 10 Mbps mode
      interface->linkSpeed = NIC_LINK_SPEED_10MBPS;
      interface->duplexMode = NIC_HALF_DUPLEX_MODE;

      //Adjust MAC configuration parameters for proper operation
      interface->nicDriver->updateMacConfig(interface);

      //Update link state
      interface->linkState = TRUE;
   }
   else
   {
      //Update link state
      interface->linkState = FALSE;
   }

   //Process link state change event
   nicNotifyLinkChange(interface);
}


/**
 * @brief Write PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @param[in] data Register value
 **/

void lan8670WritePhyReg(NetInterface *interface, uint8_t address,
   uint16_t data)
{
   //Write the specified PHY register
   if(interface->smiDriver != NULL)
   {
      interface->smiDriver->writePhyReg(SMI_OPCODE_WRITE,
         interface->phyAddr, address, data);
   }
   else
   {
      interface->nicDriver->writePhyReg(SMI_OPCODE_WRITE,
         interface->phyAddr, address, data);
   }
}


/**
 * @brief Read PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t lan8670ReadPhyReg(NetInterface *interface, uint8_t address)
{
   uint16_t data;

   //Read the specified PHY register
   if(interface->smiDriver != NULL)
   {
      data = interface->smiDriver->readPhyReg(SMI_OPCODE_READ,
         interface->phyAddr, address);
   }
   else
   {
      data = interface->nicDriver->readPhyReg(SMI_OPCODE_READ,
         interface->phyAddr, address);
   }

   //Return the value of the PHY register
   return data;
}


/**
 * @brief Dump PHY registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void lan8670DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i,
         lan8670ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}


/**
 * @brief Write MMD register
 * @param[in] interface Underlying network interface
 * @param[in] devAddr Device address
 * @param[in] regAddr Register address
 * @param[in] data MMD register value
 **/

void lan8670WriteMmdReg(NetInterface *interface, uint8_t devAddr,
   uint16_t regAddr, uint16_t data)
{
   //Select register operation
   lan8670WritePhyReg(interface, LAN8670_MMDCTRL,
      LAN8670_MMDCTRL_FNCTN_ADDR | (devAddr & LAN8670_MMDCTRL_DEVAD));

   //Write MMD register address
   lan8670WritePhyReg(interface, LAN8670_MMDAD, regAddr);

   //Select data operation
   lan8670WritePhyReg(interface, LAN8670_MMDCTRL,
      LAN8670_MMDCTRL_FNCTN_DATA_NO_POST_INC | (devAddr & LAN8670_MMDCTRL_DEVAD));

   //Write the content of the MMD register
   lan8670WritePhyReg(interface, LAN8670_MMDAD, data);
}


/**
 * @brief Read MMD register
 * @param[in] interface Underlying network interface
 * @param[in] devAddr Device address
 * @param[in] regAddr Register address
 * @return MMD register value
 **/

uint16_t lan8670ReadMmdReg(NetInterface *interface, uint8_t devAddr,
   uint16_t regAddr)
{
   //Select register operation
   lan8670WritePhyReg(interface, LAN8670_MMDCTRL,
      LAN8670_MMDCTRL_FNCTN_ADDR | (devAddr & LAN8670_MMDCTRL_DEVAD));

   //Write MMD register address
   lan8670WritePhyReg(interface, LAN8670_MMDAD, regAddr);

   //Select data operation
   lan8670WritePhyReg(interface, LAN8670_MMDCTRL,
      LAN8670_MMDCTRL_FNCTN_DATA_NO_POST_INC | (devAddr & LAN8670_MMDCTRL_DEVAD));

   //Read the content of the MMD register
   return lan8670ReadPhyReg(interface, LAN8670_MMDAD);
}


/**
 * @brief Modify MMD register
 * @param[in] interface Underlying network interface
 * @param[in] devAddr Device address
 * @param[in] regAddr Register address
 * @param[in] mask 16-bit mask
 * @param[in] data 16-bit value
 **/

void lan8670ModifyMmdReg(NetInterface *interface, uint8_t devAddr,
   uint16_t regAddr, uint16_t mask, uint16_t data)
{
   uint16_t value;

   //Read the current value of the MMD register
   value = lan8670ReadMmdReg(interface, devAddr, regAddr);
   //Modify register value
   value = (value & ~mask) | data;
   //Write the modified value back to the MMD register
   lan8670WriteMmdReg(interface, devAddr, regAddr, value);
}
