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
 * @file  hal_ll_adc.c
 * @brief Low level HAL ADC source file.
 */

#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Uncomment necessary definition to use both Vref+ and Vref- pins for the external voltage reference
 * or only Vref+ or Vref- for positive or negative voltage reference
 */
#define HAL_LL_FULL_VREF_EXTERNAL
// #define HAL_LL_NEG_VREF_EXTERNAL
// #define HAL_LL_POS_VREF_EXTERNAL

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_adc_get_base_struct(_handle) ((hal_ll_adc_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)
#define HAL_LL_MODULE_ADC_1 1
#define HAL_LL_MODULE_ADC_2 2

#define HAL_LL_ADC_CONVERSION_CLOCK            0x1F3F
#define HAL_LL_ADC_START_CONVERSION_BIT        0x0001
#define HAL_LL_ADC_TURN_ON_BIT                 0x000F
#define HAL_LL_ADC_GO_DONE_BIT                 0x0000
#define HAL_LL_ADC_RESOLUTION_BIT              0x000A
#define HAL_LL_ADC_START_CONVERSION_MASK       0x00E0
#define HAL_LL_VREF_EXTERNAL_MASK              0x6000
#define HAL_LL_VREF_MINUS_EXTERNAL_MASK        0x4000
#define HAL_LL_VREF_PLUS_EXTERNAL_MASK         0x2000

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure */
typedef struct
{
    hal_ll_base_addr_t buf0;
    hal_ll_base_addr_t __unused[OFFSET];
    hal_ll_base_addr_t con1;
    hal_ll_base_addr_t con2;
    hal_ll_base_addr_t con3;
    #ifdef MORE_REGS
    #ifndef GB610
    hal_ll_base_addr_t chs123;
    #endif
    hal_ll_base_addr_t chs0;
    #ifndef GB610
    hal_ll_base_addr_t pcfgh;
    hal_ll_base_addr_t pcfgl;
    #endif
    hal_ll_base_addr_t cssh;
    hal_ll_base_addr_t cssl;
    hal_ll_base_addr_t con4;
    #else
    hal_ll_base_addr_t chs0;
    hal_ll_base_addr_t pcfgl;
    hal_ll_base_addr_t cssl;
    #endif
} hal_ll_adc_base_handle_t;

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
    HAL_LL_ADC_ERROR = ( -1 )
} hal_ll_adc_err_t;

/*!< @brief ADC hw specific module values */
typedef struct
{
    hal_ll_pin_name_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
    #ifdef HAL_LL_ADCBUF0_REG_ADDRESS
    { HAL_LL_ADCBUF0_REG_ADDRESS, hal_ll_adc_module_num( HAL_LL_MODULE_ADC_1 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFFFF },
    #endif
    #ifdef HAL_LL_ADC1BUF0_REG_ADDRESS
    { HAL_LL_ADC1BUF0_REG_ADDRESS, hal_ll_adc_module_num( HAL_LL_MODULE_ADC_1 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFFFF },
    #endif
    #ifdef HAL_LL_ADC2BUF0_REG_ADDRESS
    { HAL_LL_ADC2BUF0_REG_ADDRESS, hal_ll_adc_module_num( HAL_LL_MODULE_ADC_2 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFFFF },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFFFF }
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
  * @param[in] *handle_map - ADC module handle map
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pin( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map );

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
static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index );

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
  * @brief  Initialize ADC module.
  * @param *map - - ADC module local map.
  * @return None
  */
static void _hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle( hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id )
{
    uint8_t pin_check_result;
    hal_ll_adc_pin_id index;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_adc_check_pin( pin, &index, handle_map ) ) ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
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

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin )
    {
        hal_ll_adc_map_pin( pin_check_result, &index );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = ( handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_adc_handle = ( handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    uint8_t pin_check_result;
    hal_ll_adc_pin_id index;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_adc_check_pin( hal_ll_adc_hw_specifics_map_local->pin, &index, ( void *)0 ) ) )
    {
        return HAL_LL_ADC_WRONG_PIN;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = ( handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution )
{
    low_level_handle = hal_ll_adc_get_handle;

    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        #ifdef SUPPORTED_ADC_RES_10_BIT
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;
        #endif
        #ifdef SUPPORTED_ADC_RES_12_BIT
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;
        #endif

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input )
{
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;

    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    low_level_handle->init_ll_state = false;

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    hal_ll_adc_base_handle_t *reg_addr = hal_ll_adc_get_base_struct( hal_ll_adc_hw_specifics_map_local->base );

    hal_ll_gpio_port_analog_input( ( hal_ll_gpio_base_t )hal_ll_gpio_port_base_map( ( hal_ll_adc_hw_specifics_map_local->pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4 ),
                                                                                      hal_ll_adc_hw_specifics_map_local->pin );

    write_reg( &reg_addr->chs0, hal_ll_adc_hw_specifics_map_local->channel );

    set_reg_bit( &reg_addr->con1, HAL_LL_ADC_START_CONVERSION_BIT );

    while ( !check_reg_bit( &reg_addr->con1, HAL_LL_ADC_GO_DONE_BIT ) );

    clear_reg_bit( &reg_addr->con1, HAL_LL_ADC_GO_DONE_BIT );

    *readDatabuf = read_reg( &reg_addr->buf0 );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if ( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base ) {

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

static hal_ll_pin_name_t hal_ll_adc_check_pin( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index , hal_ll_adc_handle_register_t *handle_map )
{
    uint8_t pin_index = 0;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    static const uint16_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( pin == hal_ll_analog_in_register_list[pin_index].pin ) {
            hal_ll_module_id = hal_ll_analog_in_register_list[pin_index].module_index;
            index->pin_an[hal_ll_module_id] = pin_index;

            if ( NULL == handle_map[hal_ll_module_id].hal_drv_adc_handle) {
                return hal_ll_module_id;
            } else if ( ADC_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }

    if (index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index ) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin = hal_ll_analog_in_register_list[index->pin_an[module_index]].pin;

    hal_ll_adc_hw_specifics_map[module_index].channel = hal_ll_analog_in_register_list[index->pin_an[module_index]].analog_in_channel_bit;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }
    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void _hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map )
{
    hal_ll_adc_base_handle_t *reg_addr = hal_ll_adc_get_base_struct( map->base );

    write_reg( &reg_addr->con1, ((31 == OFFSET) | (25 == OFFSET)) ? (HAL_LL_ADC_START_CONVERSION_MASK >> 1) : (HAL_LL_ADC_START_CONVERSION_MASK ) );

    clear_reg( &reg_addr->con2 );

    if ( HAL_LL_ADC_RESOLUTION_12_BIT == map->resolution ) {
        set_reg_bit( &reg_addr->con1, HAL_LL_ADC_RESOLUTION_BIT );
    }

    if ( HAL_LL_ADC_VREF_INTERNAL != map->vref_input ) {
        #ifdef HAL_LL_FULL_VREF_EXTERNAL
        set_reg_bits( &reg_addr->con2, HAL_LL_VREF_EXTERNAL_MASK );
        #elif defined HAL_LL_NEG_VREF_EXTERNAL
        set_reg_bits( &reg_addr->con2, HAL_LL_VREF_MINUS_EXTERNAL_MASK );
        #elif defined HAL_LL_POS_VREF_EXTERNAL
        set_reg_bits( &reg_addr->con2, HAL_LL_VREF_PLUS_EXTERNAL_MASK );
        #endif
    }

    write_reg( &reg_addr->con3, HAL_LL_ADC_CONVERSION_CLOCK );
    /**
    * @brief  Initialize two registers for dsPIC33FJ and PIC24HJ MCUs.
    * ADxCON4 allocates 1 word of buffer to each analog input,
    * ADxCSSH as an addition to ADxCSSL helps to skip input scan.
    */
    #ifdef MORE_REGS
    clear_reg( &reg_addr->con4 );
    clear_reg( &reg_addr->cssh );
    #endif

    clear_reg( &reg_addr->cssl );

    set_reg_bit( &reg_addr->con1, HAL_LL_ADC_TURN_ON_BIT );

    set_reg_bits( &reg_addr->chs0, map->channel );
    set_reg_bits( &reg_addr->chs0, map->channel << 8 );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_port_analog_input( ( hal_ll_gpio_base_t )hal_ll_gpio_port_base_map( ( map->pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4 ), map->pin );

    _hal_ll_adc_hw_init( map );

}
// ------------------------------------------------------------------------- END
