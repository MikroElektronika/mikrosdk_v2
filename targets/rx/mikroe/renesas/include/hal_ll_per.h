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
 * @file  hal_ll_per.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_PER_H_
#define _HAL_LL_PER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Peripheral enable register addresses used in source
 */
#define _PER0_REG_ADDRESS      ( uint32_t * )0xF00F0
#define _PER1_REG_ADDRESS      ( uint32_t * )0xF00FA
#define _PER2_REG_ADDRESS      ( uint32_t * )0xF00FC

/**
 *  Bit positions in the peripheral enable registers
 */
// PER0
#define PER0_TAU0EN_POS 0 // TAU0
#define PER0_SAU0EN_POS 2 // SAU0
#define PER0_SAU1EN_POS 3 // SAU1
#define PER0_IICA0EN_POS 4 // IICA0
#define PER0_ADCEN_POS 5 // ADC
#define PER0_IICA1EN_POS 6 // IICA1
// PER1
#define PER1_UTA0EN_POS 2 // UARTA0
#define PER1_TML32EN_POS 4 // TML32
// PER2
#define PER2_UTA1EN_POS 2 // UARTA1
#define PER2_UTA2EN_POS 3 // UARTA2
#define PER2_UTA3EN_POS 4 // UARTA3
#define PER2_TKBEN_POS 5 // TKB


typedef struct
{
    uint32_t placeholder;
} system_clocks_t;

/**
 * @brief Gets clock values.
 * @param[out] system_clocks_t System clocks structure.
 * @return system_clocks_t Structure containing clock values.
 */
void SYSTEM_GetClocksFrequency( system_clocks_t * SYSTEM_Clocks );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PER_H_
// ------------------------------------------------------------------------- END
