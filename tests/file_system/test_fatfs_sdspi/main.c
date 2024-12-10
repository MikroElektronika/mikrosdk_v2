// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "fatfs.h"
#include "file.h"
#include "dir.h"
#include "board.h"
#include "sdspi_physical_drive.h"
#include "ff_types.h"
#include "log.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

#define SEEK_TEST_LENGTH       (5)
#define BUFFER_SIZE            (512)

#define FSEEK_END_TEST 1
#define FSEEK_START_TEST 1
#define FSEEK_MIDDLE_TEST 1
#define FSYNC_TEST 1
#define FTELL_TEST 1
#define FREWIND_TEST 1
#define FSIZE_TEST 1

#define DOPEN_TEST 1
#define REMOVE_TEST 1
#define RENAME_TEST 1
#define DCLOSE_TEST 1

#define BANDWIDTH_TEST 1
#define MULTI_READ_TEST 0 // WARNING This test requires large buffer, so it should be disabled in cases where RAM is limited, 7kB is needed at least.

#define TEST_SUCCESS_PIN HAL_PIN_NC
#define TEST_FAILED_PIN HAL_PIN_NC

#ifdef __MIKROC_AI_FOR_AVR__
    #define __TEST_STATUS_PIN__ GPIO_PA0
    #define printf_me //printf_me
#endif

digital_out_t status;

// ----------------------------------------------------------------- VARIABLES

typedef enum {
    TEST_FS_NO_ERROR = 0,

    TEST_FS_ERROR_MKDIR,
    TEST_FS_ERROR_REMOVE,
    TEST_FS_ERROR_RENAME,

    TEST_FS_ERROR_FORMAT,
    TEST_FS_ERROR_MOUNT,
    TEST_FS_ERROR_FOPEN,
    TEST_FS_ERROR_FCLOSE,
    TEST_FS_ERROR_FREED,
    TEST_FS_ERROR_FWRITE,
    TEST_FS_ERROR_FSYNC,
    TEST_FS_ERROR_FSEEK,
    TEST_FS_ERROR_FTELL,
    TEST_FS_ERROR_FREWIND,
    TEST_FS_ERROR_FSIZE,
    TEST_FS_ERROR_FTRUNCATE,

    TEST_FS_ERROR_DOPEN,
    TEST_FS_ERROR_DCLOSE,
    TEST_FS_ERROR_DREAD,
    TEST_FS_ERROR_DREWIND,
    TEST_FS_ERROR_DSIZE
} test_fs_error_t;

uint8_t f_buffer[BUFFER_SIZE];
uint8_t test_wr_buffer[SEEK_TEST_LENGTH] = {'_', '_', '_', '_', '\0'};
uint8_t test_rd_buffer[SEEK_TEST_LENGTH] = {'\0', '\0','\0' ,'\0','\0'};

sdspi_config_t sd_conf;
sdspi_physical_drive_t sdc;

fatfs_logical_drive_t fatfs_drive;
FIL fatfs_file;
DIR fatfs_dir;
FILINFO fatfs_info;

file_t fajl1;
dir_t dir1;

test_fs_error_t error = TEST_FS_NO_ERROR;
uint8_t fs_error;

log_t logger;
log_cfg_t config;

#if MULTI_READ_TEST == 1
    #define BUFFER_SIZE_MR         (8 * BUFFER_SIZE)
    uint8_t stm32_buffer[BUFFER_SIZE_MR];
#endif

#ifdef __MIKROC_AI_FOR_AVR__
digital_out_t test_status_led;
volatile uint8_t test_counter = 0;
#endif

void test_fail() {
    digital_out_init(&status, TEST_FAILED_PIN);
    while(1) {
        digital_out_toggle(&status);
        Delay_ms(1000);
    }
}

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    uint32_t i;
    uint8_t dir_end = 0;

    LOG_MAP_USB_UART( config );
    log_init(&logger, &config);

    #ifdef __MIKROC_AI_FOR_AVR__
    digital_out_init(&test_status_led, __TEST_STATUS_PIN__);
    digital_out_low(&test_status_led);
    #endif

    log_printf( &logger, "TEST STARTED\n");

    for (i = 0; i < BUFFER_SIZE; i++) {
        f_buffer[i] = i & 0xFF;
    }

    sd_conf.spi_sck = MIKROBUS_1_SCK;
    sd_conf.spi_miso = MIKROBUS_1_MISO;
    sd_conf.spi_mosi = MIKROBUS_1_MOSI;
    sd_conf.spi_cs = MIKROBUS_1_CS;

    // initialize sdc phyiscal drive structure
    fs_error = sdspi_physical_drive_init(&sdc, &sd_conf);
    if (0 != fs_error) {
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }

    // initialize fatfs_drive logical drive structure
    fs_error = fatfs_initialize(&fatfs_drive);
    if (0 != fs_error) {
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // mount the drive fatfs_drive to the file system drive number 3 and initialize SD card where fatfs_drive will be located
    fs_error = file_system_mount(&fatfs_drive.base, "3:", &sdc.base);
    if (0 != fs_error) {
        error = TEST_FS_ERROR_MOUNT;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }

    log_printf( &logger, "FORMATTING STARTED\n");
    // format the drive 3, or format the logical drive fatfs_drive on SD card sdc
    fs_error = file_system_format("3:");
    if (0 != fs_error) {
        error = TEST_FS_ERROR_FORMAT;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "FORMATTING COMPLETED\n");

    // create __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (0 != fs_error) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // write 512 bytes of data to the file 3:/__DATA.TXT from f_buffer
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // append 512 bytes of data to the file 3:/__DATA.TXT from f_buffer
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    log_printf( &logger, "FILE __DATA.TXT CREATED\n");

    // test file_seek from end
    #if FSEEK_END_TEST == 1
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 16th character before the end of the file __DATA.TXT
    fs_error = file_seek(&fajl1, -16, SEEK_END);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // write "____" at the location of the cursor inside the file __DATA.TXT
    fs_error = file_write(&fajl1, test_wr_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 16th character before the end of the file __DATA.TXT
    fs_error = file_seek(&fajl1, -16, SEEK_END);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // read 4 character from the cursor position in the file __DATA.TXT
    fs_error = file_read(&fajl1, test_rd_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FREED;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // check if read data is the same as data that was previously written at the given cursor location in the file __DATA.TXT
    // if they are the same file_seek API work as intended from the end of the file
    if (memcmp(test_wr_buffer, test_rd_buffer, SEEK_TEST_LENGTH - 1) != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FSEEK END COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // test file_seek from start
    #if FSEEK_START_TEST == 1
    // clear the read buffer
    test_rd_buffer[0] = 0;
    test_rd_buffer[1] = 0;
    test_rd_buffer[2] = 0;
    test_rd_buffer[3] = 0;
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 16th character in the file __DATA.TXT
    fs_error = file_seek(&fajl1, 16, SEEK_START);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // write "____" at the location of the cursor inside the file __DATA.TXT
    fs_error = file_write(&fajl1, test_wr_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 16th character in the file __DATA.TXT
    fs_error = file_seek(&fajl1, 16, SEEK_START);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // read 4 character from the cursor position in the file __DATA.TXT
    fs_error = file_read(&fajl1, test_rd_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FREED;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // check if read data is the same as data that was previously written at the given cursor location in the file __DATA.TXT
    // if they are the same file_seek API work as intended from the beginning of the file
    if (memcmp(test_wr_buffer, test_rd_buffer, SEEK_TEST_LENGTH - 1) != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FSEEK START COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // test file_seek on sector division location
    #if FSEEK_MIDDLE_TEST == 1
    // clear the read buffer
    test_rd_buffer[0] = 0;
    test_rd_buffer[1] = 0;
    test_rd_buffer[2] = 0;
    test_rd_buffer[3] = 0;
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 510th character in the file __DATA.TXT
    // this location is in the middle of the file __DATA.TXT, where its data continues into different sector
    fs_error = file_seek(&fajl1, 510, SEEK_START);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    } // sector end and switch
    // write "____" at the location of the cursor inside the file __DATA.TXT
    // this will write into the first sector of the file and the beginning of the next sector of the file
    fs_error = file_write(&fajl1, test_wr_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the 510th character in the file __DATA.TXT
    fs_error = file_seek(&fajl1, 5, SEEK_CURRENT);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // read 4 character from the cursor position in the file __DATA.TXT
    // this will read from the first sector of the file and from the beginning of the next sector of the file
    fs_error = file_read(&fajl1, test_rd_buffer, SEEK_TEST_LENGTH - 1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FREED;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // check if read data is the same as data that was previously written at the given cursor location in the file __DATA.TXT
    // if they are the same file_seek API work as intended in the location of the file where 2 of its sectors meet
    if (memcmp(f_buffer + 7, test_rd_buffer, SEEK_TEST_LENGTH - 1) != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FSEEK SECTOR BREAK COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // file_sync test requires simulating loss of power by getting the SD card out before second buffer is written and file close is called
    #if FSYNC_TEST == 1
    // change first 128 characters of f_buffer to "---127---|"
    for (i = 0; i < (BUFFER_SIZE / 4); i++) {
        f_buffer[i] = '-';
    }
    f_buffer[(BUFFER_SIZE / 4) - 1] = '|';
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the beginning of the second sector of the file
    fs_error = file_seek(&fajl1, 512, SEEK_START);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // rewrite second part of the file connected to it second sector with modified f_buffer
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE / 4);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save changes to the file without closing it
    fs_error = file_sync(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSYNC;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // power loss should happen here, in order to simulate it, pull the card out in debug mode at this step
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE / 4);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // SD card needs to be pulled out at this moment and it contents needs to be checked in card reader,
    // if file_sync was successful, everything before last file write will be saved and last write will not be.
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FSYNC COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // file_tell test
    #if FTELL_TEST == 1
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // move cursor to the position 3/4 of the file (768)
    fs_error = file_seek(&fajl1, 768, SEEK_START);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FSEEK;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // position inside file is set to 768, so file_tell should return this value
    if (768 != file_tell(&fajl1)) {
        error = TEST_FS_ERROR_FTELL;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FTELL COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // rewind test
    #if FREWIND_TEST == 1
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // rewind the file 3:/__DATA.TXT
    file_rewind(&fajl1);
    // after rewind position should be 0
    if (0 != file_tell(&fajl1)) {
        error = TEST_FS_ERROR_FTELL;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FREWIND COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // size test
    #if FSIZE_TEST == 1
    // open __DATA.TXT on drive 3
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // size should be 1024
    if ((BUFFER_SIZE * 2) != file_size(&fajl1))  {
        error = TEST_FS_ERROR_FSIZE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST FSIZE COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // make new directory, then make new file in it, and copy the content from old file into the new file
    #if DOPEN_TEST == 1
    // make the new directory __DIR
    log_printf( &logger, "TEST MAKE DIRECTORY and FILE COPY STARTED\n");
    fs_error = file_system_mkdir("3:/__DIR");
    if (0 != fs_error) {
        error = TEST_FS_ERROR_MKDIR;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // open the file 3:/__DATA.TXT
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // rewind the file 3:/__DATA.TXT
    file_rewind(&fajl1);
    // read 512 bytes from the file 3:/__DATA.TXT and store it into the f_buffer
    fs_error = file_read(&fajl1, f_buffer, BUFFER_SIZE);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FREED;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }

    memset(&fatfs_file, '\0', sizeof(FIL));
    fajl1.logical_drive = 0;
    fajl1.fs_file = 0;
    // create the file 3:/__DIR/__COPY.TXT
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DIR/__COPY.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // copy/write contents read from the file into the file 3:/__DIR/__COPY.TXT
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save the changes to the file 3:/__DIR/__COPY.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }

    // make the new directory 3:/__DIR/__SUBDIR
    fs_error = file_system_mkdir("3:/__DIR/__SUBDIR");
    if (fs_error != 0) {
        error = TEST_FS_ERROR_MKDIR;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // open the directory 3:/__DIR for reading
    fs_error = dir_open(&dir1, &fatfs_dir, "3:/__DIR");
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // display the directory 3:/__DIR contents
    // file __COPY.TXT is expected
    // directory __SUBDIR is expected
    while (!dir_end) {
        fs_error = dir_read(&dir1, &fatfs_info);
        switch (fs_error) {
            case FSS_END_OF_DIRECTORY:
                dir_end = 1;
                break;
            case FSS_OK:
                if (fatfs_info.fattrib & AM_DIR) {
                    log_printf( &logger, "DIRECTORY: %s\n", fatfs_info.fname);
                }
                else {
                    log_printf( &logger, "FILE: %s\n", fatfs_info.fname);
                }
                continue;
            default:
                error = TEST_FS_ERROR_DREAD;
                log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
                test_fail();
        }
    }
    dir_end = 0;
    // close the directory 3:/__DIR
    fs_error = dir_close(&dir1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST MAKE DIRECTORY and FILE COPY COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // rename the directory __SUBDIR inside 3:/__DIR directory /to ___SUB adn display 3:/__DIR contents
    #if RENAME_TEST == 1
    // rename the directory 3:/__DIR/__SUBDIR to the 3:/__DIR/___SUB
    fs_error = file_system_rename("3:/__DIR/__SUBDIR", "3:/__DIR/___SUB");
     if (fs_error != 0) {
        error = TEST_FS_ERROR_RENAME;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // open the directory 3:/__DIR for reading
    fs_error = dir_open(&dir1, &fatfs_dir, "3:/__DIR");
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // display the directory 3:/__DIR contents
    // file __COPY.TXT is expected
    // directory __SUB is expected
    while (!dir_end) {
        fs_error = dir_read(&dir1, &fatfs_info);
        switch (fs_error) {
            case FSS_END_OF_DIRECTORY:
                dir_end = 1;
                break;
            case FSS_OK:
                if (fatfs_info.fattrib & AM_DIR) {
                    log_printf( &logger, "DIRECTORY: %s\n", fatfs_info.fname);
                }
                else {
                    log_printf( &logger, "FILE: %s\n", fatfs_info.fname);
                }
                continue;
            default:
                error = TEST_FS_ERROR_DREAD;
                log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
                test_fail();
        }
    }
    dir_end = 0;
    // close the directory 3:/__DIR
    fs_error = dir_close(&dir1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST RENAME COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // remove __SUB directory from 3:/__DIR and display contents of the 3:/__DIR directory
    #if REMOVE_TEST == 1
    // remove the directory 3:/__DIR/___SUB
    fs_error = file_system_remove("3:/__DIR/___SUB");
    if (fs_error != 0) {
        error = TEST_FS_ERROR_REMOVE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // open the directory 3:/__DIR for reading
    fs_error = dir_open(&dir1, &fatfs_dir, "3:/__DIR");
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // display the directory 3:/__DIR contents
    // file __COPY.TXT is expected
    while (!dir_end) {
        fs_error = dir_read(&dir1, &fatfs_info);
        switch (fs_error) {
            case FSS_END_OF_DIRECTORY:
                dir_end = 1;
                break;
            case FSS_OK:
                if (fatfs_info.fattrib & AM_DIR) {
                    log_printf( &logger, "DIRECTORY: %s\n", fatfs_info.fname);
                }
                else {
                    log_printf( &logger, "FILE: %s\n", fatfs_info.fname);
                }
                continue;
            default:
                error = TEST_FS_ERROR_DREAD;
                log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
                test_fail();
        }
    }
    dir_end = 0;
    // close the directory 3:/_X__COPY.TXT
    fs_error = dir_close(&dir1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_DCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST REMOVE COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // test bandwidth by writing 1MB of data into the file 3:/__DATA.TXT
    #if BANDWIDTH_TEST == 1
    log_printf( &logger, "TEST BANDWIDTH STARTED \n");
    // create the file 3:/__DATA.TXT
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST BANDWIDTH WRITE START\n");
    i = 1024 * (1024 / BUFFER_SIZE);
    // write 1MB into the file 3:/__DATA.TXT
    while (i--) {
        fs_error = file_write(&fajl1, f_buffer, BUFFER_SIZE);
        if (fs_error != 0) {
            error = TEST_FS_ERROR_FWRITE;
            log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
            test_fail();
        }
    }
    log_printf( &logger, "TEST BANDWIDTH WRITE STOP\n");
    // save changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    log_printf( &logger, "TEST BANDWIDTH COMPLETED\n");
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    #endif

    // test SD card multiple block read and write command by using large read buffers
    #if MULTI_READ_TEST == 1
    log_printf( &logger, "TEST MULTI-READ STARTED \n");
    // open the file 3:/__DATA.TXT
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DATA.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // rewind the file 3:/__DATA.TXT
    file_rewind(&fajl1);
    // read 4kB of data from the card into 4kB buffer
    // this will force file system and SD card driver to use multi block read command to read 8 blocks at once
    fs_error = file_read(&fajl1, stm32_buffer, BUFFER_SIZE_MR);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save changes to the file 3:/__DATA.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // create the file 3:/__DAT_MR.TXT and open it
    fs_error = file_open(&fajl1, &fatfs_file, "3:/__DAT_MR.TXT", FS_FILE_OPEN_APPEND | FS_FILE_WRITE | FS_FILE_READ);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FOPEN;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // copy/write data read from the file 3:/__DATA.TXT into the file 3:/__DAT_MR.TXT using the large buffer
    // this will force file system and SD card driver to use multi write command to write 8 blocks at once
    fs_error = file_write(&fajl1, stm32_buffer, BUFFER_SIZE_MR);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FWRITE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    // save changes to the file 3:/__DAT_MR.TXT and close it
    fs_error = file_close(&fajl1);
    if (fs_error != 0) {
        error = TEST_FS_ERROR_FCLOSE;
        log_printf( &logger, "FAIL LINE: %d\n", (uint16_t)__LINE__);
        test_fail();
    }
    #ifdef __MIKROC_AI_FOR_AVR__
    ++test_counter;
    #endif
    log_printf( &logger, "TEST MULTI-READ COMPLETED\n");
    #endif


    #ifdef __MIKROC_AI_FOR_AVR__
    if (12 == test_counter) {
        digital_out_high(&test_status_led);
    }
    #endif
    log_printf( &logger, "TEST COMPLETED\n");

    while (1) {
        digital_out_init(&status, TEST_SUCCESS_PIN);
        while (1) {
            digital_out_toggle(&status);
            Delay_ms(1000);
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
