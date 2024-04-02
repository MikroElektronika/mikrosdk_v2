/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
#include "hal_ll_adc_pin_map.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS
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

#define HAL_LL_ADC_ISR_OFFSET                  ( 0x00 )
#define HAL_LL_ADC_IER_OFFSET                  ( 0x04 / 4 )
#define HAL_LL_ADC_CR_OFFSET                   ( 0x08 / 4 )
#define HAL_LL_ADC_CFGR1_OFFSET                ( 0x0C / 4 )
#define HAL_LL_ADC_CFGR2_OFFSET                ( 0x10 / 4 )
#define HAL_LL_ADC_SMPR_OFFSET                 ( 0x14 / 4 )
#define HAL_LL_ADC_AWD1TR_OFFSET               ( 0x20 / 4 )
#define HAL_LL_ADC_CHSELR_OFFSET               ( 0x28 / 4 )
#define HAL_LL_ADC_DR_OFFSET                   ( 0x40 / 4 )
#define HAL_LL_ADC_CCR_OFFSET                  ( 0x308 / 4 )

#define HAL_LL_ADC_ADEN_BIT                    0
#define HAL_LL_ADC_ADRDY_BIT                   0
#define HAL_LL_ADC_ADDIS_BIT                   1
#define HAL_LL_ADC_ADSTART_BIT                 2
#define HAL_LL_ADC_EOC_BIT                     2
#define HAL_LL_ADC_SCANDIR_BIT                 2
#define HAL_LL_ADC_ADSTP_BIT                   4
#define HAL_LL_ADC_ALIGN_BIT                   5
#define HAL_LL_ADC_CONT_BIT                    13
#define HAL_LL_ADC_ADCAL_BIT                   31

#define HAL_LL_ADC1_ENABLE_CLOCK               20
#define HAL_LL_ADC_CKMODE0_BIT                 30
#define HAL_LL_ADC_CCIPR                       30
#define HAL_LL_ADC_CKMODE1_BIT                 31

#define HAL_LL_ADC_2M8HZ                       2800000ul
#define HAL_LL_ADC_8MHZ                        8000000ul
#define HAL_LL_ADC_16MHZ                       16000000ul

#define HAL_LL_ADC_12BIT_RES                   0x00000000ul
#define HAL_LL_ADC_10BIT_RES                   0x00000008ul
#define HAL_LL_ADC_8BIT_RES                    0x00000010ul
#define HAL_LL_ADC_6BIT_RES                    0x00000018ul

#define HAL_LL_ADC_RESOLUTION_MASK             0xFFFFFFE7ul

#define HAL_LL_ADC_SMPR                        0xFFFFFFF8ul
#define HAL_LL_ADC_EXTEN                       0xFFFFF3FFul
#define HAL_LL_ADC_CR_WAIT                     0x80000017ul

#define HAL_LL_MODULE_INDEX_ERROR              0xFFFFFFFFul

#define HAL_LL_ADC_DEFAULT_BASE_ADDRESS        0xFF

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< Abbreviations used in source. */
typedef uint32_t hal_ll_adc_base_handle_t;

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

/*!< @brief ADC hw specific module values */
typedef struct
{
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
    #ifdef ADC_MODULE_1
    {ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable ADC module 1 clock.
  * @param  none
  * @return none
  */
static inline void adc1_enable_clock();

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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and channel values for ADC pin
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
  * @brief  Enable ADC module gate clock.
  * @param  base - ADC module base address.
  * @return None
  */
static void _hal_ll_adc_enable_clock( uint8_t base );

/**
  * @brief  Initialize ADC module.
  * @param  *base - ADC module base address.
  * @param  resolution - ADC module resolution.
  * @return None
  */
static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id)
{
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = {HAL_LL_PIN_NC};

    if ( (pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution )
    {
    case HAL_LL_ADC_RESOLUTION_6_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_6BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_8_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_8BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_10_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_10BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_12_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_12BIT_RES;
        break;
    default:
        return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
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

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution)
{
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( resolution ) {
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_6BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_8BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_10BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_12BIT_RES;
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
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
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
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    *(base + HAL_LL_ADC_CHSELR_OFFSET) = 1ul << hal_ll_adc_hw_specifics_map_local->channel;
    set_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADSTART_BIT );

    Delay_1us();
    while( !(check_reg_bit( ( base + HAL_LL_ADC_ISR_OFFSET ), HAL_LL_ADC_EOC_BIT ) ) );
    *readDatabuf = ( *(base + HAL_LL_ADC_DR_OFFSET) );
    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map )
{
    static const uint16_t     adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );
    uint16_t     pin_index = 0;
    uint8_t      index_counter = 0;
    uint8_t      hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == _adc_map[pin_index].pin )
        {
            // Get module number
            hal_ll_module_id = _adc_map[pin_index].module_index;
            // Map pin name
            index->pin_an[hal_ll_module_id] = pin_index;

            // Check if module is taken
            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_adc_handle ) {
                return hal_ll_module_id;
            } else if ( ADC_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index ) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin = _adc_map[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = _adc_map[ index->pin_an[module_index] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void adc_clock_mode( uint32_t clock_value, hal_ll_adc_base_handle_t *base )
{
    if (clock_value < HAL_LL_ADC_8MHZ) // Set clock and prescaler.
    {
        // If less than 8MHz, prescaler is set to 1 (read caution on pg. 252 in the reference manual).
        set_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE0_BIT );
        set_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE1_BIT );
    }
    else if ( clock_value < HAL_LL_ADC_16MHZ )
    {
        // Above 8 Mhz, prescaler is set to 2.
        set_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE0_BIT );
        clear_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE1_BIT );
    }
    else
    {
        // Above 16 Mhz, prescaler is set to 4.
        clear_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE0_BIT );
        set_reg_bit( ( base + HAL_LL_ADC_CFGR2_OFFSET ), HAL_LL_ADC_CKMODE1_BIT );
    }
}


static inline void adc1_enable_clock()
{
    set_reg_bit( _RCC_APB2ENR, HAL_LL_ADC1_ENABLE_CLOCK );
}

static void _hal_ll_adc_enable_clock( uint8_t base )
{
    switch ( base )
    {
        #ifdef ADC_MODULE_1
        case ( hal_ll_adc_module_num(ADC_MODULE_1) ):
            adc1_enable_clock();
            break;
        #endif
    }
}

static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution )
{
    rcc_clocks_t    rcc_clocks;
    static uint32_t *reg;
    static uint32_t temp_reg;
    static uint32_t adc_clk;
    /* ADC clock
    The ADC features two clock schemes:
    Clock for the analog circuitry: ADCCLK, common to all ADCs
    This clock is generated from the APB2 clock divided by a programmable prescaler that
    allows the ADC to work at fPCLK2/2, /4, /6 or /8. ADCCLK maximum value is 30 MHz
    when the APB2 clock is at 60 MHz. */
    RCC_GetClocksFrequency( &rcc_clocks );

//     Turn off ADC module.
    if ( check_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADEN_BIT ) )
    {
        set_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADDIS_BIT );

        while( check_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADDIS_BIT ) );
    }
    if ( check_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADDIS_BIT ) )
    {
        set_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADSTP_BIT );
    }


    // Select the correct ADC clock source.
    temp_reg = _RCC_CCIPR;
    temp_reg >>= HAL_LL_ADC_CCIPR;

    switch ( temp_reg )
    {
    // If system clock selected as source.
    case 0 :
        adc_clk = rcc_clocks.sysclk;
        break;
    // If nothing of the above use PCLK as default clock.
    default:
        adc_clk = rcc_clocks.pclk;
        break;
    }

    adc_clock_mode( adc_clk, base );

    // Wait for ADEN to go down.
    while( check_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADEN_BIT ) );

    // Start calibration.
    set_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADCAL_BIT );
    while( check_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADCAL_BIT ) );

    // Set sampling time - 1.5 ADC clock.
    *( base + HAL_LL_ADC_SMPR_OFFSET ) &= HAL_LL_ADC_SMPR;

    // Set resolution.
    reg = ( base + HAL_LL_ADC_CFGR1_OFFSET );
    *reg &= HAL_LL_ADC_RESOLUTION_MASK;
    *reg |= resolution;

    // Wait for hardware to clear ADC_CR register.
    while( ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_WAIT ) != 0 );

    // Scan sequence upward.
    clear_reg_bit( ( base + HAL_LL_ADC_CFGR1_OFFSET ), HAL_LL_ADC_SCANDIR_BIT );

    // Data alignment - right.
    clear_reg_bit( ( base + HAL_LL_ADC_CFGR1_OFFSET ), HAL_LL_ADC_ALIGN_BIT );

    // Single conversion mode.
    clear_reg_bit( ( base + HAL_LL_ADC_CFGR1_OFFSET ), HAL_LL_ADC_CONT_BIT );

    // External trigger disable.
    *( base + HAL_LL_ADC_CFGR1_OFFSET ) &= HAL_LL_ADC_EXTEN;

    // Turn on ADC module.
    set_reg_bit( ( base + HAL_LL_ADC_CR_OFFSET ), HAL_LL_ADC_ADEN_BIT );
    while( !( check_reg_bit( ( base + HAL_LL_ADC_ISR_OFFSET ), HAL_LL_ADC_ADRDY_BIT ) ) );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                                                     hal_ll_gpio_pin_mask( map->pin ) );

    _hal_ll_adc_enable_clock( map->module_index );

    _hal_ll_adc_hw_init((hal_ll_adc_base_handle_t *)map->base, map->resolution);

}
// ------------------------------------------------------------------------- END
