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
 * @file  ft800_reg.h
 * @brief FT800 Display Controller Registers.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ft800 FT800 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ft800_registers FT800 Display Controller Registers
 * @brief FT800 Display Controller Register List
 * @{
 */

#ifndef FT800_REG_H
#define FT800_REG_H

/**
 * @brief FT800 Peripheral Clock Register.
 * @details Register address specified for dividing main clock for PCLK.
 */
#define FT800_REG_PCLK              ( 0x10246C )

/**
 * @brief FT800 Peripheral Clock Polarity Register.
 * @details Register address for configuring PCLK polarity.
 */
#define FT800_REG_PCLK_POL          ( 0x102468 )

/**
 * @brief FT800 Clock Spread Spectrum Register.
 * @details Register address for controlling clock spread spectrum.
 */
#define FT800_REG_CSPREAD           ( 0x102464 )

/**
 * @brief FT800 Swizzle Register.
 * @details Register address for configuring RGB signal swizzle pattern.
 */
#define FT800_REG_SWIZZLE           ( 0x102460 )

/**
 * @brief FT800 Dithering Register.
 * @details Register address for enabling/disabling dithering.
 */
#define FT800_REG_DITHER            ( 0x10245C )

/**
 * @brief FT800 Outbits Register.
 * @details Register address for defining number of output bits per color
 * channel.
 */
#define FT800_REG_OUTBITS           ( 0x102458 )

/**
 * @brief FT800 Rotate Register.
 * @details Register address for screen rotation configuration.
 */
#define FT800_REG_ROTATE            ( 0x102454 )

/**
 * @brief FT800 End Vertical Synchronization Register.
 * @details Register address for end position of vertical sync pulse.
 */
#define FT800_REG_VSYNC1            ( 0x10244C )

/**
 * @brief FT800 Start Vertical Synchronization Register.
 * @details Register address for start position of vertical sync pulse.
 */
#define FT800_REG_VSYNC0            ( 0x102448 )

/**
 * @brief FT800 Vertical Display Size Register.
 * @details Register address for vertical display size in pixels.
 */
#define FT800_REG_VSIZE             ( 0x102444 )

/**
 * @brief FT800 Vertical Offset Area Register.
 * @details Register address for vertical offset of the active display area.
 */
#define FT800_REG_VOFFSET           ( 0x102440 )

/**
 * @brief FT800 Vertical Lines Number Register.
 * @details Register address for number of vertical lines per screen.
 */
#define FT800_REG_VCYCLE            ( 0x10243C )

/**
 * @brief FT800 End Horizontal Synchronization Register.
 * @details Register address for end position of horizontal sync pulse.
 */
#define FT800_REG_HSYNC1            ( 0x102438 )

/**
 * @brief FT800 Start Horizontal Synchronization Register.
 * @details Register address for start position of horizontal sync pulse.
 */
#define FT800_REG_HSYNC0            ( 0x102434 )

/**
 * @brief FT800 Horizontal Display Size Register.
 * @details Register address for horizontal display size in pixels.
 */
#define FT800_REG_HSIZE             ( 0x102430 )

/**
 * @brief FT800 Horizontal Offset Area Register.
 * @details Register address for horizontal offset of the active display area.
 */
#define FT800_REG_HOFFSET           ( 0x10242C )

/**
 * @brief FT800 Horizontal Clock Number Register.
 * @details Register address for number of horizontal clocks per line.
 */
#define FT800_REG_HCYCLE            ( 0x102428 )

/**
 * @brief FT800 Touchscreen TAP Mask Settings Register.
 * @details Register address for touchscreen TAP mask settings.
 */
#define FT800_REG_TAP_MASK          ( 0x102424 )

/**
 * @brief FT800 Touchscreen TAP CRC value Register.
 * @details Register address for touchscreen TAP CRC value.
 */
#define FT800_REG_TAP_CRC           ( 0x102420 )

/**
 * @brief FT800 Display List Swap Register.
 * @details Register address to control display list swapping.
 */
#define FT800_REG_DLSWAP            ( 0x102450 )

/**
 * @brief FT800 Active TAG Register.
 * @details Register address for setting the active object TAG.
 */
#define FT800_REG_TAG               ( 0x102478 )

/**
 * @brief FT800 TAG Y Value Register.
 * @details Register address for reading Y coordinate of TAG.
 */
#define FT800_REG_TAG_Y             ( 0x102474 )

/**
 * @brief FT800 TAG X Value Register.
 * @details Register address for reading X coordinate of TAG.
 */
#define FT800_REG_TAG_X             ( 0x102470 )

/**
 * @brief FT800 TAG Z1 Z2 Raw Values Register.
 * @details Returns raw Z1 and Z2 resistance values from the touch controller.
 */
#define FT800_REG_TOUCH_DIRECT_Z1Z2 ( 0x102578 )

/**
 * @brief FT800 TAG XY Raw Values Register.
 * @details Returns raw XY position data directly from the touch controller.
 */
#define FT800_REG_TOUCH_DIRECT_XY  ( 0x102574 )

/**
 * @brief FT800 Matrix Coefficient F Transformation Register.
 * @details Affine transform matrix coefficient F for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_F ( 0x102530 )

/**
 * @brief FT800 Matrix Coefficient E Transformation Register.
 * @details Affine transform matrix coefficient E for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_E ( 0x10252C )

/**
 * @brief FT800 Matrix Coefficient D Transformation Register.
 * @details Affine transform matrix coefficient D for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_D ( 0x102528 )

/**
 * @brief FT800 Matrix Coefficient C Transformation Register.
 * @details Affine transform matrix coefficient C for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_C ( 0x102524 )

/**
 * @brief FT800 Matrix Coefficient B Transformation Register.
 * @details Affine transform matrix coefficient B for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_B ( 0x102520 )

/**
 * @brief FT800 Matrix Coefficient A Transformation Register.
 * @details Affine transform matrix coefficient A for capacitive touch
 * calibration.
 */
#define FT800_REG_TOUCH_TRANSFORM_A ( 0x10251C )


/**
 * @brief FT800 Tag Value Register.
 * @details Returns the tag value of the object currently being touched.
 */
#define FT800_REG_TOUCH_TAG        ( 0x102518 )

/**
 * @brief FT800 Touched Object XY Coordinates Register.
 * @details Returns the XY coordinates of the object currently being touched
 * ( tagged ).
 */
#define FT800_REG_TOUCH_TAG_XY     ( 0x102514 )

/**
 * @brief FT800 Touched Screen XY Coordinates Register.
 * @details Returns the screen XY coordinates from the touch panel after
 * calibration.
 */
#define FT800_REG_TOUCH_SCREEN_XY  ( 0x102510 )

/**
 * @brief FT800 Touch Pressure Resistance Value Register.
 * @details Returns touch resistance ( Rz ) as a measure of touch pressure.
 */
#define FT800_REG_TOUCH_RZ         ( 0x10250C )

/**
 * @brief FT800 Touched Panel Raw XY Coordinates Register.
 * @details Returns raw uncalibrated XY coordinates from the touch panel.
 */
#define FT800_REG_TOUCH_RAW_XY     ( 0x102508 )

/**
 * @brief FT800 Touched Panel Raw XY Coordinates Register.
 * @details Sets the pressure threshold for Rz to detect a valid touch.
 */
#define FT800_REG_TOUCH_RZTHRESH   ( 0x102504 )

/**
 * @brief FT800 Oversampling Rate Measurments Register.
 * @details Configures the oversampling rate for touch measurements.
 */
#define FT800_REG_TOUCH_OVERSAMPLE ( 0x102500 )

/**
 * @brief FT800 Touch Settle Register.
 * @details Sets the touch settle time in system clocks before ADC conversion.
 */
#define FT800_REG_TOUCH_SETTLE     ( 0x1024FC )

/**
 * @brief FT800 Charging Touch Panel Register.
 * @details Sets the duration for charging the touch panel before measurement.
 */
#define FT800_REG_TOUCH_CHARGE     ( 0x1024F8 )

/**
 * @brief FT800 Touch ADC Mode Register.
 * @details Selects the ADC mode used for touch measurements.
 */
#define FT800_REG_TOUCH_ADC_MODE   ( 0x1024F4 )

/**
 * @brief FT800 Touch Mode Register.
 * @details Configures the overall operating mode of the touch screen.
 */
#define FT800_REG_TOUCH_MODE       ( 0x102104 )

/**
 * @brief FT800 Touch Press Detect Register.
 * @details Returns a non-zero value if a touch is currently detected.
 */
#define FT800_REG_TOUCH_PRESS      ( 2147516416 )

/**
 * @brief FT800 Playback Register.
 * @details Starts playback of the effect defined in FT800_REG_SOUND.
 */
#define FT800_REG_PLAY             ( 0x102488 )

/**
 * @brief FT800 Sound Register.
 * @details Specifies the sound effect to be played by the synthesizer.
 */
#define FT800_REG_SOUND            ( 0x102484 )

/**
 * @brief FT800 Sound Volume Register.
 * @details Sets the volume of the synthesizer sound effects ( 0 – 255 ).
 */
#define FT800_REG_VOL_SOUND        ( 0x102480 )

/**
 * @brief FT800 Playback Volume Register.
 * @details Sets the volume for audio playback ( 0 – 255 ).
 */
#define FT800_REG_VOL_PB           ( 0x10247C )

/**
 * @brief FT800 Active Playback Register.
 * @details Controls whether audio playback is currently active.
 */
#define FT800_REG_PLAYBACK_PLAY    ( 0x1024BC )

/**
 * @brief FT800 Playback Loop Register.
 * @details Enables or disables looping of the audio playback.
 */
#define FT800_REG_PLAYBACK_LOOP    ( 0x1024B8 )

/**
 * @brief FT800 Playback Format Register.
 * @details Defines the format of the audio playback ( e.g., linear PCM ).
 */
#define FT800_REG_PLAYBACK_FORMAT  ( 0x1024B4 )

/**
 * @brief FT800 Playback Frequency Register.
 * @details Sets the playback sampling frequency in Hz.
 */
#define FT800_REG_PLAYBACK_FREQ    ( 0x1024B0 )

/**
 * @brief FT800 Playback Pointer Reader Register.
 * @details Returns the current playback read pointer offset in bytes.
 */
#define FT800_REG_PLAYBACK_READPTR ( 0x1024AC )

/**
 * @brief FT800 Playback Lenght Buffer Register.
 * @details Sets the length in bytes of the audio buffer to be played.
 */
#define FT800_REG_PLAYBACK_LENGTH  ( 0x1024A8 )

/**
 * @brief FT800 Starting Address Playback Register.
 * @details Sets the starting address in RAM of the audio buffer.
 */
#define FT800_REG_PLAYBACK_START   ( 0x1024A4 )

/**
 * @brief FT800 Byte Offset Register.
 * @details Indicates the byte offset of the current display list in
 * FT800_RAM_DL.
 */
#define FT800_REG_CMD_DL           ( 0x1024EC )

/**
 * @brief FT800 Write Command Register.
 * @details Write-only register to append commands to the co-processor FIFO
 * buffer.
 */
#define FT800_REG_CMD_WRITE        ( 0x1024E8 )

/**
 * @brief FT800 Read Command Register.
 * @details Read-only register indicating where the graphics engine is
 * currently reading from the command FIFO.
 */
#define FT800_REG_CMD_READ         ( 0x1024E4 )

/**
 * @brief FT800 Tracker Register.
 * @details Base address for touch tag tracking information used by cmd_track().
 */
#define FT800_REG_TRACKER          ( 0x109000 )

/**
 * @brief FT800 PWM Duty Register.
 * @details Sets the duty cycle of the PWM output ( 0 – 128 ).
 */
#define FT800_REG_PWM_DUTY         ( 0x1024C4 )

/**
 * @brief FT800 PWM Frequency Register.
 * @details Sets the frequency of the PWM output in Hz.
 */
#define FT800_REG_PWM_HZ           ( 0x1024C0 )

/**
 * @brief FT800 Interrupt Mask Register.
 * @details Masks the interrupt flags. Each bit corresponds to a specific
 * interrupt source.
 */
#define FT800_REG_INT_MASK         ( 0x1024A0 )

/**
 * @brief FT800 Interrupt Enable Register.
 * @details Enables global interrupt generation.
 */
#define FT800_REG_INT_EN           ( 0x10249C )

/**
 * @brief FT800 Interrupt Flag Register.
 * @details Indicates current interrupt flags ( status ). Each bit corresponds
 * to a source.
 */
#define FT800_REG_FLAGS            ( 0x102498 )

/**
 * @brief FT800 GPIO Register.
 * @details Sets or reads values of the general-purpose IO pins.
 */
#define FT800_REG_GPIO             ( 0x102490 )

/**
 * @brief FT800 GPIO Direction Register.
 * @details Configures direction of GPIO pins ( input / output ).
 */
#define FT800_REG_GPIO_DIR         ( 0x10248C )

/**
 * @brief FT800 Coprocessor Reset Register.
 * @details Resets the FT800 coprocessor. Write 0 or 1 to control reset state.
 */
#define FT800_REG_CPURESET         ( 0x10241C )

/**
 * @brief FT800 Read Screenshot Register.
 * @details Used to read pixel data from the screen during screenshot operation.
 */
#define FT800_REG_SCREENSHOT_READ  ( 0x102554 )

/**
 * @brief FT800 Screenshot Engine Availability Register.
 * @details Indicates whether the screenshot engine is busy.
 */
#define FT800_REG_SCREENSHOT_BUSY  ( 0x1024D8 )

/**
 * @brief FT800 Start Screenshot Engine Register.
 * @details Starts the screenshot process when written to.
 */
#define FT800_REG_SCREENSHOT_START ( 0x102418 )

/**
 * @brief FT800 Screenshot Y Coordinate Register.
 * @details Sets the Y-coordinate at which the screenshot will be captured.
 */
#define FT800_REG_SCREENSHOT_Y     ( 0x102414 )

/**
 * @brief FT800 Screenshot Enable Register.
 * @details Enables or disables the screenshot functionality.
 */
#define FT800_REG_SCREENSHOT_EN    ( 0x102410 )

/**
 * @brief FT800 Frequency Register.
 * @details Returns the operating frequency of the internal clock in Hz.
 */
#define FT800_REG_FREQUENCY        ( 0x10240C )

/**
 * @brief FT800 Clock Register.
 * @details Returns the number of clock cycles since startup.
 */
#define FT800_REG_CLOCK            ( 0x102408 )

/**
 * @brief FT800 Frames Register.
 * @details Returns the number of display frames rendered since power-up.
 */
#define FT800_REG_FRAMES           ( 0x102404 )

/**
 * @brief FT800 ID Register.
 * @details Chip ID register. Should return 0x7C for FT800.
 */
#define FT800_REG_ID               ( 0x102400 )

/**
 * @brief FT800 Trim Register.
 * @details Trims internal oscillator frequency ( write-only,
 * factory-calibrated ).
 */
#define FT800_REG_TRIM             ( 0x10256C )

/**
 * @brief FT800 Display List Address.
 * @details Base address of the Display List memory, where graphics rendering
 * commands are stored.
 */
#define FT800_RAM_DL               ( 0x100000 )

  /*! @} */ // ft800_registers
 /*! @} */ // ft800
/*! @} */ // mwgroup

#endif
// ------------------------------------------------------------------------- END
