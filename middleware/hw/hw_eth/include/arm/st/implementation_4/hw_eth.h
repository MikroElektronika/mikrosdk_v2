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
#ifdef STM32F4
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#elif defined STM32F7
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_gpio.h"
#endif

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
void stm32f4xxEthInitGpio(NetInterface *interface) {
    hw_eth_init();
}

/**
 * @brief Externally linked API for ETH configuration.
 */
void stm32f7xxEthInitGpio(NetInterface *interface) {
    hw_eth_init();
}

static inline void hw_eth_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable SYSCFG clock
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    //Enable GPIO clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    //Configure MCO (PA8) as an output
    GPIO_InitStructure.Pin = GPIO_PIN_8;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Select RMII interface mode
    SYSCFG->PMC |= SYSCFG_PMC_MII_RMII_SEL;

    //Configure RMII pins
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF11_ETH;

    //Configure ETH_RMII_REF_CLK (PA1), ETH_MDIO (PA2) and ETH_RMII_CRS_DV (PA7)
    GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Configure ETH_RMII_TX_EN (PG11), ETH_RMII_TXD0 (PG13) and ETH_RMII_TXD1 (PG14)
    GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

    //Configure ETH_MDC (PC1), ETH_RMII_RXD0 (PC4) and ETH_RMII_RXD1 (PC5)
    GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    #ifdef STM32F4
    //Configure MCO1 pin to output the PLL clock divided by 3 (150/3=50MHz)
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_3);
    #elif defined STM32F7
    //Configure MCO1 pin to output the PLL clock divided by 4 (200/4=50MHz)
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_4);
    #endif
}

/*! @} */ // ethernet
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _HW_ETH_H_
// ------------------------------------------------------------------------- END
