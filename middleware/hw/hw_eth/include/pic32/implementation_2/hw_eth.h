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
 * @note Needs to be implemented by user for current MCU.
 * @return None
 */
static inline void hw_eth_init(void);

/**
 * @brief Externally linked API for ETH configuration.
 */
void pic32mzEthInitGpio(NetInterface *interface) {
    hw_eth_init();
}

static inline void hw_eth_init(void) {
    // EMDC - RD11 - O - RPD11
    // EMDIO - RJ1 - I/O
    // ETXEN - RD6 - O -RPD6
    // ETXD0 - RJ8 - O -AN35
    // ETXD1 - RJ9 - O -AN36
    // nINT(ERFCLKO) - RJ11 - I -AN37
    // ECRS_DV - RH13 - I
    // ERXD0 - RH8 - I
    // ERXD1 - RH5 - I -AN41
    // ERXER - RH4 - I -AN40

    ANSELJbits.ANSJ8 = 0;  //AN35 - digital
    ANSELJbits.ANSJ9 = 0;  //AN36 - digital
    ANSELJbits.ANSJ11 = 0; //AN37 - digital
    ANSELHbits.ANSH4 = 0;  //AN40 - digital
    ANSELHbits.ANSH5 = 0;  //AN41 - digital
}

/*! @} */ // ethernet
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _HW_ETH_H_
// ------------------------------------------------------------------------- END
