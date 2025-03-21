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
 * @file hd44780_lcd_controller.c
 * @brief LCD(Liquid Crystal Display) HD44780 Controller Driver.
 */

#include "lcd.h"
#include "assembly.h"
#include "delays.h"

/**
 * @brief: Macro used for timeout between pulses.
 * @note: If needed.
 */
#define timeout(_x) while(_x--) assembly(NOP);

/**
 * @brief Generates pulse on command lines.
 * @details This function generates a high-to-low transition on the
 * LCD `reset` line and a toggle (high-low-high) on the `enable` (CS) line.
 * @param[in] rst LCD reset pin.
 * See #digital_out_t structure definition for detailed explanation.
 * @param[in] cs LCD "chip select" (enable) pin.
 * See #digital_out_t structure definition for detailed explanation.
 *
 * @return Nothing.
 */
static inline void lcd_pulse( digital_out_t rst, digital_out_t cs );

/* ------------------------------------------- PUBLIC INTERFACE FUNCTION IMPLEMENTATION -----------------------------------------------------*/
void hd44780_lcd_init( uint32_t lcd_handle ) {
    lcd_handle_t lcd_handle_local;
    memcpy(&lcd_handle_local, (void *)lcd_handle, sizeof(lcd_handle_t));

    if ( LCD_MODE_BIT_4 == lcd_handle_local.config.mode ) {
        // 4-bit mode.
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET | LCD_CMD_MODE_4BIT, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 5 );
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET | LCD_CMD_MODE_4BIT, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 5 );
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET | LCD_CMD_MODE_4BIT, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 1 );
    } else {
        // 8-bit mode - default state.
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 5 );
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 5 );
        lcd_write( lcd_handle_local, LCD_CMD_FUNCTION_SET, LCD_SELECT_CMD );
        lcd_pulse( lcd_handle_local.rst_pin, lcd_handle_local.cs_pin );
        Delay_ms( 1 );
    }

    // Standard LCD initialization.
    lcd_write( lcd_handle_local, LCD_CMD_CLEAR, LCD_SELECT_CMD ); // Clear LCD first.
    Delay_ms( 2 );
    lcd_write( lcd_handle_local, LCD_CMD_CURSOR_OFF, LCD_SELECT_CMD ); // Don't show cursor.
    Delay_ms( 2 );
    lcd_write( lcd_handle_local, LCD_ROW_1, LCD_SELECT_CMD ); // Set first row as active initially.
    Delay_ms( 2 );
}

// ------------------------------------------------------------------------ END

static inline void lcd_pulse( digital_out_t rst, digital_out_t cs ) {
    digital_out_low( &rst );  // Pull reset low to reset LCD
    Delay_ms( 1 );  // Wait for reset signal to settle

    digital_out_high( &cs );  // Set CS high to start pulse
    Delay_us( 1 );  // Short delay for pulse width
    digital_out_low( &cs );  // Set CS low to end pulse

    Delay_ms( 10 );  // Wait before next operation
}

// ------------------------------------------------------------------------ END
