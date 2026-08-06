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
#include "hal_ll_bit_control.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"
#include "hal_ll_mstpcr.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num(_module_num)      (_module_num - 1)

// ADC register fetch
#define ADC_REG(base, offset)  (*(volatile uint32_t *)((base) + (offset)))

// ADC instances
#define HAL_LL_ADC_INSTANCE_ADC0 0
#define HAL_LL_ADC_INSTANCE_ADC1 1

// Register address offsets
#define HAL_LL_ADC_ADCLKENR_REG_OFFSET                (0x000UL)
#define HAL_LL_ADC_ADCLKSR_REG_OFFSET                 (0x004UL)
#define HAL_LL_ADC_ADCLKCR_REG_OFFSET                 (0x008UL)
#define HAL_LL_ADC_ADMDR_REG_OFFSET                   (0x040ul)
#define HAL_LL_ADC_ADSGER_REG_OFFSET                  (0x048ul)
#define HAL_LL_ADC_ADSGCR0_REG_OFFSET                 (0x04Cul)
#define HAL_LL_ADC_ADCHCR_BASE_REG_OFFSET             (0x600ul)
#define HAL_LL_ADC_ADSSTR0_REG_OFFSET                 (0x240ul)
#define HAL_LL_ADC_ADCALSTR_REG_OFFSET                (0xC00ul)
#define HAL_LL_ADC_ADSTR_BASE_REG_OFFSET              (0xC20ul)
#define HAL_LL_ADC_ADSR_REG_OFFSET                    (0xC80ul)
#define HAL_LL_ADC_ADCALENDSR_REG_OFFSET              (0xC98ul)
#define HAL_LL_ADC_ADCALENDSCR_REG_OFFSET             (0xC9Cul)
#define HAL_LL_ADC_ADSCANENDSR_REG_OFFSET             (0xD50ul)
#define HAL_LL_ADC_ADSCANENDSCR_REG_OFFSET            (0xD54ul)
#define HAL_LL_ADC_ADDR0_REG_OFFSET                   (0x2000ul)
#define HAL_LL_ADC_ADDOPCRC_REG_OFFSET                (0x60Cul)

// Resolution values for ADDOPCRC register
#define HAL_LL_ADC_ADDOPCRC_10BIT_RES                 (0x30000UL)
#define HAL_LL_ADC_ADDOPCRC_12BIT_RES                 (0x20000UL)
#define HAL_LL_ADC_ADDOPCRC_14BIT_RES                 (0x10000UL)

#define HAL_LL_ADC_ADCHCR_REG_STRIDE                  (0x10ul)
#define HAL_LL_ADC_ADDOPCRC_REG_STRIDE                (0x10ul)
#define HAL_LL_ADC_ADDRN_REG_STRIDE                   (0x04ul)
#define HAL_LL_ADC_ADSTR_REG_STRIDE                   (0x04ul)

#define HAL_LL_ADC_ADDOPCRC_ADPRC_12BIT               (0x2ul << 16)
#define HAL_LL_ADC_ADDOPCRC_SIGNSEL_UNSIGNED          (0x1ul << 20)

// Bit positions and masks
#define HAL_LL_ADC_ADCALSTR_ADCALST_ALL               (0x7ul)
#define HAL_LL_ADC_ADCALSTR_UNIT1_POS                 (8)

#define HAL_LL_ADC_ADCHCR_AINMD                       (15)
#define HAL_LL_ADC_ADCHCR_AINMD_SINGLE_ENDED          (0x0UL)
#define HAL_LL_ADC_ADCHCR_CNVCS_POS                   (8)
#define HAL_LL_ADC_ADCHCR_SGSEL_GROUP0                (0x01ul)
#define HAL_LL_ADC_ADCHCR_SSTSEL_POS                  (16)
#define HAL_LL_ADC_ADCHCR_SSTSEL_TABLE0               (0x0UL)

#define HAL_LL_ADC_ADCLKCR_CLKSEL_MASK                (0x3UL)
#define HAL_LL_ADC_ADCLKCR_CLKSEL_PCLKA               (0x2UL)
#define HAL_LL_ADC_ADCLKCR_DIVR_DIV3                  (0x2UL)
#define HAL_LL_ADC_ADCLKCR_DIVR_MASK                  (0x70000UL)
#define HAL_LL_ADC_ADCLKCR_DIVR_POS                   (16)

#define HAL_LL_ADC_ADCLKENR_CLKEN                     (0)

#define HAL_LL_ADC_ADCLKSR_CLKSR                      (0)

#define HAL_LL_ADC_ADDR_DATA_MASK                     (0xFFFUL)

#define HAL_LL_ADC_ADMDR_MODE_MASK                    (0xFUL)
#define HAL_LL_ADC_ADMDR_UNIT1_POS                    (8)

#define HAL_LL_ADC_ADSCANENDSCR_CLEAR                 (0x1UL)

#define HAL_LL_ADC_ADSGCR0_GROUP_SEL_MASK             (0x3UL)
#define HAL_LL_ADC_ADSGCR0_UNIT_SEL_POS               (0)

#define HAL_LL_ADC_ADSGER_SGE0_POS                    (0)

#define HAL_LL_ADC_ADSR_ADACT0                        (0)
#define HAL_LL_ADC_ADSR_ADACT1                        (1)
#define HAL_LL_ADC_ADSR_CALACT0                       (16)
#define HAL_LL_ADC_ADSR_CALACT1                       (17)

#define HAL_LL_ADC_ADSSTR0_SAMPLING_TIME_DEFAULT      (50UL)

#define HAL_LL_ADC_ADSTR_ADST_START                   (0x1UL)

#define HAL_LL_ADC_SCAN_GROUP_0                       (0ul)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL, (handle_t *) NULL, false };

/**
 *  Return values.
 */
typedef enum {
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = (-1)
} hal_ll_adc_err_t;

/*!< @brief ADC hw specific module values. */
typedef struct {
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

// ---------------------------------------------------------- PRIVATE VARIABLES
/**
 * @brief Array of maps holding information for configuring hardware.
 */
static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT + 1] = {
    #ifdef ADC_MODULE_0
    {HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_PIN_NC,
     HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT,
     0, HAL_LL_ADC_RESOLUTION_DEFAULT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Check if pins are adequate.
  * @Details Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[in]  *index - ADC map index value.
  * @return hal_ll_pin_name_t Module index based on pin.
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index,
                                                hal_ll_adc_handle_register_t *handle_map );

/**
  * @brief  Maps new-found module specific values.
  * @details Maps pin name, register address and channel from
  *          analog register list to module in hardware specific map.
  * @param[in]  module_index ADC HW module index -- 0,1,2... Index in hal_ll_adc_hw_specifics_map,
  * destination of copying.
  * @param[in]  index  Pointer with ADC pin map index value. Index in hal_ll_analog_in_register_list
  * source of copying information
  * @return  None
  */
static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index );

/**
  * @brief  Get local hardware specific map.
  * @details Checks handle value and returns address of adequate
  * hal_ll_adc_hw_specifics_map array element.
  * @param[in]  handle - Object specific context handler.
  * @return address of a member in hal_ll_adc_hw_specifics_map, either a correct member
  * or an 'error' terminating member in map.
  */
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Enable or disable the ADC hardware module.
  *
  * Controls the clock and power state of the specified ADC hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
static void hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Returns the ADC module index for a given channel.
  *
  * This function determines which ADC module corresponds to the specified channel.
  * It returns the module index based on the channel number provided.
  *
  * @param[in]  channel - ADC channel number.
  * @return The index of the ADC module.
  */
static uint8_t hal_ll_adc_get_unit_for_channel( uint8_t channel );

/**
  * @brief  Initialize hardware ADC module.
  * @details ADC hardware initialization.
  * @param  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None
  */
static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Initialize ADC module @p map.
  * @details from @p map, uses pin information to set it as analog & sets
  * @param[in]  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None.
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin,
                                        hal_ll_adc_voltage_reference_t vref_input,
                                        hal_ll_adc_resolution_t resolution,
                                        hal_ll_adc_handle_register_t *handle_map,
                                        uint8_t *hal_module_id ) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if (( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_10BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_14BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_16BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[ pin_check_result ].pin != pin ) {
        hal_ll_adc_map_pin( pin_check_result, &index );
        handle_map[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle =
            ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ].hal_ll_adc_handle =
            ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle =
                    ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;

    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_10BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_14BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_16BIT_RES_VAL;
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
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
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
    uint32_t reg;

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    write_reg( &ADC_REG( hal_ll_adc_hw_specifics_map_local->base, HAL_LL_ADC_ADSTR_BASE_REG_OFFSET +
               HAL_LL_ADC_ADSTR_REG_STRIDE * HAL_LL_ADC_SCAN_GROUP_0 ), HAL_LL_ADC_ADSTR_ADST_START );

    while ( !check_reg_bit( &ADC_REG( hal_ll_adc_hw_specifics_map_local->base,
               HAL_LL_ADC_ADSCANENDSR_REG_OFFSET ), HAL_LL_ADC_SCAN_GROUP_0 ) ) {
        /* poll SCENDF0 until scan group 0 finishes */
    }

    write_reg( &ADC_REG( hal_ll_adc_hw_specifics_map_local->base, HAL_LL_ADC_ADSCANENDSCR_REG_OFFSET ), HAL_LL_ADC_ADSCANENDSCR_CLEAR );

    reg = read_reg( &ADC_REG( hal_ll_adc_hw_specifics_map_local->base, HAL_LL_ADC_ADDR0_REG_OFFSET +
               HAL_LL_ADC_ADDRN_REG_STRIDE * hal_ll_adc_hw_specifics_map_local->channel ) );

    *readDatabuf = (uint16_t)( reg & HAL_LL_ADC_ADDR_DATA_MASK );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local =
                    hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;

        hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_local, false );

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin,
                                                hal_ll_adc_pin_id *index,
                                                hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size =
        ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );
    uint16_t pin_index = 0;
    uint8_t  index_counter = 0;
    uint8_t  hal_ll_module_id = 0;

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
    hal_ll_adc_hw_specifics_map[module_index].pin =
                hal_ll_analog_in_register_list[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel =
                hal_ll_analog_in_register_list[ index->pin_an[module_index] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count =
                    sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));
    static uint8_t hal_ll_module_error =
                    sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( _MSTPCRD, MSTPCRD_MSTPD21_POS ); // Release module-stop -- enable ADC16H
    } else {
        set_reg_bit( _MSTPCRD, MSTPCRD_MSTPD21_POS );   // Assert module-stop -- disable ADC16H
    }
}

static uint8_t hal_ll_adc_get_unit_for_channel( uint8_t channel ) {
    if( ( HAL_LL_ADC_CHANNEL_5 < channel && HAL_LL_ADC_CHANNEL_12 > channel ) ||
        HAL_LL_ADC_CHANNEL_13 == channel || HAL_LL_ADC_CHANNEL_15 == channel )
        return HAL_LL_ADC_INSTANCE_ADC1;
    else
        return HAL_LL_ADC_INSTANCE_ADC0;
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    uint8_t unit = hal_ll_adc_get_unit_for_channel( map->channel );
    uint8_t adact_bit   = unit ? HAL_LL_ADC_ADSR_ADACT1  : HAL_LL_ADC_ADSR_ADACT0;
    uint8_t calact_bit  = unit ? HAL_LL_ADC_ADSR_CALACT1 : HAL_LL_ADC_ADSR_CALACT0;
    uint8_t calendf_bit = unit;
    uint32_t adcalst_value = HAL_LL_ADC_ADCALSTR_ADCALST_ALL << ( unit ? HAL_LL_ADC_ADCALSTR_UNIT1_POS : 0 );

    // Source clock - PCLKA; divisor ratio - 1/3
    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADCLKCR_REG_OFFSET ),
               HAL_LL_ADC_ADCLKCR_CLKSEL_PCLKA | ( HAL_LL_ADC_ADCLKCR_DIVR_DIV3 << HAL_LL_ADC_ADCLKCR_DIVR_POS ) );

    // Supply ADCLK
    set_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADCLKENR_REG_OFFSET ), HAL_LL_ADC_ADCLKENR_CLKEN );
    while ( !check_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADCLKSR_REG_OFFSET ), HAL_LL_ADC_ADCLKSR_CLKSR ) ) {
        // Wait for ADCLK status bit to be set
    }

    // Mode selection - SAR mode - single scan mode
    clear_reg_bits( &ADC_REG( map->base, HAL_LL_ADC_ADMDR_REG_OFFSET ),
                    unit ? ( HAL_LL_ADC_ADMDR_MODE_MASK << HAL_LL_ADC_ADMDR_UNIT1_POS ) : HAL_LL_ADC_ADMDR_MODE_MASK );

    // Select scan group 0
    clear_reg_bits( &ADC_REG( map->base, HAL_LL_ADC_ADSGCR0_REG_OFFSET ), HAL_LL_ADC_ADSGCR0_GROUP_SEL_MASK );
    if ( unit ) {
        set_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADSGCR0_REG_OFFSET ), HAL_LL_ADC_ADSGCR0_UNIT_SEL_POS );
    } else {
        clear_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADSGCR0_REG_OFFSET ), HAL_LL_ADC_ADSGCR0_UNIT_SEL_POS );
    }

    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADCHCR_BASE_REG_OFFSET + HAL_LL_ADC_ADCHCR_REG_STRIDE * map->channel ),
               ( map->channel << HAL_LL_ADC_ADCHCR_CNVCS_POS )                          |
               ( HAL_LL_ADC_ADCHCR_AINMD_SINGLE_ENDED << HAL_LL_ADC_ADCHCR_AINMD )      |
               ( HAL_LL_ADC_ADCHCR_SGSEL_GROUP0 )                                       |
               ( HAL_LL_ADC_ADCHCR_SSTSEL_TABLE0 << HAL_LL_ADC_ADCHCR_SSTSEL_POS ) );

    if ( HAL_ADC_10BIT_RES_VAL == map->resolution ) {
        write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADDOPCRC_REG_OFFSET ), HAL_LL_ADC_ADDOPCRC_10BIT_RES );
    } else if ( HAL_ADC_12BIT_RES_VAL == map->resolution ) {
        write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADDOPCRC_REG_OFFSET ), HAL_LL_ADC_ADDOPCRC_12BIT_RES );
    } else if ( HAL_ADC_14BIT_RES_VAL == map->resolution ) {
        write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADDOPCRC_REG_OFFSET ), HAL_LL_ADC_ADDOPCRC_14BIT_RES );
    } else if ( HAL_ADC_16BIT_RES_VAL == map->resolution ) {
        clear_reg( &ADC_REG( map->base, HAL_LL_ADC_ADDOPCRC_REG_OFFSET ) );
    }

    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADSSTR0_REG_OFFSET ), HAL_LL_ADC_ADSSTR0_SAMPLING_TIME_DEFAULT );

    while ( check_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADSR_REG_OFFSET ), adact_bit ) ||
            check_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADSR_REG_OFFSET ), calact_bit )
        ) {
        // Wait until the target unit is idle
    }

    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADDOPCRC_REG_OFFSET + HAL_LL_ADC_ADDOPCRC_REG_STRIDE * map->channel ),
               HAL_LL_ADC_ADDOPCRC_ADPRC_12BIT | HAL_LL_ADC_ADDOPCRC_SIGNSEL_UNSIGNED );

    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADCALSTR_REG_OFFSET ), adcalst_value );

    while ( !check_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADCALENDSR_REG_OFFSET ), calendf_bit ) ) {
        // Wait for calibration end flag to be set
    }

    // Clear calibration end flag
    write_reg( &ADC_REG( map->base, HAL_LL_ADC_ADCALENDSCR_REG_OFFSET ), ( 1UL << calendf_bit ) );

    // Scan group 0 enable
    set_reg_bit( &ADC_REG( map->base, HAL_LL_ADC_ADSGER_REG_OFFSET ), HAL_LL_ADC_ADSGER_SGE0_POS );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    // Enable ADC operation.
    hal_ll_adc_module_enable( map, true );

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                              hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_hw_init( map );
}

// ------------------------------------------------------------------------- END
