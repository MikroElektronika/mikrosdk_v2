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

/*!< @brief Helper macro for getting ADC module clock enable bits. */
#define HAL_LL_ADC0_ENABLE_CLOCK            27
#define HAL_LL_ADC1_ENABLE_CLOCK            27

/*!< @brief Helper macros for Low Level ADC hardware initialization . */

// ADCx_CFG1[ADLPC] - Low Power configuration.
#define HAL_LL_ADC_LOW_POWER_ENABLE         7

// ADCx_CFG1[ADIV] - Clock Divide select.
#define HAL_LL_ADC_CLOCK_DIV_1              0x00000000UL
#define HAL_LL_ADC_CLOCK_DIV_2              0x00000020UL
#define HAL_LL_ADC_CLOCK_DIV_4              0x00000040UL
#define HAL_LL_ADC_CLOCK_DIV_8              0x00000060UL

// ADCx_CFG1[ADLSMP] - Sample Time configuration.
#define HAL_LL_ADC_LONG_SAMPLE_TIME_ENABLE  0x00000010UL

// ADCx_CFG1[MODE] - ADC resolution (mode) configuration.
#define HAL_LL_ADC_8BIT_RES                 0x00000000UL
#define HAL_LL_ADC_10BIT_RES                0x00000008UL
#define HAL_LL_ADC_12BIT_RES                0x00000004UL
#define HAL_LL_ADC_16BIT_RES                0x0000000CUL

// ADCx_CFG1[ADICLK] - Input Clock Select.
#define HAL_LL_ADC_CLOCK_SOURCE_BUS         0x00000000UL
#define HAL_LL_ADC_CLOCK_SOURCE_ALTERNATE2  0x00000001UL
#define HAL_LL_ADC_CLOCK_SOURCE_ALTERNATE   0x00000002UL
#define HAL_LL_ADC_CLOCK_SOURCE_ASYNC       0x00000003UL

// ADCx_CFG2[ADACKEN] - Asynchronous Output Clock Enable.
#define HAL_LL_ADC_ASYNC_CLOCK_ENABLE       0x00000008UL
// ADCx_CFG2[MUXSEL] - ADC Mux Select.
#define HAL_LL_ADC_MUX_SELECT               4

#define HAL_LL_ADC_CFG1_CLEAR_MASK          0x000000FFUL
#define HAL_LL_ADC_CFG2_CLEAR_MASK          0x0000001FUL

// ADCxSC1n masks.
#define HAL_LL_ADC_DISABLE_CONVERSION       0x0000001FUL
#define HAL_LL_ADC_COCO_FLAG                0x00000080UL

// Mask in channel pins.
#define HAL_LL_ADC_MASK_CHANNEL             0x1F

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
typedef struct {
    hal_ll_base_addr_t sc1a;        /**< ADC Status and Control Register A, array offset: 0x0 */
    hal_ll_base_addr_t sc1b;        /**< ADC Status and Control Register B, array offset: 0x4 */
    hal_ll_base_addr_t cfg1;        /**< ADC Configuration Register 1, offset: 0x8 */
    hal_ll_base_addr_t cfg2;        /**< ADC Configuration Register 2, offset: 0xC */
    hal_ll_base_addr_t ra;          /**< ADC Data Result Register A, array offset: 0x10 */
    hal_ll_base_addr_t rb;          /**< ADC Data Result Register B, array offset: 0x14 */
    hal_ll_base_addr_t cv1;         /**< Compare Value Registers, offset: 0x18 */
    hal_ll_base_addr_t cv2;         /**< Compare Value Registers, offset: 0x1C */
    hal_ll_base_addr_t sc2;         /**< Status and Control Register 2, offset: 0x20 */
    hal_ll_base_addr_t sc3;         /**< Status and Control Register 3, offset: 0x24 */
    hal_ll_base_addr_t OFS;         /**< ADC Offset Correction Register, offset: 0x28 */
    hal_ll_base_addr_t PG;          /**< ADC Plus-Side Gain Register, offset: 0x2C */
    hal_ll_base_addr_t MG;          /**< ADC Minus-Side Gain Register, offset: 0x30 */
    hal_ll_base_addr_t CLPD;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
    hal_ll_base_addr_t CLPS;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
    hal_ll_base_addr_t CLP4;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
    hal_ll_base_addr_t CLP3;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
    hal_ll_base_addr_t CLP2;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
    hal_ll_base_addr_t CLP1;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
    hal_ll_base_addr_t CLP0;        /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
    hal_ll_base_addr_t __unused1;
    hal_ll_base_addr_t CLMD;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
    hal_ll_base_addr_t CLMS;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
    hal_ll_base_addr_t CLM4;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
    hal_ll_base_addr_t CLM3;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
    hal_ll_base_addr_t CLM2;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
    hal_ll_base_addr_t CLM1;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
    hal_ll_base_addr_t CLM0;        /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} hal_ll_adc_base_handle_t;

typedef struct{
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_adc_voltage_reference_t vref_input;
    float vref_value;
    uint32_t resolution;
    uint8_t channel;
    uint8_t sample;
} hal_ll_adc_hw_specifics_map_t;

typedef struct
{
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

/*!< @brief ADC low level specific structure initialization. */
static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT+1] = {

    #ifdef ADC_MODULE_0
    {HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef ADC_MODULE_1
    {HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Enable ADC module 0 clock.
  * @param  none
  * @return none
  */
static inline void hal_ll_adc0_enable_clock();

/**
  * @brief  Enable ADC module 1 clock.
  * @param  none
  * @return none
  */
static inline void hal_ll_adc1_enable_clock();

/**
  * @brief  Initialize ADC module.
  * @param[in] map - ADC module local map.
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
  * @param[in]  index - ADC map index value.
  * @param[out] handle_map - Global handle map.
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
 * @param[in]  index  Pointer with ADC pin map index value.
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
  * @param[in]  module_index - ADC module index value.
  * @return None
  */
static void hal_ll_adc_enable_clock( uint8_t module_index );

/**
 * @brief Sets adequate subchannel for selected pin.
 * @param[in] base ADC base address.
 * @param[in] adc_pin ADC pin name.
 */
static void hal_ll_adc_set_subchannel( hal_ll_adc_base_handle_t *base, hal_ll_pin_name_t adc_pin );

/**
  * @brief  Initialize ADC module.
  * @param[in]  base - ADC module base address.
  * @param[in]  resolution - ADC module resolution.
  * @param[in] map - ADC module local map.
  * @return None
  */
static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution, hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if (( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_8BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_10BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_12BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_16BIT_RES;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL: // DEFAULT CASE
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[ pin_check_result ].pin != pin ) {
        hal_ll_adc_map_pin( pin_check_result, &index );
        handle_map[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init(hal_ll_adc_hw_specifics_map_local);

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_8BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_10BIT_RES;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_12BIT_RES;
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

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input ) {
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL: // DEFAULT CASE
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );
    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle != NULL ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ) {

    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    base->sc1a = hal_ll_adc_hw_specifics_map_local->channel & HAL_LL_ADC_MASK_CHANNEL;

    while ( 0 == ( base->sc1a & HAL_LL_ADC_COCO_FLAG ) );

    *readDatabuf = ( uint16_t )base->ra;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );
    uint16_t pin_index = 0;
    uint8_t  index_counter = 0;
    uint8_t  hal_ll_module_id = 0;

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
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[ hal_ll_module_error ];
}


static inline void hal_ll_adc0_enable_clock() {
    set_reg_bit( _SIM_SCGC6, HAL_LL_ADC0_ENABLE_CLOCK );
}

static inline void hal_ll_adc1_enable_clock() {
    set_reg_bit( _SIM_SCGC3, HAL_LL_ADC1_ENABLE_CLOCK );
}

static void hal_ll_adc_enable_clock( uint8_t module_index ) {
    switch( module_index ) {
        #ifdef ADC_MODULE_0
        case hal_ll_adc_module_num( ADC_MODULE_0 ):
            hal_ll_adc0_enable_clock();
            break;
        #endif
        #ifdef ADC_MODULE_1
        case hal_ll_adc_module_num( ADC_MODULE_1 ):
            hal_ll_adc1_enable_clock();
            break;
        #endif
    }
}

static void hal_ll_adc_set_subchannel( hal_ll_adc_base_handle_t *base, hal_ll_pin_name_t adc_pin ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {
        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            if( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup ) {
                clear_reg_bit( &base->cfg2, HAL_LL_ADC_MUX_SELECT );
                break;
            } else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup ) {
                set_reg_bit( &base->cfg2, HAL_LL_ADC_MUX_SELECT );
            }
        }
    }
}

static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution, hal_ll_adc_hw_specifics_map_t *map ) {

    // Reset all registers to a known state.
    base->cfg1 = 0;
    base->cfg2 = 0;
    base->cv1  = 0;
    base->cv2  = 0;
    base->sc2  = 0;
    base->sc3  = 0;

    // Clear ADC Configuration Register 1 (ADCx_CFG1).
    base->cfg1 &= ~HAL_LL_ADC_CFG1_CLEAR_MASK;

    // Enable low power mode.
    set_reg_bit( &base->cfg1, HAL_LL_ADC_LOW_POWER_ENABLE );

    // Set ADC Input Clock divider ratio.
    base->cfg1 |= HAL_LL_ADC_CLOCK_DIV_8;

    // Set Long Sample time.
    base->cfg1 |= HAL_LL_ADC_LONG_SAMPLE_TIME_ENABLE;

    // Set ADC Resolution.
    base->cfg1 |= resolution;

    // Set ADC Clock source.
    base->cfg1 |= HAL_LL_ADC_CLOCK_SOURCE_ASYNC;

    // Clear ADC Configuration Register 2 (ADCx_CFG2).
    base->cfg2 &= ~HAL_LL_ADC_CFG2_CLEAR_MASK;

    // Changes the ADC mux setting to select between alternate sets of ADC channels.
    hal_ll_adc_set_subchannel( map->base, map->pin );

    // Async Clock Output Enable.
    base->cfg2 |= HAL_LL_ADC_ASYNC_CLOCK_ENABLE;

}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    volatile uint32_t port_name = hal_ll_gpio_port_base(hal_ll_gpio_port_index(map->pin));

    hal_ll_gpio_analog_input( &port_name,
                              hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_enable_clock( map->module_index );

    hal_ll_adc_hw_init( map->base, map->resolution, map );

}

// -------------------------------------------------------------------------- END
