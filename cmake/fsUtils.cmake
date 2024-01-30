#############################################################################
## Function to define lists used in configuring the FileSystem library
#############################################################################
function(set_file_system_config library_file_list include_dir_list interface_dir_list install_headers_list)

    set(library_file_list_local "")
    set(include_dir_list_local "")
    set(interface_dir_list_local "")
    set(install_headers_list_local "")

    ## TODO  temprorary fix, until MIKROSDK_FILESYSTEM_FAT is defined in/by NECTO
    set(MIKROSDK_FILESYSTEM_FAT true)

    # define files list used by the FileSystem library
    list(APPEND library_file_list_local "src/file_system.c")
    list(APPEND library_file_list_local "src/file.c")
    list(APPEND library_file_list_local "src/dir.c")
    list(APPEND library_file_list_local "private/include/fs_common.h")
    list(APPEND library_file_list_local "include/ff_types.h")
    list(APPEND library_file_list_local "include/ffconf.h")
    list(APPEND library_file_list_local "include/file_system.h")
    list(APPEND library_file_list_local "include/file.h")
    list(APPEND library_file_list_local "include/dir.h")
    if(${MIKROSDK_FILESYSTEM_FAT} STREQUAL true)
        list(APPEND library_file_list_local "fat/FatFs/ff.c")
        list(APPEND library_file_list_local "fat/FatFs/ffsystem.c")
        list(APPEND library_file_list_local "fat/FatFs/ffunicode.c")
        list(APPEND library_file_list_local "fat/FatFs/ff.h")
        list(APPEND library_file_list_local "fat/FatFs/diskio.h")
        list(APPEND library_file_list_local "fat/include/fatfs.h")
        list(APPEND library_file_list_local "fat/src/fatfs.c")
    endif()
    # TODO in the future, new file system implementation other than FatFs, files need to be added here
    set(${library_file_list} ${library_file_list_local} PARENT_SCOPE)

    # define include directories list used by the FileSystem library
    list(APPEND include_dir_list_local "private/include")
    list(APPEND include_dir_list_local "include")
    if(${MIKROSDK_FILESYSTEM_FAT} STREQUAL true)
        list(APPEND include_dir_list_local "fat/FatFs")
        list(APPEND include_dir_list_local "fat/include")
    endif()
    # TODO in the future, new file system implementation other than FatFs, include directories need to be added here
    set(${include_dir_list} ${include_dir_list_local} PARENT_SCOPE)

    # define interface directories list used by the FileSystem library
    list(APPEND interface_dir_list_local "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
    list(APPEND interface_dir_list_local "$<INSTALL_INTERFACE:include/middleware/filesystem>")
    if(${MIKROSDK_FILESYSTEM_FAT} STREQUAL true)
        list(APPEND interface_dir_list_local "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fat/include>")
    endif()
    # TODO in the future, new file system implementations other than FatFs, interface directories need to be added here
    list(SORT interface_dir_list_local)
    set(${interface_dir_list} ${interface_dir_list_local} PARENT_SCOPE)

    # define headers files list used by the FileSystem library
    list(APPEND install_headers_list_local "include/file_system.h")
    list(APPEND install_headers_list_local "include/ffconf.h")
    list(APPEND install_headers_list_local "include/file.h")
    list(APPEND install_headers_list_local "include/dir.h")
    list(APPEND install_headers_list_local "include/ff_types.h")
    if(${MIKROSDK_FILESYSTEM_FAT} STREQUAL true)
        list(APPEND install_headers_list_local "fat/include/fatfs.h")
    endif()
    # TODO in the future, new file system implementations other than FatFs, header files need to be added here
    set(${install_headers_list} ${install_headers_list_local} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to define lists used in configuring the PhysicalDrive library
#############################################################################
function(set_physical_drive_system_config library_file_list include_dir_list interface_dir_list install_headers_list)

    set(library_file_list_local "")
    set(include_dir_list_local "")
    set(interface_dir_list_local "")
    set(install_headers_list_local "")

    ## TODO temprorary fix, add buttons and checkboxes
    set(MIKROSDK_PHYSICAL_DRIVE_SDSPI true)

    # define files list used by the PhysicalDrive library
    list(APPEND library_file_list_local "src/physical_drive.c")
    list(APPEND library_file_list_local "include/physical_drive.h")
    list(APPEND library_file_list_local "private/include/pd_common.h")
    if(${MIKROSDK_PHYSICAL_DRIVE_SDSPI} STREQUAL true)
        list(APPEND library_file_list_local "sd/sdspi/src/sdspi_physical_drive.c")
        list(APPEND library_file_list_local "sd/sdspi/include/sdspi_physical_drive.h")
        list(APPEND library_file_list_local "sd/include/sd_common.h")
    endif()
    # TODO in the future, new physical drive implementation other than SD-SPI, files need to be added here
    set(${library_file_list} ${library_file_list_local} PARENT_SCOPE)

    # define include direcotories list used by the PhysicalDrive library
    list(APPEND include_dir_list_local "private/include")
    list(APPEND include_dir_list_local "include")
    if(${MIKROSDK_PHYSICAL_DRIVE_SDSPI} STREQUAL true)
        list(APPEND include_dir_list_local "sd/sdspi/include")
        list(APPEND include_dir_list_local "sd/include")
    endif()
    # TODO in the future, new physical drive implementation other than SD-SPI, include directories need to be added here
    set(${include_dir_list} ${include_dir_list_local} PARENT_SCOPE)

    # define interface directories list used by the PhysicalDrive library
    list(APPEND interface_dir_list_local "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
    list(APPEND interface_dir_list_local "$<INSTALL_INTERFACE:include/middleware/physical_drive>")
    if(${MIKROSDK_PHYSICAL_DRIVE_SDSPI} STREQUAL true)
        list(APPEND interface_dir_list_local "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sd/sdspi/include>")
    endif()
    # TODO in the future, new physical drive implementation other than SD-SPI, interface directories need to be added here
    list(SORT interface_dir_list_local)
    set(${interface_dir_list} ${interface_dir_list_local} PARENT_SCOPE)

    # define headers list used by the PhysicalDrive library
    list(APPEND install_headers_list_local "include/physical_drive.h")
    if(${MIKROSDK_PHYSICAL_DRIVE_SDSPI} STREQUAL true)
        list(APPEND install_headers_list_local "sd/sdspi/include/sdspi_physical_drive.h")
    endif()
    # TODO in the future, new physical drive implementation other than SD-SPI, header files need to be added here
    set(${install_headers_list} ${install_headers_list_local} PARENT_SCOPE)
endfunction()

#############################################################################
## Function used to disbale MCUs without enough FLASH and/or RAM memory
#############################################################################
function(memory_test_check enough_memory)
    set(${enough_memory} "false" PARENT_SCOPE)

    # TODO SWMIKSDK-1541
    # if ((NOT ${TOOLCHAIN_ID} MATCHES "mikroc") AND (NOT ${TOOLCHAIN_ID} STREQUAL "xpack-riscv-none-embed-gcc") AND ((NOT ${TOOLCHAIN_ID} STREQUAL "gcc_arm_none_eabi")))
        # message(FATAL_ERROR "File System memory requirements for ${test_compiler} compiler, must be set in ${CMAKE_CURRENT_FUNCTION} function inside ${CMAKE_CURRENT_FUNCTION_LIST_FILE}.")
    # endif()

    # Numbers used here represent the minimal memory requirements for FileSystem in unit of bytes
    # Their value is determined empirically
    set (check_ram 3071)           #3kB
    set (check_flash 65535)        #64kB
    if (${TOOLCHAIN_ID} STREQUAL "mikrocpic")
        set (check_flash 98303)    #96kB
    elseif(${TOOLCHAIN_ID} STREQUAL "mikrocarm")
        set (check_ram 2559)       #2.5kB
        set (check_flash 32767)    #32kB
    endif()

    if (NOT MCU_FLASH)
        message(FATAL_ERROR ": MCU_FLASH not added to database for ${MCU_NAME}.")
        if (NOT MCU_RAM)
            message(FATAL_ERROR ": MCU_RAM not added to database for ${MCU_NAME}.")
        endif()
    endif()

    if (${MCU_FLASH} GREATER_EQUAL check_flash)
        if (${MCU_RAM} GREATER_EQUAL check_ram)
            set(${enough_memory} "true" PARENT_SCOPE)
        endif()
    endif()
endfunction()
