/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/**
 * @brief MikroElektronika default TinyUSB config file.
 * @details File enables following classes for device module:
 *   + @ref CFG_TUD_CDC
 *   + @ref CFG_TUD_MSC
 *   + @ref CFG_TUD_HID
 *   + @ref CFG_TUD_MIDI
 *   + @ref CFG_TUD_VENDOR
 *   + @ref CFG_TUD_VIDEO
 *   + @ref CFG_TUD_USBTMC
 *   + @ref CFG_TUD_AUDIO
 *   + @ref CFG_TUD_DFU
 *   + @ref CFG_TUD_DFU_RUNTIME
 *   + @ref CFG_TUD_BTH
 *   + @ref CFG_TUD_ECM_RNDIS
 *   + @ref CFG_TUD_NCM - not enabled
 * @note Network class has 2 drivers:
 *         + ECM/RNDIS
 *         + NCM
 * @warning Only one of the drivers can be enabled.
 * @details File enables following classes for host module:
 *   + @ref TODO
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_TUSB_MCU OPT_MCU_NONE

//--------------------------------------------------------------------+
// MCU Specific Configuration
//--------------------------------------------------------------------+

#ifdef __HAS_DEVICE__
    // RHPort number used for device, default to port 0
    #ifndef BOARD_TUD_RHPORT
        #define BOARD_TUD_RHPORT (0)
    #endif

    // RHPort max operational speed
    #ifndef BOARD_TUD_MAX_SPEED
        #define BOARD_TUD_MAX_SPEED (OPT_MODE_DEFAULT_SPEED)
    #endif
#endif

#ifdef __HAS_HOST__
    // RHPort number used for host, default to port 1
    #ifndef BOARD_TUH_RHPORT
        #define BOARD_TUH_RHPORT (1)
    #endif

    // RHPort max operational speed
    #ifndef BOARD_TUH_MAX_SPEED
        #define BOARD_TUH_MAX_SPEED (OPT_MODE_DEFAULT_SPEED)
    #endif
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// defined by MikroE for default ISR
// set to 0 to use your own
#ifndef __USE_MIKROE_ISR__
    #define __USE_MIKROE_ISR__ (1)
#endif

// defined by compiler flags for flexibility
#ifndef CFG_TUSB_MCU
    #error CFG_TUSB_MCU must be defined
#endif

#ifndef CFG_TUC_ENABLED
    #define CFG_TUC_ENABLED (0)
#endif

#if (CFG_TUC_ENABLED==1) && !defined(TUP_TYPEC_RHPORTS_NUM)
    #define TUP_TYPEC_RHPORTS_NUM (1)
#endif

#ifndef CFG_TUSB_OS
    #define CFG_TUSB_OS (OPT_OS_NONE)
#endif

#ifndef CFG_TUSB_DEBUG
    #define CFG_TUSB_DEBUG (0)
#endif

#ifdef __HAS_DEVICE__
    // Enable Device stack
    #define CFG_TUD_ENABLED (1)
    #define TUD_OPT_RHPORT (0)

    // Default is max speed that hardware controller could support with on-chip PHY
    #ifndef CFG_TUD_MAX_SPEED
        #define CFG_TUD_MAX_SPEED (BOARD_TUD_MAX_SPEED)
    #endif
#endif

#ifdef __HAS_HOST__
    // Enable Host stack
    #define CFG_TUH_ENABLED (1)
    #define TUH_OPT_RHPORT (1)

    // Default is max speed that hardware controller could support with on-chip PHY
    #ifndef CFG_TUH_MAX_SPEED
        #define CFG_TUH_MAX_SPEED (BOARD_TUH_MAX_SPEED)
    #endif
#endif

/**
 * USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
    #define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
    #define CFG_TUSB_MEM_ALIGN __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
    #define CFG_TUD_ENDPOINT0_SIZE (64)
#endif

//------------- CLASS -------------//

#ifdef __HAS_DEVICE__
    // All device class modules are enabled by default.
    // TODO - ideja je da korisnik odabere sta zeli da koristi, pa po tome inkludujemo!
    #define CFG_TUD_CDC (1)
    #define CFG_TUD_MSC (1)
    #define CFG_TUD_HID (1)
    #define CFG_TUD_MIDI (1)
    #define CFG_TUD_VENDOR (1)
    #define CFG_TUD_VIDEO (1)
    #define CFG_TUD_USBTMC (1)
    #define CFG_TUD_AUDIO (1)
    #define CFG_TUD_DFU (1)
    #define CFG_TUD_DFU_RUNTIME (1)
    #define CFG_TUD_BTH (1)

    // Network class has 2 drivers: ECM/RNDIS and NCM.
    // Only one of the drivers can be enabled
    #define CFG_TUD_ECM_RNDIS (1)
    #define CFG_TUD_NCM (1-CFG_TUD_ECM_RNDIS)

    #if CFG_TUD_HID==1
        // HID buffer size Should be sufficient to hold ID (if any) + Data
        #ifndef CFG_TUD_HID_EP_BUFSIZE
            #define CFG_TUD_HID_EP_BUFSIZE (64)
        #endif
    #endif

    #if CFG_TUD_MSC==1
        // MSC buffer size Should be sufficient to hold ID (if any) + Data
        #ifndef CFG_TUD_MSC_EP_BUFSIZE
            #define CFG_TUD_MSC_EP_BUFSIZE (64)
        #endif
    #endif

    #if CFG_TUD_MIDI==1
        // MIDI FIFO size of TX and RX
        #ifndef CFG_TUD_MIDI_RX_BUFSIZE
            #define CFG_TUD_MIDI_RX_BUFSIZE (32)
        #endif
        #ifndef CFG_TUD_MIDI_TX_BUFSIZE
            #define CFG_TUD_MIDI_TX_BUFSIZE (32)
        #endif
    #endif

    #if CFG_TUD_VENDOR==1
        // VENDOR FIFO size of TX and RX
        #ifndef CFG_TUD_VENDOR_RX_BUFSIZE
            #define CFG_TUD_VENDOR_RX_BUFSIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)
        #endif
        #ifndef CFG_TUD_VENDOR_TX_BUFSIZE
            #define CFG_TUD_VENDOR_TX_BUFSIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)
        #endif
    #endif

    #if CFG_TUD_CDC==1
        // CDC FIFO size of TX and RX
        #ifndef CFG_TUD_CDC_RX_BUFSIZE
            #define CFG_TUD_CDC_RX_BUFSIZE (32)
        #endif
        #ifndef CFG_TUD_CDC_TX_BUFSIZE
            #define CFG_TUD_CDC_TX_BUFSIZE (32)
        #endif
    #endif

    #if CFG_TUD_VIDEO==1
        // The number of video streaming interfaces
        #ifndef CFG_TUD_VIDEO_STREAMING
            #define CFG_TUD_VIDEO_STREAMING (1)
        #endif

        // video streaming endpoint size
        #ifndef CFG_TUD_VIDEO_STREAMING_EP_BUFSIZE
            #define CFG_TUD_VIDEO_STREAMING_EP_BUFSIZE (256)
        #endif

        // use bulk endpoint for streaming interface
        #ifndef CFG_TUD_VIDEO_STREAMING_BULK
            #define CFG_TUD_VIDEO_STREAMING_BULK (0)
        #endif
    #endif

    #if CFG_TUD_USBTMC==1
        #ifndef CFG_TUD_USBTMC_ENABLE_INT_EP
            #define CFG_TUD_USBTMC_ENABLE_INT_EP (1)
        #endif
        #ifndef CFG_TUD_USBTMC_ENABLE_488
            #define CFG_TUD_USBTMC_ENABLE_488 (1)
        #endif
    #endif

    #if CFG_TUD_AUDIO==1
        #define TUD_AUDIO_HEADSET_STEREO_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
                                                + TUD_AUDIO_DESC_STD_AC_LEN\
                                                + TUD_AUDIO_DESC_CS_AC_LEN\
                                                + TUD_AUDIO_DESC_CLK_SRC_LEN\
                                                + TUD_AUDIO_DESC_INPUT_TERM_LEN\
                                                + TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN\
                                                + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
                                                + TUD_AUDIO_DESC_INPUT_TERM_LEN\
                                                + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
                                                /* Interface 1, Alternate 0 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                /* Interface 1, Alternate 1 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
                                                + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN\
                                                /* Interface 1, Alternate 2 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
                                                + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN\
                                                /* Interface 2, Alternate 0 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                /* Interface 2, Alternate 1 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
                                                + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN\
                                                /* Interface 2, Alternate 2 */\
                                                + TUD_AUDIO_DESC_STD_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_INT_LEN\
                                                + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
                                                + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
                                                + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)
        #ifndef CFG_TUD_AUDIO_FUNC_1_DESC_LEN
            #define CFG_TUD_AUDIO_FUNC_1_DESC_LEN (TUD_AUDIO_HEADSET_STEREO_DESC_LEN)
        #endif

        // How many formats are used, need to adjust USB descriptor if changed
        #ifndef CFG_TUD_AUDIO_FUNC_1_N_FORMATS
            #define CFG_TUD_AUDIO_FUNC_1_N_FORMATS (2)
        #endif

        // Audio format type I specifications
        #if defined(__RX__)
        #ifndef CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE
            // 16bit/48kHz is the best quality for Renesas RX
            #define CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE (48000)
        #endif
        #else
        #ifndef CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE
            // 24bit/96kHz is the best quality for full-speed, high-speed is needed beyond this
            #define CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE (96000)
        #endif
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX
            #define CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX (1)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX
            #define CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX (2)
        #endif

        // 16bit in 16bit slots
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_TX (2)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_1_RESOLUTION_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_1_RESOLUTION_TX (16)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_RX (2)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_1_RESOLUTION_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_1_RESOLUTION_RX (16)
        #endif

        #if defined(__RX__)
        // 8bit in 8bit slots
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_TX (1)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_TX (8)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_RX (1)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_RX (8)
        #endif
        #else
        // 24bit in 32bit slots
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_TX (4)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_TX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_TX (24)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_RX (4)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_RX
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_RESOLUTION_RX (24)
        #endif
        #endif

        // EP and buffer size - for isochronous EP´s, the buffer and EP size are equal (different sizes would not make sense)
        #ifndef CFG_TUD_AUDIO_ENABLE_EP_IN
            #define CFG_TUD_AUDIO_ENABLE_EP_IN (1)
        #endif

        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_1_EP_SZ_IN
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_1_EP_SZ_IN (TUD_AUDIO_EP_SIZE(CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE, CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_TX, CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX))
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_FORMAT_2_EP_SZ_IN
            #define CFG_TUD_AUDIO_FUNC_1_FORMAT_2_EP_SZ_IN (TUD_AUDIO_EP_SIZE(CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE, CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_TX, CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX))
        #endif

        #ifndef CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ
            #define CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ (TU_MAX(CFG_TUD_AUDIO_FUNC_1_FORMAT_1_EP_SZ_IN, CFG_TUD_AUDIO_FUNC_1_FORMAT_2_EP_SZ_IN)*2)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX
            // Maximum EP IN size for all AS alternate settings used
            #define CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX (TU_MAX(CFG_TUD_AUDIO_FUNC_1_FORMAT_1_EP_SZ_IN, CFG_TUD_AUDIO_FUNC_1_FORMAT_2_EP_SZ_IN))
        #endif

        // EP and buffer size - for isochronous EP´s, the buffer and EP size are equal (different sizes would not make sense)
        #ifndef CFG_TUD_AUDIO_ENABLE_EP_OUT
            #define CFG_TUD_AUDIO_ENABLE_EP_OUT (1)
        #endif

        #ifndef CFG_TUD_AUDIO_UNC_1_FORMAT_1_EP_SZ_OUT
            #define CFG_TUD_AUDIO_UNC_1_FORMAT_1_EP_SZ_OUT (TUD_AUDIO_EP_SIZE(CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE, CFG_TUD_AUDIO_FUNC_1_FORMAT_1_N_BYTES_PER_SAMPLE_RX, CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX))
        #endif
        #ifndef CFG_TUD_AUDIO_UNC_1_FORMAT_2_EP_SZ_OUT
            #define CFG_TUD_AUDIO_UNC_1_FORMAT_2_EP_SZ_OUT (TUD_AUDIO_EP_SIZE(CFG_TUD_AUDIO_FUNC_1_MAX_SAMPLE_RATE, CFG_TUD_AUDIO_FUNC_1_FORMAT_2_N_BYTES_PER_SAMPLE_RX, CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX))
        #endif

        #ifndef CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ
            #define CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ (TU_MAX(CFG_TUD_AUDIO_UNC_1_FORMAT_1_EP_SZ_OUT, CFG_TUD_AUDIO_UNC_1_FORMAT_2_EP_SZ_OUT)*2)
        #endif
        #ifndef CFG_TUD_AUDIO_FUNC_1_EP_OUT_SZ_MAX
            // Maximum EP IN size for all AS alternate settings used
            #define CFG_TUD_AUDIO_FUNC_1_EP_OUT_SZ_MAX (TU_MAX(CFG_TUD_AUDIO_UNC_1_FORMAT_1_EP_SZ_OUT, CFG_TUD_AUDIO_UNC_1_FORMAT_2_EP_SZ_OUT))
        #endif

        // Number of Standard AS Interface Descriptors (4.9.1) defined per audio function - this is required to be able to remember the current alternate settings of these interfaces - We restrict us here to have a constant number for all audio functions (which means this has to be the maximum number of AS interfaces an audio function has and a second audio function with less AS interfaces just wastes a few bytes)
        #ifndef CFG_TUD_AUDIO_FUNC_1_N_AS_INT
            #define CFG_TUD_AUDIO_FUNC_1_N_AS_INT (2)
        #endif

        // Size of control request buffer
        #ifndef CFG_TUD_AUDIO_FUNC_1_CTRL_BUF_SZ
            #define CFG_TUD_AUDIO_FUNC_1_CTRL_BUF_SZ (64)
        #endif
    #endif

    #if CFG_TUD_DFU==1
        #ifndef CFG_TUD_DFU_XFER_BUFSIZE
            #define CFG_TUD_DFU_XFER_BUFSIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)
        #endif
    #endif
#endif

#ifdef __HAS_HOST__
    // TODO
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */
