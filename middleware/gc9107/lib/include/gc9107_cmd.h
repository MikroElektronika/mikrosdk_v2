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
 * @file  gc9107_cmd.h
 * @brief GC9107 Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup gc9107 GC9107 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup gc9107_commands GC9107 Display Controller Commands
 * @brief GC9107 Display Controller Command List
 * @{
 */

#ifndef GC9107_CMD_H
#define GC9107_CMD_H

/**
 * @brief No operation.
 */
#define GC9107_CMD_NOP                     0x00

/**
 * @brief Software reset.
 */
#define GC9107_CMD_SWRESET                 0x01

/**
 * @brief Enter sleep mode.
 */
#define GC9107_CMD_SLPIN                   0x10

/**
 * @brief Exit sleep mode.
 */
#define GC9107_CMD_SLPOUT                  0x11

/**
 * @brief Normal display mode on.
 */
#define GC9107_CMD_NORON                   0x13

/**
 * @brief Display inversion off.
 */
#define GC9107_CMD_INVOFF                  0x20

/**
 * @brief Display inversion on.
 */
#define GC9107_CMD_INVON                   0x21

/**
 * @brief Display off.
 */
#define GC9107_CMD_DISPOFF                 0x28

/**
 * @brief Display on.
 */
#define GC9107_CMD_DISPON                  0x29

/**
 * @brief Column address set.
 */
#define GC9107_CMD_CASET                   0x2A

/**
 * @brief Row address set.
 */
#define GC9107_CMD_RASET                   0x2B

/**
 * @brief Memory write.
 */
#define GC9107_CMD_RAMWR                   0x2C

/**
 * @brief Memory data access control.
 */
#define GC9107_CMD_MADCTL                  0x36

/**
 * @brief Interface pixel format.
 */
#define GC9107_CMD_COLMOD                  0x3A

/**
 * @brief Frame rate control.
 */
#define GC9107_CMD_FRS                     0xA8

/**
 * @brief Internal command AB.
 */
#define GC9107_CMD_AB                      0xAB

/**
 * @brief RGB565 color processing.
 */
#define GC9107_CMD_CPRRGB565               0xAC

/**
 * @brief Internal command B0.
 */
#define GC9107_CMD_B0                      0xB0

/**
 * @brief Internal command B1.
 */
#define GC9107_CMD_B1                      0xB1

/**
 * @brief Internal command B2.
 */
#define GC9107_CMD_B2                      0xB2

/**
 * @brief Internal command B3.
 */
#define GC9107_CMD_B3                      0xB3

/**
 * @brief Display inversion control.
 */
#define GC9107_CMD_INVCTRL                 0xB4

/**
 * @brief Internal command B6.
 */
#define GC9107_CMD_B6                      0xB6

/**
 * @brief Internal command B7.
 */
#define GC9107_CMD_B7                      0xB7

/**
 * @brief Internal command B8.
 */
#define GC9107_CMD_B8                      0xB8

/**
 * @brief Internal command C6.
 */
#define GC9107_CMD_C6                      0xC6

/**
 * @brief Internal command C7.
 */
#define GC9107_CMD_C7                      0xC7

/**
 * @brief Voltage regulator control.
 */
#define GC9107_CMD_VREGCTL                 0xE7

/**
 * @brief VGH voltage set.
 */
#define GC9107_CMD_VGHSET                  0xE8

/**
 * @brief VGL voltage set.
 */
#define GC9107_CMD_VGLSET                  0xE9

/**
 * @brief VGH and VGL clock control.
 */
#define GC9107_CMD_VGHVGLCLK               0xEA

/**
 * @brief Inner register enable 2.
 */
#define GC9107_CMD_IREGEN2                 0xEF

/**
 * @brief Gamma set 0.
 */
#define GC9107_CMD_SETGAMMA0               0xF0

/**
 * @brief Gamma set 1.
 */
#define GC9107_CMD_SETGAMMA1               0xF1

/**
 * @brief Inner register enable 1.
 */
#define GC9107_CMD_IREGEN1                 0xFE

/**
 * @brief MADCTL default (no mirroring, no rotation).
 */
#define GC9107_MADCTL_DEFAULT              0x00

/**
 * @brief MADCTL row address order (mirror Y).
 */
#define GC9107_MADCTL_MY                   0x80

/**
 * @brief MADCTL column address order (mirror X).
 */
#define GC9107_MADCTL_MX                   0x40

/**
 * @brief MADCTL row/column exchange (swap X and Y).
 */
#define GC9107_MADCTL_MV                   0x20

/**
 * @brief COLMOD 16 bit per pixel (RGB565).
 */
#define GC9107_COLMOD_16BIT                0x05

/*! @} */ // gc9107_commands
/*! @} */ // gc9107
/*! @} */ // mwgroup

#endif // GC9107_CMD_H
// ------------------------------------------------------------------------- END