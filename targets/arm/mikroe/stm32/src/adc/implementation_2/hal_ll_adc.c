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
 * @file  hal_ll_adc.c
 * @brief Low level HAL ADC source file.
 */

#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Define for the MCU Revision (check the revision of the MCU you are using and uncomment accordingly)
#define RevisionY
// #define RevisionV
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
#define HAL_LL_ADC_CFGR_OFFSET                 ( 0x0C / 4 )
#define HAL_LL_ADC_CFGR2_OFFSET                ( 0x10 / 4 )
#define HAL_LL_ADC_SMPR1_OFFSET                ( 0x14 / 4 )
#define HAL_LL_ADC_SMPR2_OFFSET                ( 0x18 / 4 )
#define HAL_LL_ADC_PCSEL_OFFSET                ( 0x1C / 4 )
#define HAL_LL_ADC_LTR1_OFFSET                 ( 0x20 / 4 )
#define HAL_LL_ADC_HTR1_OFFSET                 ( 0x24 / 4 )
#define HAL_LL_ADC_SQR1_OFFSET                 ( 0x30 / 4 )
#define HAL_LL_ADC_SQR2_OFFSET                 ( 0x34 / 4 )
#define HAL_LL_ADC_SQR3_OFFSET                 ( 0x38 / 4 )
#define HAL_LL_ADC_SQR4_OFFSET                 ( 0x3C / 4 )
#define HAL_LL_ADC_DR_OFFSET                   ( 0x40 / 4 )
#define HAL_LL_ADC_JSQR_OFFSET                 ( 0x4C / 4 )
#define HAL_LL_ADC_OFR1_OFFSET                 ( 0x60 / 4 )
#define HAL_LL_ADC_OFR2_OFFSET                 ( 0x64 / 4 )
#define HAL_LL_ADC_OFR3_OFFSET                 ( 0x68 / 4 )
#define HAL_LL_ADC_OFR4_OFFSET                 ( 0x6C / 4 )
#define HAL_LL_ADC_JDR1_OFFSET                 ( 0x80 / 4 )
#define HAL_LL_ADC_JDR2_OFFSET                 ( 0x84 / 4 )
#define HAL_LL_ADC_JDR3_OFFSET                 ( 0x88 / 4 )
#define HAL_LL_ADC_JDR4_OFFSET                 ( 0x8C / 4 )
#define HAL_LL_ADC_AWD2CR_OFFSET               ( 0xA0 / 4 )
#define HAL_LL_ADC_AWD3CR_OFFSET               ( 0xA4 / 4 )
#define HAL_LL_ADC_LTR2_OFFSET                 ( 0xB0 / 4 )
#define HAL_LL_ADC_HTR2_OFFSET                 ( 0xB4 / 4 )
#define HAL_LL_ADC_LTR3_OFFSET                 ( 0xB8 / 4 )
#define HAL_LL_ADC_HTR3_OFFSET                 ( 0xBC / 4 )
#define HAL_LL_ADC_DIFSEL_OFFSET               ( 0xC0 / 4 )
#define HAL_LL_ADC_CALFACT_OFFSET              ( 0xC4 / 4 )
#define HAL_LL_ADC_CALFACT2_OFFSET             ( 0xC8 / 4 )
#define HAL_LL_ADC_CSR_OFFSET                  ( 0x300 / 4 )
#define HAL_LL_ADC_CCR_OFFSET                  ( 0x308 / 4 )
#define HAL_LL_ADC_CDR_OFFSET                  ( 0x30C / 4 )
#define HAL_LL_ADC_CDR2_OFFSET                 ( 0x310 / 4 )

#define HAL_LL_ADC_ADCSEL_BIT0                 16
#define HAL_LL_ADC_ADCSEL_BIT1                 17
#define HAL_LL_ADC_CKPERSEL_BIT0               28
#define HAL_LL_ADC_CKPERSEL_BIT1               29

#define HAL_LL_ADC_FIRST_CONV                  6
#define HAL_LL_ADC_SECOND_CONV                 12
#define HAL_LL_ADC_THIRD_CONV                  18
#define HAL_LL_ADC_FOURTH_CONV                 24

#define HAL_LL_ADC12_ENABLE_CLOCK              5
#define HAL_LL_ADC3_ENABLE_CLOCK               24

#define HAL_LL_ADC_ISR_ADRDY                   0x1ul
#define HAL_LL_ADC_ISR_EOSMP                   0x2ul
#define HAL_LL_ADC_ISR_EOC                     0x4ul

#define HAL_LL_ADC_CR_ADEN                     0x1ul
#define HAL_LL_ADC_CR_ADDIS                    0x2ul
#define HAL_LL_ADC_CR_ADSTART                  0x4ul
#define HAL_LL_ADC_CR_JADSTART                 0x8ul
#define HAL_LL_ADC_CR_BOOST                    0x100ul
#define HAL_LL_ADC_CR_ADCALLIN                 0x10000ul
#define HAL_LL_ADC_CR_ADCALDIF                 0x40000000ul
#define HAL_LL_ADC_CR_DEEPPWD                  0x20000000ul
#define HAL_LL_ADC_CR_ADVREGEN                 0x10000000ul
#define HAL_LL_ADC_CR_ADCAL                    0x80000000ul

#ifdef RevisionY
#define HAL_LL_ADC_16BIT_RES                   0x00000000ul
#define HAL_LL_ADC_14BIT_RES                   0x00000004ul
#define HAL_LL_ADC_12BIT_RES                   0x00000008ul
#define HAL_LL_ADC_10BIT_RES                   0x0000000Cul
#define HAL_LL_ADC_8BIT_RES                    0x00000010ul
#endif

#define HAL_LL_RESOLUTION_MASK                 0xFFFFFFE3ul

#ifdef RevisionV
#define HAL_LL_ADC_16BIT_RES                   0x00000000ul
#define HAL_LL_ADC_14BIT_RES                   0x00000014ul
#define HAL_LL_ADC_12BIT_RES                   0x00000018ul
#define HAL_LL_ADC_10BIT_RES                   0x0000000Cul
#define HAL_LL_ADC_8BIT_RES                    0x0000001Cul
#endif

#define HAL_LL_ADC_CFGR_CONT                   0x2000ul
#define HAL_LL_ADC_CFGR_DISCEN                 0x10000ul
#define HAL_LL_ADC_CFGR_SRES                   0xFFFFFFE0ul
#define HAL_LL_ADC_DMNGT_DR                    0xFFFFFFFCul
#define HAL_LL_ADC_IER_EINT                    0x000007FFul
#define HAL_LL_ADC_SQR1_RCSL                   0xFFFFFFF0ul

#define HAL_LL_MODULE_INDEX_ERROR              0xFFFFFFFFul

#define HAL_LL_ADC_DEFAULT_BASE_ADDRESS        0xFF

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC hw specific module values */
typedef struct
{
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;


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
    #ifdef I2C_MODULE_1
    {ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef I2C_MODULE_2
    {ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef I2C_MODULE_3
    {ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
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
  * @brief  Enable ADC module 2 clock.
  * @param  none
  * @return none
  */
static inline void adc2_enable_clock();

/**
  * @brief  Enable ADC module 3 clock.
  * @param  none
  * @return none
  */
static inline void adc3_enable_clock();

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
static void _hal_ll_adc_hw_init( hal_ll_base_addr_t *base, uint32_t resolution );

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
    case HAL_LL_ADC_RESOLUTION_8_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_8BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_10_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_10BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_12_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_12BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_14_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_14BIT_RES;
        break;
    case HAL_LL_ADC_RESOLUTION_16_BIT:
        hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_16BIT_RES;
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
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_8BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_10BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_12BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_14BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_16BIT_RES;
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
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
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
    static uint32_t *reg;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_base_addr_t *base = ( hal_ll_base_addr_t * )hal_ll_adc_hw_specifics_map_local->base ;

    // Preselect channel.
    *( base + HAL_LL_ADC_PCSEL_OFFSET ) |= 1ul << hal_ll_adc_hw_specifics_map_local->channel;
    // First conversion in regular sequence.
    *( base + HAL_LL_ADC_SQR1_OFFSET )  |= ( uint32_t )( hal_ll_adc_hw_specifics_map_local->channel ) << HAL_LL_ADC_FIRST_CONV;
    // Second conversion in regular sequence.
    *( base + HAL_LL_ADC_SQR1_OFFSET )  |= ( uint32_t )( hal_ll_adc_hw_specifics_map_local->channel ) << HAL_LL_ADC_SECOND_CONV;
    // Third conversion in regular sequence.
    *( base + HAL_LL_ADC_SQR1_OFFSET )  |= ( uint32_t )( hal_ll_adc_hw_specifics_map_local->channel ) << HAL_LL_ADC_THIRD_CONV;
    // Fourth conversion in regular sequence.
    *( base + HAL_LL_ADC_SQR1_OFFSET )  |= ( uint32_t )( hal_ll_adc_hw_specifics_map_local->channel ) << HAL_LL_ADC_FOURTH_CONV;
    // Start of regular conversion.
    *( base + HAL_LL_ADC_CR_OFFSET )    |= HAL_LL_ADC_CR_ADSTART;

    // The application should allow a delay of tSTAB between power up and start of conversion
    Delay_1us();

    // Wait until end of sampling phase is reached.
    while ( !( *( base + HAL_LL_ADC_ISR_OFFSET ) & HAL_LL_ADC_ISR_EOSMP ) );

    do
    {
        // Read conversion result from the last converted regular channel.
        reg = ( *( base + HAL_LL_ADC_DR_OFFSET ) );
    } while ( *( base + HAL_LL_ADC_ISR_OFFSET ) & HAL_LL_ADC_ISR_EOC );
    // Wait for EOC = 0.
    // It is cleared by software writing 1 to it or by reading the ADC_DR.
    *readDatabuf = reg;

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

static inline void adc12_enable_clock()
{
    set_reg_bit( _RCC_AHB1ENR, HAL_LL_ADC12_ENABLE_CLOCK );
}

static inline void adc3_enable_clock()
{
    set_reg_bit( _RCC_AHB4ENR, HAL_LL_ADC3_ENABLE_CLOCK );
}

static void _hal_ll_adc_enable_clock( uint8_t base )
{
    switch ( base )
    {
        #ifdef ADC_MODULE_1
        case ( hal_ll_adc_module_num(ADC_MODULE_1) ):
            adc12_enable_clock();
            break;
        #endif
        #ifdef ADC_MODULE_2
        case ( hal_ll_adc_module_num(ADC_MODULE_2) ):
            adc12_enable_clock();
            break;
        #endif
        #ifdef ADC_MODULE_3
        case ( hal_ll_adc_module_num(ADC_MODULE_3) ):
            adc3_enable_clock();
            break;
        #endif
    }
}

static void _hal_ll_adc_hw_init( hal_ll_base_addr_t *base, uint32_t resolution )
{
    /* For the startup time of the ADC voltage regulator,
       please refer to device datasheet for TADCVREG_STUP parameter */
    static uint32_t tadcvreg_stup = 0;
    static uint32_t *reg;

    // Set HSI as PER CK.
    clear_reg_bit( _RCC_D1CCIPR , HAL_LL_ADC_CKPERSEL_BIT1 );
    clear_reg_bit( _RCC_D1CCIPR , HAL_LL_ADC_CKPERSEL_BIT0 );

    // Select HSI as adc clock.
    set_reg_bit( _RCC_D3CCIPR , HAL_LL_ADC_ADCSEL_BIT1 );
    clear_reg_bit( _RCC_D3CCIPR , HAL_LL_ADC_ADCSEL_BIT0 );

    // To start ADC operations, it is first needed to exit deep-power-down.
    if ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_DEEPPWD )
    {
        *( base + HAL_LL_ADC_CR_OFFSET ) &= ~HAL_LL_ADC_CR_DEEPPWD;
    }
    // It is mandatory to enable the ADC internal voltage regulator by setting ADVREGEN.
    if ( !( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_ADVREGEN ) )
    {
        *( base + HAL_LL_ADC_CR_OFFSET ) |= HAL_LL_ADC_CR_ADVREGEN;
    }
    // The software must wait for the startup time of the ADC voltage regulator.
    tadcvreg_stup = 10 * ( Get_Fosc_kHz() / 100 );
    while ( tadcvreg_stup )
    {
        tadcvreg_stup--;
    }
    // Enable ADC interrupts.
    *( base + HAL_LL_ADC_IER_OFFSET ) |= HAL_LL_ADC_IER_EINT;
    // Disable ADC
    if ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_ADEN )  // If enabled.
    {
        *( base + HAL_LL_ADC_CR_OFFSET ) |= HAL_LL_ADC_CR_ADDIS;  // Disable adc.
        while ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_ADDIS );
    }
    // Voltage reference enable, ckmode - async, div 2.
    if ( (uint32_t)base == ADC2_BASE_ADDR )
    {
        base = ADC1_BASE_ADDR;
        *( base + HAL_LL_ADC_CCR_OFFSET ) |= ( ( 1ul << 22 ) |
                                            ( 1ul << 23 ) |
                                            ( 1ul << 19 ) );
        base = ADC2_BASE_ADDR;
    } else
    {
        *( base + HAL_LL_ADC_CCR_OFFSET ) |= ( ( 1ul << 22 ) |
                                            ( 1ul << 23 ) |
                                            ( 1ul << 19 ) );
    }
    // Calibrate.
    *( base + HAL_LL_ADC_CR_OFFSET ) &= ~HAL_LL_ADC_CR_ADEN;
    // Set single-ended input.
    *( base + HAL_LL_ADC_CR_OFFSET ) &= ~HAL_LL_ADC_CR_ADCALDIF;
    // Linearity calibration disable.
    *( base + HAL_LL_ADC_CR_OFFSET ) &= ~HAL_LL_ADC_CR_ADCALLIN;
    // Start calibration.
    *( base + HAL_LL_ADC_CR_OFFSET ) |= HAL_LL_ADC_CR_ADCAL;
    // Wait until calibration is complete.
    while ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_ADCAL );
    // Stop ongoing injected conversions.
    *( base + HAL_LL_ADC_CR_OFFSET ) |= HAL_LL_ADC_CR_BOOST;
    while ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_ADSTART );
    while ( *( base + HAL_LL_ADC_CR_OFFSET ) & HAL_LL_ADC_CR_JADSTART );
    // Set data resolution.
    reg = ( base + HAL_LL_ADC_CFGR_OFFSET );
    *reg &= HAL_LL_RESOLUTION_MASK;
    *reg |= resolution;

    // Discontinuous mode disabled.
    *( base + HAL_LL_ADC_CFGR_OFFSET ) &= ~HAL_LL_ADC_CFGR_DISCEN;
    // Single conversion mode.
    *( base + HAL_LL_ADC_CFGR_OFFSET ) &= ~HAL_LL_ADC_CFGR_CONT;
    // Regular channel sequence length.
    *( base + HAL_LL_ADC_SQR1_OFFSET ) &= HAL_LL_ADC_SQR1_RCSL;
    // Clear ADRDY bit.
    *( base + HAL_LL_ADC_ISR_OFFSET ) |= HAL_LL_ADC_ISR_ADRDY;
    // Enable ADC.
    *( base + HAL_LL_ADC_CR_OFFSET ) |= HAL_LL_ADC_CR_ADEN;
    // Wait for ADDRDY.
    while ( !( *( base + HAL_LL_ADC_ISR_OFFSET ) & HAL_LL_ADC_ISR_ADRDY ) );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                                                     hal_ll_gpio_pin_mask( map->pin ) );

    _hal_ll_adc_enable_clock( map->module_index );

    _hal_ll_adc_hw_init((hal_ll_base_addr_t *)map->base, map->resolution);

}
// ------------------------------------------------------------------------- END
