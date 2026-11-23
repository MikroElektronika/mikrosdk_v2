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
* @file  mcu_reg_addresses.h
* @brief MCU specific register address definitions.
* @details R7F101GLG register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R7F101GLG REGISTER DEFINITIONS
#define GPIO_PORT0_BASE (0xFFF00UL)
#define GPIO_PORT1_BASE (0xFFF01UL)
#define GPIO_PORT2_BASE (0xFFF02UL)
#define GPIO_PORT3_BASE (0xFFF03UL)
#define GPIO_PORT4_BASE (0xFFF04UL)
#define GPIO_PORT5_BASE (0xFFF05UL)
#define GPIO_PORT6_BASE (0xFFF06UL)
#define GPIO_PORT7_BASE (0xFFF07UL)
#define GPIO_PORT12_BASE (0xFFF0CUL)
#define GPIO_PORT13_BASE (0xFFF0DUL)
#define GPIO_PORT14_BASE (0xFFF0EUL)
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF30UL); // ADM0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF50UL); // IICA0
static const hal_ll_base_addr_t HAL_LL_SAU0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0100UL); // SSR00
static const hal_ll_base_addr_t HAL_LL_SAU1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0140UL); // SSR10
static const hal_ll_base_addr_t HAL_LL_SPI0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF10UL); // SDR00 (CSI00)
static const hal_ll_base_addr_t HAL_LL_SPI1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF12UL); // SDR01 (CSI01)
static const hal_ll_base_addr_t HAL_LL_SPI2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF44UL); // SDR02 (CSI10)
static const hal_ll_base_addr_t HAL_LL_SPI3_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF46UL); // SDR03 (CSI11)
static const hal_ll_base_addr_t HAL_LL_SPI4_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF48UL); // SDR10 (CSI20)
static const hal_ll_base_addr_t HAL_LL_SPI5_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF4AUL); // SDR11 (CSI21)
static const hal_ll_base_addr_t HAL_LL_TAU0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0190UL); // TMR00
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF1AUL); // TDR01 (TO01 slave)
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF66UL); // TDR03 (TO03 slave)
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF10UL); // SDR00 (TXD0)
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF44UL); // SDR02 (TXD1)
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF48UL); // SDR10 (TXD2)
// EOF REGISTER DEFINITIONS

// R7F101GLG MODULE SPECIFICS
// PIOR0 sits apart from PIOR1-PIOR3, which are consecutive.
#define hal_ll_pior_reg_addr(_index) ( ( _index ) ? ( 0xF02ACUL + ( _index ) ) : 0xF0077UL )

// GPIO
// PMCAn sits at HAL_LL_GPIO_PMCA_BASE + n, masks list the analog capable pins per port.
#define HAL_LL_GPIO_PMCA_BASE (0xF0060UL)
#define HAL_LL_GPIO_PMCA_MASKS { 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC0 }
// PDIDISn sits at HAL_LL_GPIO_PDIDIS_BASE + n, bit n of the mask is set if port n has one.
#define HAL_LL_GPIO_PDIDIS_BASE (0xF02B0UL)
#define HAL_LL_GPIO_PDIDIS_PORTS (0x20ABU)

// ADC
#define HAL_LL_ADC_RESULT_ADDR (0xFFF1EUL) // ADCR, ADCRH at +1
#define HAL_LL_ADC_ADM3_ADDR (0xF0014UL)
#define HAL_LL_ADC_AVREFP_PIN (GPIO_P020)

// I2C, IICA0 2nd SFR area, INTIICA0 flag/mask and PIOR0 bit 2.
#define HAL_LL_I2C0_CTRL_BASE_ADDR (0xF0230UL) // IICCTL00
#define HAL_LL_I2C0_IF_ADDR (0xFFFE2UL) // IF1L
#define HAL_LL_I2C0_MK_ADDR (0xFFFE6UL) // MK1L
#define HAL_LL_I2C0_INT_BIT (3)
#define HAL_LL_I2C0_PIOR_REG (0)
#define HAL_LL_I2C0_PIOR_MASK (0x04)

// SPI, INTCSIp flag and PIOR bits, CSI01/10/11/21 have fixed pins.
#define HAL_LL_SPI0_IF_ADDR (0xFFFE1UL) // IF0H
#define HAL_LL_SPI0_IF_BIT (5)
#define HAL_LL_SPI0_PIOR_REG (0)
#define HAL_LL_SPI0_PIOR_MASK (0x02)
#define HAL_LL_SPI1_IF_ADDR (0xFFFE2UL) // IF1L
#define HAL_LL_SPI1_IF_BIT (4)
#define HAL_LL_SPI1_PIOR_REG (0)
#define HAL_LL_SPI1_PIOR_MASK (0x00)
#define HAL_LL_SPI2_IF_ADDR (0xFFFE2UL) // IF1L
#define HAL_LL_SPI2_IF_BIT (0)
#define HAL_LL_SPI2_PIOR_REG (0)
#define HAL_LL_SPI2_PIOR_MASK (0x00)
#define HAL_LL_SPI3_IF_ADDR (0xFFFE2UL) // IF1L
#define HAL_LL_SPI3_IF_BIT (1)
#define HAL_LL_SPI3_PIOR_REG (0)
#define HAL_LL_SPI3_PIOR_MASK (0x00)
#define HAL_LL_SPI4_IF_ADDR (0xFFFE1UL) // IF0H
#define HAL_LL_SPI4_IF_BIT (0)
#define HAL_LL_SPI4_PIOR_REG (0)
#define HAL_LL_SPI4_PIOR_MASK (0x80)
#define HAL_LL_SPI5_IF_ADDR (0xFFFE1UL) // IF0H
#define HAL_LL_SPI5_IF_BIT (1)
#define HAL_LL_SPI5_PIOR_REG (0)
#define HAL_LL_SPI5_PIOR_MASK (0x00)

// TIM, PIOR3 bit routing TO0(2n+1).
#define HAL_LL_TIM0_PIOR_REG (3)
#define HAL_LL_TIM0_PIOR_MASK (0x20)
#define HAL_LL_TIM1_PIOR_REG (3)
#define HAL_LL_TIM1_PIOR_MASK (0x10)

// UART, receive data register (SDRm1/SDRm3) and PIOR0 bits.
// UART0 uses bits 1 and 6: AF 0 = P51/P50, AF 1 = P17/P16, AF 2 = P12/P11.
#define HAL_LL_UART0_RX_DATA_ADDR (0xFFF12UL) // SDR01
#define HAL_LL_UART0_PIOR_REG (0)
#define HAL_LL_UART0_PIOR_MASK (0x42)
#define HAL_LL_UART1_RX_DATA_ADDR (0xFFF46UL) // SDR03
#define HAL_LL_UART1_PIOR_REG (0)
#define HAL_LL_UART1_PIOR_MASK (0x20)
#define HAL_LL_UART2_RX_DATA_ADDR (0xFFF4AUL) // SDR11
#define HAL_LL_UART2_PIOR_REG (0)
#define HAL_LL_UART2_PIOR_MASK (0x80)
// EOF MODULE SPECIFICS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
