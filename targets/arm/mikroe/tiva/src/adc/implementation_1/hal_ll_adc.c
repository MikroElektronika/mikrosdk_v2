/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_adc_module_num(_module_num)      (_module_num - 1)

#define HAL_LL_ADC_RCGCADC_R0_BIT_POS           (0)
#define HAL_LL_ADC_RCGCADC_R0_BIT_MSK           (0x1UL << HAL_LL_ADC_RCGCADC_R0_BIT_POS)
#define HAL_LL_ADC_RCGCADC_R1_BIT_POS           (1)
#define HAL_LL_ADC_RCGCADC_R1_BIT_MSK           (0x1UL << HAL_LL_ADC_RCGCADC_R1_BIT_POS)

#define HAL_LL_ADC_CTL_VREF0_BIT                (0)
#define HAL_LL_ADC_CTL_VREF0_BIT_MASK           (1UL << HAL_LL_ADC_CTL_VREF0_BIT)
#define HAL_LL_ADC_CTL_VREF1_BIT                (1)
#define HAL_LL_ADC_CTL_VREF1_BIT_MASK           (1UL << HAL_LL_ADC_CTL_VREF1_BIT)
#define HAL_LL_ADC_CTL_VREF_MASK                (HAL_LL_ADC_CTL_VREF0_BIT_MASK | HAL_LL_ADC_CTL_VREF1_BIT_MASK)
#define HAL_LL_ADC_EMUX_SS3_TRIGGER_SELECT      (0xF000)
#define HAL_LL_ADC_ACTSS_SS3_ENABLE_BIT         (3)
#define HAL_LL_ADC_SSPRI_RESET_STATE            (0x3210)
#define HAL_LL_ADC_SSEMUX_EMUX0_BIT             (0)
#define HAL_LL_ADC_SSCTL3_END0_BIT              (1)
#define HAL_LL_ADC_SSCTL3_IE0_BIT               (2)
#define HAL_LL_ADC_SSOP3_S0DCOP_BIT             (0)
#define HAL_LL_ADC_ACTSS_ASEN3_BIT              (3)
#define HAL_LL_ADC_ISC_INTERRUPT_STATUS_MASK    (0xF)
#define HAL_LL_ADC_PSSI_SS3_BIT                 (3)
#define HAL_LL_ADC_RIS_INR3_BIT                 (3)

#define HAL_LL_ADC_12BIT_RES                    (0x00000000UL)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief Local handle list. */
static hal_ll_adc_handle_register_t hal_ll_module_state[ ADC_MODULE_COUNT ] = { (handle_t *) NULL, (handle_t *) NULL, false };

/*!< @brief ADC register structure. */
typedef struct {
    volatile uint32_t actss;
    volatile uint32_t ris;
    volatile uint32_t im;
    volatile uint32_t isc;
    volatile uint32_t ostat;
    volatile uint32_t emux;
    volatile uint32_t ustat;
    volatile uint32_t tssel;
    volatile uint32_t sspri;
    volatile uint32_t spc;
    volatile uint32_t pssi;
    uint32_t __unused1;
    volatile uint32_t sac;
    volatile uint32_t dcisc;
    volatile uint32_t ctl;
    uint32_t __unused2;
    volatile uint32_t ssmux0;
    volatile uint32_t ssctl0;
    volatile uint32_t ssfifo0;
    volatile uint32_t ssfstat0;
    volatile uint32_t ssop0;
    volatile uint32_t ssdc0;
    volatile uint32_t ssemux0;
    volatile uint32_t sstsh0;
    volatile uint32_t ssmux1;
    volatile uint32_t ssctl1;
    volatile uint32_t ssfifo1;
    volatile uint32_t ssfstat1;
    volatile uint32_t ssop01;
    volatile uint32_t ssdc1;
    volatile uint32_t ssemux1;
    volatile uint32_t sstsh1;
    volatile uint32_t ssmux2;
    volatile uint32_t ssctl2;
    volatile uint32_t ssfifo2;
    volatile uint32_t ssfstat2;
    volatile uint32_t ssop2;
    volatile uint32_t ssdc2;
    volatile uint32_t ssemux2;
    volatile uint32_t sstsh2;
    volatile uint32_t ssmux3;
    volatile uint32_t ssctl3;
    volatile uint32_t ssfifo3;
    volatile uint32_t ssfstat3;
    volatile uint32_t ssop3;
    volatile uint32_t ssdc3;
    volatile uint32_t ssemux3;
    /* Commented out for memory optimization;
     * Uncomment if needed.
     */
    /*
    volatile uint32_t sstsh3;
    uint32_t __unused3[784];
    volatile uint32_t dcric;
    uint32_t __unused4[63];
    volatile uint32_t dcctl0;
    volatile uint32_t dcctl1;
    volatile uint32_t dcctl2;
    volatile uint32_t dcctl3;
    volatile uint32_t dcctl4;
    volatile uint32_t dcctl5;
    volatile uint32_t dcctl6;
    volatile uint32_t dcctl7;
    uint32_t __unused5[8];
    volatile uint32_t dccmp0;
    volatile uint32_t dccmp1;
    volatile uint32_t dccmp2;
    volatile uint32_t dccmp3;
    volatile uint32_t dccmp4;
    volatile uint32_t dccmp5;
    volatile uint32_t dccmp6;
    volatile uint32_t dccmp7;
    uint32_t __unused6[88];
    volatile uint32_t pp;
    volatile uint32_t pc;
    volatile uint32_t cc;
    */
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
    {ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif
    #ifdef ADC_MODULE_1
    {ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_12_BIT, 0xFF},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_VREF_DEFAULT, 0, HAL_LL_ADC_RESOLUTION_DEFAULT, 0xFF}
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
static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 * @details Maps pin name, register address and channel from analog register list to module in hardware specific map.
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
  * @brief  Enable ADC module gate clock.
  * @param  module_index - ADC HW module index -- 0,1,2...
  * @param  state - true/false
  * @return None
  */
static void adc_clock_enable(uint8_t module_index , bool state );

/**
 * @brief  Initialize hardware ADC module.
 * @details Hardware initialization of Tiva.
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

hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input,
                                        hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id){
    uint8_t pin_check_result;
    hal_ll_adc_pin_id index = {HAL_LL_PIN_NC};

    if ( (pin_check_result = hal_ll_adc_check_pins( pin, &index, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_ADC_WRONG_PIN;
    };

    switch ( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map[pin_check_result].resolution = HAL_LL_ADC_12BIT_RES;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    switch ( vref_input ){
        case HAL_LL_ADC_VREF_INTERNAL:
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_INTERNAL;
            break;
        case HAL_LL_ADC_VREF_EXTERNAL: // DEFAULT CASE
            hal_ll_adc_hw_specifics_map[pin_check_result].vref_input = HAL_LL_ADC_VREF_EXTERNAL;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_VREF;
    }

    if ( hal_ll_adc_hw_specifics_map[pin_check_result].pin != pin ){
        hal_ll_adc_map_pin( pin_check_result, &index );
        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_adc_handle;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle ){
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    hal_ll_adc_handle_register_t *hal_handle = (hal_ll_adc_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_adc_hw_specifics_map_local->module_index;

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );
    hal_ll_module_state[pin_check_result].hal_ll_adc_handle = (handle_t *)&hal_ll_adc_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution){
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    if( NULL == low_level_handle->hal_ll_adc_handle ) {
        return HAL_LL_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    switch( resolution ) {
        case HAL_LL_ADC_RESOLUTION_12_BIT:
            hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_12BIT_RES;
            break;

        default:
            return HAL_LL_ADC_UNSUPPORTED_RESOLUTION;
    }

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input) {
    hal_ll_adc_handle_register_t *low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

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

    hal_ll_adc_init( hal_ll_adc_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value){
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_adc_handle  ) {
        hal_ll_adc_hw_specifics_map_local->vref_value = vref_value;
    }
}

hal_ll_err_t hal_ll_adc_read( handle_t *handle, uint16_t *readDatabuf ){
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_adc_get_module_state_address);
    low_level_handle = hal_ll_adc_get_handle;
    hal_ll_adc_base_handle_t *hal_ll_hw_reg = ( hal_ll_adc_base_handle_t * )hal_ll_adc_hw_specifics_map_local->base ;

    if( NULL == low_level_handle->hal_ll_adc_handle  ) {
        return HAL_LL_MODULE_ERROR;
    }

    // Disable SS3 before changing settings.
    clear_reg_bit( &hal_ll_hw_reg->actss, HAL_LL_ADC_ACTSS_SS3_ENABLE_BIT );

    /* Enable sample sequence 3 with a processor signal trigger. Sequence 3
     * will do a single sample when the processor sends a signal to start the
     * conversion. Each ADC module has 4 programmable sequences, sequence 0
     * to sequence 3. This library is arbitrarily using sequence 3.
     */
    hal_ll_hw_reg->emux &= ~HAL_LL_ADC_EMUX_SS3_TRIGGER_SELECT;

    // SS3 highest priority, followed by SS2, SS1 and SS0 respectively.
    hal_ll_hw_reg->sspri = HAL_LL_ADC_SSPRI_RESET_STATE;

    // Channel number for sampling data.
    hal_ll_hw_reg->ssmux3 = hal_ll_adc_hw_specifics_map_local->channel;

    if (hal_ll_adc_hw_specifics_map_local->channel > HAL_LL_ADC_CHANNEL_15)
        set_reg_bit( &hal_ll_hw_reg->ssemux3, HAL_LL_ADC_SSEMUX_EMUX0_BIT );
    else
        clear_reg_bit( &hal_ll_hw_reg->ssemux3, HAL_LL_ADC_SSEMUX_EMUX0_BIT );

    set_reg_bit( &hal_ll_hw_reg->ssctl3, HAL_LL_ADC_SSCTL3_END0_BIT );
    set_reg_bit( &hal_ll_hw_reg->ssctl3, HAL_LL_ADC_SSCTL3_IE0_BIT );
    clear_reg_bit( &hal_ll_hw_reg->ssop3, HAL_LL_ADC_SSOP3_S0DCOP_BIT );

    set_reg_bit( &hal_ll_hw_reg->actss, HAL_LL_ADC_ACTSS_ASEN3_BIT );
    // Clear all interrupts and raw interrupts before sampling.
    hal_ll_hw_reg->isc |= HAL_LL_ADC_ISC_INTERRUPT_STATUS_MASK;
    // Start conversion on SS3.
    set_reg_bit( &hal_ll_hw_reg->pssi, HAL_LL_ADC_PSSI_SS3_BIT );
    // Wait for conversion to be completed.
    while( !check_reg_bit( &hal_ll_hw_reg->ris, HAL_LL_ADC_RIS_INR3_BIT ) );

    // Conversion result from SS3.
    *readDatabuf = hal_ll_hw_reg->ssfifo3;

    return HAL_LL_ADC_SUCCESS;
}

void hal_ll_adc_close( handle_t *handle ){
    hal_ll_adc_hw_specifics_map_local = hal_ll_get_specifics( *handle );
    low_level_handle = hal_ll_adc_get_handle;

    if ( *( low_level_handle->hal_ll_adc_handle ) != NULL ) {
        hal_ll_adc_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
        hal_ll_adc_hw_specifics_map_local->vref_input = HAL_LL_ADC_VREF_DEFAULT;
        hal_ll_adc_hw_specifics_map_local->vref_value = 3.3f;
        hal_ll_adc_hw_specifics_map_local->resolution = HAL_LL_ADC_RESOLUTION_12_BIT;

        low_level_handle->hal_ll_adc_handle = NULL;
        low_level_handle->hal_drv_adc_handle = NULL;
        low_level_handle->init_ll_state = false;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_adc_check_pins( hal_ll_pin_name_t pin, hal_ll_adc_pin_id *index, hal_ll_adc_handle_register_t *handle_map ) {
    static const uint16_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );
    uint16_t pin_index = 0;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ )
    {
        if ( pin == hal_ll_analog_in_register_list[pin_index].pin )
        {
            // Get module number.
            hal_ll_module_id = hal_ll_analog_in_register_list[pin_index].module_index;
            // Map pin name.
            index->pin_an[hal_ll_module_id] = pin_index;

            // Check if module is taken.
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
    // Map new pins.
    hal_ll_adc_hw_specifics_map[module_index].pin = hal_ll_analog_in_register_list[ index->pin_an[module_index] ].pin;
    hal_ll_adc_hw_specifics_map[module_index].channel = hal_ll_analog_in_register_list[ index->pin_an[module_index] ].channel;
}

static hal_ll_adc_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_adc_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_adc_get_base_from_hal_handle == hal_ll_adc_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_adc_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_adc_hw_specifics_map[hal_ll_module_error];
}

static void adc_clock_enable( uint8_t module_index , bool state ) {
    switch( module_index ) {
        case hal_ll_adc_module_num( ADC_MODULE_0 ):
            if ( true == state ) {
                set_reg_bit( _SYSCTL_RCGCADC, HAL_LL_ADC_RCGCADC_R0_BIT_POS );
            } else {
                clear_reg_bit( _SYSCTL_RCGCADC, HAL_LL_ADC_RCGCADC_R0_BIT_POS );
            }
            break;
        case hal_ll_adc_module_num( ADC_MODULE_1 ):
            if ( true == state ) {
                set_reg_bit( _SYSCTL_RCGCADC, HAL_LL_ADC_RCGCADC_R1_BIT_POS );
            } else {
                clear_reg_bit( _SYSCTL_RCGCADC, HAL_LL_ADC_RCGCADC_R1_BIT_POS );
            }
            break;

        default:
            break;
    }
}

static void hal_ll_adc_hw_init(hal_ll_adc_hw_specifics_map_t *map) {
    hal_ll_adc_base_handle_t *hal_ll_hw_reg = ( hal_ll_adc_base_handle_t *)map->base;

    // Set Vref.
    switch ( map->vref_input ) {
        case HAL_LL_ADC_VREF_EXTERNAL :
            hal_ll_hw_reg->ctl |= HAL_LL_ADC_CTL_VREF_MASK;
            break;
        case HAL_LL_ADC_VREF_INTERNAL :
            hal_ll_hw_reg->ctl &= ~HAL_LL_ADC_CTL_VREF_MASK;
            break;

        default :
            /* In case some Vref configuration is received, that is not valid for this hardware
             * a default configuration is set up, in this case Vref internal. */
            hal_ll_hw_reg->ctl &= ~HAL_LL_ADC_CTL_VREF_MASK;
            break;
    }
}

static void hal_ll_adc_init( hal_ll_adc_hw_specifics_map_t *map ) {
    uint32_t port;

    adc_clock_enable( map->module_index, true );

    port = hal_ll_gpio_port_base( hal_ll_gpio_port_index( map->pin ) );
    hal_ll_gpio_analog_input( &port , hal_ll_gpio_pin_mask( map->pin ) );

    hal_ll_adc_hw_init( map );
}

// ------------------------------------------------------------------------- END
