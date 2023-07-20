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
 * @file dir.c
 * @brief File System Directory Access and Management.
 */

#include "dir.h"
#include "fs_common.h"

fs_status_t dir_open(dir_t * dir, fs_dir_t fs_specific_dir, const char * __generic_ptr path)
{
    uint8_t vol_id;
    logical_drive_t * logical_drive;
    fs_status_t res;

    res = FILE_SYSTEM_VALIDATE_OBJECT(dir);
    if (FSS_OK != res) {
        // error: the dir parameter is NULL
        return res;
    }
    res = FILE_SYSTEM_VALIDATE_OBJECT(fs_specific_dir);
    if (FSS_OK != res) {
        // error: the fs_specific_dir parameter is NULL
        return res;
    }

    // check if the directory can be opened
    res = file_system_validate_object_opening(dir);
    if (FSS_OK != res) {
        // error: directory is either already open, or the registry is full
        return res;
    }

    res = file_system_get_drive_id(path, &vol_id);
    if (FSS_OK != res) {
        // error: given path is not valid
        return res;
    }

    // validate the logical drive
    logical_drive = file_system_get_registred_volume(vol_id);
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (FSS_OK != res) {
        // error: logical drive is either nullptr or is not initialized
        return res;
    }

    // open the fs_specific_dir on the logical_drive
    res = logical_drive->vtptr->d_open(logical_drive, fs_specific_dir, path);

    if (FSS_OK == res) {
        // initialize the dir structure
        dir->logical_drive = logical_drive;
        dir->fs_dir = fs_specific_dir;
        // register the directory with the logical drive
        ++logical_drive->object_count;
        // register the directory with the file system
        file_system_register_object(dir);
    }

    return res;
}

fs_status_t dir_close(dir_t * dir)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_OBJECT(dir);
    if (FSS_OK != res) {
        // error: the dir parameter is NULL
        return res;
    }

    // check if the directory is open
    res = file_system_validate_object_closing(dir, &found_object_index);
    if (FSS_OK != res) {
        // error: the diurectory is not open
        return res;
    }

    // close the dir->fs_dir on the logical_drive
    logical_drive = dir->logical_drive;
    res = logical_drive->vtptr->d_close(logical_drive, dir->fs_dir);

    if (FSS_OK == res) {
        // deinitialize the dir_t structure
        dir->logical_drive = (logical_drive_t *)0;
        dir->fs_dir = (fs_dir_t)0;
        // unregister the directory from the logical drive
        --logical_drive->object_count;
        // unregister the directory from the file system
        file_system_unregister_object(dir, found_object_index);
    }

    return res;
}

fs_status_t dir_read(dir_t * dir, void * file_information)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_OBJECT(dir);
    if (FSS_OK != res) {
        // error: the dir parameter is NULL
        return res;
    }
    res = FILE_SYSTEM_VALIDATE_OBJECT(file_information);
    if (FSS_OK != res) {
        // error: the file_information parameter is NULL
        return res;
    }

    // check if the directory is open
    found_object_index = file_system_check_object_registration(dir);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the directory must be opened first
        return FSS_GENERAL_ERROR;
    }

    // read entry from dir->fs_dir on the logical_drive
    logical_drive = dir->logical_drive;
    return logical_drive->vtptr->d_read(logical_drive, dir->fs_dir, file_information);
}

fs_status_t dir_rewind(dir_t * dir)
{
    logical_drive_t * logical_drive;
    fs_status_t res;
    uint8_t found_object_index;

    res = FILE_SYSTEM_VALIDATE_OBJECT(dir);
    if (FSS_OK != res) {
        // error: the dir parameter is NULL
        return res;
    }

    // check if the directory is open
    found_object_index = file_system_check_object_registration(dir);
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == found_object_index) {
        // error: the directory must be opened first
        return FSS_GENERAL_ERROR;
    }

    // move read/write offset to the beginning of the dir->fs_dir on the logical_drive
    logical_drive = dir->logical_drive;
    return logical_drive->vtptr->d_rewind(logical_drive, dir->fs_dir);
}
