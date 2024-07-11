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
 * @file fs_common.h
 * @brief File System.
 */

#ifndef _FS_COMMON_H_
#define _FS_COMMON_H_


#define FILE_SYSTEM_VALIDATE_UNINITIALIZATION    ((uint8_t)0)
#define FILE_SYSTEM_VALIDATE_INITIALIZATION      ((uint8_t)1)

#define FILE_SYSTEM_OBJECT_NOT_FOUND             FS_MAX_OBJECTS

#define FILE_SYSTEM_VALIDATE_OBJECT(__obj__)     (void *)(__obj__) ? FSS_OK : FSS_GENERAL_ERROR
#define FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE       FILE_SYSTEM_VALIDATE_OBJECT
#define FILE_SYSTEM_VALIDATE_PHYSICAL_DRIVE      FILE_SYSTEM_VALIDATE_OBJECT
#define FILE_SYSTEM_VALIDATE_FILE                FILE_SYSTEM_VALIDATE_OBJECT
#define FILE_SYSTEM_VALIDATE_DIRECTORY           FILE_SYSTEM_VALIDATE_OBJECT

#ifdef __cplusplus
extern "C"{
#endif

typedef uint8_t file_system_validation_t;

/**
 * @ingroup logical_drive_group
 *
 * @brief Logical Drive Vector Table
 *
 * @details The struct represents a table of function pointers and it used used by @ref logical_drive_t struct,
 *          in order to call up correct functions for the file system type being used by the logical drive.
 */
struct logical_drive_vector_table {

    fs_status_t (* format)(logical_drive_t * const ptr_this);
    fs_status_t (* mount)(logical_drive_t * const ptr_this, physical_drive_t * const physical_drive);
    fs_status_t (* unmount)(logical_drive_t * const ptr_this);
    fs_status_t (* remove)(logical_drive_t * const ptr_this, const char * __generic_ptr path);
    fs_status_t (* rename)(logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path);
    fs_status_t (* mkdir)(logical_drive_t * const ptr_this, const char * __generic_ptr path);
    fs_status_t (* chdir)(logical_drive_t * const ptr_this, const char * __generic_ptr path); // TODO This function is diabled

    fs_status_t (* f_open)(logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags);
    fs_status_t (* f_close)(logical_drive_t * const ptr_this, fs_file_t file);
    fs_status_t (* f_read)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bttes_to_read);
    fs_status_t (* f_write)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write);
    fs_status_t (* f_sync)(logical_drive_t * const ptr_this, fs_file_t file);
    fs_status_t (* f_seek)(logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, fs_file_rw_pointer_t starting_position);
    uint32_t (* f_tell)(logical_drive_t * const ptr_this, fs_file_t file);
    fs_status_t (* f_rewind)(logical_drive_t * const ptr_this, fs_file_t file);
    uint32_t (* f_size)(logical_drive_t * const ptr_this, fs_file_t file);
    fs_status_t (* f_truncate)(logical_drive_t * const ptr_this, fs_file_t file, int length);

    fs_status_t (* d_open)(logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path);
    fs_status_t (* d_close)(logical_drive_t * const ptr_this, fs_dir_t dir);
    fs_status_t (* d_read)(logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information);
    fs_status_t (* d_rewind)(logical_drive_t * const ptr_this, fs_dir_t dir);
};

void file_system_initialize(logical_drive_t * ldrive_base);

logical_drive_t * file_system_get_registred_volume(const uint8_t volume);
fs_status_t file_system_get_drive_id(const char * __generic_ptr path, uint8_t * const drive_number);

uint8_t file_system_check_object_registration(void * obj);
fs_status_t file_system_validate_object_opening(void * obj);
fs_status_t file_system_validate_object_closing(void * obj, uint8_t * found_object_index);
void file_system_register_object(void * obj);
void file_system_unregister_object(void * obj, uint8_t registred_object_index);

#ifdef __cplusplus
}
#endif

#endif // !_FS_COMMON_H_
