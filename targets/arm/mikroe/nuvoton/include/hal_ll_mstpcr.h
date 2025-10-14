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

#define CLK_BASE        0x40000200UL

#define CLK_AHBCLK      ( uint32_t * )( CLK_BASE + 0x04UL )
#define CLK_APBCLK0     ( uint32_t * )( CLK_BASE + 0x08UL )
#define CLK_APBCLK1     ( uint32_t * )( CLK_BASE + 0x0CUL )
#define CLK_CLKSEL0     ( uint32_t * )( CLK_BASE + 0x10UL )
#define CLK_CLKSEL1     ( uint32_t * )( CLK_BASE + 0x14UL )
#define CLK_CLKSEL2     ( uint32_t * )( CLK_BASE + 0x18UL )
#define CLK_CLKSEL3     ( uint32_t * )( CLK_BASE + 0x1CUL )
#define CLK_CLKDIV0     ( uint32_t * )( CLK_BASE + 0x20UL )
#define CLK_CLKDIV1     ( uint32_t * )( CLK_BASE + 0x24UL )
#define CLK_CLKDIV4     ( uint32_t * )( CLK_BASE + 0x30UL )

typedef struct
{
    uint32_t hclk;
    uint32_t pclk;
} clk_clocks_t;

/**
 * @brief Gets clock values.
 *
 * @param clk_clocks_t[OUT] CLK clocks structure.
 *
 * @return *clk_clocks_t Structure containing clock values.
 */
void CLK_GetClocksFrequency( clk_clocks_t* CLK_Clocks );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_MSTPCR_H_
// ------------------------------------------------------------------------- END
