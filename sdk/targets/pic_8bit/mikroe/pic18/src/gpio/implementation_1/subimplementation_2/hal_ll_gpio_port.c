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
#define HAL_LL_PCFG_BITS_SET_AN        0xF1
#define HAL_LL_PCFG_BITS_SET_D         0xF0
#define HAL_LL_PCFG_BITS_SET_AN_CH_15  0xF0
#define HAL_LL_PCFG_BITS_MASK          0x0F
#define HAL_LL_PCFG_BITS_SET_D_CH_15   0xEF
#define HAL_LL_ANALOG_IN_CH_15         0x0F
#define HAL_LL_ALTERNATE_REGISTER_SET  0x04
#define HAL_LL_WDTCON_REG_ADDRESS      0x0FC0u
#define HAL_LL_PORT_TO_PIN             0x04
#define HAL_LL_CHECK_PIN_MASK          1
#define PCFG_BITS_FOUND                1
#define PCFG_BITS_NOT_FOUND            2
#define PCFG_BITS_NOT_CHECKED          0

// -------------------------------------------------------------- PRIVATE TYPES

/**
 *  Defines used in source
 */

/*!< @brief GPIO PORT array */
static hal_ll_gpio_base_handle_t _hal_ll_gpio_port_addresses[ PORT_COUNT + 1 ] =
{
    #ifdef __PORT_A_CN
    { PORTA_BASE_ADDRESS, LATA_BASE_ADDRESS, TRISA_BASE_ADDRESS },
    #endif
    #ifdef __PORT_B_CN
    { PORTB_BASE_ADDRESS, LATB_BASE_ADDRESS, TRISB_BASE_ADDRESS },
    #endif
    #ifdef __PORT_C_CN
    { PORTC_BASE_ADDRESS, LATC_BASE_ADDRESS, TRISC_BASE_ADDRESS },
    #endif
    #ifdef __PORT_D_CN
    { PORTD_BASE_ADDRESS, LATD_BASE_ADDRESS, TRISD_BASE_ADDRESS },
    #endif
    #ifdef __PORT_E_CN
    { PORTE_BASE_ADDRESS, LATE_BASE_ADDRESS, TRISE_BASE_ADDRESS },
    #endif
    #ifdef __PORT_F_CN
    { PORTF_BASE_ADDRESS, LATF_BASE_ADDRESS, TRISF_BASE_ADDRESS },
    #endif
    #ifdef __PORT_G_CN
    { PORTG_BASE_ADDRESS, LATG_BASE_ADDRESS, TRISG_BASE_ADDRESS },
    #endif
    #ifdef __PORT_H_CN
    { PORTH_BASE_ADDRESS, LATH_BASE_ADDRESS, TRISH_BASE_ADDRESS },
    #endif
    #ifdef __PORT_J_CN
    { PORTJ_BASE_ADDRESS, LATJ_BASE_ADDRESS, TRISJ_BASE_ADDRESS },
    #endif
    #ifdef __PORT_K_CN
    { PORTK_BASE_ADDRESS, LATK_BASE_ADDRESS, TRISK_BASE_ADDRESS },
    #endif
    #ifdef __PORT_L_CN
    { PORTL_BASE_ADDRESS, LATL_BASE_ADDRESS, TRISL_BASE_ADDRESS },
    #endif
    { HAL_LL_PORT_NC, HAL_LL_PORT_NC, HAL_LL_PORT_NC }
};

/**
  * @brief  Configure pin that has analog function
  * @param  pin        - desired pin
  *         is_digital - pin configuration( true = digital, false = analog )
  * @return none
  */
static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital );

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config( uint16_t *name, uint8_t pin_mask, uint8_t config );

/**
  * @brief  Get pin index within a port
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_SIZE-1
  */
static uint8_t hal_ll_gpio_port_pin_index( hal_ll_pin_name_t name )
{
    return ( uint8_t )name % PORT_SIZE;
}
/**
  * @brief  Get pins port index within a list of available ports
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_COUNT-1
  */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name )
{
    return ( uint8_t )name / PORT_SIZE;
}

/**
  * @brief  Get pin mask of provided pin within proprietery port
  * @param  name - desired pin
  * @return uint8_t
  */
uint8_t hal_ll_gpio_port_pin_mask( hal_ll_pin_name_t name )
{
    return ( 0x01 << hal_ll_gpio_port_pin_index( name ) );
}

/**
  * @brief  Get map address of port register offsets
  * @param  name - desired port
  * @return uint16_t address of first regsiter
  */
uint16_t hal_ll_gpio_port_base_map( hal_ll_port_name_t name )
{
    return (uint16_t)&_hal_ll_gpio_port_addresses[ name ];
}

/**
  * @brief  Set pin as analog input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_analog_input( uint16_t *port, uint8_t pin_mask )
{
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_input( uint16_t *port, uint8_t pin_mask )
{
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_port_digital_configure_port( hal_ll_gpio_port_t *port, uint8_t name, bool is_input )
{
    uint8_t adc_map_size;
    uint8_t lowest_chn = 255;
    uint8_t pin_index;
    uint16_t pcfg_register_addr;
    uint8_t count;
    uint8_t pin;
    uint8_t pcfg_found = PCFG_BITS_NOT_CHECKED;

    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)port->base;

    if ( is_input ) {
        *(uint8_t *)port_ptr->tris_reg_addr |= port->mask;
    } else {
        *(uint8_t *)port_ptr->tris_reg_addr &= ~(port->mask);
    }

    adc_map_size =  ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    for (count=0; count < PORT_SIZE; count++) {
        if ((port->mask >> count) & HAL_LL_CHECK_PIN_MASK) {
            pin = (name << HAL_LL_PORT_TO_PIN) + count;
            if (pcfg_found != PCFG_BITS_NOT_FOUND) {
                for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
                    if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
                        if ( hal_ll_analog_in_register_list[ pin_index ].multiple_pcfg_sel ) {
                            pcfg_found = PCFG_BITS_FOUND;
                            if( hal_ll_analog_in_register_list[ pin_index ].channel < lowest_chn ){
                                lowest_chn = hal_ll_analog_in_register_list[ pin_index ].channel;
                                pcfg_register_addr = hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr;
                            }
                        } else {
                            pcfg_found = PCFG_BITS_NOT_FOUND;
                            hal_ll_gpio_port_configure_analog_pin(pin, true);
                        }
                        break;
                    }
                }
            } else
                hal_ll_gpio_port_configure_analog_pin(pin, true);
        }
    }
    if ( pcfg_found == PCFG_BITS_FOUND ){
        if ( lowest_chn == HAL_LL_ANALOG_IN_CH_15 ){
            clear_reg_bits( pcfg_register_addr, HAL_LL_PCFG_BITS_MASK );
            set_reg_bits(pcfg_register_addr, ( ~lowest_chn - HAL_LL_PCFG_BITS_SET_D_CH_15 ) );
        } else {
            clear_reg_bits( pcfg_register_addr, HAL_LL_PCFG_BITS_MASK );
            set_reg_bits(pcfg_register_addr, ( ~lowest_chn - HAL_LL_PCFG_BITS_SET_D ) );
        }
    }
}

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_output( uint16_t *port, uint8_t pin )
{
    hal_ll_gpio_port_config( port, pin, GPIO_CFG_DIGITAL_OUTPUT );
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config( uint16_t *port, uint8_t pin, uint8_t config )
{
    hal_ll_pin_name_t mask= hal_ll_gpio_port_pin_mask(pin & 0x0F);

    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)port;

    set_reg_bit( HAL_LL_WDTCON_REG_ADDRESS, HAL_LL_ALTERNATE_REGISTER_SET );

    if( config == GPIO_CFG_DIGITAL_OUTPUT ) {
        *(uint8_t *)port_ptr->tris_reg_addr &= ~mask;
        hal_ll_gpio_port_configure_analog_pin(pin, true);
        clear_reg_bit( HAL_LL_WDTCON_REG_ADDRESS, HAL_LL_ALTERNATE_REGISTER_SET );
        return;
    }
    if ( config == GPIO_CFG_DIGITAL_INPUT ) {
        *(uint8_t *)port_ptr->tris_reg_addr |= mask;
        hal_ll_gpio_port_configure_analog_pin(pin, true);
        clear_reg_bit( HAL_LL_WDTCON_REG_ADDRESS, HAL_LL_ALTERNATE_REGISTER_SET );
        return;
    }
    if ( config == GPIO_CFG_ANALOG_INPUT ) {
        *(uint8_t *)port_ptr->tris_reg_addr |= mask;
        hal_ll_gpio_port_configure_analog_pin(pin, false);
        clear_reg_bit( HAL_LL_WDTCON_REG_ADDRESS, HAL_LL_ALTERNATE_REGISTER_SET );
        return;
    }
}

static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital )
{
    static uint8_t      adc_map_size;
    static uint8_t      local;
    static uint8_t      pin_index = 0;

    /*
     *  ADSHR_NOTE
     *  Specific PIC chips have shared SFR addresses.
     *  Setting the ADSHR bit in WDTCON register effectively changes the
     *  active registers.
     *  Page number 82 -- http://ww1.microchip.com/downloads/en/devicedoc/39775b.pdf
     */

    adc_map_size =  ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
            #ifdef __hal_ll_shared_sfrs__
            // Check ADSHR_NOTE for more info
            set_reg_bit( HAL_LL_WDTCON_ADDRESS, HAL_LL_WDTCON_ADSHR_BIT );
            #endif
            if ( !(hal_ll_analog_in_register_list[ pin_index ].multiple_pcfg_sel) ){
                if (is_digital)
                    set_reg_bit(hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr , ( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit ) );
                else
                    clear_reg_bit(hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr , ( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit ) );
            }
            else {
                if ( hal_ll_analog_in_register_list[ pin_index ].channel == HAL_LL_ANALOG_IN_CH_15 ){
                    if (is_digital)
                        local = HAL_LL_PCFG_BITS_SET_D_CH_15;
                    else
                        local = HAL_LL_PCFG_BITS_SET_AN_CH_15;
                }
                else{
                    if(is_digital)
                        local = HAL_LL_PCFG_BITS_SET_D;
                    else
                        local = HAL_LL_PCFG_BITS_SET_AN;
                }
                clear_reg_bits( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr, HAL_LL_PCFG_BITS_MASK );
                set_reg_bits(hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr, ( ~hal_ll_analog_in_register_list[ pin_index ].channel - local ) );
            }
            #ifdef __hal_ll_shared_sfrs__
            // Check ADSHR_NOTE for more info
            clear_reg_bit( HAL_LL_WDTCON_ADDRESS, HAL_LL_WDTCON_ADSHR_BIT );
            #endif
            break;
        }
    }
}
// ------------------------------------------------------------------------- END
