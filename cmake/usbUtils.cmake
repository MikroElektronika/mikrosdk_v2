#############################################################################
## Function used to set adequate TinyUSB sources/headers per selected MCU
#############################################################################
function(usb_get_device_lib_files libSourceList libHeaderList)
    set(listLocalSources "")
    set(listLocalHeaders "")

    ## Default config header
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/config/tusb_config.h")
    ## Host headers
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/hcd.h")
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/hub.h")
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/usbh.h")
    ## Device headers
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/dcd.h")
    list(APPEND listLocalHeaders "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/usbd.h")

    ## TODO - Add portable layer sources per MCU here.
    ## This should be correct but need to double check.
    if(${MCU_NAME} MATCHES "^MK[0-9].+$")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/nxp/khci/dcd_khci.c")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/nxp/khci/hcd_khci.c")
    elseif(${MCU_NAME} MATCHES "^TM4C12[39].+$")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/mentor/musb/dcd_musb.c")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/mentor/musb/hcd_musb.c")
    elseif(${MCU_NAME} MATCHES "^STM32.+$")
        if(${MCU_NAME} MATCHES "^STM32(F04.+|F07[028].+|F10[23].+|F30[23].[BC]|F30[23].[68DE]2?|F373.+|L0.[23].+|L1.+|L4.[23].+|G4.+)$")
            list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/st/stm32_fsdev/dcd_stm32_fsdev.c")
        else()
            list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/synopsys/dwc2/dcd_dwc2.c")
            list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/synopsys/dwc2/dwc2_common.c")
        endif()
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+$")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/synopsys/dwc2/dcd_dwc2.c")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/synopsys/dwc2/dwc2_common.c")
    elseif(${MCU_NAME} MATCHES "^PIC32.+$")
        if(${MCU_NAME} MATCHES "^PIC32MZ.+$")
            list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/microchip/pic32mz/dcd_pic32mz.c")
        elseif(${MCU_NAME} MATCHES "^PIC32MX.+$")
            # For PIC32MX460F512L atomic expresions for USB registers didn't work, so we should use the version of dcd without them.
            # This decision has been made after tests with plug-in-module and Explorer 16/32 board.
            # This probably affects all MCUs from the same datasheet.
            if(${MCU_NAME} MATCHES "^PIC32MX4[246].+")
                list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/microchip/pic32mx460/dcd_pic32mx460.c")
            else()
                list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/microchip/pic/dcd_pic.c")
            endif()
        endif()
    elseif(${MCU_NAME} MATCHES "^(ds)?PIC(24|33).+$")
        list(APPEND listLocalSources "${CMAKE_CURRENT_SOURCE_DIR}/lib/portable/microchip/pic/dcd_pic.c")
    else()
        message(FATAL_ERROR "USB sources not set for ${MCU_NAME}. Set them in ${CMAKE_CURRENT_FUNCTION} function in ${CMAKE_CURRENT_FUNCTION_LIST_FILE}.")
    endif()

    set(${libSourceList} ${listLocalSources} PARENT_SCOPE)
    set(${libHeaderList} ${listLocalHeaders} PARENT_SCOPE)
endfunction()

#############################################################################
## Function used to set adequate TinyUSB library headers per enabled function
#############################################################################
function(usb_get_header_list header_list selector)
    set(listLocal "")

    ## TODO - Add device/host header inclusion list here.
    if(${selector} STREQUAL "HOST")
        ## Host headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/hcd.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/hub.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/usbh.h")
    elseif(${selector} STREQUAL "DEVICE")
        ## Device headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/dcd.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/usbd.h")
    elseif(${selector} STREQUAL "COMMON")
        ## Common headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/tusb_option.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_common.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_mcu.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_fifo.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_compiler.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_verify.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_types.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/common/tusb_debug.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/config/tusb_config.h")
    elseif(${selector} STREQUAL "OSAL")
        ## Osal headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/osal/osal.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/osal/osal_none.h")
    elseif(${selector} STREQUAL "CLASS_HID")
        ## Class HID headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/hid/hid.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/hid/hid_host.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/hid/hid_device.h")
    elseif(${selector} STREQUAL "CLASS_MIDI")
        ## Class MIDI headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/midi/midi.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/midi/midi_device.h")
    elseif(${selector} STREQUAL "CLASS_AUDIO")
        ## Class MIDI headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/audio/audio.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/audio/audio_device.h")
    elseif(${selector} STREQUAL "CLASS_BTH")
        ## Class BTH headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/bth/bth_device.h")
    elseif(${selector} STREQUAL "CLASS_CDC")
        ## Class CDC headers
        ## CDC has additional headers for FTDI and CP210x MCUs - shall not be added
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_device.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_host.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_rndis.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_rndis_host.h")
    elseif(${selector} STREQUAL "CLASS_DFU")
        ## Class DFU headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/dfu/dfu.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/dfu/dfu_device.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/dfu/dfu_rt_device.h")
    elseif(${selector} STREQUAL "CLASS_MSC")
        ## Class MSC headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/msc/msc.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/msc/msc_device.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/msc/msc_host.h")
    elseif(${selector} STREQUAL "CLASS_NET")
        ## Class NET headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/net/ncm.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/net/net_device.h")
    elseif(${selector} STREQUAL "CLASS_USBTMC")
        ## Class USBTMC headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/usbtmc/usbtmc.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/usbtmc/usbtmc_device.h")
    elseif(${selector} STREQUAL "CLASS_VENDOR")
        ## Class VENDOR headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/vendor/vendor_device.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/vendor/vendor_host.h")
    elseif(${selector} STREQUAL "CLASS_VIDEO")
        ## Class VIDEO headers
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/video/video.h")
        list(APPEND listLocal "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/video/video_device.h")
    endif()

    set(${header_list} ${listLocal} PARENT_SCOPE)
endfunction()

#############################################################################
## Macro used to install adequate TinyUSB library headers
#############################################################################
macro(usb_install_headers list_in destination)
    install(
        FILES
            ${list_in}
        DESTINATION
            ${destination}
    )
endmacro()

#############################################################################
## Function to generate USB interface OPT_MCU macro for selected MCU
#############################################################################
function(usb_get_mcu_opt usb_opt_mcu)
    if(${MCU_NAME} MATCHES "^STM32.+$")
        string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_OPT)
    elseif(${MCU_NAME} MATCHES "^TM4C12[39].+$")
        string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_OPT)
    elseif(${MCU_NAME} MATCHES "^MK.+$")
        set(MCU_NAME_OPT "KINETIS_KL")
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+$")
        set(MCU_NAME_OPT "GD32VF103")
    elseif(${MCU_NAME} MATCHES "^PIC32MZ.+$")
        set(MCU_NAME_OPT "PIC32MZ")
    elseif(${MCU_NAME} MATCHES "^PIC32MX.+$")
        set(MCU_NAME_OPT "PIC32MX")
    elseif(${MCU_NAME} MATCHES "^dsPIC33.+$")
        set(MCU_NAME_OPT "DSPIC33")
    elseif(${MCU_NAME} MATCHES "^PIC24.+$")
        set(MCU_NAME_OPT "PIC24")
    else()
        message(FATAL_ERROR "OPT_MCU not set. Set it in ${CMAKE_CURRENT_FUNCTION} function in ${CMAKE_CURRENT_FUNCTION_LIST_FILE}.")
    endif()

    set(${usb_opt_mcu} "OPT_MCU_${MCU_NAME_OPT}" PARENT_SCOPE)
endfunction()

#############################################################################
## Macro to generate USB interface header file according to selected MCU
#############################################################################
macro(usb_generate_config fileDestination fileList)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set (extra_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_args extra_count)
    if (${extra_count} GREATER 0)
        string (SUBSTRING ${MCU_NAME} 0 9 first)
        string (SUBSTRING ${MCU_NAME} 10 11 last)
        # Create a list of directives
        set(MACRO_LIST "")
        # Define macro that will allow to include correct header
        # in in fsdev_stm32.h for all STMs
        if(${MCU_NAME} MATCHES "^STM32F[13].+")
            set(MCU "#define ${first}x${last}")
        elseif(${MCU_NAME} MATCHES "^STM32L4.+")
            set(MCU "#define ${first}xx")
        endif()

        foreach(ARGUMENT ${extra_args})
            string(APPEND MACRO_LIST "#define CFG_TUSB_MCU ${ARGUMENT}\n")
        endforeach()

        # Generate output file with adequate name and include directive
        configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallHeadersUsbConfig.cmake.in ${fileDestination}/${fileList})
    endif ()
endmacro()

#############################################################################
## Macro to generate USB default ISR according to selected MCU - src file
#############################################################################
macro(usb_generate_isr_source fileDestination fileList)
    set(ISR_MACRO "IRQHandlerUndefined")
    set(CLOCK_VALUE "(${OSC}*1000000UL)")
    ## TODO - Add default ISR handler per MCU.
    ## Create directives.
    if(${MCU_NAME} MATCHES "^STM32.+")
        if(${MCU_NAME} MATCHES "^STM32([FL]0|L4.[23]).+")
            set(ISR_MACRO "USB_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F3[0259].+")
            set(ISR_MACRO "USB_LP_CAN_RX0_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32(F37|L1|G4).+")
            set(ISR_MACRO "USB_LP_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F10[123].+")
            set(ISR_MACRO "USB_LP_CAN1_RX0_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F(10[57].+|[24].+)")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32(F7|L4[789AR]|H7).+")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32L4[PQRS][579].+")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        endif()
    elseif(${MCU_NAME} MATCHES "^TM4C.+")
        if(${MCU_NAME} MATCHES "^TM4C12[39].+")
            set(ISR_MACRO "USB0_IRQHandler")
        endif()
    elseif(${MCU_NAME} MATCHES "^MK.+")
            set(ISR_MACRO "USB0_IRQHandler")
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+$")
        set(ISR_MACRO "USB_IRQn_handler")
    # For XC compiler attribute word should be before function definition.
    elseif(${MCU_NAME} MATCHES "^PIC32MZ.+$")
        set(ISR_MACRO "__attribute__((interrupt(IPL2AUTO), vector(_USB_VECTOR))) USB_IRQn_handler")
    elseif(${MCU_NAME} MATCHES "^PIC32MX.+$")
        set(ISR_MACRO "__attribute__((interrupt(IPL5AUTO), vector(_USB_1_VECTOR))) USB_IRQn_handler")
    elseif(${MCU_NAME} MATCHES "^(ds)?PIC(24|33).+$")
        set(ISR_MACRO "__attribute__((interrupt, auto_psv)) _USB1Interrupt")
    endif()

    ## Generate output file with adequate name and include directive.
    configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallSourceUsbIsrC.cmake.in ${fileDestination}/${fileList})
endmacro()

#############################################################################
## Macro to generate USB default ISR according to selected MCU - header file
#############################################################################
macro(usb_generate_isr_header fileDestination fileList)
    set(ISR_MACRO "IRQHandlerUndefined")
    ## TODO - Add default ISR handler per MCU.
    ## Create directives.
    if(${MCU_NAME} MATCHES "^STM32.+")
        if(${MCU_NAME} MATCHES "^STM32([FL]0|L4.[23]).+")
            set(ISR_MACRO "USB_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F3[0259].+")
            set(ISR_MACRO "USB_LP_CAN_RX0_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32(F37|L1|G4).+")
            set(ISR_MACRO "USB_LP_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F10[123].+")
            set(ISR_MACRO "USB_LP_CAN1_RX0_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32F(10[57].+|[24].+)")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32(F7|L4[789AR]|H7).+")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        elseif(${MCU_NAME} MATCHES "^STM32L4[PQRS][579].+")
            set(ISR_MACRO "OTG_FS_IRQHandler")
        endif()
    elseif(${MCU_NAME} MATCHES "^TM4C.+")
        if(${MCU_NAME} MATCHES "^TM4C12[39].+")
            set(ISR_MACRO "USB0_IRQHandler")
        endif()
    elseif(${MCU_NAME} MATCHES "^MK.+")
            set(ISR_MACRO "USB0_IRQHandler")
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+$")
        set(ISR_MACRO "USB_IRQn_handler")
    elseif(${MCU_NAME} MATCHES "^PIC32.+$")
        set(ISR_MACRO "USB_IRQn_handler")
    elseif(${MCU_NAME} MATCHES "^(ds)?PIC(24|33).+$")
        set(ISR_MACRO "_USB1Interrupt")
    endif()

    find_chip_architecture(chip_architecture)
    if(${chip_architecture} STREQUAL "arm")
        set(ISR_PRAGMA "__attribute__((interrupt (\"IRQ\")))")
    elseif(${chip_architecture} STREQUAL "riscv")
        set(ISR_PRAGMA "__attribute__((interrupt))")
    elseif(${chip_architecture} STREQUAL "pic_32bit")
        set(ISR_PRAGMA "")
    elseif(${chip_architecture} STREQUAL "pic_16bit")
        set(ISR_PRAGMA "")
    endif()
    ## Generate output file with adequate name and include directive.
    configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallSourceUsbIsrH.cmake.in ${fileDestination}/${fileList})
endmacro()

#############################################################################
## Function to select USB HW specific init sequence for current MCU
#############################################################################
function(usb_set_init_sequence file_path)
    ## Set initially to unimplemented. User can set the API themself.
    set(${file_path} "unimplemented" PARENT_SCOPE)

    ## TODO - Add custom HW init sequences per MCU.
    if(${MCU_NAME} MATCHES "^STM32.+")
        if(${MCU_NAME} MATCHES "^STM32L0.[23].+")
            set(${file_path} "arm/st/implementation_1" PARENT_SCOPE)
        ## For STM32F0 MCUs only CFG_TUD_HID should be configured
        elseif (${MCU_NAME} MATCHES "^STM32F0[47][028].+")
            set(${file_path} "arm/st/implementation_2" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32F[24].[1235679].+")
            set(${file_path} "arm/st/implementation_3" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32F10[57].+")
            set(${file_path} "arm/st/implementation_4" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32F7.[235679].+")
            set(${file_path} "arm/st/implementation_5" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32(L4[1-9A][2-9]|G4).+")
            set(${file_path} "arm/st/implementation_6" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32L4[PQRS][579].+")
            set(${file_path} "arm/st/implementation_7" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32F3(02.[68BCDE]|03.[BCDE]|7[23].+)")
            set(${file_path} "arm/st/implementation_8" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^STM32(F10[23]|L1).+")
            set(${file_path} "arm/st/implementation_9" PARENT_SCOPE)
        endif()
    elseif(${MCU_NAME} MATCHES "^TM4C.+")
        if(${MCU_NAME} MATCHES "^TM4C123.+")
            ## Default TM4C123 implementation first.
            ## Following MCUs: `^TM4C123(3.+[56]|[G7].+[56])PZ$`
            set(${file_path} "arm/ti/implementation_2" PARENT_SCOPE)
            ## Then check for special cases and redefine if necessary.
            if(${MCU_NAME} MATCHES "^TM4C123(GH6(ZRB)|(ZXR)|(PGE))|(7H6PGE)$")
                set(${file_path} "arm/ti/implementation_3" PARENT_SCOPE)
            elseif(${MCU_NAME} MATCHES "^TM4C123[23].+[356]PM$|^TM4C123[67FG].+[56]PM$")
                set(${file_path} "arm/ti/implementation_4" PARENT_SCOPE)
            endif()
        elseif(${MCU_NAME} MATCHES "^TM4C129.+")
            set(${file_path} "arm/ti/implementation_1" PARENT_SCOPE)
        endif()
    elseif(${MCU_NAME} MATCHES "^MK.+")
            set(${file_path} "arm/nxp/implementation_1" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+$")
        set(${file_path} "riscv/gigadevice" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^PIC24FJ.+(DA.+|G(A[4].+|B([1246][01][068]|412)))$")
        set(${file_path} "microchip/pic16/implementation_1" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^PIC32.+$")
        if(${MCU_NAME} MATCHES "^PIC32MZ.+EF[EFGKHM][01][046][04]$")
            set(${file_path} "microchip/pic32/implementation_1" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^PIC32MX([5-79].+|2[12357].+[0-9][BDHL]|4[2-7].+[HL])$")
            set(${file_path} "microchip/pic32/implementation_2" PARENT_SCOPE)
        endif()
    else()
        message(FATAL_ERROR "${MCU_NAME} doesn't have USB")
    endif()

endfunction()

#############################################################################
## Disable MCUs without enough FLASH and/or RAM memory for USB
#############################################################################
function(check_usb_requirements check_usb)
    set(${check_usb} "false" PARENT_SCOPE)

    ## TODO - Check for minimum memory requirements in the end / possibly increase/decrease here.
    set(check_flash 10239)    # 10KB
    set(check_ram 3071)    # 3KB

    if (NOT MCU_FLASH)
        message(FATAL_ERROR ": MCU_FLASH not added to database for ${MCU_NAME}.")
        if (NOT MCU_RAM)
            message(FATAL_ERROR ": MCU_RAM not added to database for ${MCU_NAME}.")
        endif()
    endif()

    if (${MCU_FLASH} GREATER_EQUAL check_flash)
        if (${MCU_RAM} GREATER_EQUAL check_ram)
            set(${check_usb} "true" PARENT_SCOPE)
        endif()
    endif()
endfunction()

#############################################################################
## Checks if selected MCU has device/host/otg
#############################################################################
function(check_usb_components has_usb has_usb_interrupts usb_list)
    set(list_local "")
    set(has_usb "false" PARENT_SCOPE)
    set(has_usb_interrupts "true" PARENT_SCOPE)

    ## TODO - Add device/host definitions for supported MCUs
    ## TODO - Add device/host definitions for supported MCUs
    ## TODO - Be more specific with STM32G0 MCUs
    if(${MCU_NAME} MATCHES "^STM32.+")
        if ((${MCU_NAME} MATCHES "^STM32((L0.[23]|F0[47][028]|F[24].[1235679]|F10[57]|F7.[235679]|L4[1-9A][2-9]|L4[PQRS][579]|F373|F10[23]|L1|G4).+|F30(2.[68BCDE]|3.[BCDE]))"))
            if (${MCU_NAME} MATCHES "STM32G0.+")
                set(has_usb_interrupts "false" PARENT_SCOPE)
            endif()
            list(APPEND list_local "__HAS_DEVICE__")
            set(has_usb "true" PARENT_SCOPE)
        endif()
    elseif(${MCU_NAME} MATCHES "^TM4C.+")
        if(${MCU_NAME} MATCHES "^TM4C123[2-9|FG].+")
            list(APPEND list_local "__HAS_DEVICE__")
            set(has_usb "true" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^TM4C129.+")
            list(APPEND list_local "__HAS_DEVICE__")
            set(has_usb "true" PARENT_SCOPE)
        endif()
    elseif(${MCU_NAME} MATCHES "^MK[0-9].+")
            list(APPEND list_local "__HAS_DEVICE__")
            set(has_usb "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^GD32VF103.+")
        list(APPEND list_local "__HAS_DEVICE__")
        set(has_usb "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^PIC32M(Z.+EF[EFGKHM][01][046][04]|X([5-79].+|2[12357].+[0-9][BDHL]|4[2-7].+[HL]))$")
        list(APPEND list_local "__HAS_DEVICE__")
        set(has_usb "true" PARENT_SCOPE)
    elseif(${MCU_NAME} MATCHES "^PIC24FJ.+(DA.+|G(A[4].+|B([1246][01][068]|412)))$")
        list(APPEND list_local "__HAS_DEVICE__")
        set(has_usb "true" PARENT_SCOPE)
    endif()

    set(${usb_list} ${list_local} PARENT_SCOPE)
endfunction()

#############################################################################
## Function used to get adequate TinyUSB library source files for HOST
#############################################################################
function(usb_get_sources_host list_out)
    set(list_local "")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/usbh.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/host/hub.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_host.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/hid/hid_host.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/msc/msc_host.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/vendor/vendor_host.c")
    set(${list_out} ${list_local} PARENT_SCOPE)
endfunction()

#############################################################################
## Function used to get adequate TinyUSB library source files for DEVICE
#############################################################################
function(usb_get_sources_device list_out)
    set(list_local "")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/usbd.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/device/usbd_control.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/audio/audio_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/cdc/cdc_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/dfu/dfu_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/dfu/dfu_rt_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/hid/hid_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/midi/midi_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/msc/msc_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/net/ecm_rndis_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/net/ncm_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/usbtmc/usbtmc_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/vendor/vendor_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/video/video_device.c")
    list(APPEND list_local "${CMAKE_CURRENT_SOURCE_DIR}/lib/class/bth/bth_device.c")
    set(${list_out} ${list_local} PARENT_SCOPE)
endfunction()
