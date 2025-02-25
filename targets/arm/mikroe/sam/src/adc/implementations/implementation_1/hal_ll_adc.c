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
#define hal_ll_adc_module_num(_module_num) (_module_num)

#define HAL_LL_PID_AFEC1_BIT        8
#define HAL_LL_PID_AFEC0_BIT        29

#define HAL_LL_AFEC_CR_SWRST_BIT    0
#define HAL_LL_AFEC_CR_START_BIT    1

#define HAL_LL_AFEC_EMR_CMPSEL_BIT  3
#define HAL_LL_AFEC_MR_ONE_BIT      23
#define HAL_LL_AFEC_EMR_STM_BIT     25

#define HAL_LL_AFEC_EMR_NO_AVERAGE_MASK     0x00000000ul
#define HAL_LL_AFEC_ACR_PGAEN12_MASK        0x0000000Cul
#define HAL_LL_AFEC_COCR_OFFSET_MASK        0x00000200ul
#define HAL_LL_AFEC_EMR_LOW_RES_MASK        0x00010000ul
#define HAL_LL_AFEC_EMR_OSR16               0x00030000ul
#define HAL_LL_AFEC_EMR_OSR256              0x00050000ul

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/**
 *  ADC modules
 */
typedef enum
{
    HAL_LL_MODULE_ADC_DEFAULT = 0xFF,
    HAL_LL_MODULE_ADC_0 = 0,
    HAL_LL_MODULE_ADC_1 = 1,

    HAL_LL_MODULE_ADC_NONE
} hal_ll_adc_module_number_t;

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

/*!< @brief AFEC register structure. */
typedef struct
{
    hal_ll_base_addr_t cr;            /**< (AFEC Offset: 0x00) AFEC Control Register */
    hal_ll_base_addr_t mr;            /**< (AFEC Offset: 0x04) AFEC Mode Register */
    hal_ll_base_addr_t emr;           /**< (AFEC Offset: 0x08) AFEC Extended Mode Register */
    hal_ll_base_addr_t seq1r;         /**< (AFEC Offset: 0x0C) AFEC Channel Sequence 1 Register */
    hal_ll_base_addr_t seq2r;         /**< (AFEC Offset: 0x10) AFEC Channel Sequence 2 Register */
    hal_ll_base_addr_t cher;          /**< (AFEC Offset: 0x14) AFEC Channel Enable Register */
    hal_ll_base_addr_t chdr;          /**< (AFEC Offset: 0x18) AFEC Channel Disable Register */
    hal_ll_base_addr_t chsr;          /**< (AFEC Offset: 0x1C) AFEC Channel Status Register */
    hal_ll_base_addr_t lcdr;          /**< (AFEC Offset: 0x20) AFEC Last Converted Data Register */
    hal_ll_base_addr_t ier;           /**< (AFEC Offset: 0x24) AFEC Interrupt Enable Register */
    hal_ll_base_addr_t idr;           /**< (AFEC Offset: 0x28) AFEC Interrupt Disable Register */
    hal_ll_base_addr_t imr;           /**< (AFEC Offset: 0x2C) AFEC Interrupt Mask Register */
    hal_ll_base_addr_t isr;           /**< (AFEC Offset: 0x30) AFEC Interrupt Status Register */
    hal_ll_base_addr_t _unused1[6];   /** Reserved 0x34 - 0x4B **/
    hal_ll_base_addr_t over;          /**< (AFEC Offset: 0x4C) AFEC Overrun Status Register */
    hal_ll_base_addr_t cwr;           /**< (AFEC Offset: 0x50) AFEC Compare Window Register */
    hal_ll_base_addr_t cgr;           /**< (AFEC Offset: 0x54) AFEC Channel Gain Register */
    hal_ll_base_addr_t _unused2[2];   /** Reserved 0x58 - 0x5F **/
    hal_ll_base_addr_t diffr;         /**< (AFEC Offset: 0x60) AFEC Channel Differential Register */
    hal_ll_base_addr_t cselr;         /**< (AFEC Offset: 0x64) AFEC Channel Selection Register */
    hal_ll_base_addr_t cdr;           /**< (AFEC Offset: 0x68) AFEC Channel Data Register */
    hal_ll_base_addr_t cocr;          /**< (AFEC Offset: 0x6C) AFEC Channel Offset Compensation Register */
    hal_ll_base_addr_t tempmr;        /**< (AFEC Offset: 0x70) AFEC Temperature Sensor Mode Register */
    hal_ll_base_addr_t tempcwr;       /**< (AFEC Offset: 0x74) AFEC Temperature Compare Window Register */
    hal_ll_base_addr_t _unused3[7];   /** Reserved 0x78 - 0x93 **/
    hal_ll_base_addr_t acr;           /**< (AFEC Offset: 0x94) AFEC Analog Control Register */
} hal_ll_adc_base_handle_t;

/*!< @brief ADC hw specific module values */
typedef struct
{
    hal_ll_pin_name_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[] =
{
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
static inline void adc0_enable_clock();

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
  * @param  *base - ADC module base address.
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
hal_ll_err_t hal_ll_adc_register_handle( hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id )
{
    hal_ll_pin_name_t pin_check_result;
    hal_ll_adc_pin_id index = {HAL_LL_PIN_NC};

    if ( ( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_AFEC_EMR_LOW_RES_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_AFEC_EMR_NO_AVERAGE_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_AFEC_EMR_OSR16;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_AFEC_EMR_OSR256;
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
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    hal_ll_adc_handle_register_t *hal_handle = ( hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = ( handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution )
{
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    low_level_handle->init_ll_state = false;

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_AFEC_EMR_LOW_RES_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_AFEC_EMR_NO_AVERAGE_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_AFEC_EMR_OSR16;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_AFEC_EMR_OSR256;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input )
{
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

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

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value )
{
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *afec_regs = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    // Select the desired channel.
    write_reg( &afec_regs->cselr, hal_ll_adc_hw_specifics_map_local->channel );

    // Select default offset for the converted data.
    write_reg( &afec_regs->cocr, HAL_LL_AFEC_COCR_OFFSET_MASK );

    // Start conversion.
    set_reg_bit( &afec_regs->cr, HAL_LL_AFEC_CR_START_BIT );

    // Wait till data is converted.
    while ( !( check_reg_bit( &afec_regs->isr, hal_ll_adc_hw_specifics_map_local->channel ) ) );

    // Read the conversion result from converted data register.
    *readDatabuf = read_reg( &afec_regs->cdr );

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if ( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 0;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_AFEC_EMR_NO_AVERAGE_MASK;

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
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static inline void adc0_enable_clock()
{
    set_reg_bit( _PMC_PCER0, HAL_LL_PID_AFEC0_BIT );
}

static inline void adc1_enable_clock()
{
    set_reg_bit( _PMC_PCER1, HAL_LL_PID_AFEC1_BIT );
}

static void _hal_ll_adc_enable_clock( uint8_t module_index )
{
    switch ( module_index )
    {
        #ifdef ADC_MODULE_0
        case ( hal_ll_adc_module_num( ADC_MODULE_0 ) ):
            adc0_enable_clock();
            break;
        #endif
        #ifdef ADC_MODULE_1
        case ( hal_ll_adc_module_num( ADC_MODULE_1 ) ):
            adc1_enable_clock();
            break;
        #endif

        default:
            break;
    }
}

static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *afec_regs, uint32_t resolution )
{
    // Reset the AFEC module.
    set_reg_bit( &afec_regs->cr, HAL_LL_AFEC_CR_SWRST_BIT );

    // This bit must be always written.
    set_reg_bit( &afec_regs->mr, HAL_LL_AFEC_MR_ONE_BIT );

    // Set requested resolution.
    write_reg( &afec_regs->emr, resolution );

    // Set the single trigger mode.
    set_reg_bit( &afec_regs->emr, HAL_LL_AFEC_EMR_STM_BIT );

    // Enable gain amplifier.
    set_reg_bits( &afec_regs->acr, HAL_LL_AFEC_ACR_PGAEN12_MASK );

    // Enable comparison for the desired channel.
    set_reg_bits( &afec_regs->emr, hal_ll_adc_hw_specifics_map_local->channel << HAL_LL_AFEC_EMR_CMPSEL_BIT );

    // Enable the desired channel.
    set_reg_bit( &afec_regs->cher, hal_ll_adc_hw_specifics_map_local->channel );

    // Select the desired channel.
    write_reg( &afec_regs->cselr, hal_ll_adc_hw_specifics_map_local->channel );

    // Select default offset for the converted data.
    write_reg( &afec_regs->cocr, HAL_LL_AFEC_COCR_OFFSET_MASK );

    // Start conversion for dummy data.
    set_reg_bit( &afec_regs->cr, HAL_LL_AFEC_CR_START_BIT );

    // Read dummy data from the converted data register to erase it.
    read_reg( &afec_regs->cdr );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                                                     hal_ll_gpio_pin_mask( map->pin ) );

    _hal_ll_adc_enable_clock( map->module_index );

    _hal_ll_adc_hw_init( ( hal_ll_adc_base_handle_t *)map->base, map->resolution );

}
// ------------------------------------------------------------------------- END
