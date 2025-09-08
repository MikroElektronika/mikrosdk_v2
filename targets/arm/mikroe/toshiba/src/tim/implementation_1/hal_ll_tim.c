/****************************************************************************
**
** Copyright (C) MikroElektronika d.o.o.
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

#define HAL_LL_TIM_AF_CONFIG ( \                                                                
    GPIO_CFG_MODE_OUTPUT_PP |                                    /* output + push-pull */ \
    (GPIO_CFG_ALT_FUNCTION << GPIO_CFG_ALT_FUNC_POS)           /*   ALT funkcija        */ \
    )

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base


/* ==== TIM config (Toshiba T32Ax) ==== */
#define PRSCL_1_1    0b000
#define PRSCL_1_2    0b001
#define PRSCL_1_8    0b010
#define PRSCL_1_32   0b011
#define PRSCL_1_128  0b100
#define PRSCL_1_256  0b101
#define PRSCL_1_512  0b110
#define PRSCL_1_1024 0b111

#define CLK_PRESC_OUT 0b000
#define CLK_INT_TRIG  0b001
#define CLK_RE_OUT    0b010
#define CLK_FE_OUT    0b011
#define CLK_RE_EXT    0b100
#define CLK_FE_EXT    0b101

#define WBF_DIS 0
#define WBF_EN  1

#define UPDN_UP_COUNT      0b00
#define UPDN_DOWN_COUNT    0b01
#define UPDN_UP_DOWN_COUNT 0b10

#define RELD_FREE_RUNNING 0b000
#define RELD_INT_TRIG     0b001
#define RELD_RE_EXT       0b010
#define RELD_FE_EXT       0b011
#define RELD_RE_OUT       0b100
#define RELD_FE_OUT       0b101
#define RELD_SYNC_OP      0b110
#define RELD_MATCH_B1     0b111

#define TSB_CG_FSYSMENA   (*(volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENA_ADDR)
#define TSB_CG_FSYSMENB   (*(volatile uint32_t *)HAL_LL_CG_BASE_FSYSMENB_ADDR)
#define TSB_CG_PROTECT   (*(volatile uint32_t *)HAL_LL_CG_BASE_PROTECT_ADDR)

#define HAL_LL_CG_PROTECT_OPEN_KEY   0xC1u  // CG registri su write-enabled
#define HAL_LL_CG_PROTECT_CLOSE_KEY  0x00u 

#define TSB_CG_FSYSMENA_IPMENA16_Pos 16u

static inline void hal_ll_cg_protect_open(void)  { TSB_CG_PROTECT = HAL_LL_CG_PROTECT_OPEN_KEY;  }
static inline void hal_ll_cg_protect_close(void) { TSB_CG_PROTECT = HAL_LL_CG_PROTECT_CLOSE_KEY; }

static inline void _enable_portu_clock(bool en)
{
    hal_ll_cg_protect_open();
    HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA16_Pos, en);
    (void)TSB_CG_FSYSMENA; // readback
    hal_ll_cg_protect_close();
}


#define TSB_CG_FSYSMENA_IPMENA28_Pos 28u
#define TSB_CG_FSYSMENA_IPMENA29_Pos 29u
#define TSB_CG_FSYSMENA_IPMENA30_Pos 30u
#define TSB_CG_FSYSMENA_IPMENA31_Pos 31u
#define TSB_CG_FSYSMENB_IPMENB00_Pos 0u
#define TSB_CG_FSYSMENB_IPMENB01_Pos 1u

#define HAL_LL_SET_BIT(reg, pos)     ((reg) |=  (uint32_t)(1u << (pos)))
#define HAL_LL_CLR_BIT(reg, pos)     ((reg) &= ~(uint32_t)(1u << (pos)))

#define HAL_LL_WRITE_BIT(reg,pos,val) \
    do { if (val) HAL_LL_SET_BIT((reg),(pos)); else HAL_LL_CLR_BIT((reg),(pos)); } while (0)


#define HAL_LL_TIM_OUTCR_SET_RG0_CLEAR_RG1 ((2u << 0) | (1u << 2))
// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct
{
   /* ==== Common register ==== */
    volatile uint32_t MOD;      /* 0x0000 - Mode Register */

    uint32_t RESERVED0[15];     /* 0x0004 - 0x003C : Reserved */

    /* ==== Timer A Registers ==== */
    volatile uint32_t RUNA;     /* 0x0040 - Run Register A */
    volatile uint32_t CRA;      /* 0x0044 - Counter Control Register A */
    volatile uint32_t CAPCRA;   /* 0x0048 - Capture Control Register A */
    volatile uint32_t OUTCRA0;  /* 0x004C - Output Control Register A0 */
    volatile uint32_t OUTCRA1;  /* 0x0050 - Output Control Register A1 */
    volatile uint32_t STA;      /* 0x0054 - Status Register A */
    volatile uint32_t IMA;      /* 0x0058 - Interrupt Mask Register A */
    volatile uint32_t TMRA;     /* 0x005C - Counter Capture Register A */
    volatile uint32_t RELDA;    /* 0x0060 - Counter Reload Register A */
    volatile uint32_t RGA0;     /* 0x0064 - Timer Register A0 */
    volatile uint32_t RGA1;     /* 0x0068 - Timer Register A1 */
    volatile uint32_t CAPA0;    /* 0x006C - Capture Register A0 */
    volatile uint32_t CAPA1;    /* 0x0070 - Capture Register A1 */
    volatile uint32_t DMAA;     /* 0x0074 - DMA Request Enable Register A */
    volatile uint32_t CPA0;     /* 0x0078 - Compare Register A0 */
    volatile uint32_t CPA1;     /* 0x007C - Compare Register A1 */

    /* ==== Timer B Registers ==== */
    volatile uint32_t RUNB;     /* 0x0080 - Run Register B */
    volatile uint32_t CRB;      /* 0x0084 - Counter Control Register B */
    volatile uint32_t CAPCRB;   /* 0x0088 - Capture Control Register B */
    volatile uint32_t OUTCRB0;  /* 0x008C - Output Control Register B0 */
    volatile uint32_t OUTCRB1;  /* 0x0090 - Output Control Register B1 */
    volatile uint32_t STB;      /* 0x0094 - Status Register B */
    volatile uint32_t IMB;      /* 0x0098 - Interrupt Mask Register B */
    volatile uint32_t TMRB;     /* 0x009C - Counter Capture Register B */
    volatile uint32_t RELDB;    /* 0x00A0 - Counter Reload Register B */
    volatile uint32_t RGB0;     /* 0x00A4 - Timer Register B0 */
    volatile uint32_t RGB1;     /* 0x00A8 - Timer Register B1 */
    volatile uint32_t CAPB0;    /* 0x00AC - Capture Register B0 */
    volatile uint32_t CAPB1;    /* 0x00B0 - Capture Register B1 */
    volatile uint32_t DMAB;     /* 0x00B4 - DMA Request Enable Register B */
    volatile uint32_t CPB0;     /* 0x00B8 - Compare Register B0 */
    volatile uint32_t CPB1;     /* 0x00BC - Compare Register B1 */

    /* ==== Timer C Registers ==== */
    volatile uint32_t RUNC;     /* 0x00C0 - Run Register C */
    volatile uint32_t CRC;      /* 0x00C4 - Counter Control Register C */
    volatile uint32_t CAPCRC;   /* 0x00C8 - Capture Control Register C */
    volatile uint32_t OUTCRC0;  /* 0x00CC - Output Control Register C0 */
    volatile uint32_t OUTCRC1;  /* 0x00D0 - Output Control Register C1 */
    volatile uint32_t STC;      /* 0x00D4 - Status Register C */
    volatile uint32_t IMC;      /* 0x00D8 - Interrupt Mask Register C */
    volatile uint32_t TMRC;     /* 0x00DC - Counter Capture Register C */
    volatile uint32_t RELDC;    /* 0x00E0 - Counter Reload Register C */
    volatile uint32_t RGC0;     /* 0x00E4 - Timer Register C0 */
    volatile uint32_t RGC1;     /* 0x00E8 - Timer Register C1 */
    volatile uint32_t CAPC0;    /* 0x00EC - Capture Register C0 */
    volatile uint32_t CAPC1;    /* 0x00F0 - Capture Register C1 */
    volatile uint32_t DMAC;     /* 0x00F4 - DMA Request Enable Register C */
    volatile uint32_t PLSCR;    /* 0x00F8 - Pulse Count Control Register */
    volatile uint32_t CPC0;     /* 0x00FC - Compare Register C0 */
    volatile uint32_t CPC1;     /* 0x0100 - Compare Register C1 */
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

    // Memorize information about the max period available (PWM duty cycle is dependant of this information).
    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty(handle_t *handle, float duty_ratio) {
    // Resolve low-level handles and HW register base
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct(hal_ll_tim_hw_specifics_map_local->base);

    // Which TIM channel (A/B/C) this instance uses
    hal_ll_tim_pin_type_t pin_type = hal_ll_tim_hw_specifics_map_local->config.pin_type;

    // Clamp requested duty to [0..100]%
    if (duty_ratio < 0.0f)  duty_ratio = 0.0f;
    if (duty_ratio > 100.0f) duty_ratio = 100.0f;

    // Get period (TOP) value:
    // Prefer cached max_period; if zero, read the active TOP from RGx1.
    uint32_t period = hal_ll_tim_hw_specifics_map_local->max_period;
    if (period == 0u) {
        switch (pin_type) {
            case HAL_LL_TIM_PIN_A: period = hal_ll_hw_reg->RGA1; break; // A channel TOP
            case HAL_LL_TIM_PIN_B: period = hal_ll_hw_reg->RGB1; break; // B channel TOP
#ifdef HAL_LL_TIM_PIN_C
            case HAL_LL_TIM_PIN_C: period = hal_ll_hw_reg->RGC1; break; // C channel TOP
#endif
            default: return HAL_LL_TIM_WRONG_PIN;
        }
        if (period == 0u) period = 0xFFFFu;                          
    }
    uint32_t top = period;
    uint32_t compare;

    // Explicitly map edge cases 0% and 100%
    if (duty_ratio <= 0.0f) {
        compare = 0u;                                                   // 0% duty
    } else if (duty_ratio >= 100.0f) {
        compare = top;                                                  // 100% duty
    } else {
        compare = (uint32_t)((duty_ratio/100.0f) * (float)(top + 1u) + 0.5f);
        if (compare > 0u) compare--;                                    // keep in [0..TOP]
    }
    switch (pin_type) {
        case HAL_LL_TIM_PIN_A: hal_ll_hw_reg->RGA0 = compare; break;
        case HAL_LL_TIM_PIN_B: hal_ll_hw_reg->RGB0 = compare; break;
#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C: hal_ll_hw_reg->RGC0 = compare; break;
#endif
        default: return HAL_LL_TIM_WRONG_PIN;
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
            hal_ll_hw_reg->RUNA = 0x03;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RUNB = 0x03;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RUNC = 0x03;
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
            hal_ll_hw_reg->RUNA = 0x00;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RUNB = 0x00;
            break;
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RUNC = 0x00;
            break;
        default:
            return HAL_LL_TIM_WRONG_PIN;
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

static void hal_ll_tim_module_enable(hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state) {
    if (map == NULL) return;

    hal_ll_cg_protect_open();   // otklju?aj CG

    switch (map->module_index) {
        case 0: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA28_Pos, hal_ll_state); 
            break;
        case 1: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA29_Pos, hal_ll_state);
            break;
        case 2: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA30_Pos, hal_ll_state);
            break;
        case 3: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENA, TSB_CG_FSYSMENA_IPMENA31_Pos, hal_ll_state); 
            break;
        case 4: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB00_Pos, hal_ll_state);
            break;
        case 5: HAL_LL_WRITE_BIT(TSB_CG_FSYSMENB, TSB_CG_FSYSMENB_IPMENB01_Pos, hal_ll_state);
            break;
        default: break;
    }

    // read-back za post write buffering:
    (void)TSB_CG_FSYSMENA; 
    (void)TSB_CG_FSYSMENB;

    hal_ll_cg_protect_close();  // zakljucaj CG
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
typedef struct
{
    volatile uint32_t DATA;  // 0x0000 - Data Register
    volatile uint32_t CR;    // 0x0004 - Output Control Register
    volatile uint32_t FR1;   // 0x0008 - Function Register 1
    volatile uint32_t FR2;   // 0x000C - Function Register 2
    volatile uint32_t FR3;   // 0x0010 - Function Register 3
    volatile uint32_t FR4;   // 0x0014 - Function Register 4
    volatile uint32_t FR5;   // 0x0018 - Function Register 5
    volatile uint32_t FR6;   // 0x001C - Function Register 6
    volatile uint32_t FR7;   // 0x0020 - Function Register 7
    uint32_t RESERVED0;      // 0x0024 - Reserved
    volatile uint32_t OD;    // 0x0028 - Open-Drain Control Register
    volatile uint32_t PUP;   // 0x002C - Pull-up Control Register
    volatile uint32_t PDN;   // 0x0030 - Pull-down Control Register
    uint32_t RESERVED1;      // 0x0034 - Reserved
    volatile uint32_t IE;    // 0x0038 - Input Control Register
} GPIO_Port_Registers;
#include"mcu.h"
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    // if( map->config.pin != HAL_LL_PIN_NC ) {
    //     module.pins[0] =   VALUE( map->config.pin, map->config.af );
    //     module.pins[1] =   GPIO_MODULE_STRUCT_END;

    //     module.configs[0] = HAL_LL_TIM_AF_CONFIG;
    //     module.configs[1] = GPIO_MODULE_STRUCT_END;

    //     hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    // }
        // Configure GPIO pin for PWM output
    GPIO_Port_Registers *gpio_port;
    gpio_port = (GPIO_Port_Registers *) TSB_PU_BASE;
    gpio_port->FR4 |= (1 << 4);

    gpio_port->CR |= (1 << 4);    // Configure as output
    //TSB_PU->CR  |= (1 << 4);
    gpio_port->IE &= ~(1 << 4);   // Disable interrupt input
    gpio_port->OD &= ~(1 << 4);   // Disable open-drain
    gpio_port->PUP &= ~(1 << 4);  // Disable pull-up
    gpio_port->PDN &= ~(1 << 4);  // Disable pull-down
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    /* 1) Izvorni takt timera (Hz):
       TODO: zameni HAL_LL_TIM_INPUT_CLK_HZ stvarnim pozivom iz CG koda kada ga ima?. */
#ifndef HAL_LL_TIM_INPUT_CLK_HZ
#define HAL_LL_TIM_INPUT_CLK_HZ 60000000UL /* privremeno: 60 MHz */
#endif

    uint32_t want_hz = map->freq_hz;               /* o?ekujemo da je frekvencija u Hz */
    if (want_hz == 0u) {                           /* fallback ako neko pozove sa 0 Hz */
        want_hz = 1000u;                           /* npr. 1 kHz default */
    }

    /* 2) Preskaler: probaj od 1:1 do 1:1024 */
    static const struct { uint8_t prscl_bits; uint32_t div; } prs_tbl[] = {
        { PRSCL_1_1,    1u    },
        { PRSCL_1_2,    2u    },
        { PRSCL_1_8,    8u    },
        { PRSCL_1_32,   32u   },
        { PRSCL_1_128,  128u  },
        { PRSCL_1_256,  256u  },
        { PRSCL_1_512,  512u  },
        { PRSCL_1_1024, 1024u }
    };

    uint32_t tim_clk_hz = HAL_LL_TIM_INPUT_CLK_HZ;
    uint32_t top = 0;
    uint8_t  chosen_prs_bits = PRSCL_1_1;
    uint32_t chosen_div = 1u;

    for (size_t i = 0; i < sizeof(prs_tbl)/sizeof(prs_tbl[0]); ++i) {
        uint32_t div = prs_tbl[i].div;
        uint32_t ticks = (uint32_t)((tim_clk_hz + (want_hz/2u)) / (want_hz * div)); /* zaokru?ivanje */
        if (ticks >= 2u && ticks <= 0x10000u) {  /* ?elimo 1..65536 taktova; TOP = ticks-1 -> staje u 16-bit */
            chosen_prs_bits = prs_tbl[i].prscl_bits;
            chosen_div = div;
            top = ticks - 1u;
            break;
        }
    }

    /* Ako ni jedan preskaler ne staje, uzmi max preskaler i saturi?i TOP */
    if (top == 0u) {
        chosen_prs_bits = PRSCL_1_1024;
        chosen_div = 1024u;
        uint32_t ticks = (uint32_t)((tim_clk_hz + (want_hz/2u)) / (want_hz * chosen_div));
        if (ticks < 2u) ticks = 2u;
        if (ticks > 0x10000u) ticks = 0x10000u;
        top = ticks - 1u;
    }

    /* 3) Upis PRSCL u odgovaraju?i CRx (zadr?avamo ostala polja kako su postavljena u hw_init) */
    switch ( map->config.pin_type ) {
        case HAL_LL_TIM_PIN_A: {
            uint32_t cr = hal_ll_hw_reg->CRA;
            cr &= ~(0x7u << 28);
            cr |= ((uint32_t)chosen_prs_bits << 28);
            hal_ll_hw_reg->CRA = cr;
        } break;
        case HAL_LL_TIM_PIN_B: {
            uint32_t cr = hal_ll_hw_reg->CRB;
            cr &= ~(0x7u << 28);
            cr |= ((uint32_t)chosen_prs_bits << 28);
            hal_ll_hw_reg->CRB = cr;
        } break;
#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C: {
            uint32_t cr = hal_ll_hw_reg->CRC;
            cr &= ~(0x7u << 28);
            cr |= ((uint32_t)chosen_prs_bits << 28);
            hal_ll_hw_reg->CRC = cr;
        } break;
#endif
        default: break;
    }

    /* 4) RELOAD = 0, TOP = RGx1 = top; clamp-uj duty ako je ve?i od TOP */
    switch ( map->config.pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->RELDA = 0u;
            hal_ll_hw_reg->RGA1  = top;
            if (hal_ll_hw_reg->RGA0 > top) hal_ll_hw_reg->RGA0 = top / 2u;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RELDB = 0u;
            hal_ll_hw_reg->RGB1  = top;
            if (hal_ll_hw_reg->RGB0 > top) hal_ll_hw_reg->RGB0 = top / 2u;
            break;
#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RELDC = 0u;
            hal_ll_hw_reg->RGC1  = top;
            if (hal_ll_hw_reg->RGC0 > top) hal_ll_hw_reg->RGC0 = top / 2u;
            break;
#endif
        default: break;
    }

    /* 5) Vrati efektivni period (TOP). SDK ga ?uva u max_period. */
    return top;
}


static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    hal_ll_tim_pin_type_t pin_type = map->config.pin_type;

    /* 1) Stop kanala pre (re)konfiguracije */
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A: hal_ll_hw_reg->RUNA = 0x00; break;
        case HAL_LL_TIM_PIN_B: hal_ll_hw_reg->RUNB = 0x00; break;
#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C: hal_ll_hw_reg->RUNC = 0x00; break;
#endif
        default: return 0u;
    }

    /* 2) CRx: PWM sa reload-om na RGx1 (top), up-count, bez WBF (mo?e kasnije WBF_EN) */
    const uint32_t clk   = hal_ll_tim_clock_source(); /* npr. CLK_PRESC_OUT */
    const uint32_t prscl = PRSCL_1_1;                 /* privremeni preskaler; realan bira set_freq */

    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->CRA =
                (RELD_MATCH_B1 << 8)  |   /* reload na match sa A1 (top) */
                (UPDN_UP_COUNT << 16) |
                (WBF_DIS       << 20) |
                (clk           << 24) |
                (prscl         << 28);
            hal_ll_hw_reg->RELDA = 0u;    /* broji 0..RGA1 */
            break;

        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->CRB =
                (RELD_MATCH_B1 << 8)  |
                (UPDN_UP_COUNT << 16) |
                (WBF_DIS       << 20) |
                (clk           << 24) |
                (prscl         << 28);
            hal_ll_hw_reg->RELDB = 0u;
            break;

#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->CRC =
                (RELD_MATCH_B1 << 8)  |
                (UPDN_UP_COUNT << 16) |
                (WBF_DIS       << 20) |
                (clk           << 24) |
                (prscl         << 28);
            hal_ll_hw_reg->RELDC = 0u;
            break;
#endif

        default:
            return 0u;
    }

    /* 3) Izlazni obrazac: Set @ RGx0, Clear @ RGx1; status clear */
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->OUTCRA0 = 0x00u;
            hal_ll_hw_reg->OUTCRA1 = (2u << 0) | (1u << 2);  /* Clear on RGA0, Set on RGA1 */
            hal_ll_hw_reg->STA     = 0xFFu;                  /* clear status */
            break;

        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->OUTCRB0 = 0x00u;
            hal_ll_hw_reg->OUTCRB1 = (2u << 0) | (1u << 2);
            hal_ll_hw_reg->STB     = 0xFFu;
            break;

#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->OUTCRC0 = 0x00u;
            hal_ll_hw_reg->OUTCRC1 = (2u << 0) | (1u << 2);
            hal_ll_hw_reg->STC     = 0xFFu;
            break;
#endif

        default:
            return 0u;
    }

    /* 4) Izra?unaj i upi?i TOP (RGx1) + PRSCL preko helper-a; clamp duty; vrati TOP */
    uint32_t top = hal_ll_tim_set_freq_bare_metal( map );
    if ( top == 0u ) { top = 0xFFFFu; }

    /* 5) Inicijalni duty ~50% (RGx0 = top/2) */
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A: hal_ll_hw_reg->RGA0 = top >> 1; break;
        case HAL_LL_TIM_PIN_B: hal_ll_hw_reg->RGB0 = top >> 1; break;
#ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C: hal_ll_hw_reg->RGC0 = top >> 1; break;
#endif
        default: return 0u;
    }

    /* 6) Ne startujemo RUNx ovde; to radi hal_ll_tim_start() */
    return top;
}


static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map, true );

    _enable_portu_clock(true);

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
