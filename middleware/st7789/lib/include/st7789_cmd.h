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
 * @file  st7789_cmd.h
 * @brief ST7789 Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7789 ST7789 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup st7789_commands ST7789 Display Controller Commands
 * @brief ST7789 Display Controller Command List
 * @{
 */
#ifndef ST7789_CMD_H
#define ST7789_CMD_H


/**
 * @brief Software Reset
 */
#define ST7789_CMD_SWRESET 0x01

 /**
 * @brief Sleep Out
 */
#define ST7789_CMD_SLPOUT 0x11

 /**
 * @brief Display On
 */
#define ST7789_CMD_DISPON 0x29

 /**
 * @brief Display Off
 */
#define ST7789_CMD_DISPOFF 0x28

/**
 * @brief Column Address Set
 */
#define ST7789_CMD_CASET 0x2A

/**
 * @brief Row Address Set 
 */
#define ST7789_CMD_RASET 0x2B

/**
 * @brief Memory Write
 */
#define ST7789_CMD_RAMWR 0x2C

/**
 * @brief Interface Pixel Format.
 */
#define ST7789_CMD_COLMOD 0x3A

/**
 * @brief Display Inversion On.
 */
#define ST7789_CMD_INVON 0x21

/**
 * @brief Memory Data Access Control.
 */
#define ST7789_CMD_MADCTL 0x36

/**
 * @brief COLMOD parameter: 65K colors, 16 bits per pixel (RGB565).
 */
#define ST7789_COLMOD_16BIT 0x55

/**
 * @brief MADCTL bits: row address order, column address order and row/column exchange.
 */
#define ST7789_MADCTL_MY 0x80
#define ST7789_MADCTL_MX 0x40
#define ST7789_MADCTL_MV 0x20

/**
 * @brief Time to wait after Software Reset, in milliseconds.
 */
#define ST7789_DELAY_SWRESET_MS 120

/**
 * @brief Time to wait after Sleep Out, in milliseconds.
 */
#define ST7789_DELAY_SLPOUT_MS 120
/*! @} */ // st7789
/*! @} */ // st7789
/*! @} */ // mwgroup

#endif // ST7789_CMD_H
// ------------------------------------------------------------------------- END


