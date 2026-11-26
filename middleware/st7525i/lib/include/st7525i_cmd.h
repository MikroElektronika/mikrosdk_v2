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
 * @file  st7525i_cmd.h
 * @brief ST7525I command definitions.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7525i ST7525I Display Controller Driver
 * @{
 */

/*!
 * @addtogroup st7525i_commands ST7525I Display Controller Commands
 * @brief ST7525I Display Controller Command List
 * @{
 */
#ifndef ST7525I_CMD_H
#define ST7525I_CMD_H

/**
 * @brief Set lower column address (0x00 - 0x0F)
 */
#define ST7525I_CMD_COL_LOW 0x00

/**
 * @brief Set higher column address (0x10 - 0x1B)
 */
#define ST7525I_CMD_COL_HIGH 0x10

/**
 * @brief Set contrast, followed by one byte (0x00 - 0xFF)
 */
#define ST7525I_CMD_CONTRAST 0x81

/**
 * @brief Display follows RAM content
 */
#define ST7525I_CMD_ENTIRE_OFF 0xA4

/**
 * @brief Entire display on
 */
#define ST7525I_CMD_ENTIRE_ON 0xA5

/**
 * @brief Normal display (1 = pixel on)
 */
#define ST7525I_CMD_NORMAL 0xA6

/**
 * @brief Reverse display (0 = pixel on)
 */
#define ST7525I_CMD_REVERSE 0xA7

/**
 * @brief Display off (power down)
 */
#define ST7525I_CMD_DISPLAY_OFF 0xAE

/**
 * @brief Display on
 */
#define ST7525I_CMD_DISPLAY_ON 0xAF

/**
 * @brief Set page address (0xB0 - 0xB8)
 */
#define ST7525I_CMD_PAGE_ADDR 0xB0

/**
 * @brief Set display start line (first line of RAM shown at the top), 0x40 - 0x7F
 */
#define ST7525I_CMD_SCROLL_LINE 0x40

/**
 * @brief Set RAM address control (how the address counters move after each byte)
 */
#define ST7525I_CMD_RAM_ADDR_CTRL 0x88

/**
 * @brief Set frame rate, ORed with 0 (76 fps) to 3 (168 fps)
 */
#define ST7525I_CMD_FRAME_RATE 0xA0

/**
 * @brief Set scan direction, ORed with ST7525I_SCAN_DIR_MX and/or ST7525I_SCAN_DIR_MY
 */
#define ST7525I_CMD_SCAN_DIR 0xC0

/**
 * @brief Scan direction flag: reverse segment (column) direction
 */
#define ST7525I_SCAN_DIR_MX 0x02

/**
 * @brief Scan direction flag: reverse common (row) direction
 */
#define ST7525I_SCAN_DIR_MY 0x04

/**
 * @brief Software reset (does not reset the LCD power supply)
 */
#define ST7525I_CMD_SOFT_RESET 0xE2

/**
 * @brief Set LCD bias ratio, ORed with 0 (1/6) to 3 (1/9)
 */
#define ST7525I_CMD_BIAS 0xE8

/**
 * @brief Set COM end (display duty), followed by one byte, duty is 1/(value + 2) (reset value 0x3F = 1/65)
 */
#define ST7525I_CMD_COM_END 0xF1

/**
 * @brief Delay after the reset pin is released, in milliseconds
 */
#define ST7525I_DELAY_RESET_MS 10

/**
 * @brief Contrast after power on reset
 */
#define ST7525I_DEFAULT_CONTRAST 0x49

#endif // ST7525I_CMD_H

/*! @} */ // st7525i_commands
/*! @} */ // st7525i
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------- END
