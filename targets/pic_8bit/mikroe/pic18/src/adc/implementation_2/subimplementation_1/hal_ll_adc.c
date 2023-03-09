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
 * @file  hal_ll_adc.c
 * @brief Low level HAL ADC source file.
 */

#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->ch_enable

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

#define HAL_LL_ADC_CCR_OFFSET                  0x304

#define HAL_LL_ADC_AUTO_CONVERT_MODE           0x70

#define HAL_LL_ADC_RESULT_FORMAT_BIT           0x07
#define HAL_LL_ADC_CONVERSION_CLOCK            0x0F
#define HAL_LL_ADC_CLEAR_CHANNEL_BITS          0x7C
#define HAL_LL_ADC_START_CONVERSION_BIT        0x01
#define HAL_LL_ADC_TURN_ON_BIT                 0x00
#define HAL_LL_ADC_MODULE_ENABLE_BIT           0x00

#define HAL_LL_ADC_RESULT_SIGN_BIT             0x8000U

#define HAL_LL_ADC_DEFAULT_BASE_ADDRESS        0xFF

#define HAL_LL_ADC_VREF_MASK                   0x38 // voltage reference mask
#define HAL_LL_ADC_VREF_INTERN_MASK            0x30

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< Abbreviations used in source. */
typedef uint16_t hal_ll_adc_base_t;

/**
 *  Return values
 */
typedef enum
{
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = (-1)
} hal_ll_adc_err_t;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
    #ifdef ADC_MODULE
    {HAL_LL_ADCON0_ADDRESS, hal_ll_adc_module_num(ADC_MODULE), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize ADC module.
  * @param  *map - ADC module local map.
  * @return None
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Check if pins are adequate.
  *
  * Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  *
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[in]  *index - ADC map index value.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin name and channel values for ADC pin
 *
 * @param[in]  module_index ADC HW module index -- 0,1,2...
 * @param[in]  *index  ADC map index value
 *
 * @return  None
 */
static void hal_ll_adc_map_pin( uint8_t module_index, uint8_t *index );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_adc_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_adc_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Enable ADC module gate clock.
  * @param  *base - ADC module base address.
  * @return None
  */
static void _hal_ll_adc_enable_clock( hal_ll_base_addr_t *base );

/**
  * @brief  Initialize ADC module.
  * @param  *base - ADC module base address.
  * @param  resolution - ADC module resolution.
  * @return None
  */
static void _hal_ll_adc_hw_init( uint32_t resolution, uint32_t vref );

/**
  * @brief  Enable ADC module gate clock.
  * @param  *base - ADC module base address.
  * @return None
  */
static void _hal_adc_enable_module( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id)
{
    uint8_t pin_check_result;
    uint8_t index;

    if ( (pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution )
    {
    case HAL_LL_ADC_RESOLUTION_12_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
        break;
    default:
        return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
            break;
        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin )
    {
        hal_ll_adc_map_pin( pin_check_result, &index );

        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;

    handle_map[pin_check_result]->hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    uint8_t pin_check_result;
    uint8_t index;

    if ( (pin_check_result = hal_ll_adc_check_pins( hal_ll_adc_hw_specifics_map_local->pin, &index, (void *)0 ) ) == HAL_LL_PIN_NC )
    {
        return HAL_LL_ADC_WRONG_PIN;
    };

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution)
{
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input)
{
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;

    low_level_handle->init_ll_state = false;

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
            break;
        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value)
{
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    clear_reg_bits( HAL_LL_ADCON0_ADDRESS, HAL_LL_ADC_CLEAR_CHANNEL_BITS );

    set_reg_bits( HAL_LL_ADCON0_ADDRESS, ( hal_ll_adc_hw_specifics_map_local->channel << 2 ) );

    Delay_22us();

    set_reg_bit( HAL_LL_ADCON0_ADDRESS, HAL_LL_ADC_START_CONVERSION_BIT );

    while ( ( check_reg_bit( HAL_LL_ADCON0_ADDRESS, HAL_LL_ADC_START_CONVERSION_BIT ) ) );

    *readDatabuf = *(uint16_t*)HAL_LL_ADRESL_ADDRESS;

    if ( *readDatabuf & HAL_LL_ADC_RESULT_SIGN_BIT )
        *readDatabuf = 0;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if ( hal_ll_adc_hw_specifics_map_local->ch_enable != HAL_LL_MODULE_ERROR ) {

        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map )
{
    uint8_t pin_index = 0;
    static const uint16_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
            *index = pin_index;
            return hal_ll_analog_in_register_list[ pin_index ].module_index;
        }
    }

    return HAL_LL_PIN_NC;
}

static void hal_ll_adc_map_pin( uint8_t module_index, uint8_t *index ) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin = hal_ll_analog_in_register_list[*index ].pin;
    hal_ll_adc_hw_specifics_map[module_index].ch_enable = hal_ll_analog_in_register_list[ *index ].analog_in_register_addr;
    hal_ll_adc_hw_specifics_map[module_index].channel = hal_ll_analog_in_register_list[ *index ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while ( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].ch_enable) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }

    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void _hal_ll_adc_enable_module( void )
{
    #ifdef HAL_LL_ADC_PMD_ADDRESS
    clear_reg_bit( HAL_LL_ADC_PMD_ADDRESS, HAL_LL_ADCMD_BIT );
    #endif
}

static void _hal_ll_adc_hw_init( uint32_t vref )
{
    clear_reg( HAL_LL_ADCON0_ADDRESS );

    if( vref == HAL_LL_ADC_VREF_EXTERNAL)
        clear_reg_bits( HAL_LL_ADCON1_ADDRESS, ( HAL_LL_ADC_VREF_MASK ) );
    else
        {
        set_reg_bits( HAL_LL_ADCON1_ADDRESS, HAL_LL_ADC_VREF_INTERN_MASK );
        #ifdef HAL_LL_VREFCON0_ADDRESS
        set_reg_bits( HAL_LL_VREFCON0_ADDRESS, HAL_LL_VREFCON0_4096_MASK );
        while ( ( check_reg_bit( HAL_LL_VREFCON0_ADDRESS, HAL_LL_VREFCON0_READY_BIT ) ) );
        #endif
        }
    set_reg_bits( HAL_LL_ADCON2_ADDRESS, HAL_LL_ADC_CONVERSION_CLOCK );

    set_reg_bit( HAL_LL_ADCON2_ADDRESS, HAL_LL_ADC_RESULT_FORMAT_BIT );

    set_reg_bit( HAL_LL_ADCON0_ADDRESS, HAL_LL_ADC_TURN_ON_BIT );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_port_analog_input( (hal_ll_gpio_base_t)hal_ll_gpio_port_base_map((map->pin & HAL_LL_NIBBLE_HIGH_8BIT) >> 4), map->pin );

    _hal_ll_adc_enable_module();

    _hal_ll_adc_hw_init(map->vref_input);

}
// ------------------------------------------------------------------------- END
