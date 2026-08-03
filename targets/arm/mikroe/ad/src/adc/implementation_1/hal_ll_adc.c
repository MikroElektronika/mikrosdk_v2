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

#include "delays.h"
#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"
#include "hal_ll_pclkdis.h"

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

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    volatile uint32_t ctrl0;            /*!< 0x0000 ADC Control 0 Register */
    volatile uint32_t ctrl1;            /*!< 0x0004 ADC Control 1 Register */
    volatile uint32_t clkctrl;          /*!< 0x0008 ADC Clock Control Register */
    volatile uint32_t sampclkctrl;      /*!< 0x000C ADC Sample Clock Control Register */
    volatile uint32_t chsel0;           /*!< 0x0010 ADC Channel Select 0 Register */
    volatile uint32_t chsel1;           /*!< 0x0014 ADC Channel Select 1 Register */
    volatile uint32_t chsel2;           /*!< 0x0018 ADC Channel Select 2 Register */
    volatile uint32_t chsel3;           /*!< 0x001C ADC Channel Select 3 Register */
    volatile uint32_t reserved0[ 4 ];   /*!< 0x0020 - 0x002C Reserved */
    volatile uint32_t restart;          /*!< 0x0030 ADC Conversion Restart Delay */
    volatile uint32_t reserved1[ 2 ];   /*!< 0x0034, 0x0038 Reserved */
    volatile uint32_t datafmt;          /*!< 0x003C ADC Data Format Register */
    volatile uint32_t fifodmactrl;      /*!< 0x0040 ADC FIFO and DMA Control Register */
    volatile uint32_t data;             /*!< 0x0044 ADC FIFO Register */
    volatile uint32_t status;           /*!< 0x0048 ADC Status Register */
    volatile uint32_t chstatus;         /*!< 0x004C ADC Channel Status Register */
    volatile uint32_t inten;            /*!< 0x0050 ADC Interrupt Enable Register */
    volatile uint32_t intfl;            /*!< 0x0054 ADC Interrupt Flags Register */
    volatile uint32_t reserved2[ 2 ];   /*!< 0x0058, 0x005C Reserved */
    volatile uint32_t sfraddroffset;    /*!< 0x0060 ADC SFR Address Offset Register */
    volatile uint32_t sfraddr;          /*!< 0x0064 ADC SFR Address Register */
    volatile uint32_t sfrwrdata;        /*!< 0x0068 ADC SFR Write Data Register */
    volatile uint32_t sfrrddata;        /*!< 0x006C ADC SFR Read Data Register */
    volatile uint32_t sfrstatus;        /*!< 0x0070 ADC SFR Status Register */
} hal_ll_adc_base_handle_t;

// ---------------------------------------------------------- REGISTER BITMASKS

/*!< @brief ADC_CTRL0 field positions. */
#define HAL_LL_ADC_CTRL0_ADC_EN_BIT                (0)
#define HAL_LL_ADC_CTRL0_BIAS_EN_BIT               (1)
#define HAL_LL_ADC_CTRL0_SKIP_CAL_BIT              (2)
#define HAL_LL_ADC_CTRL0_RESETB_BIT                (4)

/*!< @brief ADC_CTRL1 field positions/masks. */
#define HAL_LL_ADC_CTRL1_START_BIT                 (0)
#define HAL_LL_ADC_CTRL1_TRIG_MODE_BIT             (1)
#define HAL_LL_ADC_CTRL1_CNV_MODE_BIT              (2)
#define HAL_LL_ADC_CTRL1_TRIG_SEL_POS              (4)
#define HAL_LL_ADC_CTRL1_AVG_POS                   (8)
#define HAL_LL_ADC_CTRL1_AVG_MASK                  (0x7UL << HAL_LL_ADC_CTRL1_AVG_POS)
#define HAL_LL_ADC_CTRL1_NUM_SLOTS_POS             (16)
#define HAL_LL_ADC_CTRL1_NUM_SLOTS_MASK            (0x1FUL << HAL_LL_ADC_CTRL1_NUM_SLOTS_POS)

/*!< @brief ADC_CLKCTRL field positions/masks. */
#define HAL_LL_ADC_CLKCTRL_CLKSEL_POS               (0)
#define HAL_LL_ADC_CLKCTRL_CLKSEL_MASK              (0x3UL << HAL_LL_ADC_CLKCTRL_CLKSEL_POS)
#define HAL_LL_ADC_CLKCTRL_CLKDIV_POS               (4)
#define HAL_LL_ADC_CLKSEL_SYS_OSC                   (0)

/*!< @brief ADC_SAMPCLKCTRL field positions/masks. */
#define HAL_LL_ADC_SAMPCLKCTRL_TRACK_CNT_POS        (0)
#define HAL_LL_ADC_SAMPCLKCTRL_IDLE_CNT_POS         (16)

/*!< @brief Minimum valid track_cnt so that T_TRACK = 4 + track_cnt >= 8 (Equation 11-3). */
#define HAL_LL_ADC_SAMPCLKCTRL_TRACK_CNT_MIN        (4)
#define HAL_LL_ADC_SAMPCLKCTRL_IDLE_CNT_MIN         (0)

/*!< @brief ADC_CHSELn slot field width -- 5 bits per slot (channel 0-20). */
#define HAL_LL_ADC_CHSEL_SLOT_ID_MASK               (0x1FUL)
/*!< @brief Channel not mapped yet. */
#define HAL_LL_ADC_CHANNEL_NC                       (0xFF)

/*!< @brief ADC_FIFODMACTRL field positions/masks. */
#define HAL_LL_ADC_FIFODMACTRL_FLUSH_BIT            (1)
#define HAL_LL_ADC_FIFODMACTRL_DATA_FORMAT_POS      (2)
#define HAL_LL_ADC_FIFODMACTRL_DATA_FORMAT_MASK     (0x3UL << HAL_LL_ADC_FIFODMACTRL_DATA_FORMAT_POS)
#define HAL_LL_ADC_DATA_FORMAT_DATA_ONLY            (1)

/*!< @brief ADC_DATA / ADC_STATUS / ADC_INTFL field positions. */
#define HAL_LL_ADC_DATA_VALUE_MASK                  (0xFFFUL)

#define HAL_LL_ADC_INTFL_READY_BIT                  (0)
#define HAL_LL_ADC_INTFL_CONV_DONE_BIT              (6)
#define HAL_LL_ADC_INTFL_CLEAR_ALL                  (0xFFFFFFFFUL)

/*!< @brief SFR sub-address map used for reference trim / bias-wakeup loading (Section 11.6). */
#define HAL_LL_ADC_SFR_ADDR_BIAS_CNT                (0x05)
#define HAL_LL_ADC_SFR_ADDR_WAKEUP_CNT              (0x06)
#define HAL_LL_ADC_SFR_ADDR_VX2_TUNE                (0x0B)
#define HAL_LL_ADC_SFR_ADDR_IBOOST_VREFP            (0x0C)
#define HAL_LL_ADC_SFR_ADDR_VREFM                   (0x0D)
#define HAL_LL_ADC_SFR_ADDR_IDRV_VCM                (0x0E)

/*!< @brief Bias/wake-up counter settings (Table 11-4): setting 5 -> 128 cycles (>=500us),
 *          setting 3 -> 8 cycles (>=30us), matching the worked example in Section 11.6.1. */
#define HAL_LL_ADC_BIAS_CNT_SETTING                  (5)
#define HAL_LL_ADC_WAKEUP_CNT_SETTING                (3)

/*!< @brief ADC bias regulator settle time. */
#define HAL_LL_ADC_BIAS_SETTLE_TIME_US               (500)

/*!< @brief FCR specific bit positions and masks. */
#define HAL_LL_FCR_ADCREFTRIM0_VX2_TUNE_POS             0
#define HAL_LL_FCR_ADCREFTRIM0_VX2_TUNE_MASK            (0x3FUL << HAL_LL_FCR_ADCREFTRIM0_VX2_TUNE_POS)
#define HAL_LL_FCR_ADCREFTRIM0_VREFP_POS                0
#define HAL_LL_FCR_ADCREFTRIM0_VREFP_MASK               (0x7FUL << HAL_LL_FCR_ADCREFTRIM0_VREFP_POS)
#define HAL_LL_FCR_ADCREFTRIM0_VREFM_POS                0
#define HAL_LL_FCR_ADCREFTRIM0_VREFM_MASK               (0x7FUL << HAL_LL_FCR_ADCREFTRIM0_VREFM_POS)
#define HAL_LL_FCR_ADCREFTRIM0_VCM_POS                  0
#define HAL_LL_FCR_ADCREFTRIM0_VCM_MASK                 (0x0FUL << HAL_LL_FCR_ADCREFTRIM0_VCM_POS)
#define HAL_LL_FCR_ADCREFTRIM2_VX2_TUNE_POS             0
#define HAL_LL_FCR_ADCREFTRIM2_VX2_TUNE_MASK            (0x7FUL << HAL_LL_FCR_ADCREFTRIM2_VX2_TUNE_POS)
#define HAL_LL_FCR_ADCREFTRIM2_VCM_POS                  0
#define HAL_LL_FCR_ADCREFTRIM2_VCM_MASK                 (0xFFUL << HAL_LL_FCR_ADCREFTRIM2_VCM_POS)
#define HAL_LL_FCR_ADCREFTRIM2_IBOOST_1P25_POS          0
#define HAL_LL_FCR_ADCREFTRIM2_IBOOST_1P25_MASK         (0x01UL << HAL_LL_FCR_ADCREFTRIM2_IBOOST_1P25_POS)
#define HAL_LL_FCR_ADCREFTRIM2_IDRV_1P25_POS            0
#define HAL_LL_FCR_ADCREFTRIM2_IDRV_1P25_MASK           (0x0FUL << HAL_LL_FCR_ADCREFTRIM2_IDRV_1P25_POS)

#define HAL_LL_MCR_ADCCFG0_EXT_REF_BIT                  (0)
#define HAL_LL_MCR_ADCCFG0_REF_SEL_BIT                  (1)

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

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT,
     0, HAL_LL_ADC_RESOLUTION_DEFAULT, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

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
  * @brief  Enable or disable the ADC hardware module.
  *
  * Controls the clock and power state of the specified ADC hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
static void hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Initialize hardware ADC module.
 * @details ADC hardware initialization.
 * @param  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
 * @return None
 */
static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map);

/**
 * @brief  Write a byte to the ADC SFR interface.
 * @details Helper function to write a byte to the ADC SFR interface, used for setting reference trim values.
 * @param[in]  *base - ADC base register structure.
 * @param[in]  sfr_addr - SFR sub-address (see ADC_SFRADDR).
 * @param[in]  data - Byte to write.
 * @return None
 */
static void hal_ll_adc_sfr_write( hal_ll_adc_base_handle_t *base, uint8_t sfr_addr, uint8_t data );

/**
 * @brief  Read a byte from the ADC SFR interface.
 * @details Helper function to read a byte from the ADC SFR interface, used for retrieving reference trim values.
 * @param[in]  *base - ADC base register structure.
 * @param[in]  sfr_addr - SFR sub-address (see ADC_SFRADDR).
 * @return uint8_t Byte read from ADC_SFRRDDATA.
 */
static uint8_t hal_ll_adc_sfr_read( hal_ll_adc_base_handle_t *base, uint8_t sfr_addr );

/**
 * @brief  ADC vref-related settings.
 * @details Sets adequate reference trim values for the selected voltage reference,
 *          for HAL_LL_ADC_VREF_INTERNAL and HAL_LL_ADC_VREF_EXTERNAL options.
 * @param[in]  *base - ADC base register structure.
 * @param[in]  vref_input - Selected voltage reference.
 * @return None
 */
static void hal_ll_adc_load_ref_trim( hal_ll_adc_base_handle_t *base,
                                      hal_ll_adc_voltage_reference_t vref_input );

/**
 * @brief  ADC enter SLEEP state.
 * @details Bring the ADC from ADC_RESET into the ADC_SLEEP state.
 * @param[in]  *base - ADC base register structure.
 * @param[in]  *map - ADC module local map.
 * @return None
 */
static void hal_ll_adc_enter_sleep( hal_ll_adc_base_handle_t *base, hal_ll_adc_hw_specifics_map_t *map );

/**
 * @brief  ADC enter NAP state.
 * @details Bring the ADC from ADC_SLEEP into the ADC_NAP state.
 * @param[in]  *base - ADC base register structure.
 * @return None
 */
static void hal_ll_adc_enter_nap( hal_ll_adc_base_handle_t *base );

/**
 * @brief  ADC enter ON state.
 * @details Bring the ADC from ADC_NAP into the ADC_ON state, using calibration.
 * @param[in]  *base - ADC base register structure.
 * @param[in]  *map - ADC module local map.
 * @return None
 */
static void hal_ll_adc_enter_on( hal_ll_adc_base_handle_t *base, hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Initialize ADC module @p map.
  * @details from @p map, uses pin information to set it as analog & sets
  * @param[in]  *map - ADC module local map, pointer to a
  * member in hal_ll_adc_hw_specifics_map global array.
  * @return None.
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin,
                                        hal_ll_adc_voltage_reference_t vref_input,
                                        hal_ll_adc_resolution_t resolution,
                                        hal_ll_adc_handle_register_t *handle_map,
                                        uint8_t *hal_module_id ) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if (( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_ADC_12BIT_RES_VAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_INTERNAL;
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

    if ( HAL_LL_ADC_CHANNEL_NC == hal_ll_adc_hw_specifics_map_local->channel ) {
        return HAL_LL_ADC_WRONG_CHANNEL;
    }

    // Software trigger, single conversion sequence.
    clear_reg_bit( &base->ctrl1, HAL_LL_ADC_CTRL1_TRIG_MODE_BIT );
    clear_reg_bit( &base->ctrl1, HAL_LL_ADC_CTRL1_CNV_MODE_BIT );

    // Single slot.
    clear_reg_bits( &base->ctrl1, HAL_LL_ADC_CTRL1_NUM_SLOTS_MASK );

    // Assign the mapped channel to slot 0; disable averaging (single sample per channel).
    write_reg( &base->chsel0, ( hal_ll_adc_hw_specifics_map_local->channel & HAL_LL_ADC_CHSEL_SLOT_ID_MASK ) );
    clear_reg_bits( &base->ctrl1, HAL_LL_ADC_CTRL1_AVG_MASK );

    // Data-only format: 12-bit unsigned result, no status bits.
    write_reg( &base->fifodmactrl, ( read_reg( &base->fifodmactrl ) & ~HAL_LL_ADC_FIFODMACTRL_DATA_FORMAT_MASK ) |
                                   ( HAL_LL_ADC_DATA_FORMAT_DATA_ONLY << HAL_LL_ADC_FIFODMACTRL_DATA_FORMAT_POS ) );

    // Flush any stale FIFO contents from a previous sequence.
    set_reg_bit( &base->fifodmactrl, HAL_LL_ADC_FIFODMACTRL_FLUSH_BIT );

    write_reg( &base->intfl, HAL_LL_ADC_INTFL_CLEAR_ALL );

    // Start the conversion sequence.
    set_reg_bit( &base->ctrl1, HAL_LL_ADC_CTRL1_START_BIT );

    // Wait until the conversion is done.
    while ( !check_reg_bit( &base->intfl, HAL_LL_ADC_INTFL_CONV_DONE_BIT ) );

    // Prevent an additional conversion sequence.
    clear_reg_bit( &base->ctrl1, HAL_LL_ADC_CTRL1_START_BIT );

    *readDatabuf = ( uint16_t )( read_reg( &base->data ) & HAL_LL_ADC_DATA_VALUE_MASK );

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

        hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_local, false );

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

static void hal_ll_adc_module_enable( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state ) {
    #ifdef ADC_MODULE_0
    if ( hal_ll_adc_module_num( ADC_MODULE_0 ) == map->module_index )
        clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_23 );
    #endif
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ) {
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t* )hal_ll_adc_get_base_struct( map->base );

    hal_ll_adc_enter_sleep( base, map );
    hal_ll_adc_enter_nap( base );
    hal_ll_adc_enter_on( base, map );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    hal_ll_port_name_t port_name = hal_ll_gpio_port_index( map->pin );
    uint32_t port_base = hal_ll_gpio_port_base( port_name );

    hal_ll_gpio_analog_input( &port_base, hal_ll_gpio_pin_mask( map->pin ), port_name );

    // Enable ADC operation.
    hal_ll_adc_module_enable( map, true );

    hal_ll_adc_hw_init( map );

}

static void hal_ll_adc_sfr_write( hal_ll_adc_base_handle_t *base, uint8_t sfr_addr, uint8_t data ) {
    write_reg( &base->sfraddr, sfr_addr );
    write_reg( &base->sfrwrdata, data );
}

static uint8_t hal_ll_adc_sfr_read( hal_ll_adc_base_handle_t *base, uint8_t sfr_addr ) {
    write_reg( &base->sfraddr, sfr_addr );

    return ( uint8_t )read_reg( &base->sfrrddata );
}

static void hal_ll_adc_load_ref_trim( hal_ll_adc_base_handle_t *base, hal_ll_adc_voltage_reference_t vref_input ) {
    uint8_t sfr_data;

    if ( HAL_LL_ADC_VREF_EXTERNAL == vref_input ) {
        // External reference trim.
        sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_VX2_TUNE ) & 0x80;
        sfr_data |= ( read_reg( _FCR_ADCREFTRIM2_ ) & HAL_LL_FCR_ADCREFTRIM2_VX2_TUNE_MASK ) >>
                    HAL_LL_FCR_ADCREFTRIM2_VX2_TUNE_POS;
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_VX2_TUNE, sfr_data );

        sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_IDRV_VCM );
        sfr_data |= ( read_reg( _FCR_ADCREFTRIM2_ ) & HAL_LL_FCR_ADCREFTRIM2_VCM_MASK ) >>
                    HAL_LL_FCR_ADCREFTRIM2_VCM_POS;
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_IDRV_VCM, sfr_data );
    } else {
        // 1.25V internal reference trim
        sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_VX2_TUNE ) & 0xC0;
        sfr_data |= ( read_reg( _FCR_ADCREFTRIM0_ ) & HAL_LL_FCR_ADCREFTRIM0_VX2_TUNE_MASK ) >>
                    HAL_LL_FCR_ADCREFTRIM0_VX2_TUNE_POS;
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_VX2_TUNE, sfr_data );

        sfr_data = ( ( ( read_reg( _FCR_ADCREFTRIM2_ ) & HAL_LL_FCR_ADCREFTRIM2_IBOOST_1P25_MASK ) >>
                        HAL_LL_FCR_ADCREFTRIM2_IBOOST_1P25_POS ) << 7 ) |
                   ( ( read_reg( _FCR_ADCREFTRIM0_ ) & HAL_LL_FCR_ADCREFTRIM0_VREFP_MASK ) >>
                      HAL_LL_FCR_ADCREFTRIM0_VREFP_POS );
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_IBOOST_VREFP, sfr_data );

        sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_VREFM ) & 0x80;
        sfr_data |= ( read_reg( _FCR_ADCREFTRIM0_ ) & HAL_LL_FCR_ADCREFTRIM0_VREFM_MASK ) >>
                    HAL_LL_FCR_ADCREFTRIM0_VREFM_POS;
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_VREFM, sfr_data );

        sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_IDRV_VCM ) & 0x0C;
        sfr_data |= ( ( ( read_reg( _FCR_ADCREFTRIM2_ ) & HAL_LL_FCR_ADCREFTRIM2_IDRV_1P25_MASK ) >>
                         HAL_LL_FCR_ADCREFTRIM2_IDRV_1P25_POS ) << 4 ) |
                    ( ( read_reg( _FCR_ADCREFTRIM0_ ) & HAL_LL_FCR_ADCREFTRIM0_VCM_MASK ) >>
                      HAL_LL_FCR_ADCREFTRIM0_VCM_POS );
        hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_IDRV_VCM, sfr_data );
    }

    // Bias and wake-up counter settings are common to every reference.
    sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_BIAS_CNT ) & 0xF0;
    sfr_data |= HAL_LL_ADC_BIAS_CNT_SETTING;
    hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_BIAS_CNT, sfr_data );

    sfr_data = hal_ll_adc_sfr_read( base, HAL_LL_ADC_SFR_ADDR_WAKEUP_CNT ) & 0xF0;
    sfr_data |= HAL_LL_ADC_WAKEUP_CNT_SETTING;
    hal_ll_adc_sfr_write( base, HAL_LL_ADC_SFR_ADDR_WAKEUP_CNT, sfr_data );
}

static void hal_ll_adc_enter_sleep( hal_ll_adc_base_handle_t *base, hal_ll_adc_hw_specifics_map_t *map ) {
    // Reset ADC
    clear_reg_bit( &base->ctrl0, HAL_LL_ADC_CTRL0_RESETB_BIT );

    // Clear ADC Clock Control register
    write_reg( &base->clkctrl, ( read_reg( &base->clkctrl ) & ~HAL_LL_ADC_CLKCTRL_CLKSEL_MASK ) |
                               ( HAL_LL_ADC_CLKSEL_SYS_OSC << HAL_LL_ADC_CLKCTRL_CLKSEL_POS ) );

    // Select vref source and vref value (in case of internal reference)
    if ( HAL_LL_ADC_VREF_EXTERNAL == map->vref_input ) {
        set_reg_bit( _MCR_ADCCFG0_, HAL_LL_MCR_ADCCFG0_EXT_REF_BIT );
    } else {
        clear_reg_bit( _MCR_ADCCFG0_, HAL_LL_MCR_ADCCFG0_EXT_REF_BIT );
        clear_reg_bit( _MCR_ADCCFG0_, HAL_LL_MCR_ADCCFG0_REF_SEL_BIT );
    }
    // Leave reset
    set_reg_bit( &base->ctrl0, HAL_LL_ADC_CTRL0_RESETB_BIT );
}

static void hal_ll_adc_enter_nap( hal_ll_adc_base_handle_t *base ) {
    // Bias enable
    set_reg_bit( &base->ctrl0, HAL_LL_ADC_CTRL0_BIAS_EN_BIT );

    // MAX32690 User Guide, Section 11. ADC, 11.5 Operating Modes:
    // "Enabling the bias regulator requires 500μs before performing a conversion."
    Delay_us( 500 );
}

static void hal_ll_adc_enter_on( hal_ll_adc_base_handle_t *base, hal_ll_adc_hw_specifics_map_t *map ) {
    // Skip automatic calibration.
    clear_reg_bit( &base->ctrl0, HAL_LL_ADC_CTRL0_SKIP_CAL_BIT );

    // Sample clock hold time.
    write_reg( &base->sampclkctrl, ( HAL_LL_ADC_SAMPCLKCTRL_TRACK_CNT_MIN << HAL_LL_ADC_SAMPCLKCTRL_TRACK_CNT_POS ) |
                                   ( HAL_LL_ADC_SAMPCLKCTRL_IDLE_CNT_MIN << HAL_LL_ADC_SAMPCLKCTRL_IDLE_CNT_POS ) );

    write_reg( &base->intfl, HAL_LL_ADC_INTFL_CLEAR_ALL );

    hal_ll_adc_load_ref_trim( base, map->vref_input );

    // ADC enable.
    set_reg_bit( &base->ctrl0, HAL_LL_ADC_CTRL0_ADC_EN_BIT );

    // Wait until the ADC is ready for conversions.
    while ( !check_reg_bit( &base->intfl, HAL_LL_ADC_INTFL_READY_BIT ) );
}

// ------------------------------------------------------------------------- END
