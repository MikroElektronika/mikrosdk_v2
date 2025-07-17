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
 * @file glcd.h
 * @brief GLCD (Graphic Liquid Crystal Display) Driver.
 */


#include <stdbool.h>
#include <stdint.h>

#include "drv_port.h"
#include "drv_digital_out.h"

typedef enum {
    ON = 0x3F, on = 0x3F, On = 0x3F, oN = 0x3F, 
    
    OFF = 0x3E, Off = 0x3E, oFf = 0x3E, ofF = 0x3E,
    OFf = 0x3E, oFF = 0x3E, OfF = 0x3E, off = 0x3E,
} display_cfg_t;

typedef enum { VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL } line_dir_t;
typedef enum { CENTER_DIMENSIONS, CORNER_DIMENSIONS, THREE_POINTS } rect_mode_t;
typedef enum { FAST_MODE = 15, DEFAULT_MODE = 100, PRECISION_MODE = 3000 } circle_mode_t;


#define IS_ON( x )              ( (x == ON) || (x == oN) || (x == on) || (x == oN) )
#define IS_OFF( x )             ( (x == OFF) || (x == Off) || (x == oFf) || (x == ofF) || (x == OFf) || (x == oFF) || (x == ofF) || (x == off) )

#define PI                      3.14159265359
#define CS_SIZE                 2
#define PAGE_SIZE               8
#define COL_PER_CHIP            64
#define ROW_SIZE                ( CS_SIZE * COL_PER_CHIP )

/* Pins defintion for GLCD usage */
#define E_PIN                   PE15
#define RW_PIN                  PE13
#define RS_PIN                  PE12
#define CS2_PIN                 PE11
#define CS1_PIN                 PE10
#define RESET_PIN               PE8

/* GLCD Structure context/config creation and basic geometry (point, segment, rect, ...) structure*/

/**
 * @name point
 * @brief A structure representing a 2D point on the GLCD screen.
 * 
 * @param x : ( uint8_t ) X-coordinate (0–127)
 * @param y : ( uint8_t ) Y-coordinate (0–63)
 */
typedef struct point { uint8_t x; uint8_t y; } point;

/**
 * @name segment
 * @brief A structure representing a segment (line) defined by two points and a line thickness.
 * 
 * @param pts       : ( point[2] ) Two endpoints of the segment
 * @param line_size : ( uint8_t ) Thickness of the segment
 */
typedef struct segment { point pts[2]; uint8_t line_size; } segment;

/**
 * @name rect
 * @brief A rectangle structure that defines dimensions, border thickness, and style.
 * 
 * @param w         : ( uint8_t ) Width of the rectangle (0-127)
 * @param h         : ( uint8_t ) Height of the rectangle (0-63)
 * @param line_size : ( uint8_t ) Thickness of the rectangle border (0-63)
 * @param filled    : ( bool ) If true, the rectangle will be filled
 * @param rounded   : ( bool ) If true, rounded corners will be drawn (not yet implemented)
 * 
 * @note The user must define this structure manually before passing it to drawing functions.
 */
typedef struct rect { uint8_t w; uint8_t h; uint8_t line_size; bool filled; bool rounded; } rect;

/**
 * @name circle
 * @brief A circle structure that encapsulates the essential parameters required for rendering.
 * 
 * @param o         : ( point ) Origin (center) of the circle
 * @param r         : ( uint8_t ) Radius of the circle
 * @param line_size : ( uint8_t ) Line thickness
 * @param filled    : ( bool ) If true, fills the circle
 * 
 * @note The user needs to define this structure before using it in the GLCD_Draw_Circle function.
 */
typedef struct circle { point o; uint8_t r; uint8_t line_size; bool filled; } circle;

/**
 * @name ellipse
 * @brief A structure representing an ellipse defined by its foci, semi-major axis, and style options.
 * 
 * @param mid_foci   : ( point[2] ) Two focal points of the ellipse
 * @param a          : ( float ) Semi-major axis length
 * @param line_size  : ( uint8_t ) Thickness of the ellipse's contour
 * @param filled     : ( bool ) If true, the ellipse will be filled
 * 
 * @note The two focal points must be distinct but a is calculated regarless (the user dont need
 * to bother about this parameter).
 */
typedef struct ellipse { point mid_foci[2]; float a; uint8_t line_size; bool filled; } ellipse;

/**
 * @name CHAR
 * @brief A character font structure that maps an ASCII character to its 8x8 bitmap.
 * 
 * @param c            : ( char ) The character symbol
 * @param bitmap_code  : ( uint64_t ) 8x8 bitmap representation of the character (column-wise)
 * 
 * @note Used internally by GLCD_Write_Char and GLCD_Write_Text functions.
 */
typedef struct CHAR { char c; uint64_t bitmap_code; } CHAR;

/**
 * @brief Main GLCD structure for managing configuration, GPIO control and framebuffer buffer.
 * 
 * @param data_out : ( port_t ) Port used for data output to the GLCD (1 byte)
 * @param cs1d     : ( digital_out_t ) Chip select 1 control
 * @param cs2d     : ( digital_out_t ) Chip select 2 control
 * @param ed       : ( digital_out_t ) Enable signal
 * @param resetd   : ( digital_out_t ) Reset signal
 * @param rsd      : ( digital_out_t ) Register select (data/instruction)
 * @param rwd      : ( digital_out_t ) Read/write control signal
 * @param buffer   : ( uint8_t[][][] ) Frame buffer: 2 chips × 8 pages × 64 columns
 * 
 * @note The user must initialize this structure using GLCD_Init() before use.
 */
typedef struct glcd {
    port_t data_out;
    digital_out_t cs1d; 
    digital_out_t cs2d;
    digital_out_t ed;
    digital_out_t resetd; 
    digital_out_t rsd; 
    digital_out_t rwd;
    uint8_t buffer[CS_SIZE][PAGE_SIZE][COL_PER_CHIP];
} glcd_t;

const CHAR font[] = {
    { ' ',  0x0000 },     // 0
    { '!',  0x0808080800080000 },     // 1
    { '"',  0x2828000000000000 },     // 2
    { '#',  0x287C287C28000000 },     // 3
    { '$',  0x081E281C0A3C0800 },     // 4
    { '%',  0x6094681629060000 },     // 5
    { '&',  0x1C20201926190000 },     // 6
    { '\'', 0x0808000000000000 },     // 7
    { '(',  0x0810202010080000 },     // 8
    { ')',  0x1008040408100000 },     // 9
    { '*',  0x2A1C3E1C2A000000 },     // 10
    { '+',  0x08083E0808000000 },     // 11
    { ',',  0x0000000000810000 },     // 12
    { '-',  0x003C000000000000 },     // 13
    { '.',  0x0000000000800000 },     // 14
    { '/',  0x2040810204000000 },     // 15
    { '0',  0x1824424224180000 },     // 16
    { '1',  0x08180808081C0000 },     // 17
    { '2',  0x3C420418207E0000 },     // 18
    { '3',  0x3C420418423C0000 },     // 19
    { '4',  0x081828487C080000 },     // 20
    { '5',  0x7E407C02423C0000 },     // 21
    { '6',  0x3C407C42423C0000 },     // 22
    { '7',  0x7E04081020400000 },     // 23
    { '8',  0x3C423C42423C0000 },     // 24
    { '9',  0x3C42423E023C0000 },     // 25
    { ':',  0x0000000800008000 },     // 26
    { ';',  0x0000000800010000 },     // 27
    { '<',  0x0618601806000000 },     // 28
    { '=',  0x007E00007E000000 },     // 29
    { '>',  0x6018061860000000 },     // 30
    { '?',  0x3844041800100000 },     // 31
    { '@',  0x3C449C945C201C00 },     // 32
    { 'A',  0x1818243C42420000 },     // 33
    { 'B',  0x7844784444780000 },     // 34
    { 'C',  0x3844808044380000 },     // 35
    { 'D',  0x7844444444780000 },     // 36
    { 'E',  0x7C407840407C0000 },     // 37
    { 'F',  0x7C40784040400000 },     // 38
    { 'G',  0x3844809C44380000 },     // 39
    { 'H',  0x42427E4242420000 },     // 40
    { 'I',  0x3E080808083E0000 },     // 41
    { 'J',  0x1C04040444380000 },     // 42
    { 'K',  0x4448507048440000 },     // 43
    { 'L',  0x40404040407E0000 },     // 44
    { 'M',  0x4163554941410000 },     // 45
    { 'N',  0x4262524A46420000 },     // 46
    { 'O',  0x1C222222221C0000 },     // 47
    { 'P',  0x7844784040400000 },     // 48
    { 'Q',  0x1C222222221C0200 },     // 49
    { 'R',  0x7844785048440000 },     // 50
    { 'S',  0x1C22100C221C0000 },     // 51
    { 'T',  0x7F08080808080000 },     // 52
    { 'U',  0x42424242423C0000 },     // 53
    { 'V',  0x8142422424180000 },     // 54
    { 'W',  0x4141495563410000 },     // 55
    { 'X',  0x4224181824420000 },     // 56
    { 'Y',  0x4122140808080000 },     // 57
    { 'Z',  0x7E040810207E0000 },     // 58
    { '[',  0x3820202020380000 },     // 59
    { '\\', 0x4020100804020000 },     // 60
    { ']',  0x3808080808380000 },     // 61
    { '^',  0x1028000000000000 },     // 62
    { '_',  0x00000000007E0000 },     // 63
    { '`',  0x1008000000000000 },     // 64
    { 'a',  0x003C023E463A0000 },     // 65
    { 'b',  0x40407C42625C0000 },     // 66
    { 'c',  0x001C20201C000000 },     // 67
    { 'd',  0x0008080838483800 },     // 68
    { 'e',  0x003C427E403C0000 },     // 69
    { 'f',  0x0018103810100000 },     // 70
    { 'g',  0x00344C4434043800 },     // 71
    { 'h',  0x2020382424240000 },     // 72
    { 'i',  0x0008001808080800 },     // 73
    { 'j',  0x0008001808283800 },     // 74
    { 'k',  0x20202428302C0000 },     // 75
    { 'l',  0x1010101010180000 },     // 76
    { 'm',  0x00665A4242000000 },     // 77
    { 'n',  0x002E322222000000 },     // 78
    { 'o',  0x003C42423C000000 },     // 79
    { 'p',  0x005C62427C404000 },     // 80
    { 'q',  0x003A46423E020200 },     // 81
    { 'r',  0x002C322020000000 },     // 82
    { 's',  0x001C201804380000 },     // 83
    { 't',  0x00103C1010180000 },     // 84
    { 'u',  0x002222261A000000 },     // 85
    { 'v',  0x0042422418000000 },     // 86
    { 'w',  0x0081815A66000000 },     // 87
    { 'x',  0x0042241866000000 },     // 88
    { 'y',  0x0042211408106000 },     // 89
    { 'z',  0x003C08103C000000 },     // 90
    { '{',  0x1C103030101C0000 },     // 91
    { '|',  0x0808080808080800 },     // 92
    { '}',  0x38080C0C08380000 },     // 93
    { '~',  0x0000324C00000000 },     // 94
};

/* -------------------------------------------------- Initialize functions -------------------------------------------------- */
/**
 * @name GLCD_Port_Init
 * @brief Initializes the GLCD port and control pins.
 *
 * @details This function sets up the data output port and initializes all required
 * digital output pins for controlling the GLCD, including chip select,
 * enable, reset, register select, and read/write pins.
 *
 * @param ( glcd_t* ) Pointer to the GLCD structure containing pin configurations.
 * @return Nothing
 * 
 * @note This function is called automatically by GLCD_Init() to prepare the GLCD for operation.
 * It should not be called directly unless you need to reinitialize the port.
 */
void GLCD_Port_Init                         ( glcd_t* glcd );

/**
 * @name GLCD_Init
 * @brief Initializes the GLCD hardware and sets the initial pin states.
 *
 * @details This function configures the GLCD port and sets the control pins to their
 * initial states required for proper operation. It performs the following steps:
 * - Initializes the GLCD port.
 * - Sets the enable, chip select 1, chip select 2, and reset pins to high.
 * - Sets the register select pin to low.
 * - Sets the read/write pin to high.
 * - Applies the changes to the hardware.
 *
 * @param ( glcd_t* ) glcd : to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function must be called before any other GLCD operations to ensure the hardware is ready.
 * It initializes the GLCD and prepares it for further commands and data transmission.
 * 
 * @b Example:
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 * @endcode
 */
void GLCD_Init                              ( glcd_t* glcd );

/**
 * @name GLCD_Set_Page
 * @brief Sets the current page for GLCD operations.
 *
 * @details This function sets the page address for the GLCD, which determines
 * the vertical position on the screen where subsequent data will be written.
 * The page value must be between 0 and 7 (inclusive).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) page : The page number to set (0-7).
 * @return Nothing
 * 
 * @note This function should be called before writing data to a specific page. But the user isn't supposed
 * to use this function directly, instead it should use GLCD_Write() which will handle the page setting automatically.
 * If the page number is out of range (greater than 7), the function will return immediately without making any changes.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      GLCD_Set_Page(&my_glcd, 3); // Sets page to 3
 * @endcode
*/
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );

/**
 * @name GLCD_Set_Y
 * @brief Sets the Y position (line) for GLCD operations.
 *
 * @details This function sets the Y position on the GLCD, which determines the
 * horizontal line where subsequent data will be written. The Y position
 * must be between 0 and 64 (inclusive).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) y_pos : The Y position to set (0-64).
 * @return Nothing
 * 
 * @note This function should be called before writing data to a specific line, and is done automatically by GLCD_Write().
 * If the Y position is out of range (greater than 64), the function will return immediately without making any changes.
 */
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );

/**
 * @name GLCD_Clear
 * @brief Clears the GLCD buffer by writing zeros to all pages and columns.
 *
 * @details This function iterates through all pages and columns of the GLCD
 * and writes zero to each position, effectively clearing the display.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function writes zeros to the GLCD register for each page and column,
 * which will result in a blank display when the buffer is displayed. The data (because of the GLCD_Write function) 
 * is written to the buffer as well.
 */
void GLCD_Clear                             ( glcd_t *glcd );

/**
 * @name GLCD_Display
 * @brief Turns the GLCD display on or off.
 *
 * @details This function controls the display state of the GLCD by setting the
 * appropriate control signals. It can turn the display on or off based on the
 * provided parameter.
 *
 * @param ( glcd_t* )        glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) turn_on_off : The state to set (ON or OFF).
 * @return Nothing
 * 
 * @note This function should be called to toggle the display state. It uses the CS_Config function to select the chip,
 * and applies changes to the control signals.
 */
void GLCD_Display                           ( glcd_t* glcd, display_cfg_t turn_on_off );

/**
 * @name Apply_changes
 * @brief Applies changes to the GLCD by toggling the enable pin.
 *
 * @details This function toggles the enable pin of the GLCD to apply any changes made
 * to the data or control signals. It ensures that the GLCD registers are updated with
 * the latest values. This chip uses a pulse on the enable pin to latch the data (according to the datasheet).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function should be called after writing data or control signals to the GLCD
 * to ensure that the changes take effect.
 */
void Apply_changes                          ( glcd_t* glcd );

/**
 * @name CS_Config
 * @brief Configures the chip select pins for the GLCD.
 *
 * @details This function sets the chip select pins (CS1 and CS2) to either high or low
 * based on the provided parameters. It is used to select which chip (if multiple chips are used)
 * will respond to the GLCD commands.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( bool )     cs1 : State for chip select 1 (true for low, false for high).
 * @param ( bool )     cs2 : State for chip select 2 (true for low, false for high).
 * @return Nothing
 * 
 * @note This function should be called before writing data to the GLCD to ensure that the correct chip is selected
 * and is of course, called in GLCD_Write() function. The CS logic is inverted, so a value of 1 means the chip 
 * is selected (active low).
 */
void CS_Config                              ( glcd_t* glcd, bool cs1, bool cs2 );

/* -------------------------------------------------- Read and Write functions -------------------------------------------------- */
/**
 * @name GLCD_Read
 * @brief Reads a byte from the GLCD buffer at the specified page and column.
 *
 * @details This function retrieves a byte from the GLCD buffer based on the specified
 * page and column indices. It checks if the indices are within valid ranges before accessing
 * the buffer.
 *
 * @param  ( glcd_t* )   glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param  ( uint8_t )   page : The page number (0-7).
 * @param  ( uint8_t ) column : The column number (0-127).
 * @return ( uint8_t ) The byte read from the GLCD buffer, or 0 if indices are out of range.
 * 
 * @note This function is used to read data from the GLCD buffer without affecting the display. Although it is a software read,
 * it is mainly used to access the framebuffer buffer for further processing or display updates (because the Read_LL a.k.a Low Level Read)
 * is imprecise and slower than this function. This should be a improvment for the next version of this library.
 *
 * @b Read_Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      uint8_t data = GLCD_Read(&my_glcd, 0, 0); // Reads data from page 0, column 0
 * @endcode
 */
uint8_t GLCD_Read                           ( glcd_t* glcd, uint8_t page, uint8_t lign );

/**
 * @name GLCD_Read_LL
 * @brief Reads a byte from the GLCD at the specified page and column using low-level access.
 *
 * @details This function performs a low-level read operation on the GLCD by configuring
 * the necessary control signals and reading the data from the specified page and column.
 * It is used for direct hardware access to retrieve data from the GLCD.
 *
 * @param ( glcd_t* )   glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t )   page : The page number (0-7).
 * @param ( uint8_t ) column : The column number (0-127).
 * @return ( uint8_t ) The byte read from the GLCD, or 0 if indices are out of range.
 * 
 * @note This function is used for low-level access to read data directly from the GLCD hardware.
 * It should be used with caution as it bypasses the buffer and directly interacts with the GLCD.
 * It works the same way as GLCD_Read(), follow GLCD_Read example for usage.
 */
uint8_t GLCD_Read_LL                        ( glcd_t* glcd, uint8_t page, uint8_t column );

/**
 * @name GLCD_Write
 * @brief Writes a byte to the GLCD at the specified page and line.
 *
 * @details This function writes a byte of data to the GLCD at the specified page and line.
 * It handles the chip selection based on the line number (0-63 for CS1, 64-127 for CS2).
 * The data is also stored in the GLCD buffer for later retrieval.
 *
 * @param ( glcd_t* )          glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t )          page : The page number (0-7).
 * @param ( uint8_t )          line : The line number (0-127).
 * @param ( uint8_t ) data_to_write : The byte of data to write to the GLCD.
 * @return Nothing
 * 
 * @note This function should be called to write data to the GLCD. It automatically selects the appropriate chip
 * based on the line number and updates both the GLCD display and the internal buffer.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      GLCD_Write(&my_glcd, 0, 0, 0xFF); // Writes 0xFF to page 0, line 0
 * @endcode
 */
void GLCD_Write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );

/**
 * @name GLCD_Write_Char
 * @brief Writes a character to the GLCD at the specified position.
 *
 * @details This function writes a single character to the GLCD at the specified position
 * (x, y). It retrieves the character's bitmap from a predefined font array and writes it
 * to the GLCD in a column-wise manner.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( point* )     p : Pointer to a point structure defining the position (x, y) on the GLCD.
 * @param ( char )       c : The character to write to the GLCD.
 * @return Nothing
 * 
 * @note This function is used to display individual characters on the GLCD. It calculates
 * the page and line based on the provided point and writes each byte of the character's bitmap
 * to the GLCD buffer.
 */
void GLCD_Write_Char                        ( glcd_t* glcd, point* p, char c );

/**
 * @name GLCD_Write_Text
 * @brief Writes a string of text to the GLCD at the specified position.
 *
 * @details This function writes a null-terminated string to the GLCD starting from
 * the specified point (x, y). It iterates through each character in the string and
 * calls GLCD_Write_Char to write each character to the GLCD.
 *
 * @param ( glcd_t* )  glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( point* )      p : Pointer to a point structure defining the starting position (x, y) on the GLCD.
 * @param ( const char* ) c : Pointer to a null-terminated string to write to the GLCD.
 * @return Nothing
 * 
 * @note This function is used to display text on the GLCD. It automatically handles line wrapping
 * by moving to the next line when the end of a page is reached. If the text exceeds the available space,
 * it stops writing further characters.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 * 
 *      point start = { 0, 0 };
 *      GLCD_Write_Text(&my_glcd, &start, "Hello, GLCD!"); // Writes "Hello, GLCD!" starting at (0, 0)
 * @endcode
 */
void GLCD_Write_Text                        ( glcd_t* glcd, point* p, const char* c );

/* -------------------------------------------------- Drawing functions -------------------------------------------------- */
/**
 * @name GLCD_Fill_Screen
 * @brief Fills the entire GLCD screen with a specified pattern.
 *
 * @details This function fills the entire GLCD screen by writing a specified pattern
 * to each page and column. The pattern is repeated across the entire display.
 *
 * @param ( glcd_t* )    glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) pattern : The byte pattern to fill the screen with.
 * @return Nothing
 * 
 * @note This function is used to quickly fill the entire GLCD screen with a specific pattern,
 * which can be useful for clearing the display or creating background effects.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      GLCD_Fill_Screen(&my_glcd, 0xFF); // Fills the screen with 0xFF pattern
 * @endcode
 */
void GLCD_Fill_Screen                       ( glcd_t* glcd, uint8_t pattern );

/**
 * @name GLCD_Draw_Dots
 * @brief Draws multiple dots on the GLCD at specified points.
 *
 * @details This function draws dots on the GLCD at the specified points with a given size.
 * Each point is represented by a structure containing x and y coordinates. The dot size
 * determines how many pixels will be filled around each point.
 *
 * @param ( glcd_t* )     glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) pts : Pointer to an array of points where dots will be drawn.
 * @param ( uint8_t )     size : The number of points in the array.
 * @param ( uint8_t ) dot_size : The size of each dot (1-8).
 * @return Nothing
 * 
 * @note This function is used to draw multiple dots on the GLCD. It iterates through each point
 * and fills the corresponding pixels based on the specified dot size. If the dot size is out of range,
 * it returns without making any changes.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 * 
 *      point points[] = {
 *          { 10, 10 }, 
 *          { 20, 20 },
 *          { 30, 30 }
 *      };
 *      GLCD_Draw_Dots(&my_glcd, points, 3, 2); // Draws 3 dots at specified points with size 2
 * @endcode
 */
void GLCD_Draw_Dots                         ( glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size );

/**
 * @name GLCD_Draw_Line
 * @brief Draws a line on the GLCD based on the specified segment and direction.
 *
 * @details This function draws a line on the GLCD using Bresenham's algorithm for diagonal lines,
 * and simple loops for horizontal and vertical lines. The segment is defined by two points, and the
 * direction determines how the line is drawn (vertical, horizontal, or diagonal).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( segment ) s : The segment defining the start and end points of the line.
 * @param ( line_dir_t ) direction : The direction of the line (VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL).
 * @return Nothing
 * 
 * @note This function handles drawing lines of varying sizes and directions. It checks if the points are within
 * valid ranges before attempting to draw. If the points are out of bounds, it returns without making any changes.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 * 
 *      segment line = { { { 10, 10 }, { 50, 50 } }, 2 };
 *      GLCD_Draw_Line(&my_glcd, line, DIAGONAL); // Draws a diagonal line from (10, 10) to (50, 50) with size 2
 * @endcode
 */
void GLCD_Draw_Line                         ( glcd_t* glcd, segment s, line_dir_t direction );

/**
 * @name GLCD_Draw_Rect
 * @brief Draws rectangles on the GLCD based on specified points and rectangle sizes.
 *
 * @details This function draws rectangles on the GLCD at specified points with given sizes.
 * Each rectangle is defined by a point (top-left corner) and a size (width, height).
 * It can also fill the rectangle if specified.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) p : Pointer to an array of points defining the top-left corners of rectangles.
 * @param ( uint16_t ) psize : The number of points in the array.
 * @param ( const rect* ) r : Pointer to an array of rectangles defining their sizes and properties.
 * @param ( uint16_t ) rsize : The number of rectangles in the array.
 * @return Nothing
 * 
 * @note This function is used to draw multiple rectangles on the GLCD. It iterates through each point and rectangle,
 * drawing lines for each side of the rectangle and filling it if specified. If the sizes do not match or if any input
 * is invalid, it returns without making any changes.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      
 *      point points[] = {
 *          { 10, 10 },
 *          { 30, 30 }
 *      };
 *      rect rectangles[] = {
 *          { 20, 15, 2, false, false }, // Rectangle at (10, 10) with width 20 and height 15
 *          { 15, 10, 2, true, false }    // Rectangle at (30, 30) with width 15 and height 10
 *      };
 *      GLCD_Draw_Rect(&my_glcd, points, 2, rectangles, 2 ); // Draws 2 rectangles at specified points with their sizes
 * @endcode
 */
void GLCD_Draw_Rect                         ( glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize );

/**
 * @name GLCD_Draw_Rect_Giving_Points
 * @brief Draws rectangles or triangles based on given points and size.
 *
 * @details This function draws rectangles or triangles on the GLCD based on the provided points.
 * It can handle different sizes of shapes (1-4 points) and can fill them if specified.
 * It also supports rounded edges for rectangles.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) p : Pointer to an array of points defining the corners of the shape.
 * @param ( uint8_t ) size : The number of points in the array (1-4).
 * @param ( uint8_t ) dot_size : The size of each dot in the shape.
 * @param ( bool ) is_filled : Whether to fill the shape or not.
 * @param ( bool ) round_edges : Whether to round the edges of the rectangle or not.
 * @return Nothing
 * 
 * @note This function is used to draw shapes based on a variable number of points. It handles
 * different cases for 1, 2, 3, and 4 points, drawing lines or polygons as appropriate. If the input
 * is invalid, it returns without making any changes.
 */
void GLCD_Draw_Rect_Giving_Points           ( glcd_t* glcd, const point* p, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges);

/**
 * @name GLCD_Draw_Polygon
 * @brief Draws a polygon on the GLCD based on the specified edges and size.
 *
 * @details This function draws a polygon on the GLCD by connecting the edges defined in the input array.
 * It can fill the polygon if specified and can also round the edges if required.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) edges : Pointer to an array of segments defining the edges of the polygon.
 * @param ( uint8_t ) size : The number of edges in the polygon.
 * @param ( bool ) is_filled : Whether to fill the polygon or not.
 * @param ( bool ) round_edges : Whether to round the edges of the polygon or not.
 * @return Nothing
 * 
 * @note This function is used to draw polygons with varying numbers of edges. It sorts the points using a nearest neighbor algorithm
 * and draws lines between them. If filling is enabled, it calls Fill_Polygon to fill the area inside the polygon.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      
 *      segment edges[] = {
 *          { { { 10, 10 }, { 20, 20 } }, 2 },
 *          { { { 20, 20 }, { 30, 10 } }, 2 },
 *          { { { 30, 10 }, { 10, 10 } }, 2 }
 *          // Triangle with 3 edges
 *      };
 *      GLCD_Draw_Polygon(&my_glcd, edges, 3, true, false); // Draws a filled triangle with rounded edges
 * @endcode
 */
void GLCD_Draw_Polygon                      ( glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges );

/**
 * @name GLCD_Draw_Circle
 * @brief Draws circles on the GLCD based on specified circle parameters.
 *
 * @details This function draws circles on the GLCD using a specified precision for the circle approximation.
 * It can also fill the circle if specified. The circles are defined by their center point and radius.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const circle* ) c : Pointer to an array of circles defining their center points, radii, and properties.
 * @param ( uint16_t ) csize : The number of circles in the array.
 * @param ( circle_mode_t ) precision : The precision for circle approximation (15-3000 numbers of points).
 * @return Nothing
 * 
 * @note This function is used to draw multiple circles on the GLCD. It approximates each circle using trigonometric functions
 * and draws lines between points on the circle's circumference. If filling is enabled, it calls Fill_Circle to fill the area inside the circle.
 * 
 * @b Example
 * @code
 *      static glcd_t my_glcd;
 *      GLCD_Init(&my_glcd);
 *      
 *      circle circles[] = {
 *          { { 50, 50 }, 20, false }, // Circle at (50, 50) with radius 20, not filled
 *          { { 100, 100 }, 30, true } // Circle at (100, 100) with radius 30, filled
 *          // You can add more circles as needed
 *      };
 *      GLCD_Draw_Circle(&my_glcd, circles, 2, DEFAULT_MODE); // Draws 2 circles with specified precision
 * @endcode
 */
void GLCD_Draw_Circle                       ( glcd_t* glcd, const circle* c, uint16_t csize, circle_mode_t precision );

/**
 * @name GLCD_Draw_Ellipse
 * @brief Draws ellipses on the GLCD based on specified ellipse parameters.
 * 
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const ellipse* ) e : Pointer to an array of ellipses defining their mid-foci, semi-major axis, and properties.
 * @param ( uint16_t ) esize : The number of ellipses in the array.
 * @param ( circle_mode_t ) precision : The precision for ellipse approximation (15-3000).
 * @return Nothing
 * 
 * @details This function draws ellipses on the GLCD using a specified precision for the ellipse approximation.
 */
void GLCD_Draw_Ellipse                      ( glcd_t* glcd, const ellipse* e, uint16_t esize, circle_mode_t precision );

/* -------------------------------------------------- Utils -------------------------------------------------- */
float distance                              ( point a, point b );
void Sort_Points_Nearest_Neighbor           ( const segment* input, segment* output, uint8_t size );
void Fill_Polygon                           ( glcd_t* glcd, const segment* edges, uint8_t size );
void Fill_Circle                            ( glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size );
static int dot_product                      (point a, point b, point c);
uint64_t Transpose_Word                     ( uint64_t word );
uint64_t Find_Matching_Char_From_Bitmap     ( char c );
uint8_t Reverse_Byte                        ( uint8_t b );