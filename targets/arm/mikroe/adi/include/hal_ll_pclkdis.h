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
 * @file  hal_ll_pclkdis.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_MSTPCR_H_
#define _HAL_LL_MSTPCR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#define _GCR_PCLKDIS0_    ( uint32_t * )0x40000024UL
#define _GCR_PCLKDIS1_    ( uint32_t * )0x40000048UL
#define _LPGCR_PCLKDIS_    ( uint32_t * )0x4008000CUL

#define _FCR_ADCREFTRIM0_ ( uint32_t * )0x40000828UL
#define _FCR_ADCREFTRIM1_ ( uint32_t * )0x4000082CUL
#define _FCR_ADCREFTRIM2_ ( uint32_t * )0x40000830UL

#define _MCR_ADCCFG0_     ( uint32_t * )0x40006C50UL

#define GCR_PCLKDIS0_0    (0)   // GPIO0 PORT
#define GCR_PCLKDIS0_1    (1)   // GPIO1 PORT
#define GCR_PCLKDIS0_2    (2)   // GPIO2 PORT
#define GCR_PCLKDIS0_6    (6)   // SPI0
#define GCR_PCLKDIS0_7    (7)   // SPI1
#define GCR_PCLKDIS0_8    (8)   // SPI2
#define GCR_PCLKDIS0_9    (9)   // UART0
#define GCR_PCLKDIS0_10   (10)  // UART1
#define GCR_PCLKDIS0_13   (13)  // I2C0
#define GCR_PCLKDIS0_15   (15)  // TMR0
#define GCR_PCLKDIS0_16   (16)  // TMR1
#define GCR_PCLKDIS0_17   (17)  // TMR2
#define GCR_PCLKDIS0_18   (18)  // TMR3
#define GCR_PCLKDIS0_23   (23)  // ADC
#define GCR_PCLKDIS0_28   (28)  // I2C1

#define GCR_PCLKDIS1_1    (1)   // UART2
#define GCR_PCLKDIS1_13   (13)  // OW
#define GCR_PCLKDIS1_16   (16)  // SPI3
#define GCR_PCLKDIS1_17   (17)  // SPI4
#define GCR_PCLKDIS1_24   (24)  // I2C2

#define LPGCR_PCLKDIS_0   (0)  // GPIO3 PORT
#define LPGCR_PCLKDIS_2   (2)  // TMR4(LPTMR0)
#define LPGCR_PCLKDIS_3   (3)  // TMR5(LPTMR1)
#define LPGCR_PCLKDIS_4   (4)  // UART3(LPUART0)

typedef struct
{
    uint32_t pclk;
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
