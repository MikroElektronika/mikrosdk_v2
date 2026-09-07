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
#include "hal_ll_cg.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS

#define HAL_LL_TIM_AF_CONFIG ( GPIO_CFG_PORT_DIRECTION_OUTPUT | GPIO_CFG_PULL_UP )

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ( (hal_ll_tim_base_handle_t *)_handle )

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ( (hal_ll_tim_handle_register_t *)*handle )

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

#define HAL_LL_TIM_OUT_ACT_NO_CHANGE      (0u)
#define HAL_LL_TIM_OUT_ACT_SET            (1u)
#define HAL_LL_TIM_OUT_ACT_CLEAR          (2u)
#define HAL_LL_TIM_OUT_ACT_TOGGLE         (3u)

#define HAL_LL_TIM_OUTCRx1_RG0_POS        (0u)
#define HAL_LL_TIM_OUTCRx1_RG1_POS        (2u)
#define HAL_LL_TIM_OUTCRx1_2BIT_MSK       (0x3u)

/* ==== TIM config (Toshiba T32Ax) ==== */
#define HAL_LL_TIM_PRSCL_1_1              (0x00)
#define HAL_LL_TIM_PRSCL_1_2              (0x01)
#define HAL_LL_TIM_PRSCL_1_8              (0x02)
#define HAL_LL_TIM_PRSCL_1_32             (0x03)
#define HAL_LL_TIM_PRSCL_1_128            (0x04)
#define HAL_LL_TIM_PRSCL_1_256            (0x05)
#define HAL_LL_TIM_PRSCL_1_512            (0x06)
#define HAL_LL_TIM_PRSCL_1_1024           (0x07)

#define HAL_LL_TIM_CLK_PRESC_OUT          (0x00)
#define HAL_LL_TIM_CLK_INT_TRIG           (0x01)
#define HAL_LL_TIM_CLK_RE_OUT             (0x02)
#define HAL_LL_TIM_CLK_FE_OUT             (0x03)
#define HAL_LL_TIM_CLK_RE_EXT             (0x04)
#define HAL_LL_TIM_CLK_FE_EXT             (0x05)

#define HAL_LL_TIM_WBF_DIS                (0)
#define HAL_LL_TIM_WBF_EN                 (1)

#define HAL_LL_TIM_UPDN_UP_COUNT          (0x00)
#define HAL_LL_TIM_UPDN_DOWN_COUNT        (0x01)
#define HAL_LL_TIM_UPDN_UP_DOWN_COUNT     (0x02)

#define HAL_LL_TIM_RELD_FREE_RUNNING      (0x00)
#define HAL_LL_TIM_RELD_INT_TRIG          (0x01)
#define HAL_LL_TIM_RELD_RE_EXT            (0x02)
#define HAL_LL_TIM_RELD_FE_EXT            (0x03)
#define HAL_LL_TIM_RELD_RE_OUT            (0x04)
#define HAL_LL_TIM_RELD_FE_OUT            (0x05)
#define HAL_LL_TIM_RELD_SYNC_OP           (0x06)
#define HAL_LL_TIM_RELD_MATCH_B1          (0x07)

#define HAL_LL_TIM_CR_RELD_POS            (8u)
#define HAL_LL_TIM_CR_UPDN_POS            (16u)
#define HAL_LL_TIM_CR_WBF_POS             (20u)
#define HAL_LL_TIM_CR_CLK_POS             (24u)
#define HAL_LL_TIM_CR_PRESCL_POS          (28u)

#define HAL_LL_CG_FSYSMENA   ((volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENA_ADDR)
#define HAL_LL_CG_FSYSMENB   ((volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENB_ADDR)
#define HAL_LL_CG_PROTECT    ((volatile uint32_t *)HAL_LL_CG_BASE_PROTECT_ADDR)

#define HAL_LL_CG_PROTECT_OPEN_KEY        (0xC1u)
#define HAL_LL_CG_PROTECT_CLOSE_KEY       (0x00u)

#define TSB_CG_FSYSMENA_IPMENA28_POS      (28u)
#define TSB_CG_FSYSMENA_IPMENA29_POS      (29u)
#define TSB_CG_FSYSMENA_IPMENA30_POS      (30u)
#define TSB_CG_FSYSMENA_IPMENA31_POS      (31u)
#define TSB_CG_FSYSMENB_IPMENB00_POS      (0u)
#define TSB_CG_FSYSMENB_IPMENB01_POS      (1u)

#define HAL_LL_DUTY_RATIO_MIN             (0.0f)
#define HAL_LL_DUTY_RATIO_MAX             (1.0f)
#define HAL_LL_ROUNDING_BIAS              (0.5f)
#define HAL_LL_ONE_TICK                   (1u)

#define HAL_LL_TIM_RUN_RG0_EN_POS         (0u)
#define HAL_LL_TIM_RUN_RG1_EN_POS         (1u)

#define HAL_LL_TIM_ENABLE_AND_START       ( 0x00000003 )
#define HAL_LL_TIM_DISABLE_AND_STOP       ( 0x00000004 )

#define HAL_LL_TIM_RUN_STOP_ALL           (0u)

#define HAL_LL_DEFAULT_TIM_CLK_HZ         (60000000u)
#define HAL_LL_DEFAULT_PWM_HZ             (1000u)

#define HAL_LL_DIV_1                      (1u)
#define HAL_LL_DIV_2                      (2u)
#define HAL_LL_DIV_8                      (8u)
#define HAL_LL_DIV_32                     (32u)
#define HAL_LL_DIV_128                    (128u)
#define HAL_LL_DIV_256                    (256u)
#define HAL_LL_DIV_512                    (512u)
#define HAL_LL_DIV_1024                   (1024u)

#define HAL_LL_TIM_COUNTER_TOP_MAX        (0xFFFFu)
#define HAL_LL_TIM_COUNTER_RANGE          ((uint32_t)HAL_LL_TIM_COUNTER_TOP_MAX + 1u)
#define HAL_LL_MIN_TICKS                  (2u)

#define HAL_LL_ROUNDING_DIV               (2u)

#define HAL_LL_TIM_CR_PRESC_POS           (HAL_LL_TIM_CR_PRESCL_POS)
#define HAL_LL_TIM_CR_PRESC_MSK           ( HAL_LL_MASK(3u, HAL_LL_TIM_CR_PRESC_POS) )
#define HAL_LL_TIM_CR_PRESC(V)            ( (uint32_t)(V) << HAL_LL_TIM_CR_PRESC_POS )

#define HAL_LL_TIM_MOD32_MASK             (0x00000001 << 0)

#define HAL_LL_TIM_OUTCR0_OCR_MASK       (0x00000003 << 0)
#define HAL_LL_TIM_OUTCR1_OCRCMP1_MASK   (0x00000003 << 2)
#define HAL_LL_TIM_OUTCR1_OCRCMPC0_MASK  (0x00000003 << 0)
#define HAL_LL_TIM_RUN_MASK              (0x00000001 << 0)
#define HAL_LL_TIM_RUN_SFTSTA_MASK       (0x00000001 << 1)
#define HAL_LL_TIM_RUN_SFTSTP_MASK       (0x00000001 << 2)

#define HAL_LL_TIM_OUTCRx1_RG0(ACT)     ((uint32_t)(ACT) << HAL_LL_TIM_OUTCRx1_RG0_POS)
#define HAL_LL_TIM_OUTCRx1_RG1(ACT)     ((uint32_t)(ACT) << HAL_LL_TIM_OUTCRx1_RG1_POS)

#define HAL_LL_TIM_OUTCR_CLEAR_RG0_SET_RG1 \
        ( HAL_LL_TIM_OUTCRx1_RG0(HAL_LL_TIM_OUT_ACT_CLEAR) | HAL_LL_TIM_OUTCRx1_RG1(HAL_LL_TIM_OUT_ACT_SET) )

#define HAL_LL_TIM_OUTCR_SET_RG0_CLEAR_RG1 \
        ( HAL_LL_TIM_OUTCRx1_RG0(HAL_LL_TIM_OUT_ACT_SET) | HAL_LL_TIM_OUTCRx1_RG1(HAL_LL_TIM_OUT_ACT_CLEAR) )

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Structure representing a subset of TIM registers. */
typedef struct
{
    uint32_t run;             /* 0x0040 - Run Register */
    uint32_t cr;              /* 0x0044 - Counter Control Register */
    uint32_t capcr;           /* 0x0048 - Capture Control Register */
    uint32_t outcr0;          /* 0x004C - Output Control Register 0 */
    uint32_t outcr1;          /* 0x0050 - Output Control Register 1 */
    uint32_t st;              /* 0x0054 - Status Register */
    uint32_t im;              /* 0x0058 - Interrupt Mask Register */
    uint32_t tmr;             /* 0x005C - Counter Capture Register */
    uint32_t reld;            /* 0x0060 - Counter Reload Register */
    uint32_t rg0;             /* 0x0064 - Timer Register 0 */
    uint32_t rg1;             /* 0x0068 - Timer Register 1 */
    uint32_t cap0;            /* 0x006C - Capture Register 0 */
    uint32_t cap1;            /* 0x0070 - Capture Register 1 */
    uint32_t dma;             /* 0x0074 - DMA Request Enable Register */
    uint32_t cp0;             /* 0x0078 - Compare Register 0 */
    uint32_t cp1;             /* 0x007C - Compare Register 1 */
} hal_ll_tim_register_subset_t;

/*!< @brief TIM register structure. */
typedef struct
{
    uint32_t mod;             /* 0x0000 - Mode Register */
    uint32_t _unused0[15];    /* 0x0004 - 0x003C : Reserved */

    hal_ll_tim_register_subset_t timerA; /*!< Timer A Registers */
    hal_ll_tim_register_subset_t timerB; /*!< Timer B Registers */
    hal_ll_tim_register_subset_t timerC; /*!< Timer C Registers */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_tim_pin_type_t pin_type;
    uint8_t af;
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
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_5)},
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
  * @brief  Open clock gate protection.
  * @return none
  */
static void hal_ll_cg_protect_open(void);

/**
  * @brief Close clock gate protection.
  * @return none
  */
static void hal_ll_cg_protect_close(void);

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

    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty(handle_t *handle, float duty_ratio) {
    hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local =
                        hal_ll_get_specifics(hal_ll_tim_get_module_state_address);
    hal_ll_tim_base_handle_t *hal_ll_hw_reg =
                        hal_ll_tim_get_base_struct(hal_ll_tim_hw_specifics_map_local->base);

    hal_ll_tim_pin_type_t pin_type = hal_ll_tim_hw_specifics_map_local->config.pin_type;

    // Clamp duty ratio between 0 and 1
    if ( HAL_LL_DUTY_RATIO_MIN > duty_ratio ) duty_ratio = HAL_LL_DUTY_RATIO_MIN;
    if ( HAL_LL_DUTY_RATIO_MAX < duty_ratio ) duty_ratio = HAL_LL_DUTY_RATIO_MAX;

    // Select appropriate timer channel subset
    hal_ll_tim_register_subset_t *tim_regs = NULL;

    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            tim_regs = &hal_ll_hw_reg->timerA;
            break;

        case HAL_LL_TIM_PIN_B:
            tim_regs = &hal_ll_hw_reg->timerB;
            break;

        case HAL_LL_TIM_PIN_C:
            tim_regs = &hal_ll_hw_reg->timerC;
            break;

        default:
            return HAL_LL_TIM_MODULE_ERROR;
    }

    // Calculate the period in ticks
    uint32_t period = tim_regs->rg1 - tim_regs->reld + 1u;
    if ( !period ) {
        return HAL_LL_TIM_MODULE_ERROR; // Frequency not set yet
    }

    // RM p.56: "Do not modify OUTCRx1 while RUNx = 1."
    const bool was_running = ( tim_regs->run & HAL_LL_TIM_RUN_MASK ) != 0u;
    if ( was_running ) {
        tim_regs->run |= HAL_LL_TIM_RUN_SFTSTP_MASK; // Stop counter
        tim_regs->run &= ~HAL_LL_TIM_RUN_MASK;   // Disable timer operation
    }

    /*
     * Calculate high_ticks (rounded)
     * high_ticks = duty_ratio * period
     * RGx0 = RGx1 - high_ticks + 1
     */
    double ht = ( double )period * ( double )duty_ratio;
    uint32_t high_ticks = ( uint32_t )( ht + 0.5 );

    if ( 0u == high_ticks ) {
        // Output should always be low
        tim_regs->outcr1 = 0u;
        uint32_t temp_reg = tim_regs->outcr0 & ~HAL_LL_TIM_OUTCR0_OCR_MASK;
        temp_reg |= 2u << 0; // 10b -> force LOW
        tim_regs->outcr0 = temp_reg;
    } else if ( period <= high_ticks ) {
        // Output should always be high
        tim_regs->outcr1 = 0u;
        uint32_t temp_reg = tim_regs->outcr0 & ~HAL_LL_TIM_OUTCR0_OCR_MASK;
        temp_reg |= 1u << 0; // 01b -> force HIGH
        tim_regs->outcr0 = temp_reg;
    } else {
        // Set compare register for PWM edge position
        tim_regs->rg0 = tim_regs->rg1 - ( high_ticks - 1u );

        // Clear output on match with C1
        uint32_t temp_reg = tim_regs->outcr1 & ~HAL_LL_TIM_OUTCR1_OCRCMP1_MASK;
        temp_reg |= 2u << 2;
        tim_regs->outcr1 = temp_reg;

        // Set output on match with C0
        temp_reg = tim_regs->outcr1 & ~HAL_LL_TIM_OUTCR1_OCRCMPC0_MASK;
        temp_reg |= 1u << 0;
        tim_regs->outcr1 = temp_reg;
    }

    // Restore timer state
    if ( was_running ) {
        tim_regs->run |= HAL_LL_TIM_RUN_MASK;
        tim_regs->run |= HAL_LL_TIM_RUN_SFTSTA_MASK;
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local =
                    hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg =
                    hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    hal_ll_tim_pin_type_t pin_type =  hal_ll_tim_hw_specifics_map_local->config.pin_type;

    // Enable operation for timer and start the counter
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->timerA.run = HAL_LL_TIM_ENABLE_AND_START;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->timerB.run = HAL_LL_TIM_ENABLE_AND_START;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->timerC.run = HAL_LL_TIM_ENABLE_AND_START;
            break;

        default:
            return HAL_LL_TIM_WRONG_PIN;
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // Disable the timer and stop the counter
    switch ( hal_ll_tim_hw_specifics_map_local->config.pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->timerA.run = HAL_LL_TIM_DISABLE_AND_STOP;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->timerB.run = HAL_LL_TIM_DISABLE_AND_STOP;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->timerC.run = HAL_LL_TIM_DISABLE_AND_STOP;
            break;

        default:
            return HAL_LL_TIM_WRONG_PIN;
    }

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if ( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz =    0;

        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, true );
        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.pin_type = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = 0u;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                                hal_ll_tim_handle_register_t *handle_map ) {
    hal_ll_pin_name_t pin_num;
    uint8_t index_counter =  0;
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
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) /
                                         ( sizeof( hal_ll_tim_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle ==
                        hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_tim_module_enable(hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state) {
    if (map == NULL) return;

    hal_ll_cg_protect_open();

    switch ( map->module_index ) {
        #ifdef TIM_MODULE_0
        case hal_ll_tim_module_num( TIM_MODULE_0 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA28_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA28_POS );
            }
            break;
        #endif
        #ifdef TIM_MODULE_1
        case hal_ll_tim_module_num( TIM_MODULE_1 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA29_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA29_POS );
            }
            break;
        #endif
        #ifdef TIM_MODULE_2
        case hal_ll_tim_module_num( TIM_MODULE_2 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA30_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA30_POS );
            }
            break;
        #endif
        #ifdef TIM_MODULE_3
        case hal_ll_tim_module_num( TIM_MODULE_3 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA31_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA31_POS );
            }
            break;
        #endif
        #ifdef TIM_MODULE_4
        case hal_ll_tim_module_num( TIM_MODULE_4 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB00_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB00_POS );
            }
            break;
        #endif
        #ifdef TIM_MODULE_5
        case hal_ll_tim_module_num( TIM_MODULE_5 ):
            if ( hal_ll_state ) {
                set_reg_bit( HAL_LL_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB01_POS );
            } else {
                clear_reg_bit( HAL_LL_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB01_POS );
            }
            break;
        #endif

        default:
            break;
    }

    hal_ll_cg_protect_close();
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_type = hal_ll_tim_pin_map[ index ].pin_type;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                      bool hal_ll_state ) {
    module_struct module;

    if ( map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] =   VALUE( map->config.pin, map->config.af );
        module.pins[1] =   GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_TIM_AF_CONFIG;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t period_ticks;

    CG_ClocksTypeDef cg;
    CG_GetClocksFrequency(&cg);
    uint32_t g_sysclk_hz = cg.CG_FT0M_Frequency;

    hal_ll_tim_register_subset_t *regs = NULL;

    // Select which timer subset to use
    switch (map->config.pin_type) {
        case HAL_LL_TIM_PIN_A:
            regs = &hal_ll_hw_reg->timerA;
            break;
        case HAL_LL_TIM_PIN_B:
            regs = &hal_ll_hw_reg->timerB;
            break;
        case HAL_LL_TIM_PIN_C:
            regs = &hal_ll_hw_reg->timerC;
            break;

        default:
            return 0; // Invalid type
    }

    // Stop timer before modifying registers
    const bool was_running = ( regs->run & HAL_LL_TIM_RUN_MASK ) ? true : false;

    if ( was_running ) {
        regs->run |= HAL_LL_TIM_RUN_SFTSTP_MASK;  // Stop counter
        regs->run &= ~HAL_LL_TIM_RUN_MASK;    // Disable operation
    }

    /*
     * period_ticks = RGx1 - RELDx + 1
     * T_pwm = period_ticks * (1/g_sysclk_hz)
     * => 1/map->freq_hz = (RGx1 - RELDx + 1) / g_sysclk_hz
     * => RGx1 = (g_sysclk_hz / map->freq_hz) + RELDx - 1
     */
    regs->rg1 = (g_sysclk_hz / map->freq_hz) - 1 + regs->reld;

    // Restore timer state
    if ( was_running ) {
        regs->run |= HAL_LL_TIM_RUN_MASK;
        regs->run |= HAL_LL_TIM_RUN_SFTSTA_MASK;
    }

    period_ticks = g_sysclk_hz / map->freq_hz;
    return period_ticks;
}

static void hal_ll_cg_protect_open(void) {
    write_reg(HAL_LL_CG_PROTECT, HAL_LL_CG_PROTECT_OPEN_KEY);
}

static void hal_ll_cg_protect_close(void) {
    write_reg(HAL_LL_CG_PROTECT, HAL_LL_CG_PROTECT_CLOSE_KEY);
}

static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    hal_ll_tim_pin_type_t pin_type = map->config.pin_type;

    // Select proper timer subset (A, B, or C)
    hal_ll_tim_register_subset_t *tim_regs = NULL;

    switch ( pin_type )
    {
       case HAL_LL_TIM_PIN_A:
            tim_regs = &hal_ll_hw_reg->timerA;
            hal_ll_hw_reg->mod &= ~HAL_LL_TIM_MOD32_MASK;
           break;
       case HAL_LL_TIM_PIN_B:
            tim_regs = &hal_ll_hw_reg->timerB;
            hal_ll_hw_reg->mod &= ~HAL_LL_TIM_MOD32_MASK;
           break;
       case HAL_LL_TIM_PIN_C:
            tim_regs = &hal_ll_hw_reg->timerC;
            hal_ll_hw_reg->mod |= HAL_LL_TIM_MOD32_MASK;
           break;

        default:
            return 0u;
    }

    tim_regs->cr =
        ( HAL_LL_TIM_RELD_MATCH_B1 << HAL_LL_TIM_CR_RELD_POS ) |
        ( HAL_LL_TIM_UPDN_UP_COUNT << HAL_LL_TIM_CR_UPDN_POS ) |
        ( HAL_LL_TIM_WBF_DIS       << HAL_LL_TIM_CR_WBF_POS )  |
        ( HAL_LL_TIM_CLK_PRESC_OUT << HAL_LL_TIM_CR_CLK_POS )  |
        ( HAL_LL_TIM_PRSCL_1_1     << HAL_LL_TIM_CR_PRESC_POS );

    tim_regs->reld   = 0u;
    tim_regs->outcr0 = 0x00u;
    tim_regs->outcr1 = HAL_LL_TIM_OUTCR_SET_RG0_CLEAR_RG1;

    uint32_t period = hal_ll_tim_set_freq_bare_metal(map);

    if ( !period ) {
        period = 0xFFFFu;
    }

    return period;
}

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
