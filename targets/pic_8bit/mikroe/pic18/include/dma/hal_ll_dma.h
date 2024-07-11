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
 * @file  hal_ll_dma.h
 * @brief API for DMA HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_DMA_H_
#define _HAL_LL_DMA_H_

#include "hal_ll_target.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @details Return values.
 */
typedef enum
{
    HAL_LL_DMA_SUCCESS = 0, /*!< Success. */
    HAL_LL_DMA_ERROR = (-1) /*!< Error. */
} hal_ll_dma_err_t;

/**
 * @details Module state values.
 */
typedef enum
{
    HAL_LL_DMA_STATE_FREE = 0,  /*!< DMA object is free for use. */
    HAL_LL_DMA_STATE_ALLOCATED  /*!< DMA object has been allocated - not free for use. */
} hal_ll_dma_state_t;

/**
 * @details Source address memory region.
 */
typedef enum
{
    HAL_LL_DMA_SOURCE_MEMORY_REGION_RAM      = 0,  /*!< DMA source address is in RAM section. */
    HAL_LL_DMA_SOURCE_MEMORY_REGION_PFM      = 1,  /*!< DMA source address is in Program Flash Memory section. */
    HAL_LL_DMA_SOURCE_MEMORY_REGION_DEEPROM  = 2  /*!< DMA source address is in Data EEPROM section. */
} hal_ll_dma_source_memory_region_t;

/**
 * @details Module direction values.
 */
typedef enum
{
    HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY = 0, /*!< M2M */
    HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH,     /*!< M2P */
    HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY,     /*!< P2M */
    HAL_LL_DMA_DIRECTION_PERIPH_TO_PERIPH,     /*!< P2P */

    HAL_LL_DMA_DIRECTION_DEFAULT = HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY /*!< Default value is M2M. */
} hal_ll_dma_direction_t;

/**
 * @details Module data alignment values.
 */
typedef enum
{
    HAL_LL_DMA_DATA_ALIGN_BYTES_1 = 0, /*!< Align data to byte (uint8_t). */
    HAL_LL_DMA_DATA_ALIGN_BYTES_2,    /*!< Align data to half word (uint16_t). */
    HAL_LL_DMA_DATA_ALIGN_BYTES_3,    /*!< Align data to 3 bytes (uint24_t). */
    HAL_LL_DMA_DATA_ALIGN_BYTES_4,    /*!< Align data to word (uint32_t). */

    HAL_LL_DMA_DATA_ALIGN_DEFAULT = HAL_LL_DMA_DATA_ALIGN_BYTES_1 /*!< Default data alignment of byte (uint8_t). */
} hal_ll_dma_data_align_t;

/**
 * @details Module mode values.
 */
typedef enum
{
    HAL_LL_DMA_MODE_NORMAL = 0, /*!< Normal mode. */
    HAL_LL_DMA_MODE_CIRCULAR,   /*!< Circular mode. */

    HAL_LL_DMA_MODE_DEFAULT = HAL_LL_DMA_MODE_NORMAL /*!< Default mode set to normal. */
} hal_ll_dma_mode_t;

/**
 * @details Module priority levels.
 */
typedef enum
{
    HAL_LL_DMA_PRIORITY_LOW = 0,   /*!< Sets priority level to low. */
    HAL_LL_DMA_PRIORITY_MEDIUM,    /*!< Sets priority level to medium. */
    HAL_LL_DMA_PRIORITY_HIGH,      /*!< Sets priority level to high. */
    HAL_LL_DMA_PRIORITY_VERY_HIGH, /*!< Sets priority level to very high. */

    HAL_LL_DMA_PRIORITY_DEFAULT = HAL_LL_DMA_PRIORITY_MEDIUM /*!< Default priority level set to medium. */
} hal_ll_dma_priority_t;

/**
 * @details Module burst increment size.
 */
typedef enum
{
    HAL_LL_DMA_BURST_SIZE_INCREMENT_1 = 0, /*!< Dma module burst increment size set to 1 byte. */
    HAL_LL_DMA_BURST_SIZE_INCREMENT_2,     /*!< Dma module burst increment size set to 2 bytes. */
    HAL_LL_DMA_BURST_SIZE_INCREMENT_4,     /*!< Dma module burst increment size set to 4 bytes. */
    HAL_LL_DMA_BURST_SIZE_INCREMENT_8,     /*!< Dma module burst increment size set to 8 bytes. */
    HAL_LL_DMA_BURST_SIZE_INCREMENT_16,    /*!< Dma module burst increment size set to 16 bytes. */
    HAL_LL_DMA_BURST_SIZE_INCREMENT_32,    /*!< Dma module burst increment size set to 32 bytes. */

    HAL_LL_DMA_BURST_SIZE_INCREMENT_DEFAULT = HAL_LL_DMA_BURST_SIZE_INCREMENT_1 /*!< Default burst increment size set to 1 byte. */
} hal_ll_dma_burst_size_t;

/**
 * @brief HAL LL DMA Configuration Structure prototype.
 */
typedef struct
{
    uint8_t module;                                 /*!< Specifies the module. */
    uint8_t stream;                                 /*!< Specifies the stream. */
    uint8_t channel;                                /*!< Specifies the channel used for the specified stream. */
    hal_ll_dma_direction_t direction;               /*!< Specifies if the data will be transferred from memory to peripheral,
                                                         from memory to memory, from peripheral to memory, or from
                                                         peripheral to peripheral.
                                                         This parameter can be a value of @ref hal_ll_dma_direction_t */
    hal_ll_dma_mode_t mode;                         /*!< Specifies the operation mode of the DMA Stream.
                                                         This parameter can be a value of @ref hal_ll_dma_mode_t */
    bool src_inc;                                   /*!< Specifies whether the Source address register should be incremented or not. */
    hal_ll_dma_data_align_t data_align_source;      /*!< Specifies the Source data width.
                                                         This parameter can be a value of @ref hal_ll_dma_data_align_t */
    hal_ll_dma_burst_size_t burst_size_source;      /*!< Specifies the Burst transfer configuration for the source transfers.
                                                         It specifies the amount of data to be transferred in a single non interruptable
                                                         transaction.
                                                         This parameter can be a value of @ref hal_ll_dma_burst_size_t
                                                         @note The burst mode is possible only if the address increment mode is enabled. */
    bool dst_inc;                                   /*!< Specifies whether the Destination address register should be incremented or not. */
    hal_ll_dma_data_align_t data_align_destination; /*!< Specifies the Destination data width.
                                                         This parameter can be a value of @ref hal_ll_dma_data_align_t */
    hal_ll_dma_burst_size_t burst_size_destination; /*!< Specifies the Burst transfer configuration for the destination transfers.
                                                         It specifies the amount of data to be transferred in a single non interruptable
                                                         transaction.
                                                         This parameter can be a value of @ref hal_ll_dma_burst_size_t
                                                         @note The burst mode is possible only if the address increment mode is enabled. */
    hal_ll_dma_priority_t priority;                 /*!< Specifies the software priority for the DMA Stream.
                                                         This parameter can be a value of @ref hal_ll_dma_priority_t */
    uint32_t addr_src;                              /*!< Address to transfer from. */
    uint32_t addr_dst;                              /*!< Address to transfer to. */
    size_t transfer_length;                         /*!< Number of bytes to transfer. */
} hal_ll_dma_config_t;

/**
 * @brief HAL DMA Handle prototype.
 * @details DMA hal context structure, used by every other function later on.
 */
typedef struct
{
    handle_t handle; /*!< DMA HAL LL handle. */
    hal_ll_dma_config_t config; /*!< DMA HAL LL configuration structure. */
    uint8_t module; /*!< Specifies the module. */
    uint8_t stream; /*!< Specifies the stream. */
    uint8_t channel; /*!< Specifies the channel used for the specified stream. */
    hal_ll_dma_state_t allocated; /*!< Is the object allocated or not? */
    bool initialized; /*!< Is the object initialized or not? */
} hal_ll_dma_t;

/**
 * @brief Initializes the DMA module.
 * @details Enables module clock and initializes to values set in
 * @b hal_ll_dma_t->hal_ll_dma_config_t
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj );

/**
 * @brief Set the DMA mode.
 * @details Sets DMA mode to be used by the DMA HAL LL.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @param[in] mode DMA mode.
 * See #hal_ll_dma_mode_t for valid values.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode );

/**
 * @brief Set the DMA direction.
 * @details Sets DMA direction to be used by the DMA HAL LL.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @param[in] direction DMA direction.
 * See #hal_ll_dma_direction_t for valid values.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_set_direction( hal_ll_dma_t *obj, hal_ll_dma_direction_t direction );

/**
 * @brief Set the DMA priority.
 * @details Sets DMA priority level to be used by the DMA HAL LL.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @param[in] priority DMA priority level.
 * See #hal_ll_dma_priority_t for valid values.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_set_priority( hal_ll_dma_t *obj, hal_ll_dma_priority_t priority );

/**
 * @brief Configure the DMA transfer.
 * @details Configures initialized DMA stream for transfer.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_dma_t structure definition for detailed explanation.
 * @param[in] addr_src Source address for transfer.
 * @param[in] addr_dst Destination address for transfer.
 * @param[in] transfer_size Number of bytes to transfer.
 * @param[in] src_mem_type Source address memory region.
 * @return Nothing.
 */
hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type );

/**
 * @brief Initializes the DMA transfer.
 * @details Starts previously configured DMA transfer by enabling stream.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj );

/**
 * @brief Stops the DMA transfer.
 * @details Stops an active DMA transfer by disabling stream.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj );

/**
 * @brief Aborts a DMA transfer.
 * @details Aborts any ongoing DMA transfers and disables stream.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj );

/**
 * @brief De-initializes the DMA module.
 * @details Disables module clock and de-initializes module.
 * @param[in,out] obj DMA HAL LL object.
 * See #hal_ll_dma_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * hal_ll_err_t, which is dependant on the architecture and ported low level layer.
 * @note It is recommended to check return value for error.
 */
hal_ll_err_t hal_ll_dma_deinit( hal_ll_dma_t *dma_obj );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_DMA_H_
// ------------------------------------------------------------------------- END
