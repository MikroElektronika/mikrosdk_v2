/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"
#include "hal_ll_rcc.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[TIM_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// ------------------------------------------------------------- PRIVATE MACROS
#define HAL_LL_TIM_CHANNEL_COUNT            8

#define HAL_LL_TIM_SOPT1                    0x80000UL
#if defined(MKV5)
#define HAL_LL_TIM0_SIM_SCGC6               0x1000000UL
#define HAL_LL_TIM1_SIM_SCGC6               0x2000000UL
#define HAL_LL_TIM2_SIM_SCGC6               0x4000000UL
#define HAL_LL_TIM3_SIM_SCGC6               0x40UL
#define HAL_LL_TIM_SIM_SCGC6_DEFAULT        0x1UL
#else
#define HAL_LL_TIM0_SIM_SCGC6               0x61000001UL
#define HAL_LL_TIM1_SIM_SCGC6               0x62000001UL
#define HAL_LL_TIM2_SIM_SCGC6               0x64000001UL
#define HAL_LL_TIM3_SIM_SCGC6               0x60000001UL
#define HAL_LL_TIM_SIM_SCGC6_DEFAULT        0x40000001UL
#endif
#define HAL_LL_TIM2_SIM_SCGC3               0x1000000UL
#define HAL_LL_TIM3_SIM_SCGC3               0x2000000UL
#define HAL_LL_TIM_SIM_SCGC3_DEFAULT        0x0UL
#define HAL_LL_TIM_SIM_SCGC5_PORTA          0x200UL
#define HAL_LL_TIM_SIM_SCGC5_PORTB          0x400UL
#define HAL_LL_TIM_SIM_SCGC5_PORTC          0x800UL
#define HAL_LL_TIM_SIM_SCGC5_PORTD          0x1000UL
#define HAL_LL_TIM_SIM_SCGC5_PORTE          0x2000UL

//MODE
#define HAL_LL_TIM_MODE_FTMEN               0U
#define HAL_LL_TIM_MODE_FTMEN_MASK          0x1UL
#define HAL_LL_TIM_MODE_WPDIS               2U
#define HAL_LL_TIM_RESET_MODE_REGISTER      4

//SC
#define HAL_LL_TIM_SC_PS_MASK               0x7UL
#define HAL_LL_TIM_SC_PS_SHIFT              0
#define HAL_LL_TIM_SC_CPWMS                 5
#define HAL_LL_TIM_SC_TOF                   7
#define HAL_LL_TIM_SC_CLKS_MASK             0x18U
#define HAL_LL_TIM_SC_CLKS_SHIFT            3

//SYNCONF
#define HAL_LL_TIM_SYNCONF_SYNCMODE         7
#define HAL_LL_TIM_SYNCONF_CNTINC           2
#define HAL_LL_TIM_SYNCONF_INVC             4
#define HAL_LL_TIM_SYNCONF_SWOC             5
#define HAL_LL_TIM_SYNCONF_SWRSTCNT         8
#define HAL_LL_TIM_SYNCONF_SWWRBUF          9
#define HAL_LL_TIM_SYNCONF_SWINVC           11
#define HAL_LL_TIM_SYNCONF_SWSOC            12
#define HAL_LL_TIM_SYNCONF_SWOM             10

//SYNC
#define HAL_LL_TIM_SYNC_SYNCHOM             3
#define HAL_LL_TIM_SYNC_SWSYNC              7

//COMBINE
#define HAL_LL_TIM_COMBINE_CHAN_CTRL_WIDTH  8UL
#define HAL_LL_TIM_COMBINE_SYNCEN0_MASK     0x20UL
#define HAL_LL_TIM_COMBINE_COMBINE0_MASK    0x1
#define HAL_LL_TIM_COMBINE_DECAPEN0_MASK    0x4

//CONF
#define HAL_LL_TIM_CONF_NUMTOF_MASK         0x1FU
#define HAL_LL_TIM_CONF_NUMTOF_SHIFT        0
#define HAL_LL_CONF_BDMMODE_MASK            0xC0U
#define HAL_LL_CONF_BDMMODE_SHIFT           6

//CnV
#define HAL_LL_TIM_CnV_VAL_MASK             0xFFFFU
#define HAL_LL_TIM_CnV_VAL_SHIFT            0

//CnSC
#define HAL_LL_TIM_CnSC_ELSA_MASK           0x4UL
#define HAL_LL_TIM_CnSC_ELSB_MASK           0x8UL
#define HAL_LL_TIM_CnSC_MSA_MASK            0x10u
#define HAL_LL_TIM_CnSC_MSB_MASK            0x20u

//MOD
#define HAL_LL_TIM_MOD_MOD_MASK             0xFFFFU
#define HAL_LL_TIM_MOD_MOD_SHIFT            0

//CNTIN
#define HAL_LL_TIM_CNTIN_INIT_MASK          0xFFFFU
#define HAL_LL_TIM_CNTIN_INIT_SHIFT         0

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
typedef struct {
    uint32_t sc;                                /**< Status And Control, offset: 0x0 */
    uint32_t cnt;                               /**< Counter, offset: 0x4 */
    uint32_t mod;                               /**< Modulo, offset: 0x8 */
    struct {                                    /** offset: 0xC, array step: 0x8 */
        uint32_t csc;                           /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
        uint32_t cv;                            /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
    } controls[8];
    uint32_t cntin;                             /**< Counter Initial Value, offset: 0x4C */
    uint32_t status;                            /**< Capture And Compare Status, offset: 0x50 */
    uint32_t mode;                              /**< Features Mode Selection, offset: 0x54 */
    uint32_t sync;                              /**< Synchronization, offset: 0x58 */
    uint32_t outinit;                           /**< Initial State For Channels Output, offset: 0x5C */
    uint32_t outmask;                           /**< Output Mask, offset: 0x60 */
    uint32_t combine;                           /**< Function For Linked Channels, offset: 0x64 */
    uint32_t deadtime;                          /**< Deadtime Insertion Control, offset: 0x68 */
    uint32_t exttrig;                           /**< FTM External Trigger, offset: 0x6C */
    uint32_t pol;                               /**< Channels Polarity, offset: 0x70 */
    uint32_t fms;                               /**< Fault Mode Status, offset: 0x74 */
    uint32_t filter;                            /**< Input Capture Filter Control, offset: 0x78 */
    uint32_t fltctrl;                           /**< Fault Control, offset: 0x7C */
    uint32_t qdctrl;                            /**< Quadrature Decoder Control And Status, offset: 0x80 */
    uint32_t conf;                              /**< Configuration, offset: 0x84 */
    uint32_t fltpol;                            /**< FTM Fault Input Polarity, offset: 0x88 */
    uint32_t synconf;                           /**< Synchronization Configuration, offset: 0x8C */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure*/
typedef struct
{
    hal_ll_pin_name_t       pin;
    hal_ll_channel_t        channel;
    uint8_t                 af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t  base;
    hal_ll_tim_t        config;
    uint32_t            freq_hz;
    hal_ll_pin_name_t   module_index;
    uint8_t             channel_pair_index;
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
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[TIM_MODULE_COUNT + 1 ] =
{
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, TIM_MODULE_0, HAL_LL_PIN_NC},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, TIM_MODULE_1, HAL_LL_PIN_NC},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, TIM_MODULE_2, HAL_LL_PIN_NC},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, TIM_MODULE_3, HAL_LL_PIN_NC},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC},0, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};


/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param[in]  pin - TIM pre-defined pin name.
  * @param[out] handle - Global handle object.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map  );

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
  * @brief  Set cv register.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static inline void _hal_ll_tim_set_chn_count_val(hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t channel, uint16_t val);

/**
  * @brief  Enable TIM module gate clock.
  * @param  map - Object specific context handler.
  * @return None
  */
static void _hal_ll_tim_enable_pwm_mode(hal_ll_tim_hw_specifics_map_t *map);

/**
  * @brief  Set mod register.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static inline void _hal_ll_tim_set_mode(hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t val);

/**
  * @brief  Based on selected TIM,
  *         return clock speed.
  * @param  base - TIM module base
  *                address
  * @return uint32_t clock source.
  */
static uint32_t _hal_ll_tim_get_clock_speed(hal_ll_tim_base_handle_t *hal_ll_hw_reg);

/**
  * @brief  Enable TIM module gate clock.
  * @param  pin_name - TIM pre-defined pin name.
  * @return None
  */
static void _hal_ll_tim_gate_control( hal_ll_pin_name_t pin_name );

/**
  * @brief  Enable clock for TIM module on hardware level.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state );

/**
  * @brief  Restart registers.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void _hal_ll_tim_restart_register(hal_ll_tim_hw_specifics_map_t *map);

/**
  * @brief  Set synconf, sync and combine register.
  * @param  base - TIM module base
  *                address
  * @return None
  */
static void _hal_ll_tim_hw_init_set_sync_mode(hal_ll_tim_base_handle_t *hal_ll_hw_reg);

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

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t index;
    uint16_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( pin != hal_ll_tim_hw_specifics_map[ pin_check_result ].config.pin ){
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

    uint8_t index;
    uint16_t pin_check_result;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( HAL_LL_PIN_NC == ( pin_check_result = _hal_ll_tim_check_pin( hal_ll_tim_hw_specifics_map_local->config.pin, &index, (void *)0 ) ) ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    return HAL_LL_TIM_SUCCESS;

}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if( NULL == low_level_handle->hal_ll_tim_handle ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    clear_reg_bit(&hal_ll_hw_reg->sc, HAL_LL_TIM_SC_TOF);

    _hal_ll_tim_enable_pwm_mode(hal_ll_tim_hw_specifics_map_local);

    return HAL_LL_TIM_SUCCESS;

}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {

    uint32_t tmp_channel = 0;
    uint32_t tmp_freq;
    uint32_t max_period;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = false;

    tmp_channel = hal_ll_tim_hw_specifics_map_local->config.channel;

    _hal_ll_tim_set_clock(hal_ll_tim_hw_specifics_map_local->base,true);
    hal_ll_tim_stop(handle);

    max_period = _hal_ll_tim_get_clock_speed(hal_ll_tim_hw_specifics_map_local->base) / (freq_hz * 4) - 1;

    if ( max_period > UINT16_MAX ) {
        tmp_freq = _hal_ll_tim_get_clock_speed( hal_ll_tim_hw_specifics_map_local->base ) / (UINT16_MAX + 1) / 4;
    } else {
        tmp_freq = freq_hz;
    }
    hal_ll_tim_hw_specifics_map_local->freq_hz = tmp_freq;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
    low_level_handle->init_ll_state = true;

    return tmp_freq;

}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {

    uint32_t max_duty = 0;
    uint32_t max_period;
    uint8_t channel;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if( NULL == low_level_handle->hal_ll_tim_handle ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    if ( false == low_level_handle->init_ll_state ) {
        hal_ll_tim_start( handle );
        low_level_handle->init_ll_state = true;
    }

    max_period = _hal_ll_tim_get_clock_speed(hal_ll_tim_hw_specifics_map_local->base) / (hal_ll_tim_hw_specifics_map_local->freq_hz * 4)-1;

    max_duty = ( float )max_period * (1 - duty_ratio);

    hal_ll_hw_reg->cntin &= ~HAL_LL_TIM_CNTIN_INIT_MASK;
    hal_ll_hw_reg->cntin |= (0 << HAL_LL_TIM_CNTIN_INIT_SHIFT) & HAL_LL_TIM_CNTIN_INIT_MASK;

    channel = hal_ll_tim_hw_specifics_map_local->config.channel;

    _hal_ll_tim_set_mode(hal_ll_hw_reg, max_period);
    _hal_ll_tim_set_chn_count_val(hal_ll_hw_reg, channel, max_duty);

    hal_ll_hw_reg->sc &= ~HAL_LL_TIM_SC_CLKS_MASK;
    hal_ll_hw_reg->sc |= ( 1 << HAL_LL_TIM_SC_CLKS_SHIFT) & HAL_LL_TIM_SC_CLKS_MASK;

    set_reg_bit(&hal_ll_hw_reg->sync, HAL_LL_TIM_SYNC_SWSYNC);

    hal_ll_hw_reg->mode &= ~HAL_LL_TIM_MODE_FTMEN_MASK;

    return HAL_LL_TIM_SUCCESS;

}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    uint8_t channel;
    uint8_t chnl_pair_num;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if( NULL == low_level_handle->hal_ll_tim_handle ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    channel = hal_ll_tim_hw_specifics_map_local->config.channel;
    chnl_pair_num = hal_ll_tim_hw_specifics_map_local->channel_pair_index;

    _hal_ll_tim_set_chn_count_val(hal_ll_hw_reg, channel, 0);

    hal_ll_hw_reg->controls[channel].csc &= ~HAL_LL_TIM_CnSC_ELSA_MASK;
    hal_ll_hw_reg->controls[channel].csc &= ~HAL_LL_TIM_CnSC_ELSB_MASK;

    hal_ll_hw_reg->controls[channel].csc &= ~HAL_LL_TIM_CnSC_MSA_MASK;
    hal_ll_hw_reg->controls[channel].csc &= ~HAL_LL_TIM_CnSC_MSB_MASK;

    clear_reg_bit(&hal_ll_hw_reg->sc, HAL_LL_TIM_SC_CPWMS);

    hal_ll_hw_reg->combine  &= ~(HAL_LL_TIM_COMBINE_COMBINE0_MASK << (chnl_pair_num * HAL_LL_TIM_COMBINE_CHAN_CTRL_WIDTH));

    return HAL_LL_TIM_SUCCESS;

}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_tim_handle ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;

        _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.channel = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {

    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    static const uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( pin == _tim_map[ pin_num ].pin ) {
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

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    module_struct module;

    if ( HAL_LL_PIN_NC != map->config.pin ) {
        module.pins[0] = VALUE( map->config.pin, map->config.af );
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_MODE_ALT_FUNCTION;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t pin_index ) {
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = _tim_map[ pin_index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.channel = _tim_map[ pin_index ].channel;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = _tim_map[ pin_index ].af;
    hal_ll_tim_hw_specifics_map[ module_index ].channel_pair_index = _tim_map[ pin_index ].channel_pair_index;
}

static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map[ hal_ll_module_count ].base) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static inline void _hal_ll_tim_set_chn_count_val(hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t channel, uint16_t val) {
    hal_ll_hw_reg->controls[channel].cv = (hal_ll_hw_reg->controls[channel].cv & ~HAL_LL_TIM_CnV_VAL_MASK) |
                                          (val << HAL_LL_TIM_CnV_VAL_SHIFT) & HAL_LL_TIM_CnV_VAL_MASK;
}

static void _hal_ll_tim_enable_pwm_mode(hal_ll_tim_hw_specifics_map_t *map) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint8_t chnl_pair_num = map->channel_pair_index;

    hal_ll_hw_reg->combine &= ~(HAL_LL_TIM_COMBINE_DECAPEN0_MASK << (chnl_pair_num * HAL_LL_TIM_COMBINE_CHAN_CTRL_WIDTH));

    hal_ll_hw_reg->controls[ map->config.channel].csc |= HAL_LL_TIM_CnSC_ELSA_MASK;
    hal_ll_hw_reg->controls[ map->config.channel].csc &= ~HAL_LL_TIM_CnSC_ELSB_MASK;

    hal_ll_hw_reg->combine  &= ~(HAL_LL_TIM_COMBINE_COMBINE0_MASK << (chnl_pair_num * HAL_LL_TIM_COMBINE_CHAN_CTRL_WIDTH));
    set_reg_bit(&hal_ll_hw_reg->sc, HAL_LL_TIM_SC_CPWMS);
}

static inline void _hal_ll_tim_set_mode(hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t val) {
    hal_ll_hw_reg->mod &= ~HAL_LL_TIM_MOD_MOD_MASK;
    hal_ll_hw_reg->mod |= (val << HAL_LL_TIM_MOD_MOD_SHIFT) & HAL_LL_TIM_MOD_MOD_MASK;
}

static uint32_t _hal_ll_tim_get_clock_speed(hal_ll_tim_base_handle_t *hal_ll_hw_reg){
    SIM_ClocksTypeDef sim_clocks;
    uint8_t clk_psc = (1 << (hal_ll_hw_reg->sc & HAL_LL_TIM_SC_PS_MASK));

    SIM_GetClocksFrequency(&sim_clocks);

    #ifdef HAL_LL_RCC_CLOCK_OUTPUT
    return sim_clocks.fast_peripheral_frequency;
    #else
    return (sim_clocks.busclock_frequency / clk_psc);
    #endif
}

static void _hal_ll_tim_gate_control( hal_ll_pin_name_t pin_name ) {
    uint8_t port = ( uint8_t )pin_name / PORT_SIZE;

    switch ( port ) {
        #ifdef __PORT_A_CN
        case(PORT_A):
            *_SIM_SCGC5 |= HAL_LL_TIM_SIM_SCGC5_PORTA;
            break;
        #endif
        #ifdef __PORT_B_CN
        case(PORT_B):
            *_SIM_SCGC5 |= HAL_LL_TIM_SIM_SCGC5_PORTB;
            break;
        #endif
        #ifdef __PORT_C_CN
        case(PORT_C):
            *_SIM_SCGC5 |= HAL_LL_TIM_SIM_SCGC5_PORTC;
            break;
        #endif
        #ifdef __PORT_D_CN
        case(PORT_D):
            *_SIM_SCGC5 |= HAL_LL_TIM_SIM_SCGC5_PORTD;
            break;
        #endif
        #ifdef __PORT_E_CN
        case(PORT_E):
            *_SIM_SCGC5 |= HAL_LL_TIM_SIM_SCGC5_PORTE;
            break;
        #endif
    }
}

static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state ) {
    #if defined(__mk__)
    *_SIM_SOPT1 = HAL_LL_TIM_SOPT1;
    #endif
    switch ( ( uint32_t )base ) {
    #ifdef TIM_MODULE_0
        case ( HAL_LL_TIM0_BASE_ADDR ):
            if(hal_ll_state){
                *_SIM_SCGC6 |= HAL_LL_TIM0_SIM_SCGC6;
            }else{
                *_SIM_SCGC6 = HAL_LL_TIM_SIM_SCGC6_DEFAULT;
            }
            break;
    #endif
    #ifdef TIM_MODULE_1
        case ( HAL_LL_TIM1_BASE_ADDR ):
            if(hal_ll_state){
                *_SIM_SCGC6 |= HAL_LL_TIM1_SIM_SCGC6;
            }else{
                *_SIM_SCGC6 = HAL_LL_TIM_SIM_SCGC6_DEFAULT;
            }
            break;
    #endif
    #ifdef TIM_MODULE_2
        case ( HAL_LL_TIM2_BASE_ADDR ):
            if(hal_ll_state){
                #if defined(MK64) || defined(__mkv__)
                *_SIM_SCGC6 |= HAL_LL_TIM2_SIM_SCGC6;
                #endif
                #if defined(__mk__)
                *_SIM_SCGC3 |= HAL_LL_TIM2_SIM_SCGC3;
                #endif
            }else{
                #if defined(MK64) || defined(__mkv__)
                *_SIM_SCGC6 = HAL_LL_TIM_SIM_SCGC6_DEFAULT;
                #endif
                #if defined(__mk__)
                *_SIM_SCGC3 = HAL_LL_TIM_SIM_SCGC3_DEFAULT;
                #endif
            }
            break;
    #endif
    #ifdef TIM_MODULE_3
        case ( HAL_LL_TIM3_BASE_ADDR ):
            if(hal_ll_state){
                *_SIM_SCGC6 |= HAL_LL_TIM3_SIM_SCGC6;
                #if defined(__mk__)
                *_SIM_SCGC3 |= HAL_LL_TIM3_SIM_SCGC3;
                #endif
            }else{
                *_SIM_SCGC6 = HAL_LL_TIM_SIM_SCGC6_DEFAULT;
                #if defined(__mk__)
                *_SIM_SCGC3 = HAL_LL_TIM_SIM_SCGC3_DEFAULT;
                #endif
            }
            break;
    #endif
    }
}

static void _hal_ll_tim_restart_register(hal_ll_tim_hw_specifics_map_t *map){
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = (hal_ll_tim_base_handle_t *) map->base;

    hal_ll_hw_reg->sc = 0;
    hal_ll_hw_reg->controls[map->config.channel].csc = 0;
    hal_ll_hw_reg->controls[map->config.channel].cv = 0;
    hal_ll_hw_reg->mod = 0;
    hal_ll_hw_reg->cntin = 0;
    hal_ll_hw_reg->mode = HAL_LL_TIM_RESET_MODE_REGISTER;
    hal_ll_hw_reg->sync = 0;
    hal_ll_hw_reg->combine = 0;
    hal_ll_hw_reg->conf = 0;
    hal_ll_hw_reg->synconf = 0;
}

static void _hal_ll_tim_hw_init_set_sync_mode(hal_ll_tim_base_handle_t *hal_ll_hw_reg) {
    uint32_t channel = 0;

    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SYNCMODE);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_CNTINC);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_INVC);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWOC);
    set_reg_bit(&hal_ll_hw_reg->sync, HAL_LL_TIM_SYNC_SYNCHOM);

    for (channel = 0; channel < (HAL_LL_TIM_CHANNEL_COUNT / 2); channel++){
        hal_ll_hw_reg->combine |= HAL_LL_TIM_COMBINE_SYNCEN0_MASK << (channel * HAL_LL_TIM_COMBINE_CHAN_CTRL_WIDTH);
    }

    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWRSTCNT);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWWRBUF);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWINVC);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWSOC);
    set_reg_bit(&hal_ll_hw_reg->synconf, HAL_LL_TIM_SYNCONF_SWOM);
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    set_reg_bit(&hal_ll_hw_reg->mode, HAL_LL_TIM_MODE_FTMEN );

    hal_ll_hw_reg->sc &= ~HAL_LL_TIM_SC_PS_MASK;
    hal_ll_hw_reg->sc |= (0 << HAL_LL_TIM_SC_PS_SHIFT) & HAL_LL_TIM_SC_PS_MASK;

    _hal_ll_tim_hw_init_set_sync_mode(hal_ll_hw_reg);

    hal_ll_hw_reg->conf &= ~HAL_LL_TIM_CONF_NUMTOF_MASK;
    hal_ll_hw_reg->conf |= (0<<HAL_LL_TIM_CONF_NUMTOF_SHIFT) & HAL_LL_TIM_CONF_NUMTOF_MASK;

    set_reg_bit(&hal_ll_hw_reg->mode, HAL_LL_TIM_MODE_WPDIS);

    hal_ll_hw_reg->conf &= ~HAL_LL_CONF_BDMMODE_MASK;
    hal_ll_hw_reg->conf |= (0<<HAL_LL_CONF_BDMMODE_SHIFT) & HAL_LL_CONF_BDMMODE_MASK;

    hal_ll_hw_reg->sc &= ~HAL_LL_TIM_SC_PS_MASK;
    hal_ll_hw_reg->sc |= (1 << HAL_LL_TIM_SC_PS_SHIFT) & HAL_LL_TIM_SC_PS_MASK;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    _hal_ll_tim_gate_control( map->config.pin );

    _hal_ll_tim_set_clock( map->base, true );

    _hal_ll_tim_alternate_functions_set_state( map, true );

    _hal_ll_tim_restart_register( map );

    _hal_ll_tim_hw_init( map );
}

// ------------------------------------------------------------------------- END
