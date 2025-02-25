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
 * @file lcd.h
 * @brief LCD(Liquid Crystal Display) Driver.
 */

#ifndef _LCD_H_
#define _LCD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "lcd_controllers.h"

/**
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup lcd LCD Driver
 * @brief Generic liquid crystal display APIs.
 * @{
 */

/*!
 * @addtogroup lcdcommands LCD Commands
 * @brief LCD commands.
 * @{
 */
#define LCD_CMD_FUNCTION_SET        ((uint8_t)0x20)
#define LCD_CMD_CLEAR               ((uint8_t)0x1)
#define LCD_CMD_RETURN_HOME         ((uint8_t)0x2)
#define LCD_CMD_CURSOR_OFF          ((uint8_t)0xC)
#define LCD_CMD_UNDERLINE_ON        ((uint8_t)0xE)
#define LCD_CMD_BLINK_CURSOR_ON     ((uint8_t)0xF)
#define LCD_CMD_MOVE_CURSOR_LEFT    ((uint8_t)0x10)
#define LCD_CMD_MOVE_CURSOR_RIGHT   ((uint8_t)0x14)
#define LCD_CMD_TURN_OFF            ((uint8_t)0x8)
#define LCD_CMD_TURN_ON             ((uint8_t)0xC)
#define LCD_CMD_SHIFT_LEFT          ((uint8_t)0x18)
#define LCD_CMD_SHIFT_RIGHT         ((uint8_t)0x1C)
#define LCD_CMD_MODE_4BIT           ((uint8_t)0x08)
/*! @} */ // lcdcommands

/*!
 * @brief Mapping default LCD control and data pins.
 * @attention This API is called by default in LCD code initialization.
 */
#define LCD_MAP_PINS(lcd_cfg) LCD_MAP_PINS_4BIT(lcd_cfg)

/*!
 * @brief Mapping 4-bit LCD control and data pins.
 */
#define LCD_MAP_PINS_4BIT(lcd_cfg) \
        lcd_cfg.pin_cs = LCD_CS; \
        lcd_cfg.pin_rst = LCD_RST; \
        lcd_cfg.pin_backlight = LCD_BPWM; \
        lcd_cfg.pin_d4 = LCD_D4; \
        lcd_cfg.pin_d5 = LCD_D5; \
        lcd_cfg.pin_d6 = LCD_D6; \
        lcd_cfg.pin_d7 = LCD_D7;

/*!
 * @brief Mapping 8-bit LCD control and data pins.
 */
#define LCD_MAP_PINS_8BIT(lcd_cfg) \
        lcd_cfg.pin_cs = LCD_CS; \
        lcd_cfg.pin_rst = LCD_RST; \
        lcd_cfg.pin_backlight = LCD_BPWM; \
        lcd_cfg.pin_d0 = LCD_D0; \
        lcd_cfg.pin_d1 = LCD_D1; \
        lcd_cfg.pin_d2 = LCD_D2; \
        lcd_cfg.pin_d3 = LCD_D3; \
        lcd_cfg.pin_d4 = LCD_D4; \
        lcd_cfg.pin_d5 = LCD_D5; \
        lcd_cfg.pin_d6 = LCD_D6; \
        lcd_cfg.pin_d7 = LCD_D7;

/**
 * @details Return values.
 */
typedef enum
{
    LCD_SUCCESS = 0,            /*!< Success. */
    LCD_ERROR = (-1)            /*!< Error. */
} lcd_err_t;

/**
 * @details Selects type of data passed to LCD.
 */
typedef enum
{
    LCD_SELECT_CMD = 0,         /*!< Select command. */
    LCD_SELECT_DATA             /*!< Select data. */
} lcd_select_t;

/**
 * @details Selects LCD data mode.
 */
typedef enum
{
    LCD_MODE_BIT_4 = 0,         /*!< 4 bit data mode. */
    LCD_MODE_BIT_8              /*!< 8 bit data mode. */
} lcd_mode_t;

/**
 * @details Selects desired row on initialized LCD.
 */
typedef enum
{
    LCD_ROW_1 = 0x80,           /*!< First row. */
    LCD_ROW_2 = 0xC0,           /*!< Second row. */
    LCD_ROW_3 = 0x94,           /*!< Third row. */
    LCD_ROW_4 = 0xD4            /*!< Fourth row. */
} lcd_row_t;

/**
 * @details Main cofiguration structure.
 */
typedef struct lcd_config
{
    /**
     * @brief LCD control pins.
     */
    pin_name_t pin_cs;          /*!< CS/EN pin. */
    pin_name_t pin_rst;         /*!< RST pin. */
    pin_name_t pin_backlight;   /*!< Backlight pin. */

    /**
     * @brief LCD data pins.
     */
    pin_name_t pin_d0;          /*!< Data pin 0. */
    pin_name_t pin_d1;          /*!< Data pin 1. */
    pin_name_t pin_d2;          /*!< Data pin 2. */
    pin_name_t pin_d3;          /*!< Data pin 3. */
    pin_name_t pin_d4;          /*!< Data pin 4. */
    pin_name_t pin_d5;          /*!< Data pin 5. */
    pin_name_t pin_d6;          /*!< Data pin 6. */
    pin_name_t pin_d7;          /*!< Data pin 7. */

    /**
     * @brief LCD mode.
     * @details Can be either 4 or 8 bit.
     */
    lcd_mode_t mode;            /*!< Data mode. See @ref lcd_mode_t. */

    /**
     * @brief Time to wait before generating a pulse on CS line.
     * @details Some MCUs need a higher wait time than others.
     * @note Wait time generates defined @ref waitBetweenWrites
     * number of NOP instructions before continuing.
     */
    uint16_t waitBetweenWrites; /*!< Time between strobes. */
} lcd_config_t;

/**
 * @brief Init sequence prototype.
 * @note Expected from user to provide valid routine address.
 */
typedef void (*init_sequence_ptr)(uint32_t);

/**
 * @details Main handle for LCD operations.
 */
typedef struct lcd_handle
{
    lcd_config_t config;              /*!< Configuration structure. */

    digital_out_t cs_pin;             /*!< CS pin handle. */
    digital_out_t rst_pin;            /*!< RST pin handle. */
    digital_out_t backlight_pin;      /*!< Backlight pin handle. */
    digital_out_t data_pins[8];       /*!< DATA pin handles. */

    /**
     * @brief Controller init sequence.
     * @details Mapped based on LCD controller.
     */
    init_sequence_ptr init_sequence;  /*!< Controller/Com driver init sequence. */

    /**
     * @brief Init state.
     * @details Set when LCD has been initialized.
     */
    bool init_state;
    /*!< @b true or @b false. */
} lcd_handle_t;

/**
 * @brief Configure LCD configuration structure.
 * @details Configures LCD structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config LCD driver configuration structure.
 * See #lcd_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * PIN_CS              |       HAL_PIN_NC          |
 * PIN_RST             |       HAL_PIN_NC          |
 * PIN_BACKLIGHT       |       HAL_PIN_NC          |
 * PIN_D0              |       HAL_PIN_NC          |
 * PIN_D1              |       HAL_PIN_NC          |
 * PIN_D2              |       HAL_PIN_NC          |
 * PIN_D3              |       HAL_PIN_NC          |
 * PIN_D4              |       HAL_PIN_NC          |
 * PIN_D5              |       HAL_PIN_NC          |
 * PIN_D6              |       HAL_PIN_NC          |
 * PIN_D7              |       HAL_PIN_NC          |
 * MODE                |       LCD_MODE_BIT_4      |
 * WAITBETWEENWRITES   |       1000                |
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // LCD config structure.
 *   lcd_config_t lcd_cfg;
 *
 *   // Fill structure with default values.
 *   lcd_configure_default(&lcd_cfg);
 * @endcode
 * @note PIN_BACKLIGHT is not required.
 */
void lcd_configure_default( lcd_config_t *config );

/**
 * @brief Configures LCD handle with passed configuration structure.
 * @details Configures LCD handle to values set in passed configuration structure.
 * Additionaly will initialize all provided pins.
 * @param[in,out] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] config LCD driver configuration structure.
 * See #lcd_config_t structure definition for detailed explanation.
 *
 * @return lcd_err_t.
 * Will return error if some of the pins weren't initialized correctly.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 * @endcode
 */
lcd_err_t lcd_configure( lcd_handle_t *lcd_handle, lcd_config_t *config );

/**
 * @brief Initializes LCD.
 * @details Initializes LCD with default values.
 * @param[in] lcd_handle LCD handle.
 * @param[in] init_sequence_ptr Pointer to init sequence API.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd, hd44780_lcd_init);
 * @endcode
 * @note @ref init_sequence_ptr can be declared by user as well.
 */
void lcd_init( lcd_handle_t lcd_handle, init_sequence_ptr init_sequence );

/**
 * @brief Writes data to LCD.
 * @details Writes either commands or data to LCD lines.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] lcd_cmd_data Data or command.
 * @param[in] cmd_or_data Selector for pulse signaling.
 * See #lcd_select_t enum definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Write command to set first row as active one.
 *  lcd_write(lcd, LCD_ROW_1, LCD_SELECT_CMD);
 *
 *  // Write out character 'A'.
 *  lcd_write(lcd, 'A', LCD_SELECT_DATA);
 * @endcode
 */
void lcd_write( lcd_handle_t lcd_handle, char lcd_cmd_data, lcd_select_t cmd_or_data );

/**
 * @brief Writes text to LCD.
 * @details Writes array of characters to LCD lines one by one.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] lcd_data Data.
 * @param[in] row Selects row to write to.
 * See #lcd_row_t enum definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Write out "Some text" to LCD row 1.
 *  lcd_write_text(lcd, "Some text", LCD_ROW_1);
 * @endcode
 */
void lcd_write_text( lcd_handle_t lcd_handle, char *lcd_data, lcd_row_t row );

/**
 * @brief Shifts data currently on LCD.
 * @details Shifts the data on all rows on LCD one character at a time.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Write out "Some text" to LCD row 1.
 *  lcd_write_text(lcd, "Some text", LCD_ROW_1);
 *
 *  // Move text to the left 7 times.
 *  for(char i=0; i<8; i++) {
 *      lcd_shift_left(lcd);
 *      Delay_ms(250);
 *  }
 * @endcode
 */
void lcd_shift_right( lcd_handle_t lcd_handle );

/**
 * @brief Shifts data currently on LCD.
 * @details Shifts the data on all rows on LCD one character at a time.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Write out "Some text" to LCD row 1.
 *  lcd_write_text(lcd, "Some text", LCD_ROW_1);
 *
 *  // Move text to the right 7 times.
 *  for(char i=0; i<8; i++) {
 *      lcd_shift_right(lcd);
 *      Delay_ms(250);
 *  }
 * @endcode
 */
void lcd_shift_left( lcd_handle_t lcd_handle );

/**
 * @brief Sets current active row on LCD.
 * @details Sets active row on the LCD where data is to be output.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 * @param[in] row Desired row.
 * Takes @ref lcd_row_t values.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Write out "Some text" to LCD row 2.
 *  lcd_set_row(lcd, LCD_ROW_2);
 *  lcd_write_text(lcd, "Some text", LCD_ROW_1);
 * @endcode
 */
void lcd_set_row( lcd_handle_t lcd_handle, lcd_row_t row );

/**
 * @brief Turns LCD ON.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Turn LCD ON.
 *  lcd_turn_on(lcd);
 * @endcode
 */
void lcd_turn_on( lcd_handle_t lcd_handle );

/**
 * @brief Turns LCD OFF.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Turn LCD OFF.
 *  lcd_turn_off(lcd);
 * @endcode
 */
void lcd_turn_off( lcd_handle_t lcd_handle );

/**
 * @brief Clears LCD.
 * @details Clears all characters on LCD.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_clear(lcd);
 * @endcode
 */
void lcd_clear( lcd_handle_t lcd_handle );

/**
 * @brief Moves cursor to first position.
 * @details Moves current cursor position back to the home position.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_cursor_move_home(lcd);
 * @endcode
 */
void lcd_cursor_move_home( lcd_handle_t lcd_handle );

/**
 * @brief Moves cursor position.
 * @details Moves current cursor position one column to the left.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_cursor_move_left(lcd);
 * @endcode
 */
void lcd_cursor_move_left( lcd_handle_t lcd_handle );

/**
 * @brief Moves cursor position.
 * @details Moves current cursor position one column to the right.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_cursor_move_right(lcd);
 * @endcode
 */
void lcd_cursor_move_right( lcd_handle_t lcd_handle );

/**
 * @brief Removes cursor.
 * @details Removes cursor from current position on the display.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_cursor_off(lcd);
 * @endcode
 */
void lcd_cursor_off( lcd_handle_t lcd_handle );

/**
 * @brief Shows cursor.
 * @details Shows current cursor position on the display.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_cursor_on(lcd);
 * @endcode
 * @attention Turns cursor blinking @b ON for
 * better visibility as well.
 */
void lcd_cursor_on( lcd_handle_t lcd_handle );

/**
 * @brief Turns LCD backlight OFF.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_backlight_off(lcd);
 * @endcode
 */
void lcd_backlight_off( lcd_handle_t lcd_handle );

/**
 * @brief Turns LCD backlight ON.
 * @param[in] lcd_handle LCD handle.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD.
 *  lcd_init(lcd);
 *
 *  // Clear display.
 *  lcd_backlight_on(lcd);
 * @endcode
 */
void lcd_backlight_on( lcd_handle_t lcd_handle );

/*! @} */ // middlewaregroup
/*! @} */ // lcd

#ifdef __cplusplus
}
#endif

#endif // _LCD_H_

// ------------------------------------------------------------------------ END
