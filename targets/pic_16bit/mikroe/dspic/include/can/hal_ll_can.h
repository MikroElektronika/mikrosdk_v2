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
 * @file  hal_ll_can.h
 * @brief API for CAN HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_CAN_H_
#define _HAL_LL_CAN_H_

#include "hal_ll_target.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief CAN low level pin config structure.
 *
 * The context structure for storing low level pin configuration.
 *
 */
typedef struct
{
    hal_ll_pin_name_t pin_name;
    uint8_t pin_pps;
} hal_ll_pin_pps_t;

/**
 * @brief CAN low level pins config structure.
 *
 * The context structure for storing low level pin configuration
 * for both TX and RX pins.
 *
 */
typedef struct
{
    hal_ll_pin_pps_t tx_pin; /*!< TX CAN pin. */
    hal_ll_pin_pps_t rx_pin; /*!< RX CAN pin. */
} hal_ll_can_pins_t;

/**
 * @details CAN modes.
 */
typedef enum
{
    /* Universal Modes. */
    HAL_LL_CAN_MODE_NORMAL = 0,        /*!< Mode for normal operation. */
    HAL_LL_CAN_MODE_LOOPBACK,          /*!< Mode for testing communication internally with sending TX data frames to other nodes. */
    HAL_LL_CAN_MODE_DISABLE,           /*!< Mode for ignoring TX and RX data frames. */
    /* STM32 and RISC-V Modes. */
    HAL_LL_CAN_MODE_SILENT,            /*!< Mode for only receiving messages. */
    HAL_LL_CAN_MODE_LOOPBACK_SILENT,   /*!< Mode for testing communication internally without sending TX data frames to other nodes. */
    /* NXP Modes. */
    HAL_LL_CAN_MODE_LISTENONLY,        /*!< Mode for only receiving messages. */
    HAL_LL_CAN_MODE_DOZE,              /*!< Mode for acknowledging system low-power mode. */
    HAL_LL_CAN_MODE_STOP,              /*!< Mode for acknowledging system clock stop. */
    HAL_LL_CAN_MODE_FREEZE,            /*!< Mode for ignoring TX and RX data frames. */
    /* dsPIC Modes. */
    HAL_LL_CAN_MODE_LISTENALL          /*!< Mode for receiving data frames without filter configs. */
} hal_ll_can_mode_t;

/**
 * @details CAN data frame formats.
 */
typedef enum
{
    HAL_LL_CAN_FRAME_FORMAT_STANDARD_11BITS = 0,  /*!< Standard format identifier. */
    HAL_LL_CAN_FRAME_FORMAT_EXTENDED_29BITS       /*!< Extended format identifier. */
} hal_ll_can_frame_format_t;

/**
 * @details CAN data frame types.
 */
typedef enum
{
    HAL_LL_CAN_FRAME_TYPE_DATA = 0,  /*!< Data frame. */
    HAL_LL_CAN_FRAME_TYPE_RTR        /*!< Remote frame. */
} hal_ll_can_frame_type_t;

/**
 * @details CAN filter mode.
 */
typedef enum
{
    HAL_LL_CAN_FILTER_MODE_IDMASK = 0,  /*!< Identifier mask mode. */
    HAL_LL_CAN_FILTER_MODE_IDLIST       /*!< Identifier list mode. */
} hal_ll_can_filter_mode_t;

/**
 * @details CAN filter scale.
 */
typedef enum
{
    HAL_LL_CAN_FILTER_SCALE_16BIT = 0,  /*!< Two 16-bit filters. */
    HAL_LL_CAN_FILTER_SCALE_32BIT       /*!< One 32-bit filter.  */
} hal_ll_can_filter_scale_t;

/**
 * @details CAN filter FIFO.
 */
typedef enum
{
    HAL_LL_CAN_FILTER_FIFO0 = 0,   /*!< Filter mapped to FIFO0. */
    HAL_LL_CAN_FILTER_FIFO1,       /*!< Filter mapped to FIFO1.  */
    HAL_LL_CAN_FILTER_FIFO2,       /*!< Filter mapped to FIFO2.  */
    HAL_LL_CAN_FILTER_FIFO3,       /*!< Filter mapped to FIFO3.  */
    HAL_LL_CAN_FILTER_FIFO4,       /*!< Filter mapped to FIFO4.  */
    HAL_LL_CAN_FILTER_FIFO5,       /*!< Filter mapped to FIFO5.  */
    HAL_LL_CAN_FILTER_FIFO6,       /*!< Filter mapped to FIFO6.  */
    HAL_LL_CAN_FILTER_FIFO7,       /*!< Filter mapped to FIFO7.  */
    HAL_LL_CAN_FILTER_FIFO8,       /*!< Filter mapped to FIFO8.  */
    HAL_LL_CAN_FILTER_FIFO9,       /*!< Filter mapped to FIFO9.  */
    HAL_LL_CAN_FILTER_FIFO10,      /*!< Filter mapped to FIFO10.  */
    HAL_LL_CAN_FILTER_FIFO11,      /*!< Filter mapped to FIFO11.  */
    HAL_LL_CAN_FILTER_FIFO12,      /*!< Filter mapped to FIFO12.  */
    HAL_LL_CAN_FILTER_FIFO13,      /*!< Filter mapped to FIFO13.  */
    HAL_LL_CAN_FILTER_FIFO14,      /*!< Filter mapped to FIFO14.  */
    HAL_LL_CAN_FILTER_FIFO15,      /*!< Filter mapped to FIFO15.  */
    HAL_LL_CAN_FILTER_FIFO16,      /*!< Filter mapped to FIFO16.  */
    HAL_LL_CAN_FILTER_FIFO17,      /*!< Filter mapped to FIFO17.  */
    HAL_LL_CAN_FILTER_FIFO18,      /*!< Filter mapped to FIFO18.  */
    HAL_LL_CAN_FILTER_FIFO19,      /*!< Filter mapped to FIFO19.  */
    HAL_LL_CAN_FILTER_FIFO20,      /*!< Filter mapped to FIFO20.  */
    HAL_LL_CAN_FILTER_FIFO21,      /*!< Filter mapped to FIFO21.  */
    HAL_LL_CAN_FILTER_FIFO22,      /*!< Filter mapped to FIFO22.  */
    HAL_LL_CAN_FILTER_FIFO23,      /*!< Filter mapped to FIFO23.  */
    HAL_LL_CAN_FILTER_FIFO24,      /*!< Filter mapped to FIFO24.  */
    HAL_LL_CAN_FILTER_FIFO25,      /*!< Filter mapped to FIFO25.  */
    HAL_LL_CAN_FILTER_FIFO26,      /*!< Filter mapped to FIFO26.  */
    HAL_LL_CAN_FILTER_FIFO27,      /*!< Filter mapped to FIFO27.  */
    HAL_LL_CAN_FILTER_FIFO28,      /*!< Filter mapped to FIFO28.  */
    HAL_LL_CAN_FILTER_FIFO29,      /*!< Filter mapped to FIFO29.  */
    HAL_LL_CAN_FILTER_FIFO30,      /*!< Filter mapped to FIFO30.  */
    HAL_LL_CAN_FILTER_FIFO31       /*!< Filter mapped to FIFO31.  */
} hal_ll_can_filter_fifo_t;

/**
 * @details CAN filter activation.
 */
typedef enum
{
    HAL_LL_CAN_FILTER_DISABLE = 0,  /*!< CAN filter disable. */
    HAL_LL_CAN_FILTER_ENABLE        /*!< CAN filter enable.  */
} hal_ll_can_filter_activation_t;

/**
 * @details CAN filter config structure.
 */
typedef struct
{
    union {
        struct {
            uint16_t can_filter_id_low;                /*!< 16-bit Filter ID. */
            uint16_t can_filter_id_high;               /*!< 16-bit Filter ID. */
        };
        uint32_t can_filter_id;                        /*!< 32-bit Filter ID. */
    };
    union {
        struct {
            uint16_t can_filter_mask_id_low;           /*!< 16-bit Filter ID or Filter Mask. */
            uint16_t can_filter_mask_id_high;          /*!< 16-bit Filter ID or Filter Mask. */
        };
        uint32_t can_filter_mask_id;                   /*!< 32-bit Filter ID or Filter Mask. */
    };
    uint8_t can_filter_bank;                           /*!< Filter bank. */
    hal_ll_can_frame_type_t can_filter_frame_type[4];  /*!< Type of frame, data or remote. */
    hal_ll_can_filter_activation_t can_filter_enable;  /*!< Filter activation status. */
    hal_ll_can_filter_mode_t can_filter_mode;          /*!< Filter mode. */
    hal_ll_can_filter_scale_t can_filter_scale;        /*!< Filter scale. */
    hal_ll_can_filter_fifo_t can_filter_fifo;          /*!< Filter-to-FIFO mapping. */
} hal_ll_can_filter_config_t;

/**
 * @details CAN module config structure.
 */
typedef struct
{
    hal_ll_pin_name_t tx_pin; /*!< Tx pin. */
    hal_ll_pin_name_t rx_pin; /*!< Rx pin. */
    hal_ll_can_mode_t mode;   /*!< CAN mode. */
    uint32_t frequency;       /*!< CAN frequency. */
} hal_ll_can_config_t;

/**
 * @details Message structure.
 */
typedef struct
{
    union {
        struct {
            uint16_t std_id;                          /*!< Standard format frame identifier. */
            uint16_t ext_id;                          /*!< Extended format frame identifier. */
        };
        uint32_t id;
    };
    hal_ll_can_frame_format_t frame_format;   /*!< Format of frame, standard or extended format. */
    hal_ll_can_frame_type_t frame_type;       /*!< Type of frame, data or remote. */
    uint8_t data_len;                      /*!< Data length. */
    uint8_t message_data[8];
} hal_ll_can_message_t;

/**
 * @details CAN HAL low level transmit message structure.
 */
typedef struct
{
    hal_ll_can_message_t message;  /* CAN message structure. */
} hal_ll_can_transmit_message_struct;

/**
 * @details CAN HAL low level receive message structure.
 */
typedef struct
{
    hal_ll_can_message_t message;  /* CAN message structure. */
    uint8_t rx_fifo_number;        /* Receive FIFO number. */
} hal_ll_can_receive_message_struct;

/**
 * @brief CAN low level handle.
 *
 * The context for storing low level object handler.
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    handle_t *hal_ll_can_handle;    /*!< CAN HAL low level handle */
    handle_t *hal_drv_can_handle;   /*!< CAN DRV level handle */
    bool init_ll_state;             /*!< CAN HAL low level object init state */
} hal_ll_can_handle_register_t;

/**
 * @brief Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param[in] tx_pin CAN TX pin.
 * @param[in] rx_pin CAN RX pin.
 * @param[in] *handle_map HAL layer local handle map.
 * @param[in] *hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_can_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                         hal_ll_can_handle_register_t *handle_map, uint8_t *hal_module_id );

/**
 * @brief Initializes specified module.
 *
 * Performs module configuration on the hardware
 * level. Enables module specific clock gate and
 * sets adequate alternate function values.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] config HAL low level config structure.
 * @param[in] filter_config HAL low level filter config structure.
 *
 * @return  hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_can_init( handle_t *handle, hal_ll_can_config_t *config,
                              hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Sets filter parameters.
 *
 * Initializes module with specified filter parameters.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] config HAL low level config structure.
 * @param[in] filter_config HAL low level filter config structure.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_can_set_filter( handle_t *handle, hal_ll_can_config_t *config,
                                    hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Sets adequate bit timing parameters for desired frequency.
 *
 * @note: Setting parameters that result in a baud rate that
 *        differs from the desired value is not acceptable.
 *        If two devices communicate over CAN, their baud
 *        rates need to be exactly the same.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] config HAL low level config structure.
 * @param[in] filter_config HAL low level filter config structure.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_can_set_frequency( handle_t *handle, hal_ll_can_config_t *config,
                                       hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Gets CAN frequency.
 *
 * Gets the currently configured CAN frequency.
 *
 * @param[in] handle HAL context object handle.
 *
 * Returns CAN frequency.
 */
hal_ll_err_t hal_ll_can_get_frequency( handle_t *handle );

/**
 * @brief Sets desired CAN operating mode.
 *
 * Initializes module with specified CAN mode.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] config HAL low level config structure.
 * @param[in] filter_config HAL low level filter config structure.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_can_set_mode( handle_t *handle, hal_ll_can_config_t *config,
                                  hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Gets CAN mode.
 *
 * Gets the currently configured CAN mode.
 *
 * @param[in] handle HAL context object handle.
 *
 * Returns CAN mode.
 */
hal_ll_err_t hal_ll_can_get_mode( handle_t *handle );

/**
 * @brief  Performs transmit operation.
 *
 * Accesses hardware transmit registers and
 * writes parameters and data directly to them.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] transmit_message Transmit message structure.
 *
 * Returns one of pre-defined values.
 */
hal_ll_err_t hal_ll_can_transmit( handle_t *handle, hal_ll_can_transmit_message_struct *transmit_message );

/**
 * @brief Stops transmit operation.
 *
 * Accesses hardware transmit registers and stops data transmission.
 *
 * @param[in] handle HAL context object handle.
 *
 * @return void None.
 */
void hal_ll_can_transmission_stop( handle_t *handle );

/**
 * @brief  Performs receive operation.
 *
 * Accesses hardware receive registers and
 * reads parameters and data directly from them.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] receive_message Receive message structure.
 *
 * Returns one of pre-defined values.
 */
hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message );

/**
 * @brief  Closes CAN HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param[in] *handle HAL context object handle.
 *
 * Returns one of pre-defined values.
 */
hal_ll_err_t hal_ll_can_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_H_
// ------------------------------------------------------------------------- END
