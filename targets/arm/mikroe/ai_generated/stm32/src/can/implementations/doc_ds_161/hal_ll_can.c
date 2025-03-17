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
 * @file  hal_ll_can.c
 * @brief CAN HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rcc.h"
#include "hal_ll_can.h"
#include "hal_ll_gpio.h"
#include "hal_ll_can_pin_map.h"

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
/*!< @brief Helper macro for configuring the filter */
#define hal_ll_can_filter_configure_32(mask_32) ((mask_32 & 0x07FF) << 21U | (mask_32 & 0x1FFFF800) >> 8U)
#define hal_ll_can_filter_configure_16(mask_16) ((((uint32_t)(mask_16 & 0x07FF) << 5U) | ((uint32_t)(mask_16 & 0x3800) >> 11U)))
#define hal_ll_can_filter_get_format_32(mask_32) (((mask_32 & 0x1FFFF800))?1:0)
#define hal_ll_can_filter_get_format_16(mask) ((mask & 0x1C00)?1:0)
/*!< @brief Helper macro for handling the received message */
#define hal_ll_can_message_received(fifo,mask) ((fifo & mask))
#define hal_ll_can_get_rx_data(byte,data_register,offset) ((uint8_t)(((byte) & data_register) >> offset))
#define hal_ll_can_get_rx_id(id_register,mask,offset) ((id_register & mask ) >> offset)
#define hal_ll_can_get_rx_eid(id_register,mask,offset) ((id_register & mask ) << offset)
/*!< @brief Helper macros for bit rate calculation */
#define hal_ll_can_check_time_segments(tseg1,tseg2) ((16 < tseg1) || (8 < tseg2) || (0 == tseg1) || (0 == tseg2))
#define hal_ll_can_get_btr_element_mask(element, offset) (((uint32_t)(element - 1)) << offset)

/*!< @brief GPIO congiguration constants */
#ifdef GPIO_CFG_SPEED_VERY_HIGH
#define HAL_LL_CAN_AF_CONFIG (GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_SPEED_VERY_HIGH | GPIO_CFG_OTYPE_PP | GPIO_CFG_PULL_UP)
#else
#define HAL_LL_CAN_AF_CONFIG (GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_SPEED_HIGH | GPIO_CFG_OTYPE_PP | GPIO_CFG_PULL_UP)
#endif
/*!< @brief CAN clock enable bits */
#define HAL_LL_CAN1_CLOCK_ENABLE            (25)
/*!< @brief CAN baudrate constants and register bits and masks */
#define HAL_LL_CAN_BTR_PRESCALER_OFFSET     (0)
#define HAL_LL_CAN_BTR_SJW_VALUE            (1)
#define HAL_LL_CAN_BTR_TSEG1_OFFSET         (16)
#define HAL_LL_CAN_BTR_TSEG2_OFFSET         (20)
#define HAL_LL_CAN_BTR_SJW_OFFSET           (24)
#define HAL_LL_CAN_BTR_LBKM_BIT             (30)
#define HAL_LL_CAN_BTR_SILM_BIT             (31)
#define HAL_LL_CAN_BTR_MAX_PRESCALER_VALUE  (1024)
#define HAL_LL_CAN_BTR_REGISTER_MASK        (0xC37F03FFUL)
/*!< @brief CAN control and status register bits */
#define HAL_LL_CAN_MCR_INRQ_BIT             (0)
#define HAL_LL_CAN_MSR_INAK_BIT             (0)
#define HAL_LL_CAN_MCR_SLEEP_BIT            (1)
#define HAL_LL_CAN_MSR_SLAK_BIT             (1)
/*!< @brief CAN filter constants and register bits and masks */
#define HAL_LL_CAN_FMR_FINIT_BIT            (0)
#define HAL_LL_CAN_FIR_RTR_32_BIT           (1)
#define HAL_LL_CAN_FIR_EID_32_BIT           (2)
#define HAL_LL_CAN_FIR_EID_16_LOW_BIT       (3)
#define HAL_LL_CAN_FIR_RTR_16_LOW_BIT       (4)
#define HAL_LL_CAN_SINGLE_CORE_FILTER_LIMIT (27)
#define HAL_LL_CAN_FIR_EID_16_HIGH_BIT      (19)
#define HAL_LL_CAN_FIR_RTR_16_HIGH_BIT      (20)
#define HAL_LL_CAN_FILTER_NUMBER            (27)
/*!< @brief CAN transmit constants, registers bits and masks */
#define HAL_LL_CAN_TIR_TXRQ_BIT             (0)
#define HAL_LL_CAN_TIR_RTR_BIT              (1)
#define HAL_LL_CAN_TIR_IDE_BIT              (2)
#define HAL_LL_CAN_TRANSMIT_MAILBOX_COUNT   (3)
#define HAL_LL_CAN_TIR_EID_SHIFT            (8)
#define HAL_LL_CAN_TIR_STID_SHIFT           (21)
#define HAL_LL_CAN_TSR_CODE_SHIFT           (24)
#define HAL_LL_CAN_TSR_CODE_MASK            (0x03000000UL)
/*!< @brief CAN receive register bits and masks */
#define HAL_LL_CAN_RF0R_RFOM0_BIT           (5)
#define HAL_LL_CAN_RF1R_RFOM1_BIT           (5)
#define HAL_LL_CAN_RF0R_FMP0_MASK           (0x00000003UL)
#define HAL_LL_CAN_RF1R_FMP1_MASK           (0x00000003UL)
/*!< @brief CAN receive FIFO constants, register bits and masks */
#define HAL_LL_CAN_RIR_RTR_BIT              (1)
#define HAL_LL_CAN_RIR_IDE_BIT              (2)
#define HAL_LL_CAN_RIR_EXID_SHIFT           (8)
#define HAL_LL_CAN_RIR_STID_SHIFT           (21)
#define HAL_LL_CAN_RDTR_DLC_MASK            (0x0000000FUL)
#define HAL_LL_CAN_RIR_STID_MASK            (0xFFE00000UL)
#define HAL_LL_CAN_RIR_EXID_MASK            (0x001FFFF8UL)
/*!< @brief Helper macro for defining temout value */
#define HAL_LL_CAN_TIMEOUT_VALUE            (10000UL)
/*!< @brief Byte offset macros */
#define HAL_LL_CAN_BYTE_OFFSET_0            (0U)
#define HAL_LL_CAN_BYTE_OFFSET_1            (8U)
#define HAL_LL_CAN_BYTE_OFFSET_2            (16U)
#define HAL_LL_CAN_BYTE_OFFSET_3            (24U)
#define HAL_LL_CAN_BYTE_FIRST               (0x000000FFUL)
#define HAL_LL_CAN_BYTE_SECOND              (0x0000FF00UL)
#define HAL_LL_CAN_BYTE_THIRD               (0x00FF0000UL)
#define HAL_LL_CAN_BYTE_FOURTH              (0xFF000000UL)

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

/* @brief CAN TxMailBox structure */
typedef struct
{
  hal_ll_base_addr_t tir;     /*!< CAN TX mailbox identifier register */
  hal_ll_base_addr_t tdtr;    /*!< CAN mailbox data length control and time stamp register */
  hal_ll_base_addr_t tdlr;    /*!< CAN mailbox data low register */
  hal_ll_base_addr_t tdhr;    /*!< CAN mailbox data high register */
} hal_ll_can_txmailbox_t;

/* @brief Controller Area Network FIFOMailBox structure */
typedef struct
{
  hal_ll_base_addr_t rir;     /*!< CAN receive FIFO mailbox identifier register */
  hal_ll_base_addr_t rdtr;    /*!< CAN receive FIFO mailbox data length control and time stamp register */
  hal_ll_base_addr_t rdlr;    /*!< CAN receive FIFO mailbox data low register */
  hal_ll_base_addr_t rdhr;    /*!< CAN receive FIFO mailbox data high register */
} hal_ll_can_fifomailbox_t;

/* @brief Controller Area Network FilterRegister structure */
typedef struct
{
  hal_ll_base_addr_t fr1;     /*!< CAN Filter bank register 1 */
  hal_ll_base_addr_t fr2;     /*!< CAN Filter bank register 2 */
} hal_ll_can_filter_reg_t;

/*!< @brief CAN HW register structure */
typedef struct
{
    hal_ll_base_addr_t mcr;   /*CAN master control register*/
    hal_ll_base_addr_t msr;   /*CAN master status register*/
    hal_ll_base_addr_t tsr;   /*CAN transmit status register*/
    hal_ll_base_addr_t rf0r;   /*CAN receive FIFO 0 register*/
    hal_ll_base_addr_t rf1r;   /*CAN receive FIFO 1 register*/
    hal_ll_base_addr_t ier;   /*CAN interrupt enable register*/
    hal_ll_base_addr_t esr;   /*CAN error status register*/
    hal_ll_base_addr_t btr;   /*CAN bit timing register*/
    hal_ll_base_addr_t __unused1[88];
    hal_ll_can_txmailbox_t tx_mailbox[3];
    hal_ll_can_fifomailbox_t fifo_mailbox[2];
    hal_ll_base_addr_t __unused2[12];
    hal_ll_base_addr_t fmr;   /*CAN filter master register*/
    hal_ll_base_addr_t fm1r;   /*CAN filter mode register*/
    hal_ll_base_addr_t __unused3[1];
    hal_ll_base_addr_t fs1r;   /*CAN filter scale register*/
    hal_ll_base_addr_t __unused4[1];
    hal_ll_base_addr_t ffa1r;   /*CAN filter FIFO assignment register*/
    hal_ll_base_addr_t __unused5[1];
    hal_ll_base_addr_t fa1r;   /*CAN filter activation register*/
    hal_ll_base_addr_t __unused6[8];
    hal_ll_can_filter_reg_t filter_reg[28];
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
 * @param[in]  tx_pin - TX pre-defined pin name.
 * @param[in]  rx_pin - RX pre-defined pin name.
 * @param[in]  *index_list - Index list address
 * @param[in]  *handle_map - HAL low level context object handle.
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
 * @param[in]  default_config - Defines if we should check if filter is assignable.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config );

/**
 * @brief Enable clock for CAN module on hardware level.
 *
 * Initializes CAN module clock on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  module_index - Object specific context handler.
 * @param[in]  clock_enable - True(enable clock)/False(disable clock).
 *
 * @return None
 */
static void hal_ll_can_clock_enable( uint8_t module_index, bool clock_enable );

/**
 * @brief Set operation mode.
 *
 * Sets an operation mode requested by user.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_can_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_can_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_can_pin_id index_list[CAN_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid.
    if (( pin_check_result = hal_ll_can_check_pins( tx_pin, rx_pin, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_CAN_WRONG_PINS;
    };

    if (( hal_ll_can_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin ) ||
        ( hal_ll_can_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin ))
    {
        // Clear previous alternate function for chosen CAN pins.
        hal_ll_can_alternate_functions_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], false );

        hal_ll_can_map_pins( pin_check_result, &index_list );

        // Set adequate CAN alternate function for chosen CAN pins.
        hal_ll_can_alternate_functions_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = ( handle_t * )&hal_ll_can_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_can_handle = ( handle_t * )&hal_ll_module_state[pin_check_result].hal_ll_can_handle;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_init( handle_t *handle, hal_ll_can_config_t *config,
                              hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_handle_register_t *hal_handle = ( hal_ll_can_handle_register_t * )*handle;
    uint8_t pin_check_result = hal_ll_can_hw_specifics_map_local->module_index;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config ))
        return HAL_LL_CAN_ERROR;

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = ( handle_t * )&hal_ll_can_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_filter( handle_t *handle, hal_ll_can_config_t *config,
                                    hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    low_level_handle->init_ll_state = false;
    if ( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_local, filter_config, false ))
        return HAL_LL_CAN_ERROR;

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
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint8_t tx_mailbox_num;
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    tx_mailbox_num = ( hal_ll_hw_reg->tsr & HAL_LL_CAN_TSR_CODE_MASK ) >> HAL_LL_CAN_TSR_CODE_SHIFT;

    hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir = hal_ll_can_filter_configure_32( transmit_message->message.id );

    // Set an appropriate frame format of the message.
    if( HAL_LL_CAN_FRAME_FORMAT_STANDARD_11BITS == transmit_message->message.frame_format )
        clear_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_IDE_BIT );
    else
        set_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_IDE_BIT );

    // Set an appropriate frame type of the message.
    if( HAL_LL_CAN_FRAME_TYPE_DATA == transmit_message->message.frame_type )
        clear_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_RTR_BIT );
    else
        set_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_RTR_BIT );

    hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tdtr = transmit_message->message.data_len;

    hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tdlr = (( uint32_t )transmit_message->message.message_data[0] ) |
                                                     (( uint32_t )transmit_message->message.message_data[1] << HAL_LL_CAN_BYTE_OFFSET_1 ) |
                                                     (( uint32_t )transmit_message->message.message_data[2] << HAL_LL_CAN_BYTE_OFFSET_2 ) |
                                                     (( uint32_t )transmit_message->message.message_data[3] << HAL_LL_CAN_BYTE_OFFSET_3 );

    hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tdhr = (( uint32_t )transmit_message->message.message_data[4] ) |
                                                     (( uint32_t )transmit_message->message.message_data[5] << HAL_LL_CAN_BYTE_OFFSET_1 ) |
                                                     (( uint32_t )transmit_message->message.message_data[6] << HAL_LL_CAN_BYTE_OFFSET_2 ) |
                                                     (( uint32_t )transmit_message->message.message_data[7] << HAL_LL_CAN_BYTE_OFFSET_3 );

    // Transmit mailbox request.
    set_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_TXRQ_BIT );
    // Waiting for message to be received by receiver.
    while ( check_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_TXRQ_BIT )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint8_t tx_mailbox_num;

    // Stop transmitting any messages.
    for ( tx_mailbox_num = 0; tx_mailbox_num < HAL_LL_CAN_TRANSMIT_MAILBOX_COUNT; tx_mailbox_num++ ) {
        if ( check_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_TXRQ_BIT ))
            clear_reg_bit( &hal_ll_hw_reg->tx_mailbox[tx_mailbox_num].tir, HAL_LL_CAN_TIR_TXRQ_BIT );
    }
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint8_t rx_fifo_num = receive_message->rx_fifo_number;
    uint32_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    if ( HAL_LL_CAN_FILTER_FIFO0 == rx_fifo_num ) {
        while( !( hal_ll_can_message_received( hal_ll_hw_reg->rf0r, HAL_LL_CAN_RF0R_FMP0_MASK ))) {
            if( 0 == timeout-- )
                return HAL_LL_CAN_ERROR;
        }
    } else if ( HAL_LL_CAN_FILTER_FIFO1 == rx_fifo_num ) {
        while ( !( hal_ll_can_message_received( hal_ll_hw_reg->rf1r, HAL_LL_CAN_RF1R_FMP1_MASK ))) {
            if( 0 == timeout-- )
                return HAL_LL_CAN_ERROR;
        }
    } else
        // STM32 MCUs have only 2 RX FIFOs.
        return HAL_LL_CAN_ERROR;

    // Get parameters.
    receive_message->message.data_len = hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdtr & HAL_LL_CAN_RDTR_DLC_MASK;
    receive_message->message.frame_type = check_reg_bit( &hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rir, HAL_LL_CAN_RIR_RTR_BIT );
    receive_message->message.frame_format = check_reg_bit( &hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rir, HAL_LL_CAN_RIR_IDE_BIT );

    receive_message->message.std_id = hal_ll_can_get_rx_id( hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rir, HAL_LL_CAN_RIR_STID_MASK, HAL_LL_CAN_RIR_STID_SHIFT );
    if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == receive_message->message.frame_format )
        receive_message->message.id |= hal_ll_can_get_rx_eid( hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rir, HAL_LL_CAN_RIR_EXID_MASK, HAL_LL_CAN_RIR_EXID_SHIFT );

    // Get all data bytes.
    receive_message->message.message_data[0] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FIRST, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdlr, HAL_LL_CAN_BYTE_OFFSET_0 );
    receive_message->message.message_data[1] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_SECOND, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdlr, HAL_LL_CAN_BYTE_OFFSET_1 );
    receive_message->message.message_data[2] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_THIRD, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdlr, HAL_LL_CAN_BYTE_OFFSET_2 );
    receive_message->message.message_data[3] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FOURTH, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdlr, HAL_LL_CAN_BYTE_OFFSET_3 );
    receive_message->message.message_data[4] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FIRST, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdhr, HAL_LL_CAN_BYTE_OFFSET_0 );
    receive_message->message.message_data[5] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_SECOND, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdhr, HAL_LL_CAN_BYTE_OFFSET_1 );
    receive_message->message.message_data[6] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_THIRD, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdhr, HAL_LL_CAN_BYTE_OFFSET_2 );
    receive_message->message.message_data[7] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FOURTH, hal_ll_hw_reg->fifo_mailbox[rx_fifo_num].rdhr, HAL_LL_CAN_BYTE_OFFSET_3 );

    // Release RX FIFO.
    if ( HAL_LL_CAN_FILTER_FIFO0 == rx_fifo_num )
        set_reg_bit( &hal_ll_hw_reg->rf0r, HAL_LL_CAN_RF0R_RFOM0_BIT );
    else
        set_reg_bit( &hal_ll_hw_reg->rf1r, HAL_LL_CAN_RF1R_RFOM1_BIT );

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
                        // Get module number.
                        hal_ll_module_id = hal_ll_can_tx_map[ tx_index ].module_index;

                        // Map pin names.
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken.
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

        module.configs[0] = HAL_LL_CAN_AF_CONFIG;
        module.configs[1] = HAL_LL_CAN_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        /* STM32F1xx specific. */
        module.gpio_remap = map->pins.tx_pin.pin_af;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list ) {
    // Map new pins.
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_can_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_can_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX could have different alternate function settings, hence save both AF values.
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_can_tx_map[index_list[module_index].pin_tx].af;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_can_rx_map[index_list[module_index].pin_rx].af;
}

static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_can_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_can_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if (hal_ll_can_get_base_from_hal_handle == hal_ll_can_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_can_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_can_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_can_clock_enable( uint8_t module_index, bool clock_enable ) {
    switch( module_index ) {
        #ifdef CAN_MODULE_1
        case ( hal_ll_can_module_num( CAN_MODULE_1 )):
            #ifdef _RCC_APB1ENR1
            if( true == clock_enable )
                set_reg_bit( _RCC_APB1ENR1, HAL_LL_CAN1_CLOCK_ENABLE );
            else
                clear_reg_bit( _RCC_APB1ENR1, HAL_LL_CAN1_CLOCK_ENABLE );
            break;
            #endif
        #endif
        default:
            break;
    }
}

static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    rcc_clocks_t rcc_clocks;
    uint16_t prescaler, temp;
    double time_quanta, bit_time, num_of_tq;
    uint8_t sjw, tseg1, tseg2;
    uint32_t baud_rate, can_clock;

    baud_rate = map->frequency;

    RCC_GetClocksFrequency( &rcc_clocks );
    can_clock = rcc_clocks.pclk1;

    /*
     * Description: This code snippet calculates the optimal settings for configuring
     * the CAN bus baud rate on STM32 microcontrollers, based on the provided parameters.
     *
     * Initial parameters:
     * - can_clock: CAN source clock frequency (APB1) in Hz.
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
     * - baud_rate = can_clock / (prescaler * (tseg1 + tseg2 + 1)) (from STM32 Reference manuals)
     *
     * Note: sjw (synchronization jump width) is fixed to 1, the preferred value, but can range from 1 to 4.
     */

    sjw = HAL_LL_CAN_BTR_SJW_VALUE;

    bit_time = (double) 1 / baud_rate;

    for( prescaler = 1; prescaler <= HAL_LL_CAN_BTR_MAX_PRESCALER_VALUE; prescaler++ ) {
        time_quanta = (double) prescaler / can_clock;
        num_of_tq = bit_time / time_quanta;
        tseg1 = 0.875 * num_of_tq - sjw;
        tseg2 = num_of_tq - tseg1 - sjw;

        // Time segment 1 can be anywhere between 1 and 16, while the value of time segment 2 goes from 1 to 8.
        if ( hal_ll_can_check_time_segments( tseg1, tseg2 )) continue;

        temp = prescaler * ( tseg1 + tseg2 + 1 );
        uint32_t actual_baud_rate = can_clock / temp;

        if( actual_baud_rate == baud_rate ) {
            // Exact match found.
            uint32_t sjw_val = hal_ll_can_get_btr_element_mask( sjw, HAL_LL_CAN_BTR_SJW_OFFSET );
            uint32_t tseg1_val = hal_ll_can_get_btr_element_mask( tseg1, HAL_LL_CAN_BTR_TSEG1_OFFSET );
            uint32_t tseg2_val = hal_ll_can_get_btr_element_mask( tseg2, HAL_LL_CAN_BTR_TSEG2_OFFSET );
            uint32_t prescaler_val = hal_ll_can_get_btr_element_mask( prescaler, HAL_LL_CAN_BTR_PRESCALER_OFFSET );;

            hal_ll_hw_reg->btr |= sjw_val | tseg1_val | tseg2_val | prescaler_val;
            return HAL_LL_CAN_SUCCESS;
        }

        /*
         * Note: Setting parameters that result in a baud rate that differs from the desired value is not acceptable.
         *       If two devices communicate over CAN, their baud rates need to be exactly the same.
         */
    }

    // If this point was reached, baud rate wasn't set to the desired value and error is returned.
    return HAL_LL_CAN_ERROR;
}

static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    clear_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_LBKM_BIT );
    clear_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_SILM_BIT );

    switch ( config->mode ) {
        case HAL_LL_CAN_MODE_NORMAL:
            break;
        case HAL_LL_CAN_MODE_LOOPBACK:
            set_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_LBKM_BIT );
            break;
        case HAL_LL_CAN_MODE_SILENT:
            set_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_SILM_BIT );
            break;
        case HAL_LL_CAN_MODE_LOOPBACK_SILENT:
            set_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_LBKM_BIT );
            set_reg_bit( &hal_ll_hw_reg->btr, HAL_LL_CAN_BTR_SILM_BIT );
            break;

        default:
            // STM32 doesn't have operation mode requested by user.
            return HAL_LL_CAN_ERROR;
    }
    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Request iitialization mode.
    set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_INRQ_BIT );
    // Wait until HW enters initialization mode.
    while( !check_reg_bit( &hal_ll_hw_reg->msr, HAL_LL_CAN_MSR_INAK_BIT )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;
    // Request the exit from sleep mode.
    clear_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_SLEEP_BIT );
    // Wait until HW exits sleep mode.
    while( check_reg_bit( &hal_ll_hw_reg->msr, HAL_LL_CAN_MSR_SLAK_BIT )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    // Clear CAN baudrate register.
    hal_ll_hw_reg->btr &= ~HAL_LL_CAN_BTR_REGISTER_MASK;

    // Set the operation mode requested by user.
    if ( HAL_LL_CAN_ERROR == hal_ll_can_set_operation_mode( map, config ))
        return HAL_LL_CAN_ERROR;

    // Configure bit timing.
    return hal_ll_can_bit_timing( map );
}

static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );;
    uint8_t filter_number_pos = filter_config->can_filter_bank;
    hal_ll_can_frame_format_t frame_format_id_mask[4];

    /*
     * CAN2 as a slave core of CAN1 uses the same filter registers as CAN1.
     * Filter banks dedication for devices with multiple CAN modules is following:
     *  - Filters 0 to 13 are used for single core CAN usage (CAN1 or CAN3 only);
     *  - Filters 0 to 27 are used for dual core CAN usage (CAN1 and CAN2):
     *    - Number of start bank filter for CAN2 is configured with CANSB[5:0] bits in CAN_FMR register,
            but this implementation uses default configuration (CAN2 start bank filter is 14).
     */
    if ( !default_config ) {
        #ifdef CAN_MODULE_1
        if ( HAL_LL_CAN1_BASE_ADDRESS == map->base ) {
            if ( HAL_LL_CAN_SINGLE_CORE_FILTER_LIMIT < filter_number_pos )
                return HAL_LL_CAN_ERROR;
        }
        #endif
    }

    // STM32 MCUs have only 2 FIFOs.
    if ( HAL_LL_CAN_FILTER_FIFO1 < filter_config->can_filter_fifo )
        return HAL_LL_CAN_ERROR;

    // Set an initialization mode for the filters.
    set_reg_bit( &hal_ll_hw_reg->fmr, HAL_LL_CAN_FMR_FINIT_BIT );

    if( HAL_LL_CAN_FILTER_SCALE_32BIT == filter_config->can_filter_scale ) {
        // Set single 32-bit filter scale configuration.
        set_reg_bit( &hal_ll_hw_reg->fs1r, filter_number_pos );

        hal_ll_hw_reg->filter_reg[filter_number_pos].fr1 = hal_ll_can_filter_configure_32( filter_config->can_filter_id );
        hal_ll_hw_reg->filter_reg[filter_number_pos].fr2 = hal_ll_can_filter_configure_32( filter_config->can_filter_mask_id );

        // Configure the frame type of filter/mask.
        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[0] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_32_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_32_BIT );

        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[1] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_32_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_32_BIT );


        // Configure the format of filter/mask.
        frame_format_id_mask[0] = hal_ll_can_filter_get_format_32( filter_config->can_filter_id );
        frame_format_id_mask[1] = hal_ll_can_filter_get_format_32( filter_config->can_filter_mask_id );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[0] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_32_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_32_BIT );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[1] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_32_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_32_BIT );

    } else {
        // Set dual 16-bit filter scale configuration.
        clear_reg_bit( &hal_ll_hw_reg->fs1r, filter_number_pos );

        hal_ll_hw_reg->filter_reg[filter_number_pos].fr1 =
            ( hal_ll_can_filter_configure_16( filter_config->can_filter_id_low ) |
              hal_ll_can_filter_configure_16( filter_config->can_filter_mask_id_low ) << HAL_LL_CAN_BYTE_OFFSET_2 );
        hal_ll_hw_reg->filter_reg[filter_number_pos].fr2 =
            ( hal_ll_can_filter_configure_16( filter_config->can_filter_id_high ) |
              hal_ll_can_filter_configure_16( filter_config->can_filter_mask_id_high ) << HAL_LL_CAN_BYTE_OFFSET_2 );

        // Configure the frame type of filter/mask.
        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[0] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_16_LOW_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_16_LOW_BIT );

        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[1] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_16_HIGH_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_RTR_16_HIGH_BIT );

        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[2] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_16_LOW_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_16_LOW_BIT );

        if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[3] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_16_HIGH_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_RTR_16_HIGH_BIT );

        // Configure the format of filter/mask.
        frame_format_id_mask[0] = hal_ll_can_filter_get_format_16( filter_config->can_filter_id_low );
        frame_format_id_mask[1] = hal_ll_can_filter_get_format_16( filter_config->can_filter_mask_id_low );
        frame_format_id_mask[2] = hal_ll_can_filter_get_format_16( filter_config->can_filter_id_high );
        frame_format_id_mask[3] = hal_ll_can_filter_get_format_16( filter_config->can_filter_mask_id_high );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[0] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_16_LOW_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_16_LOW_BIT );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[1] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_16_HIGH_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr1, HAL_LL_CAN_FIR_EID_16_HIGH_BIT );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[2] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_16_LOW_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_16_LOW_BIT );

        if ( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == frame_format_id_mask[3] )
            set_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_16_HIGH_BIT );
        else
            clear_reg_bit( &hal_ll_hw_reg->filter_reg[filter_number_pos].fr2, HAL_LL_CAN_FIR_EID_16_HIGH_BIT );
    }

    if ( HAL_LL_CAN_FILTER_MODE_IDMASK == filter_config->can_filter_mode )
        // Set ID-Mask Mode for the filter.
        clear_reg_bit( &hal_ll_hw_reg->fm1r, filter_number_pos );
    else
        // Set ID-List Mode for the filter.
        set_reg_bit( &hal_ll_hw_reg->fm1r, filter_number_pos );

    if ( HAL_LL_CAN_FILTER_FIFO0 == filter_config->can_filter_fifo )
        // Map this filter to FIFO0.
        clear_reg_bit( &hal_ll_hw_reg->ffa1r, filter_number_pos );
    else
        // Map this filter to FIFO1.
        set_reg_bit( &hal_ll_hw_reg->ffa1r, filter_number_pos );

    if ( HAL_LL_CAN_FILTER_ENABLE == filter_config->can_filter_enable )
        // Enable this filter.
        set_reg_bit( &hal_ll_hw_reg->fa1r, filter_number_pos );
    else
        // Disable this filter.
        clear_reg_bit( &hal_ll_hw_reg->fa1r, filter_number_pos );

    // Leave the initialization mode.
    clear_reg_bit( &hal_ll_hw_reg->fmr, HAL_LL_CAN_FMR_FINIT_BIT );
}

static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Enable clock for CAN.
    hal_ll_can_clock_enable( map->module_index, true );

    if ( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( map, filter_config, true ))
        return HAL_LL_CAN_ERROR;

    // Request the start of CAN.
    clear_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_INRQ_BIT );
    // Wait until HW starts CAN.
    while( check_reg_bit( &hal_ll_hw_reg->msr, HAL_LL_CAN_MSR_INAK_BIT )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}
// ------------------------------------------------------------------------- END
