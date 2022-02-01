/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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

/*!< @brief Helper macro for getting ADC module clock enable bits. */
// ADC macros
#define HAL_LL_ADCEN_BIT                     (27)
#define HAL_LL_ADC_MODULE                    (0)

#define HAL_LL_ADC_LOW_POWER_ENABLE          (7)

#define HAL_LL_ADC_CLOCK_DIV_1               (0x000UL)
#define HAL_LL_ADC_CLOCK_DIV_2               (0x020UL)
#define HAL_LL_ADC_CLOCK_DIV_4               (0x040UL)
#define HAL_LL_ADC_CLOCK_DIV_8               (0x060UL)

#define HAL_LL_ADC_LONG_SAMPLE_TIME_ENABLE   (0x010UL)

#define HAL_LL_ADC_6BIT_RESOLUTION           (0x000UL)
#define HAL_LL_ADC_8BIT_RESOLUTION           (0x000UL)
#define HAL_LL_ADC_10BIT_RESOLUTION          (0x008UL)
#define HAL_LL_ADC_12BIT_RESOLUTION          (0x004UL)
#define HAL_LL_ADC_16BIT_RESOLUTION          (0x00CUL)

#define HAL_LL_ADC_CLOCK_SOURCE_ASYNC        (0x003UL)

#define HAL_LL_ADC_ASYNC_CLOCK_ENABLE        (0x008UL)

#define HAL_LL_ADC_MUX_SELECT                (4)

#define HAL_LL_ADC_CFG1_CLEAR_MASK           (0x0FFUL)
#define HAL_LL_ADC_CFG2_CLEAR_MASK           (0x01FUL)

#define HAL_LL_ADC_DISABLE_CONVERSION        (0x01FUL)
#define HAL_LL_ADC_COCO_FLAG                 (0x80UL)

#define HAL_LL_ADC_MASK_CHANNEL              (0x1F)

// HSADC macros
#define HAL_LL_HSADC_MODULE                  (1)

#define HAL_LL_HSADC_6BIT_RESOLUTION         (0UL)
#define HAL_LL_HSADC_8BIT_RESOLUTION         (1UL)
#define HAL_LL_HSADC_10BIT_RESOLUTION        (2UL)
#define HAL_LL_HSADC_12BIT_RESOLUTION        (3UL)

#define HAL_LL_ADC_6BIT_RESOLUTION_MASK      (0x000UL)
#define HAL_LL_ADC_8BIT_RESOLUTION_MASK      (0x100UL)
#define HAL_LL_ADC_10BIT_RESOLUTION_MASK     (0x200UL)
#define HAL_LL_ADC_12BIT_RESOLUTION_MASK     (0x300UL)

#define HAL_LL_HSADCEN_BIT                   (28)
#define HAL_LL_HSADC_STAT_EOSIA_BIT          (11)
#define HAL_LL_HSADC_CTRL3_DMASRC_BIT        (6)
#define HAL_LL_HSADC_PWR_PSTSA_BIT           (10)
#define HAL_LL_HSADC_PWR_PSTSB_BIT           (11)
#define HAL_LL_HSADC_PWR_PDA_BIT             (0)
#define HAL_LL_HSADC_PWR_PDB_BIT             (1)
#define HAL_LL_HSADC_CTRL1_STOPA_BIT         (14)
#define HAL_LL_HSADC_CTRL2_STOPB_BIT         (14)

#define HAL_LL_HSADC_CTRL3_ADCRES_SHIFT      (8)
#define HAL_LL_HSADC_PWR_PUDELAY_SHIFT       (4)
#define HAL_LL_HSADC_PWR2_DIVB_SHIFT         (8)
#define HAL_LL_HSADC_SAMPTIM_SAMPT_B_SHIFT   (8)

#define HAL_LL_HSADC_CTRL1_SMODE_MASK        (0x7UL)
#define HAL_LL_HSADC_CTRL1_STARTA_MASK       (0x2000UL)
#define HAL_LL_HSADC_CTRL2_STARTB_MASK       (0x2000UL)
#define HAL_LL_HSADC_CTRL2_SIMULT_MASK       (0x40UL)
#define HAL_LL_HSADC_CTRL2_DIVA_MASK         (0x3FUL)
#define HAL_LL_HSADC_CTRL3_ADCRES_MASK       (0x300UL)
#define HAL_LL_HSADC_CTRL3_DMASRC_MASK       (0x40UL)
#define HAL_LL_HSADC_PWR_ASB_MASK            (0x8000UL)
#define HAL_LL_HSADC_PWR_APD_MASK            (0x8UL)
#define HAL_LL_HSADC_PWR_PUDELAY_MASK        (0x3F0UL)
#define HAL_LL_HSADC_PWR2_DIVB_MASK          (0x3F00UL)
#define HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK    (0xFFUL)
#define HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK    (0xFF00UL)
#define HAL_LL_HSADC_CALIB_REQSINGA_MASK     (0x1UL)
#define HAL_LL_HSADC_CALIB_REQSINGB_MASK     (0x10UL)

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

/*!< @brief ADC pointers to functions. */
typedef struct {
    void ( *mapped_function_adc_init )( struct hal_ll_adc_hw_specifics_map_t* );
    void ( *mapped_function_adc_set_clock )( struct hal_ll_adc_hw_specifics_map_t*, bool );
    void ( *mapped_function_hsadc_hw_init )( struct hal_ll_adc_hw_specifics_map_t*, hal_ll_adc_resolution_t );
    void ( *mapped_function_adc_hw_init )( struct hal_ll_adc_hw_specifics_map_t *, hal_ll_adc_resolution_t );
    void ( *mapped_function_adc_read_data )( struct hal_ll_adc_base_handle_t *, uint16_t * );
    void ( *mapped_function_adc_set_resolution )( struct hal_ll_adc_hw_specifics_map_t*, hal_ll_adc_resolution_t );
} hal_ll_adc_functions;

/*!< @brief HSADC register structure. */
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
    uint16_t lolim[16];
    uint16_t hilim[16];
    uint16_t offst[16];
    uint16_t pwr;
    uint16_t  __unused1[3];
    uint16_t sctrl;
    uint16_t pwr2;
    uint16_t ctrl3;
    uint16_t scintet;
    uint16_t samptim;
    uint16_t calib;
    uint16_t calval_a;
    uint16_t calval_b;
    uint16_t  __unused2[3];
    uint16_t mux67_sel;
} hal_ll_hsadc_base_handle_t;

/*!< @brief ADC register structure. */
typedef struct {
    uint32_t sc1a;
    uint32_t sc1b;
    uint32_t cfg1;
    uint32_t cfg2;
    uint32_t ra;
    uint32_t rb;
    uint32_t cv1;
    uint32_t cv2;
    uint32_t sc2;
    uint32_t sc3;
    uint32_t OFS;
    uint32_t PG;
    uint32_t MG;
    uint32_t CLPD;
    uint32_t CLPS;
    uint32_t CLP4;
    uint32_t CLP3;
    uint32_t CLP2;
    uint32_t CLP1;
    uint32_t CLP0;
    uint32_t __unused1;
    uint32_t CLMD;
    uint32_t CLMS;
    uint32_t CLM4;
    uint32_t CLM3;
    uint32_t CLM2;
    uint32_t CLM1;
    uint32_t CLM0;
} hal_ll_standard_adc_base_handle_t;

typedef struct {
    hal_ll_hsadc_base_handle_t* hsadc_base_handle;
    hal_ll_standard_adc_base_handle_t* adc_base_handle;
} hal_ll_adc_base_handle_t;

typedef struct{
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_adc_voltage_reference_t vref_input;
    float vref_value;
    uint32_t resolution;
    uint8_t channel;
    uint8_t sample;

    /* NOTE Added pointer function structure. */
    hal_ll_adc_functions mapped_functions;
} hal_ll_adc_hw_specifics_map_t;


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
  * @param[in]  subchannel - Subchannel.
  * @return None
  */
static void hal_ll_adc_converter_config( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_converter_config_t *config, uint8_t subchannel );

/**
  * @brief  Set adequate values for selected mikroBUS pin.
  *
  * @param[in]  hal_ll_adc_base_handle_t* reg_map - ADC module global map.
  * @param[in]  hal_ll_pin_name_t pin - ADC module pin name.
  * @param[in]  uint8_t module_index - ADC HW module index -- 0,1,2...
  * @return None
  */
static void hal_ll_adc_mux67( hal_ll_adc_base_handle_t *reg_map, hal_ll_pin_name_t pin, uint8_t module_index );

/**
  * @brief  Get subchannel.
  *
  * @param[in]  hal_ll_pin_name_t pin - ADC module pin name.
  * @return Subchannel.
  */
static uint8_t hal_ll_adc_subchannel( hal_ll_pin_name_t adc_pin );

/**
  * @brief  Get sample.
  *
  * @param[in]  *hal_ll_hw_reg - ADC module base address.
  * @param[in]  hal_ll_pin_name_t adc_pin - ADC module pin name.
  * @return Sample.
  */
static uint8_t hal_ll_adc_sample( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hal_ll_pin_name_t adc_pin );

/**
  * @brief  Map adequate function addresses.
  *
  * Function maps adequate function addresses based on pin.
  *
  * @param[in]  hal_ll_module_id - Module index.
  * @param[in]  module - Module type (ADC or HSADC).
  *
  * @return none
  *
  */
static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t module );

/**
  * @brief  Initialize ADC module.
  *
  * @param[in]  *map - ADC module base address.
  * @return None
  */
static inline void ptr_function_hsadc_init( hal_ll_adc_hw_specifics_map_t *map );

/**
  * @brief  Enable ADC module gate clock.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  *
  * @return None
  */
static inline void ptr_function_hsadc_set_clock( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Initialize ADC module on the hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  *
  * @return None
  */
static inline void ptr_function_hsadc_hw_init( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution );

/**
  * @brief Executes data read via ADC module.
  *
  * Function shall read raw unsigned analog value.
  *
  * @param *base - ADC module base address.
  * @param *readDatabuf Data buffer where read data
  *                     shall be placed.
  *
  * @return hal_ll_err_t Module specific error.
  */
static inline void ptr_function_hsadc_read_data( hal_ll_adc_base_handle_t *base, uint16_t *readDatabuf );

/**
  * @brief  Initialize ADC module.
  * @param[in] *map - ADC module local map.
  * @return None
  */
static inline void ptr_function_adc_init( hal_ll_adc_hw_specifics_map_t *map  );

/**
  * @brief  Enable ADC module gate clock.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  *
  * @return None
  */
static inline void ptr_function_adc_set_clock( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Initialize ADC module.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  resolution - ADC module resolution.
  *
  * @return None
  */
static inline void ptr_function_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution );

/**
  * @brief Executes data read via ADC module.
  *
  * Function shall read raw unsigned analog value.
  *
  * @param *base - ADC module base address.
  * @param *readDatabuf Data buffer where read data
  *                     shall be placed.
  *
  * @return hal_ll_err_t Module specific error.
  */
static inline void ptr_function_adc_read_data( hal_ll_adc_base_handle_t *base, uint16_t *readDatabuf );

/**
  * @brief  Set ADC resolution.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  resolution - ADC module resolution.
  *
  * @return None
  */
static inline void ptr_function_hsadc_set_resolution( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution );

/**
  * @brief  Set ADC resolution.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  resolution - ADC module resolution.
  *
  * @return None
  */
static inline void ptr_function_adc_set_resolution( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id) {
    uint16_t pin_check_result;
    hal_ll_adc_pin_id index = { HAL_LL_PIN_NC };

    if (( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )))) {
        return HAL_LL_ADC_WRONG_PIN;
    }

    (hal_ll_adc_hw_specifics_map[pin_check_result]->mapped_functions.mapped_function_adc_set_resolution)
    (( hal_ll_base_addr_t )hal_ll_adc_hw_specifics_map, resolution);

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

    if ( ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_adc_check_pins( hal_ll_adc_hw_specifics_map_local->pin, &index, (void *)0 )))) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_init)
    (( hal_ll_base_addr_t )hal_ll_adc_hw_specifics_map_local);

    hal_ll_module_state[ pin_check_result ].hal_ll_adc_handle = ( handle_t* )&hal_ll_adc_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution( handle_t *handle, hal_ll_adc_resolution_t resolution ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_set_resolution)
    (( hal_ll_base_addr_t )hal_ll_adc_hw_specifics_map_local, resolution);

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_init)
    (( hal_ll_base_addr_t )hal_ll_adc_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input( handle_t *handle, hal_ll_adc_voltage_reference_t vref_input ) {
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
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

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_init)
    (( hal_ll_base_addr_t )hal_ll_adc_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value( handle_t *handle, float vref_value ) {
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );

    if( NULL != low_level_handle->hal_ll_adc_handle ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ) {
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_adc_get_module_state_address );
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *base = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_read_data)
    (hal_ll_adc_hw_specifics_map_local->base, readDatabuf);

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ) {
    hal_ll_adc_hw_specifics_map_t *hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;

    if( HAL_LL_MODULE_ERROR != hal_ll_adc_hw_specifics_map_local->base ) {

        if( 0xFF > hal_ll_adc_hw_specifics_map_local->sample ) {
            hal_ll_adc_converter_power_enable( *handle, false );
        }

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

static uint8_t hal_ll_adc_subchannel( hal_ll_pin_name_t adc_pin ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {

        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            return _adc_map[ local_loop_counter ].channel_subgroup;
        }
    }
}

static uint8_t hal_ll_adc_sample( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hal_ll_pin_name_t adc_pin ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;
    uint8_t sample;
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)hal_ll_hw_reg;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {

        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            sample = _adc_map[ local_loop_counter ].sample;
            hal_ll_hw_register->sdis = 0;
            return sample;
        }
    }
}

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size = ( sizeof( _adc_map ) / sizeof( hal_ll_adc_pin_map_t ) );
    uint16_t pin_index = 0;
    uint16_t counter = 0;
    uint8_t  index_counter = 0;
    uint8_t  hal_ll_module_id = 0;
    uint8_t  pin_choice = 0;
    bool     adc_pin = false;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == _adc_map[pin_index].pin )
        {
            if( _adc_map[pin_index].sample < 0xFF ) { // HSADC pin

                // Get module number
                hal_ll_module_id = _adc_map[pin_index].module_index;

                hal_ll_adc_hw_specifics_map[0].base = HAL_LL_HSADC0_BASE_ADDR;
                hal_ll_adc_hw_specifics_map[1].base = HAL_LL_HSADC1_BASE_ADDR;

                map_pointer_functions( hal_ll_module_id, HAL_LL_HSADC_MODULE );
                // Map pin name
                index->pin_an[hal_ll_module_id] = pin_index;
                // Check if module is taken
                if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_adc_handle ) {
                    return hal_ll_module_id;
                } else if ( ADC_MODULE_COUNT == ++index_counter ) {
                    return --index_counter;
                }
            } else {
                pin_choice = pin_index;
                adc_pin = true;
            }
        }

        if( adc_pin && adc_map_size - 1 == counter ) {
            hal_ll_module_id = _adc_map[pin_choice].module_index;

            hal_ll_adc_hw_specifics_map[0].base = HAL_LL_ADC0_BASE_ADDR;
            hal_ll_adc_hw_specifics_map[1].base = HAL_LL_ADC1_BASE_ADDR;

            map_pointer_functions( hal_ll_module_id, HAL_LL_ADC_MODULE );
            // Map pin name
            index->pin_an[hal_ll_module_id] = pin_choice;
            // Check if module is taken
            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_adc_handle ) {
                return hal_ll_module_id;
            } else if ( ADC_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }

        counter++;
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
    hal_ll_adc_hw_specifics_map[module_index].sample = _adc_map[ index->pin_an[module_index] ].sample;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_adc_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[ hal_ll_module_count ]->base ) {
            return &hal_ll_adc_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_adc_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_adc_config_default( hsadc_config_t *config, hal_ll_adc_resolution_t resolution ) {
    config->dual_converter = HAL_LL_HSADC_CONVERTER_TRIGGERED_PARALLEL;
    config->sim_mode_enable = true;
    config->dma_trigger_source = HAL_LL_HSADC_DMA_END_OF_SCAN;
    config->resolution = resolution;
    config->idle_work_mode = HAL_LL_HSADC_IDLE_NORMAL;
    config->power_up_delay = 18;
}

static void hal_ll_adc_converter_config_default( hsadc_converter_config_t *converter_config ) {
    converter_config->clock_divisor = 3UL;
    converter_config->sampling_time = 0UL;
    converter_config->power_up_calibration_mode = HAL_LL_HSADC_CALIBRATION_MODE_SINGLE_ENDED;
}

static void hal_ll_adc_ctrl_pwr_init( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_config_t *config ) {
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)hal_ll_hw_reg;
    uint16_t mask;

    // CTRL1
    mask = hal_ll_hw_register->ctrl1 & ~HAL_LL_HSADC_CTRL1_SMODE_MASK;
    mask |= config->dual_converter & HAL_LL_HSADC_CTRL1_SMODE_MASK;
    hal_ll_hw_register->ctrl1 = mask;
    //CTRL2
    mask =  hal_ll_hw_register->ctrl2 & ~HAL_LL_HSADC_CTRL2_SIMULT_MASK;
    if( config->sim_mode_enable ) {
        mask |= HAL_LL_HSADC_CTRL2_SIMULT_MASK;
    }
    hal_ll_hw_register->ctrl2 = mask;
    // CTRL3
    mask = hal_ll_hw_register->ctrl3 & ~( HAL_LL_HSADC_CTRL3_ADCRES_MASK | HAL_LL_HSADC_CTRL3_DMASRC_MASK );
    mask |= ((( config->dma_trigger_source << HAL_LL_HSADC_CTRL3_DMASRC_BIT ) & HAL_LL_HSADC_CTRL3_DMASRC_MASK ) |
             (( config->resolution << HAL_LL_HSADC_CTRL3_ADCRES_SHIFT ) & HAL_LL_HSADC_CTRL3_ADCRES_MASK ));
    hal_ll_hw_register->ctrl3 = mask;
    // PWR
    mask = hal_ll_hw_register->pwr & ~( HAL_LL_HSADC_PWR_ASB_MASK | HAL_LL_HSADC_PWR_APD_MASK | HAL_LL_HSADC_PWR_PUDELAY_MASK );
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
    hal_ll_hw_register->pwr = mask;
}

static void hal_ll_adc_converter_config( hal_ll_adc_base_handle_t *hal_ll_hw_reg, hsadc_converter_config_t *config, uint8_t subchannel ) {
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)hal_ll_hw_reg;
    uint16_t mask;

    if( HAL_LL_ADC_CHANNEL_SUB_A == subchannel ) {
        mask = hal_ll_hw_register->ctrl2 & ~HAL_LL_HSADC_CTRL2_DIVA_MASK;
        mask |= ( config->clock_divisor - 1 ) & HAL_LL_HSADC_CTRL2_DIVA_MASK;
        hal_ll_hw_register->ctrl2 = mask;

        mask = hal_ll_hw_register->calib & ~( HAL_LL_HSADC_CALIB_REQSINGA_MASK );
        mask |= HAL_LL_HSADC_CALIB_REQSINGA_MASK;
        hal_ll_hw_register->calib = mask;

        mask = hal_ll_hw_register->samptim & ~HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK;
        mask |= config->sampling_time & HAL_LL_HSADC_SAMPTIM_SAMPT_A_MASK;
        hal_ll_hw_register->samptim = mask;
        hal_ll_hw_register->calval_a = 0;
    } else if ( HAL_LL_ADC_CHANNEL_SUB_B == subchannel ) {
        mask = hal_ll_hw_register->pwr2 & ~HAL_LL_HSADC_PWR2_DIVB_MASK;
        mask |= (( config->clock_divisor - 1 ) << HAL_LL_HSADC_PWR2_DIVB_SHIFT ) & HAL_LL_HSADC_PWR2_DIVB_MASK;
        hal_ll_hw_register->pwr2 = mask;

        mask = hal_ll_hw_register->calib & ~( HAL_LL_HSADC_CALIB_REQSINGB_MASK );
        mask |= HAL_LL_HSADC_CALIB_REQSINGB_MASK;
        hal_ll_hw_register->calib = mask;

        mask = hal_ll_hw_register->samptim & ~HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK;
        mask |= ( config->sampling_time << HAL_LL_HSADC_SAMPTIM_SAMPT_B_SHIFT ) & HAL_LL_HSADC_SAMPTIM_SAMPT_B_MASK;
        hal_ll_hw_register->samptim = mask;
        hal_ll_hw_register->calval_b = 0;
    }
}

static void hal_ll_adc_converter_power_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable ) {
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)hal_ll_hw_reg;

    if( true == enable ){
        clear_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PDA_BIT );
        clear_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PDB_BIT );
    } else {
        set_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PDA_BIT );
        set_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PDB_BIT );
    }

    while( check_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PSTSA_BIT |
           check_reg_bit( &( hal_ll_hw_register->pwr ), HAL_LL_HSADC_PWR_PSTSB_BIT )));
}

static void hal_ll_adc_converter_enable( hal_ll_adc_base_handle_t *hal_ll_hw_reg, bool enable ) {
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)hal_ll_hw_reg;

    if( true == enable ) {
        clear_reg_bit( &( hal_ll_hw_register->ctrl1 ), HAL_LL_HSADC_CTRL1_STOPA_BIT );
        clear_reg_bit( &( hal_ll_hw_register->ctrl2 ), HAL_LL_HSADC_CTRL2_STOPB_BIT );
    } else {
        set_reg_bit( &( hal_ll_hw_register->ctrl1 ), HAL_LL_HSADC_CTRL1_STOPA_BIT );
        set_reg_bit( &( hal_ll_hw_register->ctrl2 ), HAL_LL_HSADC_CTRL2_STOPB_BIT );
    }
}

static void hal_ll_adc_mux67( hal_ll_adc_base_handle_t *reg_map, hal_ll_pin_name_t adc_pin, uint8_t module_id ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;

    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)reg_map;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {

        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            if( 6 == hal_ll_adc_hw_specifics_map[module_id].sample || 7 == hal_ll_adc_hw_specifics_map[module_id].sample ||
                14 == hal_ll_adc_hw_specifics_map[module_id].sample || 15 == hal_ll_adc_hw_specifics_map[module_id].sample ) {
                switch( _adc_map[ local_loop_counter ].channel ) {
                    case 6:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x00;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x000;
                        break;
                    case 7:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x00;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x0000;
                        break;
                    case 8:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x01;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x100;
                        break;
                    case 9:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x10;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x1000;
                        break;
                    case 10:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x02;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x200;
                        break;
                    case 11:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x20;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x2000;
                        break;
                    case 12:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x03;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x300;
                        break;
                    case 13:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x30;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x3000;
                        break;
                    case 14:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x04;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x400;
                        break;
                    case 15:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x40;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x4000;
                        break;
                    case 16:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x05;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x500;
                        break;
                    case 17:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x50;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x5000;
                        break;
                    case 18:
                        if ( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x06;
                        else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup )
                            hal_ll_hw_register->mux67_sel = 0x600;
                        break;

                    default:
                        break;
                }
            }
        }
    }
}

static void hal_ll_adc_set_subchannel( hal_ll_adc_base_handle_t *base, hal_ll_pin_name_t adc_pin ) {
    static const uint16_t local_adc_map_size = ( sizeof( _adc_map )) / ( sizeof( hal_ll_adc_pin_map_t ));
    uint16_t local_loop_counter;
    hal_ll_standard_adc_base_handle_t *hal_ll_hw_register = (hal_ll_standard_adc_base_handle_t*)base;

    for( local_loop_counter = 0; local_loop_counter < local_adc_map_size; local_loop_counter++ ) {
        if( adc_pin == _adc_map[ local_loop_counter].pin ) {
            if ( _adc_map[ local_loop_counter].sample < 0xFF ) continue;
            if( HAL_LL_ADC_CHANNEL_SUB_A == _adc_map[ local_loop_counter ].channel_subgroup ) {
                clear_reg_bit( &hal_ll_hw_register->cfg2, HAL_LL_ADC_MUX_SELECT );
                break;
            } else if ( HAL_LL_ADC_CHANNEL_SUB_B == _adc_map[ local_loop_counter ].channel_subgroup ) {
                set_reg_bit( &hal_ll_hw_register->cfg2, HAL_LL_ADC_MUX_SELECT );
            }
        }
    }
}

//-------------------------------------------------------------------------- STATIC POINTER FUNCTIONS

static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t module ) {
    if ( HAL_LL_HSADC_MODULE == module ) {
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_init = &ptr_function_hsadc_init;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_set_clock = &ptr_function_hsadc_set_clock;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_hsadc_hw_init = &ptr_function_hsadc_hw_init;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_read_data = &ptr_function_hsadc_read_data;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_set_resolution = &ptr_function_hsadc_set_resolution;
    } else {
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_init = &ptr_function_adc_init;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_set_clock = &ptr_function_adc_set_clock;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_hw_init = &ptr_function_adc_hw_init;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_read_data = &ptr_function_adc_read_data;
        hal_ll_adc_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_adc_set_resolution = &ptr_function_adc_set_resolution;
    }
}

static inline void ptr_function_hsadc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    volatile uint32_t port_name = hal_ll_gpio_port_base(hal_ll_gpio_port_index(map->pin));

    hal_ll_gpio_analog_input( &port_name,
                              hal_ll_gpio_pin_mask( map->pin ) );

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_set_clock)
    (( hal_ll_base_addr_t )map, true);

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_hsadc_hw_init)
    (( hal_ll_base_addr_t )map, map->resolution);
}

static inline void ptr_function_hsadc_set_clock( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state ) {
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

static inline void ptr_function_hsadc_hw_init( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution ) {
    hsadc_config_t config;
    hsadc_converter_config_t converter_config;
    uint8_t subchannel, sample;

    hal_ll_adc_base_handle_t *hal_ll_hw_reg = hal_ll_adc_get_base_struct( map->base );
    subchannel = hal_ll_adc_subchannel( map->pin );
    sample = hal_ll_adc_sample( hal_ll_hw_reg, map->pin );

    hal_ll_adc_config_default( &config, resolution );
    hal_ll_adc_converter_config_default( &converter_config );
    hal_ll_adc_ctrl_pwr_init( hal_ll_hw_reg, &config );

    hal_ll_adc_converter_config( hal_ll_hw_reg, &converter_config, subchannel );
    hal_ll_adc_converter_power_enable( hal_ll_hw_reg, true );
    hal_ll_adc_mux67( hal_ll_hw_reg, map->pin, map->module_index );
    hal_ll_adc_converter_enable( hal_ll_hw_reg, true );
}

static inline void ptr_function_hsadc_read_data( hal_ll_adc_base_handle_t *base, uint16_t *readDatabuf ) {
    hal_ll_hsadc_base_handle_t *hal_ll_hw_register = (hal_ll_hsadc_base_handle_t*)base;

    hal_ll_hw_register->ctrl1 |= HAL_LL_HSADC_CTRL1_STARTA_MASK;
    hal_ll_hw_register->ctrl2 |= HAL_LL_HSADC_CTRL2_STARTB_MASK;

    while( !check_reg_bit( &( hal_ll_hw_register->stat ), HAL_LL_HSADC_STAT_EOSIA_BIT )){}

    if ( (1UL << hal_ll_adc_hw_specifics_map_local->sample) & hal_ll_hw_register->rdy ) {
        switch( hal_ll_hw_register->ctrl3 & HAL_LL_HSADC_CTRL3_ADCRES_MASK )
        {
            case HAL_LL_ADC_6BIT_RESOLUTION_MASK:
                *readDatabuf = hal_ll_hw_register->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 9;
                break;
            case HAL_LL_ADC_8BIT_RESOLUTION_MASK:
                *readDatabuf = hal_ll_hw_register->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 7;
                break;
            case HAL_LL_ADC_10BIT_RESOLUTION_MASK:
                *readDatabuf = hal_ll_hw_register->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 5;
                break;
            case HAL_LL_ADC_12BIT_RESOLUTION_MASK:
                *readDatabuf = hal_ll_hw_register->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 3;
                break;

            default:
                *readDatabuf = hal_ll_hw_register->rslt[hal_ll_adc_hw_specifics_map_local->sample] >> 3;
                break;
        }
    }

    hal_ll_adc_mux67( base, hal_ll_adc_hw_specifics_map_local->pin, hal_ll_adc_hw_specifics_map_local->module_index );
}

static inline void ptr_function_hsadc_set_resolution( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution ) {
        switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_6_BIT:
            map->resolution = HAL_LL_HSADC_6BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            map->resolution = HAL_LL_HSADC_8BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            map->resolution = HAL_LL_HSADC_10BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            map->resolution = HAL_LL_HSADC_12BIT_RESOLUTION;
            break;

        default:
            map->resolution = HAL_LL_HSADC_12BIT_RESOLUTION;
            break;
    }
}

static inline void ptr_function_adc_set_resolution( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution ) {
        switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_8_BIT:
            map->resolution = HAL_LL_ADC_8BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_10_BIT:
            map->resolution = HAL_LL_ADC_10BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            map->resolution = HAL_LL_ADC_12BIT_RESOLUTION;
            break;
        case HAL_LL_ADC_RESOLUTION_16_BIT:
            map->resolution = HAL_LL_ADC_16BIT_RESOLUTION;
            break;

        default:
            map->resolution = HAL_LL_ADC_12BIT_RESOLUTION;
            break;
    }
}

static inline void ptr_function_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    volatile uint32_t port_name = hal_ll_gpio_port_base(hal_ll_gpio_port_index(map->pin));

    hal_ll_gpio_analog_input( &port_name,
                              hal_ll_gpio_pin_mask( map->pin ) );

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_set_clock)
    (( hal_ll_base_addr_t )map, true);

    (hal_ll_adc_hw_specifics_map_local->mapped_functions.mapped_function_adc_hw_init)
    (( hal_ll_base_addr_t )map, map->resolution);
}

static inline void ptr_function_adc_set_clock( hal_ll_adc_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch( map->module_index ) {
        #ifdef ADC_MODULE_0
        case hal_ll_adc_module_num( ADC_MODULE_0 ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC6, HAL_LL_ADCEN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC6, HAL_LL_ADCEN_BIT );
            }
            break;
        #endif
        #if defined(ADC_MODULE_1)
        case ( hal_ll_adc_module_num( ADC_MODULE_1 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC3, HAL_LL_ADCEN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC3, HAL_LL_ADCEN_BIT );
            }
            break;
        #endif
    }
}

static inline void ptr_function_adc_hw_init( hal_ll_adc_hw_specifics_map_t *map, hal_ll_adc_resolution_t resolution ) {
    hal_ll_standard_adc_base_handle_t *hal_ll_hw_register = (hal_ll_standard_adc_base_handle_t*)map->base;

    // Reset all registers to a known state.
    hal_ll_hw_register->cfg1 = 0;
    hal_ll_hw_register->cfg2 = 0;
    hal_ll_hw_register->cv1  = 0;
    hal_ll_hw_register->cv2  = 0;
    hal_ll_hw_register->sc2  = 0;
    hal_ll_hw_register->sc3  = 0;

    // Clear ADC Configuration Register 1 (ADCx_CFG1).
    hal_ll_hw_register->cfg1 &= ~HAL_LL_ADC_CFG1_CLEAR_MASK;

    // Enable low power mode.
    set_reg_bit( &hal_ll_hw_register->cfg1, HAL_LL_ADC_LOW_POWER_ENABLE );

    // Set ADC Input Clock divider ratio.
    hal_ll_hw_register->cfg1 |= HAL_LL_ADC_CLOCK_DIV_8;

    // Set Long Sample time.
    hal_ll_hw_register->cfg1 |= HAL_LL_ADC_LONG_SAMPLE_TIME_ENABLE;

    // Set ADC Clock source.
    hal_ll_hw_register->cfg1 |= HAL_LL_ADC_CLOCK_SOURCE_ASYNC;

    // Clear ADC Configuration Register 2 (ADCx_CFG2).
    hal_ll_hw_register->cfg2 &= ~HAL_LL_ADC_CFG2_CLEAR_MASK;

    // Changes the ADC mux setting to select between alternate sets of ADC channels.
    hal_ll_adc_set_subchannel( map->base, map->pin );

    // Async Clock Output Enable.
    hal_ll_hw_register->cfg2 |= HAL_LL_ADC_ASYNC_CLOCK_ENABLE;

    // Set ADC Resolution.
    hal_ll_hw_register->cfg1 |= resolution;
}

static inline void ptr_function_adc_read_data( hal_ll_adc_base_handle_t *base, uint16_t *readDatabuf ) {
    hal_ll_standard_adc_base_handle_t *hal_ll_hw_register = (hal_ll_standard_adc_base_handle_t*)base;

    hal_ll_hw_register->sc1a = hal_ll_adc_hw_specifics_map_local->channel & HAL_LL_ADC_MASK_CHANNEL;

    while ( 0 == ( hal_ll_hw_register->sc1a & HAL_LL_ADC_COCO_FLAG ) );

    *readDatabuf = ( uint16_t )hal_ll_hw_register->ra;
}
// ------------------------------------------------------------------------- END
