/**
 * @file adin1200_driver.c
 * @brief ADIN1200 Ethernet PHY driver
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
#include "drivers/phy/adin1200_driver.h"
#include "debug.h"


/**
 * @brief ADIN1200 Ethernet PHY driver
 **/

const PhyDriver adin1200PhyDriver =
{
   adin1200Init,
   adin1200Tick,
   adin1200EnableIrq,
   adin1200DisableIrq,
   adin1200EventHandler
};


/**
 * @brief ADIN1200 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t adin1200Init(NetInterface *interface)
{
   uint16_t value;

   //Debug message
   TRACE_INFO("Initializing ADIN1200...\r\n");

   //Undefined PHY address?
   if(interface->phyAddr >= 32)
   {
      //Use the default address
      interface->phyAddr = ADIN1200_PHY_ADDR;
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

   //Reset PHY transceiver
   adin1200WritePhyReg(interface, ADIN1200_MII_CONTROL,
      ADIN1200_MII_CONTROL_SFT_RST);

   //Wait for the reset to complete
   while(adin1200ReadPhyReg(interface, ADIN1200_MII_CONTROL) &
      ADIN1200_MII_CONTROL_SFT_RST)
   {
   }

   //Dump PHY registers for debugging purpose
   adin1200DumpPhyReg(interface);

   //The PHY will generate interrupts when link status changes are detected
   adin1200WritePhyReg(interface, ADIN1200_IRQ_MASK,
      ADIN1200_IRQ_MASK_LNK_STAT_CHNG_IRQ_EN | ADIN1200_IRQ_MASK_HW_IRQ_EN);

   //Set the function of the INT_N pin
   adin1200WriteExtReg(interface, ADIN1200_GE_IO_INT_N_OR_CNTRL,
      ADIN1200_GE_IO_INT_N_OR_CNTRL_GE_IO_INT_N_OR_CNTRL_DEFAULT);

   //Exit software power-down
   value = adin1200ReadPhyReg(interface, ADIN1200_MII_CONTROL);
   value &= ~ADIN1200_MII_CONTROL_SFT_PD;
   adin1200WritePhyReg(interface, ADIN1200_MII_CONTROL, value);

   //Perform custom configuration
   adin1200InitHook(interface);

   //Force the TCP/IP stack to poll the link state at startup
   interface->phyEvent = TRUE;
   //Notify the TCP/IP stack of the event
   osSetEvent(&netEvent);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief ADIN1200 custom configuration
 * @param[in] interface Underlying network interface
 **/

__weak_func void adin1200InitHook(NetInterface *interface)
{
}


/**
 * @brief ADIN1200 timer handler
 * @param[in] interface Underlying network interface
 **/

void adin1200Tick(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

   //No external interrupt line driver?
   if(interface->extIntDriver == NULL)
   {
      //Read basic status register
      value = adin1200ReadPhyReg(interface, ADIN1200_MII_STATUS);
      //Retrieve current link state
      linkState = (value & ADIN1200_MII_STATUS_LINK_STAT_LAT) ? TRUE : FALSE;

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

void adin1200EnableIrq(NetInterface *interface)
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

void adin1200DisableIrq(NetInterface *interface)
{
   //Disable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
   {
      interface->extIntDriver->disableIrq();
   }
}


/**
 * @brief ADIN1200 event handler
 * @param[in] interface Underlying network interface
 **/

void adin1200EventHandler(NetInterface *interface)
{
   uint16_t value;

   //Read IRQ status register to acknowledge the interrupt
   value = adin1200ReadPhyReg(interface, ADIN1200_IRQ_STATUS);

   //Link status change?
   if((value & ADIN1200_IRQ_STATUS_LNK_STAT_CHNG_IRQ_STAT) != 0)
   {
      //Read PHY status register
      value = adin1200ReadPhyReg(interface, ADIN1200_PHY_STATUS_1);

      //Link is up?
      if((value & ADIN1200_PHY_STATUS_1_LINK_STAT) != 0)
      {
         //The HCD_TECH field indicates the resolved technology after the link
         //is established
         switch(value & ADIN1200_PHY_STATUS_1_HCD_TECH)
         {
         //10BASE-T half-duplex
         case ADIN1200_PHY_STATUS_1_HCD_TECH_10BT_HD:
            interface->linkSpeed = NIC_LINK_SPEED_10MBPS;
            interface->duplexMode = NIC_HALF_DUPLEX_MODE;
            break;

         //10BASE-T full-duplex
         case ADIN1200_PHY_STATUS_1_HCD_TECH_10BT_FD:
            interface->linkSpeed = NIC_LINK_SPEED_10MBPS;
            interface->duplexMode = NIC_FULL_DUPLEX_MODE;
            break;

         //100BASE-TX half-duplex
         case ADIN1200_PHY_STATUS_1_HCD_TECH_100BTX_HD:
            interface->linkSpeed = NIC_LINK_SPEED_100MBPS;
            interface->duplexMode = NIC_HALF_DUPLEX_MODE;
            break;

         //100BASE-TX full-duplex
         case ADIN1200_PHY_STATUS_1_HCD_TECH_100BTX_FD:
            interface->linkSpeed = NIC_LINK_SPEED_100MBPS;
            interface->duplexMode = NIC_FULL_DUPLEX_MODE;
            break;

         //Unknown operation mode
         default:
            //Debug message
            TRACE_WARNING("Invalid operation mode!\r\n");
            break;
         }

         //Update link state
         interface->linkState = TRUE;

         //Adjust MAC configuration parameters for proper operation
         interface->nicDriver->updateMacConfig(interface);
      }
      else
      {
         //Update link state
         interface->linkState = FALSE;
      }

      //Process link state change event
      nicNotifyLinkChange(interface);
   }
}


/**
 * @brief Write PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @param[in] data Register value
 **/

void adin1200WritePhyReg(NetInterface *interface, uint8_t address,
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

uint16_t adin1200ReadPhyReg(NetInterface *interface, uint8_t address)
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

void adin1200DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i,
         adin1200ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}


/**
 * @brief Write extended register
 * @param[in] interface Underlying network interface
 * @param[in] address Extended register address
 * @param[in] data Register value
 **/

void adin1200WriteExtReg(NetInterface *interface, uint16_t address,
   uint16_t data)
{
   //The EXT_REG_PTR and EXT_REG_DATA registers provide a mechanism to access
   //the indirect access address map via directly accessible registers
   adin1200WritePhyReg(interface, ADIN1200_EXT_REG_PTR, address);

   //Write the content of the extended register
   adin1200WritePhyReg(interface, ADIN1200_EXT_REG_DATA, data);
}


/**
 * @brief Read extended register
 * @param[in] interface Underlying network interface
 * @param[in] address Extended register address
 * @return Register value
 **/

uint16_t adin1200ReadExtReg(NetInterface *interface, uint16_t address)
{
   //The EXT_REG_PTR and EXT_REG_DATA registers provide a mechanism to access
   //the indirect access address map via directly accessible registers
   adin1200WritePhyReg(interface, ADIN1200_EXT_REG_PTR, address);

   //Read the content of the extended register
   return adin1200ReadPhyReg(interface, ADIN1200_EXT_REG_DATA);
}
