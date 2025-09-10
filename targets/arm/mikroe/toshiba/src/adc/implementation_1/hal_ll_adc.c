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
#include "hal_ll_cg.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ( (hal_ll_adc_handle_register_t *) *handle )
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *) hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_adc_get_base_struct( _handle ) ( (hal_ll_adc_base_handle_t *) _handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ( (hal_ll_adc_hw_specifics_map_t *) ( (hal_ll_adc_handle_register_t *)\
                                            ( ( (hal_ll_adc_handle_register_t *) ( handle ) ) ->hal_ll_adc_handle ) ) -> hal_ll_adc_handle )->base

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num( _module_num ) ( _module_num - 1 )

#define hal_ll_gpio_port_get_port_index( __index ) ( (uint8_t) ( __index & 0xF0 ) >> 4 )

#define HAL_LL_CG_ADC0_BIT         2
#define HAL_LL_CG_ADC1_BIT         3
#define HAL_LL_CG_ADC2_BIT         4
#define HAL_LL_CG_ADCKEN0_BIT      16
#define HAL_LL_CG_ADCKEN1_BIT      17
#define HAL_LL_CG_ADCKEN2_BIT      18
#define HAL_LL_MOD0_DACON          0x01
#define HAL_LL_CR0_ADEN            0x80
#define HAL_LL_CR0_SGL             0x02
#define HAL_LL_ST_SNGF             0x04
#define HAL_LL_MOD1_CONVERSION_CFG 0x00306122
#define HAL_LL_MOD2_CONVERSION_CFG 0x00000000
#define HAL_LL_CLK_EXAZ0           0x00000008U
#define HAL_LL_EXAZSEL_MASK        0x0C
#define HAL_LL_TSET_SW_SINGLE_MODE 0b10
#define HAL_LL_TSET_MODE_SHIFT     5
#define HAL_LL_ADC_CHANNEL_MASK    0x1F
#define HAL_LL_ADC_RESULT_SHIFT    4
#define HAL_LL_ADC_RESULT_MASK     0x0FFF

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL,
                                                                              (handle_t *) NULL,
                                                                              false };

/*!< @brief ADC register structure. */
typedef struct {
    uint32_t cr0;          // 0x0000 - Control Register0
    uint32_t cr1;          // 0x0004 - Control Register1
    uint32_t st;           // 0x0008 - Status Register
    uint32_t clk;          // 0x000C - Conversion Clock Setting Register
    uint32_t mod0;         // 0x0010 - Mode Setting Reg0
    uint32_t mod1;         // 0x0014 - Mode Setting Reg1
    uint32_t mod2;         // 0x0018 - Mode Setting Reg2
    uint32_t reserved0;    // 0x001C - Reserved
    uint32_t cmpen;        // 0x0020 - Monitor Function Enable Register
    uint32_t cmpcr0;       // 0x0024 - Monitor Function Setting Reg0
    uint32_t cmpcr1;       // 0x0028 - Monitor Function Setting Reg1
    uint32_t cmp0;         // 0x002C - Conversion Result Comparison Reg0
    uint32_t cmp1;         // 0x0030 - Conversion Result Comparison Reg1
    uint32_t _unused1[ 3 ];  // 0x0034-0x003C - Reserved
    uint32_t psel[ 12 ];     // 0x0040-0x006C - PMD Trigger Input Selection Reg0~Reg11
    uint32_t pints[ 8 ];     // 0x0070-0x008C - PMD Trigger Interrupt Selection Reg0~Reg7
    uint32_t pregs;        // 0x0090 - PMD Trigger Storage Selection Register
    uint32_t _unused2[ 2 ];  // 0x0094-0x0098 - Reserved
    uint32_t exazsel;      // 0x009C - AIN Sampling Time Selection Register
    uint32_t pset[ 8 ];      // 0x00A0-0x00BC - PMD Trigger Program Reg0~Reg7
    uint32_t tset[ 24 ];     // 0x00C0-0x016C - General Purpose Start-up Factor Program Reg0~Reg23
    uint32_t _unused3[ 8 ];  // 0x0120-0x013C - Reserved
    uint32_t reg[ 24 ];      // 0x0140-0x019C - Conversion Result Storage Reg0~Reg23
} hal_ll_adc_base_handle_t;

/**
 *  Return values.
 */
typedef enum {
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = ( -1 )
} hal_ll_adc_err_t;

/*!< @brief ADC hw specific module values. */
typedef struct {
    uint16_t pin_an[ ADC_MODULE_COUNT ];
} hal_ll_adc_pin_id;

// ---------------------------------------------------------- PRIVATE VARIABLES
/**
 * @brief Array of maps holding information for configuring hardware.
 */
static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ ADC_MODULE_COUNT + 1 ] = {
    #ifdef ADC_MODULE_0
    { HAL_LL_ADC0_BASE_ADDR,
      hal_ll_adc_module_num( ADC_MODULE_0 ),
      HAL_LL_PIN_NC,
      HAL_LL_ADC_VREF_DEFAULT,
      0,
      HAL_LL_ADC_RESOLUTION_12_BIT,
      0xFF },
    #endif
    #ifdef ADC_MODULE_1
    { HAL_LL_ADC1_BASE_ADDR,
      hal_ll_adc_module_num( ADC_MODULE_1 ),
      HAL_LL_PIN_NC,
      HAL_LL_ADC_VREF_DEFAULT,
      0,
      HAL_LL_ADC_RESOLUTION_12_BIT,
      0xFF },
    #endif
    #ifdef ADC_MODULE_2
    { HAL_LL_ADC2_BASE_ADDR,
      hal_ll_adc_module_num( ADC_MODULE_2 ),
      HAL_LL_PIN_NC,
      HAL_LL_ADC_VREF_DEFAULT,
      0,
      HAL_LL_ADC_RESOLUTION_12_BIT,
      0xFF },
    #endif

    { HAL_LL_MODULE_ERROR,
      HAL_LL_MODULE_ERROR,
      HAL_LL_PIN_NC,
      HAL_LL_ADC_VREF_DEFAULT,
      0,
      HAL_LL_ADC_RESOLUTION_DEFAULT,
      0xFF }
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t  *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Get ADC channel mask from channel enumeration
 * @details Fast lookup table-based channel to mask conversion
 * @param[in] channel - ADC channel enumeration value  
 * @return uint8_t - Corresponding mask value (0-31) or 0xFF if not found
 */
static uint8_t hal_ll_adc_get_channel_mask( hal_ll_adc_channel_t channel );

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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map );

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
 * @brief  Initialize hardware ADC module.
 * @details ADC hardware initialization.
 * @param  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
 * @return None
 */
static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Initialize ADC module @p map.
  * @details from @p map, uses pin information to set it as analog & sets
  * @param[in]  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None.
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle( hal_ll_pin_name_t              pin,
                                         hal_ll_adc_voltage_reference_t vref_input,
                                         hal_ll_adc_resolution_t        resolution,
                                         hal_ll_adc_handle_register_t  *handle_map,
                                         uint8_t                       *hal_module_id ) {
    uint16_t          pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if ( ( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_14BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
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
    hal_ll_adc_hw_specifics_map_local              = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    hal_ll_adc_handle_register_t *hal_handle       = (hal_ll_adc_handle_register_t *) *handle;
    uint8_t                       pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle =
                    ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;

    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle                  = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if ( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_14BIT_RES_VAL;
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
    hal_ll_adc_hw_specifics_map_local              = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if ( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( vref_input ) {
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
    low_level_handle                  = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if ( NULL != low_level_handle->hal_ll_adc_handle ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle                  = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *base    = (hal_ll_adc_base_handle_t *) hal_ll_adc_hw_specifics_map_local->base;

    if ( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    if ( NULL == readDatabuf ) {
        return HAL_LL_ADC_ERROR;
    }

    // Get the channel number
    uint8_t channel = hal_ll_adc_hw_specifics_map_local->channel;
    if ( 0xFF == channel ) {
        return HAL_LL_ADC_WRONG_CHANNEL;
    }

    // Start single conversion
    base->cr0 = HAL_LL_CR0_ADEN | HAL_LL_CR0_SGL;

    // Wait for conversion to start
    while ( !( base->st & HAL_LL_ST_SNGF ) );

    // Wait for conversion to complete
    while ( ( base->st & HAL_LL_ST_SNGF ) );

    uint32_t result_reg = 0;
    if ( HAL_LL_ADC_CHANNEL_2 == channel ) {  // AINC02
        result_reg = base->reg[ 4 ];
    } else if ( HAL_LL_ADC_CHANNEL_3 == channel ) {  // AINC03
        result_reg = base->reg[ 5 ];
    } else {
        result_reg = base->reg[ 1 ];
    }

    // Extract 12-bit result
    *readDatabuf = (uint16_t) ( ( result_reg >> HAL_LL_ADC_RESULT_SHIFT ) & HAL_LL_ADC_RESULT_MASK );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(
        hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;

    if ( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;

        low_level_handle->hal_ll_adc_handle  = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t
hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size     = ( sizeof( hal_ll_analog_in_register_list )
                                           / sizeof( hal_ll_pin_channel_list_t ) );
    uint16_t              pin_index        = 0;
    uint8_t               index_counter    = 0;
    uint8_t               hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( pin == hal_ll_analog_in_register_list[pin_index].pin ) {
            // Get module number
            hal_ll_module_id = hal_ll_analog_in_register_list[ pin_index ].module_index;
            // Map pin name
            index->pin_an[ hal_ll_module_id ] = pin_index;

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
    hal_ll_adc_hw_specifics_map[ module_index ].pin =
                hal_ll_analog_in_register_list[ index->pin_an[ module_index ] ].pin;
    hal_ll_adc_hw_specifics_map[ module_index ].channel =
                hal_ll_analog_in_register_list[ index->pin_an[ module_index ] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t        hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    hal_ll_adc_base_handle_t *base          = (hal_ll_adc_base_handle_t *) hal_ll_adc_get_base_struct( map->base );
    hal_ll_cg_base_handle_t  *hal_ll_cg_reg = (hal_ll_cg_base_handle_t *) HAL_LL_CG_BASE_ADDR;

    uint8_t port = hal_ll_gpio_port_get_port_index( map->pin );

    set_reg_bit( &hal_ll_cg_reg->fsysmena, port );  // Enable clock for port J

    switch ( map->module_index ) {
        #ifdef ADC_MODULE_0
        case hal_ll_adc_module_num( ADC_MODULE_0 ):
            set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC0_BIT );    // Enable clock for ADC0 module
            set_reg_bit( &hal_ll_cg_reg->spclken, HAL_LL_CG_ADCKEN0_BIT );  // ADCKEN0
            break;
        #endif
        #ifdef ADC_MODULE_1
        case hal_ll_adc_module_num( ADC_MODULE_1 ):
            set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC1_BIT );    // Enable clock for ADC1 module
            set_reg_bit( &hal_ll_cg_reg->spclken, HAL_LL_CG_ADCKEN1_BIT );  // ADCKEN1
            break;
        #endif
        #ifdef ADC_MODULE_2
        case hal_ll_adc_module_num( ADC_MODULE_2 ):
            set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC2_BIT );    // Enable clock for ADC2 module
            set_reg_bit( &hal_ll_cg_reg->spclken, HAL_LL_CG_ADCKEN2_BIT );  // ADCKEN2
            break;
        #endif

        default:
            break;
    }

    uint8_t ain_mask = map->channel;

    // MOD0: Enable ADC (DACON=1), low-power off (RCUT=0)
    base->mod0 = HAL_LL_MOD0_DACON;  // DACON = 1

    // Wait 3 µs after DACON=1 for stabilization
    Delay_us( 3 );

    // Configure CLK with proper values: VADCLK=000 (SCLK=ADCLK/4=40MHz), EXAZ0=0001 (~0.96µs)
    base->clk  = HAL_LL_CLK_EXAZ0;
    base->mod1 = HAL_LL_MOD1_CONVERSION_CFG;  // AD conversion time 0.96µs at SCLK=40MHz
    base->mod2 = HAL_LL_MOD2_CONVERSION_CFG;

    // Clear EXAZSEL for channels to use EXAZ0 setting
    base->exazsel &= ~HAL_LL_EXAZSEL_MASK;

    // TRGS=0b10 (SW single), ENINT=0, channel in bits 0-4
    uint32_t tset_value = ( HAL_LL_TSET_SW_SINGLE_MODE << HAL_LL_TSET_MODE_SHIFT )
                        | ( ain_mask & HAL_LL_ADC_CHANNEL_MASK );

    if ( HAL_LL_ADC_CHANNEL_2 == ain_mask ) {  // AINC02
        base->tset[ 4 ] = tset_value;
    } else if ( HAL_LL_ADC_CHANNEL_3 == ain_mask ) {  // AINC03
        base->tset[ 5 ] = tset_value;
    } else {
        base->tset[ 1 ] = tset_value;
    }

    // Disable DMA requests
    base->cr1 = 0x00000000;
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                              hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_hw_init( map );
}

// ------------------------------------------------------------------------- END
