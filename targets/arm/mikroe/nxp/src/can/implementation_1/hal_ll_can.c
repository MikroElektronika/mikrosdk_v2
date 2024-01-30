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

/*!< @brief Local handle list */
static volatile hal_ll_can_handle_register_t hal_ll_module_state[CAN_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_can_get_module_state_address ((hal_ll_can_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_can_get_handle (hal_ll_can_handle_register_t *)hal_ll_can_get_module_state_address->hal_ll_can_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_can_get_base_struct(_handle) ((hal_ll_can_base_handle_t *)_handle)
#define hal_ll_can_get_mask_base_struct(_handle) ((hal_ll_can_mask_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_can_get_base_from_hal_handle ((hal_ll_can_hw_specifics_map_t *)((hal_ll_can_handle_register_t *)\
                                            (((hal_ll_can_handle_register_t *)(handle))->hal_ll_can_handle))->hal_ll_can_handle)->base
/*!< @brief Helper macro for handling the received message */
#define hal_ll_can_message_received(fifo,mask) ((fifo & mask))
#define hal_ll_can_get_rx_data(byte,data_register,offset) ((uint8_t)(((byte) & data_register) >> offset))
#define hal_ll_can_get_rx_id(id_register,mask,offset) ((id_register & mask ) >> offset)
#define hal_ll_can_set_filter_id(id) (((id & 0x7FF) << 18) | ((id & 0x1FFFF800) >> 11))
/*!< @brief Helper macro for bit rate calculation */
#define hal_ll_can_get_btr_element_mask(element, offset) (((uint32_t)(element - 1)) << offset)
#define hal_ll_can_baudrate_check_success(br) ((br==125000)||(br==250000)||(br==500000)||(br==1000000))


#define HAL_LL_CAN_AF_CONFIG_RX (GPIO_CFG_MODE_INPUT)
#define HAL_LL_CAN_AF_CONFIG_TX (GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_PULL_UP)

#define HAL_LL_CAN0_CLOCK_ENABLE (4)
#ifdef __MKX_CHIPS__
#define HAL_LL_CAN1_CLOCK_ENABLE (4)
#else
#define HAL_LL_CAN1_CLOCK_ENABLE (5)
#define HAL_LL_CAN2_CLOCK_ENABLE (4)
#endif

/*!< @brief CAN configuration registers constants and bits */
#define HAL_LL_CAN_MCR_16BIT_FILTER_BIT       (8)
#define HAL_LL_CAN_CTRL1_LOOPBACK_BIT         (12)
#define HAL_LL_CAN_CTRL1_CLOCK_SOURCE_BIT     (13)
#define HAL_LL_CAN_MCR_DOZE_BIT               (18)
#define HAL_LL_CAN_MCR_LOW_POWER_BIT          (20)
#define HAL_LL_CAN_MCR_SOFT_RESET_BIT         (25)
#define HAL_LL_CAN_MCR_RFEN_BIT               (29)
#define HAL_LL_CAN_MCR_FREEZE_BIT             (30)
#define HAL_LL_CAN_CTRL1_LISTENONLY_BIT       (30)
#define HAL_LL_CAN_MCR_MDIS_BIT               (31)
#define HAL_LL_CAN_CTRL1_CONFIG_MASK          (0xA0)
#define HAL_LL_CAN_CTRL2_CONFIG_MASK          (0x30000UL)
#define HAL_LL_CAN_MCR_CONFIG_MASK            (0x28000FUL)
#define HAL_LL_CAN_MCR_LOWPOWER_MASK          (0x100000UL)
#define HAL_LL_CAN_CTRL2_RFFN_MASK            (0x3000000UL)
/*!< @brief CAN RX register constants and bits */
#define HAL_LL_CAN_RX_MB_NUMBER               (15)
#define HAL_LL_CAN_RX_FRAME_TYPE_OFFSET       (20)
#define HAL_LL_CAN_RX_FRAME_FORMAT_OFFSET     (21)
#define HAL_LL_CAN_RX_DATA_LEN_MASK           (0xF0000UL)
#define HAL_LL_CAN_RX_EXTID_MASK              (0x3FFFFUL)
#define HAL_LL_CAN_RX_FRAME_TYPE_MASK         (0x100000UL)
#define HAL_LL_CAN_RX_FRAME_FORMAT_MASK       (0x200000UL)
#define HAL_LL_CAN_RX_MB_INAC_MASK            (0x8000000UL)
#define HAL_LL_CAN_RX_MB_INIT_MASK            (0x4000000UL)
#define HAL_LL_CAN_RX_STDID_MASK              (0x1FFC0000UL)
/*!< @brief CAN TX register constants and bits */
#define HAL_LL_CAN_TX_MB_NUMBER               (15)
#define HAL_LL_CAN_TX_MB_INIT_MASK            (0x08000000UL)
#define HAL_LL_CAN_TX_ABORT_MASK              (0x09000000UL)
#define HAL_LL_CAN_TX_REQUEST_MASK            (0x0C000000UL)
/*!< @brief CAN filter constants */
#define HAL_LL_CAN_FILTER_INDIVIDUAL_MASK_NUM (14)
#define HAL_LL_CAN_FILTER_IDE_1_BIT           (14)
#define HAL_LL_CAN_FILTER_RTR_1_BIT           (15)
#define HAL_LL_CAN_FILTER_IDE_0_BIT           (30)
#define HAL_LL_CAN_FILTER_RTR_0_BIT           (31)
#define HAL_LL_CAN_FILTER_NUM                 (32)
#define HAL_LL_CAN_FILTER_16BIT_EXTID_MASK    (0x7000)
#define HAL_LL_CAN_MESSAGE_FULL_ID_MASK       (0x1FFFFFFF)
/*!< @brief CAN message constants */
#define HAL_LL_CAN_MESSAGE_EXTID_OFFSET       (11)
#define HAL_LL_CAN_MESSAGE_DATA_LENGTH_OFFSET (16)
#define HAL_LL_CAN_MESSAGE_SIDID_OFFSET       (18)
#define HAL_LL_CAN_MESSAGE_RTR_BIT            (20)
#define HAL_LL_CAN_MESSAGE_EXTID_BIT          (21)
#define HAL_LL_CAN_MESSAGE_SIDID_MASK         (0x07FF)
#define HAL_LL_CAN_MESSAGE_FRAME_TYPE_MASK    (0x100000UL)
#define HAL_LL_CAN_MESSAGE_FRAME_FORMAT_MASK  (0x200000UL)
#define HAL_LL_CAN_MESSAGE_EXTID_MASK         (0x1FFFF800UL)
/*!< @brief CAN baudrate constants and register bits and masks */
#define HAL_LL_CAN_BTR_PROPSEG_OFFSET         (0)
#define HAL_LL_CAN_BTR_PROPSEG_VALUE          (2)
#define HAL_LL_CAN_BTR_RJW_VALUE              (2)
#define HAL_LL_CAN_BTR_PSEG2_VALUE            (3)
#define HAL_LL_CAN_BTR_PSEG1_VALUE            (4)
#define HAL_LL_CAN_BTR_PSEG2_OFFSET           (16)
#define HAL_LL_CAN_BTR_PSEG1_OFFSET           (19)
#define HAL_LL_CAN_BTR_RJW_OFFSET             (22)
#define HAL_LL_CAN_BTR_PRESCALER_OFFSET       (24)
#define HAL_LL_CAN_BTR_MAX_PESCALER_VALUE     (256)
/*!< @brief Helper macro for defining timeout value */
#define HAL_LL_CAN_TIMEOUT_VALUE              (100000UL)
/*!< @brief Byte offset macros */
#define HAL_LL_CAN_BYTE_OFFSET_0              (0U)
#define HAL_LL_CAN_BIT_OFFSET_1               (1U)
#define HAL_LL_CAN_BYTE_OFFSET_1              (8U)
#define HAL_LL_CAN_BYTE_OFFSET_2              (16U)
#define HAL_LL_CAN_BYTE_OFFSET_3              (24U)
#define HAL_LL_CAN_BYTE_FIRST                 (0x000000FFUL)
#define HAL_LL_CAN_BYTE_SECOND                (0x0000FF00UL)
#define HAL_LL_CAN_BYTE_THIRD                 (0x00FF0000UL)
#define HAL_LL_CAN_BYTE_FOURTH                (0xFF000000UL)

/*!< @brief CAN hw specific structure */
typedef struct
{
    hal_ll_base_addr_t base;
    hal_ll_base_addr_t mask_base;
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


/*!< @brief Controller Area Network Mask structure */
typedef struct
{
    hal_ll_base_addr_t rximr[15];
} hal_ll_can_mask_handle_t;

/*!< @brief Controller Area Network Message Buffer */
typedef struct
{
    hal_ll_base_addr_t cs;        /*!< CAN receive FIFO mailbox identifier register. */
    hal_ll_base_addr_t id;        /*!< CAN receive FIFO mailbox data length control and time stamp register. */
    hal_ll_base_addr_t word0;     /*!< CAN receive FIFO mailbox data low register. */
    hal_ll_base_addr_t word1;     /*!< CAN receive FIFO mailbox data high register. */
} hal_ll_can_message_buffer_t;

/*!< @brief CAN HW register structure */
typedef struct
{
    hal_ll_base_addr_t mcr;                 /* Configuration register. */
    hal_ll_base_addr_t ctrl1;               /* Control 1 register. */
    hal_ll_base_addr_t timer;               /* Free running timer. */
    hal_ll_base_addr_t __unused1;
    hal_ll_base_addr_t rxmgmask;            /* RX mailboxes global mask register. */
    hal_ll_base_addr_t rx14mask;            /* RX 14 mask register. */
    hal_ll_base_addr_t rx15mask;            /* RX 15 mask register. */
    hal_ll_base_addr_t ecr;                 /* Error counter. */
    hal_ll_base_addr_t esr1;                /* Error and status 1 register. */
    hal_ll_base_addr_t __unused2;
    hal_ll_base_addr_t imask1;              /* Interrrupt masks 1 register. */
    hal_ll_base_addr_t __unused3;
    hal_ll_base_addr_t iflag1;              /* Interrupt flags 1 register. */
    hal_ll_base_addr_t ctrl2;               /* Control 2 register. */
    hal_ll_base_addr_t esr2;                /* Error and status 2 register. */
    hal_ll_base_addr_t __unused4[2];
    hal_ll_base_addr_t crcr;                /* CRC register. */
    hal_ll_base_addr_t rxfgmask;            /* RX FIFO global mask register. */
    hal_ll_base_addr_t rxfir;               /* RX FIFO information register. */
    hal_ll_base_addr_t __unused5[12];
    hal_ll_can_message_buffer_t mb[16];     /* Message buffers. */
    hal_ll_base_addr_t filter[32];
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
    { HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_RXIMR_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_0 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
    #endif
    #ifdef CAN_MODULE_1
    { HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_RXIMR_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_1 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
    #endif
    #ifdef CAN_MODULE_2
    { HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_RXIMR_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_2 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 }
};


/*!< @brief Global handle variables used in functions */
static volatile hal_ll_can_handle_register_t *low_level_handle;
static volatile hal_ll_can_hw_specifics_map_t *hal_ll_can_hw_specifics_map_local;
/*!< @brief Global flag for configuring buffers */
static bool hal_ll_can_buffers_configured = false;
/*!< @brief Global flag for configuring filter mask */
static bool hal_ll_can_filter_mask_configured = false;
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
 * @param[in]  filter_init - CAN filter initialization flag.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config, bool filter_init );

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

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_can_check_pins( tx_pin, rx_pin, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
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
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_handle_register_t *hal_handle = ( hal_ll_can_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_can_hw_specifics_map_local->module_index;

    hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config, false );

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = ( handle_t *)&hal_ll_can_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_filter( handle_t *handle, hal_ll_can_config_t *config,
                                    hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    low_level_handle->init_ll_state = false;
    hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config, true );

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
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config, false );

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
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config, false );

    low_level_handle->init_ll_state = true;

    return result;
}

hal_ll_err_t hal_ll_can_get_mode( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    return hal_ll_can_hw_specifics_map_local->mode;
}

hal_ll_err_t hal_ll_can_transmit( handle_t *handle, hal_ll_can_transmit_message_struct *transmit_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( hal_ll_can_hw_specifics_map_local->base );
    uint32_t control_and_status = 0;
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Set data length information.
    control_and_status = (uint32_t)transmit_message->message.data_len << HAL_LL_CAN_MESSAGE_DATA_LENGTH_OFFSET;
    // Set an appropriate frame format of the message.
    if( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == transmit_message->message.frame_format )
        control_and_status |= HAL_LL_CAN_MESSAGE_FRAME_FORMAT_MASK;

    // Set an appropriate frame type of the message.
    if( HAL_LL_CAN_FRAME_TYPE_RTR == transmit_message->message.frame_type )
        control_and_status |= HAL_LL_CAN_MESSAGE_FRAME_TYPE_MASK;

    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].id = ( transmit_message->message.id & HAL_LL_CAN_MESSAGE_SIDID_MASK ) << HAL_LL_CAN_MESSAGE_SIDID_OFFSET;
    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].id |= ( transmit_message->message.id & HAL_LL_CAN_MESSAGE_EXTID_MASK ) >> HAL_LL_CAN_MESSAGE_EXTID_OFFSET;

    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].word0 = ((uint32_t)transmit_message->message.message_data[3] ) |
                                                       ((uint32_t)transmit_message->message.message_data[2] << HAL_LL_CAN_BYTE_OFFSET_1 ) |
                                                       ((uint32_t)transmit_message->message.message_data[1] << HAL_LL_CAN_BYTE_OFFSET_2 ) |
                                                       ((uint32_t)transmit_message->message.message_data[0] << HAL_LL_CAN_BYTE_OFFSET_3 );

    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].word1 = ((uint32_t)transmit_message->message.message_data[7] ) |
                                                       ((uint32_t)transmit_message->message.message_data[6] << HAL_LL_CAN_BYTE_OFFSET_1 ) |
                                                       ((uint32_t)transmit_message->message.message_data[5] << HAL_LL_CAN_BYTE_OFFSET_2 ) |
                                                       ((uint32_t)transmit_message->message.message_data[4] << HAL_LL_CAN_BYTE_OFFSET_3 );

    // Set a transmit request.
    control_and_status |= HAL_LL_CAN_TX_REQUEST_MASK;

    // Write CS register to configure it and start transmission.
    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].cs = control_and_status;
    // Wait untill the transmission is acknowledged.
    while ( hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].cs == control_and_status ) {
        if ( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( hal_ll_can_hw_specifics_map_local->base );

    // Abort ongoing transmission.
    hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].cs = HAL_LL_CAN_TX_ABORT_MASK;
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( hal_ll_can_hw_specifics_map_local->base );
    uint8_t rx_mb_num = receive_message->rx_fifo_number;
    uint32_t read_timer, control_and_status = hal_ll_hw_reg->mb[rx_mb_num].cs;

    // NXP MCUs have only 16 mailboxes, 15 of them are for receiving.
    if ( HAL_LL_CAN_RX_MB_NUMBER <= rx_mb_num )
        return HAL_LL_CAN_ERROR;

    // Get parameters.
    receive_message->message.data_len = ( uint8_t )(control_and_status & HAL_LL_CAN_RX_DATA_LEN_MASK ) >> HAL_LL_CAN_MESSAGE_DATA_LENGTH_OFFSET;
    receive_message->message.frame_type = ( uint8_t )(control_and_status & HAL_LL_CAN_RX_FRAME_TYPE_MASK ) >> HAL_LL_CAN_RX_FRAME_TYPE_OFFSET;
    receive_message->message.frame_format = ( uint8_t )(control_and_status & HAL_LL_CAN_RX_FRAME_FORMAT_MASK ) >> HAL_LL_CAN_RX_FRAME_FORMAT_OFFSET;

    receive_message->message.id = ( hal_ll_hw_reg->mb[rx_mb_num].id & HAL_LL_CAN_RX_STDID_MASK ) >> HAL_LL_CAN_MESSAGE_SIDID_OFFSET;
    if( HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS == receive_message->message.frame_format )
        receive_message->message.id |= ( hal_ll_hw_reg->mb[rx_mb_num].id & HAL_LL_CAN_RX_EXTID_MASK ) << HAL_LL_CAN_MESSAGE_EXTID_OFFSET;

    // Get all data bytes.
    receive_message->message.message_data[0] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FOURTH, hal_ll_hw_reg->mb[rx_mb_num].word0,
                                                                       HAL_LL_CAN_BYTE_OFFSET_3 );
    receive_message->message.message_data[1] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_THIRD, hal_ll_hw_reg->mb[rx_mb_num].word0,
                                                                       HAL_LL_CAN_BYTE_OFFSET_2 );
    receive_message->message.message_data[2] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_SECOND, hal_ll_hw_reg->mb[rx_mb_num].word0,
                                                                       HAL_LL_CAN_BYTE_OFFSET_1 );
    receive_message->message.message_data[3] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FIRST, hal_ll_hw_reg->mb[rx_mb_num].word0,
                                                                       HAL_LL_CAN_BYTE_OFFSET_0 );
    receive_message->message.message_data[4] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FOURTH, hal_ll_hw_reg->mb[rx_mb_num].word1,
                                                                       HAL_LL_CAN_BYTE_OFFSET_3 );
    receive_message->message.message_data[5] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_THIRD, hal_ll_hw_reg->mb[rx_mb_num].word1,
                                                                       HAL_LL_CAN_BYTE_OFFSET_2 );
    receive_message->message.message_data[6] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_SECOND, hal_ll_hw_reg->mb[rx_mb_num].word1,
                                                                       HAL_LL_CAN_BYTE_OFFSET_1 );
    receive_message->message.message_data[7] = hal_ll_can_get_rx_data( HAL_LL_CAN_BYTE_FIRST, hal_ll_hw_reg->mb[rx_mb_num].word1,
                                                                       HAL_LL_CAN_BYTE_OFFSET_0 );

    // Read timer to unlock RX Message buffer.
    read_timer = hal_ll_hw_reg->timer;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_close( handle_t *handle ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

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

    if (( HAL_LL_PIN_NC == tx_pin ) || ( HAL_LL_PIN_NC == rx_pin )) {
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
                        if ( NULL == handle_map[hal_ll_module_id].hal_drv_can_handle ) {
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

        module.configs[0] = HAL_LL_CAN_AF_CONFIG_TX;
        module.configs[1] = HAL_LL_CAN_AF_CONFIG_RX;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list ) {
    // Map new pins
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_can_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_can_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX could have different alternate function settings, hence save both AF values
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_can_tx_map[index_list[module_index].pin_tx].af;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_can_rx_map[index_list[module_index].pin_rx].af;
}

static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_can_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_can_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_can_get_base_from_hal_handle == hal_ll_can_hw_specifics_map[hal_ll_module_count].base ) {
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
                set_reg_bit( _SIM_SCGC6, HAL_LL_CAN0_CLOCK_ENABLE );
            else
                clear_reg_bit( _SIM_SCGC6, HAL_LL_CAN0_CLOCK_ENABLE );
            break;
        #endif
        #ifdef CAN_MODULE_1
        case ( hal_ll_can_module_num( CAN_MODULE_1 ) ):
            #ifdef __MKX_CHIPS__
            if( true == clock_enable )
                set_reg_bit( _SIM_SCGC3, HAL_LL_CAN1_CLOCK_ENABLE );
            else
                clear_reg_bit( _SIM_SCGC3, HAL_LL_CAN1_CLOCK_ENABLE );
            #else
            if( true == clock_enable )
                set_reg_bit( _SIM_SCGC6, HAL_LL_CAN1_CLOCK_ENABLE );
            else
                clear_reg_bit( _SIM_SCGC6, HAL_LL_CAN1_CLOCK_ENABLE );
            #endif
            break;
        #endif
        #ifdef CAN_MODULE_2
        case ( hal_ll_can_module_num( CAN_MODULE_2 ) ):
            if( true == clock_enable ) {
                set_reg_bit( _SIM_SCGC6, HAL_LL_CAN1_CLOCK_ENABLE );
                set_reg_bit( _SIM_SCGC3, HAL_LL_CAN2_CLOCK_ENABLE );
            } else {
                clear_reg_bit( _SIM_SCGC6, HAL_LL_CAN1_CLOCK_ENABLE );
                clear_reg_bit( _SIM_SCGC3, HAL_LL_CAN2_CLOCK_ENABLE );
            }
            break;
        #endif

        default:
            break;
    }
}

static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    SIM_ClocksTypeDef rcc_clocks;
    uint16_t prescaler;
    uint8_t rjw, pseg1, pseg2, temp, propseg;
    uint32_t baud_rate, can_clock;

    baud_rate = map->frequency;

    SIM_GetClocksFrequency( &rcc_clocks );
    #ifdef __MKX_CHIPS__
    can_clock = rcc_clocks.busclock_frequency;
    #else
    can_clock = rcc_clocks.fast_peripheral_frequency;
    #endif

    /*
     * CAN module on MKV4 and MKV5 MCUs supports only 125K, 250K, 500K and 1M baud rates
     * so we return error if user tries to set other values.
     */
    #ifndef __MKX_CHIPS__
    if ( !hal_ll_can_baudrate_check_success( baud_rate ))
        return HAL_LL_CAN_ERROR;
    #endif

    /*
     * Values for Propagation Segment, Phase Segment 1 and 2 and Re-sync Jump Width are fixed.
     * Prescaler is the only value that is calculated based on the source clock value and the desired baud rate.
     *
     * Initial parameters:
     * - can_clock: CAN source clock frequency (APB1) in Hz.
     * - baud_rate: Desired CAN bus baud rate.
     *
     * Calculated parameters:
     * - prescaler: The prescaler value to achieve the desired baud rate.
     *
     * Formulas used:
     * - baud_rate = can_clock / (prescaler * (pseg1 + pseg2 + propseg + 1)) (from NXP Reference manuals)
     */
    propseg = HAL_LL_CAN_BTR_PROPSEG_VALUE;
    pseg1 = HAL_LL_CAN_BTR_PSEG1_VALUE;
    pseg2 = HAL_LL_CAN_BTR_PSEG2_VALUE;
    rjw = HAL_LL_CAN_BTR_RJW_VALUE;

    prescaler = can_clock / ( baud_rate * ( pseg1 + pseg2 + propseg + 1 ));

    if( HAL_LL_CAN_BTR_MAX_PESCALER_VALUE >= prescaler ) {
        uint32_t rjw_val = hal_ll_can_get_btr_element_mask( rjw, HAL_LL_CAN_BTR_RJW_OFFSET );
        uint32_t pseg1_val = hal_ll_can_get_btr_element_mask( pseg1, HAL_LL_CAN_BTR_PSEG1_OFFSET );
        uint32_t pseg2_val = hal_ll_can_get_btr_element_mask( pseg2, HAL_LL_CAN_BTR_PSEG2_OFFSET );
        uint32_t prescaler_val = hal_ll_can_get_btr_element_mask( prescaler, HAL_LL_CAN_BTR_PRESCALER_OFFSET );
        uint32_t propseg_val = hal_ll_can_get_btr_element_mask( propseg, HAL_LL_CAN_BTR_PROPSEG_OFFSET );
        hal_ll_hw_reg->ctrl1 |= rjw_val | pseg1_val | pseg2_val | prescaler_val | propseg_val;

        // Exit freeze mode.
        clear_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_FREEZE_BIT );

        /*
        * Note: Setting parameters that result in a baud rate that differs from the desired value is not acceptable.
        *       If two devices communicate over CAN, their baud rates need to be exactly the same.
        */
        return HAL_LL_CAN_SUCCESS;
    }

    // If this point was reached, baud rate wasn't set to the desired value and error is returned.
    return HAL_LL_CAN_ERROR;
}

static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct ( map->base );
    hal_ll_can_mask_handle_t *hal_ll_hw_mask_reg = hal_ll_can_get_mask_base_struct( map->mask_base );

    // Disable CAN.
    set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_MDIS_BIT );

    // Set can clock source.
    set_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL1_CLOCK_SOURCE_BIT );

    // Enable CAN.
    clear_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_MDIS_BIT );

    if ( !hal_ll_can_buffers_configured ) {
        // Inactivate the mailbox to reserve it for transmitting.
        hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].cs = HAL_LL_CAN_TX_MB_INIT_MASK;
        // Clear all TX mailbox registers as they have undefined reset value.
        hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].id = 0x00000000UL;
        hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].word0 = 0x00000000UL;
        hal_ll_hw_reg->mb[HAL_LL_CAN_TX_MB_NUMBER].word1 = 0x00000000UL;

        // Inactivate mailboxex 0 to 14 to reserve them for receiving.
        for ( uint8_t rx_mb_num = 0; rx_mb_num < HAL_LL_CAN_RX_MB_NUMBER; rx_mb_num++ ) {
            hal_ll_hw_reg->mb[rx_mb_num].cs = HAL_LL_CAN_RX_MB_INAC_MASK;
            hal_ll_hw_reg->mb[rx_mb_num].id = 0x00000000UL;
            hal_ll_hw_reg->mb[rx_mb_num].word0 = 0x00000000UL;
            hal_ll_hw_reg->mb[rx_mb_num].word1 = 0x00000000UL;
            hal_ll_hw_mask_reg->rximr[rx_mb_num] = 0x00000000UL;
        }
        hal_ll_hw_reg->rxmgmask = 0x00000000UL;
        hal_ll_hw_reg->rx14mask = 0x00000000UL;
        hal_ll_can_buffers_configured = true;
    }

    // Wait until FlexCAN exits from any Low Power Mode.
    while( check_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_LOW_POWER_BIT ));
    // Soft reset.
    set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_SOFT_RESET_BIT );
    // Wait until FlexCAN reset completes.
    while( check_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_SOFT_RESET_BIT ));

    // Configure CAN to use filtering for incoming messages and 1 mailbox as TX.
    hal_ll_hw_reg->mcr |= HAL_LL_CAN_MCR_CONFIG_MASK;

    // Configure CAN to sample received message 3 times and enable timer sync.
    hal_ll_hw_reg->ctrl1 = HAL_LL_CAN_CTRL1_CONFIG_MASK;

    // Configure CAN to enable RTR and IDE bit readings for RX message buffers.
    hal_ll_hw_reg->ctrl2 |= HAL_LL_CAN_CTRL2_CONFIG_MASK;

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    hal_ll_can_mask_handle_t *hal_ll_hw_mask_reg = hal_ll_can_get_mask_base_struct( map->mask_base );
    uint8_t rx_mailbox_num = filter_config->can_filter_fifo;
    uint8_t filter_num = filter_config->can_filter_bank;

    // This implementation supports only 14 receive mailboxes and only 1 filter per mailbox.
    if ( HAL_LL_CAN_RX_MB_NUMBER <= filter_config->can_filter_fifo || filter_num )
        return HAL_LL_CAN_ERROR;

    if ( HAL_LL_CAN_FILTER_ENABLE == filter_config->can_filter_enable ) {
        // Set ID for receive filter which is the part of RX mailbox in this case.
        hal_ll_hw_reg->mb[rx_mailbox_num].id = hal_ll_can_set_filter_id( filter_config->can_filter_id );
        hal_ll_hw_reg->mb[rx_mailbox_num].cs = HAL_LL_CAN_RX_MB_INIT_MASK;
    }

    if ( filter_config->can_filter_id & HAL_LL_CAN_MESSAGE_EXTID_MASK )
        set_reg_bit( &hal_ll_hw_reg->mb[rx_mailbox_num].cs, HAL_LL_CAN_MESSAGE_EXTID_BIT );

    if ( HAL_LL_CAN_FRAME_TYPE_RTR == filter_config->can_filter_frame_type[0] )
        set_reg_bit ( &hal_ll_hw_reg->mb[rx_mailbox_num].cs, HAL_LL_CAN_MESSAGE_RTR_BIT );

    // For RX mailboxes 0-13 there is one unique filter mask.
    if ( HAL_LL_CAN_FILTER_FIFO14 > filter_config->can_filter_fifo ) {
        if ( !hal_ll_can_filter_mask_configured ) {
            hal_ll_hw_reg->rxmgmask = hal_ll_can_set_filter_id( filter_config->can_filter_mask_id );
            hal_ll_can_filter_mask_configured = true;
        } else {
            // There can be set only one unique mask for mailboxes 0 to 13 for this implementation.
            if ( hal_ll_hw_reg->rxmgmask != hal_ll_can_set_filter_id( filter_config->can_filter_mask_id ))
                return HAL_LL_CAN_ERROR;
        }
    } else
        hal_ll_hw_reg->rx14mask = hal_ll_can_set_filter_id( filter_config->can_filter_mask_id );

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);

    switch( config->mode ) {
        case HAL_LL_CAN_MODE_NORMAL:
            break;
        case HAL_LL_CAN_MODE_FREEZE:
            set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_FREEZE_BIT );
            break;
        case HAL_LL_CAN_MODE_LOOPBACK:
            set_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL1_LOOPBACK_BIT );
            break;
        case HAL_LL_CAN_MODE_LISTENONLY:
            set_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL1_LISTENONLY_BIT );
            break;
        case HAL_LL_CAN_MODE_DISABLE:
            set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_MDIS_BIT );
            break;
        case HAL_LL_CAN_MODE_DOZE:
            set_reg_bit( &hal_ll_hw_reg->mcr, HAL_LL_CAN_MCR_DOZE_BIT );
            break;
        case HAL_LL_CAN_MODE_STOP:
            if ( hal_ll_hw_reg->mcr & HAL_LL_CAN_MCR_LOWPOWER_MASK )
                return HAL_LL_CAN_SUCCESS;
            else
                return HAL_LL_CAN_ERROR;

        default:
            // NXP MCU doesn't have operation mode requested by user.
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config, bool filter_init ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    hal_ll_err_t result;

    // Enable clock for CAN.
    hal_ll_can_clock_enable( map->module_index, true );

    if ( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    if ( filter_init ) {
        if ( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( map, filter_config ))
            return HAL_LL_CAN_ERROR;
    }

    if ( HAL_LL_CAN_ERROR == hal_ll_can_bit_timing( map ))
        return HAL_LL_CAN_ERROR;

    // Set the operation mode requested by user.
    if ( HAL_LL_CAN_ERROR == hal_ll_can_set_operation_mode( map, config ))
        return HAL_LL_CAN_ERROR;

    return HAL_LL_CAN_SUCCESS;
}
// ------------------------------------------------------------------------- END
