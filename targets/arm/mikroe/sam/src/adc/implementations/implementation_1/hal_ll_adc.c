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
#include "hal_ll_adc_pin_map.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_adc_get_module_state_address ((hal_ll_adc_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_adc_get_handle (hal_ll_adc_handle_register_t *)hal_ll_adc_get_module_state_address->hal_ll_adc_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_adc_get_base_struct(_handle) ((hal_ll_adc_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_adc_get_base_from_hal_handle ((hal_ll_adc_hw_specifics_map_t *)((hal_ll_adc_handle_register_t *)\
                                            (((hal_ll_adc_handle_register_t *)(handle))->hal_ll_adc_handle))->hal_ll_adc_handle)->base

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

#define HAL_LL_ADC_CCR_OFFSET               0x304

#define HAL_LL_ADC_ADON_BIT                 0
#define HAL_LL_ADC_SR_EOC_BIT               1
#define HAL_LL_ADC_CONT_BIT                 1
#define HAL_LL_ADC_SCAN_BIT                 8
#define HAL_LL_ADC_ALIGN_BIT                11
#define HAL_LL_ADC_RESOLUTION_BIT0          24
#define HAL_LL_ADC_RESOLUTION_BIT1          25
#define HAL_LL_ADC_SWSTART_BIT              30

#define HAL_LL_ADC1_ENABLE_CLOCK            8
#define HAL_LL_ADC2_ENABLE_CLOCK            9
#define HAL_LL_ADC3_ENABLE_CLOCK            10

#define HAL_LL_ADC_CONT                     0x2ul
#define HAL_LL_ADC_SCAN                     0x100ul
#define HAL_LL_ADC_ALIGN                    0x800ul
#define HAL_LL_ADC_JEXTSEL                  0xE0000ul

#define HAL_LL_ADC_16MHZ                    16000000ul
#define HAL_LL_ADC_60MHZ                    60000000ul
#define HAL_LL_ADC_72MHZ                    72000000ul
#define HAL_LL_ADC_120MHZ                   120000000ul
#define HAL_LL_ADC_144MHZ                   144000000ul
#define HAL_LL_ADC_180MHZ                   180000000ul

#define HAL_LL_ADC_PRESCALER_2              0x00000000ul
#define HAL_LL_ADC_PRESCALER_4              0x00010000ul
#define HAL_LL_ADC_PRESCALER_6              0x00020000ul
#define HAL_LL_ADC_PRESCALER_8              0x00030000ul

#define HAL_LL_ADC_PRESCALER_MASK           0x00F00000ul
#define HAL_LL_ADC_SEQUENCE_LENGTH_MASK     0x00F00000ul
#define HAL_LL_ADC_CONVERSION_ONE           0x0000001Ful

#define HAL_LL_ADC_12BIT_RES                0x00000000ul
#define HAL_LL_ADC_10BIT_RES                0x01000000ul
#define HAL_LL_ADC_8BIT_RES                 0x02000000ul
#define HAL_LL_ADC_6BIT_RES                 0x03000000ul

#define HAL_LL_RESOLUTION_MASK              0xFCFFFFFFul

#define HAL_LL_MODULE_INDEX_ERROR           0xFFFFFFFFul

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

/**
 *  ADC modules
 */
typedef enum
{
    HAL_LL_MODULE_ADC_DEFAULT = 0xFF,
    #if defined(ADC_MODULE)
    HAL_LL_MODULE_ADC_1 = 1,
    #elif defined(ADC_MODULE_1)
    HAL_LL_MODULE_ADC_1 = 1,
    #endif
    #if defined(ADC_MODULE_2)
    HAL_LL_MODULE_ADC_2 = 2,
    #endif
    #if defined(ADC_MODULE_3)
    HAL_LL_MODULE_ADC_3 = 3,
    #endif
    #if defined(ADC_MODULE_4)
    HAL_LL_MODULE_ADC_4 = 4,
    #endif
    HAL_LL_MODULE_ADC_NONE
} hal_ll_adc_module_number_t;

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
    uint32_t sr;            /* Address offset 0x00 */
    uint32_t cr1;           /* Address offset 0x04 */
    uint32_t cr2;           /* Address offset 0x08 */
    uint32_t smpr1;         /* Address offset 0x0C */
    uint32_t smpr2;         /* Address offset 0x10 */
    uint32_t jofr1;         /* Address offset 0x14 */
    uint32_t jofr2;         /* Address offset 0x18 */
    uint32_t jofr3;         /* Address offset 0x1C */
    uint32_t jofr4;         /* Address offset 0x20 */
    uint32_t htr;           /* Address offset 0x24 */
    uint32_t ltr;           /* Address offset 0x28 */
    uint32_t sqr1;          /* Address offset 0x2C */
    uint32_t sqr2;          /* Address offset 0x30 */
    uint32_t sqr3;          /* Address offset 0x34 */
    uint32_t jsqr;          /* Address offset 0x38 */
    uint32_t jdr1;          /* Address offset 0x3C */
    uint32_t jdr2;          /* Address offset 0x40 */
    uint32_t jdr3;          /* Address offset 0x44 */
    uint32_t jdr4;          /* Address offset 0x48 */
    uint32_t dr;            /* Address offset 0x4C */
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
  * @param  *map - ADC module local map.
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
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Enable ADC module gate clock.
  * @param  *base - ADC module base address.
  * @return None
  */
static void _hal_ll_adc_enable_clock( uint8_t base );

/**
  * @brief  Initialize ADC module.
  * @param  *base - ADC module base address.
  * @param  resolution - ADC module resolution.
  * @return None
  */
static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id)
{
    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle )
{
    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution)
{
    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input)
{
    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value)
{

}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf )
{
    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle )
{

}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map )
{
        return HAL_LL_PIN_NC;
}

static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index )
{

}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle )
{

}

static inline void adc1_enable_clock()
{

}

static inline void adc2_enable_clock()
{

}

static inline void adc3_enable_clock()
{

}

static void _hal_ll_adc_enable_clock( uint8_t base )
{

}

static void _hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution )
{

}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map )
{

}
// ------------------------------------------------------------------------- END
