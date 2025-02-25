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
 * @file  drv_dma.h
 * @brief API for DMA driver.
 */

#ifndef _DRV_DMA_H_
#define _DRV_DMA_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_dma.h"

/**
 * @details Return values.
 */
typedef enum
{
    DMA_SUCCESS = 0, /*!< Success. */
    DMA_ERROR = (-1) /*!< Error. */
} dma_err_t;

/**
 * @details Module state values.
 */
typedef enum
{
    DMA_STATE_FREE = 0,  /*!< DMA object is free for use. */
    DMA_STATE_ALLOCATED  /*!< DMA object has been allocated - not free for use. */
} dma_state_t;

/**
 * @details Source address memory region.
 */
typedef enum
{
    DMA_SOURCE_MEMORY_REGION_RAM      = 0,  /*!< DMA source address is in RAM section. */
    DMA_SOURCE_MEMORY_REGION_PFM      = 1,  /*!< DMA source address is in Program Flash Memory section. */
    DMA_SOURCE_MEMORY_REGION_DEEPROM  = 2  /*!< DMA source address is in Data EEPROM section. */
} dma_source_memory_region_t;

/**
 * @details Module direction values.
 */
typedef enum
{
    DMA_DIRECTION_MEMORY_TO_MEMORY = 0, /*!< M2M */
    DMA_DIRECTION_MEMORY_TO_PERIPH,     /*!< M2P */
    DMA_DIRECTION_PERIPH_TO_MEMORY,     /*!< P2M */
    DMA_DIRECTION_PERIPH_TO_PERIPH,     /*!< P2P */

    DMA_DIRECTION_DEFAULT = DMA_DIRECTION_MEMORY_TO_MEMORY /*!< Default value is M2M. */
} dma_direction_t;

/**
 * @details Module data alignment values.
 */
typedef enum
{
    DMA_DATA_ALIGN_BYTES_1 = 0, /*!< Align data to byte (uint8_t). */
    DMA_DATA_ALIGN_BYTES_2,    /*!< Align data to half word (uint16_t). */
    DMA_DATA_ALIGN_BYTES_3,    /*!< Align data to 3 bytes (uint24_t). */
    DMA_DATA_ALIGN_BYTES_4,    /*!< Align data to word (uint32_t). */

    DMA_DATA_ALIGN_DEFAULT = DMA_DATA_ALIGN_BYTES_1 /*!< Default data alignment of byte (uint8_t). */
} dma_data_align_t;

/**
 * @details Module mode values.
 */
typedef enum
{
    DMA_MODE_NORMAL = 0, /*!< Normal mode. */
    DMA_MODE_CIRCULAR,   /*!< Circular mode. */

    DMA_MODE_DEFAULT = DMA_MODE_NORMAL /*!< Default mode set to normal. */
} dma_mode_t;

/**
 * @details Module priority levels.
 */
typedef enum
{
    DMA_PRIORITY_LOW = 0,   /*!< Sets priority level to low. */
    DMA_PRIORITY_MEDIUM,    /*!< Sets priority level to medium. */
    DMA_PRIORITY_HIGH,      /*!< Sets priority level to high. */
    DMA_PRIORITY_VERY_HIGH, /*!< Sets priority level to very high. */

    DMA_PRIORITY_DEFAULT = DMA_PRIORITY_MEDIUM /*!< Default priority level set to medium. */
} dma_priority_t;

/**
 * @details Module burst increment size.
 */
typedef enum
{
    DMA_BURST_SIZE_INCREMENT_1 = 0, /*!< Dma module burst increment size set to 1 byte. */
    DMA_BURST_SIZE_INCREMENT_2,     /*!< Dma module burst increment size set to 2 bytes. */
    DMA_BURST_SIZE_INCREMENT_4,     /*!< Dma module burst increment size set to 4 bytes. */
    DMA_BURST_SIZE_INCREMENT_8,     /*!< Dma module burst increment size set to 8 bytes. */
    DMA_BURST_SIZE_INCREMENT_16,    /*!< Dma module burst increment size set to 16 bytes. */
    DMA_BURST_SIZE_INCREMENT_32,    /*!< Dma module burst increment size set to 32 bytes. */

    DMA_BURST_SIZE_INCREMENT_DEFAULT = DMA_BURST_SIZE_INCREMENT_1 /*!< Default burst increment size set to 1 byte. */
} dma_burst_size_t;

/**
 * @details Module/Stream/Channel array prototype.
 * @note Size varies based on selected MCU.
 * @note @ref DMA_NUM_OF_MODULES, @ref DMA_NUM_OF_STREAMS_FAMILY, @ref DMA_NUM_OF_CHANNELS_FAMILY are
 * declared separately for each MCU.
 */
typedef uint8_t dma_channel_t[ DMA_NUM_OF_MODULES ][ DMA_NUM_OF_STREAMS_FAMILY ][ DMA_NUM_OF_CHANNELS_FAMILY ];

/**
 * @brief DMA Configuration Structure prototype.
 *
 * @b Example
 * @code
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
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
    uint8_t module;                         /*!< Specifies the module. */
    uint8_t stream;                         /*!< Specifies the stream. */
    uint8_t channel;                        /*!< Specifies the channel used for the specified stream. */
    dma_direction_t direction;              /*!< Specifies if the data will be transferred from memory to peripheral,
                                                 from memory to memory, from peripheral to memory, or from
                                                 peripheral to peripheral.
                                                 This parameter can be a value of @ref dma_direction_t */
    dma_mode_t mode;                        /*!< Specifies the operation mode of the DMA Stream.
                                                 This parameter can be a value of @ref dma_mode_t */
    bool src_inc;                           /*!< Specifies whether the Source address register should be incremented or not. */
    dma_data_align_t data_align_source;     /*!< Specifies the Source data width.
                                                 This parameter can be a value of @ref dma_data_align_t */
    dma_burst_size_t burst_size_source;     /*!< Specifies the Burst transfer configuration for the source transfers.
                                                 It specifies the amount of data to be transferred in a single non interruptable
                                                 transaction.
                                                 This parameter can be a value of @ref dma_burst_size_t
                                                 @note The burst mode is possible only if the address increment mode is enabled. */
    bool dst_inc;                          /*!< Specifies whether the Destination address register should be incremented or not. */
    dma_data_align_t data_align_destination;/*!< Specifies the Destination data width.
                                                 This parameter can be a value of @ref dma_data_align_t */
    dma_burst_size_t burst_size_destination;/*!< Specifies the Burst transfer configuration for the destination transfers.
                                                 It specifies the amount of data to be transferred in a single non interruptable
                                                 transaction.
                                                 This parameter can be a value of @ref dma_burst_size_t
                                                 @note The burst mode is possible only if the address increment mode is enabled. */
    dma_priority_t priority;                /*!< Specifies the software priority for the DMA Stream.
                                                 This parameter can be a value of @ref dma_priority_t */
    uint32_t addr_src;                      /*!< Address to transfer from. */
    uint32_t addr_dst;                      /*!< Address to transfer to. */
    size_t transfer_length;                 /*!< Number of bytes to transfer. */
} dma_config_t;

/**
 * @brief DMA Handle prototype.
 * @details DMA driver context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Allocate memory for object.
 *   dma_open( &dma, &dma_cfg );
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< DMA handle. */
    dma_config_t config; /*!< DMA configuration structure. */
    uint8_t module; /*!< Specifies the module. */
    uint8_t stream; /*!< Specifies the stream. */
    uint8_t channel; /*!< Specifies the channel used for the specified stream. */
    dma_state_t allocated; /*!< Is the object allocated or not? */
    bool initialized; /*!< Is the object initialized or not? */
} dma_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvdmagroup DMA Driver
 * @brief DMA Driver API Reference.
 * @details DMA DRV API layer header.
 * Contains all enums, structures and
 * function declarations available for
 * DMA module.
 * @{
 */

/**
 * @brief Configure DMA Driver configuration structure.
 * @details Configures #dma_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config configure DMA driver configuration structure.
 * See #dma_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function                  | Default value                    |
 * --------------------------|----------------------------------|
 * Module                    | 0xFF                             |
 * Stream                    | 0xFF                             |
 * Channel                   | 0xFF                             |
 * Direction                 | DMA_DIRECTION_DEFAULT            |
 * Mode                      | DMA_MODE_DEFAULT                 |
 * Priority                  | DMA_PRIORITY_DEFAULT             |
 * Memory increment          | false                            |
 * Memory data alignment     | DMA_DATA_ALIGN_DEFAULT           |
 * Memory burst size         | DMA_BURST_SIZE_INCREMENT_DEFAULT |
 * Peripheral increment      | false                            |
 * Peripheral data alignment | DMA_DATA_ALIGN_DEFAULT           |
 * Peripheral burst size     | DMA_BURST_SIZE_INCREMENT_DEFAULT |
 * Source address            | 0                                |
 * Destination address       | 0                                |
 * Transfer length           | 0                                |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 * @endcode
 */
void dma_configure_default( dma_config_t *config );

/**
 * @brief Open the DMA Driver object.
 * @details Opens the DMA driver object on selected module, stream and channel.
 * Allocates memory for specified object.
 * Additionally, initializes the DMA module.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @param[in] config configure DMA driver configuration settings.
 * See #dma_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that \p configuration structure has been adequately
 * populated beforehand.
 * See #dma_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Specify desired DMA module.
 *   dma_cfg.module = 0; // First module (DMA0 or DMA1 based on MCU).
 *
 *   // Specify desired DMA stream number.
 *   dma_cfg.stream = 5;
 *
 *   // Specify desired DMA channel number.
 *   dma_cfg.channel = 3;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t dma_open( dma_t *obj, dma_config_t *config );

/**
 * @brief Get DMA modules/streams/channels.
 * @details Checks current MCU for available number of modules, streams and channels.
 * @param[in,out] channels DMA channel context array.
 * See #dma_channel_t definition for detailed explanation.
 * @return Nothing.
 * @pre Make sure that \p channels array has been adequately
 * instantiated before calling this API.
 * @note It is recommended to use this API in order to check
 * available resources and see which ones are free to use.
 *
 * @b Example
 * @code
 *   // DMA channel context structure.
 *   static dma_channel_t dma_channels;
 *
 *   // Get list of available channels per stream per module.
 *   dma_get_channels( &dma_channels );
 *
 *   // Lets say we want to use DMA module 0, stream 3 and channel 4.
 *   if ( DMA_STATE_FREE == dma_channels[0][3][4] )
 *   {
 *       // Module 0, stream 3, channel 4 is free for use.
 *   }
 * @endcode
 */
void dma_get_channels( dma_channel_t *channels );

/**
 * @brief Set the DMA mode.
 * @details Sets DMA mode to be used by the DMA driver.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @param[in] mode DMA mode.
 * See #dma_mode_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( DMA_ERROR == dma_set_mode( &dma, DMA_MODE_NORMAL ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t dma_set_mode( dma_t *obj, dma_mode_t mode );

/**
 * @brief Set the DMA direction.
 * @details Sets DMA direction to be used by the DMA driver.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @param[in] direction DMA direction.
 * See #dma_direction_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( DMA_ERROR == dma_set_direction( &dma, DMA_DIRECTION_MEMORY_TO_MEMORY ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t dma_set_direction( dma_t *obj, dma_direction_t direction );

/**
 * @brief Set the DMA priority.
 * @details Sets DMA priority level to be used by the DMA driver.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @param[in] priority DMA priority level.
 * See #dma_priority_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Set desired DMA mode.
 *   if ( DMA_ERROR == dma_set_priority( &dma, DMA_PRIORITY_MEDIUM ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t dma_set_priority( dma_t *obj, dma_priority_t priority );

/**
 * @brief Configure the DMA transfer.
 * @details Configures initialized DMA stream for transfer.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @param[in] addr_src Source address for transfer.
 * @param[in] addr_dst Destination address for transfer.
 * @param[in] transfer_size Number of bytes to transfer.
 * @param[in] src_mem_type Source address memory region.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   dma_cfg.data_align_memory = DMA_DATA_ALIGN_BYTES_1;
 *   dma_cfg.data_align_peripheral = DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   dma_cfg.mem_inc = true;
 *   dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( DMA_ERROR == dma_set_transfer_config( &dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2, HAL_DMA_SOURCE_MEMORY_REGION_PFM ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Transfer is now configured and can be started.
 * @endcode
 */
err_t dma_set_transfer_config( dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, dma_source_memory_region_t src_mem_type );

/**
 * @brief Initializes the DMA transfer.
 * @details Starts previously configured DMA transfer by enabling stream.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   dma_cfg.data_align_memory = DMA_DATA_ALIGN_BYTES_1;
 *   dma_cfg.data_align_peripheral = DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   dma_cfg.mem_inc = true;
 *   dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( DMA_ERROR == dma_set_transfer_config( &dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( DMA_ERROR == dma_transfer_start( &dma ) )
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
err_t dma_transfer_start( dma_t *obj );

/**
 * @brief Stops the DMA transfer.
 * @details Stops an active DMA transfer by disabling stream.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   dma_cfg.data_align_memory = DMA_DATA_ALIGN_BYTES_1;
 *   dma_cfg.data_align_peripheral = DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   dma_cfg.mem_inc = true;
 *   dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( DMA_ERROR == dma_set_transfer_config( &dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( DMA_ERROR == dma_transfer_start( &dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Compare buffers now.
 *   if ( !memcmp(buffer_src_flash, buffer_dst, sizeof(buffer_src)) )
 *   {
 *       // Successful comparison. Stop the stream now.
 *       if ( DMA_ERROR == dma_transfer_stop( &dma ) )
 *       {
 *           // Error handling strategy.
 *       }
 *   }
 * @endcode
 */
err_t dma_transfer_stop( dma_t *obj );

/**
 * @brief Aborts a DMA transfer.
 * @details Aborts any ongoing DMA transfers and disables stream.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #dma_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Source buffer in flash.
 *   static const uint8_t buffer_src[2] = {0xCa, 0xfe};
 *
 *   // Destination buffer in RAM.
 *   static uint8_t buffer_dst[2];
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Set data alignment to BYTE(8-bit) because
 *   // arrays are byte size.
 *   dma_cfg.data_align_memory = DMA_DATA_ALIGN_BYTES_1;
 *   dma_cfg.data_align_peripheral = DMA_DATA_ALIGN_BYTES_1;
 *
 *   // Set memory addresses to be incremented
 *   // for both memory and peripheral.
 *   dma_cfg.mem_inc = true;
 *   dma_cfg.periph_inc = true;
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Configure transfer to copy 2 bytes from buffer_src to buffer_dst.
 *   if ( DMA_ERROR == dma_set_transfer_config( &dma, (uint32_t)buffer_src, (uint32_t)buffer_dst, 2 ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Start the transfer and check the destination buffer.
 *   if ( DMA_ERROR == dma_transfer_start( &dma ) )
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
 *   if ( DMA_ERROR == dma_transfer_abort( &dma ) )
 *   {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t dma_transfer_abort( dma_t *obj );

/**
 * @brief Close DMA Driver object.
 * @details Closes DMA driver object,
 * aborts any ongoing transfers, disables the stream,
 * deinitializes the module, clears all buffers used by
 * object and disables module clock for lower power consumption.
 * @param[in,out] obj DMA driver object.
 * See #dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 *
 * @b Example
 * @code
 *   // DMA driver context structure.
 *   static dma_t dma;
 *
 *   // DMA driver configuration structure.
 *   static dma_config_t dma_cfg;
 *
 *   // Fill structure with default values.
 *   dma_configure_default( &dma_cfg );
 *
 *   // Initialize and allocate resources for DMA module.
 *   if ( DMA_ERROR == dma_open( &dma, &dma_cfg ) )
 *   {
 *       // Error handling strategy.
 *   }
 *
 *   // Close previously initialized DMA module object handler.
 *   if ( DMA_SUCCESS == dma_close( &dma ) {
 *       // No error.
 *   } else {
 *       // Handle the error.
 *   }
 * @endcode
 */
err_t dma_close( dma_t *obj );

/*! @} */ // drvdmagroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_DMA_H_
// ------------------------------------------------------------------------- END
