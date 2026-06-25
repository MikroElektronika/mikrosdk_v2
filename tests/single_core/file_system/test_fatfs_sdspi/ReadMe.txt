This example is meant for basic testing FatFs file system and SDSPI physical drive libraries using mikroSDK 2.0
It is not meant to cover every single functionality, and it is not meant to automatically detect failures.
The results of the test should be validated by the user by inspecting the result in the application output, or reading the SD card in the card reader on PC.

To use this test microSD click and SD card is needed, which should be put into mikroBUS slot 1.

1. Setting up the file system test
  + All structures needed for the file system to work are initialized.
    + **sdc** structure representing the SD card physical drive communicating over SPI.
    + **fatfs_drive** structure representing FatFs logical drive.
  + 512-byte buffer **f_buffer** used for reading and writing on the SD card, will be initialized using a pattern where,
    data in the Xth position is equal to number X, and if X is greater the 256 then X % 256.
  + **fatfs_drive** and **sdc** are linked and mounted to file system drive number 3.
  + File system drive 3, the previously mounted drive, will be formatted.
  + The file **__DATA.TXT** will be created and will be filled with 1024 bytes of data 2 consecutive writes with **f_buffer**.
2. file_seek API tests
  + **FSEEK_END_TEST** tests if the function will move the cursor to the correct position inside the **__DATA.TXT** file, if started from the end of the file.
    4 bytes of data will be written to the position determined by the file_seek API, 16 bytes before the end of the file, then they will be read.
    If read data matches written data, then API functionality is validated.
  + **FSEEK_START_TEST** tests if the function will move the cursor to the correct position inside the **__DATA.TXT** file, if started from the beginning of the file.
    4 bytes of data will be written to the position determined by the file_seek API, 16 bytes from the beginning of the file, then they will be read.
    If read data matches written data, then API functionality is validated.
  + **FSEEK_MIDDLE_TEST** tests if the function will move the cursor to the correct position inside the **__DATA.TXT** file, if started from the current position of the cursor in the file.
    The position is chosen in such a way that read and write operations need to cross the sector boundary line.
    4 bytes of data will be written to the position determined by the file_seek API, at position 510, then they will be read.
    If read data matches written data, then API functionality is validated.
  + All these tests will automatically be validated and do not require any inspection.
3. **FSYNC_TEST** tests file_sync API functionality. File **__DATA.TXT** will be modified from position 512 to 768 and new contents should be "---127---|",
   where 127 represents a number of '-' characters. file_sync is called after this modification. The card should be pulled out at this moment and inspected on PC using an SD card reader.
   If new modifications are visible on the file, the API works as intended.
   It is important to note that unless **file_close** is called, file modification might not be saved and the file may become corrupted. **file_sync** allows file saving without closing.
4. **FTELL_TEST** tests file_tell API functionality. With the help of the **file_seek** API, the **__DATA.TXT** file cursor will be moved to position 768 inside the file.
   **file_tell** will be called next and if it returns the previously set cursor position as 768, the test will be considered passed otherwise failed.
   This test will validate itself automatically and does not require any inspection.
5. **FREWIND_TEST** tests file_rewind API functionality. **file_rewind** is called on the file **__DATA.TXT**, next the **file_tell** API will be called and it will return
   the current cursor position. If the cursor position determined by the **file_tell** API is zero, then will be considered successful, and otherwise failed.
   This test will validate itself automatically and does not require any inspection.
6. **FSIZE_TEST** tests **file_size** API functionality. **file_size** API will be called on the file **__DATA.TXT**, and if it return 1024,
   test is considered successful, and otherwise failed
   This test will validate itself automatically and does not require any inspection.
7. **DOPEN_TEST** test will make new directory **3:/__DIR** and new sub-directory in it **__SUBDIR**(**3:/__DIR/__SUBDIR**). It will then create a new file **__COPY.TXT**,
   in the directory **3:/__DIR** (**3:/__DIR/__COPY.TXT**), and copy the contents of the file **3:__DATA.TXT** to the file **3:/__DIR/__COPY.TXT**.
   In the end, the contents of the directory **3:/__DIR** will be printed on the application output. The user is expected to verify
   if the directory **__SUBDIR** and the file **__COPY.TXT** are displayed on the application output. It is also advised to inspect the contents of the SD card on a PC, and
   check if all files and directories are there, as well if data was successfully copied to the file **3:/__DIR/__COPY.TXT**.
   This test is designed to verify the interaction between several file system applications and more complex usage, as well as to validate the correct behavior of
   **dir_open**, **dir_read**, **file_system_mkdir** APIs.
8. **RENAME_TEST** test will make rename the directory **3:/__DIR/__SUBDIR** to **3:/__DIR/__SUB** and print out contents of the directory **3:/__DIR**.
   The user is expected to verify if the directory **__SUBDIR** was successfully renamed to **__SUB** by observing the application output. Directory **__SUB**
   and file **__COPY.TXT** are expected to be printed out.
   This test is designed to validate the correct behavior of **file_system_rename** API.
9. **REMOVE_TEST** test will make remove the directory **3:/__DIR/__SUB**.
   The user is expected to verify if the directory **__SUB** was successfully removed by observing the application output. Only the file **__COPY.TXT** is expected to be printed out.
   This test is designed to validate the correct behavior of **file_system_remove** API.
10. **BANDWIDTH_TEST** will create the file **3:/__DATA.TXT** and fill it with 1MB of content in order to test performance under stress.
   The user is expected to verify if the existence of **3:/__DATA.TXT** on a PC as well if it is filled with 1MB of data, as well is that the data is of the correct pattern described in 1.
11. **MULTI_READ_TEST** will use 4kB buffer to copy the data from **3:/__DATA.TXT** file to the newly created **3:/__DAT_MR.TXT**. this test is designed primarily to test
   SDSPI physical drive library usage of multi-block read and write commands as usage of large buffer forces is to do so.
   The user is expected to verify on PC using a card reader, the existence of **3:/__DAT_MR.TXT** and if the contents of **3:/__DATA.TXT** we copied successfully.
   This test uses a large buffer and it will require at least 7kB of RAM, which might not be available on smaller MCUs, therefore it is disabled by default.
