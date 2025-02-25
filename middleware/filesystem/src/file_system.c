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
 * @file file_system.c
 * @brief File System
 */

#include "file_system.h"
#include "fs_common.h"

#define FILE_SYSTEM_DRIVE_UNREGISTRATION          ((uint8_t)0)
#define FILE_SYSTEM_DRIVE_REGISTRATION            ((uint8_t)1)

typedef uint8_t file_system_registration_t;

typedef struct {
    logical_drive_t * logical_drive;
    void * fs_obj;
} file_system_object_t;

typedef struct {
    void * object[FS_MAX_OBJECTS];
    uint8_t first_free_pointer;
    uint8_t count;
} fs_object_register_t;

static logical_drive_t * _logical_drive_registry[FS_MAX_VOLUMES] = {(void *)0, (void *)0, (void *)0, (void *)0, (void *)0};
static fs_object_register_t _file_system_object_register = {
    .object = {(void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0},
    .first_free_pointer = 0,
    .count = 0
};
static uint8_t _registred_drive_count = 0;

static fs_status_t fs_default_format(logical_drive_t * const ptr_this);
static fs_status_t fs_default_mount(logical_drive_t * const ptr_this, physical_drive_t * const physical_drive);
static fs_status_t fs_default_unmount(logical_drive_t * const ptr_this);
static fs_status_t fs_default_remove(logical_drive_t * const ptr_this, const char * __generic_ptr path);
static fs_status_t fs_default_rename(logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path);
static fs_status_t fs_default_mkdir(logical_drive_t * const ptr_this, const char * __generic_ptr path);
static fs_status_t fs_default_chdir(logical_drive_t * const ptr_this, const char * __generic_ptr path);

static fs_status_t fs_default_fopen(logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags);
static fs_status_t fs_default_fclose(logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fs_default_fread(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read);
static fs_status_t fs_default_fwrite(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write);
static fs_status_t fs_default_fsync(logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fs_default_fseek(logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, logical_drive_type_t starting_position);
static uint32_t fs_default_ftell(logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fs_default_frewind(logical_drive_t * const ptr_this, fs_file_t file);
static uint32_t fs_default_fsize(logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fs_default_ftruncate(logical_drive_t * const ptr_this, fs_file_t file, int length);

static fs_status_t fs_default_dopen(logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path);
static fs_status_t fs_default_dclose(logical_drive_t * const ptr_this, fs_dir_t dir);
static fs_status_t fs_default_dread(logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information);
static fs_status_t fs_default_drewind(logical_drive_t * const ptr_this, fs_dir_t dir);

void file_system_initialize(logical_drive_t * ldrive_base)
{
    // if some of the vector table function pointers is not set, set it here to default functions
    if (0 == ldrive_base->vtptr->format) {
        ldrive_base->vtptr->format = &fs_default_format;
    }
    if (0 == ldrive_base->vtptr->mount) {
        ldrive_base->vtptr->mount = &fs_default_mount;
    }
    if (0 == ldrive_base->vtptr->unmount) {
        ldrive_base->vtptr->unmount = &fs_default_unmount;
    }
    if (0 == ldrive_base->vtptr->remove) {
        ldrive_base->vtptr->remove = &fs_default_remove;
    }
    if (0 == ldrive_base->vtptr->rename) {
        ldrive_base->vtptr->rename = &fs_default_rename;
    }
    if (0 == ldrive_base->vtptr->mkdir) {
        ldrive_base->vtptr->mkdir = &fs_default_mkdir;
    }
    if (0 == ldrive_base->vtptr->chdir) {
        ldrive_base->vtptr->chdir = &fs_default_chdir;
    }

    if (0 == ldrive_base->vtptr->f_open) {
        ldrive_base->vtptr->f_open = &fs_default_fopen;
    }
    if (0 == ldrive_base->vtptr->f_close) {
        ldrive_base->vtptr->f_close = &fs_default_fclose;
    }
    if (0 == ldrive_base->vtptr->f_read) {
        ldrive_base->vtptr->f_read = &fs_default_fread;
    }
    if (0 == ldrive_base->vtptr->f_write) {
        ldrive_base->vtptr->f_write = &fs_default_fwrite;
    }
    if (0 == ldrive_base->vtptr->f_sync) {
        ldrive_base->vtptr->f_sync= &fs_default_fsync;
    }
    if (0 == ldrive_base->vtptr->f_seek) {
        ldrive_base->vtptr->f_seek = &fs_default_fseek;
    }
    if (0 == ldrive_base->vtptr->f_tell) {
        ldrive_base->vtptr->f_tell= &fs_default_ftell;
    }
    if (0 == ldrive_base->vtptr->f_rewind) {
        ldrive_base->vtptr->f_rewind = &fs_default_frewind;
    }
    if (0 == ldrive_base->vtptr->f_size) {
        ldrive_base->vtptr->f_size = &fs_default_fsize;
    }
    if (0 == ldrive_base->vtptr->f_truncate) {
        ldrive_base->vtptr->f_truncate = &fs_default_ftruncate;
    }

    if (0 == ldrive_base->vtptr->d_open) {
        ldrive_base->vtptr->d_open = &fs_default_dopen;
    }
    if (0 == ldrive_base->vtptr->d_close) {
        ldrive_base->vtptr->d_close = &fs_default_dclose;
    }
    if (0 == ldrive_base->vtptr->d_read) {
        ldrive_base->vtptr->d_read = &fs_default_dread;
    }
    if (0 == ldrive_base->vtptr->d_rewind) {
        ldrive_base->vtptr->d_rewind = &fs_default_drewind;
    }

    // set default values
    ldrive_base->type = FS_TYPE_UNINITIALIZED;
    ldrive_base->volume_id = 0;
    ldrive_base->object_count = 0;
    ldrive_base->error = FSS_OK;
}

static fs_status_t fs_default_format(logical_drive_t * const ptr_this)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_mount(logical_drive_t * const ptr_this, physical_drive_t * const physical_drive)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_unmount(logical_drive_t * const ptr_this)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_remove(logical_drive_t * const ptr_this, const char * __generic_ptr path)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_rename(logical_drive_t * const ptr_this, const char * oldPath, const char * newPath)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_mkdir(logical_drive_t * const ptr_this, const char * __generic_ptr path)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_chdir(logical_drive_t * const ptr_this, const char * __generic_ptr path)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fopen(logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fclose(logical_drive_t * const ptr_this, fs_file_t file)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fread(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fwrite(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fsync(logical_drive_t * const ptr_this, fs_file_t file)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_fseek(logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, logical_drive_type_t starting_position)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static uint32_t fs_default_ftell(logical_drive_t * const ptr_this, fs_file_t file)
{
    // error: the function is either disabled or not implemented at all
    return 0;
}

static fs_status_t fs_default_frewind(logical_drive_t * const ptr_this, fs_file_t file)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static uint32_t fs_default_fsize(logical_drive_t * const ptr_this, fs_file_t file)
{
    // error: the function is either disabled or not implemented at all
    return 0;
}

static fs_status_t fs_default_ftruncate(logical_drive_t * const ptr_this, fs_file_t file, int length)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_dopen(logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_dread(logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_dclose(logical_drive_t * const ptr_this, fs_dir_t dir)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

static fs_status_t fs_default_drewind(logical_drive_t * const ptr_this, fs_dir_t dir)
{
    // error: the function is either disabled or not implemented at all
    return FSS_NOT_IMPLEMENTED;
}

logical_drive_t * file_system_get_registred_volume(const uint8_t volume)
{
    // error: the function is either disabled or not implemented at all
    return _logical_drive_registry[volume];
}

fs_status_t file_system_validate_parameter(void * function_parameter)
{
    // check if the parameter is NULL
    return function_parameter ? FSS_OK : FSS_GENERAL_ERROR;
}

fs_status_t file_system_get_drive_id(const char * __generic_ptr path, uint8_t * const drive_number)
{
    // validate path
    if (!path || !path[0]) {
        // error: no path provided
        return FSS_GENERAL_ERROR;
    }

    *drive_number = 0;

    // extract drive id
    if (':' == path[1]) {
        // if drive path is specified, extract the drive number
        *drive_number = path[0] - '0';
        if (*drive_number >= FS_MAX_VOLUMES) {
            // error: illegal drive number
            return FSS_GENERAL_ERROR;
        }
    }
    // if drive path is not specified, 0 is assumed

    return FSS_OK;
}

static fs_status_t file_system_validate_registration(logical_drive_t * const logical_drive, const uint8_t drive_number, file_system_registration_t reg_type)
{
    uint8_t i;
    uint8_t extremum = FILE_SYSTEM_DRIVE_REGISTRATION == reg_type ? FS_MAX_VOLUMES : 0;

    // check for file system iregularites
    if (_registred_drive_count > FS_MAX_VOLUMES) {
        // error: number of registred drives must be positive number and lower then or equal to FS_MAX_VOLUMES
        // illegal state: APIs should not allow _registred_drive_count to get such a value
        return FSS_GENERAL_ERROR;
    }
    // check if new drives can be registred
    if (extremum == _registred_drive_count) {
        // error: maxiumum physical drive count reached.
        return FSS_GENERAL_ERROR;
    }

     if (FILE_SYSTEM_DRIVE_REGISTRATION == reg_type) {
        // prevent mounting of the same logigal drive more then once
        for (i = 0; i < FS_MAX_VOLUMES; i++) {
            if (_logical_drive_registry[i] == logical_drive) {
                // error: logical drive is already registred
                return FSS_GENERAL_ERROR;
            }
        }
        // check if registry slot is already taken
        if (_logical_drive_registry[drive_number] != 0) {
            // error: drive number is already taken, consider unmounting first
            return FSS_GENERAL_ERROR;
        }
    }
    else {
        // check if there are files or directories opened on the file system volume
        if (logical_drive->object_count > 0) {
            // error: oobjects on this files system need to be closed before unmounting
            return FSS_GENERAL_ERROR;
        }
    }

    return FSS_OK;
}

uint8_t file_system_check_object_registration(void * obj)
{
    uint8_t i = 0;
    uint8_t found_object_index = FILE_SYSTEM_OBJECT_NOT_FOUND;

    // search for file or directory in the registry
    if (0 < _file_system_object_register.count) {
        for ( ; i < FS_MAX_OBJECTS; i++) {
            if (obj == _file_system_object_register.object[i]) {
                // file or direcory is found in the registry
                found_object_index = i;
                break;
            }
        }
    }

    return found_object_index;
}

fs_status_t file_system_validate_object_opening(void * obj)
{
    uint8_t found_object_index;

    // if object registry is full
    if (FS_MAX_OBJECTS == _file_system_object_register.count) {
        // error: cannot open any more files or directories
        return FSS_GENERAL_ERROR;
    }

    // search for file or directory in the registry
    found_object_index = file_system_check_object_registration(obj);

    // if the file orthe directory was found in the registry
    if (FILE_SYSTEM_OBJECT_NOT_FOUND != found_object_index) {
        // error: file is already opened
        return FSS_GENERAL_ERROR;
    }

    return FSS_OK;
}

fs_status_t file_system_validate_object_closing(void * obj, uint8_t * found_object_index)
{
    // search for file or directory in the registry
    *found_object_index = file_system_check_object_registration(obj);

    // if the file or the directory was not found in the registry
    if (FILE_SYSTEM_OBJECT_NOT_FOUND == *found_object_index) {
        // error: file is already closed
        return FSS_GENERAL_ERROR;
    }

    return FSS_OK;
}

void file_system_register_object(void * obj)
{

    // register the file or directory
    _file_system_object_register.object[_file_system_object_register.first_free_pointer] = obj;
    ++_file_system_object_register.count;
    // find first free object register slot index
    do {
        ++_file_system_object_register.first_free_pointer;
    } while (((void *)0 != _file_system_object_register.object[_file_system_object_register.first_free_pointer])
                && (FS_MAX_OBJECTS > _file_system_object_register.first_free_pointer));
}

void file_system_unregister_object(void * obj, uint8_t registred_object_index)
{
    // unregister the opened file or directory
    _file_system_object_register.object[registred_object_index] = (void *)0;
    --_file_system_object_register.count;
    // update index of the first free slot in the object register
    if (registred_object_index < _file_system_object_register.first_free_pointer) {
        _file_system_object_register.first_free_pointer = registred_object_index;
    }
}

fs_status_t file_system_format(const char * __generic_ptr path)
{
    fs_status_t res;
    uint8_t drive_number;
    logical_drive_t * logical_drive;

    res = file_system_get_drive_id(path, &drive_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    logical_drive = _logical_drive_registry[drive_number];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    return logical_drive->vtptr->format(logical_drive);
}

fs_status_t file_system_mount(logical_drive_t * const logical_drive, const char * __generic_ptr path, physical_drive_t * const physical_drive)
{
    fs_status_t res;
    uint8_t drive_number;

    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: logical drive is either nullptr or is not initialized
        return res;
    }

    res = file_system_get_drive_id(path, &drive_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    res = FILE_SYSTEM_VALIDATE_PHYSICAL_DRIVE(physical_drive);
    if (res != FSS_OK) {
        // error: physical drive is either nullptr or is not initialized
        return res;
    }

    res = file_system_validate_registration(logical_drive, drive_number, FILE_SYSTEM_DRIVE_REGISTRATION);
    if (res != FSS_OK) {
        // error: mounting is not possible
        return res;
    }

    // mount file sytem
    logical_drive->volume_id = drive_number;
    res = logical_drive->vtptr->mount(logical_drive, physical_drive);

    if (0 == res) {
        // register the file system volume
        _logical_drive_registry[drive_number] = logical_drive;
        // register the physical drive
        ++_registred_drive_count;
    }

    return res;
}

fs_status_t file_system_unmount(const char * __generic_ptr path)
{
    uint8_t drive_number;
    logical_drive_t * logical_drive;
    fs_status_t res;

    res = file_system_get_drive_id(path, &drive_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    logical_drive = _logical_drive_registry[drive_number];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    res = file_system_validate_registration(logical_drive, drive_number, FILE_SYSTEM_DRIVE_UNREGISTRATION);
    if (res != FSS_OK) {
        // error: unmounting is not possible
        return res;
    }

    // unmount volume
    res = logical_drive->vtptr->unmount(logical_drive);
    if (0 == res) {
        // unregister file system volume
        _logical_drive_registry[drive_number] = (logical_drive_t *)0;
        // unregister physical drive
        --_registred_drive_count;
        // deinit logical drive
        logical_drive->type = FS_TYPE_UNINITIALIZED;

    }

    return res;
}

fs_status_t file_system_remove(const char * __generic_ptr path)
{
    uint8_t volume_number;
    logical_drive_t * logical_drive;
    fs_status_t res = 1;

    res = file_system_get_drive_id(path, &volume_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    logical_drive = _logical_drive_registry[volume_number];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    // remove the object from the files system volume
    return logical_drive->vtptr->remove(logical_drive, path);
}

fs_status_t file_system_rename(const char * __generic_ptr old_path, const char * __generic_ptr new_path)
{
    uint8_t volume_number_old;
    uint8_t volume_number_new;
    logical_drive_t * logical_drive;
    fs_status_t res = 1;

    res = file_system_get_drive_id(old_path, &volume_number_old);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    res = file_system_get_drive_id(new_path, &volume_number_new);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    if (volume_number_old != volume_number_new) {
        // error: both old new new file must be on same drive
        return FSS_GENERAL_ERROR;
    }

    logical_drive = _logical_drive_registry[volume_number_old];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    return logical_drive->vtptr->rename(logical_drive, old_path, new_path);
}

fs_status_t file_system_mkdir(const char * __generic_ptr path)
{
    int8_t volume_number;
    logical_drive_t * logical_drive;
    fs_status_t res = 1;

    res = file_system_get_drive_id(path, &volume_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    logical_drive = _logical_drive_registry[volume_number];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    // make new directory
    return logical_drive->vtptr->mkdir(logical_drive, path);
}

fs_status_t file_system_chdir(const char * __generic_ptr path)
{
    int8_t volume_number;
    logical_drive_t * logical_drive;
    fs_status_t res = 1;

    res = file_system_get_drive_id(path, &volume_number);
    if (res != FSS_OK) {
        // error: given path is not valid
        return res;
    }

    logical_drive = _logical_drive_registry[volume_number];
    res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(logical_drive);
    if (res != FSS_OK) {
        // error: drive not found in registry
        return res;
    }

    // change directory
    return logical_drive->vtptr->chdir(logical_drive, path);
}
