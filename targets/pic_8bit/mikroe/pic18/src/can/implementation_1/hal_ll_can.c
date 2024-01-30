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

#define HAL_LL_CAN_CANCON_REQOP_MASK           (0xE0)
#define HAL_LL_CAN_CANCON_CONFIGURATION_MASK   (0x80)
#define HAL_LL_CAN_CANCON_LISTENONLY_MASK      (0x60)
#define HAL_LL_CAN_CANCON_LOOPBACK_MASK        (0x40)
#define HAL_LL_CAN_CANCON_NORMAL_MASK          (0x00)
#define HAL_LL_CAN_CANCON_DISABLE_MASK         (0x20)

#define HAL_LL_CAN_CANCON_ABAT_BIT_POS         (4)

#define HAL_LL_CAN_CANSTAT_CONFIGURATION_MASK  (HAL_LL_CAN_CANCON_CONFIGURATION_MASK)
#define HAL_LL_CAN_CANSTAT_OPMODE_MASK         (HAL_LL_CAN_CANCON_REQOP_MASK)

#define HAL_LL_CAN_BRGCON2_SEG2PHTS_MASK     (0x80)
#define HAL_LL_CAN_BRGCON2_TSEG1_SHIFT       (3)
#define HAL_LL_CAN_BRGCON1_SJW_SHIFT         (6)
#define HAL_LL_CAN_BRGCON_PRESCALER_MAX_VAL  (64)
#define HAL_LL_CAN_BRGCON_SEG1PH_MAX_VAL     (8)
#define HAL_LL_CAN_BRGCON_SEG2PH_MAX_VAL     (8)
#define HAL_LL_CAN_BRGCON_SJW_CONST_VALUE    (1)
#define HAL_LL_CAN_BRGCON_PT_CONST_VALUE     (1)

#define HAL_LL_CAN_TXBCON_TXREQ_BIT       (3)
#define HAL_LL_CAN_RXBCON_RXFUL_BIT       (7)
#define HAL_LL_CAN_RXB0CON_FILHIT0_MASK   (0x1)
#define HAL_LL_CAN_RXB1CON_FILHIT_MASK    (0x3)

#define HAL_LL_CAN_EID_BITS_28_11         (0x3FFFF800UL)
#define HAL_LL_CAN_EID_BITS_7_0           (0xFFUL)
#define HAL_LL_CAN_EID_BITS_15_8          (0xFF00UL)
#define HAL_LL_CAN_EID_BITS_17_16         (0x30000UL)
#define HAL_LL_CAN_EID_BITS_20_18         (0x1C0000UL)
#define HAL_LL_CAN_EID_BITS_28_21         (0x1FE00000UL)
#define HAL_LL_CAN_SID_BITS_2_0           (0x7UL)
#define HAL_LL_CAN_SID_BITS_10_3          (0x7F8UL)
#define HAL_LL_CAN_SID_SHIFT              (11UL)
#define HAL_LL_CAN_EID_SIDL_SHIFT         (3UL)
#define HAL_LL_CAN_EID_EIDH_SHIFT         (8UL)
#define HAL_LL_CAN_SID_SIDL_SHIFT         (5UL)
#define HAL_LL_CAN_SID_SIDH_SHIFT         (3UL)
#define HAL_LL_CAN_EID_SIDH_SHIFT         (21UL)
#define HAL_LL_CAN_EID_SIDL_17_16_SHIFT   (16UL)
#define HAL_LL_CAN_EID_SIDL_20_18_SHIFT   (13UL)
#define HAL_LL_CAN_SIDL_EXIDE_MASK        (0x8UL)

#define HAL_LL_CAN_ECANCON_MDSEL_MASK     (0xC0)
#define HAL_LL_CAN_ECANCON_MODE0_MASK     (0x00)
#define HAL_LL_CAN_ECANCON_MODE1_MASK     (0x40)
#define HAL_LL_CAN_ECANCON_MODE2_MASK     (0x80)

#define HAL_LL_CAN_NUMBER_OF_MASKS        (2)
#define HAL_LL_CAN_NUMBER_OF_FILTERS      (6)

#define HAL_LL_CAN_CIOCON_ENDRHI_MASK     (0x20)

#define HAL_LL_CAN_REGISTER_CLEAR         (0x00)

#define HAL_LL_CAN_TIMEOUT_VALUE 10000UL

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
    uint16_t pin_tx;
    uint16_t pin_rx;
} hal_ll_can_pin_id;

/*!< @brief CAN acceptance filter structure */
typedef struct
{
    uint8_t rxfsidh;
    uint8_t rxfsidl;
    uint8_t rxfeidh;
    uint8_t rxfeidl;
} hal_ll_can_acceptance_filters;

/*!< @brief CAN acceptance mask structure */
typedef struct
{
    uint8_t rxmsidh;
    uint8_t rxmsidl;
    uint8_t rxmeidh;
    uint8_t rxmeidl;
} hal_ll_can_acceptance_masks;

/*!< @brief CAN transfer register structure */
typedef struct
{
    uint8_t con;
    uint8_t sidh;
    uint8_t sidl;
    uint8_t eidh;
    uint8_t eidl;
    uint8_t dlc;
    uint8_t d0;
    uint8_t d1;
    uint8_t d2;
    uint8_t d3;
    uint8_t d4;
    uint8_t d5;
    uint8_t d6;
    uint8_t d7;
} hal_ll_can_transfer_regs_t;

/*!< @brief CAN HW register structure */
#ifdef PIC18Kxx
typedef struct
{
    uint8_t rxerrcnt;
    uint8_t txerrcnt;
    uint8_t brgcon1;
    uint8_t brgcon2;
    uint8_t brgcon3;
    uint8_t rxfcon0;
    uint8_t rxfcon1;
    hal_ll_can_acceptance_filters acceptance_filters_6_to_15[10]; // Acceptance filters 6-15. Used only in modes 1 and 2.
    uint8_t sdflc; // Used only in modes 1 and 2.
    uint8_t rxfbcon[8]; // Used only in modes 1 and 2.
    uint8_t msel[4]; // Used only in modes 1 and 2.
    uint8_t bsel0; // Used only in modes 1 and 2.
    uint8_t bie0; // Used only in modes 1 and 2.
    uint8_t txbie; // Used only in modes 1 and 2.
    hal_ll_can_transfer_regs_t b0; // Used only in modes 1 and 2.
    uint16_t __unused0; // CANCON_RO9/CANSTAT_RO9
    hal_ll_can_transfer_regs_t b1; // Used only in modes 1 and 2.
    uint16_t __unused1; // CANCON_RO8/CANSTAT_RO8
    hal_ll_can_transfer_regs_t b2; // Used only in modes 1 and 2.
    uint16_t __unused2; // CANCON_RO7/CANSTAT_RO7
    hal_ll_can_transfer_regs_t b3; // Used only in modes 1 and 2.
    uint16_t __unused3; // CANCON_RO6/CANSTAT_RO6
    hal_ll_can_transfer_regs_t b4; // Used only in modes 1 and 2.
    uint16_t __unused4; // CANCON_RO5/CANSTAT_RO5
    hal_ll_can_transfer_regs_t b5; // Used only in modes 1 and 2.
    uint16_t __unused5; // CANCON_RO4/CANSTAT_RO4
    hal_ll_can_acceptance_filters acceptance_filters[HAL_LL_CAN_NUMBER_OF_FILTERS]; // Acceptance filters 0-5
    hal_ll_can_acceptance_masks acceptance_masks[HAL_LL_CAN_NUMBER_OF_MASKS];
    hal_ll_can_transfer_regs_t t2b_regs;                  // Transmit buffer 2
    uint16_t __unused6; // CANCON_RO3/CANSTAT_RO3
    hal_ll_can_transfer_regs_t t1b_regs;                  // Transmit buffer 1
    uint16_t __unused7; // CANCON_RO2/CANSTAT_RO2
    hal_ll_can_transfer_regs_t t0b_regs;                  // Transmit buffer 0
    uint16_t __unused8; // CANCON_RO1/CANSTAT_RO1
    hal_ll_can_transfer_regs_t r1b_regs;                  // Receive buffer 1
    uint16_t __unused9; // CANCON_RO0/CANSTAT_RO0
    uint32_t __unused10[8];
    hal_ll_can_transfer_regs_t r0b_regs;                  // Receive buffer 0
    uint8_t canstat;
    uint8_t cancon;
    uint8_t ciocon;
    uint8_t comstat;
    uint8_t ecancon;
} hal_ll_can_base_handle_t;
#else
typedef struct
{
    hal_ll_can_acceptance_filters acceptance_filters[HAL_LL_CAN_NUMBER_OF_FILTERS];
    hal_ll_can_acceptance_masks acceptance_masks[HAL_LL_CAN_NUMBER_OF_MASKS];
    hal_ll_can_transfer_regs_t t2b_regs;              // Transmit buffer 2
    uint16_t __unused0; // CANCON_RO3/CANSTAT_RO3
    hal_ll_can_transfer_regs_t t1b_regs;              // Transmit buffer 1
    uint16_t __unused1; // CANCON_RO2/CANSTAT_RO2
    hal_ll_can_transfer_regs_t t0b_regs;              // Transmit buffer 0
    uint16_t __unused2; // CANCON_RO1/CANSTAT_RO1
    hal_ll_can_transfer_regs_t r1b_regs;              // Receive buffer 1
    uint16_t __unused3; // CANCON_RO0/CANSTAT_RO0
    hal_ll_can_transfer_regs_t r0b_regs;              // Receive buffer 0
    uint8_t canstat;
    uint8_t cancon;
    uint8_t brgcon1;
    uint8_t brgcon2;
    uint8_t brgcon3;
    uint8_t ciocon;
    uint8_t comstat;
    uint8_t rxerrcnt;
    uint8_t txerrcnt;
    uint8_t ecancon;
} hal_ll_can_base_handle_t;
#endif

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
    #ifdef CAN_MODULE
    { HAL_LL_CAN_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 500000 },
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
 * @brief Sets CAN operating mode.
 *
 * Sets OPMOD field in the CAN control register, then waits for
 * adequate value in REQOP to be set by hardware.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  mode - CAN module mode structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_mode_t mode );

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
static void hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config );

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
        hal_ll_can_map_pins( pin_check_result, &index_list );
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
    hal_ll_can_mode_t original_mode;
    hal_ll_err_t result;

    low_level_handle->init_ll_state = false;

    original_mode = hal_ll_can_hw_specifics_map_local->mode;

    hal_ll_can_hw_specifics_map_local->mode = config->mode;
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    // In case the desired mode setting hasn't been achieved, there's no need to update the map.
    if( HAL_LL_CAN_SUCCESS != result )
        hal_ll_can_hw_specifics_map_local->mode = original_mode;

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
    uint32_t message_id = 0;

    // Transmit request clear.
    clear_reg_bit( &hal_ll_hw_reg->t0b_regs.con, HAL_LL_CAN_TXBCON_TXREQ_BIT );

    hal_ll_hw_reg->t0b_regs.dlc = transmit_message->message.data_len;

    message_id = (uint32_t)transmit_message->message.std_id | (uint32_t)( transmit_message->message.ext_id << 16 );
    if( HAL_LL_CAN_EID_BITS_28_11 & message_id ) {
        // Extended ID.
        hal_ll_hw_reg->t0b_regs.eidl = message_id & HAL_LL_CAN_EID_BITS_7_0; // EID[7:0]
        hal_ll_hw_reg->t0b_regs.eidh = ( message_id & HAL_LL_CAN_EID_BITS_15_8 ) >> HAL_LL_CAN_EID_EIDH_SHIFT; // EID[15:8]
        hal_ll_hw_reg->t0b_regs.sidl = (( message_id & HAL_LL_CAN_EID_BITS_20_18 ) >> HAL_LL_CAN_EID_SIDL_20_18_SHIFT ) |
                                       (( message_id & HAL_LL_CAN_EID_BITS_17_16 ) >> HAL_LL_CAN_EID_SIDL_17_16_SHIFT ) |
                                       HAL_LL_CAN_SIDL_EXIDE_MASK; // EID[17:16] | EXIDE | EID[20:18]
        hal_ll_hw_reg->t0b_regs.sidh = ( message_id & HAL_LL_CAN_EID_BITS_28_21 ) >> HAL_LL_CAN_EID_SIDH_SHIFT; // EID[28:21]
    } else {
        // Standard ID.
        hal_ll_hw_reg->t0b_regs.sidl = ( HAL_LL_CAN_SID_BITS_2_0 & transmit_message->message.std_id ) << HAL_LL_CAN_SID_SIDL_SHIFT;
        hal_ll_hw_reg->t0b_regs.sidh = ( HAL_LL_CAN_SID_BITS_10_3 & transmit_message->message.std_id ) >> HAL_LL_CAN_SID_SIDH_SHIFT;
    }

    hal_ll_hw_reg->t0b_regs.d0 = transmit_message->message.message_data[0];
    hal_ll_hw_reg->t0b_regs.d1 = transmit_message->message.message_data[1];
    hal_ll_hw_reg->t0b_regs.d2 = transmit_message->message.message_data[2];
    hal_ll_hw_reg->t0b_regs.d3 = transmit_message->message.message_data[3];
    hal_ll_hw_reg->t0b_regs.d4 = transmit_message->message.message_data[4];
    hal_ll_hw_reg->t0b_regs.d5 = transmit_message->message.message_data[5];
    hal_ll_hw_reg->t0b_regs.d6 = transmit_message->message.message_data[6];
    hal_ll_hw_reg->t0b_regs.d7 = transmit_message->message.message_data[7];

    // Request message transmission.
    set_reg_bit( &hal_ll_hw_reg->t0b_regs.con, HAL_LL_CAN_TXBCON_TXREQ_BIT );

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;

    // Abort all pending transmissions (in all transmit buffers).
    set_reg_bit( &hal_ll_hw_reg->cancon, HAL_LL_CAN_CANCON_ABAT_BIT_POS );
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    volatile hal_ll_can_transfer_regs_t *rx_buffer_regs;

    if ( HAL_LL_CAN_FILTER_FIFO0 == receive_message->rx_fifo_number ) {
        rx_buffer_regs = &hal_ll_hw_reg->r0b_regs;
    } else {
        rx_buffer_regs = &hal_ll_hw_reg->r1b_regs;
    }

    // Check if the receive buffer contains a received message.
    if( check_reg_bit( &rx_buffer_regs->con, HAL_LL_CAN_RXBCON_RXFUL_BIT )) {
        receive_message->message.data_len = rx_buffer_regs->dlc;
        receive_message->message.message_data[0] = rx_buffer_regs->d0;
        receive_message->message.message_data[1] = rx_buffer_regs->d1;
        receive_message->message.message_data[2] = rx_buffer_regs->d2;
        receive_message->message.message_data[3] = rx_buffer_regs->d3;
        receive_message->message.message_data[4] = rx_buffer_regs->d4;
        receive_message->message.message_data[5] = rx_buffer_regs->d5;
        receive_message->message.message_data[6] = rx_buffer_regs->d6;
        receive_message->message.message_data[7] = rx_buffer_regs->d7;

        // Clear RXFUL to allow CAN to load new messages.
        clear_reg_bit( &rx_buffer_regs->con, HAL_LL_CAN_RXBCON_RXFUL_BIT );
    }

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_close( handle_t *handle ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);

    if( low_level_handle->hal_ll_can_handle != NULL ) {
        hal_ll_can_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;

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

static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list ) {
    // Map new pins
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_can_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_can_rx_map[ index_list[module_index].pin_rx ].pin;
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

static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t prescaler = 0, best_prescaler = 0, tseg1 = 0, tseg2 = 0, best_tseg1 = 0, best_tseg2 = 0, temp = 0;
    uint8_t sjw = 0, pt = 0;
    uint32_t baud_rate = 0, can_clock = 0;

    baud_rate = map->frequency;

    can_clock = Get_Fosc_kHz() * 1000;

    /*
     * Description: This code snippet searches for optimal parameters for configuring
     * the CAN bus baud rate on PIC18 microcontrollers, based on the provided parameters.
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
     * - baud_rate = can_clock / (2 * prescaler * (tseg1 + tseg2 + swj + pt)) (from PIC18 Data sheets)
     *
     * Note: sjw (synchronization jump width) is fixed to 1, the preferred value, but can range from 1 to 4 TQ.
     *       pt (propagation time) is fixed to 1, the preferred value, but can range from 1 to 8 TQ.
     */

    sjw = HAL_LL_CAN_BRGCON_SJW_CONST_VALUE;
    pt = HAL_LL_CAN_BRGCON_PT_CONST_VALUE;

    for( prescaler = 1; prescaler <= HAL_LL_CAN_BRGCON_PRESCALER_MAX_VAL; prescaler++ ) {
        for( tseg1 = 1; tseg1 <= HAL_LL_CAN_BRGCON_SEG1PH_MAX_VAL; tseg1++ ) {
            for( tseg2 = 2; tseg2 <= HAL_LL_CAN_BRGCON_SEG2PH_MAX_VAL; tseg2++ ) {
                temp = 2 * prescaler * ( tseg1 + tseg2 + sjw + pt );
                uint32_t actual_baud_rate = can_clock / temp;

                if( actual_baud_rate == baud_rate ) {
                    // Exact match found
                    uint8_t pt_val = pt - 1;
                    uint8_t sjw_val = ( sjw - 1 ) << HAL_LL_CAN_BRGCON1_SJW_SHIFT;
                    uint8_t tseg1_val = ( tseg1 - 1 ) << HAL_LL_CAN_BRGCON2_TSEG1_SHIFT;
                    uint8_t tseg2_val = tseg2 - 1;
                    uint8_t prescaler_val = prescaler - 1;

                    hal_ll_hw_reg->brgcon1 = sjw_val | prescaler_val;
                    hal_ll_hw_reg->brgcon2 = HAL_LL_CAN_BRGCON2_SEG2PHTS_MASK | tseg1_val | pt_val;
                    hal_ll_hw_reg->brgcon3 = tseg2_val;

                    return HAL_LL_CAN_SUCCESS;
                }
            }
        }
        /*
         * Note: Setting parameters that result in a baud rate that differs from the desired value is not acceptable.
         *       If two devices communicate over CAN, their baud rates need to be exactly the same.
         */
    }

    // If this point was reached, baud rate wasn't set to the desired value and error is returned.
    return HAL_LL_CAN_ERROR;
}

static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    hal_ll_err_t result = HAL_LL_CAN_SUCCESS;

    hal_ll_hw_reg->ecancon = HAL_LL_CAN_ECANCON_MODE0_MASK & HAL_LL_CAN_ECANCON_MDSEL_MASK; // Set Mode 0 (Default mode)
    hal_ll_hw_reg->ciocon = HAL_LL_CAN_CIOCON_ENDRHI_MASK; // CANTX pin will drive VDD when recessive

    // These registers have undefined reset values, so they should be cleared first.
    for( uint8_t counter = 0; counter < HAL_LL_CAN_NUMBER_OF_MASKS; counter++ ) {
        hal_ll_hw_reg->acceptance_masks[counter]->rxmeidh = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_masks[counter]->rxmeidl = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_masks[counter]->rxmsidh = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_masks[counter]->rxmsidl = HAL_LL_CAN_REGISTER_CLEAR;
    }

    // These registers have undefined reset values, so they should be cleared first.
    for( uint8_t counter = 0; counter < HAL_LL_CAN_NUMBER_OF_FILTERS; counter++ ) {
        hal_ll_hw_reg->acceptance_filters[counter]->rxfeidh = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_filters[counter]->rxfeidl = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_filters[counter]->rxfsidh = HAL_LL_CAN_REGISTER_CLEAR;
        hal_ll_hw_reg->acceptance_filters[counter]->rxfsidl = HAL_LL_CAN_REGISTER_CLEAR;
    }

    result = hal_ll_can_bit_timing( map );

    return result;
}

static void hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint8_t filter_number = filter_config->can_filter_bank, mask_number = 0;

    /*
     * Acceptance filters RXF0 and RXF1 and filter mask RXM0 are associated with RXB0.
     * Filters RXF2, RXF3, RXF4 and RXF5 and mask RXM1 are associated with RXB1.
     */

    if ( HAL_LL_CAN_FILTER_FIFO0 == filter_config->can_filter_fifo ) {
        // If receive buffer is 0 (RXB0), mask is RXM0. Select filter RXF0 or RXF1.
        hal_ll_hw_reg->r0b_regs.con |= filter_number & HAL_LL_CAN_RXB0CON_FILHIT0_MASK;
        mask_number = 0;
    } else if ( HAL_LL_CAN_FILTER_FIFO1 == filter_config->can_filter_fifo ) {
        // If receive buffer is 1 (RXB1), mask is RXM1. Select filter RXF2, RXF3, RXF4 or RXF5.
        hal_ll_hw_reg->r0b_regs.con |= filter_number & HAL_LL_CAN_RXB1CON_FILHIT_MASK;
        mask_number = 1;
    }

    if ( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_11 ) {
        // Extended filter ID.
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfeidl = filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_7_0; // EID[7:0]
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfeidh = ( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_15_8 ) >> 
                                                                    HAL_LL_CAN_EID_EIDH_SHIFT; // EID[15:8]
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfsidl = (( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_17_16 ) >>
                                                                    HAL_LL_CAN_EID_SIDL_17_16_SHIFT) |
                                                                    (( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_20_18 ) >>
                                                                    HAL_LL_CAN_EID_SIDL_20_18_SHIFT ); // EID[17:16] | EID[20:18]
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfsidh = filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_21 >>
                                                                    HAL_LL_CAN_EID_SIDH_SHIFT; // EID[28:21]
    } else {
        // Standard filter ID.
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfsidl = ( filter_config->can_filter_id & HAL_LL_CAN_SID_BITS_2_0 ) <<
                                                                    HAL_LL_CAN_SID_SIDL_SHIFT; // SID[2:0]
        hal_ll_hw_reg->acceptance_filters[filter_number]->rxfsidh = ( filter_config->can_filter_id & HAL_LL_CAN_SID_BITS_10_3 ) >>
                                                                    HAL_LL_CAN_SID_SIDH_SHIFT; // EID[28:21]
    }

    if ( filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_28_11 ) {
        // Extended mask ID.
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmeidl = filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_7_0; // EID[7:0]
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmeidh = ( filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_15_8 ) >>
                                                                HAL_LL_CAN_EID_EIDH_SHIFT; // EID[15:8]
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmsidl = (( filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_17_16 ) >>
                                                                 HAL_LL_CAN_EID_SIDL_17_16_SHIFT ) |
                                                                (( filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_20_18 ) >>
                                                                 HAL_LL_CAN_EID_SIDL_20_18_SHIFT ); // EID[17:16] | EID[20:18]
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmsidh = ( filter_config->can_filter_mask_id & HAL_LL_CAN_EID_BITS_28_21 ) >>
                                                                HAL_LL_CAN_EID_SIDH_SHIFT; // EID[28:21]
    } else {
        // Standard mask ID.
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmsidl = ( filter_config->can_filter_mask_id & HAL_LL_CAN_SID_BITS_2_0 ) <<
                                                                HAL_LL_CAN_SID_SIDL_SHIFT; // SID[2:0]
        hal_ll_hw_reg->acceptance_masks[mask_number]->rxmsidh = ( filter_config->can_filter_mask_id & HAL_LL_CAN_SID_BITS_10_3 ) >>
                                                                HAL_LL_CAN_SID_SIDH_SHIFT; // EID[28:21]
    }
}

static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_mode_t mode ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    hal_ll_hw_reg->cancon &= ~HAL_LL_CAN_CANCON_REQOP_MASK;

    switch( mode ) {
        case HAL_LL_CAN_MODE_CONFIGURATION:
            hal_ll_hw_reg->cancon |= HAL_LL_CAN_CANCON_CONFIGURATION_MASK;
            /*
             * From PIC18 Datasheets:
             * "A request to switch to Configuration mode may not be immediately honored.
             *  Module will wait for CAN bus to be idle before switching to Configuration Mode.
             *  Request for other modes such as Loopback, Disable etc. may be honored immediately."
            */
            while( HAL_LL_CAN_CANSTAT_CONFIGURATION_MASK != ( hal_ll_hw_reg->canstat & HAL_LL_CAN_CANSTAT_OPMODE_MASK )) {
                if( !timeout-- )
                    return HAL_LL_CAN_ERROR;
            }
            break;
        case HAL_LL_CAN_MODE_LISTENONLY:
            hal_ll_hw_reg->cancon |= HAL_LL_CAN_CANCON_LISTENONLY_MASK;
            break;
        case HAL_LL_CAN_MODE_LOOPBACK:
            hal_ll_hw_reg->cancon |= HAL_LL_CAN_CANCON_LOOPBACK_MASK;
            break;
        case HAL_LL_CAN_MODE_NORMAL:
            hal_ll_hw_reg->cancon |= HAL_LL_CAN_CANCON_NORMAL_MASK;
            break;
        case HAL_LL_CAN_MODE_DISABLE:
            hal_ll_hw_reg->cancon |= HAL_LL_CAN_CANCON_DISABLE_MASK;
            break;

        default:
            return HAL_LL_CAN_ERROR;

    }

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);

    if( HAL_LL_CAN_ERROR == hal_ll_can_set_operation_mode( map, HAL_LL_CAN_MODE_CONFIGURATION ))
        return HAL_LL_CAN_ERROR;

    if( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    hal_ll_can_filter_init( map, filter_config );

    if( HAL_LL_CAN_ERROR == hal_ll_can_set_operation_mode( map, config->mode ))
        return HAL_LL_CAN_ERROR;

    return HAL_LL_CAN_SUCCESS;
}
// ------------------------------------------------------------------------- END
