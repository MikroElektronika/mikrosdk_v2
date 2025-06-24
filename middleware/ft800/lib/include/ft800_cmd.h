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
 * @file  ft800_cmd.h
 * @brief FT800 Display Controller Commands.
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
 * @addtogroup ft800_commands FT800 Display Controller Commands
 * @brief FT800 Display Controller Command List
 * @{
 */

#ifndef FT800_CMD_H
#define FT800_CMD_H

/**
 * @brief FT800 Alpha Function.
 * @details Macro for specifying the alpha test function.
 */
#define FT800_ALPHA_FUNC( func, ref ) ( ( 0x09 << 24 ) | ( ( ( func ) & 0x07 ) \
         << 8 ) | ( ( ref ) & 0xFF ) )

/**
 * @brief FT800 Bitmap Handle.
 * @details Macro for specifying the bitmap handle.
 */
#define FT800_BITMAP_HANDLE( handle ) ( ( 0x05 << 24 ) | ( ( handle ) & 0x1F ) )

/**
 * @brief FT800 Bitmap Layout.
 * @details Macro for specifying the source bitmap memory format and layout
 * for the current handle.
 */
#define FT800_BITMAP_LAYOUT( format, linestride, height ) ( ( 0x07 << 24 ) | \
        ( ( (format ) & 0x1F ) << 19 ) | ( ( ( linestride ) & 0x3FF ) << 9 ) | \
        ( ( height ) & 0x1FF ) )

/**
 * @brief FT800 Bitmap Size.
 * @details Macro for specifying the screen drawing of bitmaps for the current
 * handle.
 */
#define FT800_BITMAP_SIZE( filter, wrapx, wrapy, width, height ) ( ( 0x08 << 24 ) \
        | ( ( ( filter ) & 0x01 ) << 20 ) | ( ( ( wrapx ) & 0x01 ) << 19 ) | \
        ( ( ( wrapy ) & 0x01 ) << 18 ) | ( ( ( width ) & 0x1FF ) << 9 ) | \
        ( ( height ) & 0x1FF ) )

/**
 * @brief FT800 Bitmap Source.
 * @details Macro for specifying the source address of bitmap data in FT800
 * graphics memory RAM_G.
 */
#define FT800_BITMAP_SOURCE( addr ) ( ( 0x01 << 24 ) | ( ( addr ) & 0xFFFFF ) )

/**
 * @brief FT800 Bitmap Transformation A.
 * @details Macro for specifying the A coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRANSFORM_A( a ) ( ( 0x15 << 24 ) | ( ( a ) & 0x1FFFF ) )

/**
 * @brief FT800 Bitmap Transformation B.
 * @details Macro for specifying the B coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRANSFORM_B( b ) ( ( 0x16 << 24 ) | ( ( b ) & 0x1FFFF ) )

/**
 * @brief FT800 Bitmap Transformation C.
 * @details Macro for specifying the C coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRANSFORM_C( c ) ( ( 0x17 << 24 ) | ( ( c ) & 0xFFFFFF ) )

/**
 * @brief FT800 Bitmap Transformation D.
 * @details Macro for specifying the D coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRANSFORM_D( d ) ( ( 0x18 << 24 ) | ( ( d ) & 0x1FFFF ) )

/**
 * @brief FT800 Bitmap Transformation E.
 * @details Macro for specifying the E coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRANSFORM_E( e ) ( ( 0x19 << 24 ) | ( ( e ) & 0x1FFFF ) )

/**
 * @brief FT800 Bitmap Transformation F.
 * @details Macro for specifying the F coefficient of the bitmap transform matrix.
 */
#define FT800_BITMAP_TRAMSFORM_F( f ) ( ( 0x1A << 24 ) | ( ( f ) & 0xFFFFFF ) )

/**
 * @brief FT800 Blen Function.
 * @details Macro for specifying pixel arithmetic.
 */
#define FT800_BLEND_FUNC( src, dst ) ( ( 0x0B << 24 ) | ( ( ( src ) & 0x07 ) \
        << 3 ) | ( ( dst ) & 0x07 ) )

/**
 * @brief FT800 Cell.
 * @details Macro for specifying the bitmap cell number for the VERTEX2F command.
 */
#define FT800_CELL( cell ) ( ( 0x06 << 24 ) | ( ( cell ) & 0x7F ) )

/**
 * @brief FT800 Clear.
 * @details Macro for cleaning buffers to preset values.
 */
#define FT800_CLEAR( c, s, t ) ( ( 0x26 << 24 ) | ( ( ( c ) & 0x1 ) << 2 ) | \
        ( ( ( s ) & 0x1 ) << 1 ) | ( ( ( t ) & 0x1 ) << 0 ) )

/**
 * @brief FT800 Clear Color A.
 * @details Macro for specifying clear value for the alpha channel.
 */
#define FT800_CLEAR_COLOR_A( alpha ) ( ( 0x0F << 24 ) | ( ( alpha ) & 0xFF ) )

/**
 * @brief FT800 Clear Color RGB.
 * @details Macro for specifying clear values for red, green and blue channels.
 */
#define FT800_CLEAR_COLOR_RGB( red, green, blue ) ( ( 0x2 << 24 ) | ( ( ( red ) \
        & 0xFF ) << 16 ) | ( ( ( green ) & 0xFF ) << 8 ) | ( ( ( blue ) & 0xFF ) \
        << 0 ) )

/**
 * @brief FT800 Clear Stencil.
 * @details Macro for specifying clear value for the stencil buffer.
 */
#define FT800_CLEAR_STENCIL( s ) ( ( 0x11 << 24 ) | ( ( s ) & 0xFF ) )

/**
 * @brief FT800 Clear Tag.
 * @details Macro for specifying clear value for the tag buffer.
 */
#define FT800_CLEAR_TAG( t ) ( ( 0x12 << 24 ) | ( ( t ) & 0xFF ) )

/**
 * @brief FT800 Color A.
 * @details Macro for setting current color alpha.
 */
#define FT800_COLOR_A( alpha ) ( ( 0x10 << 24 ) | ( ( alpha ) & 0xFF ) )

/**
 * @brief FT800 Color Mask.
 * @details Macro for enabling or disabling writing of color components.
 */
#define FT800_COLOR_MASK( r, g, b, a ) ( ( 0x20 << 24 ) | ( ( ( r ) & 0x01 ) \
        << 3 ) | ( ( ( g ) & 0x01 ) << 2 ) | ( ( ( b ) & 0x01 ) << 1 ) | \
        ( ( a ) & 0x01 ) )

/**
 * @brief FT800 Color RGB.
 * @details Macro for setting current color red, green and blue.
 */
#define FT800_COLOR_RGB( red, green, blue ) ( ( 0x04 << 24 ) | ( ( ( red ) & \
        0xFF ) << 16 ) | ( ( ( green ) & 0xFF ) << 8 ) | ( ( ( blue ) & 0xFF ) \
        << 0 ) )

/**
 * @brief FT800 Line Width.
 * @details Macro for specifying the width of lines to be drawn with primitive
 * FT800_LINES in 1/16 pixel precision.
 */
#define FT800_LINE_WIDTH( width ) ( ( 0x0E << 24 ) | ( ( width ) & 0xFFF ) )

/**
 * @brief FT800 Point Size.
 * @details Macro for specifying the radius of points.
 */
#define FT800_POINT_SIZE( size ) ( ( 0xD<<24 ) | ( ( ( size ) & 0x1FFF ) << 0 ) )

/**
 * @brief FT800 Restore Contex.
 * @details Macro for restoring the current graphics context from the context
 * stack.
 */
#define FT800_RESTORE_CONTEX() ( 0x23 << 24 )

/**
 * @brief FT800 Save Contex.
 * @details Macro for pushing the current graphics context on the context stack.
 */
#define FT800_SAVE_CONTEX() ( 0x22 << 24 )

/**
 * @brief FT800 Scissor Size.
 * @details Macro for specifying the size of the scissor clip rectangle.
 */
#define FT800_SCISSOR_SIZE( width, height ) ( ( 0x1C << 24 ) | ( ( ( width ) & \
        0x3FF ) << 10 ) | ( ( height ) & 0x3FF ) )

/**
 * @brief FT800 Scissor XY.
 * @details Macro for specifying the top left corner of the scissor clip rectangle.
 */
#define FT800_SCISSOR_XY( x, y ) ( ( 0x1B << 24 ) | ( ( ( x ) & 0x1FF ) << 9 ) \
        | ( ( y ) & 0x1FF ) )

/**
 * @brief FT800 Stencil Function.
 * @details Macro for setting value for stencil testing.
 */
#define FT800_STENCIL_FUNC( func, ref, mask ) ( ( 0x0A << 24 ) | ( ( ( func ) \
        & 0x0F ) << 16 ) | ( ( ( ref ) & 0xFF ) << 8 ) | ( ( mask ) & 0xFF ) )

/**
 * @brief FT800 Stencil Mask.
 * @details Macro for control the writing of individual bits in the stencil planes.
 */
#define FT800_STENCIL_MASK( mask ) ( ( 0x13 << 24 ) | ( ( mask ) & 0xFF ) )

/**
 * @brief FT800 Stencil Operation.
 * @details Macro for setting stencil test actions.
 */
#define FT800_STENCIL_OP( sfail, spass ) ( ( 0x0C << 24 ) | ( ( ( sfail ) \
        & 0x07 ) << 3 ) | ( ( spass ) & 0x07 ) )

/**
 * @brief FT800 Tag.
 * @details Macro for attachment the tag value for the following graphics objects
 * drawn on the screen.
 */
#define FT800_TAG( s ) ( ( 0x03 << 24 ) | ( ( s ) & 0xFF ) )

/**
 * @brief FT800 Tag Mask.
 * @details Macro for control the writing of the tag buffer.
 */
#define FT800_TAG_MASK( mask ) ( ( 0x14 << 24 ) | ( ( mask ) & 0x01 ) )

/**
 * @brief FT800 Begin.
 * @details Macro for beginning drawing a graphics primitive.
 */
#define FT800_BEGIN( prim ) ( ( 0x1F << 24 ) | ( ( ( prim ) & 0xF ) << 0 ) )

/**
 * @brief FT800 End.
 * @details Macro for ending drawing a graphics primitive.
 */
#define FT800_END() ( 0x21 << 24 )

/**
 * @brief FT800 VERTEX2F.
 * @details Macro for starting the operation of graphics primitives at the
 * specified screen coordinate, in 1/16th pixel precision.
 */
#define FT800_VERTEX2F( x, y ) ( ( 0x01 << 30 ) | ( ( ( x ) & 0x7FFF ) << 15 ) \
        | ( ( y ) & 0x7FFF ) )

/**
 * @brief FT800 VERTEX2II.
 * @details Macro for starting the operation of graphics primitive at the
 * specified coordinates in pixel precision.
 */
#define FT800_VERTEX2II( x, y, handle, cell ) ( ( 0x2 << 30 ) | ( ( ( x ) & \
        0x1FF ) << 21 ) | ( ( ( y ) & 0x1FF ) << 12 ) | ( ( ( handle ) & 0x1F ) \
        << 7 ) | ( ( ( cell ) & 0x7F ) << 0 ) )

/**
 * @brief FT800 Jump.
 * @details Macro for executing commands at another location in the display list.
 */
#define FT800_JUMP( dest ) ( ( 0x1E << 24 ) | ( ( dest ) & 0xFFFF ) )

/**
 * @brief FT800 Macro.
 * @details Macro for executing a single command from a macro register.
 */
#define FT800_MACRO( m ) ( ( 0x25 << 24 ) | ( ( m ) & 0x01 ) )

/**
 * @brief FT800 Call.
 * @details Macro for executing a sequence of commands at another location in
 * the display list.
 */
#define FT800_CALL( dest ) ( ( 0x1D << 24 ) | ( ( dest ) & 0xFFFF ) )

/**
 * @brief FT800 Return.
 * @details Macro for returning from a previous CALL command.
 */
#define FT800_RETURN() ( 0x24 << 24 )

/**
 * @brief FT800 Display.
 * @details Macro for ending display list.
 */
#define FT800_DISPLAY() ( 0x00 << 24 )

/**
 * @brief FT800 Active Host Command.
 * @details Switch from Standby/Sleep modes to active mode.
 */
#define FT800_ACTIVE                        ( 0x00 )

/**
 * @brief FT800 Standby Host Command.
 * @details Put FT800 core to standby mode, clock gate are off, PLL and
 * oscillator remain on.
 */
#define FT800_STANDBY                       ( 0x41 )

/**
 * @brief FT800 Host Command.
 * @details Put FT800 core to sleep mode, clock gate, PLL and oscillator are off.
 */
#define FT800_SLEEP                         ( 0x42 )

/**
 * @brief FT800 Host Command.
 * @details Switch off 1.2V internal regulator, clock, PLL and oscillator are off.
 */
#define FT800_PWRDOWN                       ( 0x50 )

/**
 * @brief FT800 Host Command.
 * @details Enable PLL input from crystal oscillator or external input clock.
 */
#define FT800_CLKEXT                        ( 0x44 )

/**
 * @brief FT800 Host Command.
 * @details Switch PLL output clock to 48MHz.
 */
#define FT800_CLK48M                        ( 0x62 )

/**
 * @brief FT800 Host Command.
 * @details Switch PLL output clock to 36MHz.
 */
#define FT800_CLK36M                        ( 0x61 )

/**
 * @brief FT800 Host Command.
 * @details Send reset pulse to FT800 core and all registers and state machines
 * will be reset.
 */
#define FT800_CORERST                       ( 0x68 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing bitmaps.
 */
#define FT800_BITMAPS                       ( 1 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing points.
 */
#define FT800_POINTS                        ( 2 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing lines.
 */
#define FT800_LINES                         ( 3 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing strips.
 */
#define FT800_LINE_STRIP                    ( 4 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing right side edge
 * strip.
 */
#define FT800_EDGE_STRIP_R                  ( 5 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing left side edge strip.
 */
#define FT800_EDGE_STRIP_L                  ( 6 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing above strip.
 */
#define FT800_EDGE_STRIP_A                  ( 7 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing below strip.
 */
#define FT800_EDGE_STRIP_B                  ( 8 )

/**
 * @brief FT800 Graphic Primitives.
 * @details The value sent to the function to start drawing rectangles.
 */
#define FT800_RECTS                         ( 9 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting ARGB1555 bitmap layout.
 */
#define FT800_ARGB1555                      ( 0 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting L1 bitmap layout.
 */
#define FT800_L1                            ( 1 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting L4 bitmap layout.
 */
#define FT800_L4                            ( 2 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting L8 bitmap layout.
 */
#define FT800_L8                            ( 3 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting RGB232 bitmap layout.
 */
#define FT800_RGB332                        ( 4 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting ARGB2 bitmap layout.
 */
#define FT800_ARGB2                         ( 5 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting ARGB4 bitmap layout.
 */
#define FT800_ARGB4                         ( 6 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting RGB565 bitmap layout.
 */
#define FT800_RGB565                        ( 7 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting Paletted bitmap layout.
 */
#define FT800_PALETTED                      ( 8 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting TEXT8X8 bitmap layout.
 */
#define FT800_TEXT8X8                       ( 9 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting TEXTVGA bitmap layout.
 */
#define FT800_TEXTVGA                       ( 10 )

/**
 * @brief FT800 Bitmap Format.
 * @details The value sent to the function for selecting Bargraph bitmap layout.
 */
#define FT800_BARGRAPH                      ( 11 )

/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on NEVER
 * mode.
 */
#define FT800_NEVER                         ( 0 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on LESS
 * mode.
 */
#define FT800_LESS                          ( 1 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on LEQUAL
 * mode.
 */
#define FT800_LEQUAL                        ( 2 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on GREATER
 * mode.
 */
#define FT800_GREATER                       ( 3 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on GEQUAL
 * mode.
 */
#define FT800_GEQUAL                        ( 4 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on EQUAL
 * mode.
 */
#define FT800_EQUAL                         ( 5 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on NOTEQUAL
 * mode.
 */
#define FT800_NOTEQUAL                      ( 6 )


/**
 * @brief FT800 Alpha Functions Constants.
 * @details The value sent to the function for setting alpha function on ALWAYS
 * mode.
 */
#define FT800_ALWAYS                        ( 7 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on ZERO
 * mode.
 */
#define FT800_BL_ZERO                       ( 0 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on ONE
 * mode.
 */
#define FT800_BL_ONE                        ( 1 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on
 * SRC_ALPHA  mode.
 */
#define FT800_BL_SRC_ALPHA                  ( 2 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on
 * DST_ALPHA mode.
 */
#define FT800_BL_DST_ALPHA                  ( 3 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on
 * ONE_MINUS_SRC_ALPHA mode.
 */
#define FT800_BL_ONE_MINUS_SRC_ALPHA        ( 4 )

/**
 * @brief FT800 Blend Functions Constants.
 * @details The value sent to the function for setting blend function on
 * ONE_MINUS_DST_ALPHA mode.
 */
#define FT800_BL_ONE_MINUS_DST_ALPHA        ( 5 )

/**
 * @brief FT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer is set to
 * zero.
 */
#define FT800_ST_ZERO                       ( 0 )

/**
 * @brief FT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer keep his
 * value.
 */
#define FT800_ST_KEEP                       ( 1 )


/**
 * @brief FT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer replaced
 * his value.
 */
#define FT800_ST_REPLACE                    ( 2 )


/**
 * @brief FT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer increment
 * his value.
 */
#define FT800_ST_INCR                       ( 3 )


/**
 * @brief FFT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer decrement
 * his value.
 */
#define FT800_ST_DECR                       ( 4 )


/**
 * @brief FT800 Stencil Operation Constants.
 * @details The value sent to the function means that stencill buffer invert his
 * value.
 */
#define FT800_ST_INVERT                     ( 5 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details This adress indicates the starting address of the FIFO command buffer.
 */
#define FT800_CMD_ADDRES                    ( 0x000000 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details Starting adress of location where is it stored co-processor commands.
 */
#define FT800_RAM_CMD                       ( 0x108000 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, it requests a
 * display list swap immediately after current display list is scanned out.
 */
#define FT800_CMD_SWAP                      ( 0xFFFFFF01 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will end
 * display list and display everything that is drawn in it.
 */
#define FT800_CMD_DISPLAY                   ( 0x00000000 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, it waits until
 * the current display list is scanned out, then sets FT800_REG_CMD_DL to zero.
 */
#define FT800_CMD_DLSTART                   ( 0xFFFFFF00 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will start
 * calibration routine.
 */
#define FT800_CMD_CALIBRATE                 ( 0xFFFFFF15 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * text.
 */
#define FT800_CMD_TEXT                      ( 0xFFFFFF0C )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * number.
 */
#define FT800_CMD_NUMBER                    ( 0xFFFFFF2E )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * button widget.
 */
#define FT800_CMD_BUTTON                    ( 0xFFFFFF0D )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * clock widget.
 */
#define FT800_CMD_CLOCK                     ( 0xFFFFFF14 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * gauge widget.
 */
#define FT800_CMD_GAUGE                     ( 0xFFFFFF13 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will fill
 * area with gradient color.
 */
#define FT800_CMD_GRADIENT                  ( 0xFFFFFF0B )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * keys.
 */
#define FT800_CMD_KEYS                      ( 0xFFFFFF0E )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * progress bar widget.
 */
#define FT800_CMD_PROGRESS                  ( 0xFFFFFF0F )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * slider.
 */
#define FT800_CMD_SLIDER                    ( 0xFFFFFF10 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * scroll bar widget.
 */
#define FT800_CMD_SCROLLBAR                 ( 0xFFFFFF11 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * dial widget.
 */
#define FT800_CMD_DIAL                      ( 0xFFFFFF2D )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will draw a
 * toggle widget.
 */
#define FT800_CMD_TOGGLE                    ( 0xFFFFFF12 )

/**
 * @brief FT800 Co-Processor Objects Commands.
 * @details When the co-processor engine executes this command, he will start
 * track a press detection and movement at defined area.
 */
#define FT800_CMD_TRACK                     ( 0xFFFFFF2C )

  /*! @} */ // ft800_commands
 /*! @} */ // ft800
/*! @} */ // mwgroup

#endif
// ------------------------------------------------------------------------- END
