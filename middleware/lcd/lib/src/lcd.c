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
 * @file lcd.c
 * @brief LCD(Liquid Crystal Display) Driver.
 */

#include "lcd.h"
#include "board.h"
#include "assembly.h"
#include "delays.h"

/**
 * @brief: Macro used for timeout between pulses.
 */
#define timeout(_x) while(_x--) assembly(NOP);

/**
 * @brief: Variable used to store data before shifting.
 */
static uint8_t lcd_cmd_data_saved;

/* --------------------------------------------- PRIVATE FUNCTIONS - DECLARATIONS -------------------------------------------*/

/**
 * @brief API clears LCD lines.
 * @details This API writes 0 to all LCD data lines.
 * This ensures a clean initial state with no leftover
 * data on the pins.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 */
static inline void clear_lines( lcd_handle_t lcd_handle );

/**
 * @brief API generates pulse on command lines.
 * @details This API generates a low-to-high or
 * high-to-low transition on the LCD command lines
 * depending on the data type.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] cmd_or_data Data type selector.
 * See #lcd_select_t enum definition for detailed explanation.
 *
 * @return Nothing.
 */
static inline void lcd_pulse( lcd_handle_t lcd_handle, lcd_select_t cmd_or_data );

/**
 * @brief API writes data to LCD.
 * @details This API writes @ref value byte of data
 * to the LCD data lines.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] value Byte of data to be written.
 *
 * @return Nothing.
 */
static inline void lcd_write_bit_of_data( lcd_handle_t lcd_handle, uint8_t value );

/* ------------------------------------------- PUBLIC INTERFACE FUNCTION IMPLEMENTATION -----------------------------------------------------*/

void lcd_configure_default( lcd_config_t *config ) {
    if ( config ) {
        /**
         * @brief Fill structure with invalid data - @b 0xFF.
         * @note Sets all pins to invalid state.
         */
        memset(config, HAL_PIN_NC, sizeof(lcd_config_t));

        /**
         * @brief Set 4bit mode by default.
         */
        config->mode = LCD_MODE_BIT_4;

        /**
         * @brief Set 10000 by default.
         */
        config->waitBetweenWrites = 10000;
    }
}

lcd_err_t lcd_configure( lcd_handle_t *lcd_handle, lcd_config_t *config ) {
    lcd_err_t status = LCD_ERROR;
    uint8_t bit_data_err_cnt = 0;

    if ( lcd_handle ) {
        if ( config ) {
            lcd_config_t *p_config = &lcd_handle->config;
            memcpy( p_config, config, sizeof( lcd_config_t ) );

            if ( DIGITAL_OUT_SUCCESS != digital_out_init( &lcd_handle->cs_pin, lcd_handle->config.pin_cs ) )
                return status;
            else
                digital_out_low( &lcd_handle->cs_pin );

            if ( DIGITAL_OUT_SUCCESS != digital_out_init( &lcd_handle->rst_pin, lcd_handle->config.pin_rst ) )
                return status;
            else
                digital_out_low( &lcd_handle->rst_pin );

            // Backlight pin is optional.
            if ( HAL_PIN_NC != lcd_handle->config.pin_backlight ) {
                if ( DIGITAL_OUT_SUCCESS != digital_out_init( &lcd_handle->backlight_pin, lcd_handle->config.pin_backlight ) )
                    return status;
                else
                    digital_out_high( &lcd_handle->backlight_pin );
            }

            pin_name_t *data_pin_iteration = &lcd_handle->config.pin_d0;
            for ( uint8_t i = 0; i < 8; i++ ) {
                if ( DIGITAL_OUT_SUCCESS != digital_out_init( &lcd_handle->data_pins[i], *data_pin_iteration ) )
                    bit_data_err_cnt++;
                data_pin_iteration++;
            }

            /**
             * SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
             * according to datasheet, we need at least 40 ms after power rises above 2.7 V
             * before sending commands.
             */
            Delay_ms( 50 );

            if ( ( LCD_MODE_BIT_4 == lcd_handle->config.mode ) && ( 4 == bit_data_err_cnt ) )
                status = LCD_SUCCESS;

            if ( ( LCD_MODE_BIT_8 == lcd_handle->config.mode ) && ( 0 == bit_data_err_cnt ) )
                status = LCD_SUCCESS;

            if ( LCD_SUCCESS == status )
                lcd_handle->init_state = true;
        }
    }

    return status;
}

void lcd_init( lcd_handle_t lcd_handle, init_sequence_ptr init_sequence ) {
    if ( true == lcd_handle.init_state ) {
        clear_lines( lcd_handle );
        timeout( lcd_handle.config.waitBetweenWrites );
        if (init_sequence) {
            (*init_sequence)((uint32_t)&lcd_handle);
        }
    }
}

void lcd_write( lcd_handle_t lcd_handle, char lcd_cmd_data, lcd_select_t cmd_or_data ) {
    lcd_cmd_data_saved = lcd_cmd_data;
    if ( false == lcd_handle.init_state ) {
        return;
    }

    if ( LCD_MODE_BIT_4 == lcd_handle.config.mode ) {
        // 4-bit mode.
        // First send higher nibble.
        lcd_write_bit_of_data( lcd_handle, lcd_cmd_data >> 4 );
        lcd_pulse( lcd_handle, cmd_or_data );
    }

    // 8-bit mode or lower nibble for 4-bit mode.
    lcd_write_bit_of_data( lcd_handle, lcd_cmd_data_saved );
    lcd_pulse( lcd_handle, cmd_or_data );
}

void lcd_write_text( lcd_handle_t lcd_handle, char *lcd_data, lcd_row_t row ) {
    uint8_t i = 0;

    if ( false == lcd_handle.init_state ) {
        return;
    }

    // Set row first.
    lcd_write( lcd_handle, row, LCD_SELECT_CMD );
    // Then proceed to write all bytes of data one by one.
    while ( lcd_data[i] ) {
        lcd_write( lcd_handle, lcd_data[i++], LCD_SELECT_DATA );
    }
}

void lcd_shift_right( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_SHIFT_RIGHT, LCD_SELECT_CMD );
}

void lcd_shift_left( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_SHIFT_LEFT, LCD_SELECT_CMD );
}

void lcd_turn_on( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_TURN_ON, LCD_SELECT_CMD );
}

void lcd_turn_off( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_TURN_OFF, LCD_SELECT_CMD );
}

void lcd_clear( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_CLEAR, LCD_SELECT_CMD );
}

void lcd_set_row( lcd_handle_t lcd_handle, lcd_row_t row ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, row, LCD_SELECT_CMD );
}

void lcd_cursor_move_left( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_MOVE_CURSOR_LEFT, LCD_SELECT_CMD );
}

void lcd_cursor_move_right( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_MOVE_CURSOR_RIGHT, LCD_SELECT_CMD );
}

void lcd_cursor_off( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_CURSOR_OFF, LCD_SELECT_CMD );
}

void lcd_cursor_on( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_BLINK_CURSOR_ON, LCD_SELECT_CMD );
}

void lcd_cursor_move_home( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    lcd_write( lcd_handle, LCD_CMD_RETURN_HOME, LCD_SELECT_CMD );
}

void lcd_backlight_off( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    digital_out_low( &lcd_handle.backlight_pin );
}

void lcd_backlight_on( lcd_handle_t lcd_handle ) {
    if ( false == lcd_handle.init_state ) {
        return;
    }

    digital_out_high( &lcd_handle.backlight_pin );
}

/* --------------------------------------------- PRIVATE FUNCTIONS - IMPLEMENTATIONS ----------------------------------------*/

static inline void lcd_pulse( lcd_handle_t lcd_handle, lcd_select_t cmd_or_data ) {
    // Send LOW or HIGH pulse on RS/RST pin for selecting adequate register.
    if ( LCD_SELECT_CMD == cmd_or_data ) {
        digital_out_low( &lcd_handle.rst_pin );
    } else {
        digital_out_high( &lcd_handle.rst_pin );
    }

    // Generate a High-to-low pulse on EN/CS pin.
    Delay_ms( 1 );
    digital_out_high( &lcd_handle.cs_pin );
    Delay_us( 1 );
    digital_out_low( &lcd_handle.cs_pin );
    Delay_ms( 10 );
}

static inline void clear_lines( lcd_handle_t lcd_handle ) {
    // Write 0 to all data lines.
    lcd_write_bit_of_data( lcd_handle, 0x00 );
    Delay_ms( 2 );
}

static inline void lcd_write_bit_of_data( lcd_handle_t lcd_handle, uint8_t value ) {
    uint8_t cnt = 0;
    pin_name_t *data_pin_iteration = &lcd_handle.config.pin_d0;

    for ( uint8_t i = 0; i < 8; i++ ) {
        if ( HAL_PIN_NC != *data_pin_iteration ) {
            digital_out_write( &lcd_handle.data_pins[i], ( ( value >> cnt ) & 0x01 ) );
            cnt++;
        }
        data_pin_iteration++;
    }
}

// ------------------------------------------------------------------------ END
