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
 * @file  ssd1312_cmd.h
 * @brief SSD1312 command definitions.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ssd1312 SSD1312 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ssd1312_commands SSD1312 Display Controller Commands
 * @brief SSD1312 Display Controller Command List
 * @{
 */
#ifndef SSD1312_CMD_H
#define SSD1312_CMD_H

/**
 * @brief Set lower column address (0x00 - 0x0F)
 */
#define SSD1312_CMD_COL_LOW 0x00

/**
 * @brief Set higher column address (0x10 - 0x17)
 */
#define SSD1312_CMD_COL_HIGH 0x10

/**
 * @brief Set memory addressing mode, followed by one byte (SSD1312_MEM_MODE_PAGE)
 */
#define SSD1312_CMD_MEM_MODE 0x20

/**
 * @brief Page addressing mode (default), parameter of SSD1312_CMD_MEM_MODE
 */
#define SSD1312_MEM_MODE_PAGE 0x02

/**
 * @brief Set contrast, followed by one byte (0x01 - 0xFF)
 */
#define SSD1312_CMD_CONTRAST 0x81

/**
 * @brief Segment re-map normal
 */
#define SSD1312_CMD_SEG_REMAP_OFF 0xA0

/**
 * @brief Segment re-map reversed
 */
#define SSD1312_CMD_SEG_REMAP_ON 0xA1

/**
 * @brief Set multiplex ratio, followed by one byte (0x0F - 0x3F)
 */
#define SSD1312_CMD_MULTIPLEX 0xA8

/**
 * @brief Multiplex ratio for 64 COM lines (the 64x128 module drives 64 rows; 0x7F breaks the picture)
 */
#define SSD1312_MULTIPLEX_64 0x3F

/**
 * @brief Display follows RAM content
 */
#define SSD1312_CMD_ENTIRE_OFF 0xA4

/**
 * @brief Entire display on
 */
#define SSD1312_CMD_ENTIRE_ON 0xA5

/**
 * @brief Normal display (1 = pixel on)
 */
#define SSD1312_CMD_NORMAL 0xA6

/**
 * @brief Reverse display (0 = pixel on)
 */
#define SSD1312_CMD_REVERSE 0xA7

/**
 * @brief Set display offset, followed by one byte
 */
#define SSD1312_CMD_DISPLAY_OFFSET 0xD3

/**
 * @brief Select external or internal IREF, followed by SSD1312_IREF_EXTERNAL or SSD1312_IREF_INTERNAL
 */
#define SSD1312_CMD_IREF_SELECT 0xAD

/**
 * @brief External IREF (default)
 */
#define SSD1312_IREF_EXTERNAL 0x40

/**
 * @brief Internal IREF is enabled while the display is on
 */
#define SSD1312_IREF_INTERNAL 0x50

/**
 * @brief Display off (sleep)
 */
#define SSD1312_CMD_DISPLAY_OFF 0xAE

/**
 * @brief Display on
 */
#define SSD1312_CMD_DISPLAY_ON 0xAF

/**
 * @brief Set page address (0xB0 - 0xBF; the 64x128 module uses 16 pages)
 */
#define SSD1312_CMD_PAGE_ADDR 0xB0

/**
 * @brief Common output scan direction normal
 */
#define SSD1312_CMD_COM_SCAN_NORMAL 0xC0

/**
 * @brief Common output scan direction reversed
 */
#define SSD1312_CMD_COM_SCAN_REVERSE 0xC8

/**
 * @brief Set display clock divide ratio / oscillator frequency, followed by one byte
 */
#define SSD1312_CMD_CLOCK_DIV 0xD5

/**
 * @brief Set dis-charge / pre-charge period, followed by one byte
 */
#define SSD1312_CMD_PRECHARGE 0xD9

/**
 * @brief Set VCOM deselect level, followed by one byte
 */
#define SSD1312_CMD_VCOM_DESELECT 0xDB

/**
 * @brief Set display start line, OR-ed with the line number (0x40 - 0x7F)
 */
#define SSD1312_CMD_START_LINE 0x40

/**
 * @brief Charge pump setting, followed by SSD1312_CHARGE_PUMP_OFF or SSD1312_CHARGE_PUMP_ON
 */
#define SSD1312_CMD_CHARGE_PUMP 0x8D

/**
 * @brief Internal charge pump disabled (default)
 */
#define SSD1312_CHARGE_PUMP_OFF 0x10

/**
 * @brief Internal charge pump enabled (7.5 V)
 */
#define SSD1312_CHARGE_PUMP_ON 0x12

/**
 * @brief Set SEG pins hardware configuration, followed by SSD1312_SEG_PINS_SEQUENTIAL or SSD1312_SEG_PINS_ALTERNATIVE
 */
#define SSD1312_CMD_SEG_PINS 0xDA

/**
 * @brief Sequential SEG pin configuration
 */
#define SSD1312_SEG_PINS_SEQUENTIAL 0x00

/**
 * @brief Alternative (odd/even) SEG pin configuration (default)
 */
#define SSD1312_SEG_PINS_ALTERNATIVE 0x10

/**
 * @brief Set command lock, followed by SSD1312_COMMAND_UNLOCK or SSD1312_COMMAND_LOCK
 */
#define SSD1312_CMD_COMMAND_LOCK 0xFD

/**
 * @brief Unlock the MCU interface, commands are accepted (default)
 */
#define SSD1312_COMMAND_UNLOCK 0x12

/**
 * @brief Lock the MCU interface, commands are ignored
 */
#define SSD1312_COMMAND_LOCK 0x16

/**
 * @brief I2C control byte: the following byte is a command
 */
#define SSD1312_CONTROL_COMMAND 0x00

/**
 * @brief I2C control byte: the following bytes are display data
 */
#define SSD1312_CONTROL_DATA 0x40

/**
 * @brief Delay after the reset pin is released, in milliseconds
 */
#define SSD1312_DELAY_RESET_MS 10

/**
 * @brief Delay after the display is turned on, in milliseconds
 */
#define SSD1312_DELAY_DISPLAY_ON_MS 100

/**
 * @brief Contrast after power on reset
 */
#define SSD1312_DEFAULT_CONTRAST 0x7F

#endif // SSD1312_CMD_H

/*! @} */ // ssd1312_commands
/*! @} */ // ssd1312
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------- END
