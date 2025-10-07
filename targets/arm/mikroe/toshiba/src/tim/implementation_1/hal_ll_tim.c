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



#define T32A_OUT_ACT_NO_CHANGE            (0u)
#define T32A_OUT_ACT_SET                  (1u)
#define T32A_OUT_ACT_CLEAR                (2u)
#define T32A_OUT_ACT_TOGGLE               (3u)


#define T32A_OUTCRx1_RG0_POS              (0u)
#define T32A_OUTCRx1_RG1_POS              (2u)
#define T32A_OUTCRx1_2BIT_MSK             (0x3u)

/* ==== TIM config (Toshiba T32Ax) ==== */
#define PRSCL_1_1                         (0x00)
#define PRSCL_1_2                         (0x01)
#define PRSCL_1_8                         (0x02)
#define PRSCL_1_32                        (0x03)
#define PRSCL_1_128                       (0x04)
#define PRSCL_1_256                       (0x05)
#define PRSCL_1_512                       (0x06)
#define PRSCL_1_1024                      (0x07)

#define CLK_PRESC_OUT                     (0x00)
#define CLK_INT_TRIG                      (0x01)
#define CLK_RE_OUT                        (0x02)
#define CLK_FE_OUT                        (0x03)
#define CLK_RE_EXT                        (0x04)
#define CLK_FE_EXT                        (0x05)

#define WBF_DIS                           (0)
#define WBF_EN                            (1)

#define UPDN_UP_COUNT                     (0x00)
#define UPDN_DOWN_COUNT                   (0x01)
#define UPDN_UP_DOWN_COUNT                (0x02)

#define RELD_FREE_RUNNING                 (0x00)
#define RELD_INT_TRIG                     (0x01)
#define RELD_RE_EXT                       (0x02)
#define RELD_FE_EXT                       (0x03)
#define RELD_RE_OUT                       (0x04)
#define RELD_FE_OUT                       (0x05)
#define RELD_SYNC_OP                      (0x06)
#define RELD_MATCH_B1                     (0x07)
                                    
#define T32A_CR_RELD_POS                  (8u)  
#define T32A_CR_UPDN_POS                  (16u)  
#define T32A_CR_WBF_POS                   (20u) 
#define T32A_CR_CLK_POS                   (24u)  
#define CR_PRESCL_POS                     (28u)

#define TSB_CG_FSYSMENA                   (*(volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENA_ADDR)
#define TSB_CG_FSYSMENB                   (*(volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENB_ADDR)
#define TSB_CG_PROTECT                    (*(volatile uint32_t *)HAL_LL_CG_BASE_PROTECT_ADDR)

#define HAL_LL_CG_PROTECT_OPEN_KEY        (0xC1u)  
#define HAL_LL_CG_PROTECT_CLOSE_KEY       (0x00u) 


static inline void hal_ll_cg_protect_open(void)  { TSB_CG_PROTECT = HAL_LL_CG_PROTECT_OPEN_KEY;  }
static inline void hal_ll_cg_protect_close(void) { TSB_CG_PROTECT = HAL_LL_CG_PROTECT_CLOSE_KEY; }


#define TSB_CG_FSYSMENA_IPMENA28_POS      (28u)
#define TSB_CG_FSYSMENA_IPMENA29_POS      (29u)
#define TSB_CG_FSYSMENA_IPMENA30_POS      (30u)
#define TSB_CG_FSYSMENA_IPMENA31_POS      (31u)
#define TSB_CG_FSYSMENB_IPMENB00_POS      (0u)
#define TSB_CG_FSYSMENB_IPMENB01_POS      (1u)

#define HAL_LL_BIT(POS)                   ((uint32_t)1u << (POS))
#define HAL_LL_MASK(WIDTH, POS)           ((((uint32_t)1u << (WIDTH)) - 1u) << (POS))

#define HAL_LL_SET_BIT(REG, POS)          ((REG) |=  HAL_LL_BIT(POS))
#define HAL_LL_CLR_BIT(REG, POS)          ((REG) &= ~HAL_LL_BIT(POS))
#define HAL_LL_WRITE_BIT(REG, POS, VAL) do { if (VAL) (REG) |= HAL_LL_BIT(POS); else (REG) &= ~HAL_LL_BIT(POS); } while (0)

#define HAL_LL_DUTY_RATIO_MIN             (0.0f)
#define HAL_LL_DUTY_RATIO_MAX             (1.0f)
#define HAL_LL_ROUNDING_BIAS              (0.5f)
#define HAL_LL_ONE_TICK                   (1u)

#define T32A_RUN_RG0_EN_POS               (0u)
#define T32A_RUN_RG1_EN_POS               (1u)

#define T32A_RUN_RG0_EN                   HAL_LL_BIT(T32A_RUN_RG0_EN_POS)
#define T32A_RUN_RG1_EN                   HAL_LL_BIT(T32A_RUN_RG1_EN_POS)

#define T32A_ENABLE_AND_START            ( 0x00000003 )
#define T32A_DISABLE_AND_STOP            ( 0x00000004 )

#define T32A_RUN_START_BOTH               (T32A_RUN_RG0_EN | T32A_RUN_RG1_EN)
#define T32A_RUN_STOP_ALL                 (0u) 

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

#define T32A_COUNTER_TOP_MAX              (0xFFFFu)
#define T32A_COUNTER_RANGE                ((uint32_t)T32A_COUNTER_TOP_MAX + 1u)  
#define HAL_LL_MIN_TICKS                  (2u)  

#define HAL_LL_ROUNDING_DIV               (2u)

#define T32A_CR_PRESC_POS                 (CR_PRESCL_POS)                
#define T32A_CR_PRESC_MSK                 ( HAL_LL_MASK(3u, T32A_CR_PRESC_POS) ) 
#define T32A_CR_PRESC(V)                  ( (uint32_t)(V) << T32A_CR_PRESC_POS )

#define T32A_MOD32_mask                   (0x00000001 << 0)


#define UPDNC_mask     (0x00000003 << 16)
#define PRSCLC_mask    (0x00000007 << 28)
#define CLCK_mask      (0x00000007 << 24)
#define RELDC_mask     (0x00000007 << 8)
#define OCRC_mask      (0x00000003 << 0)
#define OCRCMPC1_mask  (0x00000003 << 2)
#define OCRCMPC0_mask  (0x00000003 << 0)
#define RUNC_mask      (0x00000001 << 0)
#define SFTSTAC_mask   (0x00000001 << 1)
#define SFTSTPC_mask   (0x00000001 << 2)
  

static inline uint32_t _tim_input_clk_hz(void)
{
    CG_ClocksTypeDef clks;
    CG_GetClocksFrequency(&clks);
    return clks.CG_FT0H_Frequency;
}
 
#define T32A_OUTCRx1_RG0(ACT)   ((uint32_t)(ACT) << T32A_OUTCRx1_RG0_POS)
#define T32A_OUTCRx1_RG1(ACT)   ((uint32_t)(ACT) << T32A_OUTCRx1_RG1_POS)

#define HAL_LL_TIM_OUTCR_CLEAR_RG0_SET_RG1 \
        ( T32A_OUTCRx1_RG0(T32A_OUT_ACT_CLEAR) | T32A_OUTCRx1_RG1(T32A_OUT_ACT_SET) )

#define HAL_LL_TIM_OUTCR_SET_RG0_CLEAR_RG1 \
        ( T32A_OUTCRx1_RG0(T32A_OUT_ACT_SET) | T32A_OUTCRx1_RG1(T32A_OUT_ACT_CLEAR) )

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct
{
   /* ==== Common register ==== */
    uint32_t mod;                        /* 0x0000 - Mode Register */

    uint32_t _unused0[15];               /* 0x0004 - 0x003C : Reserved */

    /* ==== Timer A Registers ==== */
     uint32_t runa;                       /* 0x0040 - Run Register A */
     uint32_t cra;                        /* 0x0044 - Counter Control Register A */
     uint32_t capcra;                     /* 0x0048 - Capture Control Register A */
     uint32_t outcra0;                    /* 0x004C - Output Control Register A0 */
     uint32_t outcra1;                    /* 0x0050 - Output Control Register A1 */
     uint32_t sta;                        /* 0x0054 - Status Register A */
     uint32_t ima;                        /* 0x0058 - Interrupt Mask Register A */
     uint32_t tmra;                       /* 0x005C - Counter Capture Register A */
     uint32_t relda;                      /* 0x0060 - Counter Reload Register A */
     uint32_t rga0;                       /* 0x0064 - Timer Register A0 */
     uint32_t rga1;                       /* 0x0068 - Timer Register A1 */
     uint32_t capa0;                      /* 0x006C - Capture Register A0 */
     uint32_t capa1;                      /* 0x0070 - Capture Register A1 */
     uint32_t dmaa;                       /* 0x0074 - DMA Request Enable Register A */
     uint32_t cpa0;                       /* 0x0078 - Compare Register A0 */
     uint32_t cpa1;                       /* 0x007C - Compare Register A1 */

    /* ==== Timer B Registers ==== */
     uint32_t runb;                       /* 0x0080 - Run Register B */
     uint32_t crb;                        /* 0x0084 - Counter Control Register B */
     uint32_t capcrb;                     /* 0x0088 - Capture Control Register B */
     uint32_t outcrb0;                    /* 0x008C - Output Control Register B0 */
     uint32_t outcrb1;                    /* 0x0090 - Output Control Register B1 */
     uint32_t stb;                        /* 0x0094 - Status Register B */
     uint32_t imb;                        /* 0x0098 - Interrupt Mask Register B */
     uint32_t tmrb;                       /* 0x009C - Counter Capture Register B */
     uint32_t reldb;                      /* 0x00A0 - Counter Reload Register B */
     uint32_t rgb0;                       /* 0x00A4 - Timer Register B0 */
     uint32_t rgb1;                       /* 0x00A8 - Timer Register B1 */
     uint32_t capb0;                      /* 0x00AC - Capture Register B0 */
     uint32_t capb1;                      /* 0x00B0 - Capture Register B1 */
     uint32_t dmab;                       /* 0x00B4 - DMA Request Enable Register B */
     uint32_t cpb0;                       /* 0x00B8 - Compare Register B0 */
     uint32_t cpb1;                       /* 0x00BC - Compare Register B1 */

    /* ==== Timer C Registers ==== */
     uint32_t runc;                       /* 0x00C0 - Run Register C */
     uint32_t crc;                        /* 0x00C4 - Counter Control Register C */
     uint32_t capcrc;                     /* 0x00C8 - Capture Control Register C */
     uint32_t outcrc0;                    /* 0x00CC - Output Control Register C0 */
     uint32_t outcrc1;                    /* 0x00D0 - Output Control Register C1 */
     uint32_t stc;                        /* 0x00D4 - Status Register C */
     uint32_t imc;                        /* 0x00D8 - Interrupt Mask Register C */
     uint32_t tmrc;                       /* 0x00DC - Counter Capture Register C */
     uint32_t reldc;                      /* 0x00E0 - Counter Reload Register C */
     uint32_t rgc0;                       /* 0x00E4 - Timer Register C0 */
     uint32_t rgc1;                       /* 0x00E8 - Timer Register C1 */
     uint32_t capc0;                      /* 0x00EC - Capture Register C0 */
     uint32_t capc1;                      /* 0x00F0 - Capture Register C1 */
     uint32_t dmac;                       /* 0x00F4 - DMA Request Enable Register C */
     uint32_t plscr;                      /* 0x00F8 - Pulse Count Control Register */
     uint32_t cpc0;                       /* 0x00FC - Compare Register C0 */
     uint32_t cpc1;                       /* 0x0100 - Compare Register C1 */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_tim_pin_type_t pin_type;
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

    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct(hal_ll_tim_hw_specifics_map_local->base);

    // which channel is used A/B/C
    hal_ll_tim_pin_type_t pin_type = hal_ll_tim_hw_specifics_map_local->config.pin_type;
    
    // Clamp duty_ratio between 0 and 1
    if (duty_ratio < HAL_LL_DUTY_RATIO_MIN) duty_ratio = HAL_LL_DUTY_RATIO_MIN;
    if (duty_ratio > HAL_LL_DUTY_RATIO_MAX) duty_ratio = HAL_LL_DUTY_RATIO_MAX;

    // helper registers
    struct tim_ch_regs_t{
            uint32_t *RUNx;
            uint32_t *OUTCRx0;
            uint32_t *OUTCRx1;
            uint32_t *RGx0;
            uint32_t *RGx1;
            uint32_t *RELDx;        
    }ch;

    switch (pin_type)
    {
       case HAL_LL_TIM_PIN_A:
            ch.RUNx  = &hal_ll_hw_reg->runa;  ch.OUTCRx0 = &hal_ll_hw_reg->outcra0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcra1;
            ch.RGx0  = &hal_ll_hw_reg->rga0;  ch.RGx1  = &hal_ll_hw_reg->rga1;       ch.RELDx = &hal_ll_hw_reg->relda;
       break;
       case HAL_LL_TIM_PIN_B:
            ch.RUNx  = &hal_ll_hw_reg->runb;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrb0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrb1;
            ch.RGx0  = &hal_ll_hw_reg->rgb0;  ch.RGx1  = &hal_ll_hw_reg->rgb1;       ch.RELDx = &hal_ll_hw_reg->reldb;
       break;
       case HAL_LL_TIM_PIN_C:
            ch.RUNx  = &hal_ll_hw_reg->runc;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrc0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrc1;
            ch.RGx0  = &hal_ll_hw_reg->rgc0;  ch.RGx1  = &hal_ll_hw_reg->rgc1;       ch.RELDx = &hal_ll_hw_reg->reldc;
       break;
    }

    uint32_t period = *ch.RGx1 - *ch.RELDx + 1;
    if(period == 0) return HAL_LL_TIM_MODULE_ERROR; // Freq has not been set yet
    
    // RM page 56 => "Do not make any changes of [T32AxOUTCRC1] register while the [T32AxRUNC]<RUNC> = 1. "
    const bool was_running = ((*ch.RUNx) & RUNC_mask) != 0;
    if (was_running) {
        *ch.RUNx |= SFTSTPC_mask;     // stops counter
        *ch.RUNx &= ~RUNC_mask;        // disables the operation of timer
    }
    

    /*
       * calculate high_ticks(must be rounded)
       * period_ticks = RGx1 - RELDx + 1
       * duty = high_ticks / period_ticks
       * high_ticks = duty * period_ticks
       * RGx0 = RGx1 - high_ticks + 1
    */
    double ht = (double)period * (double)duty_ratio;
    uint32_t high_ticks = (uint32_t)(ht + 0.5);

    if (high_ticks == 0u) {
        // output should always be low => force it with OUTx0
        *ch.OUTCRx1 = 0u; // invalid capture/compare logic
        uint32_t temp_reg = *ch.OUTCRx0 & ~OCRC_mask;
        temp_reg |= (2 << 0 );        // 10b -> LOW
        *ch.OUTCRx0 = temp_reg;       // force out to be low
    } else if (high_ticks >= period) {
        // output should always be high => force it with OUTx0
        *ch.OUTCRx1 = 0u; 
        uint32_t temp_reg = *ch.OUTCRx0 & ~OCRC_mask;
        temp_reg |= (1 << 0 );        // 01b -> HIGH
        *ch.OUTCRx0 = temp_reg;       //force out to be high
    } else {
        // calculate RGx0 based on the wanted duty_ratio
        *ch.RGx0 = *ch.RGx1 - (high_ticks - 1u);

        // make sure output is low before the compare match
        // uint32_t temp_reg = *ch.OUTCRx0 & ~OCRC_mask;
        // temp_reg |= (2 << 0 );        // 10b -> LOW
        // *ch.OUTCRx0 = temp_reg; // force out to be low

        // clear output when counter c1
        uint32_t temp_reg = *ch.OUTCRx1 & (~OCRCMPC1_mask);
        temp_reg |= (2 << 2);
        *ch.OUTCRx1 = temp_reg;

        //set output when counter reaches c0
        temp_reg = *ch.OUTCRx1 & (~OCRCMPC0_mask);
        temp_reg |= (1 << 0);
        *ch.OUTCRx1 = temp_reg;
    }
    
    // load back the state that timer was in
    if (was_running) {
        *ch.RUNx |= RUNC_mask;
        *ch.RUNx |= SFTSTAC_mask;     
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    hal_ll_tim_pin_type_t pin_type =  hal_ll_tim_hw_specifics_map_local->config.pin_type;

    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->runa = T32A_ENABLE_AND_START; // enable operation for timer and start the conter 
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->runb = T32A_ENABLE_AND_START;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->runc = T32A_ENABLE_AND_START;
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

    switch ( hal_ll_tim_hw_specifics_map_local->config.pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->runa = T32A_DISABLE_AND_STOP; // disable timer and stops the counter  
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->runb = T32A_DISABLE_AND_STOP;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->runc = T32A_DISABLE_AND_STOP; 
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
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_tim_module_enable(hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state) {
    if (map == NULL) return;

    hal_ll_cg_protect_open();   

    switch (map->module_index) {
        case 0:
            HAL_LL_WRITE_BIT( TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA28_POS, hal_ll_state); 
            break;
        case 1:
            HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA29_POS, hal_ll_state);
            break;
        case 2: 
            HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA30_POS, hal_ll_state);
            break;
        case 3:
            HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA31_POS, hal_ll_state); 
            break;
        case 4: 
            HAL_LL_WRITE_BIT(TSB_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB00_POS, hal_ll_state);
            break;
        case 5: 
            HAL_LL_WRITE_BIT(TSB_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB01_POS, hal_ll_state);
            break;
        default: break;
    }

     hal_ll_cg_protect_close();  
}

static uint32_t hal_ll_tim_clock_source() {
     return CLK_PRESC_OUT; 
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_type = hal_ll_tim_pin_map[ index ].pin_type;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
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
    uint32_t period;

    CG_ClocksTypeDef cg;
    CG_GetClocksFrequency(&cg);
    uint32_t g_sysclk_hz = cg.CG_FT0M_Frequency;


    // which channel is used A/B/C
    hal_ll_tim_pin_type_t pin_type = map->config.pin_type;

    // helper registers
    struct tim_ch_regs_t{
            uint32_t *RUNx;
            uint32_t *OUTCRx0;
            uint32_t *OUTCRx1;
            uint32_t *RGx0;
            uint32_t *RGx1;
            uint32_t *RELDx;        
    }ch;

    switch (pin_type)
    {
       case HAL_LL_TIM_PIN_A:
            ch.RUNx  = &hal_ll_hw_reg->runa;  ch.OUTCRx0 = &hal_ll_hw_reg->outcra0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcra1;
            ch.RGx0  = &hal_ll_hw_reg->rga0;  ch.RGx1  = &hal_ll_hw_reg->rga1;       ch.RELDx = &hal_ll_hw_reg->relda;
       break;
       case HAL_LL_TIM_PIN_B:
            ch.RUNx  = &hal_ll_hw_reg->runb;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrb0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrb1;
            ch.RGx0  = &hal_ll_hw_reg->rgb0;  ch.RGx1  = &hal_ll_hw_reg->rgb1;       ch.RELDx = &hal_ll_hw_reg->reldb;
       break;
       case HAL_LL_TIM_PIN_C:
            ch.RUNx  = &hal_ll_hw_reg->runc;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrc0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrc1;
            ch.RGx0  = &hal_ll_hw_reg->rgc0;  ch.RGx1  = &hal_ll_hw_reg->rgc1;       ch.RELDx = &hal_ll_hw_reg->reldc;
       break;
    }

    // RM page 56 => "Do not make any changes of [T32AxOUTCRC1] register while the [T32AxRUNC]<RUNC> = 1. "
    const bool was_running = ((*ch.RUNx) & RUNC_mask) != 0;
    if (was_running) {
        *ch.RUNx |= SFTSTPC_mask;     // stops counter
        *ch.RUNx &= ~RUNC_mask;       // disables the operation of timer
    }
    
    /*
      * period_ticks = RGx1 - RELDx + 1
      * T_pwm = period_ticks * T_clk, Tclk = 1/g_sysclk_hz, T_pwm = 1/map->freq_hz
      * 1/map->freq_hz = ( RGx1 - RELDx + 1 ) / g_sysclk_hz
      * RGx1 = ( g_sysclk_hz/map->freq_hz ) + RELDx - 1
    */
    *ch.RGx1 = (g_sysclk_hz/map->freq_hz) - 1 + *ch.RELDx;


    // load back the state that timer was in
    if (was_running) {
        *ch.RUNx |= RUNC_mask;
        *ch.RUNx |= SFTSTAC_mask;     
    }
   
    // calculate period_ticks based on updated RGx1
    uint32_t period_ticks  = g_sysclk_hz/map->freq_hz;

    return period_ticks;


}


static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    hal_ll_tim_pin_type_t pin_type = map->config.pin_type;

    // helper registers
    struct tim_ch_regs_t{
            uint32_t *RUNx;
            uint32_t *OUTCRx0;
            uint32_t *OUTCRx1;
            uint32_t *CRx;
            uint32_t *RELDx;       
            uint32_t *RGx0; 
    }ch;

    switch (pin_type)
    {
       case HAL_LL_TIM_PIN_A:
            ch.RUNx  = &hal_ll_hw_reg->runa;  ch.OUTCRx0 = &hal_ll_hw_reg->outcra0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcra1;
            ch.CRx  = &hal_ll_hw_reg->cra;  ch.RELDx = &hal_ll_hw_reg->relda;        ch.RGx0  = &hal_ll_hw_reg->rga0;
            hal_ll_hw_reg->mod &= ~T32A_MOD32_mask;
       break;
       case HAL_LL_TIM_PIN_B:
            ch.RUNx  = &hal_ll_hw_reg->runb;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrb0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrb1;
            ch.CRx  = &hal_ll_hw_reg->crb;    ch.RELDx = &hal_ll_hw_reg->reldb;      ch.RGx0  = &hal_ll_hw_reg->rgb0;
            hal_ll_hw_reg->mod &= ~T32A_MOD32_mask;
       break;
       case HAL_LL_TIM_PIN_C:
            ch.RUNx  = &hal_ll_hw_reg->runc;  ch.OUTCRx0 = &hal_ll_hw_reg->outcrc0;  ch.OUTCRx1 = &hal_ll_hw_reg->outcrc1;
            ch.CRx  = &hal_ll_hw_reg->crc;    ch.RELDx = &hal_ll_hw_reg->reldc;      ch.RGx0  = &hal_ll_hw_reg->rgc0;
            hal_ll_hw_reg->mod |= T32A_MOD32_mask;
       break;
    }

    const uint32_t clk   = hal_ll_tim_clock_source();  

    *ch.CRx =
            ( RELD_MATCH_B1 << T32A_CR_RELD_POS   )   |   // reload when counter matches tiemr register C1
            ( UPDN_UP_COUNT << T32A_CR_UPDN_POS   )   |   // up counting
            ( WBF_DIS       << T32A_CR_WBF_POS    )   |   // disable double buffering
            ( clk           << T32A_CR_CLK_POS    )   |   // sets prescaler as a count clock
            ( PRSCL_1_1         << T32A_CR_PRESC_POS  );  // prescaler division ratio = 1/1

    *ch.RELDx = 0u;                                       // set default reload value to 0

    *ch.OUTCRx0 = 0x00u;                                  // clear output
    *ch.OUTCRx1 = HAL_LL_TIM_OUTCR_SET_RG0_CLEAR_RG1;     // set on C0 clear on C1

    uint32_t period = hal_ll_tim_set_freq_bare_metal( map );

    // dividing with 0 protection
    if ( period == 0u ) { period = 0xFFFFu; }

    return period;
  
}


static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
