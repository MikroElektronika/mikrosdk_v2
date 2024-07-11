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
 * @file  drv_can.h
 * @brief API for CAN driver.
 */

#ifndef _DRV_CAN_H_
#define _DRV_CAN_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_can.h"

#define CAN_FILTER_FIFO_DEFAULT HAL_CAN_FILTER_FIFO_DEFAULT
#define CAN_FILTER_BANK_DEFAULT HAL_CAN_FILTER_BANK_DEFAULT

/**
 * @details Return values.
 */
typedef enum
{
    CAN_SUCCESS = 0,  /*!< Success. */
    CAN_ERROR = (-1)  /*!< Error. */
} can_err_t;

/**
 * @details CAN modes.
 */
typedef enum
{
    /* Universal Modes. */
    CAN_MODE_NORMAL = 0,        /*!< Mode for normal operation. */
    CAN_MODE_LOOPBACK,          /*!< Mode for testing communication internally with sending TX data frames to other nodes. */
    CAN_MODE_DISABLE,           /*!< Mode for ignoring TX and RX data frames - ARM specific. */
    /* STM32 and RISC-V Modes. */
    CAN_MODE_SILENT,            /*!< Mode for only receiving messages - ARM specific. */
    CAN_MODE_LOOPBACK_SILENT,   /*!< Mode for testing communication internally without sending TX data frames to other nodes. */
    /* NXP Modes. */
    CAN_MODE_LISTENONLY,        /*!< Mode for only receiving messages - NXP specific. */
    CAN_MODE_DOZE,              /*!< Mode for acknowledging system low-power mode. */
    CAN_MODE_STOP,              /*!< Mode for acknowledging system clock stop. */
    CAN_MODE_FREEZE,            /*!< Mode for ignoring TX and RX data frames - NXP specific. */
    /* dsPIC Modes.*/
    CAN_MODE_LISTENALL,         /*!< Mode for receiving data frames without filter configs. */
    /* PIC/PIC32 Modes. */
    CAN_MODE_CONFIGURATION      /*!< Mode for configuring CAN module. */
} can_mode_t;

/**
 * @details CAN states.
 */
typedef enum
{
    CAN_STATE_RESET = 0,    /*!< Reset state of CAN. */
    CAN_STATE_READY,        /*!< Ready state of CAN. */
    CAN_STATE_LISTENING,    /*!< Listening state of CAN.*/
    CAN_STATE_ERROR         /*!< Error state of CAN. */
} can_state_t;

/**
 * @details CAN data frame formats.
 */
typedef enum
{
    CAN_FRAME_FORMAT_STANDARD_11BITS = 0,  /*!< Standard format identifier. */
    CAN_FRAME_FORMAT_EXTENDED_29BITS       /*!< Extended format identifier. */
} can_frame_format_t;

/**
 * @details CAN data frame types
 */
typedef enum
{
    CAN_FRAME_TYPE_DATA = 0,  /*!< Data frame. */
    CAN_FRAME_TYPE_RTR        /*!< Remote frame. */
} can_frame_type_t;

/**
 * @details CAN filter mode.
 */
typedef enum
{
    CAN_FILTER_MODE_IDMASK = 0,  /*!< Identifier mask mode. */
    CAN_FILTER_MODE_IDLIST       /*!< Identifier list mode. */
} can_filter_mode_t;

/**
 * @details CAN filter scale.
 */
typedef enum
{
    CAN_FILTER_SCALE_16BIT = 0,  /*!< Two 16-bit filters. */
    CAN_FILTER_SCALE_32BIT       /*!< One 32-bit filter.  */
} can_filter_scale_t;

/**
 * @details CAN filter FIFO.
 */
typedef enum
{
    CAN_FILTER_FIFO0 = 0,   /*!< Filter mapped to FIFO0. */
    CAN_FILTER_FIFO1,       /*!< Filter mapped to FIFO1.  */
    CAN_FILTER_FIFO2,       /*!< Filter mapped to FIFO2.  */
    CAN_FILTER_FIFO3,       /*!< Filter mapped to FIFO3.  */
    CAN_FILTER_FIFO4,       /*!< Filter mapped to FIFO4.  */
    CAN_FILTER_FIFO5,       /*!< Filter mapped to FIFO5.  */
    CAN_FILTER_FIFO6,       /*!< Filter mapped to FIFO6.  */
    CAN_FILTER_FIFO7,       /*!< Filter mapped to FIFO7.  */
    CAN_FILTER_FIFO8,       /*!< Filter mapped to FIFO8.  */
    CAN_FILTER_FIFO9,       /*!< Filter mapped to FIFO9.  */
    CAN_FILTER_FIFO10,      /*!< Filter mapped to FIFO10.  */
    CAN_FILTER_FIFO11,      /*!< Filter mapped to FIFO11.  */
    CAN_FILTER_FIFO12,      /*!< Filter mapped to FIFO12.  */
    CAN_FILTER_FIFO13,      /*!< Filter mapped to FIFO13.  */
    CAN_FILTER_FIFO14,      /*!< Filter mapped to FIFO14.  */
    CAN_FILTER_FIFO15,      /*!< Filter mapped to FIFO15.  */
    CAN_FILTER_FIFO16,      /*!< Filter mapped to FIFO16.  */
    CAN_FILTER_FIFO17,      /*!< Filter mapped to FIFO17.  */
    CAN_FILTER_FIFO18,      /*!< Filter mapped to FIFO18.  */
    CAN_FILTER_FIFO19,      /*!< Filter mapped to FIFO19.  */
    CAN_FILTER_FIFO20,      /*!< Filter mapped to FIFO20.  */
    CAN_FILTER_FIFO21,      /*!< Filter mapped to FIFO21.  */
    CAN_FILTER_FIFO22,      /*!< Filter mapped to FIFO22.  */
    CAN_FILTER_FIFO23,      /*!< Filter mapped to FIFO23.  */
    CAN_FILTER_FIFO24,      /*!< Filter mapped to FIFO24.  */
    CAN_FILTER_FIFO25,      /*!< Filter mapped to FIFO25.  */
    CAN_FILTER_FIFO26,      /*!< Filter mapped to FIFO26.  */
    CAN_FILTER_FIFO27,      /*!< Filter mapped to FIFO27.  */
    CAN_FILTER_FIFO28,      /*!< Filter mapped to FIFO28.  */
    CAN_FILTER_FIFO29,      /*!< Filter mapped to FIFO29.  */
    CAN_FILTER_FIFO30,      /*!< Filter mapped to FIFO30.  */
    CAN_FILTER_FIFO31       /*!< Filter mapped to FIFO31.  */
} can_filter_fifo_t;

/**
 * @details CAN filter activation.
 */
typedef enum
{
    CAN_FILTER_DISABLE = 0,  /*!< CAN filter disable. */
    CAN_FILTER_ENABLE        /*!< CAN filter enable.  */
} can_filter_activation_t;

/**
 * @brief CAN filter init configuration structure.
 * @details User needs to specify values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 * Based on the user input, SW will define either extended or standard
 * frame ID should be chosen for filter configuration.
 *
 * 16-bit ID and Mask structure variables for ARM MCUs:
 * CAN_FILTER_MODE_IDMASK and CAN_FILTER_SCALE_32BIT - user is configuring 1 32-bit filter with mask:
 * - Filter(n) ID     is                   can_filter_id                        (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[0]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * - Filter(n) Mask   is                 can_filter_mask_id                     (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[1]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * CAN_FILTER_MODE_IDLIST and CAN_FILTER_SCALE_32BIT - you user is configuring 2 32-bit filters without masks:
 * - Filter(n) ID     is                   can_filter_id                        (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[0]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * - Filter(n+1) ID   is                 can_filter_mask_id                     (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[1]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * CAN_FILTER_MODE_IDMASK and CAN_FILTER_SCALE_16BIT - user is configuring 2 16-bit filters with masks:
 * - Filter(n) ID     is     can_filter_id_low       (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[0]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n) Mask   is   can_filter_mask_id_low    (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[1]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n+1) ID   is   can_filter_id_high        (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[2]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n+1) Mask is can_filter_mask_id_high     (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[3]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * CAN_FILTER_MODE_IDLIST and CAN_FILTER_SCALE_16BIT - user is configuring 4 16-bit filters:
 * - Filter(n) ID     is     can_filter_id_low       (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[0]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n) ID     is   can_filter_mask_id_low    (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[1]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n+1) ID   is   can_filter_id_high        (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[2]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * - Filter(n+1) ID   is can_filter_mask_id_high     (frame type is defined
 *                         0b0011 1111 1111 1111      with can_filter_frame_type[3]
 *                             |___|___________|      variable)
 *                         EID[17:15] SID[10:0]
 *
 * 16-bit ID and Mask structure variables for PIC MCUs:
 * - Filter(n) ID     is                   can_filter_id                        (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[0]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * - Filter(n) Mask   is                 can_filter_mask_id                     (frame type is defined
 *                         0b0001 1111 1111 1111 1111 1111 1111 1111             with can_filter_frame_type[1]
 *                              |______________________|___________|             variable)
 *                                     EID[17:0]        SID[10:0]
 *
 * @b Example
 * @code
 *   // CAN filter configuration structure.
 *   static can_filter_config_t can_filter_cfg;
 *
 * @endcode
 */
typedef struct
{
    union {
        struct {
            uint16_t can_filter_id_low;         /*!< 16-bit Filter ID. */
            uint16_t can_filter_id_high;        /*!< 16-bit Filter ID. */
        };
        uint32_t can_filter_id;                 /*!< 32-bit Filter ID. */
    };
    union {
        struct {
            uint16_t can_filter_mask_id_low;    /*!< 16-bit Filter ID or Filter Mask. */
            uint16_t can_filter_mask_id_high;   /*!< 16-bit Filter ID or Filter Mask. */
        };
        uint32_t can_filter_mask_id;            /*!< 32-bit Filter ID or Filter Mask. */
    };
    uint8_t can_filter_bank;                    /*!< Filter bank. */
    can_frame_type_t can_filter_frame_type[4];  /*!< Type of frame, data or remote. */
    can_filter_activation_t can_filter_enable;  /*!< Filter activation status. */
    can_filter_mode_t can_filter_mode;          /*!< Filter mode. */
    can_filter_scale_t can_filter_scale;        /*!< Filter scale. */
    can_filter_fifo_t can_filter_fifo;          /*!< Filter-to-FIFO mapping. */
} can_filter_config_t;

/**
 * @brief CAN init configuration structure.
 * @details User needs to specify values herein.
 * @note Take into consideration that any value can be changed
 * explicitly by the user.
 * @warning The following example includes pins mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // CAN driver configuration structure.
 *   static can_config_t can_cfg;
 *
 *   // Fill structure with default values.
 *   can_configure_default(&can_cfg);
 *
 *   // Specify desired CAN TX pin.
 *   can_cfg.tx_pin = CAN_TX;
 *
 *   // Specify desired CAN RX pin.
 *   can_cfg.rx_pin = CAN_RX;
 *
 * @endcode
 */
typedef struct
{
    pin_name_t tx_pin;  /*!< Tx pin. */
    pin_name_t rx_pin;  /*!< Rx pin. */
    can_mode_t mode;    /*!< CAN mode. */
    uint32_t frequency; /*!< CAN frequency. */
} can_config_t;

/**
 * @brief CAN driver context structure.
 * @details CAN driver context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 * @endcode
 */
typedef struct
{
    handle_t handle;                   /*!< CAN handle. */
    can_config_t config;               /*!< CAN configuration structure. */
    can_filter_config_t filter_config; /*!< CAN filter configuration structure. */
} can_t;

/**
 * @brief CAN driver message structure.
 * @details CAN driver message structure, used by
 * receive and transmit structures.
 *
 * @note id variable is divided in the folowing order:
 * - 0b0001 1111 1111 1111 1111 1111 1111 1111
 *        |______________________|___________|
 *                 EID[17:0]        SID[10:0]
 *
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
    can_frame_format_t frame_format;   /*!< Format of frame, standard or extended format. */
    can_frame_type_t frame_type;       /*!< Type of frame, data or remote. */
    uint8_t data_len;                  /*!< Data length. */
    uint8_t message_data[8];           /*!< Data. */
} can_message_t;

/**
 * @brief CAN driver transmit message structure.
 * @details CAN driver transmit message structure, used by
 * can_transmit later on.
 *
 * @b Example
 * @code
 *   // CAN driver transmit message structure.
 *   static can_transmit_message_struct tx_message;
 * @endcode
 */
typedef struct
{
    can_message_t message;  /* CAN message structure. */
} can_transmit_message_struct;

/**
 * @brief CAN driver receive message structure.
 * @details CAN driver receive message structure, used by
 * can_receive later on.
 *
 * @b Example
 * @code
 *   // CAN driver receive message structure.
 *   static can_receive_message_struct rx_message;
 * @endcode
 */
typedef struct
{
    can_message_t message;  /* CAN message structure. */
    uint8_t rx_fifo_number; /* Receive FIFO number. */
} can_receive_message_struct;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvcangroup CAN Driver
 * @brief CAN Driver API Reference.
 * @details CAN DRV API layer header.
 * Contains all enums, structures and
 * function declarations available for
 * CAN module.
 * @{
 */

/**
 * @brief Configure CAN Driver configuration structure.
 * @details Configures #can_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config configure CAN driver configuration structure.
 * See #can_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * Tx pin              | 0xFFFFFFFF (invalid pin)  |
 * Rx pin              | 0xFFFFFFFF (invalid pin)  |
 * Mode                | CAN_MODE_NORMAL           |
 * Frequency           | 500000                    |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // CAN driver configuration structure.
 *   static can_config_t can_cfg;
 *
 *   // Fill structure with default values.
 *   can_configure_default( &can_cfg );
 * @endcode
 */
void can_configure_default( can_config_t *config );

/**
 * @brief Configure CAN Driver filter configuration structure.
 * @details Configures #can_filter_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] filter_config configure CAN driver filter configuration structure.
 * See #can_filter_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * ID high             | 0x0000                    |
 * ID low              | 0x0000                    |
 * ID mask high        | 0x0000                    |
 * ID mask low         | 0x0000                    |
 * Filter mode         | CAN_FILTER_MODE_IDMASK    |
 * Filter scale        | CAN_FILTER_SCALE_16BIT    |
 * Filter enable       | CAN_FILTER_DISABLE        |
 * Filter FIFO         | CAN_FILTER_FIFO0          |
 * Filter bank         | 0                         |
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // CAN driver configuration structure.
 *   static can_filter_config_t can_filter_cfg;
 *
 *   // Fill structure with default values.
 *   can_filter_configure_default( &can_filter_cfg );
 * @endcode
 */
void can_filter_configure_default( can_filter_config_t *filter_config );

/**
 * @brief Open the CAN driver object.
 * @details Opens the CAN driver object on selected pins.
 * Allocates memory and pins for specified object.
 * @param[in,out] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] config CAN driver configuration settings.
 * See #can_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that \p config structure has been adequately
 * populated beforehand.
 * See #can_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *   // CAN driver configuration structure.
 *   static can_config_t can_cfg;
 *
 *   // Specify desired TX pin.
 *   can_cfg.tx_pin = CAN_TX;
 *
 *   // Specify desired RX pin.
 *   can_cfg.rx_pin = CAN_RX;
 *
 *   // Allocate resources for CAN module.
 *   if ( can_open( &can, &can_cfg ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t can_open( can_t *obj, can_config_t *config );

/**
 * @brief Initialize CAN module.
 * @details Sets CAN module parameters.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #can_open function.
 * @post This function initializes CAN module and sets adequate parameters.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Call the function.
 *   if ( can_init( &can ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t can_init( can_t *obj );

/**
 * @brief Initialize CAN module filter.
 * @details Sets CAN module filter parameters.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] filter_config CAN filter config structure.
 * See #can_filter_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that \p can_filter_config_t structure has been adequately
 * filled out.
 * @post This function initializes CAN filter and sets adequate parameters.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // CAN driver filter config structure.
 *   static can_filter_config_t can_filter_cfg;
 *
 *   // Configure CAN filter.
 *   if ( can_set_filter( &can, &can_filter_cfg ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t can_set_filter( can_t *obj, can_filter_config_t *filter_config );

/**
 * @brief Set CAN module frequency.
 * @details Sets CAN module frequency to \p frequency value if possible.
 * Frequency must be set to exact amount as requested, otherwise error is returned.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] frequency Specified CAN transmission rate.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #can_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Set transmission rate.
 *   if ( can_set_frequency( &can, 500000 ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t can_set_frequency( can_t *obj, uint32_t frequency );

/**
 * @brief Get CAN module frequency.
 * @details Gets the currently configured CAN frequency.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @return The function can return the CAN_ERROR value defined by
 * #can_err_t, which is size dependant on the architecture, or the actual frequency.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #can_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Get transmission rate.
 *   int32_t frequency = can_get_frequency( &can );
 *
 * @endcode
 */
err_t can_get_frequency( can_t *obj );

/**
 * @brief Set CAN module mode.
 * @details Sets CAN module mode to \p mode if possible.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] mode Specified CAN mode.
 * See #can_mode_t definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #can_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Set mode.
 *   if ( can_set_mode( &can, CAN_MODE_NORMAL ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t can_set_mode( can_t *obj, can_mode_t mode );

/**
 * @brief Get CAN module mode.
 * @details Gets the currently configured CAN mode.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @return The function can return the CAN_ERROR value defined by
 * #can_err_t, which is size dependant on the architecture, or the actual mode.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #can_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Get mode.
 *   can_mode_t mode = can_get_mode( &can );
 *
 * @endcode
 */
err_t can_get_mode( can_t *obj );

/**
 * @brief Transmit data to the first free TX mailbox.
 * @details Function sets parameters from the transmit message structure
 *          in the appropriate registers and then sends out the data.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] transmit_message Structure containing necessary information
 *                             about the message being transmitted.
 * See #can_message_struct structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate CAN frequency.
 * See #can_open definition and #can_set_frequency
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // CAN transmit structure.
 *   can_transmit_message_struct *tx_message;
 *
 *   // Set the ID type.
 *   tx_message.tx_id_type = CAN_FRAME_FORMAT_STANDARD_11BITS;
 *
 *   // Set a unique standard ID.
 *   tx_message.tx_std_id = 0x321;
 *
 *   // Set the length of the message in bytes.
 *   tx_message.tx_data_len = 3;
 *
 *   // Set the data.
 *   tx_message.tx_data[0] = 0xAA;
 *   tx_message.tx_data[1] = 0xBB;
 *   tx_message.tx_data[2] = 0xCC;
 *
 *   if ( can_transmit( &can, &tx_message ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 *
 * @endcode
 */
err_t can_transmit( can_t *obj, can_transmit_message_struct *transmit_message );

/**
 * @brief Stop transmit operation.
 * @details Function accesses hardware transmit registers, finds the transmit mailbox
 * that has message transmission request in progress and stops data transmission.
 * @param[in] obj CAN driver object.
 * @return void None.
 * @pre Make sure that there is transmission in progress.
 * See #can_transmit definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // CAN HAL context structure.
 *   static hal_can_t hal_can;
 *
 *   // Stop transmission.
 *   hal_can_transmission_stop( &hal_can );
 *
 * @endcode
 */
void can_transmission_stop( can_t *obj );

/**
 * @brief Get data from the RX FIFO.
 * @details Function stores previously transmitted data into
 *          the rx_data in receive_message structure.
 * @param[in] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @param[in] receive_message Structure designed to store received information and data
 *                            retrieved from the CAN registers.
 * See #can_message_struct structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate CAN frequency.
 * See #can_open definition and #can_set_frequency
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // CAN receive structure.
 *   can_receive_message_struct *rx_message;
 *
 *   if ( can_receive( &can, &rx_message ) == CAN_ERROR )
 *   {
 *       // Error handling strategy.
 *   }
 *
 * @endcode
 */
err_t can_receive( can_t *obj, can_receive_message_struct *receive_message );

/**
 * @brief Close CAN driver object.
 * @details De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level, resets pin AF to default values,
 * clears all buffers used by object and disables module
 * clock for lower power consumption.
 * @param[in,out] obj CAN driver object.
 * See #can_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #can_err_t, which is size dependant on the architecture.
 *
 * @b Example
 * @code
 *   // CAN driver context structure.
 *   static can_t can;
 *
 *   // Close the CAN module object handler.
 *   if ( CAN_SUCCESS == can_close( &can ) ) {
 *       // No error
 *   } else {
 *       // Handle the error.
 *   }
 * @endcode
 */
err_t can_close( can_t *obj );

/*! @} */ // drvcangroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_CAN_H_
// ------------------------------------------------------------------------- END
