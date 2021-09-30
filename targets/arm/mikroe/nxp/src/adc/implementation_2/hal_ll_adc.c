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
 * @file  hal_ll_adc.c
 * @brief Low level HAL ADC source file.
 */

#include "hal_ll_adc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_adc_pin_map.h"

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

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list */
static hal_ll_adc_handle_register_t hal_ll_module_state[ADC_MODULE_COUNT] = { (handle_t *) NULL, (handle_t *) NULL, false };

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

#define HAL_LL_ADC_6BIT_RESOLUTION_MASK      0UL
#define HAL_LL_ADC_8BIT_RESOLUTION_MASK      1UL
#define HAL_LL_ADC_10BIT_RESOLUTION_MASK     2UL
#define HAL_LL_ADC_12BIT_RESOLUTION_MASK     3UL

#define HAL_LL_HSADC_SAMPLE_10               0x400UL

#define HAL_LL_HSADCEN_BIT                   28
#define HAL_LL_HSADC_STAT_EOSIA_BIT          11
#define HAL_LL_HSADC_CTRL3_DMASRC_BIT        6
#define HAL_LL_HSADC_PWR_PSTSA_BIT           10
#define HAL_LL_HSADC_PWR_PSTSB_BIT           11
#define HAL_LL_HSADC_PWR_PDA_BIT             0
#define HAL_LL_HSADC_PWR_PDB_BIT             1
#define HAL_LL_HSADC_CTRL1_STOPA_BIT         14
#define HAL_LL_HSADC_CTRL2_STOPB_BIT         14

#define HAL_LL_HSADC_CTRL3_ADCRES_SHIFT      8
#define HAL_LL_HSADC_PWR_PUDELAY_SHIFT       4
#define HAL_LL_HSADC_PWR2_DIVB_SHIFT         8
#define HAL_LL_HSADC_SAMPTIM_SAMPT_B_SHIFT   8

#define HAL_LL_HSADC_CTRL1_SMODE_MASK        0x7UL
#define HAL_LL_HSADC_CTRL1_STARTA_MASK       0x2000UL
#define HAL_LL_HSADC_CTRL2_STARTB_MASK       0x2000UL
#define HAL_LL_HSADC_CTRL2_SIMULT_MASK       0x40UL
#define HAL_LL_HSADC_CTRL2_DIVA_MASK         0x3FUL
#define HAL_LL_HSADC_CTRL3_ADCRES_MASK       0x300UL
#define HAL_LL_HSADC_CTRL3_DMASRC_MASK       0x40UL
#define HAL_LL_HSADC_PWR_ASB_MASK            0x8000UL
#define HAL_LL_HSADC_PWR_APD_MASK            0x8UL
#define HAL_LL_HSADC_PWR_PUDELAY_MASK        0x3F0UL
#define HAL_LL_HSADC_PWR2_DIVB_MASK          0x3F00UL
#define HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK    0xFFUL
#define HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK    0xFF00UL
#define HAL_LL_HSADC_CALIB_REQSINGA_MASK     0x1UL
#define HAL_LL_HSADC_CALIB_REQDIFA_MASK      0x2UL
#define HAL_LL_HSADC_CALIB_REQSINGB_MASK     0x10UL
#define HAL_LL_HSADC_CALIB_REQDIFB_MASK      0x20UL

// ADCx_CFG2[MUXSEL] - ADC Mux Select.
#define HAL_LL_ADC_CFG2_ADDRESS (uint32_t *)(0x4003B00C)
#define HAL_LL_ADC_MUX_SELECT 4

typedef struct {
    uint16_t pin_an[ADC_MODULE_COUNT];
} hal_ll_adc_pin_id;

/*!
 * @brief Defines the enumeration for the DMA trigger source.
 */
typedef enum _hsadc_dma_trigger_source {
    HAL_LL_HSADC_DMA_END_OF_SCAN = 0,   /*!< DMA trigger source is end of scan interrupt. */
    HAL_LL_HSADC_DMA_SOURCE_READY       /*!< DMA trigger source is RDY bits. */
} hsadc_dma_trigger_source_t;

/*!
 * @brief Defines the enumeration for dual converter scan mode.
 */
typedef enum _hsadc_dual_converter_scan_mode {
    HAL_LL_HSADC_CONVERTER_ONCE_SEQUENTIAL = 0,
    HAL_LL_HSADC_CONVERTER_ONCE_PARALLEL,
    HAL_LL_HSADC_CONVERTER_LOOP_SEQUENTIAL,
    HAL_LL_HSADC_CONVERTER_LOOP_PARALLEL,
    HAL_LL_HSADC_CONVERTER_TRIGGERED_SEQUENTIAL,
    HAL_LL_HSADC_CONVERTER_TRIGGERED_PARALLEL
} hsadc_dual_converter_scan_mode_t;

/*!
 * @brief Defines the enumeration for the converter's work mode in idle mode.
 */
typedef enum _hsadc_idle_work_mode {
    HAL_LL_HSADC_IDLE_NORMAL = 0,     /*!< Keep normal. */
    HAL_LL_HSADC_IDLE_AUTO_STANDBY,   /*!< Fall into standby mode automatically. */
    HAL_LL_HSADC_IDLE_AUTO_POWER_DOWN /*!< Fall into power down mode automatically. */
} hsadc_idle_work_mode_t;

/*!
 * @brief Converter's calibration mode.
 */
typedef enum _hsadc_calibration_mode {
    HAL_LL_HSADC_CALIBRATION_MODE_SINGLE_ENDED = 1,
    HAL_LL_HSADC_CALIBRATION_MODE_DIFFERENTIAL
} hsadc_calibration_mode;

/*!
 * @brief Defines the structure for configuring the HSADC's common setting.
 */
typedef struct _hsadc_config {
    hsadc_dual_converter_scan_mode_t dual_converter;
    bool sim_mode_enable;
    hal_ll_adc_resolution_t resolution;
    hsadc_dma_trigger_source_t dma_trigger_source;
    hsadc_idle_work_mode_t idle_work_mode;
    uint8_t power_up_delay;
} hsadc_config_t;

/*!
 * @brief Defines the structure for configuring each converter.
 */
typedef struct _hsadc_converter_config {
    uint16_t clock_divisor;
    uint16_t sampling_time;
    uint16_t power_up_calibration_mode;
} hsadc_converter_config_t;

/*!< @brief ADC register structure. */
typedef struct {
    uint16_t ctrl1;
    uint16_t ctrl2;
    uint16_t zxctrl1;
    uint16_t zxctrl2;
    uint16_t clist1;
    uint16_t clist2;
    uint16_t clist3;
    uint16_t clist4;
    uint16_t sdis;
    uint16_t stat;
    uint16_t rdy;
    uint16_t lolimstat;
    uint16_t hilimstat;
    uint16_t zxstat;
    uint16_t rslt[16];
    uint16_t lolim0;
    uint16_t lolim1;
    uint16_t lolim2;
    uint16_t lolim3;
    uint16_t lolim4;
    uint16_t lolim5;
    uint16_t lolim6;
    uint16_t lolim7;
    uint16_t lolim8;
    uint16_t lolim9;
    uint16_t lolim10;
    uint16_t lolim11;
    uint16_t lolim12;
    uint16_t lolim13;
    uint16_t lolim14;
    uint16_t lolim15;
    uint16_t hilim0;
    uint16_t hilim1;
    uint16_t hilim2;
    uint16_t hilim3;
    uint16_t hilim4;
    uint16_t hilim5;
    uint16_t hilim6;
    uint16_t hilim7;
    uint16_t hilim8;
    uint16_t hilim9;
    uint16_t hilim10;
    uint16_t hilim11;
    uint16_t hilim12;
    uint16_t hilim13;
    uint16_t hilim14;
    uint16_t hilim15;
    uint16_t offst0;
    uint16_t offst1;
    uint16_t offst2;
    uint16_t offst3;
    uint16_t offst4;
    uint16_t offst5;
    uint16_t offst6;
    uint16_t offst7;
    uint16_t offst8;
    uint16_t offst9;
    uint16_t offst10;
    uint16_t offst11;
    uint16_t offst12;
    uint16_t offst13;
    uint16_t offst14;
    uint16_t offst15;
    uint16_t pwr;
    uint8_t  __unused1[6];
    uint16_t sctrl;
    uint16_t pwr2;
    uint16_t ctrl3;
    uint16_t scintet;
    uint16_t samptim;
    uint16_t calib;
    uint16_t calval_a;
    uint16_t calval_b;
    uint8_t  __unused2[6];
    uint16_t mux67_sel;
} hal_ll_adc_base_handle_t;

static hal_ll_adc_hw_specifics_map_t hal_ll_adc_hw_specifics_map[ADC_MODULE_COUNT + 1] =
{
    #ifdef ADC_MODULE_0
    {HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF, 0xFF},
    #endif
    #ifdef ADC_MODULE_1
    {HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF, 0xFF}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_adc_handle_register_t *low_level_handle;
static volatile hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

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
  *
  * @param[in]  *base - ADC module base address.
  * @return None
  */
static void hal_ll_adc_set_clock( uint8_t base );

/**
  * @brief  Default ADC module configuration.
  *
  * @param[in]  *config - Config type.
  * @return None
  */
static void hal_ll_adc_config_default( hsadc_config_t *config );

/**
  * @brief  Initialize ADC module.
  *
  * @param[in]  *hal_ll_hw_reg - ADC module base address.
  * @param[in]  *config - Config type.
  * @return None
  */
static void hal_ll_adc_ctrl_pwr_init( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_config_t *config );

/**
  * @brief  Enable converter A and converter B manually.
  *
  * @param[in]  *hal_ll_hw_reg - ADC module base address.
  * @param[in]  enable - Boolean type.
  * @return None
  */
static void hal_ll_adc_converter_power_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable );

/**
  * @brief  Enable ADC converters by clearing STOP bits.
  *
  * @param[in]  *hal_ll_hw_reg - ADC module base address.
  * @param[in]  enable - Boolean type.
  * @return None
  */
static void hal_ll_adc_converter_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable );

/**
  * @brief  Configure converters.
  *
  * @param[in]  *hal_ll_hw_reg - ADC module base address.
  * @param[in]  *config - Config type.
  * @return None
  */
static void hal_ll_adc_converter_config( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_converter_config_t *config );

/**
 * @brief Sets adequate subchannel for selected pin.
 * @param[in] adc_pin ADC pin name.
 */
static void hal_ll_adc_set_subchannel( hal_ll_pin_name_t adc_pin );

/**
  * @brief  Initialize ADC module on the hardware level.
  *
  * @param[in]  *base - ADC module base address.
  * @param[in]  resolution - ADC module resolution.
  * @return None
  */
static void hal_ll_adc_hw_init( hal_ll_adc_base_handle_t *base, uint32_t resolution );

/**
  * @brief  Initialize ADC module.
  *
  * @param[in]  *map - ADC module base address.
  * @return None
  */
static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Set adequate read channel for ADC.
  *
  * @param[in]  hal_ll_pin_name_t pin - ADC module pin name.
  * @param[in]  uint8_t module_id - ADC module id.
  * @return Adequate conversion scan mode for selected pin.
  */
static hsadc_dual_converter_scan_mode_t hal_ll_adc_set_read_channel( hal_ll_pin_name_t pin, uint8_t module_id );

/**
  * @brief  Set adequate values for selected mikroBUS pin.
  *
  * @param[in]  hal_ll_adc_base_handle_t* reg_map - ADC module global map.
  * @param[in]  hal_ll_pin_name_t pin - ADC module pin name.
  * @return None
  */
static void hal_ll_adc_set_mikrobus( hal_ll_adc_base_handle_t *reg_map, hal_ll_pin_name_t pin );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if (( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    switch ( resolution )
    {
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_6BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_8BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_10BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_12BIT_RESOLUTION_MASK;
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
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[ pin_check_result ].pin != pin ) {
        hal_ll_adc_map_pin( pin_check_result, &index );
        handle_map[ pin_check_result ]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ]->hal_ll_adc_handle = ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    uint8_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if ( ( pin_check_result = hal_ll_adc_check_pins( hal_ll_adc_hw_specifics_map_local->pin, &index, (void *)0 ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_6BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_8BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_10BIT_RESOLUTION_MASK;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_12BIT_RESOLUTION_MASK;
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
        case HAL_LL_ADC_VREF_DEFAULT:
            hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_EXTERNAL;
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
    uint16_t read_value = 0;

    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    if( low_level_handle->hal_ll_adc_handle == NULL ) {
        return HAL_LL_MODULE_ERROR;
    }

    base->ctrl1 |= HAL_LL_HSADC_CTRL1_STARTA_MASK;
    base->ctrl2 |= HAL_LL_HSADC_CTRL2_STARTB_MASK;

    while( !check_reg_bit( &( base->stat ), HAL_LL_HSADC_STAT_EOSIA_BIT )){}

    if ( (1UL << hal_ll_adc_hw_specifics_map_local->sample) & base->rdy ) {
        *readDatabuf = base->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 3;
    }

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( hal_ll_adc_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {

        hal_ll_adc_converter_power_enable( *handle, false );

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

// TODO - set for mikroBUS pins.
// Further updates will fix for all pins independent of pin name.
static hsadc_dual_converter_scan_mode_t hal_ll_adc_set_read_channel( hal_ll_pin_name_t pin, uint8_t module_id ) {
    switch ( pin )
    {
        case PB0:
            hal_ll_adc_hw_specifics_map[module_id].sample = 10;
            return HAL_LL_HSADC_CONVERTER_ONCE_PARALLEL;
            break;

        case PB1:
            hal_ll_adc_hw_specifics_map[module_id].sample = 11;
            return HAL_LL_HSADC_CONVERTER_ONCE_PARALLEL;
            break;

        case PB2:
            hal_ll_adc_hw_specifics_map[module_id].sample = 6;
            return HAL_LL_HSADC_CONVERTER_ONCE_SEQUENTIAL;
            break;

        case PB3:
            hal_ll_adc_hw_specifics_map[module_id].sample = 15;
            return HAL_LL_HSADC_CONVERTER_ONCE_PARALLEL;
            break;

        default:
            hal_ll_adc_hw_specifics_map[module_id].sample = 10;
            return HAL_LL_HSADC_CONVERTER_ONCE_SEQUENTIAL;
            break;
    }
}

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );
    uint16_t pin_index = 0;
    uint8_t  index_counter = 0;
    uint8_t  hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == _adc_map[pin_index].pin )
        {
            // Get module number
            hal_ll_module_id = _adc_map[pin_index].module_index;
            // Map pin name
            index->pin_an[hal_ll_module_id] = pin_index;

            hal_ll_adc_set_read_channel( pin, hal_ll_module_id );

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
    hal_ll_adc_hw_specifics_map[module_index].pin = _adc_map[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = _adc_map[ index->pin_an[module_index] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_adc_config_default( hsadc_config_t *config ) {
    config->dual_converter = HAL_LL_HSADC_CONVERTER_TRIGGERED_PARALLEL;
    config->sim_mode_enable = true;
    config->dma_trigger_source = HAL_LL_HSADC_DMA_END_OF_SCAN;
    config->resolution = HAL_LL_ADC_12BIT_RESOLUTION_MASK;
    config->idle_work_mode = HAL_LL_HSADC_IDLE_NORMAL;
    config->power_up_delay = 18;
}

static void hal_ll_adc_ctrl_pwr_init( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_config_t *config ) {
    uint16_t mask;

    // CTRL1
    mask = hal_ll_hw_reg->ctrl1 & ~HAL_LL_HSADC_CTRL1_SMODE_MASK;
    mask |= config->dual_converter & HAL_LL_HSADC_CTRL1_SMODE_MASK;
    hal_ll_hw_reg->ctrl1 = mask;
    //CTRL2
    mask =  hal_ll_hw_reg->ctrl2 & ~HAL_LL_HSADC_CTRL2_SIMULT_MASK;
    if( config->sim_mode_enable ) {
        mask |= HAL_LL_HSADC_CTRL2_SIMULT_MASK;
    }
    hal_ll_hw_reg->ctrl2 = mask;
    // CTRL3
    mask = hal_ll_hw_reg->ctrl3 & ~( HAL_LL_HSADC_CTRL3_ADCRES_MASK | HAL_LL_HSADC_CTRL3_DMASRC_MASK );
    mask |= ((( config->dma_trigger_source << HAL_LL_HSADC_CTRL3_DMASRC_BIT ) & HAL_LL_HSADC_CTRL3_DMASRC_MASK ) |
             (( config->resolution << HAL_LL_HSADC_CTRL3_ADCRES_SHIFT ) & HAL_LL_HSADC_CTRL3_ADCRES_MASK ));
    hal_ll_hw_reg->ctrl3 = mask;
    // PWR
    mask = hal_ll_hw_reg->pwr & ~( HAL_LL_HSADC_PWR_ASB_MASK | HAL_LL_HSADC_PWR_APD_MASK | HAL_LL_HSADC_PWR_PUDELAY_MASK );
    switch ( config->idle_work_mode )
    {
        case HAL_LL_HSADC_IDLE_NORMAL:
            break;
        case HAL_LL_HSADC_IDLE_AUTO_STANDBY:
            mask |= HAL_LL_HSADC_PWR_ASB_MASK;
            break;
        case HAL_LL_HSADC_IDLE_AUTO_POWER_DOWN:
            mask |= HAL_LL_HSADC_PWR_APD_MASK;
            break;

        default:
            break;
    }
    mask |= ( config->power_up_delay << HAL_LL_HSADC_PWR_PUDELAY_SHIFT ) & HAL_LL_HSADC_PWR_PUDELAY_MASK;
    hal_ll_hw_reg->pwr = mask;
}

static void hal_ll_adc_converter_config( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_converter_config_t *config ) {
    uint16_t mask;

    // CTRL2
    mask = hal_ll_hw_reg->ctrl2 & ~HAL_LL_HSADC_CTRL2_DIVA_MASK;
    mask |= ( config->clock_divisor -1 ) & HAL_LL_HSADC_CTRL2_DIVA_MASK;
    hal_ll_hw_reg->ctrl2 = mask;
    // PWR2
    mask = hal_ll_hw_reg->pwr2 & ~HAL_LL_HSADC_PWR2_DIVB_MASK;
    mask |= (( config->clock_divisor -1 ) << HAL_LL_HSADC_PWR2_DIVB_SHIFT ) & HAL_LL_HSADC_PWR2_DIVB_MASK;
    hal_ll_hw_reg->pwr2 = mask;
    // SAMPTIM
    mask = hal_ll_hw_reg->samptim & ~HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK;
    mask |= ( config->sampling_time << HAL_LL_HSADC_SAMPTIM_SAMPT_B_SHIFT ) & HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK;
    hal_ll_hw_reg->samptim = mask;
    mask = hal_ll_hw_reg->samptim & ~HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK;
    mask |= config->sampling_time & HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK;
    hal_ll_hw_reg->samptim = mask;
    // CALIB
    mask = hal_ll_hw_reg->calib & ~( HAL_LL_HSADC_CALIB_REQSINGA_MASK | HAL_LL_HSADC_CALIB_REQDIFA_MASK );
    if( config->power_up_calibration_mode & HAL_LL_HSADC_CALIBRATION_MODE_SINGLE_ENDED )
        mask |= HAL_LL_HSADC_CALIB_REQSINGA_MASK;
    if( config->power_up_calibration_mode & HAL_LL_HSADC_CALIBRATION_MODE_DIFFERENTIAL )
        mask |= HAL_LL_HSADC_CALIB_REQDIFA_MASK;
    hal_ll_hw_reg->calib = mask;
    mask = hal_ll_hw_reg->calib & ~( HAL_LL_HSADC_CALIB_REQSINGB_MASK | HAL_LL_HSADC_CALIB_REQDIFB_MASK );
    if( config->power_up_calibration_mode & HAL_LL_HSADC_CALIBRATION_MODE_SINGLE_ENDED )
        mask |= HAL_LL_HSADC_CALIB_REQSINGB_MASK;
    if( config->power_up_calibration_mode & HAL_LL_HSADC_CALIBRATION_MODE_DIFFERENTIAL )
        mask |= HAL_LL_HSADC_CALIB_REQDIFB_MASK;
    hal_ll_hw_reg->calib = mask;
}

static void hal_ll_adc_converter_power_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable ) {
    if( true == enable ){
        clear_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PDA_BIT );
        clear_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PDB_BIT );
    } else {
        set_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PDA_BIT );
        set_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PDB_BIT );
    }

    while( check_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PSTSA_BIT |
           check_reg_bit( &( hal_ll_hw_reg->pwr ), HAL_LL_HSADC_PWR_PSTSB_BIT )));
}

static void hal_ll_adc_converter_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable ) {
    if( true == enable ) {
        clear_reg_bit( &( hal_ll_hw_reg->ctrl1 ), HAL_LL_HSADC_CTRL1_STOPA_BIT );
        clear_reg_bit( &( hal_ll_hw_reg->ctrl2 ), HAL_LL_HSADC_CTRL2_STOPB_BIT );
    } else {
        set_reg_bit( &( hal_ll_hw_reg->ctrl1 ), HAL_LL_HSADC_CTRL1_STOPA_BIT );
        set_reg_bit( &( hal_ll_hw_reg->ctrl2 ), HAL_LL_HSADC_CTRL2_STOPB_BIT );
    }
}

static void hal_ll_adc_set_clock( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #if defined(ADC_MODULE_0)
        case ( hal_ll_adc_module_num( ADC_MODULE_0 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC5, HAL_LL_HSADCEN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC5, HAL_LL_HSADCEN_BIT );
            }
            break;
        #endif
        #if defined(ADC_MODULE_1)
        case ( hal_ll_adc_module_num( ADC_MODULE_1 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC2, HAL_LL_HSADCEN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC2, HAL_LL_HSADCEN_BIT );
            }
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_adc_set_subchannel( hal_ll_pin_name_t adc_pin ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {
        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            if( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup ) {
                clear_reg_bit( HAL_LL_ADC_CFG2_ADDRESS, HAL_LL_ADC_MUX_SELECT );
                break;
            } else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup ) {
                set_reg_bit( HAL_LL_ADC_CFG2_ADDRESS, HAL_LL_ADC_MUX_SELECT );
            }
        }
    }
}

// TODO - set for mikroBUS pins.
// Further updates will fix for all pins independent of pin name.
static void hal_ll_adc_set_mikrobus( hal_ll_adc_base_handle_t *reg_map, hal_ll_pin_name_t pin ) {
    switch ( pin )
    {
        case PB2:
            reg_map->sdis = 0xF000;
            HSADC0_MUX67_SEL = 0x4;
            break;

        case PB3:
            reg_map->sdis = 0x0000;
            HSADC0_MUX67_SEL = 0x4000;
            break;

        default:
            break;
    }
}

static void hal_ll_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map ){
    hsadc_config_t config;
    hsadc_converter_config_t converter_config;
    hal_ll_adc_base_handle_t *hal_ll_hw_reg = hal_ll_adc_get_base_struct( map->base );

    hal_ll_adc_config_default( &config );
    config.dual_converter = hal_ll_adc_set_read_channel( map->pin, map->module_index );
    hal_ll_adc_ctrl_pwr_init( hal_ll_hw_reg, &config );

    converter_config.clock_divisor = 3UL;
    converter_config.sampling_time = 0UL;
    converter_config.power_up_calibration_mode = 0UL;

    // Changes the ADC mux setting to select between alternate sets of ADC channels.
    hal_ll_adc_set_subchannel( map->pin );

    hal_ll_adc_converter_config( hal_ll_hw_reg, &converter_config );
    hal_ll_adc_converter_power_enable( hal_ll_hw_reg, true );
    hal_ll_adc_set_mikrobus( hal_ll_hw_reg ,map->pin );
    hal_ll_adc_converter_enable( hal_ll_hw_reg, true );
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {

    volatile uint32_t port_name = hal_ll_gpio_port_base(hal_ll_gpio_port_index(map->pin));

    hal_ll_gpio_analog_input( &port_name,
                              hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_set_clock( map, true );

    hal_ll_adc_hw_init( map );
}
// ------------------------------------------------------------------------- END
