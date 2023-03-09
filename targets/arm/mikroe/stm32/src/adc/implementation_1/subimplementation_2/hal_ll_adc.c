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
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

#define HAL_LL_ADC_CSR_OFFSET                  ( 0x300 / 4 )
#define HAL_LL_ADC_CCR_OFFSET                  ( 0x308 / 4 )
#define HAL_LL_ADC_CDR_OFFSET                  ( 0x30A / 4 )
#define HAL_LL_ADC_ASCR_OFFSET                 ( 0x2C  / 4 )

#define HAL_LL_ADC_APB2ENR_SYSCFGEN            0
#define HAL_LL_ADC_VREF_ENVR                   0
#define HAL_LL_ADC_ADRDYIE_BIT                 0
#define HAL_LL_ADC_ADEN_BIT                    0
#define HAL_LL_ADC_ADRDY_BIT                   0
#define HAL_LL_ADC_ADDIS_BIT                   1
#define HAL_LL_ADC_EOC_BIT                     1
#define HAL_LL_ADC_ADSTART_BIT                 2
#define HAL_LL_ADC_RESOLUTION_BIT0             3
#define HAL_LL_ADC_VREF_VRR                    3
#define HAL_LL_ADC_RESOLUTION_BIT1             4
#define HAL_LL_ADC_ALIGN_BIT                   5
#define HAL_LL_ADC_ENABLE_CLOCK                13
#define HAL_LL_ADC_CONT_BIT                    13
#define HAL_LL_ADC_DISCEN_BIT                  16
#define HAL_LL_ADC_ADVREGEN_BIT                28
#define HAL_LL_ADC_DEEPPWD_BIT                 29
#define HAL_LL_ADC_ADCALDIF_BIT                30
#define HAL_LL_ADC_ADCAL_BIT                   31
#define HAL_LL_ADC_PIN_MASK                    0xF

#define HAL_LL_ADC_12BIT_RES                   0x00000000ul
#define HAL_LL_ADC_10BIT_RES                   0x00000008ul
#define HAL_LL_ADC_8BIT_RES                    0x00000010ul
#define HAL_LL_ADC_6BIT_RES                    0x00000018ul

#define ADC_CAL_SINGLE                         0x00000000ul
#define ADC_CAL_DIF                            0x00000001ul
#define HAL_LL_ADC_CLK_SRC                     0x30000000ul
#define HAL_LL_ADC_VOLTAGE                     0xCFFFFFFFul
#define HAL_LL_ADC_CCR                         0x50040308ul
#define HAL_LL_ADC_CKMODE                      0x00400000ul
#define HAL_LL_ADC_CCIPR                       0x40021088ul
#define HAL_LL_ADC_PRESCALER                   0xFFE3FFFFul
#define HAL_LL_ADC_CONVERSION                  0xFFFFFFF0ul
#define HAL_LL_ADC_VREF_CSR                    0x40010030ul
#define HAL_LL_ADC_CONVERSION_ONE              0x000007C0ul

#define HAL_LL_MODULE_INDEX_ERROR              0xFFFFFFFFul

#define HAL_LL_RESOLUTION_MASK                 0xFFFFFFE7ul

#define HAL_LL_ADC_DEFAULT_BASE_ADDRESS        0xFF

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
    uint32_t isr;            /* Address offset 0x00 */
    uint32_t ier;            /* Address offset 0x04 */
    uint32_t cr;             /* Address offset 0x08 */
    uint32_t cfgr;           /* Address offset 0x0C */
    uint32_t cfgr2;          /* Address offset 0x10 */
    uint32_t smpr1;          /* Address offset 0x14 */
    uint32_t smpr2;          /* Address offset 0x18 */
    uint32_t __unused1;      /* Unused         0x1C */
    uint32_t tr1;            /* Address offset 0x20 */
    uint32_t tr2;            /* Address offset 0x24 */
    uint32_t tr3;            /* Address offset 0x28 */
    uint32_t __unused2;      /* Unused         0x2C */
    uint32_t sqr1;           /* Address offset 0x30 */
    uint32_t sqr2;           /* Address offset 0x34 */
    uint32_t sqr3;           /* Address offset 0x38 */
    uint32_t sqr4;           /* Address offset 0x3C */
    uint32_t dr;             /* Address offset 0x40 */
} hal_ll_adc_base_handle_t;

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
    #ifdef ADC_MODULE_2
    {ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef ADC_MODULE_3
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
  * @param  *map - ADC module config map.
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
 * @brief Searches for the specific map.
 *
 * @param handle     - Handle containing base adress.
 * @return           - Specific map.
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
  * @return None
  */
static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle( hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id )
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
        case HAL_LL_ADC_VREF_DEFAULT:
            break;
        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin )
    {
        hal_ll_adc_map_pin( pin_check_result, &index );

        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result]->hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_pin_id index = {HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( (pin_check_result = hal_ll_adc_check_pins( hal_ll_adc_hw_specifics_map_local->pin, &index, (void *)0 ) ) == HAL_LL_PIN_NC )
    {
        return HAL_LL_ADC_WRONG_PIN;
    };

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

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
    low_level_handle = hal_ll_adc_get_handle;

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
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

    base->sqr1 &= ~HAL_LL_ADC_CONVERSION_ONE;
    base->sqr1 |= ( ( hal_ll_adc_hw_specifics_map_local->channel << 6 ) & ( HAL_LL_ADC_CONVERSION_ONE ) );

    // Start the conversion.
    set_reg_bit( &( base->cr ), HAL_LL_ADC_ADSTART_BIT );

    // The application should allow a delay of tSTAB between power up and start of conversion.
    Delay_1us();

    while ( !( check_reg_bit( &( base->isr ), HAL_LL_ADC_EOC_BIT ) ) );
    // Conversion result from SS3.
    *readDatabuf = base->dr;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
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
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static inline void adc1_enable_clock()
{
    set_reg_bit( _RCC_AHB2ENR, HAL_LL_ADC_ENABLE_CLOCK );
}

static inline void adc2_enable_clock()
{
    set_reg_bit( _RCC_AHB2ENR, HAL_LL_ADC_ENABLE_CLOCK );
}

static inline void adc3_enable_clock()
{
    set_reg_bit( _RCC_AHB2ENR, HAL_LL_ADC_ENABLE_CLOCK );
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
        #ifdef ADC_MODULE_2
        case ( hal_ll_adc_module_num(ADC_MODULE_2) ):
            adc2_enable_clock();
            break;
        #endif
        #ifdef ADC_MODULE_3
        case ( hal_ll_adc_module_num(ADC_MODULE_3) ):
            adc3_enable_clock();
            break;
        #endif
    }
}

static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution )
{
    static uint32_t wait_loop_index = 0;
    static uint32_t *reg;
    reg = HAL_LL_ADC_CCIPR;

    // Select ADC clock source.
    *reg |= HAL_LL_ADC_CLK_SRC;

    // Exit from deep power down mode.
    if ( check_reg_bit( &( base->cr ), HAL_LL_ADC_DEEPPWD_BIT ) )
    {
        clear_reg_bit( &( base->cr ), HAL_LL_ADC_DEEPPWD_BIT );
    }

    // Enable voltage regulator.
    base->cr &= HAL_LL_ADC_VOLTAGE;

    if ( !( check_reg_bit( &( base->cr ), HAL_LL_ADC_ADVREGEN_BIT ) ) )
    {
        set_reg_bit( &( base->cr ), HAL_LL_ADC_ADVREGEN_BIT );
    }

    // Enable ADC interrupts.
    set_reg_bit( &( base->ier ), HAL_LL_ADC_ADRDYIE_BIT );

    // Disable ADC
    if ( check_reg_bit( &( base->cr ), HAL_LL_ADC_ADEN_BIT ) )
    {
        set_reg_bit( &( base->cr ), HAL_LL_ADC_ADDIS_BIT );
    }

    // Voltage reference enable, ckmode SYSCLK.
    reg = HAL_LL_ADC_CCR;
    *reg |= HAL_LL_ADC_CKMODE;

    // Select calibration mode.
    clear_reg_bit( &( base->cr ), HAL_LL_ADC_ADCALDIF_BIT );

    // Start ADC calibration.
    set_reg_bit( &( base->cr ), HAL_LL_ADC_ADCAL_BIT );

    // Wait for calibration.
    while ( check_reg_bit( &( base->cr ), HAL_LL_ADC_ADCAL_BIT ) );

    // Prescaler.
    *reg &= HAL_LL_ADC_PRESCALER;

    // Clear ADRDY bit ADC_ISR by writting 1.
    set_reg_bit( &( base->isr ), HAL_LL_ADC_ADRDY_BIT );

    // Set delay for voltage regulator to be initialized correctly.
    wait_loop_index = 10 * ( Get_Fosc_kHz() / 1000 );
    while( wait_loop_index != 0 )
    {
        wait_loop_index--;
    }

    // Enable ADC.
    set_reg_bit( &( base->cr ), HAL_LL_ADC_ADEN_BIT );

    // ADRDY bit.
    while ( !( check_reg_bit( &( base->cr ), HAL_LL_ADC_ADRDY_BIT ) ) );

    // Resolution.
    base->cfgr &= HAL_LL_RESOLUTION_MASK;
    base->cfgr |= resolution;

    // Data alignment.
    clear_reg_bit( &( base->cfgr ), HAL_LL_ADC_ALIGN_BIT );

    // Discontinuos mode disabled.
    clear_reg_bit( &( base->cfgr ), HAL_LL_ADC_DISCEN_BIT );

    // Continuos conversion mode.
    clear_reg_bit( &( base->cfgr ), HAL_LL_ADC_CONT_BIT );

    // Regular channel sequence length.
    base->sqr1 &= HAL_LL_ADC_CONVERSION;
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    uint32_t *tmp_switch;

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                                                     hal_ll_gpio_pin_mask( map->pin ) );

    // ADC Switch.
    #if defined(STM32L486xx) || defined(STM32L476xx) || defined(STM32L475xx) || \
        defined(STM32L4S9xx) || defined(STM32L4S7xx) || defined(STM32L4S5xx) || \
        defined(STM32L4R9xx) || defined(STM32L4R7xx) || defined(STM32L4R5xx)
    tmp_switch = hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) );
    tmp_switch += HAL_LL_ADC_ASCR_OFFSET;
    *tmp_switch |= 1ul << ( map->pin & HAL_LL_ADC_PIN_MASK );
    #endif

    _hal_ll_adc_enable_clock( map->module_index );

    _hal_ll_adc_hw_init((hal_ll_adc_base_handle_t *)map->base, map->resolution);

}
// ------------------------------------------------------------------------- END
