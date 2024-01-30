/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_ll_can.c
 * @brief CAN HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rcc.h"
#include "hal_ll_can.h"
#include "hal_ll_gpio.h"
#include "hal_ll_can_pin_map.h"
#include "hal_ll_bit_control.h"

/*!< @brief Local handle list */
static volatile hal_ll_can_handle_register_t hal_ll_module_state[CAN_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_can_get_module_state_address ((hal_ll_can_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_can_get_handle (hal_ll_can_handle_register_t *)hal_ll_can_get_module_state_address->hal_ll_can_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_can_get_base_struct(_handle) ((hal_ll_can_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_can_get_base_from_hal_handle ((hal_ll_can_hw_specifics_map_t *)((hal_ll_can_handle_register_t *)\
                                            (((hal_ll_can_handle_register_t *)(handle))->hal_ll_can_handle))->hal_ll_can_handle)->base

#define HAL_LL_CAN_AF_CONFIG (GPIO_CFG_ALT_FUNCTION | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA)

#define HAL_LL_CAN1_CLOCK_ENABLE            (0)
#define HAL_LL_CAN2_CLOCK_ENABLE            (1)

#define HAL_LL_CAN_CANCTL_INIT_BIT          (0)
#define HAL_LL_CAN_CANCTL_DAR_BIT           (5)
#define HAL_LL_CAN_CANCTL_TEST_BIT          (7)
#define HAL_LL_CAN_CANTST_LBACK_BIT         (4)
#define HAL_LL_CAN_CANCTL_CCE_BIT           (6)

#define HAL_LL_CAN_IF_CRQ_BUSY_BIT          (15)

#define HAL_LL_CAN_IF_CMSK_WRNRD_MASK       (0x80UL)
#define HAL_LL_CAN_IF_CMSK_MASK_MASK        (0x40UL)
#define HAL_LL_CAN_IF_CMSK_ARB_MASK         (0x20UL)
#define HAL_LL_CAN_IF_CMSK_CONTROL_MASK     (0x10UL)
#define HAL_LL_CAN_IF_CMSK_CLRINTPND_MASK   (0x8UL)
#define HAL_LL_CAN_IF_CMSK_NEWDAT_MASK      (0x4UL)
#define HAL_LL_CAN_IF_CMSK_TXRQST_MASK      (HAL_LL_CAN_IF_CMSK_NEWDAT_MASK)
#define HAL_LL_CAN_IF_CMSK_DATAA_MASK       (0x2UL)
#define HAL_LL_CAN_IF_CMSK_DATAB_MASK       (0x1UL)
#define HAL_LL_CAN_IF_CMSK_TXRQST_BIT       (2)
#define HAL_LL_CAN_IF_CMSK_NEWDAT_BIT       (HAL_LL_CAN_IF_CMSK_TXRQST_BIT)

#define HAL_LL_CAN_IF_MCTL_RMTEN_BIT        (9)
#define HAL_LL_CAN_IF_MCTL_TXRQST_BIT       (8)
#define HAL_LL_CAN_IF_MCTL_EOB_BIT          (7)
#define HAL_LL_CAN_IF_MCTL_NEWDAT_BIT       (15)
#define HAL_LL_CAN_IF_MCTL_DLC_MASK         (0xFUL)
#define HAL_LL_CAN_IF_MCTL_TXRQST_MASK      (0x100UL)
#define HAL_LL_CAN_IF_MCTL_UMASK_BIT        (12)

#define HAL_LL_CAN_IF_ARB2_MSGVAL_BIT       (15)
#define HAL_LL_CAN_IF_ARB2_XTD_BIT          (14)
#define HAL_LL_CAN_IF_ARB2_DIR_BIT          (13)
#define HAL_LL_CAN_IF_ARB2_ID_MASK          (0x1FFFUL)
#define HAL_LL_CAN_IF_ARB2_MSGVAL_MASK      (0x8000UL)
#define HAL_LL_CAN_IF_ARB2_DIR_MASK         (0x2000UL)
#define HAL_LL_CAN_IF_ARB2_ID_SHIFT         (2)

#define HAL_LL_CAN_IF_MSK2_ID_SHIFT         (HAL_LL_CAN_IF_ARB2_ID_SHIFT)

#define HAL_LL_CAN_CANBIT_SJW_SHIFT         (6)
#define HAL_LL_CAN_CANBIT_TSEG1_SHIFT       (8)
#define HAL_LL_CAN_CANBIT_TSEG2_SHIFT       (12)
#define HAL_LL_CAN_CANBRPE_PRESCALER_SHIFT  (6)
#define HAL_LL_CAN_PRESCALER_BITS_5_0       (0x3FUL)
#define HAL_LL_CAN_PRESCALER_BITS_10_6      (0x3CUL)

#define HAL_LL_CAN_SJW_CONST_VALUE          (1)
#define HAL_LL_CAN_TSEG1_MAX_VAL            (16)
#define HAL_LL_CAN_TSEG2_MAX_VAL            (8)
#define HAL_LL_CAN_PRESCALER_MAX_VAL        (1024)
#define HAL_LL_CAN_BIT_RATE_SAMPLE_POINT    (0.875)

#define HAL_LL_CAN_TRANSMIT_MESSAGE_ID      (1)

#define HAL_LL_CAN_EID_BITS_28_11           (0x3FFFF800UL)
#define HAL_LL_CAN_SID_MASK                 (0x7FFUL)

#define HAL_LL_CAN_MAX_MNUM                 (32)

#define HAL_LL_CAN_REG_CLEAR                (0x0000UL)

#define HAL_LL_CAN_IF_DATA_SHIFT            (8)

#define HAL_LL_CAN_TIMEOUT_VALUE            (10000UL)

/*!< @brief CAN hw specific structure */
typedef struct
{
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_can_pins_t pins;
    hal_ll_can_mode_t mode;
    uint32_t frequency;
} hal_ll_can_hw_specifics_map_t;

/*!< @brief CAN hw specific module values */
typedef struct
{
    hal_ll_pin_name_t pin_tx;
    hal_ll_pin_name_t pin_rx;
} hal_ll_can_pin_id;

/*!< @brief CAN IF structure */
typedef struct
{
    hal_ll_base_addr_t crq;
    hal_ll_base_addr_t cmsk;
    hal_ll_base_addr_t msk1;
    hal_ll_base_addr_t msk2;
    hal_ll_base_addr_t arb1;
    hal_ll_base_addr_t arb2;
    hal_ll_base_addr_t mctl;
    hal_ll_base_addr_t da1;
    hal_ll_base_addr_t da2;
    hal_ll_base_addr_t db1;
    hal_ll_base_addr_t db2;
} hal_ll_can_if;

/*!< @brief CAN HW register structure */
typedef struct
{
    hal_ll_base_addr_t canctl;
    hal_ll_base_addr_t cansts;
    hal_ll_base_addr_t canerr;
    hal_ll_base_addr_t canbit;
    hal_ll_base_addr_t canint;
    hal_ll_base_addr_t cantst;
    hal_ll_base_addr_t canbrpe;
    hal_ll_base_addr_t  res0;
    hal_ll_can_if can_if1;
    hal_ll_base_addr_t  res[13];
    hal_ll_can_if can_if2;
    hal_ll_base_addr_t  res1[21];
    hal_ll_base_addr_t cantxrq[2];
    hal_ll_base_addr_t res2[6];
    hal_ll_base_addr_t cannwda[2];
    hal_ll_base_addr_t res5[6];
    hal_ll_base_addr_t canmsgint[2];
    hal_ll_base_addr_t res4[6];
    hal_ll_base_addr_t canmsgval[2];
} hal_ll_can_base_handle_t;

/*!< @brief CAN hw specific error values */
typedef enum
{
    HAL_LL_CAN_SUCCESS = 0,
    HAL_LL_CAN_WRONG_PINS,
    HAL_LL_CAN_MODULE_ERROR,

    HAL_LL_CAN_ERROR = (-1)
} hal_ll_can_err_t;
// ------------------------------------------------------------------ VARIABLES
/*!< @brief CAN hardware specific info */
static hal_ll_can_hw_specifics_map_t hal_ll_can_hw_specifics_map[] =
{
    #ifdef CAN_MODULE_0
    { HAL_LL_CAN0_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_0 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
    #endif
    #ifdef CAN_MODULE_1
    { HAL_LL_CAN1_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_1 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 }
};


/*!< @brief Global handle variables used in functions */
static volatile hal_ll_can_handle_register_t *low_level_handle;
static volatile hal_ll_can_hw_specifics_map_t *hal_ll_can_hw_specifics_map_local;
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Check if pins are adequate.
 *
 * Checks tx and rx pins the user has passed with pre-defined
 * pins in tx and rx maps. Take into consideration that module
 * index numbers have to be the same for both pins.
 *
 * @param[in]  tx - TX pre-defined pin name.
 * @param[in]  rx - RX pre-defined pin name.
 * @param[in]  *index_list - Index list address
 * @return hal_ll_pin_name_t Module index based on pins.
 *
 * Returns pre-defined module index from pin maps, if pins
 * are adequate.
 */
static hal_ll_pin_name_t hal_ll_can_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                hal_ll_can_pin_id *index_list, hal_ll_can_handle_register_t *handle_map );

/**
 * @brief Sets CAN pin alternate function state.
 *
 * Sets adequate value for alternate function settings.
 * This function must be called if CAN is to work.
 * Based on value of hal_ll_state, alternate functions can be
 * set or cleared.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - Init/De-init
 *
 * @return  None
 */
static void hal_ll_can_alternate_functions_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * CAN TX and RX pins.
 *
 * @param[in]  module_index CAN HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TX and RX map index values
 *                          and module number
 *
 * @return  None
 */
static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list );

/**
 * @brief Get local hardware specific map.
 *
 * Checks handle value and returns address of adequate
 * hal_ll_can_hw_specifics_map array index.
 *
 * @param[in]  handle - Object specific context handler.
 * @return hal_ll_can_hw_specifics_map_t Map address.
 *
 * Returns pre-defined map index address based on handle value,
 * if handle is adequate.
 */
static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
 * @brief Full CAN module initialization procedure.
 *
 * Initializes CAN module on hardware level, based on beforehand
 * set configuration and module handler. Sets control and filter registers.
 * Initializes module clock.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @param[in]  filter_config - CAN filter config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Calculates parameters for desired CAN frequency.
 *
 * Calculates adequate values to be written in CAN_BTR register
 * in order to set appropriate baud rate.
 *
 * @param[in]  map - Object specific context handler.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map );

/**
 * @brief Initialize CAN module on hardware level.
 *
 * Initializes CAN module on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config );

/**
 * @brief Configure CAN filter.
 *
 * Initializes CAN filter on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  filter_config - CAN filter config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Enable clock for CAN module on hardware level.
 *
 * Initializes CAN module clock on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  clock_enable - True(enable clock)/False(disable clock).
 *
 * @return None
 */
static void hal_ll_can_clock_enable( uint8_t module_index, bool clock_enable );

/**
 * @brief Configure CAN message object.
 *
 * Initializes CAN message object on hardware level, based on its number and identifier.
 *
 * @param[in]  base - CAN module base address.
 * @param[in]  message_object_num - Message object number.
 * @return identifier Message/filter ID.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t message_config( hal_ll_base_addr_t *base, uint8_t message_object_num, uint32_t identifier );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_can_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_can_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_can_pin_id index_list[CAN_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_can_check_pins( tx_pin, rx_pin, &index_list, handle_map ))) {
        return HAL_LL_CAN_WRONG_PINS;
    };

    if ( (hal_ll_can_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin) ||
         (hal_ll_can_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin) )
    {
        hal_ll_can_alternate_functions_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], false );

        hal_ll_can_map_pins( pin_check_result, &index_list );

        hal_ll_can_alternate_functions_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_can_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_can_handle;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_init( handle_t *handle, hal_ll_can_config_t *config,
                              hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_handle_register_t *hal_handle = (hal_ll_can_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_can_hw_specifics_map_local->module_index;

    hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_can_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_filter( handle_t *handle, hal_ll_can_config_t *config,
                                    hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    low_level_handle->init_ll_state = false;
    hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    low_level_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_frequency( handle_t *handle, hal_ll_can_config_t *config,
                                       hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    uint32_t original_frequency;
    hal_ll_err_t result;

    low_level_handle->init_ll_state = false;

    original_frequency = hal_ll_can_hw_specifics_map_local->frequency;

    hal_ll_can_hw_specifics_map_local->frequency = config->frequency;
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    // In case the desired frequency setting hasn't been achieved, there's no need to update the map.
    if( HAL_LL_CAN_SUCCESS != result )
        hal_ll_can_hw_specifics_map_local->frequency = original_frequency;

    low_level_handle->init_ll_state = true;

    return result;
}

hal_ll_err_t hal_ll_can_get_frequency( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    return hal_ll_can_hw_specifics_map_local->frequency;
}

hal_ll_err_t hal_ll_can_set_mode( handle_t *handle, hal_ll_can_config_t *config,
                                  hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_err_t result;

    low_level_handle->init_ll_state = false;

    // NOTE: Changing mode won't result in an error, so saving the previous value is not needed.
    hal_ll_can_hw_specifics_map_local->mode = config->mode;
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    low_level_handle->init_ll_state = true;

    return result;
}

hal_ll_err_t hal_ll_can_get_mode( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    return hal_ll_can_hw_specifics_map_local->mode;
}

hal_ll_err_t hal_ll_can_transmit( handle_t *handle, hal_ll_can_transmit_message_struct *transmit_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint32_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Configure transmit message object
    message_config( (hal_ll_base_addr_t *)hal_ll_can_hw_specifics_map_local->base,
                    HAL_LL_CAN_TRANSMIT_MESSAGE_ID, transmit_message->message.std_id );

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if1.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    hal_ll_hw_reg->can_if2.cmsk = HAL_LL_CAN_IF_CMSK_CONTROL_MASK | HAL_LL_CAN_IF_CMSK_MASK_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK |
                                  HAL_LL_CAN_IF_CMSK_DATAA_MASK | HAL_LL_CAN_IF_CMSK_DATAB_MASK;

    hal_ll_hw_reg->can_if2.crq = HAL_LL_CAN_TRANSMIT_MESSAGE_ID;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if2.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    hal_ll_hw_reg->can_if1.da1 = (uint32_t)transmit_message->message.message_data[0];
    hal_ll_hw_reg->can_if1.da1 |= (uint32_t)transmit_message->message.message_data[1] << HAL_LL_CAN_IF_DATA_SHIFT;
    hal_ll_hw_reg->can_if1.da2 = (uint32_t)transmit_message->message.message_data[2];
    hal_ll_hw_reg->can_if1.da2 |= (uint32_t)transmit_message->message.message_data[3] << HAL_LL_CAN_IF_DATA_SHIFT;
    hal_ll_hw_reg->can_if1.db1 = (uint32_t)transmit_message->message.message_data[4];
    hal_ll_hw_reg->can_if1.db1 |= (uint32_t)transmit_message->message.message_data[5] << HAL_LL_CAN_IF_DATA_SHIFT;
    hal_ll_hw_reg->can_if1.db2 = (uint32_t)transmit_message->message.message_data[6];
    hal_ll_hw_reg->can_if1.db2 |= (uint32_t)transmit_message->message.message_data[7] << HAL_LL_CAN_IF_DATA_SHIFT;

    hal_ll_hw_reg->can_if1.cmsk = HAL_LL_CAN_IF_CMSK_WRNRD_MASK | HAL_LL_CAN_IF_CMSK_DATAA_MASK | HAL_LL_CAN_IF_CMSK_DATAB_MASK |
                                  HAL_LL_CAN_IF_CMSK_CONTROL_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK;

    hal_ll_hw_reg->can_if1.arb2 |= (( transmit_message->message.std_id << HAL_LL_CAN_IF_ARB2_ID_SHIFT ) & HAL_LL_CAN_IF_ARB2_ID_MASK ) |
                                   HAL_LL_CAN_IF_ARB2_MSGVAL_MASK | HAL_LL_CAN_IF_ARB2_DIR_MASK;
    hal_ll_hw_reg->can_if1.mctl |= ( transmit_message->message.data_len & HAL_LL_CAN_IF_MCTL_DLC_MASK ) |
                                   HAL_LL_CAN_IF_MCTL_TXRQST_MASK;

    hal_ll_hw_reg->can_if1.crq = HAL_LL_CAN_TRANSMIT_MESSAGE_ID;
    set_reg_bit( &hal_ll_hw_reg->can_if2.cmsk, HAL_LL_CAN_IF_CMSK_TXRQST_BIT );

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;

    // Putting CAN module in initialization mode stops all bus activities.
    set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_INIT_BIT );
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    hal_ll_hw_reg->can_if2.cmsk = HAL_LL_CAN_IF_CMSK_DATAA_MASK | HAL_LL_CAN_IF_CMSK_DATAB_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK |
                                  HAL_LL_CAN_IF_CMSK_MASK_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK;

    // Configure ARB2 register.
    clear_reg_bit( &hal_ll_hw_reg->can_if2.arb2, HAL_LL_CAN_IF_ARB2_XTD_BIT );
    clear_reg_bit( &hal_ll_hw_reg->can_if2.arb2, HAL_LL_CAN_IF_ARB2_DIR_BIT );
    set_reg_bit( &hal_ll_hw_reg->can_if2.arb2, HAL_LL_CAN_IF_ARB2_MSGVAL_BIT );

    // Configure MCTL register.
    set_reg_bit( &hal_ll_hw_reg->can_if2.mctl, HAL_LL_CAN_IF_MCTL_UMASK_BIT );
    clear_reg_bit( &hal_ll_hw_reg->can_if2.mctl, HAL_LL_CAN_IF_MCTL_RMTEN_BIT );
    set_reg_bit( &hal_ll_hw_reg->can_if2.mctl, HAL_LL_CAN_IF_MCTL_EOB_BIT );

    hal_ll_hw_reg->can_if2.crq = receive_message->rx_fifo_number;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if2.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    receive_message->message.std_id = ( hal_ll_hw_reg->can_if1.arb2 & HAL_LL_CAN_IF_ARB2_ID_MASK ) >> HAL_LL_CAN_IF_ARB2_ID_SHIFT;

    // Check for new data.
    if( check_reg_bit( &hal_ll_hw_reg->can_if2.mctl, HAL_LL_CAN_IF_MCTL_NEWDAT_BIT )) {
        receive_message->message.data_len = hal_ll_hw_reg->can_if2.mctl & HAL_LL_CAN_IF_MCTL_DLC_MASK;
        receive_message->message.message_data[0] = hal_ll_hw_reg->can_if2.da1;
        receive_message->message.message_data[1] = hal_ll_hw_reg->can_if2.da1 >> HAL_LL_CAN_IF_DATA_SHIFT;
        receive_message->message.message_data[2] = hal_ll_hw_reg->can_if2.da2;
        receive_message->message.message_data[3] = hal_ll_hw_reg->can_if2.da2 >> HAL_LL_CAN_IF_DATA_SHIFT;
        receive_message->message.message_data[4] = hal_ll_hw_reg->can_if2.db1;
        receive_message->message.message_data[5] = hal_ll_hw_reg->can_if2.db1 >> HAL_LL_CAN_IF_DATA_SHIFT;
        receive_message->message.message_data[6] = hal_ll_hw_reg->can_if2.db2;
        receive_message->message.message_data[7] = hal_ll_hw_reg->can_if2.db2 >> HAL_LL_CAN_IF_DATA_SHIFT;
    }

    // Clear NEWDAT.
    clear_reg_bit( &hal_ll_hw_reg->can_if2.mctl, HAL_LL_CAN_IF_MCTL_NEWDAT_BIT );
    set_reg_bit( &hal_ll_hw_reg->can_if2.cmsk, HAL_LL_CAN_IF_CMSK_NEWDAT_BIT );

    hal_ll_hw_reg->can_if2.crq = receive_message->rx_fifo_number;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if2.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_close( handle_t *handle ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);

    if( low_level_handle->hal_ll_can_handle != NULL ) {
        hal_ll_can_clock_enable(hal_ll_can_hw_specifics_map_local->module_index, true);
        hal_ll_can_alternate_functions_set_state( hal_ll_can_hw_specifics_map_local, false );

        hal_ll_can_clock_enable(hal_ll_can_hw_specifics_map_local->module_index, false);

        hal_ll_can_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.tx_pin.pin_af = 0;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin.pin_af = 0;

        hal_ll_can_hw_specifics_map_local->frequency = 500000UL;

        low_level_handle->hal_ll_can_handle = NULL;
        low_level_handle->hal_drv_can_handle = NULL;

        low_level_handle->init_ll_state = false;

        return HAL_LL_CAN_SUCCESS;
    } else
        return HAL_LL_CAN_ERROR;
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_can_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                hal_ll_can_pin_id *index_list, hal_ll_can_handle_register_t *handle_map ) {
    static const uint16_t tx_map_size = ( sizeof( hal_ll_can_tx_map ) / sizeof( hal_ll_can_pin_map_t ) );
    static const uint16_t rx_map_size = ( sizeof( hal_ll_can_rx_map ) / sizeof( hal_ll_can_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t tx_index;
    uint16_t rx_index;

    if ( (HAL_LL_PIN_NC == tx_pin) || (HAL_LL_PIN_NC == rx_pin) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ )
    {
        if ( hal_ll_can_tx_map[ tx_index ].pin == tx_pin )
        {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ )
            {
                if ( hal_ll_can_rx_map[ rx_index ].pin == rx_pin )
                {
                    if ( hal_ll_can_tx_map[ tx_index ].base == hal_ll_can_rx_map[ rx_index ].base ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_can_tx_map[ tx_index ].module_index;

                        // Map pin names
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_can_handle ) {
                            return hal_ll_module_id;
                        } else if ( CAN_MODULE_COUNT == ++index_counter ) {
                            return --index_counter;
                        }
                    }
                }
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_can_alternate_functions_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( (map->pins.tx_pin.pin_name != HAL_LL_PIN_NC) && map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) {
        module.pins[0] = VALUE( map->pins.tx_pin.pin_name, map->pins.tx_pin.pin_af );
        module.pins[1] = VALUE( map->pins.rx_pin.pin_name, map->pins.rx_pin.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] =  GPIO_CFG_ALT_FUNCTION | GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[1] =  GPIO_CFG_ALT_FUNCTION | GPIO_CFG_DIGITAL_INPUT;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list ) {
    // Map new pins
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_can_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_can_rx_map[ index_list[module_index].pin_rx ].pin;
    // TX and RX could have different alternate function settings, hence save both AF values
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_can_tx_map[ index_list[module_index].pin_tx ].af;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_can_rx_map[ index_list[module_index].pin_rx ].af;
}

static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_can_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_can_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_can_get_base_from_hal_handle == hal_ll_can_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_can_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_can_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_can_clock_enable( uint8_t module_index, bool clock_enable ) {

    switch( module_index ) {
        #ifdef CAN_MODULE_0
        case ( hal_ll_can_module_num( CAN_MODULE_0 ) ):
            if( true == clock_enable )
                set_reg_bit( _SYSCTL_RCGCCAN, HAL_LL_CAN1_CLOCK_ENABLE );
            else
                clear_reg_bit( _SYSCTL_RCGCCAN, HAL_LL_CAN1_CLOCK_ENABLE );
            break;
        #endif
        #ifdef CAN_MODULE_1
        case ( hal_ll_can_module_num( CAN_MODULE_1 ) ):
            if( true == clock_enable )
                set_reg_bit( _SYSCTL_RCGCCAN, HAL_LL_CAN2_CLOCK_ENABLE );
            else
                clear_reg_bit( _SYSCTL_RCGCCAN, HAL_LL_CAN2_CLOCK_ENABLE );
            break;
        #endif

        default:
            break;
    }
}

static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t prescaler = 0, tseg1 = 0, tseg2 = 0, temp = 0;
    float time_quanta = 0.0, bit_time = 0.0, num_of_tq = 0.0;
    uint32_t baud_rate = 0, can_clock = 0;
    uint8_t sjw = 0;

    baud_rate = map->frequency;

    can_clock = Get_Fosc_kHz() * 1000; // CAN clock in Hz

    /*
     * Description: This code snippet calculates the optimal settings for configuring
     * the CAN bus baud rate on Tiva microcontrollers, based on the provided parameters.
     *
     * Initial parameters:
     * - can_clock: CAN source clock frequency in Hz.
     * - baud_rate: Desired CAN bus baud rate.
     *
     * Calculated parameters:
     * - prescaler: The prescaler value to achieve the desired baud rate.
     * - tseg1, tseg2: Time segment values for configuring the CAN bus.
     *
     * Formulas used:
     * - time_quanta = 1 / can_clock
     * - bit_time = 1 / baud_rate
     * - num_of_tq = bit_time / time_quanta (number of time quanta)
     * - (sjw + tseg1) / (sjw + tseg1 + tseg2) = 87.5% (optimal sampling for CAN)
     * - baud_rate = can_clock / (prescaler * (tseg1 + tseg2 + 1)) (from Tiva Reference manuals)
     *
     * Note: sjw (synchronization jump width) is fixed to 1, the preferred value, but can range from 1 to 4.
     */

    sjw = HAL_LL_CAN_SJW_CONST_VALUE;

    bit_time = (float) 1 / baud_rate;

    set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_CCE_BIT );
    for( prescaler = 1; prescaler <= HAL_LL_CAN_PRESCALER_MAX_VAL; prescaler++ ) {
        time_quanta = (float) prescaler / can_clock;
        num_of_tq = (float)bit_time / (float)time_quanta;
        tseg1 = HAL_LL_CAN_BIT_RATE_SAMPLE_POINT * num_of_tq - sjw;
        tseg2 = num_of_tq - tseg1 - sjw;

        // Time segment 1 can be anywhere between 1 and 16, while the value of time segment 2 goes from 1 to 8.
        if( ( HAL_LL_CAN_TSEG1_MAX_VAL < tseg1 ) || ( HAL_LL_CAN_TSEG2_MAX_VAL < tseg2 ) || !tseg1 || !tseg2 ) continue;

        temp = prescaler * ( tseg1 + tseg2 + 1 );
        uint32_t actual_baud_rate = can_clock / temp;

        if( actual_baud_rate == baud_rate ) {
            // Exact match found
            uint32_t sjw_val = ((uint32_t)(sjw - 1)) << HAL_LL_CAN_CANBIT_SJW_SHIFT;
            uint32_t tseg1_val = ((uint32_t)(tseg1 - 1)) << HAL_LL_CAN_CANBIT_TSEG1_SHIFT;
            uint32_t tseg2_val = ((uint32_t)(tseg2 - 1)) << HAL_LL_CAN_CANBIT_TSEG2_SHIFT;
            uint32_t prescaler_val_low = HAL_LL_CAN_PRESCALER_BITS_5_0 & (prescaler - 1);
            uint32_t prescaler_val_high = (HAL_LL_CAN_PRESCALER_BITS_10_6 & (prescaler - 1)) >> HAL_LL_CAN_CANBRPE_PRESCALER_SHIFT;
            hal_ll_hw_reg->canbit = sjw_val | tseg1_val | tseg2_val | prescaler_val_low;
            hal_ll_hw_reg->canbrpe = prescaler_val_high;
            clear_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_CCE_BIT );

            return HAL_LL_CAN_SUCCESS;
        }

        /*
         * Note: Setting parameters that result in a baud rate that differs from the desired value is not acceptable.
         *       If two devices communicate over CAN, their baud rates need to be exactly the same.
         */
    }

    // If this point was reached, baud rate wasn't set to the desired value and error is returned.
    clear_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_CCE_BIT );

    return HAL_LL_CAN_ERROR;
}

static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Start SW initialization.
    set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_INIT_BIT );

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if1.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    hal_ll_hw_reg->can_if1.cmsk = HAL_LL_CAN_IF_CMSK_WRNRD_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK;

    hal_ll_hw_reg->can_if1.arb1 = HAL_LL_CAN_REG_CLEAR;
    hal_ll_hw_reg->can_if1.arb2 = HAL_LL_CAN_REG_CLEAR;
    hal_ll_hw_reg->can_if1.mctl = HAL_LL_CAN_REG_CLEAR;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Loop through to program all 32 message objects.
    for( uint8_t i = 1; i <= HAL_LL_CAN_MAX_MNUM; i++ ) {
        hal_ll_hw_reg->can_if1.crq = i;
        // Wait for BUSY bit to clear.
        while( check_reg_bit( &hal_ll_hw_reg->can_if1.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
            if( !timeout-- )
                return HAL_LL_CAN_ERROR;
    }

    hal_ll_hw_reg->can_if1.cmsk = HAL_LL_CAN_IF_CMSK_CLRINTPND_MASK | HAL_LL_CAN_IF_CMSK_NEWDAT_MASK;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Loop through to program all 32 message objects.
    for( uint8_t i = 1; i < HAL_LL_CAN_MAX_MNUM; i++ ) {
        hal_ll_hw_reg->can_if1.crq = i;
        // Wait for BUSY bit to clear.
        while( check_reg_bit( &hal_ll_hw_reg->can_if1.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
            if( !timeout-- )
                return HAL_LL_CAN_ERROR;
    }

    // Read CANSTS register to clear message interrupts.
    (void)hal_ll_hw_reg->cansts;

    if( HAL_LL_CAN_ERROR == hal_ll_can_bit_timing( map ))
        return HAL_LL_CAN_ERROR;

    // Disable auto retransmission.
    set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_DAR_BIT );

    // Start SW initialization.
    set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_INIT_BIT );

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Mask configuration.
    hal_ll_hw_reg->can_if2.cmsk |= HAL_LL_CAN_IF_CMSK_ARB_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK |
                                   HAL_LL_CAN_IF_CMSK_MASK_MASK | HAL_LL_CAN_IF_CMSK_DATAA_MASK | HAL_LL_CAN_IF_CMSK_DATAB_MASK;

    hal_ll_hw_reg->can_if2.crq = filter_config->can_filter_fifo;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if2.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    hal_ll_hw_reg->can_if1.cmsk |= HAL_LL_CAN_IF_CMSK_WRNRD_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK | HAL_LL_CAN_IF_CMSK_MASK_MASK;

    hal_ll_hw_reg->can_if1.msk1 = HAL_LL_CAN_REG_CLEAR;

    if ( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_11 ) {
        // Extended filter mask ID
        hal_ll_hw_reg->can_if1.msk1 = filter_config->can_filter_mask_id_low;
        hal_ll_hw_reg->can_if1.msk2 = filter_config->can_filter_mask_id_high;
    } else {
        // Standard filter mask ID
        hal_ll_hw_reg->can_if1.msk2 = ( filter_config->can_filter_mask_id_low & HAL_LL_CAN_SID_MASK ) << HAL_LL_CAN_IF_MSK2_ID_SHIFT;
    }

    // Use acceptance mask
    set_reg_bit( &hal_ll_hw_reg->can_if1.mctl, HAL_LL_CAN_IF_MCTL_UMASK_BIT );
    // End of mask configuration.

    // Filter configuration.
    hal_ll_hw_reg->can_if2.cmsk |= HAL_LL_CAN_IF_CMSK_MASK_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK |
                                   HAL_LL_CAN_IF_CMSK_ARB_MASK | HAL_LL_CAN_IF_CMSK_DATAA_MASK |
                                   HAL_LL_CAN_IF_CMSK_DATAB_MASK;

    hal_ll_hw_reg->can_if2.crq = filter_config->can_filter_fifo;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &hal_ll_hw_reg->can_if2.crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    hal_ll_hw_reg->can_if1.cmsk = HAL_LL_CAN_IF_CMSK_WRNRD_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK;

    if ( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_11 ) {
        // Extended filter ID
        hal_ll_hw_reg->can_if1.arb1 |= filter_config->can_filter_id_low;
        hal_ll_hw_reg->can_if1.arb2 |= filter_config->can_filter_id_high;
    } else {
        // Standard filter ID
        hal_ll_hw_reg->can_if1.arb2 |= ( filter_config->can_filter_id_low & HAL_LL_CAN_SID_MASK ) << HAL_LL_CAN_IF_ARB2_ID_SHIFT;
    }

    set_reg_bit( &hal_ll_hw_reg->can_if1.arb2, HAL_LL_CAN_IF_ARB2_MSGVAL_BIT );

    hal_ll_hw_reg->can_if1.crq = filter_config->can_filter_fifo;
    // End of filter configuration.

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t message_config( hal_ll_base_addr_t *base, uint8_t message_object_num, uint32_t identifier ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(base);
    volatile hal_ll_can_if *can_interface;
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    //  One interface is used to transmit and the other to receive data.
    if ( HAL_LL_CAN_TRANSMIT_MESSAGE_ID == message_object_num ) {
        can_interface = &hal_ll_hw_reg->can_if1;
    } else {
        can_interface = &hal_ll_hw_reg->can_if2;
    }

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &can_interface->crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    can_interface->cmsk |= HAL_LL_CAN_IF_CMSK_WRNRD_MASK | HAL_LL_CAN_IF_CMSK_CONTROL_MASK | HAL_LL_CAN_IF_CMSK_ARB_MASK;

    can_interface->crq = message_object_num;

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Wait for BUSY bit to clear.
    while( check_reg_bit( &can_interface->crq, HAL_LL_CAN_IF_CRQ_BUSY_BIT ))
        if( !timeout-- )
            return HAL_LL_CAN_ERROR;

    if( HAL_LL_CAN_EID_BITS_28_11 & identifier )
        // Extended ID
        set_reg_bit( &can_interface->arb2, HAL_LL_CAN_IF_ARB2_XTD_BIT );
    else
        // Standard ID
        clear_reg_bit( &can_interface->arb2, HAL_LL_CAN_IF_ARB2_XTD_BIT );

    set_reg_bit( &can_interface->arb2, HAL_LL_CAN_IF_ARB2_MSGVAL_BIT );

    if( HAL_LL_CAN_TRANSMIT_MESSAGE_ID == message_object_num ) {
        // Transmit message object
        set_reg_bit( &can_interface->arb2, HAL_LL_CAN_IF_ARB2_DIR_BIT ); // Set direction to Transmit
    } else {
        // Receive message object
        clear_reg_bit( &can_interface->arb2, HAL_LL_CAN_IF_ARB2_DIR_BIT ); // Set direction to Receive
    }

    can_interface->crq = message_object_num;

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    hal_ll_err_t result = HAL_LL_CAN_SUCCESS;

    // Enable clock for CAN.
    hal_ll_can_clock_enable( map->module_index, true );
    /*
     * According to the Datasheet:
     * "There must be a delay of 3 system clocks after the CAN module clock is enabled before
     * any CAN module registers are accessed."
     */
    assembly( nop );
    assembly( nop );
    assembly( nop );

    if( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    // Configure receive message object
    if( HAL_LL_CAN_ERROR == message_config( (hal_ll_base_addr_t *)map->base, filter_config->can_filter_fifo, filter_config->can_filter_id ))
        return HAL_LL_CAN_ERROR;

    if( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( map, filter_config ))
        return HAL_LL_CAN_ERROR;

    if( HAL_LL_CAN_MODE_LOOPBACK == config->mode ) {
        set_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_TEST_BIT );
        set_reg_bit( &hal_ll_hw_reg->cantst, HAL_LL_CAN_CANTST_LBACK_BIT );
    }

    // Leave SW initialization.
    clear_reg_bit( &hal_ll_hw_reg->canctl, HAL_LL_CAN_CANCTL_INIT_BIT );

    return result;
}
// ------------------------------------------------------------------------- END
