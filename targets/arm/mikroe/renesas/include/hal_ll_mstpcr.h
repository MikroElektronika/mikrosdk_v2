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
#define _MSTPCRA   ( uint32_t * )0x4001E01C
#define _MSTPCRB   ( uint32_t * )0x40047000
#define _MSTPCRC   ( uint32_t * )0x40047004
#define _MSTPCRD   ( uint32_t * )0x40047008

#define MSTPCRA_MSTPA0_POS 0 // SRAM0
#define MSTPCRA_MSTPA6_POS 6 // ECCSRAM
#define MSTPCRA_MSTPA22_POS 22 // DMA/DTC
#define MSTPCRB_MSTPB2_POS 2 // CAN0
#define MSTPCRB_MSTPB8_POS 8 // I2C1
#define MSTPCRB_MSTPB9_POS 9 // I2C0
#define MSTPCRB_MSTPB11_POS 11 // USBFS
#define MSTPCRB_MSTPB18_POS 18 // SPI1
#define MSTPCRB_MSTPB19_POS 19 // SPI0
#define MSTPCRB_MSTPB22_POS 22 // SCI9
#define MSTPCRB_MSTPB29_POS 29 // SCI2
#define MSTPCRB_MSTPB30_POS 30 // SCI1
#define MSTPCRB_MSTPB31_POS 31 // SCI0
#define MSTPCRC_MSTPC0_POS 0 // CAC
#define MSTPCRC_MSTPC1_POS 1 // CRC
#define MSTPCRC_MSTPC3_POS 3 // CTSU
#define MSTPCRC_MSTPC4_POS 4 // SLCDC
#define MSTPCRC_MSTPC8_POS 8 // SSIE0
#define MSTPCRC_MSTPC13_POS 13 // DOC
#define MSTPCRC_MSTPC14_POS 14 // ELC
#define MSTPCRC_MSTPC31_POS 31 // SCE5
#define MSTPCRD_MSTPD2_POS 2 // AGT1
#define MSTPCRD_MSTPD3_POS 3 // AGT0
#define MSTPCRD_MSTPD5_POS 5 // GPT321 to GPT320
#define MSTPCRD_MSTPD6_POS 6 // GPT167 to GPT162
#define MSTPCRD_MSTPD14_POS 14 // POEG
#define MSTPCRD_MSTPD16_POS 16 // ADC140
#define MSTPCRD_MSTPD19_POS 19 // DAC8
#define MSTPCRD_MSTPD20_POS 20 // DAC12
#define MSTPCRD_MSTPD29_POS 29 // ACMPLP
#define MSTPCRD_MSTPD31_POS 31 // OPAMP

typedef struct
{
  uint32_t iclk;    // System clock frequency in Hz
  uint32_t pclka;   // PCLKA clock frequency in Hz
  uint32_t pclkb;   // PCLKB clock frequency in Hz
  uint32_t pclkc;   // PCLKC clock frequency in Hz
  uint32_t pclkd;   // PCLKD clock frequency in Hz
  uint32_t fclk;    // Flash interface clock frequency in Hz
} system_clocks_t;

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_MSTPCR_H_
// ------------------------------------------------------------------------- END
