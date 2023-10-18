/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file dir.h
 * @brief File System Directory Access and Management.
 */

#ifndef _DIR_H_
#define _DIR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "file_system.h"

/**
 * @defgroup directory_data_group Directory Data
 * @ingroup directory_group
 * @brief Directory Data Structure Reference.
 */

/**
 * @ingroup directory_data_group
 *
 * @brief Directory Data Structure.
 *
 * @details The struct is used to link file system specific directory data structure @c fs_dir,
 *          to the logical drive struct where the directory is located.
 *          It is used as identifier for the directory in Directory Access API functions.
 *
 * @note The directory is considered closed or uninitialized when both of its elements are NULL,
 * and if both elements are set the directory is considered to be open.
 * If one element is NULL while the other is not, the directory is considered to be uninitialized.
 */
typedef struct {
    logical_drive_t * logical_drive;    /**< A pointer to base Logical drive structure where the directory is located. See @ref logical_drive_t for detailed explanation.  */
    fs_dir_t fs_dir;                    /**< Directory data structure specific to the particular file system in which @c logical_drive is initialized. */
} dir_t;

/**
 * @addtogroup directory_group Directory Access
 * @brief Directory Access and Management.
 * @{
 */

/**
 * @brief Open a Directory.
 *
 * @details This API function will open an existing @c dir in a location specified by the parameter @c path,
 *          on the logical drive identified by the drive number found also in the @c path parameter.
 *          The directory data structure specific to the particular file system implementation @c fs_specific_dir,
 *          and @c dir structure will be initialized too.
 *
 * @param[inout] dir A pointer to the directory data structure, that acts as the directory identifier.
 * See @ref dir_t, structure for detailed explanation.
 * @param[in] fs_specific_dir A pointer to the directory data structure specific to the particular file system.
 * See @ref fs_dir_t structure for detailed explanation.
 * @param[in] path A null terminated string, that specifies the absolute path to the directory that needs to be opened.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 *
 * @retval FSS_OK If the directory was opened successfully,
 * @retval FSS_GENERAL_ERROR If too many directories or files are opened already,
 *         if directory identified by the @c dir paramater does not exist on the logical drive identified by the parameter @c path, etc.
 *
 * @pre A logical drive must be mounted to the file system to the location specified by the @c path
 * See @ref file_system_mount function for detailed explanation.
 *
 * @post Other directory access APIs can now be called, using the @c dir structure as identifier,
 * allowing various operations with the opened directory.
 *
 * @note Maximum 10 files and/or directories can be opened at one time. See @ref FS_MAX_OBJECTS.
 */
fs_status_t dir_open(dir_t *dir, fs_dir_t fs_specific_dir, const char* __generic_ptr path);

/**
 * @brief Close an Opened Directory.
 *
 * @details This API function will close an open @c dir object.
 *
 * @param[inout] dir A pointer to the directory data structure, that acts as the opened directory identifier.
 * See @ref dir_t, structure for detailed explanation.
 *
 * @retval FSS_OK If the directory was closed successfully,
 * @retval FSS_GENERAL_ERROR If the @c dir was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c dir must be opened first, before calling this function.
 * See @ref dir_open, function for detailed explanation.
 */
fs_status_t dir_close(dir_t *dir);

/**
 * @brief Read Directory Entry.
 *
 * @details This API function will read an directory entry, from the opened @c dir.
 *
 * @param[in] dir A pointer to the directory data structure, that acts as the opened directory identifier.
 * See @ref dir_t, structure for detailed explanation.
 * @param[in] file_information A pointer to the structure, where the read directory entry will be stored.
 *
 * @retval FSS_OK If the directory entry was read successfully.
 * @retval FSS_END_OF_DIRECTORY If read directory was null .
 * @retval FSS_GENERAL_ERROR If the @c dir was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c dir must be opened first, before calling this function.
 * See @ref dir_open, function for detailed explanation.
 */
fs_status_t dir_read(dir_t *dir, void * file_information);

/**
 * @brief Move Read/Write Offset to the beginning of the Directory.
 *
 * @details This API function will will move read/write offset of the opened @c dir,
 *          to the beginning of the opened @c dir.
 *
 * @param[in] dir A pointer to the directory data structure, that acts as the opened directory identifier.
 * See @ref dir_t, structure for detailed explanation.
 *
 * @retval FSS_OK If read/write offset of the @c dir was moved to the desired offset successfully.
 * @retval FSS_GENERAL_ERROR If the @c dir was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c dir must be opened first, before calling this function.
 * See @ref dir_open, function for detailed explanation.
 */
fs_status_t dir_rewind(dir_t *dir);

/*! @} */ // directory_group

#ifdef __cplusplus
}
#endif

#endif // !_DIR_H_
