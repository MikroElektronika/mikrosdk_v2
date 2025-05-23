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

/*--------------------------------------------------------------------------Setting Graphics state--------------------------------------------------------------------------*/

#define FT800_ALPHA_FUNC( func, ref ) ( ( 0x09 << 24 ) | ( ( ( func ) & 0x07 ) << 8 ) | ( ( ref ) & 0xFF ) ) 
#define FT800_BITMAP_HANDLE( handle ) ( ( 0x05 << 24 ) | ( ( handle ) & 0x1F ) )
#define FT800_BITMAP_LAYOUT( format, linestride, height ) ( ( 0x07 << 24 ) | ( ( (format ) & 0x1F ) << 19 ) | ( ( ( linestride ) & 0x3FF ) << 9 ) | ( ( height ) & 0x1FF ) )
#define FT800_BITMAP_SIZE( filter, wrapx, wrapy, width, height ) ( ( 0x08 << 24 ) | ( ( ( filter ) & 0x01 ) << 20 ) | ( ( ( wrapx ) & 0x01 ) << 19 ) | ( ( ( wrapy ) & 0x01 ) << 18 ) | ( ( ( width ) & 0x1FF ) << 9 ) | ( ( height ) & 0x1FF ) )
#define FT800_BITMAP_SOURCE( addr ) ( ( 0x01 << 24 ) | ( ( addr ) & 0xFFFFF ) )
#define FT800_BITMAP_TRANSFORM_A( a ) ( ( 0x15 << 24 ) | ( ( a ) & 0x1FFFF ) )
#define FT800_BITMAP_TRANSFORM_B( b ) ( ( 0x16 << 24 ) | ( ( b ) & 0x1FFFF ) )
#define FT800_BITMAP_TRANSFORM_C( c ) ( ( 0x17 << 24 ) | ( ( c ) & 0xFFFFFF ) )
#define FT800_BITMAP_TRANSFORM_D( d ) ( ( 0x18 << 24 ) | ( ( d ) & 0x1FFFF ) )
#define FT800_BITMAP_TRANSFORM_E( e ) ( ( 0x19 << 24 ) | ( ( e ) & 0x1FFFF ) )
#define FT800_BITMAP_TRAMSFORM_F( f ) ( ( 0x1A << 24 ) | ( ( f ) & 0xFFFFFF ) )
#define FT800_BLEND_FUNC( src, dst ) ( ( 0x0B << 24 ) | ( ( ( src ) & 0x07 ) << 3 ) | ( ( dst ) & 0x07 ) )
#define FT800_CELL( cell ) ( ( 0x06 << 24 ) | ( ( cell ) & 0x7F ) )
#define FT800_CLEAR( c, s, t ) ( ( 0x26 << 24 ) | ( ( ( c ) & 0x1 ) << 2 ) | ( ( ( s ) & 0x1 ) << 1 ) | ( ( ( t ) & 0x1 ) << 0 ) )
#define FT800_CLEAR_COLOR_A( alpha ) ( ( 0x0F << 24 ) | ( ( alpha ) & 0xFF ) )
#define FT800_CLEAR_COLOR_RGB( red, green, blue ) ( ( 0x2 << 24 ) | ( ( ( red ) & 0xFF ) << 16 ) | ( ( ( green ) & 0xFF ) << 8 ) | ( ( ( blue ) & 0xFF ) << 0 ) )
#define FT800_CLEAR_STENCIL( s ) ( ( 0x11 << 24 ) | ( ( s ) & 0xFF ) )
#define FT800_CLEAR_TAG( t ) ( ( 0x12 << 24 ) | ( ( t ) & 0xFF ) )
#define FT800_COLOR_A( alpha ) ( ( 0x10 << 24 ) | ( ( alpha ) & 0xFF ) )
#define FT800_COLOR_MASK( r, g, b, a ) ( ( 0x20 << 24 ) | ( ( ( r ) & 0x01 ) << 3 ) | ( ( ( g ) & 0x01 ) << 2 ) | ( ( ( b ) & 0x01 ) << 1 ) | ( ( a ) & 0x01 ) )
#define FT800_COLOR_RGB( red, green, blue ) ( ( 0x04 << 24 ) | ( ( ( red ) & 0xFF ) << 16 ) | ( ( ( green ) & 0xFF ) << 8 ) | ( ( ( blue ) & 0xFF ) << 0 ) )
#define FT800_LINE_WIDTH( width ) ( ( 0x0E << 24 ) | ( ( width ) & 0xFFF ) )
#define FT800_POINT_SIZE( size ) ( ( 0xD<<24 ) | ( ( ( size ) & 0x1FFF ) << 0 ) )
#define FT800_RESTORE_CONTEX() ( 0x23 << 24 )
#define FT800_SAVE_CONTEX() ( 0x22 << 24 )
#define FT800_SCISSOR_SIZE( width, height ) ( ( 0x1C << 24 ) | ( ( ( width ) & 0x3FF ) << 10 ) | ( ( height ) & 0x3FF ) )
#define FT800_SCISSOR_XY( x, y ) ( ( 0x1B << 24 ) | ( ( ( x ) & 0x1FF ) << 9 ) | ( ( y ) & 0x1FF ) )
#define FT800_STENCIL_FUNC( func, ref, mask ) ( ( 0x0A << 24 ) | ( ( ( func ) & 0x0F ) << 16 ) | ( ( ( ref ) & 0xFF ) << 8 ) | ( ( mask ) & 0xFF ) )
#define FT800_STENCIL_MASK( mask ) ( ( 0x13 << 24 ) | ( ( mask ) & 0xFF ) )
#define FT800_STENCIL_OP( sfail, spass ) ( ( 0x0C << 24 ) | ( ( ( sfail ) & 0x07 ) << 3 ) | ( ( spass ) & 0x07 ) )
#define FT800_TAG( s ) ( ( 0x03 << 24 ) | ( ( s ) & 0xFF ) )
#define FT800_TAG_MASK( mask ) ( ( 0x14 << 24 ) | ( ( mask ) & 0x01 ) )

/*---------------------------------------------------------------------------End of Graphic state---------------------------------------------------------------------------*/


/*-------------------------------------------------------Drawing actions-------------------------------------------------------*/

#define FT800_BEGIN( prim ) ( ( 0x1F << 24 ) | ( ( ( prim ) & 0xF ) << 0 ) )
#define FT800_END() ( 0x21 << 24 )
#define FT800_VERTEX2F( x, y ) ( ( 0x01 << 30 ) | ( ( ( x ) & 0x7FFF ) << 15 ) | ( ( y ) & 0x7FFF ) )
#define FT800_VERTEX2II( x, y, handle, cell ) ( ( 0x2 << 30 ) | ( ( ( x ) & 0x1FF ) << 21 ) | ( ( ( y ) & 0x1FF ) << 12 ) | ( ( ( handle ) & 0x1F ) << 7 ) | ( ( ( cell ) & 0x7F ) << 0 ) )

/*----------------------------------------------------End of Drawing actions----------------------------------------------------*/


/*-----------------Execution control-----------------*/

#define FT800_JUMP( dest ) ( ( 0x1E << 24 ) | ( ( dest ) & 0xFFFF ) )
#define FT800_MACRO( m ) ( ( 0x25 << 24 ) | ( ( m ) & 0x01 ) )
#define FT800_CALL( dest ) ( ( 0x1D << 24 ) | ( ( dest ) & 0xFFFF ) )
#define FT800_RETURN() ( 0x24<<24 )
#define FT800_DISPLAY() ( 0x00<<24 )

/*--------------End of Execution control--------------*/


/*--------------Host commands--------------*/

#define FT800_ACTIVE                   0x00
#define FT800_STANDBY                  0x41
#define FT800_SLEEP                    0x42
#define FT800_PWRDOWN                  0x50
#define FT800_CLKEXT                   0x44
#define FT800_CLK48M                   0x62
#define FT800_CLK36M                   0x61
#define FT800_CORERST                  0x68
#define FT800_CMD_ADDRES               0x00

/*-----------End of Host commands----------*/


/*---------Graphics Primitives---------*/

#define FT800_BITMAPS                  1  
#define FT800_POINTS                   2  
#define FT800_LINES                    3
#define FT800_LINE_STRIP               4
#define FT800_EDGE_STRIP_R             5
#define FT800_EDGE_STRIP_L             6
#define FT800_EDGE_STRIP_A             7
#define FT800_EDGE_STRIP_B             8
#define FT800_RECTS                    9

/*------End of Graphics Primitives------*/


/*--------Graphics Bitmap Format--------*/

#define FT800_ARGB1555                 0
#define FT800_L1                       1
#define FT800_L4                       2
#define FT800_L8                       3
#define FT800_RGB332                   4
#define FT800_ARGB2                    5
#define FT800_ARGB4                    6
#define FT800_RGB565                   7
#define FT800_PALETTED                 8
#define FT800_TEXT8X8                  9
#define FT800_TEXTVGA                 10
#define FT800_BARGRAPH                11

/*----End of Graphics Bitmap Format----*/


/*--------Alpha functions constants--------*/

#define FT800_NEVER                    0
#define FT800_LESS                     1
#define FT800_LEQUAL                   2
#define FT800_GREATER                  3
#define FT800_GEQUAL                   4
#define FT800_EQUAL                    5
#define FT800_NOTEQUAL                 6
#define FT800_ALWAYS                   7

/*-----End of Alpha functions constants-----*/


/*---------Blend functions constants--------*/

#define FT800_BL_ZERO                     0
#define FT800_BL_ONE                      1
#define FT800_BL_SRC_ALPHA                2
#define FT800_BL_DST_ALPHA                3
#define FT800_BL_ONE_MINUS_SRC_ALPHA      4
#define FT800_BL_ONE_MINUS_DST_ALPHA      5

/*-----End of Blend functions constants-----*/


/*-------Stencil operation constants--------*/

#define FT800_ST_ZERO                     0
#define FT800_ST_KEEP                     1
#define FT800_ST_REPLACE                  2
#define FT800_ST_INCR                     3
#define FT800_ST_DECR                     4
#define FT800_ST_INVERT                   5

/*----End of Stencil operation constants----*/

/*-------Co-processor objects constants--------*/

#define FT800_RAM_CMD               0x108000
#define FT800_CMD_SWAP              0xFFFFFF01
#define FT800_CMD_DISPLAY           0x00000000  
#define FT800_CMD_DLSTART           0xFFFFFF00
#define FT800_CMD_CALIBRATE         0xFFFFFF15
#define FT800_CMD_TEXT              0xFFFFFF0C
#define FT800_CMD_NUMBER            0xFFFFFF2E
#define FT800_CMD_BUTTON            0xFFFFFF0D
#define FT800_CMD_CLOCK             0xFFFFFF14
#define FT800_CMD_GAUGE             0xFFFFFF13
#define FT800_CMD_GRADIENT          0xFFFFFF0B
#define FT800_CMD_KEYS              0xFFFFFF0E
#define FT800_CMD_PROGRESS          0xFFFFFF0F
#define FT800_CMD_SLIDER            0xFFFFFF10
#define FT800_CMD_SCROLLBAR         0xFFFFFF11
#define FT800_CMD_DIAL              0xFFFFFF2D
#define FT800_CMD_TOGGLE            0xFFFFFF12
#define FT800_CMD_TRACK             0xFFFFFF2C

/*------End of Co-processor objects constants-------*/


#endif 
// ------------------------------------------------------------------------- END
