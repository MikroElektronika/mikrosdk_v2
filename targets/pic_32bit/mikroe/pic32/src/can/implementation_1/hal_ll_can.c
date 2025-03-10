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
 * @file  hal_ll_can.c
 * @brief CAN HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_pps.h"
#include "hal_ll_can.h"
#include "hal_ll_gpio.h"
#include "hal_ll_can_pin_map.h"
#include "hal_ll_pps.h"

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

/*!< @brief CAN register specific bits and masks. */
#define HAL_LL_CAN_CMSGEID_SRR_BIT           (5)
#define HAL_LL_CAN_CMSGEID_IDE_BIT           (4)
#define HAL_LL_CAN_CMSGEID_RTR_BIT           (1)

#define HAL_LL_CAN_CCON_CONFIGURATION_MODE   (0x4UL)
#define HAL_LL_CAN_CCON_LISTENONLY_MODE      (0x3UL)
#define HAL_LL_CAN_CCON_LOOPBACK_MODE        (0x2UL)
#define HAL_LL_CAN_CCON_DISABLE_MODE         (0x1UL)
#define HAL_LL_CAN_CCON_NORMAL_MODE          (0x0UL)
#define HAL_LL_CAN_CCON_ON_MASK              (0x8000UL)
#define HAL_LL_CAN_CCON_OPMOD_BIT_POS        (21)
#define HAL_LL_CAN_CCON_OPMOD_MASK           (0xE00000UL)
#define HAL_LL_CAN_CCON_REQOP_BIT_POS        (24)
#define HAL_LL_CAN_CCON_REQOP_MASK           (0x07000000UL)

#define HAL_LL_CAN_MESSAGE_RAM_CONFIG_SIZE   (2U)

#define HAL_LL_CAN_CCFG_PRSEG_BIT_POS        (8)
#define HAL_LL_CAN_CCFG_SEG1PH_BIT_POS       (11)
#define HAL_LL_CAN_CCFG_SEG2PH_BIT_POS       (16)
#define HAL_LL_CAN_CCFG_SJW_BIT_POS          (6)
#define HAL_LL_CAN_CCFG_SEG2PHTS_MASK        (0x8000UL)
#define HAL_LL_CAN_CCFG_PRSEG_MAX_VAL        (8)
#define HAL_LL_CAN_CCFG_SEG1PH_MAX_VAL       (8)
#define HAL_LL_CAN_CCFG_SEG2PH_MAX_VAL       (8)
#define HAL_LL_CAN_CCFG_PRESCALER_MAX_VAL    (64)
#define HAL_LL_CAN_NUM_OF_TIME_QUANTA_MAX    (25)
#define HAL_LL_CAN_NUM_OF_TIME_QUANTA_MIN    (8)
#define HAL_LL_CAN_CCFG_SJW_CONST_VALUE      (1)

#define HAL_LL_CAN_CFIFOCONN_FSIZE_BIT_POS   (16)
#define HAL_LL_CAN_CFIFOCONN_FSIZE_MASK      (0x1F0000UL)
#define HAL_LL_CAN_CFIFOCONN_FSIZE_DEPTH_0   (0x0UL)
#define HAL_LL_CAN_CFIFOCONN_RTREN_BIT_POS   (2)
#define HAL_LL_CAN_CFIFOCONN_RTREN_MASK      (0x4)
#define HAL_LL_CAN_CFIFOCONN_TXEN_MASK       (0x80UL)
#define HAL_LL_CAN_CFIFOCONN_TXPRI_BIT_POS   (0)
#define HAL_LL_CAN_CFIFOCONN_TXPRI_MASK      (0x3UL)
#define HAL_LL_CAN_CFIFOCONN_TXREQ_MASK      (0x8UL)
#define HAL_LL_CAN_CFIFOCONN_UINC_MASK       (0x2000UL)
#define HAL_LL_CAN_CFLTCONN_FLTEN0_MASK      (0x80UL)
#define HAL_LL_CAN_CFLTCONN_FLTEN_ENABLE     (0x1UL)

#define HAL_LL_CAN_CFLTCONN_FSEL0_BIT_POS    (0)
#define HAL_LL_CAN_CFLTCONN_FSEL_MASK        (0x1FUL)
#define HAL_LL_CAN_CFLTCONN_MSEL0_BIT_POS    (5)
#define HAL_LL_CAN_CFLTCONN_MSEL_MASK        (0x3UL)

#define HAL_LL_CAN_CRXFN_SID_BIT_POS         (21)
#define HAL_LL_CAN_CRXMN_SID_BIT_POS         (21)

#define HAL_LL_CAN_NUM_OF_MASKS              (4)

#define HAL_LL_CAN_TRANSMIT_FIFO_NUM         (0)

#define HAL_LL_CAN_CFIFOCON_TXPR_LOWEST      (0x0UL)
#define HAL_LL_CAN_CFIFOCON_TXPR_LOW         (0x1UL)
#define HAL_LL_CAN_CFIFOCON_TXPR_HIGH        (0x2UL)
#define HAL_LL_CAN_CFIFOCON_TXPR_HIGHEST     (0x3UL)

#define HAL_LL_CAN_CFIFOCON_AUTORTR_ENABLE   (0x1UL)
#define HAL_LL_CAN_CFIFOCON_AUTORTR_DISABLE  (0x0UL)

#define HAL_LL_CAN_EID_BITS_17_0             (0x3FFFFUL)
#define HAL_LL_CAN_EID_BITS_28_18            (0x3FFC0000UL)
#define HAL_LL_CAN_SID_BITS_10_0             (0xFFE00000UL)
#define HAL_LL_CAN_EID_BITS_28_11            (0x3FFFF800UL)

#define HAL_LL_CAN_SID_EXTENSION_SHIFT       (3UL)

#define HAL_LL_CAN_CMSGEID_EID_SHIFT         (10UL)
#define HAL_LL_CAN_CMSGEID_DLC_MASK          (0xFUL)
#define HAL_LL_CAN_CMSGEID_EID_MASK          (0xFFFFC00UL)

#define HAL_LL_CAN_SID_MASK                  (0x7FFUL)
#define HAL_LL_CAN_SID_SHIFT                 (11UL)

#define HAL_LL_CAN_MASK_NOT_FOUND            (0xFUL)

#define HAL_LL_CAN_TIMEOUT_VALUE             (10000UL)

typedef unsigned long hal_ll_can_paddr_t; /* a physical address */
typedef unsigned long hal_ll_can_vaddr_t; /* a virtual address */

/*
 * Translate a kernel virtual address in KSEG0 or KSEG1 to a real
 * physical address and back.
 */
#define KVA_TO_PA(v) 	((hal_ll_can_paddr_t)(v) & 0x1FFFFFFFUL)
#define PA_TO_KVA1(pa)	((void *) ((pa) | 0xA0000000UL ))

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

/*!< @brief Macros used for pin/port manipulation */
#define pin_mask 0x0F
#define port_mask 0xF0
#define hal_ll_pin(port_name) (port_name & pin_mask)
#define hal_ll_port(port_name) ((port_name & port_mask) >> 4)

typedef struct
{
    hal_ll_base_addr_t reg;
    hal_ll_base_addr_t clr;
    hal_ll_base_addr_t set;
    hal_ll_base_addr_t inv;
} hal_ll_can_reg_op_t;

/*!< @brief CAN FIFO registers structure */
typedef struct
{
    hal_ll_can_reg_op_t cfifoconn;
    hal_ll_can_reg_op_t cfifointn;
    hal_ll_can_reg_op_t cfifouan;
    hal_ll_can_reg_op_t cfifocin;
} hal_ll_can_fifo_structure_t;

/*!< @brief CAN HW register structure */
typedef struct
{
    hal_ll_can_reg_op_t ccon;
    hal_ll_can_reg_op_t ccfg;
    hal_ll_can_reg_op_t cint;
    hal_ll_can_reg_op_t cvec;
    hal_ll_can_reg_op_t ctrec;
    hal_ll_can_reg_op_t cfstat;
    hal_ll_can_reg_op_t crxovf;
    hal_ll_can_reg_op_t ctmr;
    hal_ll_can_reg_op_t crxm[4];
    hal_ll_can_reg_op_t cfltcon[8];
    hal_ll_can_reg_op_t crxfn[32];
    hal_ll_can_reg_op_t cfifoba;
    hal_ll_can_fifo_structure_t cfifo[32];
} hal_ll_can_base_handle_t;

/*!< @brief CAN transmit message buffer structure - CMSGSID */
typedef struct
{
    union {
        struct {
            uint8_t byte0; // SID[7:0]
            uint8_t byte1; // RES RES RES RES SID[10:8]
            uint8_t byte2; // RES RES RES RES RES RES RES
            uint8_t byte3; // RES RES RES RES RES RES RES
        };
        uint32_t cmsgsid_word;
    };
} hal_ll_can_tx_buffer_cmsgsid_t;

/*!< @brief CAN transmit message buffer structure - CMSGEID */
typedef struct
{
    union {
        struct {
            uint8_t byte0; // RES RES RES RB0 DLC[3:0]
            uint8_t byte1; // EID[5:0] RTR RB1
            uint8_t byte2; // EID[13:6]
            uint8_t byte3; // RES RES SRR IDE EID[17:14]
        };
        uint32_t cmsgeid_word;
    };
} hal_ll_can_tx_buffer_cmsgeid_t;

/*!< @brief CAN transmit message buffer structure */
typedef struct
{
    hal_ll_can_tx_buffer_cmsgsid_t cmsgsid;
    hal_ll_can_tx_buffer_cmsgeid_t cmsgeid;
    uint8_t cmsgdata_byte[8];
} hal_ll_can_tx_buffer_structure_t;

/*!< @brief CAN receive message buffer structure - CMSGSID */
typedef struct
{
    union {
        struct {
            uint8_t byte0; // SID[7:0]
            uint8_t byte1; // FILHIT[4:0] SID[10:8]
            uint8_t byte2; // CMSGTS[7:0]
            uint8_t byte3; // CMSGTS[15:8]
        };
        uint32_t cmsgsid_word;
    };
} hal_ll_can_rx_buffer_cmsgsid_t;

/*!< @brief CAN receive message buffer structure - CMSGEID */
typedef struct
{
    union {
        struct {
            uint8_t byte0; // RES RES RES RB0 DLC[3:0]
            uint8_t byte1; // EID[5:0] RTR RB1
            uint8_t byte2; // EID[13:6]
            uint8_t byte3; // RES RES SRR IDE EID[17:14]
        };
        uint32_t cmsgeid_word;
    };
} hal_ll_can_rx_buffer_cmsgeid_t;

/*!< @brief CAN receive message buffer structure */
typedef struct
{
    hal_ll_can_rx_buffer_cmsgsid_t cmsgsid;
    hal_ll_can_rx_buffer_cmsgeid_t cmsgeid;
    uint8_t cmsgdata_byte[8];
} hal_ll_can_rx_buffer_structure_t;

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
    { HAL_LL_CAN1_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_CAN_MODE_NORMAL, 125000 },
    #endif
    #ifdef CAN_MODULE_2
    { HAL_LL_CAN2_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_2 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_CAN_MODE_NORMAL, 125000 },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_CAN_MODE_NORMAL, 125000 }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_can_handle_register_t *low_level_handle;
static volatile hal_ll_can_hw_specifics_map_t *hal_ll_can_hw_specifics_map_local;
static volatile hal_ll_can_tx_buffer_structure_t can_message_buffer[HAL_LL_CAN_MESSAGE_RAM_CONFIG_SIZE];
static volatile uint8_t num_of_assigned_masks = 0; // Number of assigned acceptance masks. Maximum number of masks is 4.

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
 * @param[in]  default_config - Flag indicating if filters are being set from can_filter_configure_default or not.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config );

/**
 * @brief  Set PPS state.
 *
 * Sets adequate RPINRx and RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Sets CAN operating mode.
 *
 * Sets OPMOD field in the CAN control register, then waits for
 * adequate value in REQOP to be set by hardware.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  map - CAN mode to be set.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_can_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_can_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_can_pin_id index_list[CAN_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( HAL_LL_PIN_NC == (pin_check_result = hal_ll_can_check_pins( tx_pin, rx_pin, &index_list, handle_map ))) {
        return HAL_LL_CAN_WRONG_PINS;
    };

    if ( (hal_ll_can_hw_specifics_map[pin_check_result].pins.tx_pin != tx_pin) ||
         (hal_ll_can_hw_specifics_map[pin_check_result].pins.rx_pin != rx_pin) )
    {
        #if HAL_LL_CAN_PPS_ENABLED == true
        if ( HAL_LL_CAN_SUCCESS != hal_ll_pps_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], false ))
            return HAL_LL_CAN_WRONG_PINS;
        #endif

        hal_ll_can_map_pins( pin_check_result, &index_list );

        // Used only for chips which have CAN PPS pins
        #if HAL_LL_CAN_PPS_ENABLED == true
        if ( HAL_LL_CAN_SUCCESS != hal_ll_pps_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], true ))
            return HAL_LL_CAN_WRONG_PINS;
        #endif
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
    hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_local, filter_config, false );

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
    uint8_t count = 0;

    hal_ll_can_tx_buffer_structure_t *transmit_message_buffer = NULL;

    transmit_message_buffer = ( hal_ll_can_tx_buffer_structure_t * )PA_TO_KVA1( hal_ll_hw_reg->cfifo[HAL_LL_CAN_TRANSMIT_FIFO_NUM].cfifouan.reg );

    if ( HAL_LL_CAN_FRAME_FORMAT_STANDARD_11BITS == transmit_message->message.frame_format ) {
        transmit_message_buffer->cmsgsid.cmsgsid_word = transmit_message->message.std_id & HAL_LL_CAN_SID_MASK;
        transmit_message_buffer->cmsgeid.cmsgeid_word = 0;
    } else {
        transmit_message_buffer->cmsgsid.cmsgsid_word = transmit_message->message.ext_id & HAL_LL_CAN_EID_BITS_28_18;
        transmit_message_buffer->cmsgeid.cmsgeid_word = ( transmit_message->message.ext_id & HAL_LL_CAN_EID_BITS_17_0 ) <<
                                                        HAL_LL_CAN_CMSGEID_EID_SHIFT;

        set_reg_bit( &transmit_message_buffer->cmsgeid.byte3, HAL_LL_CAN_CMSGEID_SRR_BIT ); // Set SRR bit
        set_reg_bit( &transmit_message_buffer->cmsgeid.byte3, HAL_LL_CAN_CMSGEID_IDE_BIT ); // Set IDE bit
    }

    if ( HAL_LL_CAN_FRAME_TYPE_RTR == transmit_message->message.frame_type ) {
        set_reg_bit( &transmit_message_buffer->cmsgeid.byte1, HAL_LL_CAN_CMSGEID_RTR_BIT ); // Set RTR bit
    } else {
        if ( 8U < transmit_message->message.data_len )
            transmit_message->message.data_len = 8U;

        transmit_message_buffer->cmsgeid.byte0 = transmit_message->message.data_len & HAL_LL_CAN_CMSGEID_DLC_MASK;

        while( count < transmit_message->message.data_len )
            transmit_message_buffer->cmsgdata_byte[count++] = transmit_message->message.message_data[count];
    }

    /* Request the transmit */
    hal_ll_hw_reg->cfifo[HAL_LL_CAN_TRANSMIT_FIFO_NUM].cfifoconn.set = HAL_LL_CAN_CFIFOCONN_UINC_MASK;
    hal_ll_hw_reg->cfifo[HAL_LL_CAN_TRANSMIT_FIFO_NUM].cfifoconn.set = HAL_LL_CAN_CFIFOCONN_TXREQ_MASK;

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint32_t fifonum = 0;

    for( fifonum = 0; fifonum < 32; fifonum++ ) {
        hal_ll_hw_reg->cfifo[fifonum].cfifoconn.clr = HAL_LL_CAN_CFIFOCONN_TXREQ_MASK;
    }
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = ( hal_ll_can_base_handle_t *)hal_ll_can_hw_specifics_map_local->base;
    uint8_t count = 0, fifo_num = 0;

    hal_ll_can_rx_buffer_structure_t *receive_message_buffer = NULL;

    fifo_num = receive_message->rx_fifo_number;
    /* Get a pointer to RX message buffer */
    receive_message_buffer = (hal_ll_can_rx_buffer_structure_t *)PA_TO_KVA1( hal_ll_hw_reg->cfifo[fifo_num].cfifouan.reg );

    if ( !( receive_message_buffer->cmsgeid.byte3 & HAL_LL_CAN_CMSGEID_IDE_BIT ) ) {
        // Extended ID
        uint32_t eid_filter_mask = 0;
        uint32_t sid_filter_mask = 0;

        eid_filter_mask = ( receive_message_buffer->cmsgeid.cmsgeid_word & HAL_LL_CAN_CMSGEID_EID_MASK ) >> HAL_LL_CAN_CMSGEID_EID_SHIFT;
        sid_filter_mask = receive_message_buffer->cmsgsid.cmsgsid_word & HAL_LL_CAN_SID_MASK;

        receive_message->message.ext_id = eid_filter_mask << HAL_LL_CAN_SID_SHIFT | sid_filter_mask;

        if ( !( receive_message_buffer->cmsgeid.byte1 & HAL_LL_CAN_CMSGEID_RTR_BIT ) )
            receive_message->message.frame_type = HAL_LL_CAN_FRAME_TYPE_RTR;
        else
            receive_message->message.frame_type = HAL_LL_CAN_FRAME_TYPE_DATA;
    } else {
        // Standard ID
        receive_message->message.std_id = receive_message_buffer->cmsgsid.cmsgsid_word & HAL_LL_CAN_SID_MASK;

        if( !( receive_message_buffer->cmsgeid.byte3 & HAL_LL_CAN_CMSGEID_SRR_BIT ))
            receive_message->message.frame_type = HAL_LL_CAN_FRAME_TYPE_RTR;
        else
            receive_message->message.frame_type = HAL_LL_CAN_FRAME_TYPE_DATA;
    }

    receive_message->message.data_len = (uint8_t)( receive_message_buffer->cmsgeid.byte0 & HAL_LL_CAN_CMSGEID_DLC_MASK );

    /* Copy read data. */
    while ( count < receive_message->message.data_len )
        receive_message->message.message_data[count++] = receive_message_buffer->cmsgdata_byte[count];

    /* Message processing is done, update the message buffer pointer. */
    hal_ll_hw_reg->cfifo[fifo_num].cfifoconn.set = HAL_LL_CAN_CFIFOCONN_UINC_MASK;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_close( handle_t *handle ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);

    if( low_level_handle->hal_ll_can_handle != NULL ) {
        hal_ll_can_hw_specifics_map_local->pins.tx_pin = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin = HAL_LL_PIN_NC;

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
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin = hal_ll_can_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin = hal_ll_can_rx_map[ index_list[module_index].pin_rx ].pin;
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
    uint8_t prescaler = 0, pseg1 = 0, pseg2 = 0;
    uint8_t sjw = 0, prseg = 0;
    uint32_t baud_rate = 0, can_clock = 0;
    float bit_time = 0, temp = 0, can_clock_float;
    uint32_t actual_baud_rate = 0;

    /*
     * Description: This code snippet searches for optimal parameters for configuring
     * the CAN bus baud rate on PIC32 microcontrollers, based on the provided parameters.
     *
     * Initial parameters:
     * - can_clock: CAN source clock frequency in Hz.
     * - baud_rate: Desired CAN bus baud rate.
     *
     * Calculated parameters:
     * - sjw is set to 1 to ensure communication stability
     * - prescaler: The prescaler value to achieve the desired baud rate.
     * - prseg: Propagation delay that compensates for any time delay that may occur.
     * - pseg1, pseg2: Time segment values for configuring the CAN bus.
     *
     * Formulas used:
     * - can_clock = Fosc [MHz] - input frequency to CAN module
     * - actual_baud_rate = can_clock / (2 * prescaler * (sjw + prseg + pseg1 + pseg2)) - baud rate that we are trying to achieve
     */

    baud_rate = map->frequency;

    #ifdef PIC32MXxx
    can_clock = Get_Fosc_kHz() * 1000;
    #else
    // CAN is clocked from PBCLK5 = SYSCLK / 2
    can_clock = Get_Fosc_kHz() * 1000 / 2;
    #endif

    sjw = HAL_LL_CAN_CCFG_SJW_CONST_VALUE;

    for( prescaler = 1; prescaler <= HAL_LL_CAN_CCFG_PRESCALER_MAX_VAL; prescaler++ ) {
        for( pseg1 = 1; pseg1 <= HAL_LL_CAN_CCFG_SEG1PH_MAX_VAL; pseg1++ ) {
            for( pseg2 = 2; pseg2 <= HAL_LL_CAN_CCFG_SEG2PH_MAX_VAL; pseg2++ ) {
                for ( prseg = 1; prseg <= HAL_LL_CAN_CCFG_PRSEG_MAX_VAL; prseg++ ) {
                    temp = pseg1 + pseg2 + sjw + prseg;

                    if( HAL_LL_CAN_NUM_OF_TIME_QUANTA_MIN > (uint8_t)temp || HAL_LL_CAN_NUM_OF_TIME_QUANTA_MAX < (uint8_t)temp ||
                        ( ( prseg + pseg1 ) < pseg2 ) )
                        continue;

                    temp *= 2 * prescaler;
                    actual_baud_rate = ( can_clock / temp );
                    if( actual_baud_rate == baud_rate ) {
                        // Exact match found
                        uint32_t prseg_val = ((uint32_t)(prseg - 1)) << HAL_LL_CAN_CCFG_PRSEG_BIT_POS;
                        uint32_t sjw_val = ((uint32_t)(sjw - 1)) << HAL_LL_CAN_CCFG_SJW_BIT_POS;
                        uint32_t pseg1_val = ((uint32_t)(pseg1 - 1)) << HAL_LL_CAN_CCFG_SEG1PH_BIT_POS;
                        uint32_t pseg2_val = ((uint32_t)(pseg2 - 1)) << HAL_LL_CAN_CCFG_SEG2PH_BIT_POS;
                        uint32_t prescaler_val = prescaler - 1;

                        hal_ll_hw_reg->ccfg.reg = prescaler_val | pseg1_val | pseg2_val | sjw_val | prseg_val | HAL_LL_CAN_CCFG_SEG2PHTS_MASK;

                        return HAL_LL_CAN_SUCCESS;
                    }
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

    /* Switch the CAN module ON */
    hal_ll_hw_reg->ccon.set = HAL_LL_CAN_CCON_ON_MASK;

    if ( HAL_LL_CAN_ERROR == ( result = hal_ll_can_set_operation_mode( map, HAL_LL_CAN_MODE_CONFIGURATION )))
        return result;

    if ( HAL_LL_CAN_ERROR == ( result = hal_ll_can_bit_timing( map )))
        return result;

    /* Set FIFO base address for all message buffers */
    hal_ll_hw_reg->cfifoba.reg = (uint32_t)KVA_TO_PA(can_message_buffer);

    // Set FIFO0 to be used for transmitting
    hal_ll_hw_reg->cfifo[HAL_LL_CAN_TRANSMIT_FIFO_NUM].cfifoconn.reg =
                            (( HAL_LL_CAN_CFIFOCONN_FSIZE_DEPTH_0 << HAL_LL_CAN_CFIFOCONN_FSIZE_BIT_POS) & HAL_LL_CAN_CFIFOCONN_FSIZE_MASK ) |
                            (( HAL_LL_CAN_CFIFOCON_TXPR_LOWEST << HAL_LL_CAN_CFIFOCONN_TXPRI_BIT_POS) & HAL_LL_CAN_CFIFOCONN_TXPRI_MASK ) |
                            (( HAL_LL_CAN_CFIFOCON_AUTORTR_DISABLE << HAL_LL_CAN_CFIFOCONN_RTREN_BIT_POS) & HAL_LL_CAN_CFIFOCONN_RTREN_MASK ) |
                            HAL_LL_CAN_CFIFOCONN_TXEN_MASK;

    return result;
}

static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint32_t fsel_pos = 0, msel_pos = 0, flten_pos = 0, filter_reg = 0, current_mask = 0, masks[HAL_LL_CAN_NUM_OF_MASKS];

    uint32_t filter_number = filter_config->can_filter_bank;
    uint8_t mask_to_be_used = HAL_LL_CAN_MASK_NOT_FOUND, arr_position = 0;

    if( !default_config ) {
        // Set user defined FIFO to be used for receiving
        hal_ll_hw_reg->cfifo[filter_config->can_filter_fifo].cfifoconn.reg =
                                    ( HAL_LL_CAN_CFIFOCONN_FSIZE_DEPTH_0 << HAL_LL_CAN_CFIFOCONN_FSIZE_BIT_POS ) &
                                    HAL_LL_CAN_CFIFOCONN_FSIZE_MASK;
        /* Configure CAN Filters */
        if( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_11 ) {
            // Extended ID
            hal_ll_hw_reg->crxfn[filter_number].reg =
                            ( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_17_0 ) |
                            (( filter_config->can_filter_id & HAL_LL_CAN_EID_BITS_28_18 ) << HAL_LL_CAN_SID_EXTENSION_SHIFT );
        } else {
            // Standard ID
            hal_ll_hw_reg->crxfn[filter_number].reg = ( filter_config->can_filter_id & HAL_LL_CAN_SID_MASK ) << HAL_LL_CAN_CRXFN_SID_BIT_POS;
        }

        current_mask = filter_config->can_filter_mask_id;

        for( arr_position = 0; arr_position < HAL_LL_CAN_NUM_OF_MASKS; arr_position++ ) {
            if( hal_ll_hw_reg->crxm[arr_position].reg & HAL_LL_CAN_EID_BITS_17_0 ) {
                // Extended ID.
                masks[arr_position] = ( hal_ll_hw_reg->crxm[arr_position].reg & HAL_LL_CAN_EID_BITS_17_0 ) |
                        (( hal_ll_hw_reg->crxm[arr_position].reg & HAL_LL_CAN_SID_BITS_10_0 ) >> HAL_LL_CAN_SID_EXTENSION_SHIFT );
            } else {
                // Standard ID.
                masks[arr_position] = hal_ll_hw_reg->crxm[arr_position].reg & HAL_LL_CAN_SID_BITS_10_0 >> HAL_LL_CAN_CRXMN_SID_BIT_POS;
            }
        }

        for( arr_position = 0; arr_position < HAL_LL_CAN_NUM_OF_MASKS; arr_position++ ) {
            if( masks[arr_position] == current_mask ) {
                mask_to_be_used = arr_position;
                break;
            }
        }

        // If desired mask has not been assigned yet
        if( HAL_LL_CAN_MASK_NOT_FOUND == mask_to_be_used ) {
            // If the number of assigned masks so far is less than maximum
            if( HAL_LL_CAN_NUM_OF_MASKS > num_of_assigned_masks ) {
                masks[num_of_assigned_masks] = current_mask;
                mask_to_be_used = num_of_assigned_masks;
                num_of_assigned_masks++;
            } else if ( HAL_LL_CAN_NUM_OF_MASKS <= num_of_assigned_masks )
                // Maximum number of masks set. Return error.
                return HAL_LL_CAN_ERROR;
        }

        /* Configure CAN Acceptance Filter Masks */
        for( arr_position = 0; arr_position < HAL_LL_CAN_NUM_OF_MASKS; arr_position++ ) {
            if( masks[arr_position] & HAL_LL_CAN_EID_BITS_28_11 ) {
                // Extended ID.
                hal_ll_hw_reg->crxm[arr_position].reg = (( masks[arr_position] & HAL_LL_CAN_EID_BITS_28_18 ) << HAL_LL_CAN_SID_EXTENSION_SHIFT ) |
                                            ( masks[arr_position] & HAL_LL_CAN_EID_BITS_17_0 );
            } else {
                // Standard ID.
                hal_ll_hw_reg->crxm[arr_position].reg = masks[arr_position] & HAL_LL_CAN_SID_MASK << HAL_LL_CAN_CRXMN_SID_BIT_POS;
            }
        }

        // CiFLTCON0 includes settings for filters 0 to 3, while CiFLTCON1 covers filters 4 to 7 and so on. i = 0...7
        fsel_pos = filter_number % 4 * 8; // Possible positions: 0, 8, 16, 24.
        msel_pos = filter_number % 4 * 8 + 5; // Possible positions: 5, 13, 31, 29.
        flten_pos = filter_number % 4 * 8 + 7; // Possible positions: 7, 15, 23, 31.
        filter_reg = filter_number / 4; // Possible values: 0 to 7.

        hal_ll_hw_reg->cfltcon[filter_reg].set = (( filter_config->can_filter_fifo << fsel_pos ) & HAL_LL_CAN_CFLTCONN_FSEL_MASK << fsel_pos ) |
                                                 ((( uint32_t ) mask_to_be_used << msel_pos ) & HAL_LL_CAN_CFLTCONN_MSEL_MASK << msel_pos ) |
                                                 ( uint32_t ) HAL_LL_CAN_CFLTCONN_FLTEN_ENABLE << flten_pos;
    }

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_mode_t mode ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    hal_ll_can_mode_t set_mode = mode;
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    switch( mode ) {
        case HAL_LL_CAN_MODE_CONFIGURATION:
            set_mode = HAL_LL_CAN_CCON_CONFIGURATION_MODE;
            break;
        case HAL_LL_CAN_MODE_LISTENONLY:
            set_mode = HAL_LL_CAN_CCON_LISTENONLY_MODE;
            break;
        case HAL_LL_CAN_MODE_LOOPBACK:
            set_mode = HAL_LL_CAN_CCON_LOOPBACK_MODE;
            break;
        case HAL_LL_CAN_MODE_NORMAL:
            set_mode = HAL_LL_CAN_CCON_NORMAL_MODE;
            break;
        case HAL_LL_CAN_MODE_DISABLE:
            set_mode = HAL_LL_CAN_CCON_DISABLE_MODE;
            break;

        default:
            return HAL_LL_CAN_ERROR;
    }

    hal_ll_hw_reg->ccon.reg &= ~HAL_LL_CAN_CCON_REQOP_MASK;
    hal_ll_hw_reg->ccon.reg |= (( uint32_t )set_mode << HAL_LL_CAN_CCON_REQOP_BIT_POS ) & HAL_LL_CAN_CCON_REQOP_MASK;
    while ((( hal_ll_hw_reg->ccon.reg & HAL_LL_CAN_CCON_OPMOD_MASK ) >> HAL_LL_CAN_CCON_OPMOD_BIT_POS ) != ( uint32_t )set_mode ) {
        if ( !timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_CAN_SUCCESS;

    if (( map->pins.tx_pin != HAL_LL_PIN_NC ) && ( map->pins.rx_pin != HAL_LL_PIN_NC )) {
        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.tx_pin ), hal_ll_pin( map->pins.tx_pin ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_CAN, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_CAN_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.rx_pin ), hal_ll_pin( map->pins.rx_pin ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_CAN, map->module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_CAN_SUCCESS;
    }
}

static void hal_ll_can_hw_ansel_set( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_gpio_pin_t local_pin;

    /*
     * Configures TX and RX pins as output/input by clearing/setting
     * corresponding TRIS bits.
     */
    hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
    hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin, HAL_LL_GPIO_DIGITAL_INPUT );
}


static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_hw_ansel_set( map );

    #if HAL_LL_CAN_PPS_ENABLED == true
    hal_ll_pps_set_state( map, true );
    #endif

    if( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    if( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( map, filter_config, true ))
        return HAL_LL_CAN_ERROR;

    hal_ll_can_set_operation_mode( map, config->mode );

    return HAL_LL_CAN_SUCCESS;
}
// ------------------------------------------------------------------------- END
