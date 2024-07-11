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
 * @file file_system.h
 * @brief File System.
 */

#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "physical_drive.h"
#include "cstdio.h"
#include "assembly.h"

#define NOP() assembly(nop)

/**
 * @defgroup file_system_group File System
 * @ingroup middlewaregroup
 * @brief File System Reference.
 */

/**
 * @defgroup file_system_config_group File System Configuration
 * @ingroup file_system_group
 * @brief File System Configuration.
 * @{
 */

/**
 * @brief Specifies the maximum amount of logical/physical drives that can be mounted at the same time.
 *
 * @details Number is chosen based on number of mikro BUS slots on development boards.
 */
#define FS_MAX_VOLUMES                   ((uint8_t)5)

/**
 * @brief: Specifies the maximum number of files and directories that can be opened at the same time.
 *
 * @details Number is chosen so that every logical drive can have at least one file and one directory open at a time.
 */
#define FS_MAX_OBJECTS                   ((uint8_t)10)

/*! @} */ // file_system_config_group

/**
 * @defgroup file_system_status_group File System APIs Status
 * @ingroup file_system_group
 * @brief File System API function return values.
 * @{
 */

/**
 * @brief: Success.
 */
#define FSS_OK                           ((uint8_t)0)

/**
 * @brief: Error.
 */
#define FSS_GENERAL_ERROR                ((uint8_t)1)

/**
 * @brief: Drive memory is full, cannot write anymore into it.
 */
#define FSS_DRIVE_FULL                   ((uint8_t)2)

/**
 * @brief: The end of the file is reached while reading from it.
 */
#define FSS_END_OF_FILE                  ((uint8_t)3)

/**
 * @brief: The end of the directory is reached while reading its entries.
 */
#define FSS_END_OF_DIRECTORY             ((uint8_t)4)

/**
 * @brief: Function is either not implemented, or it is disabled.
 */
#define FSS_NOT_IMPLEMENTED              ((uint8_t)5)

/*! @} */ // file_system_status_group


/**
 * @defgroup file_flags_group File Flags
 * @ingroup file_data_group
 *
 * @brief Mode Flags used by @ref file_open API.
 *
 * @details Mode Flags used by @ref file_open API, that specifies the type of access and open method for the file.
 *          It is specified by a combination of following flags.
 * @{
 */

/**
 * @brief: Specifies read access to the file. Data can be read from the file.
 */
#define	FS_FILE_READ                     0x01

/**
 * @brief: Specifies write access to the file. Data can be written to the file. Combine with FS_FILE_READ for read-write access.
 */
#define	FS_FILE_WRITE                    0x02

/**
 * @brief: Opens a file. The function fails if the file is not existing.
 */
#define	FS_FILE_OPEN_EXISTING            0x00

/**
 * @brief: Creates a new file. The function fails, if the file is existing.
 */
#define	FS_FILE_CREATE_NEW               0x04

/**
 * @brief: Creates a new file. If the file is existing, it will be truncated and overwritten.
 */
#define	FS_FILE_CREATE_ALWAYS            0x08

/**
 * @brief: Opens the file if it is existing. If not, a new file will be created.
 */
#define	FS_FILE_OPEN_ALWAYS              0x10

/**
 * @brief: Same as FS_FILE_OPEN_ALWAYS except the read/write pointer is set at the end of the file.
 */
#define	FS_FILE_OPEN_APPEND              0x30

/*! @} */ // file_flags_group


/**
 * @brief: File System API return value
 *
 * @details Specifies the status of File System API execution, whether it was completed successfully
 *          or if it did not, and if did not, then why.
 */
typedef int8_t fs_status_t;


/**
 * @brief: @ref file_seek API Starting Offset
 * @details Specifies from what position in the file the API should start seeking.
 */
typedef enum {
    SEEK_START = 0, /**< Seek from the beginning of the file. */
    SEEK_CURRENT,   /**< Seek from the cursor's current position in the file. */
    SEEK_END,       /**< Seek from the end of the file. */
} fs_file_rw_pointer_t;

/**
 * @brief: File data specific to a particular file system.
 *
 * @details Allows file system APIs to accept file data struct parameter,
 *          no matter what particular file system implementation is used.
 */
typedef void * fs_file_t;


/**
 * @brief: Directory Data specific to a particular File System.
 *
 * @details Allows file system APIs to accept file data struct parameter,
 *          no matter what particular file system implementation of file data structure is used.
 */
typedef void * fs_dir_t;

/**
 * @ingroup logical_drive_group
 *
 * @brief Logical Drive Vector Table
 *
 * @details The struct represents a table of function pointers and it used used by @ref logical_drive_t struct,
 *          in order to call up correct functions for the file system type being used by the logical drive.
 */
typedef struct logical_drive_vector_table logical_drive_vector_table_t;


/**
 * @brief Logical Drive File System Type Enumerator.
 * @details Used to specify what file system is logical drive configured in.
 */
typedef enum {
    FS_TYPE_UNINITIALIZED = 0, /**< Logical Drive structure is not initialized. */
    FS_TYPE_FATFS              /**< Logical Drive structure is initialized as FatFs. */
} logical_drive_type_t;

/**
 * @defgroup logical_drive_group Logical Drive
 * @ingroup file_system_group
 * @brief Logical Drive Data Structures Reference.
 * @{
 */

/**
 * @brief Logical Drive Base Data Structure.
 *
 * @details Keeps track of the relevant data for the logical drive and manages what APIs,
 * are being called depending on what type of file system it is initialized in.
 * It's intended usage is, as a base structure of a derived structures, eg. @ref fatfs_logical_drive_t.
 * It is not intended to be used independently.
 */
typedef struct {
    logical_drive_vector_table_t * vtptr; /**< Logical drive table with function pointers to specific file system APIs implementations. See @ref logical_drive_vector_table_t structure. */
    logical_drive_type_t type;            /**< Type of files system that this logical drive uses. See @ref logical_drive_type_t structure */
    uint8_t volume_id;                    /**< Logical drive id. */
    uint8_t object_count;                 /**< Number of open files and directories on this logical drive */
    uint8_t error;                        /**< Tracks APIs statuses and errors on this logical drive */
} logical_drive_t;

/*! @} */ // logical_drive_group


/**
 * @defgroup file_system_management_group File System Management
 * @ingroup file_system_group
 * @brief File System Management API Reference.
 * @details Volume, File and Directory Management and System Configuration.
 * @{
 */

/**
 * @brief Format the Logical Drive.
 *
 * @details This API function will format the logical drive, identified by its drive number specified in the parameter @c path.
 *          It will use the format function defined in particular files system, in which the logical drive is initialized in,
 *          with its default configuration.
 *
 * @param[in] path A null terminated string, that specifies the drive number of the logical drive that will be formatted.
 * It should contain the drive number and semicolon at the beginning of the string,  eg @c "3:/". If it does not,
 * the default logical drive, @c 0:, will be assumed.
 * @retval FSS_OK If the logical drive was formatted successfully,
 * @retval FSS_GENERAL_ERROR If the logical drive was not mounted first,
 *         if the provided path was wrong, etc.
 *
 * @pre The logical drive must be mounted before this API is called.
 * See @ref file_system_mount for detailed explanation.
 */
fs_status_t file_system_format(const char * __generic_ptr path);

/**
 * @brief Mount Logical Drive to the File System.
 *
 * @details This API function will mount the logical drive identified by its base @c ldrive_base,
 *          to the file system by registering it with the drive number specified by the parameter @c path,
 *          and then linking it with the physical drive identified by its base @c pdrive_base.
 *          Parts of the structure specific to the particular file system implementation,
 *          used by the logical drive will be initialized too.
 *
 * @param[in] ldrive_base A pointer to the logical drive base structure.
 * See @ref logical_drive_t, and @ref fatfs_logical_drive_t structures for detailed explanation.
 * @param[in] path A null terminated string, that specifies the drive number that will act
 * as the logical drive identifier by the file system.
 * It should contain the drive number and semicolon at the beginning of the string, eg @c "3:/". If it does not,
 * the default logical drive, @c 0:, will be assumed.
 * @param[in] pdrive_base A pointer to physical drive that will be linked with the mounted logical drive.
 * See @ref physical_drive_t, and @ref sdspi_physical_drive_t structures for detailed explanation.
 *
 * @retval FSS_OK If the logical drive was mounted successfully,
 * @retval FSS_GENERAL_ERROR If too many drives were mounted already, or if provided drive number
 *         in the @c path parameter already has registered drive with it, etc.
 *
 * @pre @c ldrive_base and @c pdrive_base structures must be initialized before calling this function.
 * See @ref fatfs_initialize, and @ref sdspi_physical_drive_init functions for detailed explanation.
 *
 * @post Operation on files and directories on the mounted logical drive can now be performed.
 * Other file system APIs can now be called, and to reference the logical drive,
 * drive number specified in @c path parameter should be used, in their @c path parameters.
 *
 * @note Maximum 5 logical drives can be mounted at the file system at one time. See @ref FS_MAX_VOLUMES.
 * @note Both @c ldrive_base and @c pdrive_base should be used as bases of derived structures.
 * Eg. @ref fatfs_logical_drive_t, and @ref sdspi_physical_drive_t.
 */
fs_status_t file_system_mount(logical_drive_t * const ldrive_base, const char * __generic_ptr path, physical_drive_t * const pdrive_base);

/**
 * @brief Unmount Logical Drive from the File System.
 *
 * @details This API function will unmount the logical drive, identified by its drive number specified in the @c path parameter,
 *          from the file system, deinitialize its structure, and break the link with its corresponding physical drive.
 *          Parts of the structure specific to the particular file system implementation,
 *          used by the logical drive will be uninitialized too. If the corresponding physical drive
 *          is not linked with any other logical drive, the physical drive structure will also be uninitialized.
 *
 * @param[in] path A null terminated string, that specifies the drive number of the logical drive that will be unmounted.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 *
 * @retval FSS_OK If the logical drive was unmounted successfully,
 * @retval FSS_GENERAL_ERROR If the logical drive was not mounted first,
 * if there are files and directories open on the logical drive, etc.
 *
 * @pre The logical drive must be mounted before this API is called.
 * See @ref file_system_mount for detailed explanation.
 *
 * @post Any further usage of unmounted drive structures will require their re-initialization.
 * See @ref fatfs_initialize, and @ref sdspi_physical_drive_init functions for detailed explanation.
 *
 * @note Open files or directories on the logical drive identified by the @path should be closed before calling this function.
 */
fs_status_t file_system_unmount(const char * __generic_ptr path);

/**
 * @brief Removes a File or a Directory.
 *
 * @details This function will remove a file or a directory specified by the @c path parameter,
 *          found on the logical drive identified by the drive number specified also in the @c path parameter.
 *
 * @param[in] path A null terminated string, that specifies the absolute path to the file or directory that needs to be removed.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 *
 * @retval FSS_OK If a file or a directory was removed successfully,
 * @retval FSS_GENERAL_ERROR If the logical drive was not mounted first,
 *         if file or directory was not found on the drive, etc.
 *
 * @warning File or directory that needs to be removed, must be closed before this function is called.
 *
 * @pre The logical drive must be mounted before this API is called.
 * See @ref file_system_mount for detailed explanation.
 */
fs_status_t file_system_remove(const char * __generic_ptr path);

/**
 * @brief Renames a File or a Directory.
 *
 * @details This function will rename a file or a directory, specified by the @c old_path parameter,
 *          found on the logical drive identified by the drive number specified also in the @c old_path parameter,
 *          with the name specified by the parameter @c new_path.
 *
 * @param[in] old_path A terminated string, that specifies the absolute path to the file or directory that needs to be renamed.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 * @param[in] new_path A string that specifies new file or directory name in form of an absolute path.
 * If it contains drive number, it will be ignored.
 *
 * @retval FSS_OK If a file or directory was renamed successfully,
 * @retval FSS_GENERAL_ERROR If the logical drive was not mounted first,
 *         if file or directory that needs to be renamed was not found on the drive, etc.
 *
 * @warning File or directory that needs to be renamed, must be closed before this function is called.
 * @warning If the absolute path in the function parameters do not match,
 * files or directories that need to be renamed might be moved instead.
 *
 * @pre The logical drive drive must be mounted before this API is called.
 * See @ref file_system_mount for detailed explanation.
 */
fs_status_t file_system_rename(const char * __generic_ptr old_path, const char * __generic_ptr new_path);

/**
 * @brief Make new Directory.
 *
 * @details This function will create a new directory with the name and,
 *          in the location specified by the @c path parameter,
 *          found on the logical drive identified by the drive number specified also in the @c path parameter.
 *
 * @param[in] path A null terminated string, that specifies the absolute path for directory that needs to be created.
 * It should contain the the logical drive identifying drive number and semicolon at the beginning of the string, eg @c "3:/".
 * If it does not, the default logical drive, @c 0:, will be assumed.
 *
 * @retval FSS_OK If the directory was created successfully,
 * @retval FSS_GENERAL_ERROR If the logical drive was not mounted first,
 *         if the path parameters was wrong, etc.
 *
 * @pre The logical drive drive must be mounted before this API is called.
 * See @ref file_system_mount for detailed explanation.
 */
fs_status_t file_system_mkdir(const char * __generic_ptr path);

/*! @} */ // file_system_management_group

/**
 * @defgroup file_group File Access
 * @ingroup file_system_group
 * @brief File Access and Management.
 */

/**
 * @defgroup directory_group Directory Access
 * @ingroup file_system_group
 * @brief Directory Access and Management.
 */

#ifdef __cplusplus
}
#endif

#endif // !_FILE_SYSTEM_H_
