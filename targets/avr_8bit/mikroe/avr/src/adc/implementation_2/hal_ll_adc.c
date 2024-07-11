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
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base
#define hal_ll_adc_get_base_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_get_handle)->hal_ll_adc_handle))->base
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_adc_get_base_struct(_handle) ((const hal_ll_adc_base_handle_t *)_handle)

/*!< @brief Macros defining channel specific setting values. */
#define HAL_LL_ADC_CH_CTRL_SINGLEENDED    (0x01)
#define HAL_LL_ADC_CH_MUXCTRL_SHIFT       (3)
#define HAL_LL_ADC_CH_CTRL_START          (7)
#define HAL_LL_ADC_CH_INTFLAGS_IF         (0)
#define HAL_LL_ADC_CH_0                   (0)
#define HAL_LL_ADC_CH_1                   (1)
#define HAL_LL_ADC_CH_2                   (2)
#define HAL_LL_ADC_CH_3                   (3)

/*!< @brief Macros defining control register values. */
#define HAL_LL_ADC_CTRLA_ENABLE           (0x01)
#define HAL_LL_ADC_CTRLB_RESOLUTION_12BIT (0x00)
#define HAL_LL_ADC_CTRLB_RESOLUTION_8BIT  (0x04)

/*!< @brief Macros defining voltage reference setting values. */
#define HAL_LL_ADC_REFCTRL_INTVCC         (0x10)
#define HAL_LL_ADC_REFCTRL_AREFA          (0x20)
#define HAL_LL_ADC_REFCTRL_AREFB_D        (0x30)

/*!< @brief Macros defining ADC prescaler values. */
#define HAL_LL_ADC_PRESCALER_4            (0)
#define HAL_LL_ADC_PRESCALER_8            (1)
#define HAL_LL_ADC_PRESCALER_16           (2)
#define HAL_LL_ADC_PRESCALER_32           (3)
#define HAL_LL_ADC_PRESCALER_64           (4)
#define HAL_LL_ADC_PRESCALER_128          (5)
#define HAL_LL_ADC_PRESCALER_256          (6)
#define HAL_LL_ADC_PRESCALER_512          (7)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    uint16_t ctrla;
    uint16_t ctrlb;
    uint16_t refctrl;
    uint16_t evctrl;
    uint16_t prescaler;
} adc_regs_t;

/*!< @brief ADC channel register structure. */
typedef struct {
    uint16_t ch_ctrl;
    uint16_t ch_muxctrl;
    uint16_t ch_intctrl;
    uint16_t ch_intflags;
    uint16_t ch_resl;
    uint16_t ch_resh;
} chn_regs_t;

/*!< @brief ADC and channel specific register structure. */
typedef struct {
    adc_regs_t adc_regs;
//  NOTE: XMEGA A and XMEGA AU have 4 ADC channels.
//  In order to use channels other than CH0, replace [1] with [4].
    chn_regs_t chn_regs[1];
} hal_ll_adc_base_handle_t;

/*!< @brief ADC hw specific structure. */
typedef struct {
    const hal_ll_adc_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_adc_voltage_reference_t vref_input;
    float vref_value;
    uint16_t resolution;
    uint8_t channel;
} hal_ll_adc_hw_specifics_map_t;

/*!< @brief ADC return values. */
typedef enum {
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = (-1)
} hal_ll_adc_err_t;

// ------------------------------------------------------------------ CONSTANTS
/*
 * In order to use ADC channels CH1, CH2 or CH3, `hal_ll_adc_regs` elements must be appended with adequate registers:
 * HAL_LL_ADCx_CHnCTRL_REG_ADDRESS, HAL_LL_ADCx_CHnMUXCTRL_REG_ADDRESS, HAL_LL_ADCx_CHnINTCTRL_REG_ADDRESS, HAL_LL_ADCx_CHnINTFLAGS_REG_ADDRESS,
 * where n = {1, 2, 3} is the number of ADC channel.
 */
/*!< @brief ADC modules register array */
static const hal_ll_adc_base_handle_t hal_ll_adc_regs[ ADC_MODULE_COUNT + 1 ] = {
    #ifdef ADC_MODULE_0
    { HAL_LL_ADC0_CTRLA_REG_ADDRESS, HAL_LL_ADC0_CTRLB_REG_ADDRESS, HAL_LL_ADC0_REFCTRL_REG_ADDRESS, HAL_LL_ADC0_EVCTRL_REG_ADDRESS,
      HAL_LL_ADC0_PRESCALER_REG_ADDRESS, HAL_LL_ADC0_CH0CTRL_REG_ADDRESS, HAL_LL_ADC0_CH0MUXCTRL_REG_ADDRESS, HAL_LL_ADC0_CH0INTCTRL_REG_ADDRESS,
      HAL_LL_ADC0_CH0INTFLAGS_REG_ADDRESS, HAL_LL_ADC0_CH0RESL_REG_ADDRESS, HAL_LL_ADC0_CH0RESH_REG_ADDRESS },
    #endif
    #ifdef ADC_MODULE_1
    { HAL_LL_ADC1_CTRLA_REG_ADDRESS, HAL_LL_ADC1_CTRLB_REG_ADDRESS, HAL_LL_ADC1_REFCTRL_REG_ADDRESS, HAL_LL_ADC1_EVCTRL_REG_ADDRESS,
      HAL_LL_ADC1_PRESCALER_REG_ADDRESS, HAL_LL_ADC1_CH0CTRL_REG_ADDRESS, HAL_LL_ADC1_CH0MUXCTRL_REG_ADDRESS, HAL_LL_ADC1_CH0INTCTRL_REG_ADDRESS,
      HAL_LL_ADC1_CH0INTFLAGS_REG_ADDRESS, HAL_LL_ADC1_CH0RESL_REG_ADDRESS, HAL_LL_ADC1_CH0RESH_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
      HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ ADC_MODULE_COUNT + 1 ] = {
    #ifdef ADC_MODULE_0
    { &hal_ll_adc_regs[ hal_ll_adc_module_num( ADC_MODULE_0 )], hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF },
    #endif
    #ifdef ADC_MODULE_1
    { &hal_ll_adc_regs[ hal_ll_adc_module_num( ADC_MODULE_1 )], hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF },
    #endif

    { &hal_ll_adc_regs[ hal_ll_adc_module_num( ADC_MODULE_COUNT )], HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Initialize ADC module.
  * @param  *map - ADC module local map.
  * @return None
  */
static void hal_ll_adc_init(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Check if pins are adequate.
  *
  * Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  *
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[in] *index Array with ADC pin map index values.
  * @param[in] *handle_map Structure with info about available ADC modules.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins(hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map);

/**
  * @brief  Maps new-found module specific values.
  *
  * Maps pin name, register address and channel.
  *
  * @param[in]  module_index ADC HW module index -- 0,1,2...
  * @param[in]  *index  Pointer with ADC pin map index value
  *
  * @return  None
  */
static void hal_ll_adc_map_pin(uint8_t module_index, uint8_t *index);

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
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle);

/**
  * @brief  Set voltage reference source.
  *
  * Checks external vref pins and
  * sets voltage reference source.
  *
  * @param[in] *map - ADC module local map.
  * @param[in] index - ADC module map index value.
  * @param[in] vref_input - ADC reference voltage source.
  * @return  hal_ll_err_t Module specific error.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_err_t hal_ll_adc_check_vref_input(hal_ll_adc_hw_specifics_map_t *map, uint8_t index, hal_ll_adc_voltage_reference_t vref_input);

/**
  * @brief  Set voltage reference.
  *         NOTE: XMEGA microcontrollers have 2 pins for external voltage reference.
  *               Pin PB0 (PD0 for XMEGA E family) is set as default vref pin.
  *               In case that pin is used as analog input, vref is switched to PA0.
  *               If selected microcontroller doesn't have PA0, function `hal_ll_adc_register_handle`
  *               will return `HAL_LL_ADC_UNSUPPORTED_VREF` error.
  * @param  *map - ADC module local map.
  * @return None
  */
static void hal_ll_adc_set_vref_bare_metal(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Set resolution.
  * @param  *map - ADC module local map.
  * @return None
  */
static void hal_ll_adc_set_resolution_bare_metal(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Initialize ADC module.
  * @param  *map - ADC module local.
  * @return None
  */
static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint8_t pin_check_result;
    uint8_t index;

    if ( HAL_LL_PIN_NC == (pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_8_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin )
    {
        hal_ll_adc_map_pin( pin_check_result, &index );

        handle_map[pin_check_result]->init_ll_state = false;
    }

    if ( HAL_LL_ADC_UNSUPPORTED_VREF == hal_ll_adc_check_vref_input( hal_ll_adc_hw_specifics_map, pin_check_result, vref_input )) {
        return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result]->hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc(handle_t *handle) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_8_BIT;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    low_level_handle->init_ll_state = false;

    if ( HAL_LL_ADC_UNSUPPORTED_VREF == hal_ll_adc_check_vref_input( hal_ll_adc_hw_specifics_map_local, hal_ll_adc_hw_specifics_map_local->module_index, vref_input )) {
        return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    if( HAL_LL_ADC_VREF_INTERNAL == hal_ll_adc_hw_specifics_map_local->vref_input ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = (float) ( vref_value / 1.6 );
    } else {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read(handle_t *handle, uint16_t *readDatabuf) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_handle;
    volatile uint16_t resl, resh, analog_input;

    analog_input = hal_ll_adc_hw_specifics_map_local->channel;

    write_reg( base->chn_regs[HAL_LL_ADC_CH_0].ch_ctrl, HAL_LL_ADC_CH_CTRL_SINGLEENDED ); // Single-ended mode

    write_reg( base->chn_regs[HAL_LL_ADC_CH_0].ch_muxctrl, analog_input << HAL_LL_ADC_CH_MUXCTRL_SHIFT ); // Analog input select

    clear_reg( base->chn_regs[HAL_LL_ADC_CH_0].ch_intctrl ); // Disable interrupt mode

    set_reg_bit( base->chn_regs[HAL_LL_ADC_CH_0].ch_ctrl, HAL_LL_ADC_CH_CTRL_START ); // Start conversion

    while( !( check_reg_bit( base->chn_regs[HAL_LL_ADC_CH_0].ch_intflags, HAL_LL_ADC_CH_INTFLAGS_IF ))); // Wait until IF flag is 1

    set_reg_bit( base->chn_regs[HAL_LL_ADC_CH_0].ch_intflags, HAL_LL_ADC_CH_INTFLAGS_IF ); // Clear IF flag by writing 1

    resl = read_reg( base->chn_regs[HAL_LL_ADC_CH_0].ch_resl );
    resh = read_reg( base->chn_regs[HAL_LL_ADC_CH_0].ch_resh );

    *readDatabuf = resl | ( resh << 8 );

    /*
     * From documentation:
     * "The approximate value corresponding to ground is around 200.
     *  This value corresponds to the digital result of ∆V (0.05 * 4095).
     *  ∆V exists to allow zero-crossing detection."
     *
     * This formula is used to map converted values from range [200-4095] to [0-4095] with 12 bit resolution.
     * (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
     *        x - converted value
     *   in_min - 200
     *   in_max - 4095
     *  out_min - 0
     *  out_max - 4095
     *
     * Uncomment the code below if you want to avoid zero-crossing.
     */
    //BEGIN
    /*
    volatile uint16_t res, out_max;
    float mul, lower_limit;
    if( HAL_LL_ADC_RESOLUTION_12_BIT == hal_ll_adc_hw_specifics_map_local->resolution ) {
        out_max = 4095;
    } else if ( HAL_LL_ADC_RESOLUTION_8_BIT == hal_ll_adc_hw_specifics_map_local->resolution ) {
        out_max = 255;
    }

    res = resl | ( resh << 8 );
    lower_limit = (float)( 0.05 * out_max );
    mul = (float)( out_max / ( out_max - lower_limit ));
    if( res >= lower_limit ) {
        *readDatabuf = (( resl | ( resh << 8 )) - lower_limit ) * mul;
    } else {
        *readDatabuf = 0;
    }
    */
    //END

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close(handle_t *handle) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base->adc_regs.ctrla ||
        HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base->chn_regs[HAL_LL_ADC_CH_0].ch_ctrl ) {

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

static hal_ll_pin_name_t hal_ll_adc_check_pins(hal_ll_pin_name_t pin, uint8_t *index, hal_ll_adc_handle_register_t *handle_map) {
    uint8_t pin_index = 0;
    static const uint16_t adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( _adc_map[pin_index].pin == pin ) {
            *index = pin_index;
            return _adc_map[ pin_index ].module_index;
        }
    }

    return HAL_LL_PIN_NC;
}

static void hal_ll_adc_map_pin(uint8_t module_index, uint8_t *index) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin = _adc_map[*index ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = _adc_map[ *index ].channel;
    hal_ll_adc_hw_specifics_map[module_index].module_index = _adc_map[ *index ].module_index;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while ( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_adc_set_resolution_bare_metal(hal_ll_adc_hw_specifics_map_t *map) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    /*
     * CTRLB_RESOLUTION[2:1]
     * 00 -> 12-bit, right adjusted
     * 01 -> reserved
     * 10 -> 8-bit, right adjusted
     * 11 -> 12-bit, left adjusted
     */
    if( HAL_LL_ADC_RESOLUTION_12_BIT == map->resolution ) {
        write_reg( base->adc_regs.ctrlb, HAL_LL_ADC_CTRLB_RESOLUTION_12BIT );
    } else if( HAL_LL_ADC_RESOLUTION_8_BIT == map->resolution ) {
        write_reg( base->adc_regs.ctrlb, HAL_LL_ADC_CTRLB_RESOLUTION_8BIT );
    }
}

static hal_ll_err_t hal_ll_adc_check_vref_input(hal_ll_adc_hw_specifics_map_t *map, uint8_t index, hal_ll_adc_voltage_reference_t vref_input) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    switch ( vref_input )
    {
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_EXTERNAL:
            #ifdef PB0
            // Check if PB0 is being used as analog input pin.
            if( PB0 == hal_ll_adc_hw_specifics_map[index].pin ) {
                #ifndef PA0
                return HAL_LL_ADC_UNSUPPORTED_VREF;
                #else
                hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
                #endif
            } else {
                hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            }
            #elif defined (PD0)
            // Check if PD0 is being used as analog input pin.
            if( PD0 == hal_ll_adc_hw_specifics_map[index].pin ) {
                #ifndef PA0
                return HAL_LL_ADC_UNSUPPORTED_VREF;
                #else
                hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
                #endif
            } else {
                hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            }
            #else
                return HAL_LL_ADC_UNSUPPORTED_VREF;
            #endif
            break;
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map[index].vref_input = HAL_LL_ADC_VREF_DEFAULT;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }
}

static void hal_ll_adc_set_vref_bare_metal(hal_ll_adc_hw_specifics_map_t *map) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    /*
     * REFCTRL_REFSEL[6:4]:
     * 001 -> Internal Vcc/1.6V
     * 010 -> External reference on PORTA
     * 011 -> External reference on PORTB (PORTD on XMEGA E chips)
     * 100 -> Internal Vcc/2V (not supported on XMEGA A)
     */
    if( HAL_LL_ADC_VREF_INTERNAL == map->vref_input ) {
        write_reg( base->adc_regs.refctrl, HAL_LL_ADC_REFCTRL_INTVCC ); // Vcc/1.6V
    } else if( HAL_LL_ADC_VREF_EXTERNAL == map->vref_input ) {
         #ifdef PB0
        // Check if PB0 is being used as analog input pin.
        if( PB0 != map->pin ) {
            write_reg( base->adc_regs.refctrl, HAL_LL_ADC_REFCTRL_AREFB_D ); // PB0
        } else {
            #ifdef PA0
            write_reg( base->adc_regs.refctrl, HAL_LL_ADC_REFCTRL_AREFA ); // PA0
            #endif
        }
        #elif defined (PD0)
        // Check if PD0 is being used as analog input pin.
        if( PD0 != map->pin ) {
            write_reg( base->adc_regs.refctrl, HAL_LL_ADC_REFCTRL_AREFB_D ); // PD0
        } else {
            #ifdef PA0
            write_reg( base->adc_regs.refctrl, HAL_LL_ADC_REFCTRL_AREFA ); // PA0
            #endif
        }
        #endif
    }
}

static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    write_reg( base->adc_regs.prescaler, HAL_LL_ADC_PRESCALER_8);

    hal_ll_adc_set_resolution_bare_metal( map );

    hal_ll_adc_set_vref_bare_metal( map );
}

static void hal_ll_adc_init(hal_ll_adc_hw_specifics_map_t *map) {
    const hal_ll_adc_base_handle_t *base = hal_ll_adc_get_base_struct(map->base);

    hal_ll_adc_hw_init( map );

    write_reg( base->adc_regs.ctrla, HAL_LL_ADC_CTRLA_ENABLE ); // ADC enable
}

// ------------------------------------------------------------------------- END
