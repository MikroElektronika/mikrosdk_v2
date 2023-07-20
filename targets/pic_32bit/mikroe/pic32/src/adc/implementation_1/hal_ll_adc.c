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
/*!< @brief Helper macro for getting hal_ll_module_state address. */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle ((hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle. */
#define hal_ll_adc_get_base_from_hal_handle (((hal_ll_adc_hw_specifics_map_t *)(low_level_handle->hal_ll_adc_handle))->ch_enable)
/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/**
 * @defgroup AD1CON1_bits
 * @brief AD1CON1 configuration bits
 * @{
 */
#define HAL_LL_AD1CON1_INTERNAL_COUNTER_END_BITS                      ( ( uint32_t ) 0x00E0 )
#define HAL_LL_AD1CON1_ON_BIT                                         ( ( uint8_t ) 15 )
#define HAL_LL_AD1CON1_DONE_BIT                                       ( ( uint8_t ) 0 )
#define HAL_LL_AD1CON1_SAMP_BIT                                       ( ( uint8_t ) 1 )
/** @}*/


/**
 * @defgroup AD1CON2_bits
 * @brief AD1CON2 configuration bits
 * @{
 */
#define HAL_LL_AD1CON2_VCFG_EXTERNAL_BITS                             ( ( uint32_t ) 0x6000 )
#define HAL_LL_AD1CON2_VCFG_INTERNAL_CLEAR_MASK                       ( ( uint32_t ) 0xE000 )
#define HAL_LL_AD1CON2_VCFG_VREFH_INTERNAL_VREFL_EXTERNAL_BITS        ( ( uint32_t ) 0x4000 )
#define HAL_LL_AD1CON2_VCFG_VREFH_EXTERNAL_VREFL_INTERNAL_BITS        ( ( uint32_t ) 0x2000 )
#define HAL_LL_AD1CON2_SKIP_INPUT_SCAN_BITS                           ( ( uint32_t ) 0x0000 )
/** @}*/


/**
 * @defgroup AD1CON3_bits
 * @brief AD1CON3 configuration bits
 * @{
 */
#define HAL_LL_AD1CON3_SAMPLE_TIME_31_CYCLE_BITS                      ( ( uint32_t ) 0x1FFF )
/** @}*/

/**
 * @brief Peripheral Module Disable bit used for enabling clock for ADC module.
 */
#define HAL_LL_PMD1_ADCMD_BIT                                         ( ( uint8_t ) 0 )


// -------------------------------------------------------------- PRIVATE TYPES
/**
 *  @brief Return values
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

// ---------------------------------------------------------- PRIVATE VARIABLES

/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/**
 * @brief Array of maps holding information for configuring hardware.
 * @details Each module has its hw_specific_map to track it's current state
 * since PIC32mx has only one module then only one map + terminating map is needed,
 * hal_ll_module_state array holds pointers to elements in this list.
 */
static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
    #ifdef ADC_MODULE
    {HAL_LL_AD1CHS_ADDRESS, hal_ll_adc_module_num(ADC_MODULE), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_10_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF}
};

/*!< @brief Global handle variables used in functions, declared global for the puroses of memory efficiency. */
static volatile hal_ll_adc_handle_register_t  *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local; // pointer to element in hw_specific_map;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Initialize ADC module @p map.
  * @details from @p map, uses pin information to set it as analog & sets
  * @param[in]  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None.
  */
static void _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Check if pins are adequate.
  * @details Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[out]  index - index in hal_ll_analog_in_register_list configuration registers
  * & ADC module information for that specific @p pin
  * @return hal_ll_pin_name_t Module index based on pins.
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_adc_check_pins( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 * @details Maps pin name, register address and channel from analog register list to module in hardware specific map.
 * @param[in]  module_index ADC HW module index -- 0,1,2... Index in hal_ll_adc_hw_specifics_map,
 * destination of copying.
 * @param[in]  index  Pointer with ADC pin map index value. Index in hal_ll_analog_in_register_list
 * source of copying information
 * @return  None
 */
static void _hal_ll_adc_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Get local hardware specific map.
  * @details Checks handle value and returns address of adequate
  * hal_ll_adc_hw_specifics_map array element.
  * @param[in]  handle - Object specific context handler.
  * @return address of a member in hal_ll_adc_hw_specifics_map, either a correct member
  * or an 'error' terminating member in map.
  */
static hal_ll_adc_hw_specifics_map_t* _hal_ll_get_specifics( handle_t *handle );

/**
 * @brief  Initialize hardware ADC module.
 * @details Since PIC32MX has only one ADC module only
 * reference voltage and input chanel are neccesaray for hardware initialization
 * @param vref Voltage reference used for AD1CON2.
 * @param channel Channel/pin used for input to ADC, set in AD1CON1.
 * @return None
 */
static void _hal_ll_adc_hw_init( uint32_t channel, hal_ll_adc_voltage_reference_t vref );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_adc_register_handle(
    hal_ll_pin_name_t               pin,
    hal_ll_adc_voltage_reference_t  vref_input,
    hal_ll_adc_resolution_t         resolution,
    hal_ll_adc_handle_register_t    *handle_map,
    uint8_t                         *hal_module_id
) {
    uint8_t index;
    hal_ll_pin_name_t pin_check_result = _hal_ll_adc_check_pins( pin, &index, handle_map );

    // see if requested pin supports analog input
    if ( HAL_LL_PIN_NC == pin_check_result ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    // pic32mx has only 10 bit ADC resolution
    if ( HAL_LL_ADC_RESOLUTION_10_BIT == resolution ) {
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
    } else {
        return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    // set desired state of hardware to hardwer specific map
    // switch only validates if the vref_input variable is in the enum range
    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
        case HAL_LL_ADC_VREF_INTERNAL:
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = vref_input;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
     }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin ) {
        // copy pin information from 'analog in' list to hw specific map element at 'index' index
        _hal_ll_adc_map_pin( pin_check_result, index );
        // after the hw specific map has been mapped, mark it as uninitialized so next time it's used
        // it will trigger hal_ll_module_configure_adc to actualy initialize hardware
        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    // set register for configuring analog pin
    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;

    handle_map[pin_check_result]->hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics(handle);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    // initialize adc registers
    _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics(handle); // this function will update low_level_handle

    if ( HAL_LL_ADC_RESOLUTION_10_BIT == resolution ) {
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
    } else {
        // in case of bad resolution function will fail leaving low_level handle marked as uninitialized
        // trigerring configure action from upper layer on next read
        low_level_handle->init_ll_state = false;
        return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    // reinitialize the hardware since resolution is changed
    _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    // hardware is reinitialized, make sure low_level_handle reflects that
    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics(handle); // this function will update low_level_handle

    // validating if the vref input is inside the enum range
    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
        case HAL_LL_ADC_VREF_INTERNAL:
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map_local->vref_input = vref_input;
            break;

        default:
            // in case of bad vref, function will fail leaving low_level_handle marked as uninitialized
            // trigerring configure action from upper layer on next read
            low_level_handle->init_ll_state = false;
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    // reinitialize the hardware since vref input has changed
    _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    // mark handle to hardware as intitialized
    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *read_buff ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    // initialize sampling
    set_reg_bit( HAL_LL_AD1CON1_ADDRESS,  HAL_LL_AD1CON1_SAMP_BIT );
    // wait until conversion is done
    while ( !check_reg_bit( HAL_LL_AD1CON1_ADDRESS, HAL_LL_AD1CON1_DONE_BIT ) ) {
        continue;
    }
    // read data
    *read_buff = *( uint16_t *) HAL_LL_ADC1BUF0_ADDRESS;
    // stop sampling
    clear_reg_bit( HAL_LL_AD1CON1_ADDRESS,  HAL_LL_AD1CON1_SAMP_BIT );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    if ( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->ch_enable ) {
        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;

        #if defined( PIC32MX1xx ) || defined( PIC32MX2xx ) || defined( PIC32MX530xx ) || defined( PIC32MX550xx ) || defined( PIC32MX570xx )
        set_reg_bit( HAL_LL_PMD1_ADDRESS, HAL_LL_PMD1_ADCMD_BIT );
        #endif

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t _hal_ll_adc_check_pins( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map ) {
    static uint8_t  pin_index = 0;
    static const uint16_t adc_map_size = sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }
    // search through hal_ll_analog_in_register_list for elemenet with 'pin' member
    // matching 'pin' function argument
    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
            *index = pin_index;
            // will return module 0 since all 16 analog pins belong to a single module
            return hal_ll_analog_in_register_list[ pin_index ].module_index;
        }
    }

    return HAL_LL_PIN_NC;
}

static void _hal_ll_adc_map_pin( uint8_t module_index, uint8_t index ) {
    // simple copying of elements
    hal_ll_adc_hw_specifics_map[ module_index ].pin       = hal_ll_analog_in_register_list[ index ].pin;
    hal_ll_adc_hw_specifics_map[ module_index ].ch_enable = hal_ll_analog_in_register_list[ index ].analog_in_register_addr;
    hal_ll_adc_hw_specifics_map[ module_index ].channel   = hal_ll_analog_in_register_list[ index ].channel;
}

static hal_ll_adc_hw_specifics_map_t *_hal_ll_get_specifics( handle_t* handle ) {
    low_level_handle = hal_ll_adc_get_handle;
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / sizeof( hal_ll_adc_handle_register_t );
    static const uint8_t hal_ll_module_error = hal_ll_module_count;

    // search through hal_ll_adc_hw_specific_map
    while ( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].ch_enable ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void _hal_ll_adc_hw_init(uint32_t channel, hal_ll_adc_voltage_reference_t vref) {
    // intenal counter ends conversion, automatic conversion
    // since whole register by reset is 0, output form is 16bit unsigned integer arranged
    // in a way such that no shifting is needed
    write_reg( HAL_LL_AD1CON1_ADDRESS, HAL_LL_AD1CON1_INTERNAL_COUNTER_END_BITS );
    asm nop;

    // select channel for sampling
    write_reg( HAL_LL_AD1CHS_ADDRESS, ((uint32_t)hal_ll_adc_hw_specifics_map_local->channel) << 16);

    // do not scan inputs, buffer configure as one 16-word buffer, etc.
    write_reg( HAL_LL_AD1CON2_ADDRESS, HAL_LL_AD1CON2_SKIP_INPUT_SCAN_BITS );

    // set referenca voltage
    switch ( vref )
    {
        case HAL_LL_ADC_VREF_DEFAULT:
        case HAL_LL_ADC_VREF_EXTERNAL:
            set_reg_bits( HAL_LL_AD1CON2_ADDRESS, HAL_LL_AD1CON2_VCFG_VREFH_EXTERNAL_VREFL_INTERNAL_BITS );
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            clear_reg_bits( HAL_LL_AD1CON2_ADDRESS, HAL_LL_AD1CON2_VCFG_INTERNAL_CLEAR_MASK );
            break;

        default:
            // unreachable
            break;
    }

    // sample time == 31 Tad. Tad = 512*Tpb
    write_reg( HAL_LL_AD1CON3_ADDRESS, HAL_LL_AD1CON3_SAMPLE_TIME_31_CYCLE_BITS );
    // all analog channels omitted from input scan
    clear_reg( HAL_LL_AD1CSSL_ADDRESS );
    // turn on ADC
    set_reg_bit( HAL_LL_AD1CON1_ADDRESS, HAL_LL_AD1CON1_ON_BIT );
}

static void _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    #if defined( PIC32MX1xx ) || defined( PIC32MX2xx ) || defined( PIC32MX530xx ) || defined( PIC32MX550xx ) || defined( PIC32MX570xx )
    clear_reg_bit( HAL_LL_PMD1_ADDRESS, HAL_LL_PMD1_ADCMD_BIT );
    #endif

    // set AD1PCFG & TRIS registers to appropriate state
    hal_ll_gpio_port_analog_input(
        hal_ll_gpio_port_base_map( hal_ll_gpio_port_index( map->pin ) ),
        map->pin
    );

    // configure AD1CON1, AD1CON2, AD1CON3, AD1CSSL registers
    _hal_ll_adc_hw_init( map->channel, map->vref_input );
}

// ------------------------------------------------------------------------- END
