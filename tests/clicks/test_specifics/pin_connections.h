/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  pin_connections.h
 * @brief This file contains default pin definitions for boards without
 *        defined USB_UART and MIKROBUS pins.
 *        Used for click examples.
 */
// ----------------------------------------------------------------------------

#ifndef _PIN_CONNECTIONS_
#define _PIN_CONNECTIONS_

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrobus.h"

// ----------------------------------------------------------------------------
#ifndef MIKROBUS_1
    #define MIKROBUS_1 1
#endif
#ifndef MIKROBUS_2
    #define MIKROBUS_2 2
#endif
#ifndef MIKROBUS_3
    #define MIKROBUS_3 3
#endif
#ifndef MIKROBUS_4
    #define MIKROBUS_4 4
#endif
#ifndef MIKROBUS_5
    #define MIKROBUS_5 5
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// USB UART connetions, make sure
// to define them here manually
#ifndef USB_UART_RX
    #define USB_UART_RX HAL_PIN_NC
#endif
#ifndef USB_UART_TX
    #define USB_UART_TX HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// AN pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_AN
    #define MIKROBUS_1_AN HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_AN
    #define MIKROBUS_2_AN HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_AN
    #define MIKROBUS_3_AN HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_AN
    #define MIKROBUS_4_AN HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_AN
    #define MIKROBUS_5_AN HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// RST pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_RST
    #define MIKROBUS_1_RST HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_RST
    #define MIKROBUS_2_RST HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_RST
    #define MIKROBUS_3_RST HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_RST
    #define MIKROBUS_4_RST HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_RST
    #define MIKROBUS_5_RST HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// CS pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_CS
    #define MIKROBUS_1_CS HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_CS
    #define MIKROBUS_2_CS HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_CS
    #define MIKROBUS_3_CS HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_CS
    #define MIKROBUS_4_CS HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_CS
    #define MIKROBUS_5_CS HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// SCK pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_SCK
    #define MIKROBUS_1_SCK HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_SCK
    #define MIKROBUS_2_SCK HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_SCK
    #define MIKROBUS_3_SCK HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_SCK
    #define MIKROBUS_4_SCK HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_SCK
    #define MIKROBUS_5_SCK HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// MISO pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_MISO
    #define MIKROBUS_1_MISO HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_MISO
    #define MIKROBUS_2_MISO HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_MISO
    #define MIKROBUS_3_MISO HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_MISO
    #define MIKROBUS_4_MISO HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_MISO
    #define MIKROBUS_5_MISO HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// MOSI pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_MOSI
    #define MIKROBUS_1_MOSI HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_MOSI
    #define MIKROBUS_2_MOSI HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_MOSI
    #define MIKROBUS_3_MOSI HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_MOSI
    #define MIKROBUS_4_MOSI HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_MOSI
    #define MIKROBUS_5_MOSI HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// PWM pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_PWM
    #define MIKROBUS_1_PWM HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_PWM
    #define MIKROBUS_2_PWM HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_PWM
    #define MIKROBUS_3_PWM HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_PWM
    #define MIKROBUS_4_PWM HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_PWM
    #define MIKROBUS_5_PWM HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// INT pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_INT
    #define MIKROBUS_1_INT HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_INT
    #define MIKROBUS_2_INT HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_INT
    #define MIKROBUS_3_INT HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_INT
    #define MIKROBUS_4_INT HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_INT
    #define MIKROBUS_5_INT HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// RX pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_RX
    #define MIKROBUS_1_RX HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_RX
    #define MIKROBUS_2_RX HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_RX
    #define MIKROBUS_3_RX HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_RX
    #define MIKROBUS_4_RX HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_RX
    #define MIKROBUS_5_RX HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// TX pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_TX
    #define MIKROBUS_1_TX HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_TX
    #define MIKROBUS_2_TX HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_TX
    #define MIKROBUS_3_TX HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_TX
    #define MIKROBUS_4_TX HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_TX
    #define MIKROBUS_5_TX HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// SCL pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_SCL
    #define MIKROBUS_1_SCL HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_SCL
    #define MIKROBUS_2_SCL HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_SCL
    #define MIKROBUS_3_SCL HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_SCL
    #define MIKROBUS_4_SCL HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_SCL
    #define MIKROBUS_5_SCL HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// TODO
// If using a board with undefined
// SDA pin connetion, make sure
// to define it here manually
#ifndef MIKROBUS_1_SDA
    #define MIKROBUS_1_SDA HAL_PIN_NC
#endif
#ifndef MIKROBUS_2_SDA
    #define MIKROBUS_2_SDA HAL_PIN_NC
#endif
#ifndef MIKROBUS_3_SDA
    #define MIKROBUS_3_SDA HAL_PIN_NC
#endif
#ifndef MIKROBUS_4_SDA
    #define MIKROBUS_4_SDA HAL_PIN_NC
#endif
#ifndef MIKROBUS_5_SDA
    #define MIKROBUS_5_SDA HAL_PIN_NC
#endif
// ----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif  // _PIN_CONNECTIONS_

// ------------------------------------------------------------------------- END
