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
 * @file  hal_ll_mstpcr.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_MSTPCR_H_
#define _HAL_LL_MSTPCR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Core register addresses used in source
 */

#define _MSTPCRA   ( uint32_t * )0x00080010
#define _MSTPCRB   ( uint32_t * )0x00080014
#define _MSTPCRC   ( uint32_t * )0x00080018
#define _MSTPCRD   ( uint32_t * )0x0008001C


#define HAL_LL_MSTPCR_PRCR_ADDR        (0x000803FEUL)
#define HAL_LL_MSTPCR_PRCR_LOCK_VAL    (0xA500U)
#define HAL_LL_MSTPCR_PRCR_UNLOCK_VAL  (0xA502U)

// MSTPCRA bit positions
#define MSTPCRA_MSTPA16_POS 16 // ADC1
#define MSTPCRA_MSTPA17_POS 17 // ADC0
#define MSTPCRA_MSTPA23_POS 23 // ADC2

#define MSTPCRB_MSTPB4_POS   4 // SCI12
#define MSTPCRB_MSTPB21_POS  21 // RIIC0
#define MSTPCRB_MSTPB25_POS  25 // SCI6
#define MSTPCRB_MSTPB26_POS  26 // SCI5
#define MSTPCRB_MSTPB30_POS  30 // SCI1

#define MSTPCRC_MSTPC24_POS  24 // RSCI11
#define MSTPCRC_MSTPC26_POS  26 // RSCI9
#define MSTPCRC_MSTPC27_POS  27 // RSCI8

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

#endif // _HAL_LL_MSTPCR_H_
// ------------------------------------------------------------------------- END
