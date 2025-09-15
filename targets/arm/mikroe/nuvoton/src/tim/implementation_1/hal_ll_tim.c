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
#include "hal_ll_mstpcr.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
#define CLK_APBCLK0_TMRCKEN_OFFSET          (2)

#define SYS_IPRST1_TMRRST_OFFSET            (2)
#define SYS_IPRST2_TMRRST_OFFSET            (20)

#define TIM_ALCTL_FUNCSEL_OFFSET            (0)

#define TIM_PWMCTL_CNTEN_OFFSET             (0)
#define TIM_PWMCTL_CNTTYPE_OFFSET           (1)
#define TIM_PWMCTL_CNTTYPE_MASK             ( 0x3UL << TIM_PWMCTL_CNTTYPE_OFFSET )

#define TIM_PWMCTL_CNTMODE_OFFSET           (3)
#define TIM_PWMCTL_IMMLDEN_OFFSET           (9)
#define TIM_PWMCTL_OUTMODE_OFFSET           (16)

#define TIM_PWMPOEN_POEN0_OFFSET            (0)

#define TIM_PWMCLKSRC_CLKSRC_MASK           0x7UL

#define CLK_FREQUENCY                       12000000

//#define HAL_LL_TIM_AF_CONFIG (GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PORT_PULL_UP_ENABLE)

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
    uint32_t ctl;                   /*!< [0x0000] Timer Control Register                                          */
    uint32_t cmp;                   /*!< [0x0004] Timer Comparator Register                                       */
    uint32_t intsts;                /*!< [0x0008] Timer Interrupt Status Register                                 */
    uint32_t cnt;                   /*!< [0x000c] Timer Data Register                                             */
    uint32_t cap;                   /*!< [0x0010] Timer Capture Data Register                                     */
    uint32_t extctl;                /*!< [0x0014] Timer External Control Register                                 */
    uint32_t eintsts;               /*!< [0x0018] Timer External Interrupt Status Register                        */
    uint32_t trgctl;                /*!< [0x001c] Timer Trigger Control Register                                  */
    uint32_t altctl;                /*!< [0x0020] Timer Alternative Control Register                              */
    uint32_t _unused[7];
    uint32_t pwmctl;                /*!< [0x0040] Timer PWM Control Register                                      */
    uint32_t pwmclksrc;             /*!< [0x0044] Timer PWM Counter Clock Source Register                         */
    uint32_t pwmclkpsc;             /*!< [0x0048] Timer PWM Counter Clock Pre-scale Register                      */
    uint32_t pwmcntclr;             /*!< [0x004c] Timer PWM Clear Counter Register                                */
    uint32_t pwmperiod;             /*!< [0x0050] Timer PWM Period Register                                       */
    uint32_t pwmcmpdat;             /*!< [0x0054] Timer PWM Comparator Register                                   */
    uint32_t pwmdtctl;              /*!< [0x0058] Timer PWM Dead-Time Control Register                            */
    uint32_t pwmcnt;                /*!< [0x005c] Timer PWM Counter Register                                      */
    uint32_t pwmmsken;              /*!< [0x0060] Timer PWM Output Mask Enable Register                           */
    uint32_t pwmmsk;                /*!< [0x0064] Timer PWM Output Mask Data Control Register                     */
    uint32_t pwmbnf;                /*!< [0x0068] Timer PWM Brake Pin Noise Filter Register                       */
    uint32_t pwmfailbrk;            /*!< [0x006c] Timer PWM System Fail Brake Control Register                    */
    uint32_t pwmbrkctl;             /*!< [0x0070] Timer PWM Brake Control Register                                */
    uint32_t pwmpolctl;             /*!< [0x0074] Timer PWM Pin Output Polar Control Register                     */
    uint32_t pwmpoen;               /*!< [0x0078] Timer PWM Pin Output Enable Register                            */
    uint32_t pwmswbrk;              /*!< [0x007c] Timer PWM Software Trigger Brake Control Register               */
    uint32_t pwminten0;             /*!< [0x0080] Timer PWM Interrupt Enable Register 0                           */
    uint32_t pwminten1;             /*!< [0x0084] Timer PWM Interrupt Enable Register 1                           */
    uint32_t pwmintsts0;            /*!< [0x0088] Timer PWM Interrupt Status Register 0                           */
    uint32_t pwmintsts1;            /*!< [0x008c] Timer PWM Interrupt Status Register 1                           */
    uint32_t pwmtrgctl;             /*!< [0x0090] Timer PWM Trigger Control Register                              */
    uint32_t pwmsctl;               /*!< [0x0094] Timer PWM Synchronous Control Register                          */
    uint32_t pwmstrg;               /*!< [0x0098] Timer PWM Synchronous Trigger Register                          */
    uint32_t pwmstatus;             /*!< [0x009c] Timer PWM Status Register                                       */
    uint32_t pwmpbuf;               /*!< [0x00a0] Timer PWM Period Buffer Register                                */
    uint32_t pwmcmpbuf;             /*!< [0x00a4] Timer PWM Comparator Buffer Register                            */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
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
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_0 },
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_1 },
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_2 },
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_3 },
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_4 },
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_5 },
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable TIM module gate clock.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Select TIM clock source
  * @return uint32_t - clock source
  */
static uint32_t hal_ll_tim_clock_source();

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param  map - Object specific context handler.
  * @return uint32_t - Set period.
  *
  */
static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Full TIM module initialization procedure.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param  map - Object specific context handler.
  * @return uint32_t - Set period.
  *
  */
static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

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
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                               hal_ll_tim_handle_register_t *handle_map );

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
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                      bool hal_ll_state );

/**
  * @brief  Set TIM frequency register values.
  *
  * Calculates and writes values to the period registers
  * based on the peripheral clock and desired frequency.
  *
  * @param[in] map - Object specific context handler.
  * @return uint32_t - Set period
  *
  */
static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map );

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

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                         (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    uint16_t local_freq = 0;
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );
    uint32_t period;

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    period = hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Memorize information about the max period available (PWM duty cycle is dependant of this information).
    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // hal_ll_tim_pin_type_t pin_type =  hal_ll_tim_hw_specifics_map_local->config.pin_type;

    // TODO - Define the function behavior here!

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // hal_ll_tim_pin_type_t pin_type =  hal_ll_tim_hw_specifics_map_local->config.pin_type;

    set_reg_bit( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_CNTEN_OFFSET );
    set_reg_bit( &( hal_ll_hw_reg->pwmpoen ), TIM_PWMPOEN_POEN0_OFFSET );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    clear_reg_bit( &( hal_ll_hw_reg->pwmpoen ), TIM_PWMPOEN_POEN0_OFFSET );
    clear_reg_bit( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_CNTEN_OFFSET );

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

        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, true );
        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.pin_type = HAL_LL_PIN_NC;
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

static void hal_ll_tim_module_enable( uint8_t module_index, bool hal_ll_state ) {
    if ( TIM_MODULE_4 > module_index ) {
        set_reg_bit( CLK_APBCLK0, module_index + CLK_APBCLK0_TMRCKEN_OFFSET );          //clock enable

        set_reg_bit( SYS_IPRST1, module_index + SYS_IPRST1_TMRRST_OFFSET );             //reset config module
        clear_reg_bit( SYS_IPRST1, module_index + SYS_IPRST1_TMRRST_OFFSET );
    } 
    else {
        set_reg_bit( CLK_APBCLK1, module_index );                                       //clock enable

        set_reg_bit( SYS_IPRST2, module_index + SYS_IPRST2_TMRRST_OFFSET - 4 );         //reset config module
        clear_reg_bit( SYS_IPRST2, module_index + SYS_IPRST2_TMRRST_OFFSET - 4);
    }
        
}

static uint32_t hal_ll_tim_clock_source() {
    // TODO - Define the function behavior here!
    return CLK_FREQUENCY;
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] = map->config.pin;
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = map->config.af;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t period;

    // TODO - Define the function behavior here!

    return period;
}

static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    // hal_ll_tim_pin_type_t pin_type =  map->config.pin_type;
    uint8_t module_index = map->module_index;
    uint32_t period;

    uint16_t prescaler_value = hal_ll_tim_clock_source() / map->freq_hz;
    
    set_reg_bit( &( hal_ll_hw_reg->altctl ), TIM_ALCTL_FUNCSEL_OFFSET );

    if ( TIM_MODULE_4 > module_index )
        clear_reg_btis( &( hal_ll_hw_reg->pwmclksrc ), TIM_PWMCLKSRC_CLKSRC_MASK );

    set_reg_bits( &( hal_ll_hw_reg->pwmclkpcs ), prescaler_value - 1 );

    clear_reg_bits( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_CNTTYPE_MASK );
    clear_reg_bit( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_CNTMODE_OFFSET );
    clear_reg_bit( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_IMMLDEN_OFFSET );
    clear_reg_bit( &( hal_ll_hw_reg->pwmctl ), TIM_PWMCTL_OUTMODE_OFFSET );

    return period;
}

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map->module_index, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END