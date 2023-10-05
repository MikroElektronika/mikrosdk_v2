/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
 * @note Needs to implemented by user for current MCU.
 * @return None
 */
static inline void hw_eth_init(void);

/**
 * @brief Externally linked API for ETH configuration.
 */
void mkv5xEthInitGpio(NetInterface *interface) {
    hw_eth_init();
}

static inline void hw_eth_init(void) {
    // Note: Added for MikroE implementation.

    //Enable PORTA peripheral clock and PORTE for ENET_1588_CLKIN.
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;

    //Configure RMII0_RXER (PTA5).
    PORTA->PCR[5] = PORT_PCR_MUX(4) | PORT_PCR_PE_MASK;
    //Configure RMII0_RXD1 (PTA12).
    PORTA->PCR[12] = PORT_PCR_MUX(5);
    //Configure RMII0_RXD0 (PTA13).
    PORTA->PCR[13] = PORT_PCR_MUX(5);
    //Configure RMII0_CRS_DV (PTA14).
    PORTA->PCR[14] = PORT_PCR_MUX(5);
    //Configure RMII0_TXEN (PTA15).
    PORTA->PCR[15] = PORT_PCR_MUX(5);
    //Configure RMII0_TXD0 (PTA16).
    PORTA->PCR[16] = PORT_PCR_MUX(5);
    //Configure RMII0_TXD1 (PTA17).
    PORTA->PCR[17] = PORT_PCR_MUX(5);

    //Configure RMII0_MDIO (PTA7).
    PORTA->PCR[7] = PORT_PCR_MUX(5) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    //Configure RMII0_MDC (PTA8).
    PORTA->PCR[8] = PORT_PCR_MUX(5);

    //Configure ENET_1588_CLKIN (PTE26).
    PORTE->PCR[26] = PORT_PCR_MUX(2);

    //Select RMII clock source (ENET_1588_CLKIN) and IEEE 1588 timestamp clock source (ENET_1588_CLKIN).
    SIM->SOPT2 |= SIM_SOPT2_RMIISRC_MASK | SIM_SOPT2_TIMESRC_MASK;
}

/*! @} */ // ethernet
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _HW_ETH_H_
// ------------------------------------------------------------------------- END
