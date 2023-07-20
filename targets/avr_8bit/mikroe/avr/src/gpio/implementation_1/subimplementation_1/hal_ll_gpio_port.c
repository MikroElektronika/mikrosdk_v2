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
 * @file hal_ll_port_gpio.c
 * @brief Low level HAL GPIO ported source file.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS

// -------------------------------------------------------------- PRIVATE TYPES

/**
 *  Defines used in source
 */

/*!< @brief GPIO PORT null-pointer constants (for non-existant ports) */
#ifndef __PORT_A_CN
    #define PORTA_REG_ADDRESS NULL
    #define DDRA_REG_ADDRESS NULL
    #define PINA_REG_ADDRESS NULL
#endif
#ifndef __PORT_B_CN
    #define PORTB_REG_ADDRESS NULL
    #define DDRB_REG_ADDRESS NULL
    #define PINB_REG_ADDRESS NULL
#endif
#ifndef __PORT_C_CN
    #define PORTC_REG_ADDRESS NULL
    #define DDRC_REG_ADDRESS NULL
    #define PINC_REG_ADDRESS NULL
#endif
#ifndef __PORT_D_CN
    #define PORTD_REG_ADDRESS NULL
    #define DDRD_REG_ADDRESS NULL
    #define PIND_REG_ADDRESS NULL
#endif
#ifndef __PORT_E_CN
    #define PORTE_REG_ADDRESS NULL
    #define DDRE_REG_ADDRESS NULL
    #define PINE_REG_ADDRESS NULL
#endif
#ifndef __PORT_F_CN
    #define PORTF_REG_ADDRESS NULL
    #define DDRF_REG_ADDRESS NULL
    #define PINF_REG_ADDRESS NULL
#endif
#ifndef __PORT_G_CN
    #define PORTG_REG_ADDRESS NULL
    #define DDRG_REG_ADDRESS NULL
    #define PING_REG_ADDRESS NULL
#endif
#ifndef __PORT_H_CN
    #define PORTH_REG_ADDRESS NULL
    #define DDRH_REG_ADDRESS NULL
    #define PINH_REG_ADDRESS NULL
#endif
#ifndef __PORT_I_CN
    #define PORTI_REG_ADDRESS NULL
    #define DDRI_REG_ADDRESS NULL
    #define PINI_REG_ADDRESS NULL
#endif
#ifndef __PORT_J_CN
    #define PORTJ_REG_ADDRESS NULL
    #define DDRJ_REG_ADDRESS NULL
    #define PINJ_REG_ADDRESS NULL
#endif
#ifndef __PORT_K_CN
    #define PORTK_REG_ADDRESS NULL
    #define DDRK_REG_ADDRESS NULL
    #define PINK_REG_ADDRESS NULL
#endif
#ifndef __PORT_L_CN
    #define PORTL_REG_ADDRESS NULL
    #define DDRL_REG_ADDRESS NULL
    #define PINL_REG_ADDRESS NULL
#endif
#ifndef __PORT_M_CN
    #define PORTM_REG_ADDRESS NULL
    #define DDRM_REG_ADDRESS NULL
    #define PINM_REG_ADDRESS NULL
#endif
#ifndef __PORT_N_CN
    #define PORTN_REG_ADDRESS NULL
    #define DDRN_REG_ADDRESS NULL
    #define PINN_REG_ADDRESS NULL
#endif
#ifndef __PORT_P_CN
    #define PORTP_REG_ADDRESS NULL
    #define DDRP_REG_ADDRESS NULL
    #define PINP_REG_ADDRESS NULL
#endif
#ifndef __PORT_Q_CN
    #define PORTQ_REG_ADDRESS NULL
    #define DDRQ_REG_ADDRESS NULL
    #define PINQ_REG_ADDRESS NULL
#endif
#ifndef __PORT_R_CN
    #define PORTR_REG_ADDRESS NULL
    #define DDRR_REG_ADDRESS NULL
    #define PINR_REG_ADDRESS NULL
#endif
#ifndef __PORT_S_CN
    #define PORTS_REG_ADDRESS NULL
    #define DDRS_REG_ADDRESS NULL
    #define PINS_REG_ADDRESS NULL
#endif
#ifndef __PORT_T_CN
    #define PORTT_REG_ADDRESS NULL
    #define DDRT_REG_ADDRESS NULL
    #define PINT_REG_ADDRESS NULL
#endif

/*!< @brief GPIO PORT array */
static hal_ll_gpio_base_handle_t _hal_ll_gpio_port_addresses[] = {
    { PORTA_REG_ADDRESS, DDRA_REG_ADDRESS, PINA_REG_ADDRESS },
    { PORTB_REG_ADDRESS, DDRB_REG_ADDRESS, PINB_REG_ADDRESS },
    { PORTC_REG_ADDRESS, DDRC_REG_ADDRESS, PINC_REG_ADDRESS },
    { PORTD_REG_ADDRESS, DDRD_REG_ADDRESS, PIND_REG_ADDRESS },
    { PORTE_REG_ADDRESS, DDRE_REG_ADDRESS, PINE_REG_ADDRESS },
    { PORTF_REG_ADDRESS, DDRF_REG_ADDRESS, PINF_REG_ADDRESS },
    { PORTG_REG_ADDRESS, DDRG_REG_ADDRESS, PING_REG_ADDRESS },
    { PORTH_REG_ADDRESS, DDRH_REG_ADDRESS, PINH_REG_ADDRESS },
    { PORTI_REG_ADDRESS, DDRI_REG_ADDRESS, PINI_REG_ADDRESS },
    { PORTJ_REG_ADDRESS, DDRJ_REG_ADDRESS, PINJ_REG_ADDRESS },
    { PORTK_REG_ADDRESS, DDRK_REG_ADDRESS, PINK_REG_ADDRESS },
    { PORTL_REG_ADDRESS, DDRL_REG_ADDRESS, PINL_REG_ADDRESS },
    { PORTM_REG_ADDRESS, DDRM_REG_ADDRESS, PINM_REG_ADDRESS },
    { PORTN_REG_ADDRESS, DDRN_REG_ADDRESS, PINN_REG_ADDRESS },
    { PORTP_REG_ADDRESS, DDRP_REG_ADDRESS, PINP_REG_ADDRESS },
    { PORTQ_REG_ADDRESS, DDRQ_REG_ADDRESS, PINQ_REG_ADDRESS },
    { PORTR_REG_ADDRESS, DDRR_REG_ADDRESS, PINR_REG_ADDRESS },
    { PORTS_REG_ADDRESS, DDRS_REG_ADDRESS, PINS_REG_ADDRESS },
    { PORTT_REG_ADDRESS, DDRT_REG_ADDRESS, PINT_REG_ADDRESS },

    { HAL_LL_PORT_NC, HAL_LL_PORT_NC, HAL_LL_PORT_NC }
};

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config(uint16_t *name, uint8_t pin_mask, uint8_t config);

/**
  * @brief  Get pin index within a port
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_SIZE-1
  */
static uint8_t hal_ll_gpio_port_pin_index(hal_ll_pin_name_t name) {
    return ( uint8_t )name % PORT_SIZE;
}

/**
  * @brief  Get pins port index within a list of available ports
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_COUNT-1
  */
uint8_t hal_ll_gpio_port_index(hal_ll_pin_name_t name) {
    return ( uint8_t )name / PORT_SIZE;
}

/**
  * @brief  Get pin mask of provided pin within proprietary port
  * @param  name - desired pin
  * @return uint8_t
  */
uint8_t hal_ll_gpio_port_pin_mask(hal_ll_pin_name_t name) {
    return ( 0x01 << ( hal_ll_gpio_port_pin_index(name) ) );
}

/**
  * @brief  Get map address of port register offsets
  * @param  name - desired port
  * @return uint16_t address of first register
  */
uint16_t hal_ll_gpio_port_base_map(hal_ll_port_name_t name) {
    return (hal_ll_gpio_base_t)&_hal_ll_gpio_port_addresses[ name ];
}

/**
  * @brief  Set pin as analog input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_analog_input(uint16_t *port, uint8_t pin_mask) {
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_input(uint16_t *port, uint8_t pin_mask) {
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_port_digital_configure_port(hal_ll_gpio_port_t *port, uint8_t name, bool is_input) {
    // Get appropriate PORT, DDR and PIN register.
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)port->base;

    if (is_input) {
        *(uint8_t *)port_ptr->ddr_reg_addr &= ~(port->mask);
    } else {
        *(uint8_t *)port_ptr->ddr_reg_addr |= port->mask;
    }
}

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_output(uint16_t *port, uint8_t pin) {
    hal_ll_gpio_port_config( port, pin, GPIO_CFG_DIGITAL_OUTPUT );
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config(uint16_t *port, uint8_t pin, uint8_t config) {
    // Get appropriate PORT, DDR and PIN register.
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)port;

    // Get pin mask.
    hal_ll_pin_name_t mask = hal_ll_gpio_port_pin_mask( pin & 0xF );

    if ( GPIO_CFG_DIGITAL_INPUT == config ) {
        *(uint8_t *)port_ptr->ddr_reg_addr &= ~(mask);
    }
    if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
        *(uint8_t *)port_ptr->ddr_reg_addr |= mask;
    }
    if ( GPIO_CFG_ANALOG_INPUT == config ) {
        // Clear PORT value (we are making sure pull-up will be disabled for the analog logic)...
        *(uint8_t *)port_ptr->port_reg_addr &= ~(mask);

        // Set input logic.
        *(uint8_t *)port_ptr->ddr_reg_addr &= ~(mask);
    }
}

// ------------------------------------------------------------------------- END
