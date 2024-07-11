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
 * @file sdspi_physical_drive.h
 * @brief SD SPI Physical Drive.
 */

#ifndef _PHYSICAL_DRIVE_H_
#define _PHYSICAL_DRIVE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "generic_pointer.h"

/**
 * @defgroup physical_drive_group Physical Drive
 * @ingroup middlewaregroup
 * @brief Physical Drive Reference.
 * @details Physical Drive Data Structures and API Reference.
 */


/**
 * @defgroup physical_drive_status_group Physical Drive APIs Status
 * @ingroup physical_drive_group
 * @brief Physical Drive API function return values.
 * @{
 */

/**
 * @brief: Success.
 */
#define PDS_OK                 ((uint8_t)0)

/**
 * @brief: Error.
 */
#define PDS_GENERAL_ERROR      ((uint8_t)1)

/**
 * @brief: Function is not implemented.
 */
#define PDS_NOT_IMPLEMENTED    ((uint8_t)2)

typedef uint8_t pd_status_t;

/*! @} */ // physical_drive_status_group


/**
 * @brief Physical Drive Type Enumerator.
 *
 * @details Indicate that a physical drives is initialized, what implementation the physical drive uses,
 *          and what it's @ref physical_drive_vector_table_t functions point to.
 */
typedef enum {
    PD_TYPE_UNINITIALIZED = 0,
    PD_TYPE_SDSPI,
} physical_drive_type_t;

/**
 * @ingroup physical_drive_data_group
 *
 * @brief Physical Drive Vector Table
 *
 * @details A table of function pointers, used used by @ref physical_drive_t struct,
 *          in order to call up correct functions for the particular implementation of the physical drive.
 */
typedef struct physical_drive_vector_table physical_drive_vector_table_t;


/**
 * @defgroup physical_drive_data_group Physical Drive Data
 * @ingroup physical_drive_group
 * @brief Physical Drive Data Structure Reference.
 */

/**
 * @ingroup physical_drive_data_group
 *
 * @brief Physical Drive Base Data Structure Reference.
 *
 * @details Keeps track of the relevant data for the physical drive and manages communication with hardware memory module,
 * with it's vector table that point to correct function for particular physical drive implementation.
 * It's intended usage is, as a base structure of a derived structures, eg. @ref sdspi_logical_drive_t.
 * It is not intended to be used independently.
 */
typedef struct {
    physical_drive_vector_table_t * vtptr;    /**< Physical drive vector table. See @ref physical_drive_vector_table_t structure. */
    physical_drive_type_t type;               /**< Type of physical drive. See @ref  physical_drive_type_t enum.*/
    uint32_t sector_count;                    /**< Number of sectors on this physical drive. */
    uint16_t sector_size;                     /**< Sector size in unit of bytes, on this physical drive. */
    uint16_t erase_block_size;                /**< Erase block size on this physical drive. */
    uint8_t volumes;                          /**< Number of logical drives mounted on this physical drive */
    uint8_t error;                            /**< Tracks APIs statuses and errors on this physical drive */
} physical_drive_t;

/**
 * @addtogroup physical_drive_group
 * @brief Physical Drive Reference.
 * @details Physical Drive Data Structures and API Reference.
 * @{
 */

/**
 * @brief Initialize a Hardware memory module.
 *
 * @details This API function will initialize hardware memory module, making it ready for subsequent read and write operations.
 *
 * @param[in] physical_drive A pointer to the physical drive base structure.
 * It manages communication with, and identifies hardware memory module.
 * See @ref physical_drive_t, and @ref sdspi_physical_drive_t structures for detailed explanation.
 *
 * @retval PDS_OK If the hardware memory module is initialized successfully.
 * @retval FSS_GENERAL_ERROR If the hardware memory module failed.
 *
 * @pre @c physical_drive structure must be initialized before calling this function.
 * See @ref sdspi_physical_drive_init functions for detailed explanation.
 *
 * @post Reading from and writing to hardware memory module is now possible.
 * All other physical drive API function can be called.
 *
 * @note @c physical_drive should be used  only as base of derived structures.
 * Eg. @ref sdspi_physical_drive_t.
 */
pd_status_t physical_drive_init(physical_drive_t * physical_drive);

/**
 * @brief Write to a Hardware Memory Module.
 *
 * @details This API function will write @c size number of bytes from the @c buffer
 *          into the hardware memory module at the location indicated by the parameter @c addr.
 *
 * @param[in] physical_drive A pointer to the physical drive base structure.
 * It manages communication with, and identifies hardware memory module.
 * See @ref physical_drive_t, and @ref sdspi_physical_drive_t structures for detailed explanation.
 * @param[in] buffer A pointer to the buffer from which data will be written to the hardware memory module.
 * @param[in] addr The location inside hardware memory module, in unit of bytes, where data will be written.
 * @param[in] size Number of bytes data that needs to be written into the hardware memory module.
 *
 * @retval PDS_OK If data was written to the hardware memory module successfully.
 * @retval FSS_GENERAL_ERROR If writing data failed.
 *
 * @pre The hardware memory module must be initialized first.
 * See @ref physical_drive_init functions for detailed explanation.
 *
 * @note @c physical_drive should be used only as base of derived structures.
 * Eg. @ref sdspi_physical_drive_t.
 */
pd_status_t physical_drive_read(physical_drive_t * physical_drive, void * buffer, unsigned long long addr, unsigned long long size);

/**
 * @brief Read from a Hardware Memory Module.
 *
 * @details This API function will read @c size number of bytes from the location indicated
 *          by the parameter @c addr inside hardware memory module, and store it into the @c buffer.
 *
 * @param[in] physical_drive A pointer to the physical drive base structure.
 * It manages communication with, and identifies hardware memory module.
 * See @ref physical_drive_t, and @ref sdspi_physical_drive_t structures for detailed explanation.
 * @param[in] buffer A pointer to the buffer where data read form the hardware memory module will be stored.
 * @param[in] addr The location inside hardware memory module, from which data will be read.
 * @param[in] size Number of bytes data that needs to be read from the hardware memory module.
 *
 * @retval PDS_OK If data was read from the hardware memory module successfully.
 * @retval FSS_GENERAL_ERROR If reading data failed.
 *
 * @pre The hardware memory module must be initialized first.
 * See @ref physical_drive_init functions for detailed explanation.
 */
pd_status_t physical_drive_write(physical_drive_t * physical_drive, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size);

/*! @} */ // physical_drive_group


#ifdef __cplusplus
}
#endif

#endif // !_PHYSICAL_DRIVE_H_
