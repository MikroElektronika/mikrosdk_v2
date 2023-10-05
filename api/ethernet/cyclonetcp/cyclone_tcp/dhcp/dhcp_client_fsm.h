/**
 * @file dhcp_client_fsm.h
 * @brief DHCP client finite state machine
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

#ifndef _DHCP_CLIENT_FSM_H
#define _DHCP_CLIENT_FSM_H

//Dependencies
#include "core/net.h"
#include "dhcp/dhcp_client.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//DHCP client related functions
void dhcpClientStateInit(DhcpClientContext *context);
void dhcpClientStateSelecting(DhcpClientContext *context);
void dhcpClientStateRequesting(DhcpClientContext *context);
void dhcpClientStateInitReboot(DhcpClientContext *context);
void dhcpClientStateRebooting(DhcpClientContext *context);
void dhcpClientStateProbing(DhcpClientContext *context);
void dhcpClientStateAnnouncing(DhcpClientContext *context);
void dhcpClientStateBound(DhcpClientContext *context);
void dhcpClientStateRenewing(DhcpClientContext *context);
void dhcpClientStateRebinding(DhcpClientContext *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
