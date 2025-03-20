#if 1
// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "cstdio.h"
#include "board.h"
#include "lcd.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

// ------------------------------------------ PRIVATE FUNCTIONS - DECLARATIONS
/**
 * @brief First test.
 * @details Fills out config structure,
 * Initializes handle and connections to LCD.
 * Initializes LCD to default 4-bit setting.
 * @return @ref lcd_err_t.
 */
static lcd_err_t test_1();

/**
 * @brief Writes out a set of characters.
 * @details Tests @ref lcd_write API.
 * @return Nothing.
 */
static void test_2(void);

/**
 * @brief Clears LCD the writes text.
 * @details Tests @ref lcd_clear and @ref lcd_write_text API.
 * @return Nothing.
 */
static void test_3(void);

/**
 * @brief Sets row 2 as active and writes out text.
 * @details Tests @ref lcd_set_row and @ref lcd_write with variables as parameters.
 * @return Nothing.
 */
static void test_4(void);

/**
 * @brief Shifts data to the left.
 * @details Tests @ref lcd_shift_left API.
 * @return Nothing.
 */
static void test_5(void);

/**
 * @brief Shifts data to the right.
 * @details Tests @ref lcd_shift_right API.
 * @return Nothing.
 */
static void test_6(void);

/**
 * @brief Turns LCD ON and OFF.
 * @details Tests @ref lcd_turn_on and @ref lcd_turn_off API.
 * @return Nothing.
 */
static void test_7(void);

/**
 * @brief Turns cursor ON and OFF.
 * @details Tests @ref lcd_cursor_on and @ref lcd_cursor_off API.
 * @return Nothing.
 */
static void test_8(void);

/**
 * @brief Shifts cursor to the left, moves it home and then to the right.
 * @details Tests @ref lcd_cursor_move_left, @ref lcd_cursor_move_right and
 * @ref lcd_cursor_move_home API.
 * @return Nothing.
 */
static void test_9(void);

/**
 * @brief Turns LCD backlight ON and OFF.
 * @details Tests @ref lcd_backlight_off, @ref lcd_backlight_on and API.
 * @return Nothing.
 */
static void test_10(void);

// ----------------------------------------------------------------- VARIABLES

static lcd_handle_t lcd;
static lcd_config_t lcd_cfg;

// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Expected output is for display to be turned ON.
    if (LCD_ERROR == test_1()) {
        printf_me("LCD failed initialization!\r\n");
        while(1);
    }

    while(1) {
        // Expected output is the following text in row 1:
        // CHAR:123+-/*@&
        test_2();

        // Expected output is the following text in row 1:
        // Clear and write!
        test_3();

        // Expected output is the following text in row 1:
        // Clear and write!
        // And following output in row 2:
        // MikroE LCD Test
        test_4();

        // Expected output is text being shifted to the left.
        test_5();

        // Expected output is text being shifted to the right.
        test_6();

        // Expected output is text disappearing and reappearing a couple of times.
        test_7();

        // Expected output is cursor disappearing and reappearing a couple of times
        // at the last position. Next to last character in row 2.
        test_8();

        // Expected output is cursor moving to the left 3 times,
        // then moving to first position and finally moving
        // 3 times to the right.
        test_9();

        // Expected output is the LCD blinking.
        test_10();

        // Signal END on LCD.
        lcd_clear(lcd);
        lcd_cursor_off(lcd);
        lcd_write_text(lcd, "TEST COMPLETED!!", LCD_ROW_1);
    }

    return 0;
}

static lcd_err_t test_1() {
    lcd_configure_default(&lcd_cfg);
    LCD_MAP_PINS(lcd_cfg);

    // Increase wait between data transmission to 65K NOPs.
    lcd_cfg.waitBetweenWrites = 0xFFFF;

    if (LCD_ERROR == lcd_configure(&lcd, &lcd_cfg))
        return LCD_ERROR;

    /**
     * @brief Map controller initialization sequence.
     */
    lcd_init(lcd, hd44780_lcd_init);

    return LCD_SUCCESS;
}

static void test_2(void) {
    lcd_write(lcd, 'C', LCD_SELECT_DATA);
    lcd_write(lcd, 'H', LCD_SELECT_DATA);
    lcd_write(lcd, 'A', LCD_SELECT_DATA);
    lcd_write(lcd, 'R', LCD_SELECT_DATA);
    lcd_write(lcd, ':', LCD_SELECT_DATA);
    lcd_write(lcd, '1', LCD_SELECT_DATA);
    lcd_write(lcd, '2', LCD_SELECT_DATA);
    lcd_write(lcd, '3', LCD_SELECT_DATA);
    lcd_write(lcd, '+', LCD_SELECT_DATA);
    lcd_write(lcd, '-', LCD_SELECT_DATA);
    lcd_write(lcd, '/', LCD_SELECT_DATA);
    lcd_write(lcd, '*', LCD_SELECT_DATA);
    lcd_write(lcd, '@', LCD_SELECT_DATA);
    lcd_write(lcd, '&', LCD_SELECT_DATA);
}

static void test_3(void) {
    Delay_ms(1000);
    lcd_clear(lcd);
    lcd_write_text(lcd, "Clear and write!", LCD_ROW_1);
    Delay_ms(1000);
}

static void test_4(void) {
    char i,testArray[]={"MikroE LCD Test"};

    lcd_set_row(lcd, LCD_ROW_2);
    for(i=0;testArray[i]!=0;i++)
    {
        lcd_write(lcd, testArray[i], LCD_SELECT_DATA);
    }
}

static void test_5(void) {
    uint8_t i = 0;

    for(i=0; i<8; i++) {
        lcd_shift_left(lcd);
        Delay_ms(250);
    }
}

static void test_6(void) {
    uint8_t i = 0;

    for (i=0; i<8; i++) {
        lcd_shift_right(lcd);
        Delay_ms(250);
    }
}

static void test_7(void) {
    lcd_turn_off(lcd);
    Delay_ms(500);
    lcd_turn_on(lcd);
    Delay_ms(500);
    lcd_turn_off(lcd);
    Delay_ms(500);
    lcd_turn_on(lcd);
    Delay_ms(500);
}

static void test_8(void) {
    lcd_cursor_off(lcd);
    Delay_ms(1000);
    lcd_cursor_on(lcd);
    Delay_ms(1000);
    lcd_cursor_off(lcd);
    Delay_ms(1000);
    lcd_cursor_on(lcd);
    Delay_ms(1000);
}

static void test_9(void) {
    lcd_cursor_move_left(lcd);
    Delay_ms(500);
    lcd_cursor_move_left(lcd);
    Delay_ms(500);
    lcd_cursor_move_left(lcd);
    Delay_ms(500);
    lcd_cursor_move_home(lcd);
    Delay_ms(500);
    lcd_cursor_move_right(lcd);
    Delay_ms(500);
    lcd_cursor_move_right(lcd);
    Delay_ms(500);
    lcd_cursor_move_right(lcd);
    Delay_ms(500);
}

static void test_10(void) {
    for(int8_t cnt = 0; cnt < 10; cnt++) {
        lcd_backlight_off(lcd);
        Delay_ms(200);
        lcd_backlight_on(lcd);
        Delay_ms(200);
    }
}

// ----------------------------------------------------------------------- END
#else
/****************************************************************************
** Copyright (C) 2024 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package.
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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
/* Project name:
 *  LCD demo
 * Copyright:
 *  (c) Mikroelektronika, 2024.
 * Description:
 *  Example is meant for demonstrating LCD functionality using mikroSDK 2.0.
 *  If you're using one of the MIKROE v8 boards, Put LCD display into LCD socket.
 */

/**
 * @brief For a detailed explanation of this demo, please visit:
 * <https://github.com/MikroElektronika/necto_demos/blob/main/demos/sdk/demolcd/project/README.md>
 */

// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "board.h"
#include "lcd.h"
#include "drv_digital_out.h"
// #include "mikrosdk_version.h"

// // ----------------------------------------------------------------- MACROS
// #if mikroSDK_GET_VERSION < 21000ul
//     #error "SDK version must be 2.10.0 or higher."
// #endif

#define DELAY_LCD 300

// ----------------------------------------------------------------- VARIABLES
static lcd_config_t lcd_cfg; // LCD config structure.
static lcd_handle_t lcd;     // LCD handle.

static char txt1[] = "LCD_demo";
static char txt2[] = "mikroElektronika";

static char i;

// ----------------------------------------------------------------- USER CODE
void lcd_demo_init(void) {
    // Default configuration.
    lcd_configure_default(&lcd_cfg);

    // Mapping LCD pins.
    LCD_MAP_PINS(lcd_cfg);

    // Initialize handle and pins.
    lcd_configure(&lcd, &lcd_cfg);

    // Initialize LCD.
    lcd_init(lcd, hd44780_lcd_init);

    // LCD turning on.
    lcd_turn_on(lcd);
    Delay_ms(DELAY_LCD);

    // Backlight turning on.
    lcd_backlight_on(lcd);
    Delay_ms(DELAY_LCD);

    // Clearing LCD.
    lcd_clear(lcd);
    Delay_ms(DELAY_LCD);

    // LCD cursor off.
    lcd_cursor_off(lcd);
    Delay_ms(DELAY_LCD);
}

int main(void) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    lcd_demo_init();

    // Clearing LCD.
    lcd_clear(lcd);
    Delay_ms(DELAY_LCD);

    // Setting first row.
    lcd_set_row(lcd, LCD_ROW_1);
    Delay_ms(DELAY_LCD);

    // Writing text in first row.
    lcd_write_text(lcd, txt1, LCD_ROW_1);
    Delay_ms(DELAY_LCD);

    // Setting second row.
    lcd_set_row(lcd, LCD_ROW_2);
    Delay_ms(DELAY_LCD);

    // Writing text in second row.
    lcd_write_text(lcd, txt2, LCD_ROW_2);
    Delay_ms(DELAY_LCD);

    // uint8_t a = 2;
    while(1) {
        // if(a--)
            // lcd_clear(lcd);
        // Shifting characters left 5 times.
        for(i=0; i<5; i++) {
            lcd_shift_left(lcd);
            Delay_ms(DELAY_LCD);
        }

        // Shifting characters right 5 times.
        for(i=0; i<5; i++) {
            lcd_shift_right(lcd);
            Delay_ms(DELAY_LCD);
        }
    }

  return 0;
}
// ----------------------------------------------------------------------- END
#endif