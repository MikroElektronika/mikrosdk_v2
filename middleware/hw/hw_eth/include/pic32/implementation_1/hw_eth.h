/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file hw_eth.h
 * @brief Initializes ETH HW module.
 * @details Sets clock, pins, etc.
 */

#ifndef _HW_ETH_H_
#define _HW_ETH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu.h"
#include "net.h"

/*!
 * @addtogroup middleware Middleware
 * @{
 */

/*!
 * @addtogroup ethernet MikroE ETH HW implementation.
 * @brief MikroE ETH HW init library.
 *
 * @details This library initializes HW specific
 * ethernet pins/clock etc.
 * @{
 */

/**
 * @brief Initializes ETH.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @note Needs to be implemented by user for current MCU.
 * @return None
 */
static inline void hw_eth_init(void);

/**
 * @brief Externally linked API for ETH configuration.
 */
void pic32mxEthInitGpio(NetInterface *interface) {
    hw_eth_init();
}

extern uint32_t timeout; // Declared in application, and updated in 1ms_timer ISR
static inline void hw_eth_init(void) {
    // EMDC - RD11 - O
    // EMDIO - RD8 - I/O
    // ETXEN - RD6 - O
    // ETXD0 - RF1 - O
    // ETXD1 - RF0 - O
    // nINT(ERFCLKO) - RG9 - I
    // ECRS_DV - RG8 - I
    // ERXD0 - RB12 - I - AN12
    AD1PCFGbits.PCFG12 = 1;
    // ERXD1 - RB13 - I - AN13
    AD1PCFGbits.PCFG13 = 1;
    // ERXER - RB11 - I - AN11
    AD1PCFGbits.PCFG11 = 1;
    /** Note: ERXER - RB11 is not connected to PHY on MCU CARD for PIC32.
      *       To circumvent the problems that might arise, and to ensure proper functioning,
      *       RB11 must be shorted to ground!!!
      */

    // Configure PHY_RST (RG7)
    TRISGbits.TRISG7 = 0;
    // Reset PHY transceiver (hard reset)
    LATGbits.LATG7 = 0;
    timeout = 0;
    while (timeout < 50); // Must be asserted at least 25ms according to LAN8720A datasheet.
    LATGbits.LATG7 = 1;
    timeout = 0;
    while (timeout < 1);
}

/*! @} */ // ethernet
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _HW_ETH_H_
// ------------------------------------------------------------------------- END
