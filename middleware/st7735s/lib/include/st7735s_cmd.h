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
 * @file  st7735s_cmd.h
 * @brief ST7735S Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7735s ST7735S Display Controller Driver
 * @{
 */

/*!
 * @addtogroup st7735s_commands ST7735S Display Controller Commands
 * @brief ST7735S Display Controller Command List
 * @{
 */
#ifndef ST7735S_CMD_H
#define ST7735S_CMD_H

/**
 * @brief Software Reset
 */
#define ST7735S_CMD_SWRESET 0x01

/**
 * @brief Sleep Out
 */
#define ST7735S_CMD_SLPOUT 0x11

/**
 * @brief Normal Display Mode On
 */
#define ST7735S_CMD_NORON 0x13

/**
 * @brief Display Inversion Off
 */
#define ST7735S_CMD_INVOFF 0x20

/**
 * @brief Display Inversion On
 */
#define ST7735S_CMD_INVON 0x21

/**
 * @brief Display Off
 */
#define ST7735S_CMD_DISPOFF 0x28

/**
 * @brief Display On
 */
#define ST7735S_CMD_DISPON 0x29

/**
 * @brief Column Address Set
 */
#define ST7735S_CMD_CASET 0x2A

/**
 * @brief Row Address Set
 */
#define ST7735S_CMD_RASET 0x2B

/**
 * @brief Memory Write
 */
#define ST7735S_CMD_RAMWR 0x2C

/**
 * @brief Memory Data Access Control.
 */
#define ST7735S_CMD_MADCTL 0x36

/**
 * @brief Interface Pixel Format.
 */
#define ST7735S_CMD_COLMOD 0x3A

/**
 * @brief Frame Rate Control (normal mode, idle mode, partial mode).
 */
#define ST7735S_CMD_FRMCTR1 0xB1
#define ST7735S_CMD_FRMCTR2 0xB2
#define ST7735S_CMD_FRMCTR3 0xB3

/**
 * @brief Display Inversion Control (dot / column inversion, not the same as INVON).
 */
#define ST7735S_CMD_INVCTR 0xB4

/**
 * @brief Power Control 1 to 5.
 */
#define ST7735S_CMD_PWCTR1 0xC0
#define ST7735S_CMD_PWCTR2 0xC1
#define ST7735S_CMD_PWCTR3 0xC2
#define ST7735S_CMD_PWCTR4 0xC3
#define ST7735S_CMD_PWCTR5 0xC4

/**
 * @brief VCOM Control 1.
 */
#define ST7735S_CMD_VMCTR1 0xC5

/**
 * @brief Gamma ('+' and '-' polarity) Correction Characteristics Setting.
 */
#define ST7735S_CMD_GMCTRP1 0xE0
#define ST7735S_CMD_GMCTRN1 0xE1

/**
 * @brief COLMOD parameter: 65K colors, 16 bits per pixel (RGB565).
 */
#define ST7735S_COLMOD_16BIT 0x55

/**
 * @brief MADCTL bits: row address order, column address order, row/column exchange
 * and RGB-BGR order (0 = RGB color filter panel, 1 = BGR color filter panel).
 */
#define ST7735S_MADCTL_MY  0x80
#define ST7735S_MADCTL_MX  0x40
#define ST7735S_MADCTL_MV  0x20
#define ST7735S_MADCTL_RGB 0x08

/**
 * @brief Time to wait after Software Reset, in milliseconds.
 */
#define ST7735S_DELAY_SWRESET_MS 120

/**
 * @brief Time to wait after Sleep Out, in milliseconds.
 */
#define ST7735S_DELAY_SLPOUT_MS 120
/*! @} */ // st7735s_commands
/*! @} */ // st7735s
/*! @} */ // mwgroup

#endif // ST7735S_CMD_H
// ------------------------------------------------------------------------- END