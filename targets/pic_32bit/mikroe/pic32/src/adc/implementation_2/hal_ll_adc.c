/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
#define hal_ll_adc_get_module_state_address ( ( hal_ll_adc_handle_register_t * ) *handle )
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle ( ( hal_ll_adc_handle_register_t * ) hal_ll_adc_get_module_state_address->hal_ll_adc_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle. */
#define hal_ll_adc_get_base_from_hal_handle ( ( ( hal_ll_adc_hw_specifics_map_t * ) ( low_level_handle->hal_ll_adc_handle ) )->ch_enable )
/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num( _module_num ) ( _module_num - 1 )

/*!< @brief Utility macro for copying entire register. */
#define copy_reg( dest, source ) ( selected_reg( dest ) = selected_reg( source ) )

/**
 * @defgroup ADCCON1_bits
 * @brief ADCCON1 configuration bits for resolution, enabling global software tringering,
 * and enabling the ADC module.
 * @{
 */
#define HAL_LL_ADCCON1_SELRES_12_BIT_BITS    ( ( uint32_t ) ( 3UL << 21 ) )
#define HAL_LL_ADCCON1_SELRES_10_BIT_BITS    ( ( uint32_t ) ( 2UL << 21 ) )
#define HAL_LL_ADCCON1_SELRES_8_BIT_BITS     ( ( uint32_t ) ( 1UL << 21 ) )
#define HAL_LL_ADCCON1_SELRES_6_BIT_BITS     ( ( uint32_t ) ( 0UL << 21 ) )
#define HAL_LL_ADCCON1_GSWTRG_BITS           ( ( uint32_t ) ( 0x1 ) )
#define HAL_LL_ADCCON1_ON_BIT                ( ( uint8_t ) 15 )
/** @}*/

/**
 * @defgroup ADCCON2_bits
 * @brief Macros for configuring ADCCON2 register.
 * @{
 */
#define HAL_LL_ADCCON2_SAMC_BITS( x )        ( ( uint32_t ) ( (x) & 0x3ff ) )
#define HAL_LL_ADCCON2_ADCDIV_BITS( x )      ( ( uint32_t ) ( (x) & 0x7f  ) )
#define HAL_LL_ADCCON2_BGVRRDY_BIT           ( ( uint8_t ) 31 )
#define HAL_LL_ADCCON2_REFFLT_BIT            ( ( uint8_t ) 30 )
/** @}*/

/**
 * @defgroup ADCCON3_bits
 * @brief Macros for configuring ADCCON3 register.
 * @{
 */
#define HAL_LL_ADCCON3_RQCNVRT_BIT           ( ( uint8_t ) 8 )
#define HAL_LL_ADCCON3_DIGEN_ALL_BITS        ( ( uint32_t ) 0xff0000 )
#define HAL_LL_ADCCON3_ADCSEL_TCLK_BITS      ( ( uint32_t ) ( 0ul << 22 ) )
#define HAL_LL_ADCCON3_ADCSEL_REFCLK3_BITS   ( ( uint32_t ) ( 1ul << 22 ) )
#define HAL_LL_ADCCON3_ADCSEL_FRCOSC_BITS    ( ( uint32_t ) ( 2ul << 22 ) )
#define HAL_LL_ADCCON3_ADCSEL_PBCLK_BITS     ( ( uint32_t ) ( 3ul << 22 ) )
#define HAL_LL_ADCCON3_VREFSEL_EXTERNAL_BITS ( ( uint32_t ) ( 3uL << 13 ) )
#define HAL_LL_ADCCON3_VREFSEL_INTERNAL_BITS ( ( uint32_t ) ( 0uL << 13 ) )
#define HAL_LL_ADCCON3_CONCLKDIV_BITS( x )   ( ( uint32_t ) ( (x) & 0x3f ) )
#define HAL_LL_ADCCON3_ADINSEL_BITS( x )     ( ( uint32_t ) ( (x) & 0x3f ) )
#define HAL_LL_ADCCON3_ADINSEL_BITS_ALL      ( ( uint32_t ) 0x3f )
/** @}*/

/**
 * @defgroup ADCTIME_bits
 * @brief Macros for selecting ADC resolution, divisor, and sample time
 * @{
 */
#define HAL_LL_ADCTIME_SELRES_12_BIT_BITS    ( ( uint32_t ) ( 3ul << 24 ) )
#define HAL_LL_ADCTIME_SELRES_10_BIT_BITS    ( ( uint32_t ) ( 2ul << 24 ) )
#define HAL_LL_ADCTIME_SELRES_8_BIT_BITS     ( ( uint32_t ) ( 1ul << 24 ) )
#define HAL_LL_ADCTIME_SELRES_6_BIT_BITS     ( ( uint32_t ) ( 0ul << 24 ) )
#define HAL_LL_ADCTIME_ADCDIV_BITS( x )      ( ( uint32_t ) ( (x) & 0x7f  ) )
#define HAL_LL_ADCTIME_SAMC_BITS( x )        ( ( uint32_t ) ( (x) & 0x3ff ) )
/** @}*/

/**
 * @defgroup ADCANCON_bits
 * @brief Macros for enabling ADC module & checking if ADC module is ready.
 * @{
 */
#define HAL_LL_ADCANCON_ANEN0_BIT            ( ( uint8_t ) 0  )
#define HAL_LL_ADCANCON_ANEN1_BIT            ( ( uint8_t ) 1  )
#define HAL_LL_ADCANCON_ANEN2_BIT            ( ( uint8_t ) 2  )
#define HAL_LL_ADCANCON_ANEN3_BIT            ( ( uint8_t ) 3  )
#define HAL_LL_ADCANCON_ANEN4_BIT            ( ( uint8_t ) 4  )
#define HAL_LL_ADCANCON_ANEN7_BIT            ( ( uint8_t ) 7  )
#define HAL_LL_ADCANCON_ANEN_ALL_BITS        ( ( uint32_t ) 0x9f )
#define HAL_LL_ADCANCON_WKRDY0_BIT           ( ( uint8_t ) 8 )
#define HAL_LL_ADCANCON_WKRDY1_BIT           ( ( uint8_t ) 9 )
#define HAL_LL_ADCANCON_WKRDY2_BIT           ( ( uint8_t ) 10 )
#define HAL_LL_ADCANCON_WKRDY3_BIT           ( ( uint8_t ) 11 )
#define HAL_LL_ADCANCON_WKRDY4_BIT           ( ( uint8_t ) 12 )
#define HAL_LL_ADCANCON_WKRDY7_BIT           ( ( uint8_t ) 15 )
#define HAL_LL_ADCANCON_WKRDY_ALL_BITS       ( ( uint32_t ) 0x9f00 )
#define HAL_LL_ADCANCON_WKUPCLKCNT_BITS( x ) ( ( ( ( uint32_t ) (x) & 0b111 ) << 24 ) )
/** @}*/

/**
 * @brief ADCTRG mask for enabling software trigger for all ADC modules.
 */
#define HAL_LL_ADCTRG_TRGSRC_ALL_BITS        ( ( uint32_t ) 0x1f1f )

/**
 * @brief Peripheral Module Disable bit used for enabling clock for ADC module.
 */
#define HAL_LL_PMD1_ADCMD_BIT                ( ( uint8_t ) 0 )

/**
 * @brief ADCTRMODE macro for using alternative (class 3) pins.
 */
#define HAL_LL_ADCTRGMODE_SHxALT_BITS(x)     ( ( uint32_t ) ( 1ul << 16 + 2 * ( ( x ) - 45 ) ) )

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
    { HAL_LL_ADCCON1_ADDRESS , hal_ll_adc_module_num( ADC_MODULE ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF }
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
 * @details Since PIC32MZ has only one ADC module only
 * reference voltage and input chanel are neccesaray for hardware initialization
 * @param vref Voltage reference used
 * @param channel Channel/pin used for input to ADC,
 * @return None
 */
static void _hal_ll_adc_hw_init( hal_ll_adc_resolution_t resolution, hal_ll_adc_voltage_reference_t vref );

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

    // switch only validates if the vref_input variable is in the enum range
    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;
        #ifdef PIC32MZxx
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_8_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_RESOLUTION_6_BIT;
            break;
        #endif

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    // set desired state of hardware to hardwer specific map
    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_DEFAULT;
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
    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = ( handle_t * ) &hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;

    handle_map[pin_check_result]->hal_ll_adc_handle = ( handle_t * ) &hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );
    uint8_t index;
    uint16_t pin_check_result = _hal_ll_adc_check_pins( hal_ll_adc_hw_specifics_map_local->pin, &index, (void *)0 );

    if ( HAL_LL_PIN_NC == pin_check_result ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    // initialize adc registers
    _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = ( handle_t * )&hal_ll_adc_hw_specifics_map[pin_check_result].ch_enable;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    // this function will update low_level_handle
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_10_BIT;
            break;
        #ifdef PIC32MZxx
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_8_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_6_BIT;
            break;
        #endif

        default:
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
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle ); // this function will update low_level_handle

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

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *read_buff )
{
    static const uint32_t *data_ptr = (uint32_t)HAL_LL_ADCDATA0_ADDRESS;

    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    uint8_t channel = hal_ll_adc_hw_specifics_map_local->channel;

    // remove all inputs
    clear_reg_bits( HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_ADINSEL_BITS_ALL );
    // writing to ADINSEL bits
    if ( 45 <= channel  ) {
        set_reg_bits( HAL_LL_ADCCON3_ADDRESS, channel - 45);         // channel to manually trigger
    } else {
        set_reg_bits( HAL_LL_ADCCON3_ADDRESS, channel );             // channel to manually trigger
    }

    set_reg_bit(HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_RQCNVRT_BIT); // manually trigger selected channel

    if ( 31 >= channel ) {
        while ( check_reg_bit( HAL_LL_ADCDSTAT1_ADDRESS, channel ) == 0 ) {
            continue;
        }
    } else if ( 45 <= channel ) {
        while ( check_reg_bit( HAL_LL_ADCDSTAT1_ADDRESS, (channel - 45) ) == 0 ) {
            continue;
        }
    } else {
        while ( check_reg_bit( HAL_LL_ADCDSTAT2_ADDRESS, (channel - 32) ) == 0 ) {
            continue;
        }
    }

    if ( 45 <= channel ) {
        channel -= 45;
    }

    // Changing the resolution of the ADC does not shift the result in the corresponding ADCDATAx
    // register. The result will still occupy 12 bits, with the corresponding lower unused bits set to ‘0’.
    // For example, a resolution of 6 bits will result in ADCDATAx<5:0> being set to ‘0’, and
    // ADCDATAx<11:6> holding the result.
    switch ( hal_ll_adc_hw_specifics_map_local->resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            *read_buff = data_ptr[channel] >> 2;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            *read_buff = data_ptr[channel] >> 4;
            break;
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            *read_buff = data_ptr[channel] >> 6;
            break;

        default:
            // default for PIC32MZ is 12bit
            *read_buff = data_ptr[channel];
            break;
    }

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = _hal_ll_get_specifics( handle );

    if ( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->ch_enable ) {
        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_DEFAULT;

        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
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

static void _hal_ll_adc_hw_init(
    uint32_t channel,
    hal_ll_adc_resolution_t resolution,
    hal_ll_adc_voltage_reference_t vref
) {
    // necesary copy of calibration data. Microchip why?
    copy_reg( HAL_LL_ADC0CFG_ADDRESS, HAL_LL_DEVADC0_ADDRESS );
    copy_reg( HAL_LL_ADC1CFG_ADDRESS, HAL_LL_DEVADC1_ADDRESS );
    copy_reg( HAL_LL_ADC2CFG_ADDRESS, HAL_LL_DEVADC2_ADDRESS );
    copy_reg( HAL_LL_ADC3CFG_ADDRESS, HAL_LL_DEVADC3_ADDRESS );
    copy_reg( HAL_LL_ADC4CFG_ADDRESS, HAL_LL_DEVADC4_ADDRESS );
    copy_reg( HAL_LL_ADC7CFG_ADDRESS, HAL_LL_DEVADC7_ADDRESS );

    // clear control registers
    clear_reg( HAL_LL_ADCCON1_ADDRESS );
    clear_reg( HAL_LL_ADCCON2_ADDRESS );
    clear_reg( HAL_LL_ADCCON3_ADDRESS );
    clear_reg( HAL_LL_ADCANCON_ADDRESS );
    clear_reg( HAL_LL_ADCTRGSNS_ADDRESS );

    // configure all channels as single-ended, unipolar inputs
    clear_reg( HAL_LL_ADCIMCON1_ADDRESS );
    clear_reg( HAL_LL_ADCIMCON2_ADDRESS );
    clear_reg( HAL_LL_ADCIMCON3_ADDRESS );

    // disable all global interrupts
    clear_reg( HAL_LL_ADCGIRQEN1_ADDRESS );
    clear_reg( HAL_LL_ADCGIRQEN2_ADDRESS );

    // disable all early interrupts
    clear_reg( HAL_LL_ADCEIEN1_ADDRESS );
    clear_reg( HAL_LL_ADCEIEN2_ADDRESS );

    // disable digital comparators
    clear_reg( HAL_LL_ADCCMPCON1_ADDRESS );
    clear_reg( HAL_LL_ADCCMPCON2_ADDRESS );
    clear_reg( HAL_LL_ADCCMPCON3_ADDRESS );

    // disable oversampling filters
    clear_reg( HAL_LL_ADCFLTR1_ADDRESS );
    clear_reg( HAL_LL_ADCFLTR2_ADDRESS );
    clear_reg( HAL_LL_ADCFLTR3_ADDRESS );
    clear_reg( HAL_LL_ADCFLTR4_ADDRESS );
    clear_reg( HAL_LL_ADCFLTR5_ADDRESS );
    clear_reg( HAL_LL_ADCFLTR6_ADDRESS );

    uint32_t adctime_resolution_mask;
    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            set_reg_bits( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_SELRES_12_BIT_BITS );
            adctime_resolution_mask  = HAL_LL_ADCTIME_SELRES_12_BIT_BITS;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            set_reg_bits( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_SELRES_10_BIT_BITS );
            adctime_resolution_mask  = HAL_LL_ADCTIME_SELRES_10_BIT_BITS;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            set_reg_bits( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_SELRES_8_BIT_BITS );
            adctime_resolution_mask  = HAL_LL_ADCTIME_SELRES_8_BIT_BITS;
            break;
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            set_reg_bits( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_SELRES_6_BIT_BITS );
            adctime_resolution_mask  = HAL_LL_ADCTIME_SELRES_6_BIT_BITS;
            break;

        default:
            /* unreachable */
            break;
    }

    // scan Trig Source Select (Global Software Trigger (GSWTRG))
    set_reg_bits( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_GSWTRG_BITS );

    // ADCCON2
    // ADC7 Sample Time (70 * Tad7)
    set_reg_bits( HAL_LL_ADCCON2_ADDRESS, HAL_LL_ADCCON2_SAMC_BITS(1) );
    // ADC7 Clock Divider (Divide by 2)
    set_reg_bits( HAL_LL_ADCCON2_ADDRESS, HAL_LL_ADCCON2_ADCDIV_BITS(1) );

    // ADCCON3
    set_reg_bits(HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_ADCSEL_TCLK_BITS);
    set_reg_bits(HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_CONCLKDIV_BITS(1));

    switch ( vref ) // Voltage Reference Input Selection (AVdd, AVss)
    {
        case HAL_LL_ADC_VREF_DEFAULT:
        case HAL_LL_ADC_VREF_EXTERNAL:
            set_reg_bits( HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_VREFSEL_EXTERNAL_BITS );
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            set_reg_bits( HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_VREFSEL_INTERNAL_BITS );
            break;

        default:
            // used by the ll adc functions, wich will validate that vreft is withing enum bounds
            break;
    }

    clear_reg( HAL_LL_ADC0TIME_ADDRESS );
    clear_reg( HAL_LL_ADC1TIME_ADDRESS );
    clear_reg( HAL_LL_ADC2TIME_ADDRESS );
    clear_reg( HAL_LL_ADC3TIME_ADDRESS );
    clear_reg( HAL_LL_ADC4TIME_ADDRESS );

    // select ADC sample time and conversion clock, x bit res, sampling time of
    // 5 * TADx
    set_reg_bits( HAL_LL_ADC0TIME_ADDRESS, HAL_LL_ADCTIME_ADCDIV_BITS(1) );
    set_reg_bits( HAL_LL_ADC1TIME_ADDRESS, HAL_LL_ADCTIME_ADCDIV_BITS(1) );
    set_reg_bits( HAL_LL_ADC2TIME_ADDRESS, HAL_LL_ADCTIME_ADCDIV_BITS(1) );
    set_reg_bits( HAL_LL_ADC3TIME_ADDRESS, HAL_LL_ADCTIME_ADCDIV_BITS(1) );
    set_reg_bits( HAL_LL_ADC4TIME_ADDRESS, HAL_LL_ADCTIME_ADCDIV_BITS(1) );

    set_reg_bits( HAL_LL_ADC0TIME_ADDRESS, HAL_LL_ADCTIME_SAMC_BITS(1) );
    set_reg_bits( HAL_LL_ADC1TIME_ADDRESS, HAL_LL_ADCTIME_SAMC_BITS(1) );
    set_reg_bits( HAL_LL_ADC2TIME_ADDRESS, HAL_LL_ADCTIME_SAMC_BITS(1) );
    set_reg_bits( HAL_LL_ADC3TIME_ADDRESS, HAL_LL_ADCTIME_SAMC_BITS(1) );
    set_reg_bits( HAL_LL_ADC4TIME_ADDRESS, HAL_LL_ADCTIME_SAMC_BITS(1) );

    set_reg_bits( HAL_LL_ADC0TIME_ADDRESS, adctime_resolution_mask );
    set_reg_bits( HAL_LL_ADC1TIME_ADDRESS, adctime_resolution_mask );
    set_reg_bits( HAL_LL_ADC2TIME_ADDRESS, adctime_resolution_mask );
    set_reg_bits( HAL_LL_ADC3TIME_ADDRESS, adctime_resolution_mask );
    set_reg_bits( HAL_LL_ADC4TIME_ADDRESS, adctime_resolution_mask );


    // select analog input for ADC modules, no presync trigger, not sync sampling
    clear_reg( HAL_LL_ADCTRGMODE_ADDRESS );

    // common scan select skip for input scan
    clear_reg( HAL_LL_ADCCSS1_ADDRESS );
    clear_reg( HAL_LL_ADCCSS2_ADDRESS );

    // wake-up Clock Count (2^7 Clocks)
    set_reg_bits( HAL_LL_ADCANCON_ADDRESS, HAL_LL_ADCANCON_WKUPCLKCNT_BITS(7) );

    // set up trigger sources
    clear_reg( HAL_LL_ADCTRGSNS_ADDRESS );

    // set up software triggering - need this for each desired channel
    set_reg_bits( HAL_LL_ADCTRG1_ADDRESS, HAL_LL_ADCTRG_TRGSRC_ALL_BITS );
    set_reg_bits( HAL_LL_ADCTRG2_ADDRESS, HAL_LL_ADCTRG_TRGSRC_ALL_BITS );
    set_reg_bits( HAL_LL_ADCTRG3_ADDRESS, HAL_LL_ADCTRG_TRGSRC_ALL_BITS );

    if ( channel >= 45 ) {
        set_reg_bits(HAL_LL_ADCTRGMODE_ADDRESS, HAL_LL_ADCTRGMODE_SHxALT_BITS(channel));
    }

    // turn on ADC module
    set_reg_bit( HAL_LL_ADCCON1_ADDRESS, HAL_LL_ADCCON1_ON_BIT );

    // let Vref stabilize
    while ( !check_reg_bit( HAL_LL_ADCCON2_ADDRESS, HAL_LL_ADCCON2_BGVRRDY_BIT ) ) {
        continue;
    }

    while ( check_reg_bit( HAL_LL_ADCCON2_ADDRESS, HAL_LL_ADCCON2_REFFLT_BIT ) ) {
        continue;
    }

    // enable clk to analog - need this for each desired channel
    set_reg_bits( HAL_LL_ADCANCON_ADDRESS, HAL_LL_ADCANCON_ANEN_ALL_BITS );

    // wait for ADC ready
    while ( read_reg_bits( HAL_LL_ADCANCON_ADDRESS, HAL_LL_ADCANCON_WKRDY_ALL_BITS ) ) {
        continue;
    }

    // enable ADC - need this for each desired channel
    set_reg_bits( HAL_LL_ADCCON3_ADDRESS, HAL_LL_ADCCON3_DIGEN_ALL_BITS );
}

static void _hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
    clear_reg_bit( HAL_LL_PMD1_ADDRESS, HAL_LL_PMD1_ADCMD_BIT );
    #endif

    //  set ANSELx register flag to  1
    hal_ll_gpio_port_analog_input(
        hal_ll_gpio_port_base_map( hal_ll_gpio_port_index( map->pin ) ),
        map->pin
    );

    _hal_ll_adc_hw_init(
        map->channel,
        map->resolution,
        map->vref_input
    );
}

// ------------------------------------------------------------------------- END
