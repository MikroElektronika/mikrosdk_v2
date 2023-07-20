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
* @file  mcu_definitions.h
* @brief MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

// ADC
#define ADC1_PB0_CH0
#define ADC1_PB1_CH1
#define ADC1_PB2_CH2
#define ADC1_PB3_CH3
#define ADC1_PB4_CH4
#define ADC1_PB5_CH5
#define ADC1_PB6_CH6
#define ADC1_PB7_CH7

#define ADC_MODULE_1 (1)

#define HAL_LL_AN_COUNT (8)
#define ADC_MODULE_COUNT (1)

// ADC Register addresses and offsets
#define HAL_LL_ADC1_CTRLA_REG_ADDRESS (0x240)
#define HAL_LL_ADC1_BASE_ADDRESS (HAL_LL_ADC1_CTRLA_REG_ADDRESS)
#define HAL_LL_ADC1_CTRLB_REG_ADDRESS (0x241)
#define HAL_LL_ADC1_REFCTRL_REG_ADDRESS (0x242)
#define HAL_LL_ADC1_EVCTRL_REG_ADDRESS (0x243)
#define HAL_LL_ADC1_PRESCALER_REG_ADDRESS (0x244)
#define HAL_LL_ADC1_INTFLAGS_REG_ADDRESS (0x246)
#define HAL_LL_ADC1_TEMP_REG_ADDRESS (0x247)
#define HAL_LL_ADC1_CH0RESL_REG_ADDRESS (0x250)
#define HAL_LL_ADC1_CH0RESH_REG_ADDRESS (0x251)
#define HAL_LL_ADC1_CH0RES_REG_ADDRESS (0x250)
#define HAL_LL_ADC1_CH0CTRL_REG_ADDRESS (0x260)
#define HAL_LL_ADC1_CH0MUXCTRL_REG_ADDRESS (0x261)
#define HAL_LL_ADC1_CH0INTCTRL_REG_ADDRESS (0x262)
#define HAL_LL_ADC1_CH0INTFLAGS_REG_ADDRESS (0x263)
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define TWIC_SCL_PC1
#define TWIC_SDA_PC0

#define TWI_MODULE_C (1)
#define I2C_MODULE_0 (TWI_MODULE_C)
#define TWI_MODULE_COUNT (1)
#define I2C_MODULE_COUNT (TWI_MODULE_COUNT)

// I2C Register addresses and offsets
#define HAL_LL_TWIC_CTRL_REG_ADDRESS (0x480)
#define HAL_LL_I2C0_BASE_ADDRESS (HAL_LL_TWIC_CTRL_REG_ADDRESS)
#define HAL_LL_TWIC_MASTERCTRLA_REG_ADDRESS (0x481)
#define HAL_LL_TWIC_MASTERCTRLB_REG_ADDRESS (0x482)
#define HAL_LL_TWIC_MASTERCTRLC_REG_ADDRESS (0x483)
#define HAL_LL_TWIC_MASTERSTATUS_REG_ADDRESS (0x484)
#define HAL_LL_TWIC_MASTERBAUD_REG_ADDRESS (0x485)
#define HAL_LL_TWIC_MASTERADDR_REG_ADDRESS (0x486)
#define HAL_LL_TWIC_MASTERDATA_REG_ADDRESS (0x487)
#define HAL_LL_TWIC_SLAVECTRLA_REG_ADDRESS (0x488)
#define HAL_LL_TWIC_SLAVECTRLB_REG_ADDRESS (0x489)
#define HAL_LL_TWIC_SLAVESTATUS_REG_ADDRESS (0x48A)
#define HAL_LL_TWIC_SLAVEADDR_REG_ADDRESS (0x48B)
#define HAL_LL_TWIC_SLAVEDATA_REG_ADDRESS (0x48C)
#define HAL_LL_TWIC_SLAVEADDRMASK_REG_ADDRESS (0x48D)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define USARTC0_RXD_PC2
#define USARTC0_RXD_PC6_ALT
#define USARTC0_TXD_PC3
#define USARTC0_TXD_PC7_ALT

#define UART_MODULE_C0 (1)
#define UART_MODULE_0 (UART_MODULE_C0)
#define UART_MODULE_COUNT (1)

// U(S)ART Register addresses and offsets
#define HAL_LL_USARTC0_DATA_REG_ADDRESS (0x8A0)
#define HAL_LL_USARTC0_STATUS_REG_ADDRESS (0x8A1)
#define HAL_LL_USARTC0_CTRLA_REG_ADDRESS (0x8A3)
#define HAL_LL_USARTC0_CTRLB_REG_ADDRESS (0x8A4)
#define HAL_LL_USARTC0_CTRLC_REG_ADDRESS (0x8A5)
#define HAL_LL_USARTC0_BAUDCTRLA_REG_ADDRESS (0x8A6)
#define HAL_LL_USARTC0_BAUDCTRLB_REG_ADDRESS (0x8A7)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI0_MISO_PC6
#define SPI0_MOSI_PC5
#define SPI0_MOSI_PC7
#define SPI0_SCK_PC5
#define SPI0_SCK_PC7
#define SPI0_SS_PC4

#define SPI_MODULE_0 (1)
#define SPI_MODULE_COUNT (1)

// SPI Register addresses and offsets
#define HAL_LL_SPI0_CTRL_REG_ADDRESS (0x8C0)
#define HAL_LL_SPI0_INTCTRL_REG_ADDRESS (0x8C1)
#define HAL_LL_SPI0_STATUS_REG_ADDRESS (0x8C2)
#define HAL_LL_SPI0_DATA_REG_ADDRESS (0x8C3)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define TIM0_PC0_CH_A
#define TIM0_PC1_CH_B
#define TIM0_PC2_CH_C
#define TIM0_PC3_CH_D
#define TIM4_PC4_CH_A
#define TIM4_PC5_CH_B

#define TIM_MODULE_0 (1)
#define TIM_MODULE_4 (2)
#define TIM_MODULE_COUNT (2)

// TIM Register addresses and offsets
#define HAL_LL_TIM0_CTRLA_REG_ADDRESS (0x800)
#define HAL_LL_TIM0_CTRLB_REG_ADDRESS (0x801)
#define HAL_LL_TIM0_CTRLC_REG_ADDRESS (0x802)
#define HAL_LL_TIM0_CTRLD_REG_ADDRESS (0x803)
#define HAL_LL_TIM0_CTRLE_REG_ADDRESS (0x804)
#define HAL_LL_TIM0_INTCTRLA_REG_ADDRESS (0x806)
#define HAL_LL_TIM0_INTCTRLB_REG_ADDRESS (0x807)
#define HAL_LL_TIM0_CTRLFCLR_REG_ADDRESS (0x808)
#define HAL_LL_TIM0_CTRLGCLR_REG_ADDRESS (0x80A)
#define HAL_LL_TIM0_CTRLGSET_REG_ADDRESS (0x80B)
#define HAL_LL_TIM0_INTFLAGS_REG_ADDRESS (0x80C)
#define HAL_LL_TIM0_TEMP_REG_ADDRESS (0x80F)
#define HAL_LL_TIM0_PERBUF_REG_ADDRESS (0x836)
#define HAL_LL_TIM0_CCABUF_REG_ADDRESS (0x838)
#define HAL_LL_TIM0_CCBBUF_REG_ADDRESS (0x83A)
#define HAL_LL_TIM0_CCCBUF_REG_ADDRESS (0x83C)
#define HAL_LL_TIM0_CCDBUF_REG_ADDRESS (0x83E)
#define HAL_LL_TIM4_CTRLA_REG_ADDRESS (0x840)
#define HAL_LL_TIM4_CTRLB_REG_ADDRESS (0x841)
#define HAL_LL_TIM4_CTRLC_REG_ADDRESS (0x842)
#define HAL_LL_TIM4_CTRLD_REG_ADDRESS (0x843)
#define HAL_LL_TIM4_CTRLE_REG_ADDRESS (0x844)
#define HAL_LL_TIM4_INTCTRLA_REG_ADDRESS (0x846)
#define HAL_LL_TIM4_INTCTRLB_REG_ADDRESS (0x847)
#define HAL_LL_TIM4_CTRLFCLR_REG_ADDRESS (0x848)
#define HAL_LL_TIM4_CTRLFSET_REG_ADDRESS (0x849)
#define HAL_LL_TIM4_CTRLGCLR_REG_ADDRESS (0x84A)
#define HAL_LL_TIM4_CTRLGSET_REG_ADDRESS (0x84B)
#define HAL_LL_TIM4_INTFLAGS_REG_ADDRESS (0x84C)
#define HAL_LL_TIM4_TEMP_REG_ADDRESS (0x84F)
#define HAL_LL_TIM4_CNT_REG_ADDRESS (0x860)
#define HAL_LL_TIM4_PERL_REG_ADDRESS (0x866)
#define HAL_LL_TIM4_PERH_REG_ADDRESS (0x867)
#define HAL_LL_TIM4_PER_REG_ADDRESS (0x866)
#define HAL_LL_TIM4_CCA_REG_ADDRESS (0x868)
#define HAL_LL_TIM4_CCB_REG_ADDRESS (0x86A)
#define HAL_LL_TIM4_PERBUF_REG_ADDRESS (0x876)
#define HAL_LL_TIM4_CCABUF_REG_ADDRESS (0x878)
#define HAL_LL_TIM4_CCBBUF_REG_ADDRESS (0x87A)
#define HAL_LL_TIM0_CNT_REG_ADDRESS (0x820)
#define HAL_LL_TIM0_PERL_REG_ADDRESS (0x826)
#define HAL_LL_TIM0_PERH_REG_ADDRESS (0x827)
#define HAL_LL_TIM0_CCA_REG_ADDRESS (0x828)
#define HAL_LL_TIM0_CCB_REG_ADDRESS (0x82A)
#define HAL_LL_TIM0_CCC_REG_ADDRESS (0x82C)
#define HAL_LL_TIM0_CCD_REG_ADDRESS (0x82E)
// Following registers don't exist, but defined as NULL for source code implementation
#define HAL_LL_TIM4_CCCBUF_REG_ADDRESS (NULL)
#define HAL_LL_TIM4_CCDBUF_REG_ADDRESS (NULL)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
#define __PD0_CN
#define __PD1_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PG4_CN
#define __PG5_CN
#define __PG6_CN
#define __PG7_CN
#define __PM0_CN
#define __PM1_CN
#define __PM2_CN
#define __PM3_CN
#define __PM4_CN
#define __PM5_CN
#define __PM6_CN
#define __PM7_CN
#define __PR0_CN
#define __PR1_CN

#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_G_CN
#define __PORT_M_CN
#define __PORT_R_CN

#define PORT_SIZE  (8)
#define PORT_COUNT (6)

// GPIO Register addresses and offsets
#define DDRB_REG_ADDRESS (0x620)
#define PORTB_REG_ADDRESS (0x624)
#define PINB_REG_ADDRESS (0x628)
#define DDRC_REG_ADDRESS (0x640)
#define PORTC_REG_ADDRESS (0x644)
#define PINC_REG_ADDRESS (0x648)
#define DDRD_REG_ADDRESS (0x660)
#define PORTD_REG_ADDRESS (0x664)
#define PIND_REG_ADDRESS (0x668)
#define DDRG_REG_ADDRESS (0x6C0)
#define PORTG_REG_ADDRESS (0x6C4)
#define PING_REG_ADDRESS (0x6C8)
#define DDRM_REG_ADDRESS (0x760)
#define PORTM_REG_ADDRESS (0x764)
#define PINM_REG_ADDRESS (0x768)
#define DDRR_REG_ADDRESS (0x7E0)
#define PORTR_REG_ADDRESS (0x7E4)
#define PINR_REG_ADDRESS (0x7E8)
// REMAP Register addresses
#define HAL_LL_MODULE_REMAP (true)
#define PORTB_REMAP_REG_ADDRESS (0x62E)
#define PORTC_REMAP_REG_ADDRESS (0x64E)
#define PORTD_REMAP_REG_ADDRESS (0x66E)
#define PORTG_REMAP_REG_ADDRESS (0x6CE)
#define PORTM_REMAP_REG_ADDRESS (0x76E)
#define PORTR_REMAP_REG_ADDRESS (0x7EE)
// EOF GPIO Register addresses and offsets
// EOF GPIO

// POWER REDUCTION REGISTER
#define HAL_LL_PRPA_REG_ADDRESS (0x71)
#define HAL_LL_PRPB_REG_ADDRESS (0x72)
#define HAL_LL_PRPC_REG_ADDRESS (0x73)
#define HAL_LL_PRPE_REG_ADDRESS (0x75)
#define HAL_LL_POWER_REDUCTION (true)
// EOF POWER REDUCTION REGISTER

// IVT
#define HAL_LL_USARTC0_RXC_IVT (25)
#define HAL_LL_USARTC0_DRE_IVT (26)
#define HAL_LL_USARTC0_TXC_IVT (27)
// IVT ADDRESSES
#define HAL_LL_USARTC0_RXC_IVT_ADDRESS (0x32)
#define HAL_LL_USARTC0_DRE_IVT_ADDRESS (0x34)
#define HAL_LL_USARTC0_TXC_IVT_ADDRESS (0x36)
// Programmable multilevel interrupt controller
#define HAL_LL_PMIC_STATUS_REG_ADDRESS (0xA0)
#define HAL_LL_PMIC_INTPRI_REG_ADDRESS (0xA1)
#define HAL_LL_PMIC_CTRL_REG_ADDRESS (0xA2)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
