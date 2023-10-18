/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem module  R0.15                               /
/-----------------------------------------------------------------------------/
/
/ Copyright (C) 2022, ChaN, all right reserved.
/
/ FatFs module is an open source software. Redistribution and use of FatFs in
/ source and binary forms, with or without modification, are permitted provided
/ that the following condition is met:

/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/
/----------------------------------------------------------------------------*/


#ifndef FF_DEFINED
#define FF_DEFINED	80286	/* Revision ID */

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ff_types.h"   /* Declarations of FatFs custom types */
#include "ffconf.h"		/* FatFs configuration options */
#include "generic_pointer.h"

#if FF_DEFINED != FFCONF_DEF
#error Wrong configuration file (ffconf.h).
#endif


/*--------------------------------------------------------------*/
/* FatFs Module Application Interface                           */
/*--------------------------------------------------------------*/

FRESULT f_open (FIL* fp, const TCHAR* __generic_ptr path, BYTE mode);				/* Open or create a file */
FRESULT f_close (FIL* fp);											/* Close an open file object */
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* Read data from the file */
FRESULT f_write (FIL* fp, const void* __generic_ptr buff, UINT btw, UINT* bw);	/* Write data to the file */
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								/* Move file pointer of the file object */
FRESULT f_truncate (FIL* fp);										/* Truncate the file */
FRESULT f_sync (FIL* fp);											/* Flush cached data of the writing file */
FRESULT f_opendir (DIR* dp, const TCHAR* __generic_ptr path);						/* Open a directory */
FRESULT f_closedir (DIR* dp);										/* Close an open directory */
FRESULT f_readdir (DIR* dp, FILINFO* fno);							/* Read a directory item */
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* __generic_ptr path, const TCHAR* __generic_ptr pattern);	/* Find first file */
FRESULT f_findnext (DIR* dp, FILINFO* fno);							/* Find next file */
FRESULT f_mkdir (const TCHAR* __generic_ptr path);								/* Create a sub directory */
FRESULT f_unlink (const TCHAR* __generic_ptr path);								/* Delete an existing file or directory */
FRESULT f_rename (const TCHAR* __generic_ptr path_old, const TCHAR* __generic_ptr path_new);	/* Rename/Move a file or directory */
FRESULT f_stat (const TCHAR* __generic_ptr path, FILINFO* fno);					/* Get file status */
FRESULT f_chmod (const TCHAR* __generic_ptr path, BYTE attr, BYTE mask);			/* Change attribute of a file/dir */
FRESULT f_utime (const TCHAR* __generic_ptr path, const FILINFO* fno);			/* Change timestamp of a file/dir */
FRESULT f_chdir (const TCHAR* __generic_ptr path);								/* Change current directory */
FRESULT f_chdrive (const TCHAR* __generic_ptr path);								/* Change current drive */
FRESULT f_getcwd (TCHAR* buff, UINT len);							/* Get current directory */
FRESULT f_getfree (const TCHAR* __generic_ptr path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */
FRESULT f_getlabel (const TCHAR* __generic_ptr path, TCHAR* label, DWORD* vsn);	/* Get volume label */
FRESULT f_setlabel (const TCHAR* __generic_ptr label);							/* Set volume label */
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE* __generic_ptr,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */
FRESULT f_expand (FIL* fp, FSIZE_t fsz, BYTE opt);					/* Allocate a contiguous block to the file */
FRESULT f_mount (FATFS* fs, const TCHAR* __generic_ptr path, BYTE opt);			/* Mount/Unmount a logical drive */
FRESULT f_mkfs (const TCHAR* __generic_ptr path, const MKFS_PARM* __generic_ptr opt, void* work, UINT len);	/* Create a FAT volume */
FRESULT f_fdisk (BYTE pdrv, const LBA_t ptbl[], void* work);		/* Divide a physical drive into some partitions */
FRESULT f_setcp (WORD cp);											/* Set current code page */
int f_putc (TCHAR c, FIL* fp);										/* Put a character to the file */
int f_puts (const TCHAR* __generic_ptr str, FIL* cp);								/* Put a string to the file */
int f_printf (FIL* fp, const TCHAR* __generic_ptr str, ...);						/* Put a formatted string to the file */
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* Get a string from the file */

/* Some API fucntions are implemented as macro */

#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
#define f_error(fp) ((fp)->err)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->obj.objsize)
#define f_rewind(fp) f_lseek((fp), 0)
#define f_rewinddir(dp) f_readdir((dp), 0)
#define f_rmdir(path) f_unlink(path)
#define f_unmount(path) f_mount(0, path, 0)




/*--------------------------------------------------------------*/
/* Additional Functions                                         */
/*--------------------------------------------------------------*/

/* RTC function (provided by user) */
#if !FF_FS_READONLY && !FF_FS_NORTC
DWORD get_fattime (void);	/* Get current time */
#endif


/* LFN support functions (defined in ffunicode.c) */

#if FF_USE_LFN >= 1
WCHAR ff_oem2uni (WCHAR oem, WORD cp);	/* OEM code to Unicode conversion */
WCHAR ff_uni2oem (DWORD uni, WORD cp);	/* Unicode to OEM code conversion */
DWORD ff_wtoupper (DWORD uni);			/* Unicode upper-case conversion */
#endif


/* O/S dependent functions (samples available in ffsystem.c) */

#if FF_USE_LFN == 3		/* Dynamic memory allocation */
void* ff_memalloc (UINT msize);		/* Allocate memory block */
void ff_memfree (void* mblock);		/* Free memory block */
#endif
#if FF_FS_REENTRANT	/* Sync functions */
int ff_mutex_create (int vol);		/* Create a sync object */
void ff_mutex_delete (int vol);		/* Delete a sync object */
int ff_mutex_take (int vol);		/* Lock sync object */
void ff_mutex_give (int vol);		/* Unlock sync object */
#endif




/*--------------------------------------------------------------*/
/* Flags and Offset Address                                     */
/*--------------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif /* FF_DEFINED */
