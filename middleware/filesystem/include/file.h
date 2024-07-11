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
 * @file file.h
 * @brief File System File Access and Management.
 */

#ifndef _FILE_H_
#define _FILE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "file_system.h"

/**
 * @defgroup file_data_group File Data
 * @ingroup file_group
 * @brief File Data Structure Reference.
 */

/**
 * @ingroup file_data_group
 *
 * @brief File Data Structure.
 *
 * @details The struct is used to link file system specific file data structure @c fs_file,
 *          to the logical drive struct where the file is located.
 *          It is used as identifier for the directory in File Access API functions.
 *
 * @note The file is considered closed or uninitialized when both of its elements are NULL,
 * and if both elements are set the file is considered to be open.
 * If one element is NULL while the other is not, the directory is considered to be uninitialized.
 */
typedef struct {
    logical_drive_t * logical_drive;    /**< A pointer to base Logical drive structure where the file is located. See @ref logical_drive_t for detailed explanation.  */
    fs_file_t fs_file;                  /**< File data structure specific to the particular file system in which @c logical_drive is initialized. */
} file_t;


/**
 * @addtogroup file_group File Access
 * @ingroup file_system_group
 * @brief File Access and Management.
 * @{
 */

/**
 * @brief Open or Create a File.
 *
 * @details This API function will open a @c file in a location specified by the parameter @c path,
 *          on the logical drive identified by the drive number found also in the @c path parameter.
 *          The file data structure specific to the particular file system implementation @c fs_specific_file,
 *          and  @c file structure will be initialized too. Parameter @c flags will affect the circumstances
 *          of the file creation and/or modification, as well what operations can be performed later with it.
 *
 * @param[inout] file A pointer to the file data structure, that acts as the file identifier.
 * See @ref file_t, structure for detailed explanation.
 * @param[in] fs_specific_file A pointer to the file data structure specific to the particular file system.
 * See @ref fs_file_t structure for detailed explanation.
 * @param[in] path A null terminated string, that specifies the absolute path to the file that needs to be opened.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 * @param[in] flags Determins the type of access and open method for the file.
 * It is specified by a combination of following flags. See @ref file_flags_group, macros for detailed explanation.
 *
 * @retval FSS_OK If file was opened successfully,
 * @retval FSS_GENERAL_ERROR If too many files were opened already, or if @c flags paramater
 *         does not allow creation of the new file but no @c file is found on the drive, etc.
 *
 * @pre A logical drive must be mounted to the file system to the location specified by the @c path
 * See @ref file_system_mount function for detailed explanation.
 *
 * @post Other file access APIs can now be called, using the @c file structure as identifier,
 * allowing various operations with the opened file.
 *
 * @note Maximum 10 files and/or directories can be opened at one time. See @ref FS_MAX_OBJECTS.
 */
fs_status_t file_open(file_t * file, fs_file_t fs_specific_file, const char * __generic_ptr path, int flags);

/**
 * @brief Close the Opened File.
 *
 * @details This API function will close an open @c file object. If the file has been changed,
 *          the cached information of the file will be written to the drive specified by the @c file structure.
 *
 * @param[inout] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @retval FSS_OK If file was closed successfully,
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_close(file_t * file);

/**
 * @brief Read Data from the File.
 *
 * @details This API function will read @c bytes_to_read number of bytes of data, from the opened @c file,
 *          starting from the offset pointed by the read/write pointer of the @c file object, and store it into the @c buffer.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 * @param[in] buffer A pointer to the buffer address, where the read data will be stored.
 * @param[in] bytes_to_read Specifies number of bytes of data that needs to be read from the @c file.
 *
 * @retval FSS_OK If all the data was read successfully.
 * @retval FSS_END_OF_FILE If the end of the file is reached before the @c bytes_to_read number of bytes is read from it.
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_read(file_t * file, void * buffer, uint32_t bytes_to_read);

/**
 * @brief Write Data to a File.
 *
 * @details This API function will write @c bytes_to_write number of bytes of data, from the the @c buffer to the opened @c file,
 *          starting from the offset pointed by the read/write pointer of the @c file object, and store it into the @c buffer.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 * @param[in] buffer A pointer to the buffer address, where data needs to be written is stored.
 * @param[in] bytes_to_write Specifies number of bytes of data that needs to be written to the @c file.
 *
 * @retval FSS_OK If all the data was read successfully.
 * @retval FSS_DRIVE_FULL If during the writing to the opened @c file, memory of the logical drive
 * identified by the @c file structure, is filled before @c bytes_to_write number of bytes could be written.
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_write(file_t * file, void * buffer, uint32_t bytes_to_write);

/**
 * @brief Flush Cached Data of a File.
 *
 * @details This API function will flush the cached data of a file to the logical drive identified by the @c file structure.
 *          It performs the same process as, @ref file_close API, but the @c file will remain open for further
 *          read/write/seek operations on it. Performing a sync operation can minimize the risk
 *          of data loss due to a loss of power, or media removal.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @retval FSS_OK If cached data was flushed successfully,
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_sync(file_t * file);

/**
 * @brief Move Read/Write Pointer of the File.
 *
 * @details This API function will move read/write pointer of the opened @c file,
 *          by @c offset from the position indicated by the @c starting_position parameter.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 * @param[in] offset Byte offset from @c starting_position to move read/write pointer of the opened @c file.
 * Negative values will move it toward the beginning, while positive values will move it towards the end of the file.
 * @param[in] starting_position Position in the @c file, from where read/write pointer of the @c file will be moved from.
 *
 * @retval FSS_OK If read/write pointer of the @c file was moved to the desired offset successfully.
 * @retval FSS_DRIVE_FULL If positive offset was used, and if the @c file needed to be expanded
 * but the was not more free space on the logical drive identified by the @c file structure.
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 *
 * @note Negative value @c offset can move the read/write pointer only up to the beginning of the @c file.
 * @note Positive value offset may expand the @c file size.
 */
fs_status_t file_seek(file_t * file, int32_t offset, logical_drive_type_t starting_position);

/**
 * @brief Get Current Read/Write Pointer of the File.
 *
 * @details This API function will return current read/write pointer of the opened @c file structure.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @return read/write pointer of the @c file.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
uint32_t file_tell(file_t * file);

/**
 * @brief Move Read/Write Pointer to the beginning of the File.
 *
 * @details This API function will will move read/write pointer of the opened @c file,
 *          to the beginning of the opened @c file.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @retval FSS_OK If read/write pointer of the @c file was moved to the desired offset successfully.
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_rewind(file_t * file);

/**
 * @brief Get Size of the File.
 *
 * @details This API function will return size of the opened @c file.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @return Size of the @c file in uint of bytes.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
uint32_t file_size(file_t * file);

/**
 * @brief Truncate File Size.
 *
 * @details This API function will truncate the opened @c file to the size indicated by the parameter @c truncated_size.
 *
 * @param[in] file A pointer to the file data structure, that acts as the opened file identifier.
 * See @ref file_t, structure for detailed explanation.
 *
 * @retval FSS_OK If the @c file was truncated successfully.
 * @retval FSS_GENERAL_ERROR If the @c file was not opened, or if there was an error
 * on the physical drive linked to the logical drive, etc.
 *
 * @pre The @c file must be opened first, before calling this function.
 * See @ref file_open, function for detailed explanation.
 */
fs_status_t file_truncate(file_t * file, uint32_t truncated_size);

/*! @} */ // file_group

#ifdef __cplusplus
}
#endif

#endif // !_FILE_H_
