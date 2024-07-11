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
 * @file fatfs.c
 * @brief FatFs File System.
 */

#include "fatfs.h"
#include "ff.h"
#include "fs_common.h"
#include "diskio.h"
#include "string.h"

#define FS_FAT_MAX_PARTITIONS          FF_MULTI_PARTITION ? ((uint8_t)4) : ((uint8_t)1)

#if FF_FS_RPATH > 0
    #define FATFS_CHDIR                fatfs_chdir
#else
   #define FATFS_CHDIR                 0
#endif

#if 1 == FF_USE_MKFS
    #define FATFS_FORMAT                fatfs_format
#else
   #define FATFS_FORMAT                 0
#endif

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

static physical_drive_t * fatfs_physical_drive[FF_VOLUMES] = {(void *)0, (void *)0, (void *)0, (void *)0, (void *)0};

static fs_status_t fatfs_format(fatfs_logical_drive_t * const ptr_this);
static fs_status_t fatfs_mount(fatfs_logical_drive_t * const ptr_this, physical_drive_t * const physical_drive);
static fs_status_t fatfs_unmount(fatfs_logical_drive_t * const ptr_this);
static fs_status_t fatfs_remove(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr path);
static fs_status_t fatfs_rename(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path);
static fs_status_t fatfs_mkdir(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr path);
static fs_status_t fatfs_chdir(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr path);

static fs_status_t fatfs_fopen(fatfs_logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags);
static fs_status_t fatfs_fclose(fatfs_logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fatfs_fread(fatfs_logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read);
static fs_status_t fatfs_fwrite(fatfs_logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write);
static fs_status_t fatfs_fsync(fatfs_logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fatfs_fseek(fatfs_logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, fs_file_rw_pointer_t starting_position);
static uint32_t fatfs_ftell(fatfs_logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fatfs_frewind(fatfs_logical_drive_t * const ptr_this, fs_file_t file);
static uint32_t fatfs_fsize(fatfs_logical_drive_t * const ptr_this, fs_file_t file);
static fs_status_t fatfs_ftruncate(fatfs_logical_drive_t * const ptr_this, fs_file_t file, int length);

static fs_status_t fatfs_dopen(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path);
static fs_status_t fatfs_dclose(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir);
static fs_status_t fatfs_dread(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information);
static fs_status_t fatfs_drewind(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir);

#ifdef __XC8
static logical_drive_vector_table_t fatfs_vtable = {
    (fs_status_t (*)(logical_drive_t * const ptr_this))FATFS_FORMAT,
    (fs_status_t (*)(logical_drive_t * const ptr_this, physical_drive_t * const physical_drive))&fatfs_mount,
    (fs_status_t (*)(logical_drive_t * const ptr_this))fatfs_unmount,
    (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))fatfs_remove,
    (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path))fatfs_rename,
    (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))fatfs_mkdir,
    (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))FATFS_CHDIR,

    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags))fatfs_fopen,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fclose,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read))fatfs_fread,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write))fatfs_fwrite,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fsync,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, fs_file_rw_pointer_t starting_position))fatfs_fseek,
    (uint32_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_ftell,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_frewind,
    (uint32_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fsize,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, int length))fatfs_ftruncate,

    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path))fatfs_dopen,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir))fatfs_dclose,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information))fatfs_dread,
    (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir))fatfs_drewind
};
#endif

fs_status_t fatfs_initialize(fatfs_logical_drive_t * ldrive)
{
    #ifndef __XC8
    static struct logical_drive_vector_table fatfs_vtable = {
        (fs_status_t (*)(logical_drive_t * const ptr_this))FATFS_FORMAT,
        (fs_status_t (*)(logical_drive_t * const ptr_this, physical_drive_t * const physical_drive))&fatfs_mount,
        (fs_status_t (*)(logical_drive_t * const ptr_this))fatfs_unmount,
        (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))fatfs_remove,
        (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path))fatfs_rename,
        (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))fatfs_mkdir,
        (fs_status_t (*)(logical_drive_t * const ptr_this, const char * __generic_ptr path))FATFS_CHDIR,

        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags))fatfs_fopen,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fclose,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read))fatfs_fread,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write))fatfs_fwrite,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fsync,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, fs_file_rw_pointer_t starting_position))fatfs_fseek,
        (uint32_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_ftell,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_frewind,
        (uint32_t (*)(logical_drive_t * const ptr_this, fs_file_t file))fatfs_fsize,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_file_t file, int length))fatfs_ftruncate,

        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path))fatfs_dopen,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir))fatfs_dclose,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information))fatfs_dread,
        (fs_status_t (*)(logical_drive_t * const ptr_this, fs_dir_t dir))fatfs_drewind
    };
    #endif
    fs_status_t fs_res;

    #ifdef FILE_SYSTEM_PIC18_VECTOR_TABLE
    fatfs_vtable.format = FATFS_FORMAT;
    fatfs_vtable.mount = fatfs_mount;
    fatfs_vtable.unmount = fatfs_unmount;
    fatfs_vtable.remove = fatfs_remove;
    fatfs_vtable.rename = fatfs_rename;
    fatfs_vtable.mkdir = fatfs_mkdir;

    fatfs_vtable.f_open = fatfs_fopen;
    fatfs_vtable.f_close = fatfs_fclose;
    fatfs_vtable.f_read = fatfs_fread;
    fatfs_vtable.d_rewind = fatfs_drewind;

    fatfs_vtable.d_open = fatfs_dopen;
    fatfs_vtable.d_close = fatfs_dclose;
    fatfs_vtable.d_read = fatfs_dread;
    fatfs_vtable.f_write = fatfs_fwrite;
    fatfs_vtable.f_sync = fatfs_fsync;
    fatfs_vtable.f_seek = fatfs_fseek;
    fatfs_vtable.f_tell = fatfs_ftell;
    fatfs_vtable.f_rewind = fatfs_frewind;
    fatfs_vtable.f_size = fatfs_fsize;
    fatfs_vtable.f_truncate = fatfs_ftruncate;
    #endif

    fs_res = FILE_SYSTEM_VALIDATE_LOGICAL_DRIVE(ldrive);

    if (FSS_OK == fs_res) {
        // clear fatfs structure
        memset(&ldrive->fatfs, '\0', sizeof(FATFS));
        // set vector table
        ldrive->base.vtptr = &fatfs_vtable;
        file_system_initialize(&ldrive->base);
        // set file system type
        ldrive->base.type = FS_TYPE_FATFS;
    }

    return fs_res;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv           /* Physical drive number to identify the drive */
)
{
    DRESULT res = RES_OK;

    // Check if the physical drive is registered
    if ((physical_drive_t *)0 == fatfs_physical_drive[pdrv]) {
        res = STA_NODISK;
    }

	return res;
}



/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv               /* Physical drive number to identify the drive */
)
{
    DRESULT res;

    // Check if the physical drive is registered
    if ((physical_drive_t *)0 != fatfs_physical_drive[pdrv]) {
        if (0 == physical_drive_init(fatfs_physical_drive[pdrv])) {
            res = RES_OK;
        }
        else {
            res = RES_ERROR;
        }
    }
    else {
        res = RES_NOTRDY;
    }

    return res;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,	    /* Physical drive number to identify the drive */
    BYTE *buff,	    /* Data buffer to store read data */
    LBA_t sector,   /* Start sector in LBA */
    UINT count      /* Number of sectors to read */
)
{
    DRESULT res;
    WORD sector_size = (WORD)fatfs_physical_drive[pdrv]->sector_size;

    // Check if the physical drive is registered
	if ((physical_drive_t *)0 != fatfs_physical_drive[pdrv]) {
        if (0 == physical_drive_read(fatfs_physical_drive[pdrv], buff, sector * sector_size, count * sector_size)) {
            res = RES_OK;
        }
        else {
            res = RES_ERROR;
        }
    }
    else {
        res = RES_NOTRDY;
    }

     return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,                          /* Physical drive number to identify the drive */
    const BYTE * __generic_ptr buff,    /* Data to be written */
    LBA_t sector,                       /* Start sector in LBA */
    UINT count	                        /* Number of sectors to write */
)
{
    DRESULT res;
    WORD sector_size = (WORD)fatfs_physical_drive[pdrv]->sector_size;

    // Check if the physical drive is registered
    if ((physical_drive_t *)0 != fatfs_physical_drive[pdrv]) {
        if (0 == physical_drive_write(fatfs_physical_drive[pdrv], buff, sector * sector_size, count * sector_size)) {
            res = RES_OK;
        }
        else {
            res = RES_ERROR;
        }
    }
    else {
        res = RES_NOTRDY;
    }

    return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,	    /* Physical drive number (0..) */
    BYTE cmd,	    /* Control code */
    void *buff	    /* Buffer to send/receive control data */
)
{
    DRESULT res;

    // Check if the physical drive is registered
    if ((physical_drive_t *)0 != fatfs_physical_drive[pdrv]) {
        switch (cmd) {
            case CTRL_SYNC:
                // Make sure there is no pending write process in the lower layer
                res = RES_OK;
                break;
            case GET_SECTOR_COUNT:
                // Retrieves number of available sectors, the largest allowable LBA + 1, on the drive into the LBA_t variable pointed by buff.
                // This command is used by f_mkfs and f_fdisk function to determine the size of volume/partition to be created.
                *(LBA_t *)buff = (LBA_t)fatfs_physical_drive[pdrv]->sector_count;
                res = RES_OK;
                break;
            case GET_SECTOR_SIZE:
                // Retrieves sector size, minimum data unit for generic read/write, into the WORD variable pointed by buff.
                // Valid sector sizes are 512, 1024, 2048 and 4096.
                // This command is required only if FF_MAX_SS > FF_MIN_SS.
                // When FF_MAX_SS == FF_MIN_SS, this command will never be used and the disk_read and disk_write functions must work in FF_MAX_SS bytes/sector.
                *(WORD *)buff = (WORD)fatfs_physical_drive[pdrv]->sector_size;
                res = RES_OK;
                break;
            case GET_BLOCK_SIZE:
                // Retrieves erase block size in unit of sector of the flash memory media into the DWORD variable pointed by buff.
                // The allowable value is 1 to 32768 in power of 2. Return 1 if it is unknown or in non flash memory media.
                // This command is used by f_mkfs function with block size not specified and it attempts to align the data area on the suggested block boundary.
                // Note that FatFs does not have FTL (flash translation layer), so that either disk I/O layer or storage device must have an FTL in it.
                *(DWORD *)buff = (DWORD)fatfs_physical_drive[pdrv]->erase_block_size;
                res = RES_OK;
                break;
            case CTRL_TRIM:
                // Informs the disk I/O layer or the storage device that the data on the block of sectors is no longer needed and it can be erased.
                // The sector block is specified in an LBA_t array {<Start LBA>, <End LBA>} pointed by buff.
                // This is an identical command to Trim of ATA device.
                // Nothing to do for this command if this function is not supported or not a flash memory device.
                // FatFs does not check the result code and the file function is not affected even if the sector block was not erased well.
                // This command is called on remove a cluster chain and in the f_mkfs function.
                // It is required when FF_USE_TRIM == 1.
                res = RES_ERROR;  // TODO This is only placeholder. Yet to be implemented.
                break;
            default:
                res= RES_ERROR;
                break;
        }
    }
    else {
        res = RES_NOTRDY;
    }

	return res;
}

#ifdef __XC8
static BYTE work[FF_MAX_SS]; // Variable must be global because it might be greater then memory bank size.
#endif
static fs_status_t fatfs_format(fatfs_logical_drive_t * const ptr_this)
{
    FRESULT res;
    fs_status_t fs_res = FSS_OK;
    FATFS * fat_fs = (FATFS *)&ptr_this->fatfs;
    physical_drive_t * physical_drive = fatfs_physical_drive[fat_fs->pdrv];
    #ifndef __XC8
    BYTE work[FF_MAX_SS];
    #endif
    TCHAR path[5] = "0:";  // TODO DSPIC workaround
    fs_res = FILE_SYSTEM_VALIDATE_PHYSICAL_DRIVE(physical_drive);

    if (FSS_OK == fs_res) {
        path[0] = '0' + ptr_this->base.volume_id;
        res = f_mkfs(path, 0, work, sizeof(work));
    }

    if (FR_OK != res)
    {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_mount(fatfs_logical_drive_t * const ptr_this, physical_drive_t * const physical_drive)
{
    FATFS * fatfs = (FATFS *)&ptr_this->fatfs;
    TCHAR path[] = "0:";
    BYTE delayed_mount = 0;
    fs_status_t fs_res = FSS_OK;

    // If more volumes can be added to the physical drive
    if (FS_FAT_MAX_PARTITIONS > physical_drive->volumes) {
        path[0] = '0' + ptr_this->base.volume_id;
        // f_mount must be delayed because at this point physical drive is unknown, and will only be determined during f_mount call
        f_mount(fatfs, path, delayed_mount);

        // link the physical drive with the logical drive
        if (0 == fatfs_physical_drive[fatfs->pdrv]) {
            // register the physical drive
            fatfs_physical_drive[fatfs->pdrv] = physical_drive;
        }
        else if (fatfs_physical_drive[fatfs->pdrv] != physical_drive) {
            // error: another physical drive is already registered
            // illegal state: logical drive slot was free for mounting but corresponding physical drive is not
            // TODO remap fatfs errors
            fs_res = FSS_GENERAL_ERROR;
        }

        // register volume to the physical drive
        ++physical_drive->volumes;
    }
    else if (FS_FAT_MAX_PARTITIONS == physical_drive->volumes) {
        // error: cannot add more partitions to the physical drive
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }
    else {
        // if (FS_FAT_MAX_PARTITIONS < physical_drive->volumes)
        // error: number of partitions on this physical drive is above maximum allowed
        // illegal state: number of registered partitions on this drive is above the maximum allowed
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_unmount(fatfs_logical_drive_t * const ptr_this)
{
    FATFS * fat_fs = (FATFS *)&ptr_this->fatfs;
    physical_drive_t * physical_drive = fatfs_physical_drive[fat_fs->pdrv];
    BYTE vol_id = (BYTE)ptr_this->base.volume_id;
    TCHAR path[] = "0:";
    fs_status_t fs_res;

    fs_res = FILE_SYSTEM_VALIDATE_PHYSICAL_DRIVE(physical_drive);
    if (FSS_OK == fs_res) {
        // check for file system irregularities
        if ((0 != physical_drive->volumes) &&
            (FS_FAT_MAX_PARTITIONS <= physical_drive->volumes))
        {
            path[0] = '0' + vol_id;
            f_unmount(path);

            // unregister file system volume from the physical drive
            if (0 == --physical_drive->volumes) {
                // deinit physical drive if no files system volumes are mounted on it
                physical_drive->type = PD_TYPE_UNINITIALIZED;
                // unregister physical drive if no files system volumes are mounted on it
                fatfs_physical_drive[fat_fs->pdrv] = (physical_drive_t *)0;
            }
        }
        else {
            // error: illegal number of partitions detected on this physical drive
            // illegal state: APIs should not allow number of volumes to be out of bounds
            // TODO remap fatfs errors
            fs_res = FSS_GENERAL_ERROR;
        }
    }

    return fs_res;
}

static fs_status_t fatfs_remove(fatfs_logical_drive_t * const ptr_this, const char* path)
{
    FRESULT res;
    fs_status_t fs_res = FSS_OK;

    // WARNING path object must not be opened.
    res = f_unlink(path);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_rename(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr old_path, const char * __generic_ptr new_path)
{
    FRESULT res;
    fs_status_t fs_res = FSS_OK;

    // WARNING f_rename function will move files if absolute addresses do not match.
    // WARNING old_path object must not be opened.
    res = f_rename(old_path, new_path);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_mkdir(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr path)
{
    FRESULT res;
    fs_status_t fs_res = FSS_OK;

    res = f_mkdir(path);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

#if (FATFS_CHDIR != 0)
static fs_status_t fatfs_chdir(fatfs_logical_drive_t * const ptr_this, const char * __generic_ptr path)
{
    FRESULT res;
    fs_status_t fs_res = FSS_OK;

    // WARNING this function is not enabled in ffconf.h
    res = f_chdir(path);

    if (FR_OK !=res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }
    return fs_res;
}
#endif

static fs_status_t fatfs_fopen(fatfs_logical_drive_t * const ptr_this, fs_file_t file, const char * __generic_ptr path, int flags)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    BYTE mode = (BYTE)flags;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_open(ptr_fatfs_file, path, mode);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_fclose(fatfs_logical_drive_t * const ptr_this, fs_file_t file)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_close(ptr_fatfs_file);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_fread(fatfs_logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_read)
{
    FIL * ptr_fatfs_file = (FIL*)file;
    UINT bytes_read = 0;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    if (0 != ptr_this) {
        // prevents compiler to optimize ptr_this variable
        // this is specific to MikroC for ARM compiler
        // TODO
        NOP();
    }

    res = f_read(ptr_fatfs_file, buffer, bytes_to_read, &bytes_read);

    // check if bytes of data were read
    if (FR_OK == res) {
        if (bytes_read != bytes_to_read) {
            // Not enough bytes were read, because end of the file was reached
            fs_res = FSS_END_OF_FILE;
        }
    }
    else {
        // TODO remap fatfs errors
        fs_res =  FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_fwrite(fatfs_logical_drive_t * const ptr_this, fs_file_t file, void * buffer, uint32_t bytes_to_write)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    UINT bytes_written = 0;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    if (0 != ptr_this) {
        // prevents compiler to optimize ptr_this variable
        // this is specific to MikroC for ARM compiler
        // TODO
        NOP();
    }

    res = f_write(ptr_fatfs_file, buffer, bytes_to_write, &bytes_written);

    // check if all data bytes were written
    if (FR_OK == res) {
        if (bytes_written != bytes_to_write) {
            // Not all bytes of data could be written, because the drive memory is full
            fs_res = FSS_DRIVE_FULL;
        }
    }
    else {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_fsync(fatfs_logical_drive_t * const ptr_this, fs_file_t file)
{
    FIL* ptr_fatfs_file = (FIL*)file;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_sync(ptr_fatfs_file);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_fseek(fatfs_logical_drive_t * const ptr_this, fs_file_t file, int32_t offset, fs_file_rw_pointer_t starting_position)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    FSIZE_t current_offset = 0;
    fs_status_t fs_res = FSS_OK;
    FSIZE_t absolute_offset;
    FRESULT res;

    if (0 != ptr_this) {
        // prevents compiler to optimize ptr_this variable
        // this is specific to MikroC for ARM compiler
        // TODO
        NOP();
    }

    // recalculate the offset, so that starting position is taken into account
    switch (starting_position) {
        case SEEK_CURRENT:
            // current cursor value is added to offset
            offset += f_tell(ptr_fatfs_file);
            break;
        case SEEK_END:
            // file size is added to offset
            offset += f_size(ptr_fatfs_file);
            break;
        default:
            // offset is not modified
            break;
    }
    // file cursor cannot be negative
    absolute_offset = offset >= 0 ? offset : 0;

    // move the file cursor by the recalculated offset, from the beginning of the file
    res = f_lseek(ptr_fatfs_file, absolute_offset);
    current_offset = ptr_fatfs_file->fptr;

    // check if cursor was moved to the desired position
    if (FR_OK == res) {
        if (current_offset != absolute_offset) {
            // file could not be expanded because the drive is full
            fs_res = FSS_DRIVE_FULL; // TODO proper error map needs to be made
        }
    }
    else {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static uint32_t fatfs_ftell(fatfs_logical_drive_t * const ptr_this, fs_file_t file)
{
    FIL * ptr_fatfs_file = (FIL *)file;

    return (uint32_t)f_tell(ptr_fatfs_file);
}

static fs_status_t fatfs_frewind(fatfs_logical_drive_t * const ptr_this, fs_file_t file)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_rewind(ptr_fatfs_file);

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static uint32_t fatfs_fsize(fatfs_logical_drive_t * const ptr_this, fs_file_t file)
{
    FIL * ptr_fatfs_file = (FIL *)file;

    return (uint32_t)f_size(ptr_fatfs_file);
}

static fs_status_t fatfs_ftruncate(fatfs_logical_drive_t * const ptr_this, fs_file_t file, int truncated_size)
{
    FIL * ptr_fatfs_file = (FIL *)file;
    FSIZE_t old_cursor_position = f_tell(ptr_fatfs_file);
    FSIZE_t new_cursor_position = (FSIZE_t)truncated_size > old_cursor_position ? old_cursor_position : (FSIZE_t)truncated_size;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    // move cursor to the position indicated by the parameter truncated_size
    res = f_lseek(ptr_fatfs_file, truncated_size);
    if (FR_OK == res) {
        // truncate the file to position of cursor
        res = f_truncate(ptr_fatfs_file);
    }

    if (FR_OK == res) {
        // return cursor into the original position if possible, otherwise move it to the end of the truncated file
        res = f_lseek(ptr_fatfs_file, new_cursor_position);
    }

    if (FR_OK != res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_dopen(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir, const char * __generic_ptr path)
{
    DIR * ptr_fatfs_dir = (DIR *)dir;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_opendir(ptr_fatfs_dir, path);

    if (FR_OK !=res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_dclose(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir)
{
    DIR * ptr_fstfs_dir = (DIR*)dir;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_closedir(ptr_fstfs_dir);

    if (FR_OK !=res) {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_dread(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir, void * file_information)
{
    DIR * ptr_fstfs_dir = (DIR *)dir;
    FILINFO * ptr_finfo = (FILINFO *)file_information;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    // read the directory entry
    res = f_readdir(ptr_fstfs_dir, ptr_finfo);

    if (FR_OK == res) {
        if (0 == ptr_finfo->fname[0]) {
            // end of directory is reached
            fs_res = FSS_END_OF_DIRECTORY;
        }
    }
    else {
        // TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}

static fs_status_t fatfs_drewind(fatfs_logical_drive_t * const ptr_this, fs_dir_t dir)
{
    DIR * ptr_fatfs_dir = (DIR *)dir;
    fs_status_t fs_res = FSS_OK;
    FRESULT res;

    res = f_rewinddir(ptr_fatfs_dir);

    if (FR_OK !=res) {
        /// TODO remap fatfs errors
        fs_res = FSS_GENERAL_ERROR;
    }

    return fs_res;
}
