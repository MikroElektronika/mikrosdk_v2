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
 * @file  hal_ll_rcc.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_RCC_H_
#define _HAL_LL_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Core register addresses used in source
 */
#define _SIM_SCGC1     (( uint32_t * )0x40048028)
#define _SIM_SCGC2     (( uint32_t * )0x4004802C)
#define _SIM_SCGC3     (( uint32_t * )0x40048030)
#define _SIM_SCGC4     (( uint32_t * )0x40048034)
#define _SIM_SCGC5     (( uint32_t * )0x40048038)
#define _SIM_SCGC6     (( uint32_t * )0x4004803C)
#define _SIM_SCGC7     (( uint32_t * )0x40048040)

#define _SIM_SOPT1     (( uint32_t * )0x40047000)
#define _SIM_SOPT2     (( uint32_t * )0x40048004)

/**
 *  RCC Structs used in source
 */
#ifdef __MKV4X_RCC__
typedef struct
{
    uint32_t system_frequency;           // SYSTEM clock frequency in Hz
    uint32_t fast_peripheral_frequency;  // FAST PERIPHERAL clock frequency in Hz
    uint32_t flash_frequency;            // FLASH clock frequency  in Hz
} SIM_ClocksTypeDef;
#elif defined(__MKV5X_RCC__)
typedef struct
{
    uint32_t system_frequency;           // SYSTEM clock frequency in Hz
    uint32_t fast_peripheral_frequency;  // BUSCLOCK clock frequency in Hz
    uint32_t flexbus_frequency;          // FLEXBUS clock frequency in Hz
    uint32_t bus_flash_frequency;        // FLASH clock frequency in Hz
} SIM_ClocksTypeDef;
#else // __MKX_RCC__
typedef struct
{
    uint32_t system_frequency;           // SYSTEM clock frequency in Hz
    uint32_t busclock_frequency;         // BUSCLOCK clock frequency in Hz
    uint32_t flexbus_frequency;          // FLEXBUS clock frequency in Hz
    uint32_t flash_frequency;            // FLASH clock frequency in Hz
} SIM_ClocksTypeDef;
#endif

/**
 * @brief Gets clock values.
 * @param[out] SIM_ClocksTypeDef SIM clocks structure.
 * @return SIM_Clocks Structure containing clock values.
 */
void SIM_GetClocksFrequency( SIM_ClocksTypeDef *SIM_Clocks );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_RCC_H_
// ------------------------------------------------------------------------- END
