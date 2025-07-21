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
 * @file  hal_ll_tim.c
 * @brief TIM HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"
#include "mcu.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
/*!< CR1 constants. */

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct
{
    uint32_t todo;
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_channel_t  channel;
    uint32_t af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t  base;
    hal_ll_tim_t        config;
    uint16_t            max_period;
    uint32_t            freq_hz;
    hal_ll_pin_name_t   module_index;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum
{
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] =
{
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_1 - 1},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_2 - 1},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_3 - 1},
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_4 - 1},
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_5 - 1},
    #endif
    #ifdef TIM_MODULE_8
    {HAL_LL_TIM8_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_8 - 1},
    #endif
    #ifdef TIM_MODULE_9
    {HAL_LL_TIM9_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_9 - 1},
    #endif
    #ifdef TIM_MODULE_10
    {HAL_LL_TIM10_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_10 - 1},
    #endif
    #ifdef TIM_MODULE_11
    {HAL_LL_TIM11_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_11 - 1},
    #endif
    #ifdef TIM_MODULE_12
    {HAL_LL_TIM12_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_12 - 1},
    #endif
    #ifdef TIM_MODULE_13
    {HAL_LL_TIM13_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_13 - 1},
    #endif
    #ifdef TIM_MODULE_14
    {HAL_LL_TIM14_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_14 - 1},
    #endif
    #ifdef TIM_MODULE_15
    {HAL_LL_TIM15_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_15 - 1},
    #endif
    #ifdef TIM_MODULE_16
    {HAL_LL_TIM16_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_16 - 1},
    #endif
    #ifdef TIM_MODULE_17
    {HAL_LL_TIM17_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_17 - 1},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

static bool HAL_LL_TIM_IS_COMPLEMENTARY;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable TIM module gate clock.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state );

/**
  * @brief  Select TIM clock source
  * @param  selector - clock source selector
  * @return uint32_t - clock source
  */
static uint32_t hal_ll_tim_clock_source( uint8_t selector );

/**
  * @brief  Based on selected TIM,
  *         return clock speed.
  * @param  base - TIM module base
  *                address
  * @return uint32_t clock source.
  */
static uint32_t hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param  map - Object specific context handler.
  * @return none
  *
  */
static void hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Full TIM module initialization procedure.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param  map - Object specific context handler.
  * @return none
  *
  */
static void hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_tim_hw_specifics_map array index.
  *
  * @param  handle - Object specific context handler.
  * @return hal_ll_tim_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param  pin - TIM pre-defined pin name.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * TIM pin.
 *
 * @param[in]  module_index TIM HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TIM map index values
 *
 * @return  None
 */
static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Sets TIM pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if TIM is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param  map - Object specific context handler.
  *
  * @param  hal_ll_state - Init/De-init
  * @return none
  *
  */
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result].config.pin != pin ) {
        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );

        hal_ll_tim_map_pin( pin_check_result, index );

        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_init(hal_ll_tim_hw_specifics_map_local);

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;

        hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, true );
        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.channel = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                                hal_ll_tim_handle_register_t *handle_map ) {
    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    uint16_t map_size = ( sizeof( hal_ll_tim_pin_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( hal_ll_tim_pin_map[ pin_num ].pin == pin ) {
            // Get module number
            hal_ll_module_id = hal_ll_tim_pin_map[ pin_num ].module_index;
            if ( NULL == handle_map[hal_ll_module_id].hal_drv_tim_handle ) {
                *index = pin_num;
                return hal_ll_module_id;
            } else if ( TIM_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }
    // By default return last error msg.
    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {

    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state ) {

}

static uint32_t hal_ll_tim_clock_source( uint8_t selector ) {

    return 0;
}

static uint32_t hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base ) {

    return 0;
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {

}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

}

static void hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
#define PCLK        60000000UL  // Example Peripheral Clock
#define FREQ_HZ     1000.0f     // Desired PWM frequency
#define DUTY        0.5f        // 50% duty cycle

#define PERIOD      ((uint32_t)(PCLK / FREQ_HZ))       // e.g. 60000
#define COMPARE     ((uint32_t)(PERIOD * DUTY) - 1)    // e.g. 29999
    // PSEL 3
    R_MSTP->MSTPCRD_b.MSTPD6 = 0;

    R_GPT4->GTCR_b.CST = 0; // stop operation first
    R_GPT4->GTCR_b.MD = 0x0; // PWM mode
    R_GPT4->GTBER_b.PR = 1; // count up
    R_GPT4->GTBER_b.PR = 1; // single buffer operation
    // .... // freq settings
    R_GPT4->GTCR = 0;              // Clear control register (stop, reset config)

    R_GPT4->GTUDDTYC = 0x00;       // Saw-wave PWM mode (count up)
    R_GPT4->GTIOR = 
        (0b01 << 2)  |             // GTIOCA output when counting up and match A (initial output = 1)
        (0b00 << 0)  |             // GTIOCA output when counting up and not matching (output = 0)
        (1 << 14);                 // Enable GTIOCA output

    R_GPT4->GTCCR[0] = COMPARE;    // Set compare match A
    R_GPT4->GTCCR[2] = COMPARE;    // Buffered A

    R_GPT4->GTPR = PERIOD - 1;     // Set PWM period
    R_GPT4->GTPBR = PERIOD - 1;    // Buffered period

    R_GPT4->GTCR = (0b000 << 1);  // PCLK/1 as clock source (TPCS bits)

    R_GPT4->GTCNT = 0;             // Clear counter
    R_GPT4->GTCR |= (1 << 0);      // Start timer (CST = 1)
    // .... // freq settings


    R_GPT4->GTCNT = 0; // initial counter value

    // A
    R_GPT4->GTIOR_b.GTIOA = 0x9;               // Set GTIOC pin function (Initial low -> Low at GTCCRA/B compare match -> High at cycle end)
    R_GPT4->GTIOR_b.OAE = 1;                   // Enable GTIOC pin output
    R_GPT4->GTBER_b.CCRA = 1;                  // Set buffer operation for the duty
    // uint32_t duty = 0; //  ????
    // R_GPT4->GTCCR[0] = duty? duty - 1 : duty;  // Set compare match value
    R_GPT4->GTCCR[2] = R_GPT4->GTCCR[0];

    R_PFS->PORT[3].PIN[2].PmnPFS_b.PMR = 1;
    R_PFS->PORT[3].PIN[2].PmnPFS_b.PMR = 1;
    R_PFS->PORT[3].PIN[2].PmnPFS_b.PSEL = 3;

    if (R_GPT4->GTPR && R_GPT4->GTCCR[0]) {
        R_GPT4->GTCR_b.CST = 1;
    }
}

static void hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_set_clock( map->base, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
