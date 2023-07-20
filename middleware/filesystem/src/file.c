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
 * @file file.c
 * @brief File System File Access and Management.
 */

#include "file.h"
#include "fs_common.h"
#include "fatfs.h"

fs_status_t file_open(file_t * file, fs_file_t fs_specific_file, const char * __generic_ptr path, int flags)
{
    uint8_t vol_id;
    logical_drive_t * logical_drive;
    fs_status_t res;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }
    res = FILE_SYSTEM_VALIDATE_FILE(fs_specific_file);
    if (FSS_OK != res) {
        // error: the fs_specific_file parameter is NULL
        return res;
    }

    // check if the file can be opened
    res = file_system_validate_object_opening(file);
    if (FSS_OK != res) {
        // error: the file is already open, or the registry is full
        return res;
    }

    res = file_system_get_drive_id(path, &vol_id);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    // validate the logical drive
    logical_drive = file_system_get_registred_volume(vol_id);
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: logical drive is either nullptr or is not initialized
        return res;
    }

    // open fs_specific_file on the logical_drive
    res = logical_drive->vtptr->f_open(logical_drive, fs_specific_file, path, flags);

    if (FSS_OK == res) {
        // initialize the file structure
        file->logical_drive = logical_drive;
        file->fs_file = fs_specific_file;
        // register the file wtth the logical drive
        ++logical_drive->object_count;
        // register the file wtth the file system
        file_system_register_object(file);
    }

    return res;
}

fs_status_t file_close(file_t * file)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }

    // check if the file is opened
    res = file_system_validate_object_closing(file, &found_object_index);
    if (res != FSS_OK) {
        // error: the file is not open
        return res;
    }

    // close the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    res = logical_drive->vtptr->f_close(logical_drive, file->fs_file);

    if (FSS_OK == res) {
        // deinitialize the file_t structure
        file->logical_drive = (logical_drive_t *)0;
        file->fs_file = (fs_file_t)0;
        // unregister the file from the logical drive
        --logical_drive->object_count;
        // unregister the file from the file system
        file_system_unregister_object(file, found_object_index);
    }

    return res;
}

fs_status_t file_read(file_t * file, void * buffer, uint32_t bytes_to_read)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }
    res = FILE_SYSTEM_VALIDATE_FILE(buffer);
    if (FSS_OK != res) {
        // error: the buffer parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // read from the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_read(logical_drive, file->fs_file, buffer, bytes_to_read);
}

fs_status_t file_write(file_t * file, void * buffer, uint32_t bytes_to_write)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }
    res = FILE_SYSTEM_VALIDATE_FILE(buffer);
    if (FSS_OK != res) {
        // error: the buffer parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // write to the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_write(logical_drive, file->fs_file, buffer, bytes_to_write);
}

fs_status_t file_sync(file_t * file)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // sync the file->fs_file on the logical drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_sync(logical_drive, file->fs_file);
}

fs_status_t file_seek(file_t * file, int32_t offset, logical_drive_type_t starting_position)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // seek position in the file->fs_file in the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_seek(logical_drive, file->fs_file, offset, starting_position);
}

uint32_t file_tell(file_t * file)
{
    logical_drive_t * logical_drive;
    uint32_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return 0;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;    // TODO must be 0, but it manifests PIC compiler bug 
    }

    // get current read/write pointer in the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_tell(logical_drive, file->fs_file);
}

fs_status_t file_rewind(file_t * file)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // move read/write pointer to the beginning of the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_rewind(logical_drive,  file->fs_file);
}

uint32_t file_size(file_t * file)
{
    logical_drive_t * logical_drive;
    uint32_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return 0;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return 0;
    }

    // get size of the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_size(logical_drive,  file->fs_file);
}

fs_status_t file_truncate(file_t * file, uint32_t truncated_size)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_FILE(file);
    if (FSS_OK != res) {
        // error: the file parameter is NULL
        return res;
    }

    // check if the file is open
    found_object_index = file_system_check_object_registration(file);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the file must be opened first
        return FSS_GENERAL_ERROR;
    }

    // truncate the file->fs_file on the logical_drive
    logical_drive = file->logical_drive;
    return logical_drive->vtptr->f_truncate(logical_drive, file->fs_file, truncated_size);
}
