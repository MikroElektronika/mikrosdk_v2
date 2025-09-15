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
#include "hal_ll_mstpcr.h"

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

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num(_module_num)      (_module_num - 1)

#define CLK_APBCLK0_EADCCKEN_OFFSET             (28)

#define CLK_CLKDIV0_EADCDIV_OFFSET              (16)
#define CLK_CLKDIV0_EADCDIV_MASK                ( 0xFFUL << CLK_CLKDIV0_EADCDIV_OFFSET )

#define SYS_IPRST1_EADCRST_OFFSET               (28)

#define ADC_DAT_RESULT_MASK                     0xFFFFUL
#define ADC_DAT_8BIT_RESULT_MASK                0x00FFUL
#define ADC_DAT_10BIT_RESULT_MASK               0x03FFUL

#define ADC_CTL_ADCEN_OFFSET                    (0)
#define ADC_CTL_ADCRST_OFFSET                   (1)
#define ADC_CTL_ADCIEN_OFFSET                   (2)
#define ADC_CTL_RESSEL_OFFSET                   (6)
#define ADC_CTL_DIFFEN_OFFSET                   (8)

#define ADC_SCTL_CHSEL_OFFSET                   (0)
#define ADC_SCTL_TRGSEL_OFFSET                  (16)
#define ADC_SCTL_TRGSEL_MASK                    ( 0xFUL << ADC_SCTL_TRGSEL_OFFSET )

#define ADC_STATUS2_ADIF0_OFFSET                (0)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    uint32_t dat[19];               /*!< [0x0000~0x0048] ADC Data Register n for Sample Module n, n=0~18           */
    uint32_t curdat;                /*!< [0x004c] ADC PDMA Current Transfer Data Register                          */
    uint32_t ctl;                   /*!< [0x0050] ADC Control Register                                             */
    uint32_t swtrg;                 /*!< [0x0054] ADC Sample Module Software Start Register                        */
    uint32_t pendsts;               /*!< [0x0058] ADC Start of Conversion Pending Flag Register                    */
    uint32_t ovsts;                 /*!< [0x005c] ADC Sample Module Start of Conversion Overrun Flag Register      */
    uint32_t _unused0[8];
    uint32_t sctl[19];              /*!< [0x0080~0x00c8]  ADC Sample Module n Control Register, n=0~18             */
    uint32_t _unused1[1];
    uint32_t intsrc[4];             /*!< [0x00d0~0x00dc]  ADC interrupt n Source Enable Control Register, n=0~3    */
    uint32_t cmp[4];                /*!< [0x00e0~0x00ec]  ADC Result Compare Register n, n=0~3                     */
    uint32_t status0;               /*!< [0x00f0] ADC status Register 0                                            */
    uint32_t status1;               /*!< [0x00f4] ADC status Register 1                                            */
    uint32_t status2;               /*!< [0x00f8] ADC status Register 2                                            */
    uint32_t status3;               /*!< [0x00fc] ADC status Register 3                                            */
    uint32_t ddat[4];               /*!< [0x0100~0x010c]  ADC Double Data Register n for Sample Module n, n=0~3    */
    uint32_t pwrm;                  /*!< [0x0110] ADC Power Management Register                                    */
    uint32_t calctl;                /*!< [0x0114] ADC Calibration Control Register                                 */
    uint32_t caldwrd;               /*!< [0x0118] ADC Calibration Load Word Register                               */
    uint32_t _unused2[5];
    uint32_t pdmactl;               /*!< [0x0130] ADC PDMA Control Register                                        */
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
 * @brief  Initialize hardware ADC module.
 * @details ADC hardware initialization.
 * @param  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
 * @return None
 */
static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution, uint8_t channel );

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
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
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
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_12BIT_RES;
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
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base;

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }
    
    uint8_t sample_mod = hal_ll_adc_hw_specifics_map_local->channel;

    set_reg_bit( &( base->ctl ), ADC_CTL_ADCEN_OFFSET );
    Delay_500us();

    set_reg_bit( &( base->swtrg ), sample_mod );
    Delay_500us();

    while( !check_reg_bit( &( base->status2 ), ADC_STATUS2_ADIF0_OFFSET ) );

    *readDatabuf = read_reg_bits( &( base->dat[sample_mod] ), ADC_DAT_RESULT_MASK );
    set_reg_bit( &( base->status2 ), ADC_STATUS2_ADIF0_OFFSET );

    clear_reg_bit( &( base->ctl ), ADC_CTL_ADCEN_OFFSET );

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

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_adc_clock_enable( void ) {
    clear_reg_bits( CLK_CLKDIV0, CLK_CLKDIV0_EADCDIV_MASK );
    set_reg_bit( CLK_APBCLK0, CLK_APBCLK0_EADCCKEN_OFFSET );
}

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

static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution, uint8_t channel ) {
    uint8_t sample_mod = channel;

    set_reg_bits( &( base->ctl ), resolution << ADC_CTL_RESSEL_OFFSET );           //resolution can't be set to 6, 8, or 10 bit

    set_reg_bits( &( base->ctl ), 0xFUL << ADC_CTL_ADCIEN_OFFSET );

    clear_reg_bit( &( base->ctl ), ADC_CTL_DIFFEN_OFFSET );


    set_reg_bits( &( base->sctl[sample_mod] ), sample_mod << ADC_SCTL_CHSEL_OFFSET );
    clear_reg_bits( &( base->sctl[sample_mod] ), ADC_SCTL_TRGSEL_MASK );

    set_reg_bit( &( base->intsrc[0] ), sample_mod );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_adc_clock_enable();

    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t* )hal_ll_adc_get_base_struct( map->base );

    set_reg_bit( &( base->ctl ), ADC_CTL_ADCRST_OFFSET );

    set_reg_bit( SYS_IPRST1, SYS_IPRST1_EADCRST_OFFSET );
    clear_reg_bit( SYS_IPRST1, SYS_IPRST1_EADCRST_OFFSET );

    hal_ll_gpio_analog_input( map->pin );
    hal_ll_adc_hw_init( base, map->resolution, map->channel );
}

// ------------------------------------------------------------------------- END