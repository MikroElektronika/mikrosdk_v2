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
 * @file  sh1107_cmd.h
 * @brief SH1107 command definitions.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup sh1107 SH1107 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup sh1107_commands SH1107 Display Controller Commands
 * @brief SH1107 Display Controller Command List
 * @{
 */
#ifndef SH1107_CMD_H
#define SH1107_CMD_H

/**
 * @brief Set lower column address (0x00 - 0x0F)
 */
#define SH1107_CMD_COL_LOW 0x00

/**
 * @brief Set higher column address (0x10 - 0x17)
 */
#define SH1107_CMD_COL_HIGH 0x10

/**
 * @brief Page addressing mode (default)
 */
#define SH1107_CMD_MEM_MODE_PAGE 0x20

/**
 * @brief Vertical addressing mode
 */
#define SH1107_CMD_MEM_MODE_VERT 0x21

/**
 * @brief Set contrast, followed by one byte (0x00 - 0xFF)
 */
#define SH1107_CMD_CONTRAST 0x81

/**
 * @brief Segment re-map normal
 */
#define SH1107_CMD_SEG_REMAP_OFF 0xA0

/**
 * @brief Segment re-map reversed
 */
#define SH1107_CMD_SEG_REMAP_ON 0xA1

/**
 * @brief Set multiplex ratio, followed by one byte (0x00 - 0x7F)
 */
#define SH1107_CMD_MULTIPLEX 0xA8

/**
 * @brief Display follows RAM content
 */
#define SH1107_CMD_ENTIRE_OFF 0xA4

/**
 * @brief Entire display on
 */
#define SH1107_CMD_ENTIRE_ON 0xA5

/**
 * @brief Normal display (1 = pixel on)
 */
#define SH1107_CMD_NORMAL 0xA6

/**
 * @brief Reverse display (0 = pixel on)
 */
#define SH1107_CMD_REVERSE 0xA7

/**
 * @brief Set display offset, followed by one byte
 */
#define SH1107_CMD_DISPLAY_OFFSET 0xD3

/**
 * @brief DC-DC control mode set, followed by SH1107_DCDC_OFF or SH1107_DCDC_ON
 */
#define SH1107_CMD_DCDC_CONTROL 0xAD

/**
 * @brief Built-in DC-DC converter off
 */
#define SH1107_DCDC_OFF 0x8A

/**
 * @brief Built-in DC-DC converter on
 */
#define SH1107_DCDC_ON 0x8B

/**
 * @brief Display off (sleep)
 */
#define SH1107_CMD_DISPLAY_OFF 0xAE

/**
 * @brief Display on
 */
#define SH1107_CMD_DISPLAY_ON 0xAF

/**
 * @brief Set page address (0xB0 - 0xBF)
 */
#define SH1107_CMD_PAGE_ADDR 0xB0

/**
 * @brief Common output scan direction normal
 */
#define SH1107_CMD_COM_SCAN_NORMAL 0xC0

/**
 * @brief Common output scan direction reversed
 */
#define SH1107_CMD_COM_SCAN_REVERSE 0xC8

/**
 * @brief Set display clock divide ratio / oscillator frequency, followed by one byte
 */
#define SH1107_CMD_CLOCK_DIV 0xD5

/**
 * @brief Set dis-charge / pre-charge period, followed by one byte
 */
#define SH1107_CMD_PRECHARGE 0xD9

/**
 * @brief Set VCOM deselect level, followed by one byte
 */
#define SH1107_CMD_VCOM_DESELECT 0xDB

/**
 * @brief Set display start line, followed by one byte (0x00 - 0x7F)
 */
#define SH1107_CMD_START_LINE 0xDC

/**
 * @brief Delay after the reset pin is released, in milliseconds
 */
#define SH1107_DELAY_RESET_MS 10

/**
 * @brief Delay after the display is turned on, in milliseconds
 */
#define SH1107_DELAY_DISPLAY_ON_MS 100

/**
 * @brief Contrast after power on reset
 */
#define SH1107_DEFAULT_CONTRAST 0x80

#endif // SH1107_CMD_H

/*! @} */ // sh1107_commands
/*! @} */ // sh1107
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------- END
