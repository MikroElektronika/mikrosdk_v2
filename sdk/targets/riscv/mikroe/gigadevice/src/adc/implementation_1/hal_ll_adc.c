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
#include "hal_ll_adc_pin_map.h"

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

#define HAL_LL_ADC_STAT_EOC_BIT             (1)
#define HAL_LL_ADC_STAT_EOIC_BIT            (2)
#define HAL_LL_ADC_CTL0_SM_BIT              (8)
#define HAL_LL_ADC_CTL1_ADCON_BIT           (0)
#define HAL_LL_ADC_CTL1_CTN_BIT             (1)
#define HAL_LL_ADC_CTL1_CLB_BIT             (2)
#define HAL_LL_ADC_CTL1_RSTCLB_BIT          (3)
#define HAL_LL_ADC_CTL1_DAL_BIT             (11)
#define HAL_LL_ADC_CTL1_SWRCST_BIT          (22)

#define HAL_ADC0_ENABLE_CLOCK               (9)
#define HAL_ADC1_ENABLE_CLOCK               (10)

#define HAL_LL_ADC_CTL0_SM_MASK             (0xFFF0FEFFUL)
#define HAL_LL_ADC_CTL0_SYNCM_MASK          (0xFFF0FFFFUL)
#define HAL_LL_ADC_CTL1_ETSRC_MASK          (0x000E0000UL)
#define HAL_LL_ADC_CLEAR_MASK               (0xFFF0F7FDUL)
#define HAL_LL_ADC_CONVERSION_ONE           (0x00F00000UL)
#define HAL_LL_ADC_SEQUENCE_LENGTH_MASK     (0xFF0FFFFFUL)
#define HAL_LL_ADC_OVSAMPCTL_RES_MASK       (0x00003000UL)

#define HAL_LL_ADC_DELAY_PERIOD             (110)

#define HAL_LL_MODULE_INDEX_ERROR           (0xFFFFFFFFUL)

#define HAL_LL_ADC_6BIT_RES                 (0x3000UL)
#define HAL_LL_ADC_8BIT_RES                 (0x2000UL)
#define HAL_LL_ADC_10BIT_RES                (0x1000UL)
#define HAL_LL_ADC_12BIT_RES                (0x0000UL)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

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

/*!< @brief ADC register structure. */
typedef struct
{
    uint32_t stat;           /* Address offset 0x00 */
    uint32_t ctl0;           /* Address offset 0x04 */
    uint32_t ctl1;           /* Address offset 0x08 */
    uint32_t sampt0;         /* Address offset 0x0C */
    uint32_t sampt1;         /* Address offset 0x10 */
    uint32_t ioff0;          /* Address offset 0x14 */
    uint32_t ioff1;          /* Address offset 0x18 */
    uint32_t ioff2;          /* Address offset 0x1C */
    uint32_t ioff3;          /* Address offset 0x20 */
    uint32_t wdht;           /* Address offset 0x24 */
    uint32_t wdlt;           /* Address offset 0x28 */
    uint32_t rsq0;           /* Address offset 0x2C */
    uint32_t rsq1;           /* Address offset 0x30 */
    uint32_t rsq2;           /* Address offset 0x34 */
    uint32_t isq;            /* Address offset 0x38 */
    uint32_t idata0;         /* Address offset 0x3C */
    uint32_t idata1;         /* Address offset 0x40 */
    uint32_t idata2;         /* Address offset 0x44 */
    uint32_t idata3;         /* Address offset 0x48 */
    uint32_t rdata;          /* Address offset 0x4C */
    uint32_t _unused[12];    /* Address offset 0x50 */
    uint32_t ovsampctl;      /* Address offset 0x80 */
} hal_ll_adc_base_handle_t;

/*!< @brief ADC hw specific module values */
typedef struct
{
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
    #ifdef ADC_MODULE_0
    {ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
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
  * @param[in]  *handle_map - ADC handle register
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin name and channel.
 *
 * @param[in]  module_index ADC HW module index -- 0,1,2...
 * @param[in]  *index  Pointer with ADC pin map index value
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
static void hal_ll_adc_enable_clock( uint8_t base );

/**
  * @brief  Initialize ADC module.
  * @param  *base - ADC module base address.
  * @param  resolution - ADC module resolution.
  * @return None
  */
static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = {HAL_LL_PIN_NC};

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map ))) {
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

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( resolution )
    {
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

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input ) {
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch( vref_input )
    {
        case HAL_LL_ADC_VREF_EXTERNAL:
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base;
    uint8_t stabilization_time = HAL_LL_ADC_DELAY_PERIOD;

    base->rsq0 &= ~HAL_LL_ADC_CONVERSION_ONE;
    base->rsq2 |= hal_ll_adc_hw_specifics_map_local->channel;

    // Enable ADC.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_ADCON_BIT );

    // Wait for ADC to stabilize before starting the conversion.
    while ( stabilization_time-- ) asm("nop");

    // Start the conversion.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_SWRCST_BIT );

    // Start ADC calibration.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_CLB_BIT );

    // Wait for calibration to finish.
    while (( check_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_CLB_BIT )));

    // Wait for the end of conversion.
    while (!( check_reg_bit( &( base->stat ), HAL_LL_ADC_STAT_EOC_BIT )));

    *readDatabuf = base->rdata;

    clear_reg_bit( &( base->stat ), HAL_LL_ADC_STAT_EOC_BIT );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base ) {

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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ));
    uint16_t pin_index = 0;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == hal_ll_analog_in_register_list[pin_index].pin )
        {
            // Get module number
            hal_ll_module_id = hal_ll_analog_in_register_list[pin_index].module_index;
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
    hal_ll_adc_hw_specifics_map[module_index].pin = hal_ll_analog_in_register_list[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = hal_ll_analog_in_register_list[ index->pin_an[module_index] ].channel;
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

static void hal_ll_adc_enable_clock( uint8_t base ) {
    switch ( base )
    {
        #ifdef ADC_MODULE_0
        case ( hal_ll_adc_module_num(ADC_MODULE_0) ):
            set_reg_bit( RCU_APB2EN, HAL_ADC0_ENABLE_CLOCK );
            break;
        #endif
        #ifdef ADC_MODULE_1
        case ( hal_ll_adc_module_num(ADC_MODULE_1) ):
            set_reg_bit( RCU_APB2EN, HAL_ADC1_ENABLE_CLOCK );
            break;
        #endif
    }
}

static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution ) {
    // Disable ADC.
    clear_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_ADCON_BIT );

    // Resolution
    base->ovsampctl &= ~HAL_LL_ADC_OVSAMPCTL_RES_MASK;
    base->ovsampctl |= resolution;

    // Clear SCAN bits.
    base->ctl0 &= HAL_LL_ADC_CTL0_SM_MASK;

    // Clear CONT, ALIGN bits.
    base->ctl1 &= HAL_LL_ADC_CLEAR_MASK;

    // Independent mode.
    base->ctl0 &= HAL_LL_ADC_CTL0_SYNCM_MASK;

    // Scan mode disabled.
    clear_reg_bit( &( base->ctl0 ), HAL_LL_ADC_CTL0_SM_BIT );

    // Single conversion mode.
    clear_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_CTN_BIT );

    // Data alignment = right.
    clear_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_DAL_BIT );

    // Conversion on external event disabled.
    base->ctl1 |= HAL_LL_ADC_CTL1_ETSRC_MASK;

    // Regular channel sequence length 0000: 1 conversion.
    base->rsq0 &= HAL_LL_ADC_SEQUENCE_LENGTH_MASK;

    // Enable ADC.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_ADCON_BIT );

    // Enable ADC reset calibration register.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_RSTCLB_BIT );
    while (( check_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_RSTCLB_BIT )));

    // Start ADC calibration.
    set_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_CLB_BIT );
    while (( check_reg_bit( &( base->ctl1 ), HAL_LL_ADC_CTL1_CLB_BIT )));
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin )),
                                                     hal_ll_gpio_pin_mask( map->pin ));
    hal_ll_adc_enable_clock( map->module_index );

    hal_ll_adc_hw_init(( hal_ll_adc_base_handle_t *)map->base, map->resolution );
}
// ------------------------------------------------------------------------- END
