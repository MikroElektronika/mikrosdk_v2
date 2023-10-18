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
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base
#define hal_ll_adc_get_base_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_get_handle)->hal_ll_adc_handle))->base
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_adc_get_base_struct(_handle) ((const hal_ll_adc_base_handle_t *)_handle)

/*!< @brief Macros defining register bit location */
#define HAL_LL_ADC_ADCSRA_ADSC_BIT     (6)
#define HAL_LL_ADC_ADCSRA_ADEN         (0x80)
#define HAL_LL_ADC_ADCSRA_ADPS         (0x7)

/*!< @brief Macros defining register specific bit masks */
#define HAL_LL_ADC_ADMUX_MASK          (0xFF)
#define HAL_LL_ADC_ADCSRB_MUX5         (3)

/*!< @brief Macros defining voltage reference related values */
#define HAL_LL_ADC_ADMUX_REFS_INTERNAL (0xC0)
#define HAL_LL_ADC_INTERNAL_VREF_VALUE (2.56)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    uint8_t adcl;
    uint8_t adch;
    uint8_t adcsra;
    uint8_t adcsrb;
    uint8_t admux;
} hal_ll_adc_base_handle_t;

/**
 * @brief ADC low level specific structure.
 *
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    const hal_ll_adc_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_adc_voltage_reference_t vref_input;
    float vref_value;
    uint16_t resolution;
    uint8_t channel;
} hal_ll_adc_hw_specifics_map_t;

/**
 *  Return values
 */
typedef enum {
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = (-1)
} hal_ll_adc_err_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief ADC modules register array */
static const hal_ll_adc_base_handle_t hal_ll_adc_regs[ ADC_MODULE_COUNT + 1 ] = {
    #ifdef ADC_MODULE_0
    { HAL_LL_ADC0_ADCL_REG_ADDRESS, HAL_LL_ADC0_ADCH_REG_ADDRESS, HAL_LL_ADC0_ADCSRA_REG_ADDRESS, HAL_LL_ADC0_ADCSRB_REG_ADDRESS, HAL_LL_ADC0_ADMUX_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT + 1] = {
    #ifdef ADC_MODULE_0
    { &hal_ll_adc_regs[ hal_ll_adc_module_num( ADC_MODULE_0 )], hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_10_BIT, 0xFF },
    #endif

    { &hal_ll_adc_regs[ hal_ll_adc_module_num( ADC_MODULE_COUNT )], HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_10_BIT, 0xFF }
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
static void hal_ll_adc_init(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Check if pins are adequate.
  *
  * Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  *
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[in]  *index  Pointer with ADC pin map index value.
  * @param[in]  *handle_map  ADC low level handle pointer.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins(hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map);

/**
  * @brief  Maps new-found module specific values.
  *
  * Maps pin name, register address and channel.
  *
  * @param[in]  module_index ADC HW module index -- 0,1,2...
  * @param[in]  *index  Pointer with ADC pin map index value
  *
  * @return  None
  */
static void hal_ll_adc_map_pin(uint8_t module_index, uint8_t *index);

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
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle);

/**
  * @brief  Initialize ADC module.
  * @param  *base - ADC module base address.
  * @return None
  */
static void _hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint8_t pin_check_result;
    uint8_t index;

    if ( HAL_LL_PIN_NC == (pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_DEFAULT;
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

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result]->hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc(handle_t *handle) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
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

void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    if( HAL_LL_ADC_VREF_INTERNAL == hal_ll_adc_hw_specifics_map_local->vref_input ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = HAL_LL_ADC_INTERNAL_VREF_VALUE;
    } else {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read(handle_t *handle, uint16_t *readDatabuf) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_handle;

    uint16_t volatile adcl_var = 0, adch_var = 0;

    set_reg_bit( base->adcsra, HAL_LL_ADC_ADCSRA_ADSC_BIT ); // ADSC - ADC Start Conversion bit
    while( check_reg_bit( base->adcsra, HAL_LL_ADC_ADCSRA_ADSC_BIT )); // Wait for conversion to end

    // Documentation: "ADCL must be read first, then ADCH, to ensure that the content of the Data Registers belongs to the same conversion."
    adcl_var = read_reg( base->adcl );
    adch_var = ( read_reg( base->adch )) << 8;
    *readDatabuf = ( adch_var | adcl_var );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close(handle_t *handle) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base->adcl ) {

        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_10_BIT;

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_adc_check_pins(hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map) {
    uint8_t pin_index = 0;
    static const uint16_t adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( _adc_map[pin_index].pin == pin ) {
            *index = pin_index;
            return _adc_map[ pin_index ].module_index;
        }
    }

    return HAL_LL_PIN_NC;
}

static void hal_ll_adc_map_pin(uint8_t module_index, uint8_t *index) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin = _adc_map[*index ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = _adc_map[ *index ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while ( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void _hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    clear_reg_bits( base->admux, HAL_LL_ADC_ADMUX_MASK );
    write_reg( base->adcsra, HAL_LL_ADC_ADCSRA_ADEN | HAL_LL_ADC_ADCSRA_ADPS );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    _hal_ll_adc_hw_init( map );
    if( HAL_LL_ADC_VREF_INTERNAL == map->vref_input )
        set_reg_bits( base->admux, HAL_LL_ADC_ADMUX_REFS_INTERNAL );
    #ifdef HAS_ADC_MUX5_BIT
    if( 8 > map->channel ) {
        set_reg_bits( base->admux, map->channel );
    } else {
        /*
         * When ADC channel number is higher than 7 (0b1000 - 0b1111), the lower 3 bits
         * are written to ADMUX[MUX2:0] and the highest bit is written to ADCSRB[MUX5].
         */
        set_reg_bits( base->admux, map->channel & 0x7 );
        set_reg_bit( base->adcsrb, HAL_LL_ADC_ADCSRB_MUX5 );
    }
    #else 
        set_reg_bits( base->admux, map->channel );
    #endif
}

// ------------------------------------------------------------------------- END
