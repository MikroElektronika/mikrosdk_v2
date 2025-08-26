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

#define HAL_LL_TIM_AF_CONFIG 0 // TODO 

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

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    hal_ll_tim_pin_type_t pin_type =  hal_ll_tim_hw_specifics_map_local->config.pin_type;

  
    if ( duty_ratio < 0.0f )  duty_ratio = 0.0f;
    if ( duty_ratio > 100.0f ) duty_ratio = 100.0f;

    uint32_t period = hal_ll_tim_hw_specifics_map_local->max_period;
    if ( period == 0u ) {
        switch ( pin_type ) {
            case HAL_LL_TIM_PIN_A: period = hal_ll_hw_reg->RGA1; break;
            case HAL_LL_TIM_PIN_B: period = hal_ll_hw_reg->RGB1; break;
            
            #ifdef HAL_LL_TIM_PIN_C
            case HAL_LL_TIM_PIN_C: period = hal_ll_hw_reg->RGC1; break;
            #endif
            default: return HAL_LL_TIM_WRONG_PIN;
        }
       
        if ( period == 0u ) period = 0xFFFFu;
    }

   
    uint32_t compare = (uint32_t)((duty_ratio * (float)period) / 100.0f);

    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->RGA0 = compare;
            break;
        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RGB0 = compare;
            break;
        #ifdef HAL_LL_TIM_PIN_C
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RGC0 = compare;
            break;
        #endif
        default:
            return HAL_LL_TIM_WRONG_PIN;
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

static void hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    if (map == NULL) {
        return;
    }
    /* map->module_index: 0..5  ->  T32A0..T32A5 */
    switch (map->module_index) {
        /* T32A0..T32A3 su u FSYSMENA (IPMENA28..31) */
        case 0:  /* T32A0 */
            // TSB_CG_FSYSMENA_IPMENA28 = hal_ll_state ? 1 : 0; // TODO
            break;
        case 1:  /* T32A1 */
            // TSB_CG_FSYSMENA_IPMENA29 = hal_ll_state ? 1 : 0; // TODO
            break;
        case 2:  /* T32A2 */
            // TSB_CG_FSYSMENA_IPMENA30 = hal_ll_state ? 1 : 0; // TODO
            break;
        case 3:  /* T32A3 */
            // TSB_CG_FSYSMENA_IPMENA31 = hal_ll_state ? 1 : 0; // TODO
            break;

        /* T32A4..T32A5 su u FSYSMENB (IPMENB00..01) */
        case 4:  /* T32A4 */
            // TSB_CG_FSYSMENB_IPMENB00 = hal_ll_state ? 1 : 0; // TODO
            break;
        case 5:  /* T32A5 */
            // TSB_CG_FSYSMENB_IPMENB01 = hal_ll_state ? 1 : 0; // TODO
            break;

        default:
    
        break;
    }
}

static uint32_t hal_ll_tim_clock_source() {
    // return CLK_PRESC_OUT; // TODO
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_type = hal_ll_tim_pin_map[ index ].pin_type;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] = VALUE( map->config.pin, map->config.af );
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_TIM_AF_CONFIG;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t period = map->freq_hz;

    /* Fallback ? ako korisnik jo? nije postavio period, koristi pun 16-bit opseg */
    if (period == 0u) {
        period = 0xFFFFu;
    }

    /* Upis perioda u odgovaraju?i kanal (A/B; dodaj C ako ga koristi? u mapi) */
    switch ( map->config.pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->RGA1 = period;                /* period */
            if (hal_ll_hw_reg->RGA0 > period)            /* clamp duty ako je ve?i od perioda */
                hal_ll_hw_reg->RGA0 = period / 2u;
            break;

        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RGB1 = period;                /* period */
            if (hal_ll_hw_reg->RGB0 > period)
                hal_ll_hw_reg->RGB0 = period / 2u;
            break;

        /* Ako u tvojoj pin-mapi koristi? i kanal C, odkomentari?i ovo:
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RGC1 = period;
            if (hal_ll_hw_reg->RGC0 > period)
                hal_ll_hw_reg->RGC0 = period / 2u;
            break;
        */

        default:
            /* Nevalidan pin/channel u mapi ? ne menjamo ni?ta */
            break;
    }

    return period;
}


static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    hal_ll_tim_pin_type_t pin_type =  map->config.pin_type;
    uint32_t period;

    /* 1) Zaustavi odgovaraju?i kanal pre konfiguracije */
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A: hal_ll_hw_reg->RUNA = 0x00; break;
        case HAL_LL_TIM_PIN_B: hal_ll_hw_reg->RUNB = 0x00; break;
        /* Ako koristi? i kanal C u pin-mapi, ostavi ovo:
        case HAL_LL_TIM_PIN_C: hal_ll_hw_reg->RUNC = 0x00; break;
        */
        default: return 0u;
    }

    /* 2) Podesi kontrolni registar za izabrani kanal:
          - RELD: free-running
          - UPDN: up-count
          - WBF:  disabled
          - CLK:  izvor takta (po tvojoj funkciji hal_ll_tim_clock_source())
          - PRSCL: delilnik (po defaultu 1:1; mo?e? kasnije da ga ra?una? prema ?eljenoj frekvenciji) */
    const uint32_t clk   = hal_ll_tim_clock_source();
    // const uint32_t prscl = PRSCL_1_1; //

    // switch ( pin_type ) {
    //     case HAL_LL_TIM_PIN_A:
    //         hal_ll_hw_reg->CRA   = (RELD_FREE_RUNNING << 8) | (UPDN_UP_COUNT << 16) |
    //                                (WBF_DIS << 20) | (clk << 24) | (prscl << 28);
    //         hal_ll_hw_reg->RELDA = 0u;
    //         break;

    //     case HAL_LL_TIM_PIN_B:
    //         hal_ll_hw_reg->CRB   = (RELD_FREE_RUNNING << 8) | (UPDN_UP_COUNT << 16) |
    //                                (WBF_DIS << 20) | (clk << 24) | (prscl << 28);
    //         hal_ll_hw_reg->RELDB = 0u;
    //         break;

        /* Ako koristi? i kanal C:
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->CRC   = (RELD_FREE_RUNNING << 8) | (UPDN_UP_COUNT << 16) |
                                   (WBF_DIS << 20) | (clk << 24) | (prscl << 28);
            hal_ll_hw_reg->RELDC = 0u;
            break;
        */
    //     default:
    //         return 0u;
    // }

    /* 3) Postavi period (u RGx0) ? koristi internu rutinu za setovanje frekvencije/perioda */
    period = hal_ll_tim_set_freq_bare_metal( map );
    if ( period == 0u ) {
        /* fallback da ne ostane nula */
        period = 0xFFFFu;
    }

    /* 4) Inicijalni duty (50%) i PWM polaritet (OUTCRx):
          OUTCRx0 = 0 (nema promene na tim uslovima),
          OUTCRx1 = Set na RGx0, Clear na RGx1 (isto kao u tvom referentnom primeru) */
    switch ( pin_type ) {
        case HAL_LL_TIM_PIN_A:
            hal_ll_hw_reg->RGA0    = period;                 /* period (TOP) */
            hal_ll_hw_reg->RGA1    = period >> 1;            /* duty = 50%  */
            hal_ll_hw_reg->OUTCRA0 = 0x00;                   /* bez promene */
            hal_ll_hw_reg->OUTCRA1 = (2u << 0) | (1u << 2);  /* set na RG0, clear na RG1 */
            hal_ll_hw_reg->STA     = 0xFF;                   /* po?isti statuse */
            break;

        case HAL_LL_TIM_PIN_B:
            hal_ll_hw_reg->RGB0    = period;
            hal_ll_hw_reg->RGB1    = period >> 1;
            hal_ll_hw_reg->OUTCRB0 = 0x00;
            hal_ll_hw_reg->OUTCRB1 = (2u << 0) | (1u << 2);
            hal_ll_hw_reg->STB     = 0xFF;
            break;

        /* Ako koristi? i kanal C:
        case HAL_LL_TIM_PIN_C:
            hal_ll_hw_reg->RGC0    = period;
            hal_ll_hw_reg->RGC1    = period >> 1;
            hal_ll_hw_reg->OUTCRC0 = 0x00;
            hal_ll_hw_reg->OUTCRC1 = (2u << 0) | (1u << 2);
            hal_ll_hw_reg->STC     = 0xFF;
            break;
        */
        default:
            return 0u;
    }

    return period;
}

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map->base, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
