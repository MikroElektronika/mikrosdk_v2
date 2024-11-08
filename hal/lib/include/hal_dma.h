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
 * @file  hal_dma.h
 * @brief API for DMA HAL level.
 */

#ifndef _HAL_DMA_H_
#define _HAL_DMA_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

#if !DRV_TO_HAL
#include "hal_ll_dma.h"
#endif

/**
 * @details Return values.
 */
typedef enum
{
    HAL_DMA_SUCCESS = 0, /*!< Success. */
    HAL_DMA_ERROR = (-1) /*!< Error. */
} hal_dma_err_t;

/**
 * @details Module state values.
 */
typedef enum
{
    HAL_DMA_STATE_FREE = 0,  /*!< DMA object is free for use. */
    HAL_DMA_STATE_ALLOCATED  /*!< DMA object has been allocated - not free for use. */
} hal_dma_state_t;

/**
 * @details Source address memory region.
 */
typedef enum
{
    HAL_DMA_SOURCE_MEMORY_REGION_RAM      = 0,  /*!< DMA source address is in RAM section. */
    HAL_DMA_SOURCE_MEMORY_REGION_PFM      = 1,  /*!< DMA source address is in Program Flash Memory section. */
    HAL_DMA_SOURCE_MEMORY_REGION_DEEPROM  = 2  /*!< DMA source address is in Data EEPROM section. */
} hal_dma_source_memory_region_t;

/**
 * @details Module direction values.
 */
typedef enum
{
    HAL_DMA_DIRECTION_MEMORY_TO_MEMORY = 0, /*!< M2M */
    HAL_DMA_DIRECTION_MEMORY_TO_PERIPH,     /*!< M2P */
    HAL_DMA_DIRECTION_PERIPH_TO_MEMORY,     /*!< P2M */
    HAL_DMA_DIRECTION_PERIPH_TO_PERIPH,     /*!< P2P */

    HAL_DMA_DIRECTION_DEFAULT = HAL_DMA_DIRECTION_MEMORY_TO_MEMORY /*!< Default value is M2M. */
} hal_dma_direction_t;

/**
 * @details Module data alignment values.
 */
typedef enum
{
    HAL_DMA_DATA_ALIGN_BYTES_1 = 0, /*!< Align data to byte (uint8_t). */
    HAL_DMA_DATA_ALIGN_BYTES_2,    /*!< Align data to half word (uint16_t). */
    HAL_DMA_DATA_ALIGN_BYTES_3,    /*!< Align data to 3 bytes (uint24_t). */
    HAL_DMA_DATA_ALIGN_BYTES_4,    /*!< Align data to word (uint32_t). */

    HAL_DMA_DATA_ALIGN_DEFAULT = HAL_DMA_DATA_ALIGN_BYTES_1 /*!< Default data alignment of byte (uint8_t). */
} hal_dma_data_align_t;

/**
 * @details Module mode values.
 */
typedef enum
{
    HAL_DMA_MODE_NORMAL = 0, /*!< Normal mode. */
    HAL_DMA_MODE_CIRCULAR,   /*!< Circular mode. */

    HAL_DMA_MODE_DEFAULT = HAL_DMA_MODE_NORMAL /*!< Default mode set to normal. */
} hal_dma_mode_t;

/**
 * @details Module priority levels.
 */
typedef enum
{
    HAL_DMA_PRIORITY_LOW = 0,   /*!< Sets priority level to low. */
    HAL_DMA_PRIORITY_MEDIUM,    /*!< Sets priority level to medium. */
    HAL_DMA_PRIORITY_HIGH,      /*!< Sets priority level to high. */
    HAL_DMA_PRIORITY_VERY_HIGH, /*!< Sets priority level to very high. */

    HAL_DMA_PRIORITY_DEFAULT = HAL_DMA_PRIORITY_MEDIUM /*!< Default priority level set to medium. */
} hal_dma_priority_t;

/**
 * @details Module burst increment size.
 */
typedef enum
{
    HAL_DMA_BURST_SIZE_INCREMENT_1 = 0, /*!< Dma module burst increment size set to 1 byte. */
    HAL_DMA_BURST_SIZE_INCREMENT_2,     /*!< Dma module burst increment size set to 2 bytes. */
    HAL_DMA_BURST_SIZE_INCREMENT_4,     /*!< Dma module burst increment size set to 4 bytes. */
    HAL_DMA_BURST_SIZE_INCREMENT_8,     /*!< Dma module burst increment size set to 8 bytes. */
    HAL_DMA_BURST_SIZE_INCREMENT_16,    /*!< Dma module burst increment size set to 16 bytes. */
    HAL_DMA_BURST_SIZE_INCREMENT_32,    /*!< Dma module burst increment size set to 32 bytes. */

    HAL_DMA_BURST_SIZE_INCREMENT_DEFAULT = HAL_DMA_BURST_SIZE_INCREMENT_1 /*!< Default burst increment size set to 1 byte. */
} hal_dma_burst_size_t;

/**
 * @details Module/Stream/Channel array prototype.
 * @note Size varies based on selected MCU.
 * @note @ref DMA_NUM_OF_MODULES, @ref DMA_NUM_OF_STREAMS_FAMILY, @ref DMA_NUM_OF_CHANNELS_FAMILY are
 * declared separately for each MCU.
 */
typedef uint8_t hal_dma_channel_t[ DMA_NUM_OF_MODULES ][ DMA_NUM_OF_STREAMS_FAMILY ][ DMA_NUM_OF_CHANNELS_FAMILY ];

/**
 * @brief HAL DMA Configuration Structure prototype.
 *
 * @b Example
 * @code
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Specify desired DMA module.
 *   dma_cfg.module = 0; // First module (DMA0 or DMA1 based on MCU).
 *
 *   // Specify desired DMA stream number.
 *   dma_cfg.stream = 5;
 *
 *   // Specify desired DMA channel number.
 *   dma_cfg.channel = 3;
 * @endcode
 */
typedef struct
{
    uint8_t module;                             /*!< Specifies the module. */
    uint8_t stream;                             /*!< Specifies the stream. */
    uint8_t channel;                            /*!< Specifies the channel used for the specified stream. */
    hal_dma_direction_t direction;              /*!< Specifies if the data will be transferred from memory to peripheral,
                                                     from memory to memory, from peripheral to memory, or from
                                                     peripheral to peripheral.
                                                     This parameter can be a value of @ref hal_dma_direction_t */
    hal_dma_mode_t mode;                        /*!< Specifies the operation mode of the DMA Stream.
                                                     This parameter can be a value of @ref hal_dma_mode_t */
    bool source_inc;                            /*!< Specifies whether the Source address register should be incremented or not. */
    hal_dma_data_align_t data_align_source;     /*!< Specifies the Source data width.
                                                     This parameter can be a value of @ref hal_dma_data_align_t */
    hal_dma_burst_size_t burst_size_source;     /*!< Specifies the Burst transfer configuration for the memory transfers.
                                                     It specifies the amount of data to be transferred in a single non interruptable
                                                     transaction.
                                                     This parameter can be a value of @ref hal_dma_burst_size_t
                                                     @note The burst mode is possible only if the address increment mode is enabled. */
    bool destination_inc;                           /*!< Specifies whether the Destination address register should be incremented or not. */
    hal_dma_data_align_t data_align_destination;/*!< Specifies the Destination data width.
                                                 This parameter can be a value of @ref hal_dma_data_align_t */
    hal_dma_burst_size_t burst_size_destination;/*!< Specifies the Burst transfer configuration for the destination transfers.
                                                     It specifies the amount of data to be transferred in a single non interruptable
                                                     transaction.
                                                     This parameter can be a value of @ref hal_dma_burst_size_t
                                                     @note The burst mode is possible only if the address increment mode is enabled. */
    hal_dma_priority_t priority;                /*!< Specifies the software priority for the DMA Stream.
                                                     This parameter can be a value of @ref hal_dma_priority_t */
    uint32_t addr_src;                          /*!< Address to transfer from. */
    uint32_t addr_dst;                          /*!< Address to transfer to. */
    size_t transfer_length;                     /*!< Number of bytes to transfer. */
} hal_dma_config_t;

/**
 * @brief HAL DMA Handle prototype.
 * @details DMA HAL context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Allocate memory for object.
 *   hal_dma_open( &hal_dma, &hal_dma_cfg );
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< DMA HAL handle. */
    hal_dma_config_t config; /*!< DMA HAL configuration structure. */
    uint8_t module; /*!< Specifies the module. */
    uint8_t stream; /*!< Specifies the stream. */
    uint8_t channel; /*!< Specifies the channel used for the specified stream. */
    hal_dma_state_t allocated; /*!< Is the object allocated or not? */
    bool initialized; /*!< Is the object initialized or not? */
} hal_dma_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/*!
 * @addtogroup haldmagroup DMA HAL
 * @brief DMA Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating DMA HAL module.
 * @{
 */

/**
 * @brief Configure DMA HAL configuration structure.
 * @details Configures #hal_dma_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config configure DMA HAL configuration structure.
 * See #hal_dma_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function                  | Default value                        |
 * --------------------------|--------------------------------------|
 * Module                    | 0xFF                                 |
 * Stream                    | 0xFF                                 |
 * Channel                   | 0xFF                                 |
 * Direction                 | HAL_DMA_DIRECTION_DEFAULT            |
 * Mode                      | HAL_DMA_MODE_DEFAULT                 |
 * Priority                  | HAL_DMA_PRIORITY_DEFAULT             |
 * Memory increment          | false                                |
 * Memory data alignment     | HAL_DMA_DATA_ALIGN_DEFAULT           |
 * Memory burst size         | HAL_DMA_BURST_SIZE_INCREMENT_DEFAULT |
 * Peripheral increment      | false                                |
 * Peripheral data alignment | HAL_DMA_DATA_ALIGN_DEFAULT           |
 * Peripheral burst size     | HAL_DMA_BURST_SIZE_INCREMENT_DEFAULT |
 * Source address            | 0                                    |
 * Destination address       | 0                                    |
 * Transfer length           | 0                                    |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 * @endcode
 */
void hal_dma_configure_default( hal_dma_config_t *config );

/**
 * @brief Open the DMA HAL object.
 * @details Opens the DMA HAL object on selected module, stream and channel.
 * Allocates memory for specified object.
 * Additionally, initializes the DMA module.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] config configure DMA HAL configuration settings.
 * See #hal_dma_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that \p configuration structure has been adequately
 * populated beforehand.
 * See #hal_dma_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Specify desired DMA module.
 *   hal_dma_cfg.module = 0; // First module (DMA0 or DMA1 based on MCU).
 *
 *   // Specify desired DMA stream number.
 *   hal_dma_cfg.stream = 5;
 *
 *   // Specify desired DMA channel number.
 *   hal_dma_cfg.channel = 3;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_dma_open( hal_dma_t *obj, hal_dma_config_t *config );

/**
 * @brief Get DMA modules/streams/channels.
 * @details Checks current MCU for available number of modules, streams and channels.
 * @param[in,out] channels DMA channel context array.
 * See #hal_dma_channel_t definition for detailed explanation.
 * @return Nothing.
 * @pre Make sure that \p channels array has been adequately
 * instantiated before calling this API.
 * @note It is recommended to use this API in order to check
 * available resources and see which ones are free to use.
 *
 * @b Example
 * @code
 *   // DMA HAL channel context structure.
 *   static hal_dma_channel_t hal_dma_channels;
 *
 *   // Get list of available channels per stream per module.
 *   hal_dma_get_channels( &hal_dma_channels );
 *
 *   // Lets say we want to use DMA module 0, stream 3 and channel 4.
 *   if ( DMA_STATE_FREE == hal_dma_channels[0][3][4] )
 *   {
 *       // Module 0, stream 3, channel 4 is free for use.
 *   }
 * @endcode
 */
void hal_dma_get_channels( hal_dma_channel_t *channels );

/**
 * @brief Set the DMA mode.
 * @details Sets DMA mode to be used by the DMA HAL.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] mode DMA mode.
 * See #hal_dma_mode_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( HAL_DMA_ERROR == hal_dma_set_mode( &hal_dma, HAL_DMA_MODE_NORMAL ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_dma_set_mode( hal_dma_t *obj, hal_dma_mode_t mode );

/**
 * @brief Set the DMA direction.
 * @details Sets DMA direction to be used by the DMA HAL.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] direction DMA direction.
 * See #hal_dma_direction_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( HAL_DMA_ERROR == hal_dma_set_direction( &hal_dma, HAL_DMA_DIRECTION_MEMORY_TO_MEMORY ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_dma_set_direction( hal_dma_t *obj, hal_dma_direction_t direction );

/**
 * @brief Set the DMA priority.
 * @details Sets DMA priority level to be used by the DMA HAL.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] priority DMA priority level.
 * See #hal_dma_priority_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( HAL_DMA_ERROR == hal_dma_set_priority( &hal_dma, HAL_DMA_PRIORITY_MEDIUM ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_dma_set_priority( hal_dma_t *obj, hal_dma_priority_t priority );

/**
 * @brief Configure the DMA transfer.
 * @details Configures initialized DMA stream for transfer.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] addr_src Source address for transfer.
 * @param[in] addr_dst Destination address for transfer.
 * @param[in] transfer_size Number of bytes to transfer.
 * @param[in] src_mem_type Source address memory region.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   hal_dma_cfg.data_align_memory = HAL_DMA_DATA_ALIGN_BYTES_1;
 *   hal_dma_cfg.data_align_peripheral = HAL_DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   hal_dma_cfg.mem_inc = true;
 *   hal_dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( HAL_DMA_ERROR == hal_dma_set_transfer_config( &hal_dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2,  HAL_DMA_SOURCE_MEMORY_REGION_PFM ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Transfer is now configured and can be started.
 * @endcode
 */
err_t hal_dma_set_transfer_config( hal_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_dma_source_memory_region_t src_mem_type );

/**
 * @brief Initializes the DMA transfer.
 * @details Starts previously configured DMA transfer by enabling stream.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   hal_dma_cfg.data_align_memory = HAL_DMA_DATA_ALIGN_BYTES_1;
 *   hal_dma_cfg.data_align_peripheral = HAL_DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   hal_dma_cfg.mem_inc = true;
 *   hal_dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( HAL_DMA_ERROR == hal_dma_set_transfer_config( &hal_dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( HAL_DMA_ERROR == hal_dma_transfer_start( &hal_dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Compare buffers now.
 *   if ( !memcmp(buffer_src_flash, buffer_dst, sizeof(buffer_src)) )
 *   {
 *       // Successful comparison.
 *   }
 * @endcode
 */
err_t hal_dma_transfer_start( hal_dma_t *obj );

/**
 * @brief Stops the DMA transfer.
 * @details Stops an active DMA transfer by disabling stream.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   hal_dma_cfg.data_align_memory = HAL_DMA_DATA_ALIGN_BYTES_1;
 *   hal_dma_cfg.data_align_peripheral = HAL_DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   hal_dma_cfg.mem_inc = true;
 *   hal_dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( HAL_DMA_ERROR == hal_dma_set_transfer_config( &hal_dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( HAL_DMA_ERROR == hal_dma_transfer_start( &hal_dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Compare buffers now.
 *   if ( !memcmp(buffer_src_flash, buffer_dst, sizeof(buffer_src)) )
 *   {
 *       // Successful comparison. Stop the stream now.
 *       if ( HAL_DMA_ERROR == hal_dma_transfer_stop( &hal_dma ) )
 *       {
 *           // Error handling strategy.
 *       }
 *   }
 * @endcode
 */
err_t hal_dma_transfer_stop( hal_dma_t *obj );

/**
 * @brief Aborts a DMA transfer.
 * @details Aborts any ongoing DMA transfers and disables stream.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   hal_dma_cfg.data_align_memory = HAL_DMA_DATA_ALIGN_BYTES_1;
 *   hal_dma_cfg.data_align_peripheral = HAL_DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   hal_dma_cfg.mem_inc = true;
 *   hal_dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( HAL_DMA_ERROR == hal_dma_set_transfer_config( &hal_dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( HAL_DMA_ERROR == hal_dma_transfer_start( &hal_dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Compare buffers now.
 *   if ( !memcmp(buffer_src_flash, buffer_dst, sizeof(buffer_src)) )
 *   {
 *       // Successful comparison.
 *   }
 *
 *   // Abort any further ongoing transfers.
 *   if ( HAL_DMA_ERROR == hal_dma_transfer_abort( &hal_dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_dma_transfer_abort( hal_dma_t *obj );

/**
 * @brief Close DMA HAL object.
 * @details Closes DMA HAL object,
 * aborts any ongoing transfers, disables the stream,
 * deinitializes the module, clears all buffers used by
 * object and disables module clock for lower power consumption.
 * @param[in,out] obj DMA HAL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 *
 * @b Example
 * @code
 *   // DMA HAL context structure.
 *   static hal_dma_t hal_dma;
 *
 *   // DMA HAL configuration structure.
 *   static hal_dma_config_t hal_dma_cfg;
 *
 *   // Fill structure with default values.
 *   hal_dma_configure_default( &hal_dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( HAL_DMA_ERROR == hal_dma_open( &hal_dma, &hal_dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Close previously initialized DMA module object handler.
 *   if ( HAL_DMA_SUCCESS == hal_dma_close( &hal_dma ) {
 *       // No error.
 *   } else {
 *       // Handle the error.
 *   }
 * @endcode
 */
err_t hal_dma_close( hal_dma_t *obj );

/*! @} */ // haldmagroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_DMA_H_
// ------------------------------------------------------------------------- END
