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
 * @file  ft800_reg.h
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

#ifndef FT800_REG_H
#define FT800_REG_H

/*--------Graphic Engine Registers--------*/

#define FT800_REG_PCLK              0x10246C
#define FT800_REG_PCLK_POL          0x102468
#define FT800_REG_CSPREAD           0x102464
#define FT800_REG_SWIZZLE           0x102460
#define FT800_REG_DITHER            0x10245C
#define FT800_REG_OUTBITS           0x102458
#define FT800_REG_ROTATE            0x102454
#define FT800_REG_VSYNC1            0x10244C
#define FT800_REG_VSYNC0            0x102448
#define FT800_REG_VSIZE             0x102444
#define FT800_REG_VOFFSET           0x102440
#define FT800_REG_VCYCLE            0x10243C
#define FT800_REG_HSYNC1            0x102438
#define FT800_REG_HSYNC0            0x102434
#define FT800_REG_HSIZE             0x102430
#define FT800_REG_HOFFSET           0x10242C
#define FT800_REG_HCYCLE            0x102428
#define FT800_REG_TAP_MASK          0x102424
#define FT800_REG_TAP_CRC           0x102420
#define FT800_REG_DLSWAP            0x102450
#define FT800_REG_TAG               0x102478
#define FT800_REG_TAG_Y             0x102474
#define FT800_REG_TAG_X             0x102470

/*-----End of Graphic Engine Registers-----*/


/*---------Touch Engine Registers----------*/

#define FT800_REG_TOUCH_DIRECT_Z1Z2 0x102578
#define FT800_REG_TOUCH_DIRECT_XY   0x102574
#define FT800_REG_TOUCH_TRANSFORM_F 0x102530
#define FT800_REG_TOUCH_TRANSFORM_E 0x10252C
#define FT800_REG_TOUCH_TRANSFORM_D 0x102528
#define FT800_REG_TOUCH_TRANSFORM_C 0x102524
#define FT800_REG_TOUCH_TRANSFORM_B 0x102520
#define FT800_REG_TOUCH_TRANSFORM_A 0x10251C
#define FT800_REG_TOUCH_TAG         0x102518
#define FT800_REG_TOUCH_TAG_XY      0x102514
#define FT800_REG_TOUCH_SCREEN_XY   0x102510
#define FT800_REG_TOUCH_RZ          0x10250C
#define FT800_REG_TOUCH_RAW_XY      0x102508
#define FT800_REG_TOUCH_RZTHRESH    0x102504
#define FT800_REG_TOUCH_OVERSAMPLE  0x102500
#define FT800_REG_TOUCH_SETTLE      0x1024FC
#define FT800_REG_TOUCH_CHARGE      0x1024F8
#define FT800_REG_TOUCH_ADC_MODE    0x1024F4
#define FT800_REG_TOUCH_MODE        0x102104
#define FT800_REG_TOUCH_PRESS       2147516416 

/*------End of Touch Engine Registers------*/


/*---------Audio Engine Registers----------*/

#define FT800_REG_PLAY              0x102488
#define FT800_REG_SOUND             0x102484
#define FT800_REG_VOL_SOUND         0x102480
#define FT800_REG_VOL_PB            0x10247C
#define FT800_REG_PLAYBACK_PLAY     0x1024BC
#define FT800_REG_PLAYBACK_LOOP     0x1024B8
#define FT800_REG_PLAYBACK_FORMAT   0x1024B4
#define FT800_REG_PLAYBACK_FREQ     0x1024B0
#define FT800_REG_PLAYBACK_READPTR  0x1024AC
#define FT800_REG_PLAYBACK_LENGTH   0x1024A8
#define FT800_REG_PLAYBACK_START    0x1024A4

/*------End of Audio Engine Registers------*/


/*------Co-processor Engine Registers------*/

#define FT800_REG_CMD_DL            0x1024EC
#define FT800_REG_CMD_WRITE         0x1024E8
#define FT800_REG_CMD_READ          0x1024E4
#define FT800_REG_TRACKER           0x109000

/*---End of Co-processor Engine Registers--*/


/*---------Miscellaneous Registers---------*/

#define FT800_REG_PWM_DUTY          0x1024C4
#define FT800_REG_PWM_HZ            0x1024C0
#define FT800_REG_INT_MASK          0x1024A0
#define FT800_REG_INT_EN            0x10249C
#define FT800_REG_FLAGS             0x102498
#define FT800_REG_GPIO              0x102490
#define FT800_REG_GPIO_DIR          0x10248C
#define FT800_REG_CPURESET          0x10241C
#define FT800_REG_SCREENSHOT_READ   0x102554
#define FT800_REG_SCREENSHOT_BUSY   0x1024D8
#define FT800_REG_SCREENSHOT_START  0x102418
#define FT800_REG_SCREENSHOT_Y      0x102414
#define FT800_REG_SCREENSHOT_EN     0x102410
#define FT800_REG_FREQUENCY         0x10240C
#define FT800_REG_CLOCK             0x102408
#define FT800_REG_FRAMES            0x102404
#define FT800_REG_ID                0x102400
#define FT800_REG_TRIM              0x10256C

/*--End of Miscellaneous Engine Registers--*/

#define RAM_DL                      0x100000


#endif 
// ------------------------------------------------------------------------- END
