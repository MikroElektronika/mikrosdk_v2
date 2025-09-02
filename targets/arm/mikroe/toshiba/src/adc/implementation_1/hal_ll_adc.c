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
 * @file  hal_ll_adc.c
 * @brief Low level HAL ADC source file.
 */

#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"
#include "hal_ll_cg.h"

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

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num(_module_num)      (_module_num - 1)

#define HAL_LL_CG_ADC0_BIT 2
#define HAL_LL_CG_ADC1_BIT 3
#define HAL_LL_CG_ADC2_BIT 4

#define ADxMOD0_DACON_mask          (0x01U << 0)
#define ADxCR0_ADEN_mask            (0x01U << 7)
#define ADxCR0_SGL_mask             (0x01U << 1)
#define ADxST_SNGF_mask             (0x01U << 2)
#define ADC_RESULT_MASK             (0x0FFFU)

#define ADxCLK_160M_SCLK40M_EXAZ0   (0x00000008U)  // VADCLK=000, EXAZ0=0001, EXAZ1=0000

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    uint32_t cr0;          // 0x0000 - Control Register0
    uint32_t cr1;          // 0x0004 - Control Register1
    uint32_t st;           // 0x0008 - Status Register
    uint32_t clk;          // 0x000C - Conversion Clock Setting Register
    uint32_t mod0;         // 0x0010 - Mode Setting Reg0
    uint32_t mod1;         // 0x0014 - Mode Setting Reg1
    uint32_t mod2;         // 0x0018 - Mode Setting Reg2
    uint32_t reserved0;    // 0x001C - Reserved
    uint32_t cmpen;        // 0x0020 - Monitor Function Enable Register
    uint32_t cmpcr0;       // 0x0024 - Monitor Function Setting Reg0
    uint32_t cmpcr1;       // 0x0028 - Monitor Function Setting Reg1
    uint32_t cmp0;         // 0x002C - Conversion Result Comparison Reg0
    uint32_t cmp1;         // 0x0030 - Conversion Result Comparison Reg1
    uint32_t _unused1[3];  // 0x0034-0x003C - Reserved
    uint32_t psel0;        // 0x0040 - PMD Trigger Program Number Selection Reg0
    uint32_t psel1;        // 0x0044 - PMD Trigger Program Number Selection Reg1
    uint32_t psel2;        // 0x0048 - PMD Trigger Program Number Selection Reg2
    uint32_t psel3;        // 0x004C - PMD Trigger Program Number Selection Reg3
    uint32_t psel4;        // 0x0050 - PMD Trigger Program Number Selection Reg4
    uint32_t psel5;        // 0x0054 - PMD Trigger Program Number Selection Reg5
    uint32_t psel6;        // 0x0058 - PMD Trigger Program Number Selection Reg6
    uint32_t psel7;        // 0x005C - PMD Trigger Program Number Selection Reg7
    uint32_t psel8;        // 0x0060 - PMD Trigger Program Number Selection Reg8
    uint32_t psel9;        // 0x0064 - PMD Trigger Program Number Selection Reg9
    uint32_t psel10;       // 0x0068 - PMD Trigger Program Number Selection Reg10
    uint32_t psel11;       // 0x006C - PMD Trigger Program Number Selection Reg11
    uint32_t pints0;       // 0x0070 - PMD Trigger Interrupt Selection Reg0
    uint32_t pints1;       // 0x0074 - PMD Trigger Interrupt Selection Reg1
    uint32_t pints2;       // 0x0078 - PMD Trigger Interrupt Selection Reg2 
    uint32_t pints3;       // 0x007C - PMD Trigger Interrupt Selection Reg3
    uint32_t pints4;       // 0x0080 - PMD Trigger Interrupt Selection Reg4
    uint32_t pints5;       // 0x0084 - PMD Trigger Interrupt Selection Reg5
    uint32_t pints6;       // 0x0088 - PMD Trigger Interrupt Selection Reg6
    uint32_t pints7;       // 0x008C - PMD Trigger Interrupt Selection Reg7
    uint32_t pregs;        // 0x0090 - PMD Trigger Storage Selection Register
    uint32_t _unused2[2];  // 0x0094-0x0098 - Reserved
    uint32_t exazsel;      // 0x009C - AIN Sampling Time Selection Register
    uint32_t pset0;        // 0x00A0 - PMD Trigger Program Reg0
    uint32_t pset1;        // 0x00A4 - PMD Trigger Program Reg1
    uint32_t pset2;        // 0x00A8 - PMD Trigger Program Reg2
    uint32_t pset3;        // 0x00AC - PMD Trigger Program Reg3
    uint32_t pset4;        // 0x00B0 - PMD Trigger Program Reg4
    uint32_t pset5;        // 0x00B4 - PMD Trigger Program Reg5
    uint32_t pset6;        // 0x00B8 - PMD Trigger Program Reg6
    uint32_t pset7;        // 0x00BC - PMD Trigger Program Reg7
    uint32_t tset0;        // 0x00C0 - General Purpose Start-up Factor Program Reg0
    uint32_t tset1;        // 0x00C4 - General Purpose Start-up Factor Program Reg1
    uint32_t tset2;        // 0x00C8 - General Purpose Start-up Factor Program Reg2
    uint32_t tset3;        // 0x00CC - General Purpose Start-up Factor Program Reg3
    uint32_t tset4;        // 0x00D0 - General Purpose Start-up Factor Program Reg4
    uint32_t tset5;        // 0x00D4 - General Purpose Start-up Factor Program Reg5
    uint32_t tset6;        // 0x00D8 - General Purpose Start-up Factor Program Reg6
    uint32_t tset7;        // 0x00DC - General Purpose Start-up Factor Program Reg7
    uint32_t tset8;        // 0x00E0 - General Purpose Start-up Factor Program Reg8
    uint32_t tset9;        // 0x00E4 - General Purpose Start-up Factor Program Reg9
    uint32_t tset10;       // 0x00E8 - General Purpose Start-up Factor Program Reg10
    uint32_t tset11;       // 0x00EC - General Purpose Start-up Factor Program Reg11
    uint32_t tset12;       // 0x00F0 - General Purpose Start-up Factor Program Reg12
    uint32_t tset13;       // 0x00F4 - General Purpose Start-up Factor Program Reg13
    uint32_t tset14;       // 0x00F8 - General Purpose Start-up Factor Program Reg14
    uint32_t tset15;       // 0x00FC - General Purpose Start-up Factor Program Reg15
    uint32_t tset16;       // 0x0100 - General Purpose Start-up Factor Program Reg16
    uint32_t tset17;       // 0x0104 - General Purpose Start-up Factor Program Reg17
    uint32_t tset18;       // 0x0108 - General Purpose Start-up Factor Program Reg18
    uint32_t tset19;       // 0x010C - General Purpose Start-up Factor Program Reg19
    uint32_t tset20;       // 0x0110 - General Purpose Start-up Factor Program Reg20
    uint32_t tset21;       // 0x0114 - General Purpose Start-up Factor Program Reg21
    uint32_t tset22;       // 0x0118 - General Purpose Start-up Factor Program Reg22
    uint32_t tset23;       // 0x011C - General Purpose Start-up Factor Program Reg23
    uint32_t _unused3[8];  // 0x0120-0x013C - Reserved
    uint32_t reg0;         // 0x0140 - Conversion Result Storage Reg0
    uint32_t reg1;         // 0x0144 - Conversion Result Storage Reg1
    uint32_t reg2;         // 0x0148 - Conversion Result Storage Reg2
    uint32_t reg3;         // 0x014C - Conversion Result Storage Reg3
    uint32_t reg4;         // 0x0150 - Conversion Result Storage Reg4
    uint32_t reg5;         // 0x0154 - Conversion Result Storage Reg5
    uint32_t reg6;         // 0x0158 - Conversion Result Storage Reg6
    uint32_t reg7;         // 0x015C - Conversion Result Storage Reg7
    uint32_t reg8;         // 0x0160 - Conversion Result Storage Reg8
    uint32_t reg9;         // 0x0164 - Conversion Result Storage Reg9
    uint32_t reg10;        // 0x0168 - Conversion Result Storage Reg10
    uint32_t reg11;        // 0x016C - Conversion Result Storage Reg11
    uint32_t reg12;        // 0x0170 - Conversion Result Storage Reg12
    uint32_t reg13;        // 0x0174 - Conversion Result Storage Reg13
    uint32_t reg14;        // 0x0178 - Conversion Result Storage Reg14
    uint32_t reg15;        // 0x017C - Conversion Result Storage Reg15
    uint32_t reg16;        // 0x0180 - Conversion Result Storage Reg16
    uint32_t reg17;        // 0x0184 - Conversion Result Storage Reg17
    uint32_t reg18;        // 0x0188 - Conversion Result Storage Reg18
    uint32_t reg19;        // 0x018C - Conversion Result Storage Reg19
    uint32_t reg20;        // 0x0190 - Conversion Result Storage Reg20
    uint32_t reg21;        // 0x0194 - Conversion Result Storage Reg21
    uint32_t reg22;        // 0x0198 - Conversion Result Storage Reg22
    uint32_t reg23;        // 0x019C - Conversion Result Storage Reg23
} hal_ll_adc_base_handle_t;

/**
 *  Return values.
 */
typedef enum {
    HAL_LL_ADC_SUCCESS = 0,
    HAL_LL_ADC_WRONG_PIN,

    HAL_LL_ADC_UNSUPPORTED_RESOLUTION = 1100,
    HAL_LL_ADC_UNSUPPORTED_VREF,
    HAL_LL_ADC_WRONG_CHANNEL,
    HAL_LL_ADC_ERROR = (-1)
} hal_ll_adc_err_t;

/*!< @brief ADC hw specific module values. */
typedef struct {
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

// ---------------------------------------------------------- PRIVATE VARIABLES
/**
 * @brief Array of maps holding information for configuring hardware.
 */
static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT + 1] = {
    #ifdef ADC_MODULE_0
    {HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_PIN_NC,
     HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef ADC_MODULE_1
    {HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_PIN_NC,
     HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef ADC_MODULE_2
    {HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_PIN_NC,
     HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT,
     0, HAL_LL_ADC_RESOLUTION_DEFAULT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;
static bool hal_ll_adc_hw_specifics_map_initialized = false;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize ADC hardware specifics map.
  *
  * Initializes all ADC module entries in the hardware specifics map
  * with proper base addresses, module indices, and default values.
  *
  * @return None
  */
static void hal_ll_adc_hw_specifics_map_init( void );

/**
 * @brief Get ADC channel mask from channel enumeration
 * @details Fast lookup table-based channel to mask conversion
 * @param[in] channel - ADC channel enumeration value  
 * @return uint8_t - Corresponding mask value (0-31) or 0xFF if not found
 */
static uint8_t hal_ll_adc_get_channel_mask(hal_ll_adc_channel_t channel);

/**
  * @brief  Check if pins are adequate.
  * @Details Checks analog pin the user has passed with pre-defined
  * pins in ADC pin map.
  * @param[in]  pin - ADC pre-defined pin name.
  * @param[in]  *index - ADC map index value.
  * @return hal_ll_pin_name_t Module index based on pin.
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index,
                                                hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 * @details Maps pin name, register address and channel from
 *          analog register list to module in hardware specific map.
 * @param[in]  module_index ADC HW module index -- 0,1,2... Index in hal_ll_adc_hw_specifics_map,
 * destination of copying.
 * @param[in]  index  Pointer with ADC pin map index value. Index in hal_ll_analog_in_register_list
 * source of copying information
 * @return  None
 */
static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index );

/**
  * @brief  Get local hardware specific map.
  * @details Checks handle value and returns address of adequate
  * hal_ll_adc_hw_specifics_map array element.
  * @param[in]  handle - Object specific context handler.
  * @return address of a member in hal_ll_adc_hw_specifics_map, either a correct member
  * or an 'error' terminating member in map.
  */
static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
 * @brief  Initialize hardware ADC module.
 * @details ADC hardware initialization.
 * @param  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
 * @return None
 */
static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map);

/**
  * @brief  Initialize ADC module @p map.
  * @details from @p map, uses pin information to set it as analog & sets
  * @param[in]  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None.
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

/**
 * @brief  Initialize ADC hardware specifics map.
 */
static void hal_ll_adc_hw_specifics_map_init( void ) {
    if (hal_ll_adc_hw_specifics_map_initialized) {
        return; // Already initialized
    }

    // Initialize all entries to default values
    for (int i = 0; i <= ADC_MODULE_COUNT; i++) {
        hal_ll_adc_hw_specifics_map[i].base = 0;
        hal_ll_adc_hw_specifics_map[i].module_index = 0;
        hal_ll_adc_hw_specifics_map[i].pin = HAL_LL_PIN_NC;
        hal_ll_adc_hw_specifics_map[i].vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map[i].vref_value = 0.0f;
        hal_ll_adc_hw_specifics_map[i].resolution = HAL_LL_ADC_RESOLUTION_DEFAULT;
        hal_ll_adc_hw_specifics_map[i].channel = 0xFF;
    }

    #ifdef ADC_MODULE_0
    // Initialize ADC MODULE 0
    hal_ll_adc_hw_specifics_map[0].base = HAL_LL_ADC0_BASE_ADDR;
    hal_ll_adc_hw_specifics_map[0].module_index = hal_ll_adc_module_num(ADC_MODULE_0);
    hal_ll_adc_hw_specifics_map[0].pin = HAL_LL_PIN_NC;
    hal_ll_adc_hw_specifics_map[0].vref_input = HAL_LL_ADC_VREF_DEFAULT;
    hal_ll_adc_hw_specifics_map[0].vref_value = 0.0f;
    hal_ll_adc_hw_specifics_map[0].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
    hal_ll_adc_hw_specifics_map[0].channel = 0xFF;
    #endif

    #ifdef ADC_MODULE_1
    // Initialize ADC MODULE 1
    hal_ll_adc_hw_specifics_map[1].base = HAL_LL_ADC1_BASE_ADDR;
    hal_ll_adc_hw_specifics_map[1].module_index = hal_ll_adc_module_num(ADC_MODULE_1);
    hal_ll_adc_hw_specifics_map[1].pin = HAL_LL_PIN_NC;
    hal_ll_adc_hw_specifics_map[1].vref_input = HAL_LL_ADC_VREF_DEFAULT;
    hal_ll_adc_hw_specifics_map[1].vref_value = 0.0f;
    hal_ll_adc_hw_specifics_map[1].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
    hal_ll_adc_hw_specifics_map[1].channel = 0xFF;
    #endif

    #ifdef ADC_MODULE_2
    // Initialize ADC MODULE 2
    hal_ll_adc_hw_specifics_map[2].base = HAL_LL_ADC2_BASE_ADDR;
    hal_ll_adc_hw_specifics_map[2].module_index = hal_ll_adc_module_num(ADC_MODULE_2);
    hal_ll_adc_hw_specifics_map[2].pin = HAL_LL_PIN_NC;
    hal_ll_adc_hw_specifics_map[2].vref_input = HAL_LL_ADC_VREF_DEFAULT;
    hal_ll_adc_hw_specifics_map[2].vref_value = 0.0f;
    hal_ll_adc_hw_specifics_map[2].resolution = HAL_LL_ADC_RESOLUTION_12_BIT;
    hal_ll_adc_hw_specifics_map[2].channel = 0xFF;
    #endif

    // Set error terminating entry
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].base = HAL_LL_MODULE_ERROR;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].module_index = (uint8_t)HAL_LL_MODULE_ERROR;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].pin = HAL_LL_PIN_NC;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].vref_input = HAL_LL_ADC_VREF_DEFAULT;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].vref_value = 0.0f;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].resolution = HAL_LL_ADC_RESOLUTION_DEFAULT;
    hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT].channel = 0xFF;

    hal_ll_adc_hw_specifics_map_initialized = true;
}

static uint8_t hal_ll_adc_get_channel_mask(hal_ll_adc_channel_t channel) {
    static const uint8_t channel_masks[] = {
        [HAL_LL_ADC_CHANNEL_AINA05] = 0x05,  // 0b00101
        [HAL_LL_ADC_CHANNEL_AINA06] = 0x06,  // 0b00110  
        [HAL_LL_ADC_CHANNEL_AINA07] = 0x07,  // 0b00111
        [HAL_LL_ADC_CHANNEL_AINA08] = 0x08,  // 0b01000
        [HAL_LL_ADC_CHANNEL_AINA09] = 0x09,  // 0b01001
        [HAL_LL_ADC_CHANNEL_AINA13] = 0x0D,  // 0b01101
        [HAL_LL_ADC_CHANNEL_AINA14] = 0x0E,  // 0b01110
        [HAL_LL_ADC_CHANNEL_AINA15] = 0x0F,  // 0b01111
        [HAL_LL_ADC_CHANNEL_AINA16] = 0x10,  // 0b10000
        [HAL_LL_ADC_CHANNEL_AINA17] = 0x11,  // 0b10001
        [HAL_LL_ADC_CHANNEL_AINA18] = 0x12,  // 0b10010
        [HAL_LL_ADC_CHANNEL_AINB00] = 0x00,  // 0b00000
        [HAL_LL_ADC_CHANNEL_AINB01] = 0x01,  // 0b00001
        [HAL_LL_ADC_CHANNEL_AINB02] = 0x02,  // 0b00010
        [HAL_LL_ADC_CHANNEL_AINB03] = 0x03,  // 0b00011
        [HAL_LL_ADC_CHANNEL_AINB04] = 0x04,  // 0b00100
        [HAL_LL_ADC_CHANNEL_AINC00] = 0x00,  // 0b00000
        [HAL_LL_ADC_CHANNEL_AINC01] = 0x01,  // 0b00001
        [HAL_LL_ADC_CHANNEL_AINC02] = 0x02,  // 0b00010
        [HAL_LL_ADC_CHANNEL_AINC03] = 0x03,  // 0b00011
        [HAL_LL_ADC_CHANNEL_AINC04] = 0x04,  // 0b00100
        [HAL_LL_ADC_CHANNEL_AINC05] = 0x05,  // 0b00101
    };
    
    if (channel < (sizeof(channel_masks) / sizeof(channel_masks[0]))) {
        return channel_masks[channel];
    }
    else {
        return 0xFF;
    }
}

hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin,
                                        hal_ll_adc_voltage_reference_t vref_input,
                                        hal_ll_adc_resolution_t resolution,
                                        hal_ll_adc_handle_register_t *handle_map,
                                        uint8_t *hal_module_id ) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    hal_ll_adc_hw_specifics_map_initialized = false;

    // Initialize hardware specifics map if not already initialized
    hal_ll_adc_hw_specifics_map_init();

    if (( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_14BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[ pin_check_result ].pin != pin ) {
        hal_ll_adc_map_pin( pin_check_result, &index );
        handle_map[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle =
            ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ].hal_ll_adc_handle =
            ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle =
                    ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;

    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_12BIT_RES_VAL;
            break;
        case HAL_LL_ADC_RESOLUTION_14_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_ADC_14BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );
    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input ) {
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );
    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle != NULL ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base;

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    if( NULL == readDatabuf ) {
        return HAL_LL_ADC_ERROR;
    }

    // Get the channel number
    uint8_t channel = hal_ll_adc_hw_specifics_map_local->channel;
    channel = hal_ll_adc_get_channel_mask(channel);
    if( channel == 0xFF ) {
        return HAL_LL_ADC_WRONG_CHANNEL;
    }

    // Start single conversion
    base->cr0 = ADxCR0_ADEN_mask | ADxCR0_SGL_mask;

    // Wait for conversion to start
    while (!(base->st & ADxST_SNGF_mask)); 
    
    // Wait for conversion to complete 
    while ((base->st & ADxST_SNGF_mask));

    uint32_t result_reg = 0;
    if (channel == 0x02) { // AINC02
        result_reg = base->reg4;
    } else if (channel == 0x03) { // AINC03
        result_reg = base->reg5;
    } else {
        result_reg = base->reg1;
    }
    
    // Extract 12-bit result
    *readDatabuf = (uint16_t)((result_reg >> 4) & ADC_RESULT_MASK);

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local =
                    hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

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

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin,
                                                hal_ll_adc_pin_id *index,
                                                hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size =
        ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );
    uint16_t pin_index = 0;
    uint8_t  index_counter = 0;
    uint8_t  hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == hal_ll_analog_in_register_list[pin_index].pin )
        {
            // Get module number
            hal_ll_module_id = hal_ll_analog_in_register_list[pin_index].module_index;
            // Map pin name
            index->pin_an[hal_ll_module_id] = pin_index;

            // Check if module is taken
            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_adc_handle ) {
                return hal_ll_module_id;
            } else if ( ADC_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_adc_map_pin( uint8_t module_index, hal_ll_adc_pin_id *index ) {
    // Map new pins
    hal_ll_adc_hw_specifics_map[module_index].pin =
                hal_ll_analog_in_register_list[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel =
                hal_ll_analog_in_register_list[ index->pin_an[module_index] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count =
                    sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));
    static uint8_t hal_ll_module_error =
                    sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t* )hal_ll_adc_get_base_struct( map->base );
    hal_ll_cg_base_handle_t *hal_ll_cg_reg = (hal_ll_cg_base_handle_t *)HAL_LL_CG_BASE_ADDR;
    
    set_reg_bit( &hal_ll_cg_reg->fsysmena, 8 ); // Enable clock for port J

    switch ( map->module_index ) {
            #ifdef ADC_MODULE_0
            case hal_ll_adc_module_num(ADC_MODULE_0):
                set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC0_BIT ); // Enable clock for ADC0 module
                set_reg_bit( &hal_ll_cg_reg->spclken, 16 ); // ADCKEN0
                break;
            #endif
            #ifdef ADC_MODULE_1
            case hal_ll_adc_module_num(ADC_MODULE_1):
                set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC1_BIT ); // Enable clock for ADC1 module
                set_reg_bit( &hal_ll_cg_reg->spclken, 17 ); // ADCKEN1
                break;
            #endif
            #ifdef ADC_MODULE_2
            case hal_ll_adc_module_num(ADC_MODULE_2):
                set_reg_bit( &hal_ll_cg_reg->fsysmenb, HAL_LL_CG_ADC2_BIT ); // Enable clock for ADC2 module
                set_reg_bit( &hal_ll_cg_reg->spclken, 18 ); // ADCKEN2
                break;
            #endif

            default:
                break;
    }

    uint8_t ain_mask = hal_ll_adc_get_channel_mask(map->channel);

    // MOD0: Enable ADC (DACON=1), low-power off (RCUT=0)
    base->mod0  = ADxMOD0_DACON_mask; // DACON = 1
    
    // Wait 3 µs after DACON=1 for stabilization
    for(volatile uint32_t i = 0; i < (3 * 330U); ++i) { __asm__("nop"); }
    
    // Configure CLK with proper values: VADCLK=000 (SCLK=ADCLK/4=40MHz), EXAZ0=0001 (~0.96µs)
    base->clk   = ADxCLK_160M_SCLK40M_EXAZ0;
    base->mod1  = 0x00306122; // AD conversion time 0.96µs at SCLK=40MHz
    base->mod2  = 0x00000000;
    
    // Clear EXAZSEL for channels to use EXAZ0 setting
    base->exazsel &= ~((1u << 2) | (1u << 3));
    
    // TRGS=10b (SW single), ENINT=0, channel in bits 0-4
    uint32_t tset_value = (0b10 << 5) | (ain_mask & 0x1F);
    
    if (ain_mask == 0x02) { // AINC02
        base->tset4 = tset_value;
    } else if (ain_mask == 0x03) { // AINC03  
        base->tset5 = tset_value;
    } else {
        base->tset1 = tset_value;
    }
    
    // Disable DMA requests
    base->cr1   = 0x00000000;
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) ),
                                                     hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_hw_init( map );
}

// ------------------------------------------------------------------------- END
