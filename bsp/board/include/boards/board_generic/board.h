/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  board.h
 * @brief Main board pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (1)

#define BOARD_NAME "Generic Board"

/// Mapping
#define TFT_RST HAL_PIN_NC // Define this pin.
#define TFT_CS HAL_PIN_NC // Define this pin.
#define TFT_D_C HAL_PIN_NC // Define this pin.
#define TFT_RD HAL_PIN_NC // Define this pin.
#define TFT_WR HAL_PIN_NC // Define this pin.
#define TFT_TE HAL_PIN_NC // Define this pin.
#define TFT_GPIO HAL_PIN_NC // Define this pin.
#define TFT_BPWM HAL_PIN_NC // Define this pin.
#define TFT_D0 HAL_PIN_NC // Define this pin.
#define TFT_D1 HAL_PIN_NC // Define this pin.
#define TFT_D2 HAL_PIN_NC // Define this pin.
#define TFT_D3 HAL_PIN_NC // Define this pin.
#define TFT_D4 HAL_PIN_NC // Define this pin.
#define TFT_D5 HAL_PIN_NC // Define this pin.
#define TFT_D6 HAL_PIN_NC // Define this pin.
#define TFT_D7 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D7 PE7").
#define TFT_D8 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D8 PE8").
#define TFT_D9 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D9 PE9").
#define TFT_D10 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D10 PE10").
#define TFT_D11 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D11 PE11").
#define TFT_D12 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D12 PE12").
#define TFT_D13 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D13 PE13").
#define TFT_D14 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D14 PE14").
#define TFT_D15 HAL_PIN_NC // If TFT data lines are 8-bits wide do not remove "HAL_PIN_NC" definition, else define this pin (e.g., "#define TFT_D15 PE15").

#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC // Define this port (e.g., "#define TFT_8BIT_DATA_PORT_CH0 PORT_E").
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x0000 // Define mask for this port (e.g., "#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF").

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC // If TFT data lines are 8-bits wide, define "HAL_PORT_NC" (e.g., "#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC"), else define this port.
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000 // If TFT data lines are 8-bits wide, define "0x0000" (e.g., "#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000"), else define mask for this port.

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC // If TFT data lines are 8-bits wide, define "HAL_PORT_NC" (e.g., "#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC"), else define this port.
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000 // If TFT data lines are 8-bits wide, define "0x0000" (e.g., "#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000"), else define mask for this port.

#define CTP_SDA HAL_PIN_NC // If TFT device does not have capacitive touch capabilities, do not remove "HAL_PORT_NC" definition, else define this pin.
#define CTP_SCL HAL_PIN_NC // If TFT device does not have capacitive touch capabilities, do not remove "HAL_PORT_NC" definition, else define this pin.
#define CTP_INT HAL_PIN_NC // If TFT device does not have capacitive touch capabilities, do not remove "HAL_PORT_NC" definition, else define this pin.
#define CTP_WAKE HAL_PIN_NC // If TFT device does not have capacitive touch capabilities, do not remove "HAL_PORT_NC" definition, else define this pin.
#define CTP_RST HAL_PIN_NC // If TFT device does not have capacitive touch capabilities, do not remove "HAL_PORT_NC" definition, else define this pin.

#define USB_UART_TX HAL_PIN_NC // Define this pin if using logger.
#define USB_UART_RX HAL_PIN_NC // Define this pin if using logger.

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
