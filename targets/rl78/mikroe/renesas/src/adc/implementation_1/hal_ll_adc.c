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

#include "delays.h"
#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"
#include "hal_ll_per.h"

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

/*!< @brief Volatile register accessors, the bit control macros don't add volatile themselves. */
#define hal_ll_adc_reg8(_addr)        ( ( volatile uint8_t * )( _addr ) )
#define hal_ll_adc_reg16(_addr)       ( ( volatile uint16_t * )( _addr ) )

/*!< @brief CPU/peripheral clock (fCLK) used for the conversion clock divider. */
#ifndef HAL_LL_ADC_FCLK_HZ
#define HAL_LL_ADC_FCLK_HZ            ( 32000000UL ) /* TODO: replace with real fCLK source */
#endif

// ADC register addresses
#define HAL_LL_ADC_PER0_ADDR          ( 0xF00F0UL )
#define HAL_LL_ADC_ADM0_ADDR          ( 0xFFF30UL )
#define HAL_LL_ADC_ADM1_ADDR          ( 0xFFF32UL )
#define HAL_LL_ADC_ADM2_ADDR          ( 0xF0010UL )
#define HAL_LL_ADC_ADS_ADDR           ( 0xFFF31UL )
#define HAL_LL_ADC_ADUL_ADDR          ( 0xF0011UL )
#define HAL_LL_ADC_ADLL_ADDR          ( 0xF0012UL )
#define HAL_LL_ADC_ADTES_ADDR         ( 0xF0013UL )
#define HAL_LL_ADC_ADCR0_ADDR         ( 0xF0020UL )
#define HAL_LL_ADC_ADCR0H_ADDR        ( 0xF0021UL )

// ADC bit positions and masks
#define HAL_LL_ADC_PER0_ADCEN_BIT     ( 5 )
#define HAL_LL_ADC_ADM0_ADCS_BIT      ( 7 )
#define HAL_LL_ADC_ADM0_ADCE_BIT      ( 0 )
#define HAL_LL_ADC_ADM0_FR_SHIFT      ( 3 )     /* Conversion clock, bits 5:3 */
#define HAL_LL_ADC_ADM0_LV_NORMAL1    ( 0x00 )  /* Normal mode 1, LV1:LV0 = 00 */
#define HAL_LL_ADC_ADM0_LV_LOW1       ( 0x04 )  /* Low-voltage mode 1, LV1:LV0 = 10 */
#define HAL_LL_ADC_ADM1_ADSCM         ( 0x20 )  /* One-shot conversion mode */
#define HAL_LL_ADC_ADM1_ADLSP         ( 0x08 )  /* 1 MHz <= fCLK <= 4 MHz */

#define HAL_LL_ADC_ADM2_ADTYP_10BIT   ( 0x00 )
#define HAL_LL_ADC_ADM2_ADTYP_8BIT    ( 0x01 )
#define HAL_LL_ADC_ADM2_ADTYP_12BIT   ( 0x02 )
#define HAL_LL_ADC_ADM2_ADREFP_EXT    ( 0x40 )  /* P21/AVREFP pin */
#define HAL_LL_ADC_ADM2_ADREFP_INT    ( 0x80 )  /* Internal reference */
#define HAL_LL_ADC_ADM2_ADREFP_DISCH  ( 0xC0 )  /* Required before switching to internal ref */

#define HAL_LL_ADC_ADS_CHANNEL_MASK   ( 0x1F )
#define HAL_LL_ADC_10BIT_SHIFT        ( 6 )     /* 10-bit result is left aligned in ADCR0 */

#define HAL_LL_ADC_FAD_MAX_HZ         ( 2000000UL ) /* Keeps fAD in 1-2 MHz, valid for every mode */
#define HAL_LL_ADC_ADLSP_MAX_HZ       ( 4000000UL )
#define HAL_LL_ADC_FR_FCLK            ( 5 )     /* FR2:FR0 = 101 -> fAD = fCLK */

/*!< @brief P21 is shared between ANI0 and AVREFP. */
#define HAL_LL_ADC_AVREFP_PIN         ( GPIO_P021 )

#define HAL_LL_ADC_STOP_WAIT_US       ( 5 )  /* 0.2us before FR/LV change, 5us before re-enabling */
#define HAL_LL_ADC_REF_STABILIZE_US   ( 5 )  /* Reference voltage stabilization time A */
#define HAL_LL_ADC_STABILIZATION_US   ( 3 )  /* Time B: 1us + 2 fAD cycles, fAD >= 1 MHz */
#define HAL_LL_ADC_DISCHARGE_US       ( 1 )  /* Reference discharge time */

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
  * @brief  Set the conversion clock (FR2:FR0, ADLSP), conversion mode and operation voltage mode.
  * @param[in]  lv_mode - LV1:LV0 bits, already shifted into ADM0 position.
  * @return None
  */
static void hal_ll_adc_set_clock( uint8_t lv_mode );

/**
  * @brief  Set the ADM2 positive reference source (AVREFP pin or internal) and resolution, 16.3.6.
  * @param[in]  vref - Voltage reference.
  * @param[in]  adm2_adtyp_resolution - ADTYP1:ADTYP0 bits.
  * @return None
  */
static void hal_ll_adc_set_reference( hal_ll_adc_voltage_reference_t vref, uint8_t adm2_adtyp_resolution );

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
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_10BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_8BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            // ANI0 and AVREFP share P21, 16.3.9 caution 5.
            if ( HAL_LL_ADC_AVREFP_PIN == pin ) {
                return HAL_LL_ADC_UNSUPPORTED_VREF;
            }
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
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_10BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_8BIT_RES_VAL;
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
            // ANI0 and AVREFP share P21, 16.3.9 caution 5.
            if ( HAL_LL_ADC_AVREFP_PIN == hal_ll_adc_hw_specifics_map_local->pin ) {
                return HAL_LL_ADC_UNSUPPORTED_VREF;
            }
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

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADS_ADDR ),
               ( uint8_t ) ( hal_ll_adc_hw_specifics_map_local->channel & HAL_LL_ADC_ADS_CHANNEL_MASK ) );

    if ( !check_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), HAL_LL_ADC_ADM0_ADCE_BIT ) ) {
        set_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), HAL_LL_ADC_ADM0_ADCE_BIT );
        // Stabilization time B is needed on the ADCE 0->1 transition.
        Delay_us( HAL_LL_ADC_STABILIZATION_US );
    }

    set_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), HAL_LL_ADC_ADM0_ADCS_BIT );

    // One-shot mode: ADCS self-clears when conversion ends.
    while ( check_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), HAL_LL_ADC_ADM0_ADCS_BIT ) );

    switch ( hal_ll_adc_hw_specifics_map_local->resolution ) {
        case HAL_ADC_8BIT_RES_VAL:
            *readDatabuf = read_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADCR0H_ADDR ) );
            break;
        case HAL_ADC_10BIT_RES_VAL:
            *readDatabuf = read_reg( hal_ll_adc_reg16( HAL_LL_ADC_ADCR0_ADDR ) ) >> HAL_LL_ADC_10BIT_SHIFT;
            break;
        default:
            *readDatabuf = read_reg( hal_ll_adc_reg16( HAL_LL_ADC_ADCR0_ADDR ) ) & HAL_ADC_12BIT_RES_VAL;
            break;
    }

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
    if ( false == hal_ll_state ) {
        // Stop conversion before gating the clock
        write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), 0 );

        clear_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_PER0_ADDR ), HAL_LL_ADC_PER0_ADCEN_BIT );

        return;
    }

    // ADCEN must be set before any other ADC register is written, 16.3.1.
    set_reg_bit( hal_ll_adc_reg8( HAL_LL_ADC_PER0_ADDR ), HAL_LL_ADC_PER0_ADCEN_BIT );
}

static void hal_ll_adc_set_clock( uint8_t lv_mode ) {
    uint8_t div_shift = 0;
    uint8_t adm1 = HAL_LL_ADC_ADM1_ADSCM;

    // fCLK <= 4 MHz must be flagged through ADLSP, Table 16-3.
    if ( HAL_LL_ADC_ADLSP_MAX_HZ >= HAL_LL_ADC_FCLK_HZ ) {
        adm1 |= HAL_LL_ADC_ADM1_ADLSP;
    }

    // Smallest divider (fCLK/1 ... fCLK/32) that keeps fAD <= 2 MHz.
    while ( ( HAL_LL_ADC_FAD_MAX_HZ < ( HAL_LL_ADC_FCLK_HZ >> div_shift ) ) &&
            ( HAL_LL_ADC_FR_FCLK > div_shift ) ) {
        div_shift++;
    }

    // Software trigger no-wait, one-shot.
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM1_ADDR ), adm1 );
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ),
               ( uint8_t )( ( ( HAL_LL_ADC_FR_FCLK - div_shift ) << HAL_LL_ADC_ADM0_FR_SHIFT ) | lv_mode ) );
}

static void hal_ll_adc_set_reference( hal_ll_adc_voltage_reference_t vref, uint8_t adm2_adtyp_resolution ) {
    if ( HAL_LL_ADC_VREF_INTERNAL == vref ) {
        // Discharge first when switching to the internal reference, 16.3.6.
        write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM2_ADDR ), HAL_LL_ADC_ADM2_ADREFP_DISCH | adm2_adtyp_resolution );
        Delay_us( HAL_LL_ADC_DISCHARGE_US );

        write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM2_ADDR ), HAL_LL_ADC_ADM2_ADREFP_INT | adm2_adtyp_resolution );
    } else {
        write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM2_ADDR ), HAL_LL_ADC_ADM2_ADREFP_EXT | adm2_adtyp_resolution );
    }

    // Reference voltage stabilization time A.
    Delay_us( HAL_LL_ADC_REF_STABILIZE_US );
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    uint8_t adm2_adtyp_resolution;

    // Stop conversion (ADCS = ADCE = 0) before changing FR/LV, ADM1 and ADM2.
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADM0_ADDR ), 0 );
    Delay_us( HAL_LL_ADC_STOP_WAIT_US );

    // Internal reference is only allowed in low-voltage mode, Table 16-3 caution 5.
    hal_ll_adc_set_clock( ( HAL_LL_ADC_VREF_INTERNAL == map->vref_input ) ?
                          HAL_LL_ADC_ADM0_LV_LOW1 : HAL_LL_ADC_ADM0_LV_NORMAL1 );

    switch ( map->resolution ) {
        case HAL_ADC_8BIT_RES_VAL:
            adm2_adtyp_resolution = HAL_LL_ADC_ADM2_ADTYP_8BIT;
            break;
        case HAL_ADC_10BIT_RES_VAL:
            adm2_adtyp_resolution = HAL_LL_ADC_ADM2_ADTYP_10BIT;
            break;
        case HAL_ADC_12BIT_RES_VAL:
        default:
            adm2_adtyp_resolution = HAL_LL_ADC_ADM2_ADTYP_12BIT;
            break;
    }

    // Disable result range checking so every conversion is stored and flagged.
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADUL_ADDR ), 0xFF );
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADLL_ADDR ), 0x00 );
    write_reg( hal_ll_adc_reg8( HAL_LL_ADC_ADTES_ADDR ), 0x00 );

    // ADREFM = 0 (VSS), ADRCK = 0, AWC = 0.
    hal_ll_adc_set_reference( map->vref_input, adm2_adtyp_resolution );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( ( uint32_t * ) hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                               hal_ll_gpio_pin_mask( map->pin ) );

    // AVREFP pin has to be in analog input mode, 16.3.6 caution 3.
    if ( HAL_LL_ADC_VREF_EXTERNAL == map->vref_input ) {
        hal_ll_gpio_analog_input( ( uint32_t * ) hal_ll_gpio_port_base( hal_ll_gpio_port_index( HAL_LL_ADC_AVREFP_PIN ) ),
                                   hal_ll_gpio_pin_mask( HAL_LL_ADC_AVREFP_PIN ) );
    }

    hal_ll_adc_module_enable( map, true );

    hal_ll_adc_hw_init( map );
}

// ------------------------------------------------------------------------- END
