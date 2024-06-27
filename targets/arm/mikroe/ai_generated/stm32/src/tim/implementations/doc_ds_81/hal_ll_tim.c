/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_ll_tim.c
 * @brief TIM HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_rcc.h"
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
/*!< CR1 constants. */
#define HAL_LL_TIM_ENABLE_COUNTER_BIT        0
#define HAL_LL_TIM_BDTR_MOE_BIT              15
#define HAL_LL_TIM_BDTR_MOE                  0x8000

#define HAL_LL_TIM_CCMR_CC2S_BIT0            0x100u
#define HAL_LL_TIM_CCMR_CC2S_BIT1            0x200u
#define HAL_LL_TIM_CCMR_OC2PE                0x800u
#define HAL_LL_TIM_CCMR_OC2M_BIT0            0x1000u
#define HAL_LL_TIM_CCMR_OC2M_BIT1            0x2000u
#define HAL_LL_TIM_CCMR_OC2M_BIT2            0x4000u

#define HAL_LL_TIM_CCMR_CC3S_BIT0            0x1u
#define HAL_LL_TIM_CCMR_CC3S_BIT1            0x2u
#define HAL_LL_TIM_CCMR_OC3PE                0x8u
#define HAL_LL_TIM_CCMR_OC3M_BIT0            0x10u
#define HAL_LL_TIM_CCMR_OC3M_BIT1            0x20u
#define HAL_LL_TIM_CCMR_OC3M_BIT2            0x40u

#define HAL_LL_TIM_CR1_DIR                   0x10
#define HAL_LL_TIM_CR1_DIR_BIT               4

#define HAL_LL_TIM_ENABLE_1                 11

#define HAL_LL_TIM_ENABLE_2                 0

#define HAL_LL_TIM_ENABLE_3                 1

#define HAL_LL_TIM_ENABLE_4                 2

#define HAL_LL_TIM_ENABLE_14                 15

#define HAL_LL_TIM_ENABLE_15                 16

#define HAL_LL_TIM_ENABLE_16                 17

#define HAL_LL_TIM_ENABLE_17                 18


#define HAL_LL_APB1_TIMER_CLOCK              1



#define hal_ll_tim_channel_static( _chn )    ( _chn-1 )

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
    uint32_t cr1;            /* Address offset 0x00 */
    uint32_t cr2;            /* Address offset 0x04 */
    uint32_t smcr;           /* Address offset 0x08 */
    uint32_t dier;           /* Address offset 0x0C */
    uint32_t sr;             /* Address offset 0x10 */
    uint32_t egr;            /* Address offset 0x14 */
    uint32_t ccmr1;          /* Address offset 0x18 */
    uint32_t ccmr2;          /* Address offset 0x1C */
    uint32_t ccer;           /* Address offset 0x20 */
    uint32_t cnt;            /* Address offset 0x24 */
    uint32_t psc;            /* Address offset 0x28 */
    uint32_t arr;            /* Address offset 0x2C */
    uint32_t rcr;            /* Address offset 0x30 */
    uint32_t ccr1;           /* Address offset 0x34 */
    uint32_t ccr2;           /* Address offset 0x38 */
    uint32_t ccr3;           /* Address offset 0x3C */
    uint32_t ccr4;           /* Address offset 0x40 */
    uint32_t bdtr;           /* Address offset 0x44 */
    uint32_t dcr;            /* Address offset 0x48 */
    uint32_t dmar;           /* Address offset 0x4C */
    uint32_t tim2_5_or;      /* Address offset 0x50 */
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
 * @brief  Enable TIM module 1 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim1_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 2 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim2_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 3 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim3_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 4 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim4_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 14 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim14_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 15 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim15_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 16 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim16_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 17 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @return none
 */
static inline void _hal_ll_tim17_set_clock( bool hal_ll_state );


/**
  * @brief  Enable TIM module gate clock.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state );

/**
  * @brief  Select TIM clock source
  * @param  selector - clock source selector
  * @return uint32_t - clock source
  */
static uint32_t _hal_ll_tim_clock_source( uint8_t selector );

/**
  * @brief  Based on selected TIM,
  *         return clock speed.
  * @param  base - TIM module base
  *                address
  * @return uint32_t clock source.
  */
static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base );

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
static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

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
static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

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
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

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
static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

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
static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result ].config.pin != pin ){
        // Clear previous module alternate functions
        _hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );

        _hal_ll_tim_map_pin( pin_check_result, index );

        _hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );

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

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {

    uint32_t tmp_channel;
    uint32_t ck_psc;
    uint32_t local_base_addr;
    uint32_t local_freq;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if( hal_ll_tim_hw_specifics_map_local->base == HAL_LL_MODULE_ERROR ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    tmp_channel = hal_ll_tim_hw_specifics_map_local->config.channel;

    // If complementary output channel is used.
    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        // Stop capture/compare.
        hal_ll_hw_reg->ccer &= 1UL << tmp_channel * 4 + 2;
    } else {
        // Stop capture/compare.
        hal_ll_hw_reg->ccer &= 1UL << tmp_channel * 4;
    }

    // Set TIM duty to 0.
    *( &hal_ll_hw_reg->ccr1 + hal_ll_tim_channel_static( tmp_channel ) ) = 0;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    local_freq      = hal_ll_tim_hw_specifics_map_local->freq_hz;
    local_base_addr = hal_ll_tim_hw_specifics_map_local->base;

    ck_psc = _hal_ll_tim_get_clock_speed( local_base_addr ) / local_freq;

    if ( ck_psc > UINT16_MAX ) {
        tmp_freq = _hal_ll_tim_get_clock_speed( local_base_addr ) / UINT16_MAX;
        hal_ll_tim_hw_specifics_map_local->freq_hz = tmp_freq;
    } else {
        tmp_freq = freq_hz;
        hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return tmp_freq;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {

    float    tmp_duty;
    uint32_t max_duty = 0;
    uint16_t max_period;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( low_level_handle->init_ll_state == false ) {
        hal_ll_tim_start( handle );
        low_level_handle->init_ll_state = true;
    }

    tmp_duty = duty_ratio * 100;
    max_period = hal_ll_tim_hw_specifics_map_local->max_period;

    max_duty = ( ( float )max_period / 100 ) * tmp_duty;

    *( &hal_ll_hw_reg->ccr1 + hal_ll_tim_channel_static( hal_ll_tim_hw_specifics_map_local->config.channel ) ) = max_duty;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    uint32_t tmp_channel;
    volatile uint32_t  tmp,
                       *tmpPtr;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    tmp_channel = hal_ll_tim_hw_specifics_map_local->config.channel;

    // Capture/Compare 1 output enable.
    tmp = hal_ll_hw_reg->ccer;

    // If complementary output channel is used.
    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        // Capture/Compare complementary output enable
        tmp |=  ( 1UL << ( hal_ll_tim_channel_static( tmp_channel ) * 4 + 2 ) );
        // Capture/Compare complementary output polarity(ACTIVE HIGH).
        tmp &= ~( 1UL << ( hal_ll_tim_channel_static( tmp_channel ) * 4 + 3 ) );
    } else {
        // Capture/Compare output polarity.
        tmp |=  ( 1UL << ( hal_ll_tim_channel_static( tmp_channel ) * 4 ) );
        // Capture/Compare output polarity(ACTIVE HIGH).
        tmp &= ~( 1UL << ( hal_ll_tim_channel_static( tmp_channel ) * 4 + 1 ) );
    }

    hal_ll_hw_reg->ccer = tmp;

    #if defined(TIM_MODULE_1) || defined(TIM_MODULE_8) || defined(TIM_MODULE_20)
    // Main output enabled.
    set_reg_bit( &hal_ll_hw_reg->bdtr, HAL_LL_TIM_BDTR_MOE_BIT );
    #endif

    tmpPtr = &hal_ll_hw_reg->ccmr1;

    if( hal_ll_tim_channel_static( tmp_channel ) > 1 ) {
        tmpPtr = &hal_ll_hw_reg->ccmr2;
    }

    if( ( hal_ll_tim_channel_static( tmp_channel ) / 2 ) * 2 !=
          hal_ll_tim_channel_static( tmp_channel ) ) {
        // Clear CCxS, OCxM[0].
        *tmpPtr &= ~( HAL_LL_TIM_CCMR_CC2S_BIT0 |
                      HAL_LL_TIM_CCMR_CC2S_BIT1 |
                      HAL_LL_TIM_CCMR_OC2PE |
                      HAL_LL_TIM_CCMR_OC2M_BIT0 );
        // Set OCxM[2, 1]
        *tmpPtr |= HAL_LL_TIM_CCMR_OC2M_BIT1 | HAL_LL_TIM_CCMR_OC2M_BIT2;
    } else {
        // Clear CCxS, OCxM[0].
        *tmpPtr &= ~( HAL_LL_TIM_CCMR_CC3S_BIT0 |
                      HAL_LL_TIM_CCMR_CC3S_BIT1 |
                      HAL_LL_TIM_CCMR_OC3PE |
                      HAL_LL_TIM_CCMR_OC3M_BIT0 );

        // Set OCxM[2, 1].
        *tmpPtr |=  HAL_LL_TIM_CCMR_OC3M_BIT1 | HAL_LL_TIM_CCMR_OC3M_BIT2;
    }

    // Enable counter.
    set_reg_bit( &hal_ll_hw_reg->cr1, HAL_LL_TIM_ENABLE_COUNTER_BIT );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // If complementary output channel is used.
    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        hal_ll_hw_reg->ccer &= 1UL << hal_ll_tim_hw_specifics_map_local->config.channel * 4 + 2;
    } else {
        hal_ll_hw_reg->ccer &= 1UL << hal_ll_tim_hw_specifics_map_local->config.channel * 4;
    }

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

        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, true );
        _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.channel = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static inline void _hal_ll_tim1_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_1 );
    } else {
        clear_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_1 );
    }
}

static inline void _hal_ll_tim2_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_2 );
    } else {
        clear_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_2 );
    }
}

static inline void _hal_ll_tim3_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_3 );
    } else {
        clear_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_3 );
    }
}

static inline void _hal_ll_tim4_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_4 );
    } else {
        clear_reg_bit( _RCC_APBENR1, HAL_LL_TIM_ENABLE_4 );
    }
}

static inline void _hal_ll_tim14_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_14 );
    } else {
        clear_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_14 );
    }
}

static inline void _hal_ll_tim15_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_15 );
    } else {
        clear_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_15 );
    }
}

static inline void _hal_ll_tim16_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_16 );
    } else {
        clear_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_16 );
    }
}

static inline void _hal_ll_tim17_set_clock( bool hal_ll_state ) {
    if( hal_ll_state ) {
        set_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_17 );
    } else {
        clear_reg_bit( _RCC_APBENR2, HAL_LL_TIM_ENABLE_17 );
    }
}


static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {

    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( _tim_map[ pin_num ].pin == pin ) {
            // Get module number
            hal_ll_module_id = _tim_map[ pin_num ].module_index;
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

static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state ) {

    switch ( ( uint32_t )base ) { // 32-bit base address.
    #ifdef TIM_MODULE_1
        case ( HAL_LL_TIM1_BASE_ADDR ):
            _hal_ll_tim1_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_2
        case ( HAL_LL_TIM2_BASE_ADDR ):
            _hal_ll_tim2_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_3
        case ( HAL_LL_TIM3_BASE_ADDR ):
            _hal_ll_tim3_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_4
        case ( HAL_LL_TIM4_BASE_ADDR ):
            _hal_ll_tim4_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_14
        case ( HAL_LL_TIM14_BASE_ADDR ):
            _hal_ll_tim14_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_15
        case ( HAL_LL_TIM15_BASE_ADDR ):
            _hal_ll_tim15_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_16
        case ( HAL_LL_TIM16_BASE_ADDR ):
            _hal_ll_tim16_set_clock( hal_ll_state );
            break;
    #endif

    #ifdef TIM_MODULE_17
        case ( HAL_LL_TIM17_BASE_ADDR ):
            _hal_ll_tim17_set_clock( hal_ll_state );
            break;
    #endif

    }
}

static uint32_t _hal_ll_tim_clock_source( uint8_t selector ) {

    rcc_clocks_t rcc_clocks;

    RCC_GetClocksFrequency( &rcc_clocks );

    if( selector == HAL_LL_APB1_TIMER_CLOCK ) {
        if( rcc_clocks.hclk/rcc_clocks.pclk > 1 ) {
            return rcc_clocks.pclk * 2;
        } else {
            return rcc_clocks.pclk;
        }
    }

    return 0;
}

static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base ) {

    switch ( ( uint32_t )base ) {
        #ifdef TIM_MODULE_1
        case ( HAL_LL_TIM1_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM1_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_2
        case ( HAL_LL_TIM2_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM2_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_3
        case ( HAL_LL_TIM3_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM3_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_4
        case ( HAL_LL_TIM4_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM4_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_14
        case ( HAL_LL_TIM14_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM14_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_15
        case ( HAL_LL_TIM15_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM15_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_16
        case ( HAL_LL_TIM16_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM16_BUS );
            break;
        #endif

        #ifdef TIM_MODULE_17
        case ( HAL_LL_TIM17_BASE_ADDR ):
            return _hal_ll_tim_clock_source( TIM17_BUS );
            break;
        #endif

    }
    return 0;
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {

    uint8_t tmp_channel;

    // Map new pin
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = _tim_map[ index ].pin;
    tmp_channel = _tim_map[ index ].channel;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = _tim_map[ index ].af;

    if ( tmp_channel >= HAL_LL_TIM_CHANNEL_1N ) {
        HAL_LL_TIM_IS_COMPLEMENTARY = true;
        hal_ll_tim_hw_specifics_map[ module_index ].config.channel = tmp_channel - 4;
    } else {
        HAL_LL_TIM_IS_COMPLEMENTARY = false;
        hal_ll_tim_hw_specifics_map[ module_index ].config.channel = tmp_channel;
    }
}

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    module_struct module;
    uint32_t      tim_config = 0;

    if( map->config.pin != HAL_LL_PIN_NC ) {
        if( hal_ll_state == false ) {
            tim_config = GPIO_CFG_MODE_ALT_FUNCTION |
                         GPIO_CFG_SPEED_LOW |
                         GPIO_CFG_OTYPE_PP;
        } else {
            tim_config = GPIO_CFG_MODE_ALT_FUNCTION |
                         GPIO_CFG_SPEED_HIGH |
                         GPIO_CFG_OTYPE_PP;
        }

        module.pins[ 0 ] = VALUE( map->config.pin, map->config.af );
        module.pins[ 1 ] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = tim_config;
        module.configs[ 1 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {

    uint32_t  ck_psc;

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    // Counter used as upcounter.
    clear_reg_bit( &hal_ll_hw_reg->cr1, HAL_LL_TIM_CR1_DIR_BIT );

    // Get clock speed.
    ck_psc = _hal_ll_tim_get_clock_speed( map->base ) / map->freq_hz;

    // This should not be the case. ck_psc should not be greater than 65535, which is max value.
    if( ck_psc > UINT16_MAX ) {
        // In case of duty period beeing greater than 65535 set ck_psc to max value.
        ck_psc = UINT16_MAX - 1; // Because of ( ck_psc / UINT16_MAX + 1 ) ), has to be minus 1.
    }else if ( ck_psc < 1 ) {
        ck_psc = 1;
    }

    // Write prescale value.
    hal_ll_hw_reg->psc = ( uint16_t )( ck_psc / UINT16_MAX );

    // Write max count value.
    hal_ll_hw_reg->arr = ( uint16_t )( ck_psc/( ck_psc / UINT16_MAX + 1 ) );

    // Write max period to global array.
    map->max_period = ( uint16_t )ck_psc;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    _hal_ll_tim_set_clock( map->base, true );

    _hal_ll_tim_alternate_functions_set_state( map, true );

    _hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END

