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
 * @file fatfs.h
 * @brief FatFs File System.
 */

#ifndef _FATFS_FILESYSTEM_H_
#define _FATFS_FILESYSTEM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "file_system.h"
#include "ff_types.h"

/**
 * @ingroup logical_drive_group
 *
 * @brief FatFs Logical Drive
 *
 * @details Keeps track of relevant data for the logical drive, FatFs filesystem, and calling correct FatFs APIs.
 *          It is derived from @ref logical_drive_t struct.
 */
typedef struct {
    logical_drive_t base;    /**< Logical Drive base structure. It identifies and represents @c fatfs_logical_drive_t in files system API functions */
    FATFS fatfs;             /**< FatFs File System Logical Drive Structure, keeps all the relevant data specific to the FatFS logical drive implementation. */
} fatfs_logical_drive_t;

/**
 * @ingroup logical_drive_group
 *
 * @brief Initializes FatFs logical drive
 *
 * @details This API function will initialize the @c fatfs_drive, by zeroing @c fatfs structure making it ready to be used,
 *          as well as setting vector table @c vtptr inside @c base to point to functions relevant for FatFs operations. It also sets
 *          @c type inside @c base struct to be @ref FS_TYPE_FATFS, signaling at the same time that logical drive is initialized and
 *          that its type is FatFs. All other values are set to zeros.
 *
 * @post Logical drive @c fatfs_drive is now ready to be used by filesystem.
 */
fs_status_t fatfs_initialize(fatfs_logical_drive_t * const fatfs_drive);

#ifdef __cplusplus
}
#endif

#endif // !_FATFS_FILESYSTEM_H_
