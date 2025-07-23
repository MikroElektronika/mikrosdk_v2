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
#include <stdint.h>
#include <stdbool.h>

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_port.h"

typedef enum {
    ON = 0x3F,
    OFF = 0x3E
} display_cfg_t;

/**
 * @brief Enumeration for line drawing directions.
 * @details This enumeration defines the possible directions for drawing lines on the glcd.
 * It includes vertical, horizontal, and diagonal directions.
 */
typedef enum {
    VERTICAL_LINE,
    HORIZONTAL_LINE,
    DIAGONAL
} line_dir_t;

/**
 * @brief Enumeration for rectangle drawing modes.
 * @details This enumeration defines the modes for drawing rectangles on the glcd.
 * It includes center dimensions, corner dimensions, and three points mode.
 */
typedef enum {
    CENTER_DIMENSIONS,
    CORNER_DIMENSIONS,
    THREE_POINTS
} rect_mode_t;

/**
 * @brief Enumeration for polygon drawing modes.
 * @details This enumeration defines the number of sides for regular polygons that can be drawn on the glcd.
 * It includes modes for triangles, rectangles, pentagons, hexagons, heptagons, octagons, nonagons, and decagons.
 *
 * @note The user can specify the number of sides when drawing polygons using the glcd_Draw_Regular_Polygon function.
 * He can also use glcd_Draw_Shape to draw custom shapes defined by segments.
 */
typedef enum {
    TRIANGLE = 3,
    RECTANGLE = 4,
    PENTAGON = 5,
    HEXAGON = 6,
    HEPTAGON = 7,
    OCTAGON = 8,
    NONAGON = 9,
    DECAGON = 10
} polygon_mode_t;

/**
 * @brief Enumeration for circle drawing modes.
 * @details This enumeration defines the precision levels for drawing circles on the glcd.
 * It includes fast, default, and high precision modes, which determine the number of points used to approximate the circle.
 */
typedef enum {
    FAST = 15,
    DEFAULT = 100,
    PRECISION = 3000
} circle_mode_t;

#define PI                      3.14159265359
#define CS_SIZE                 2
#define PAGE_SIZE               8
#define COL_PER_CHIP            64
#define ROW_SIZE                ( CS_SIZE * COL_PER_CHIP )


/**
 * @brief Enumeration for GLCD control pins.
 * @details This enumeration defines the pin names used for controlling the GLCD.
 *
 * @param GLCD_E_PIN : ( pin_name_t ) Enable pin.
 * @param GLCD_RW_PIN : ( pin_name_t ) Read/Write 2 pin.
 * @param GLCD_RS_PIN : ( pin_name_t ) Data/Instruction pin.
 * @param GLCD_CS1_PIN : ( pin_name_t ) CS1 pin.
 * @param GLCD_CS2_PIN : ( pin_name_t ) CS2 pin.
 * @param GLCD_RESET_PIN : ( pin_name_t ) Reset control pin.
 *
 * @note The user can define these pins in the glcd_cfg_t structure to match their hardware setup.
 */
typedef struct {
    /**
     * @brief GLCD control pins.
     */
    pin_name_t GLCD_E_PIN;              /*!< Chip select 1 pin. */
    pin_name_t GLCD_RW_PIN;             /*!< Chip select 2 pin. */
    pin_name_t GLCD_RS_PIN;             /*!< Enable pin. */
    pin_name_t GLCD_CS1_PIN;            /*!< Reset pin. */
    pin_name_t GLCD_CS2_PIN;            /*!< Register select (data/instruction) pin. */
    pin_name_t GLCD_RESET_PIN;          /*!< Read/write control pin. */

    /**
     * @brief GLCD data pins.
     */
    port_name_t data_out;               /*!< Port used for data output to the glcd (1 byte) */
} glcd_cfg_t;

/**
 * @brief Main glcd structure for managing configuration, GPIO control and framebuffer buffer.
 *
 * @param data_out : ( port_t ) Port used for data output to the glcd (1 byte)
 * @param cs1d     : ( digital_out_t ) Chip select 1 control
 * @param cs2d     : ( digital_out_t ) Chip select 2 control
 * @param ed       : ( digital_out_t ) Enable signal
 * @param resetd   : ( digital_out_t ) Reset signal
 * @param rsd      : ( digital_out_t ) Register select (data/instruction)
 * @param rwd      : ( digital_out_t ) Read/write control signal
 * @param buffer   : ( uint8_t[][][] ) Frame buffer: 2 chips with 8 pages and 64 columns
 *
 * @note The user must initialize this structure using glcd_init() before use.
 */

typedef struct glcd
{
    glcd_cfg_t config;                  /*!< Configuration structure. */

    digital_out_t cs1d;
    digital_out_t cs2d;
    digital_out_t ed;
    digital_out_t resetd;
    digital_out_t rsd;
    digital_out_t rwd;
    port_t data_out;

    uint8_t buffer[CS_SIZE][PAGE_SIZE][COL_PER_CHIP];
} glcd_t;

/* glcd Structure context/config creation and basic geometry (point, segment, rect, ...) structure*/
/**
 * @name point
 * @brief A structure representing a 2D point on the glcd screen.
 *
 * @param x : ( uint8_t ) X-coordinate (0–127)
 * @param y : ( uint8_t ) Y-coordinate (0–63)
 */
typedef struct point {
    uint8_t x;
    uint8_t y;
} point;

/**
 * @name segment
 * @brief A structure representing a segment (line) defined by two points and a line thickness.
 *
 * @param pts       : ( point[2] ) Two endpoints of the segment
 * @param line_size : ( uint8_t ) Thickness of the segment
 */
typedef struct segment {
    point pts[2];
    uint8_t line_size;
} segment;

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
 * @note The user needs to define this structure before using it in the glcd_Draw_Circle function.
 */
typedef struct circle {
    point o;
    uint8_t r;
    uint8_t line_size;
    bool filled;
} circle;

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
typedef struct ellipse {
    point mid_foci[2];
    float a;
    uint8_t line_size;
    bool filled;
} ellipse;

/**
 * @name char_def
 * @brief A character font structure that maps an ASCII character to its 8x8 bitmap.
 *
 * @param c            : ( char ) The character symbol
 * @param bitmap_code  : ( uint64_t ) 8x8 bitmap representation of the character (column-wise)
 *
 * @note Used internally by glcd_Write_Char and glcd_Write_Text functions.
 */
typedef struct char_def {
    char c;
    uint64_t bitmap_code;
} char_def;


/* -------------------------------------------------- Initialize functions -------------------------------------------------- */
/**
 * @name glcd_port_init
 * @brief Initializes the GLCD port and control pins.
 *
 * @details This function sets up the data output port and initializes all required
 * digital output pins for controlling the GLCD, including chip select,
 * enable, reset, register select, and read/write pins.
 *
 * @param ( glcd_t* ) Pointer to the GLCD structure containing pin configurations.
 * @return Nothing
 *
 * @note This function is called automatically by glcd_init() to prepare the GLCD for operation.
 * It should not be called directly unless you need to reinitialize the port.
 */
void glcd_port_init                         ( glcd_t* glcd );

/**
 * @name glcd_init
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
 */
void glcd_init                              ( glcd_t* glcd );

/**
 * @name glcd_set_page
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
 */
void glcd_set_page                          ( glcd_t* glcd, uint8_t page );

/**
 * @name glcd_set_y
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
void glcd_set_y                             ( glcd_t* glcd, uint8_t y_pos );

/**
 * @name glcd_clear
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
void glcd_clear                             ( glcd_t *glcd );

/**
 * @name glcd_cisplay
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
void glcd_cisplay                           ( glcd_t* glcd, display_cfg_t turn_on_off );

/**
 * @name apply_changes
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
void apply_changes                          ( glcd_t* glcd );

/**
 * @name cs_config
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
void cs_config                              ( glcd_t* glcd, bool cs1, bool cs2 );

/* -------------------------------------------------- Read and Write functions -------------------------------------------------- */
/**
 * @name glcd_read
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
 */
uint8_t glcd_read                           ( glcd_t* glcd, uint8_t page, uint8_t lign );

/**
 * @name glcd_read_ll
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
 */
uint8_t glcd_read_ll                        ( glcd_t* glcd, uint8_t page, uint8_t column );

/**
 * @name glcd_write
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
 */
void glcd_write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );

/**
 * @name glcd_write_char
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
void glcd_write_char                        ( glcd_t* glcd, point* p, char c );

/**
 * @name glcd_write_text
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
 */
void glcd_write_text                        ( glcd_t* glcd, point* p, const char* c );

/* -------------------------------------------------- Drawing functions -------------------------------------------------- */
/**
 * @name glcd_fill_screen
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
 */
void glcd_fill_screen                       ( glcd_t* glcd, uint8_t pattern );

/**
 * @name glcd_draw_dots
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
 */
void glcd_draw_dots                         ( glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size );

/**
 * @name glcd_draw_line
 * @brief Draws a line on the GLCD based on the specified segment and direction.
 *
 * @details This function draws a line on the GLCD using Bresenham's algorithm for diagonal lines,
 * and simple loops for horizontal and vertical lines. The segment is defined by two points, and the
 * direction determines how the line is drawn (vertical, horizontal, or diagonal).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) s : An array of segment(s) to plot.
 * @param ( line_dir_t ) direction : The direction of the line (VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL).
 * @return Nothing
 *
 * @note This function handles drawing lines of varying sizes and directions. It checks if the points are within
 * valid ranges before attempting to draw. If the points are out of bounds, it returns without making any changes.
 */
void glcd_draw_line                         ( glcd_t* glcd, const segment* s, uint8_t s_size, line_dir_t direction );

/**
 * @name glcd_draw_rect
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
 */
void glcd_draw_rect                         ( glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize );

/**
 * @name glcd_draw_shape
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
 */
void glcd_draw_shape                        ( glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges );

/**
 * @name glcd_draw_regular_Polygon
 * @brief Draws regular polygons on the GLCD based on specified parameters.
 *
 * @details This function draws regular polygons on the GLCD using a specified number of sides and properties.
 * It can also fill the polygon if specified. The polygons are defined by their origin point and properties.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) ori : Pointer to an array of points defining the origin of each polygon.
 * @param ( uint8_t ) num_of_ori : The number of origins in the array.
 * @param ( const polygon_mode_t* ) pol : Pointer to an array of polygon modes defining properties like number of sides, size, and filling.
 * @param ( uint8_t ) num_of_pol : The number of polygons in the array.
 * @param ( bool ) is_filled : Whether to fill the polygon or not.
 * @return Nothing
 *
 * @note This function is used to draw multiple regular polygons on the GLCD. It calculates the vertices of each polygon
 * based on the origin and properties, and draws lines between them. If filling is enabled, it calls Fill_Polygon to fill
 * the area inside the polygon.
 */
void glcd_draw_regular_Polygon              ( glcd_t* glcd, const point* ori, uint8_t num_of_ori, const polygon_mode_t* pol, uint8_t num_of_pol, bool is_filled );

/**
 * @name glcd_draw_circle
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
 */
void glcd_draw_circle                       ( glcd_t* glcd, const circle* c, uint16_t csize, circle_mode_t precision );

/**
 * @name glcd_draw_ellipse
 * @brief Draws ellipses on the GLCD based on specified ellipse parameters.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const ellipse* ) e : Pointer to an array of ellipses defining their mid-foci, semi-major axis, and properties.
 * @param ( uint16_t ) esize : The number of ellipses in the array.
 * @param ( circle_mode_t ) precision : The precision for ellipse approximation (15-3000).
 * @return Nothing
 *
 * @details This function draws ellipses on the GLCD using a specified precision for the ellipse approximation.
 *
 * @todo This function seems to be incomplete in a sense that sometimes, even if a is changed, the ellipse stays the same.
 */
void glcd_draw_ellipse                      ( glcd_t* glcd, const ellipse* e, uint16_t esize, circle_mode_t precision );

/* -------------------------------------------------- Utils -------------------------------------------------- */
/**
 * @name distance
 * @brief Calculates the Euclidean distance between two points.
 *
 * This function computes the straight-line distance between point 'a' and point 'b'
 * using the Pythagorean theorem.
 *
 * @param ( point ) a : The first point with x and y coordinates.
 * @param ( point ) b : The second point with x and y coordinates.
 * @return ( float ) The Euclidean distance as a float.
 *
 * @note This function is used to calculate the distance between two points in a 2D space.
 * It is commonly used in algorithms that require distance calculations, such as nearest neighbor searches.
 */
float distance                              ( point a, point b );

/**
 * @name sort_points_nearest_neighbor
 * @brief Sorts points using the nearest neighbor algorithm.
 *
 * This function sorts an array of segments based on the distance from the origin (0, 0)
 * and then arranges them in a sequence that connects each segment to the next closest one.
 *
 * @param ( const segment* ) input : Pointer to the input array of segments.
 * @param ( segment* ) output : Pointer to the output array where sorted segments will be stored.
 * @param ( uint8_t ) size : The number of segments in the input array.
 * @return Nothing
 *
 * @note This function is used to sort segments based on their proximity to each other, which can be useful in graphical applications
 * where segments need to be drawn in a specific order. It uses a nearest neighbor approach to find the optimal order of segments.
 * It assumes that the input segments are valid and that the output array has enough space to hold the sorted segments.
 */
void sort_points_nearest_neighbor           ( const segment* input, segment* output, uint8_t size );

/**
 * @name fill_polygon
 * @brief Fills a polygon on the GLCD based on the specified edges and size.
 *
 * @details This function fills a polygon on the GLCD by determining the intersections of the edges
 * at each horizontal line and drawing filled segments between these intersections.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) edges : Pointer to an array of segments defining the edges of the polygon.
 * @param ( uint8_t ) size : The number of edges in the polygon.
 * @return Nothing
 *
 * @note This function is used to fill polygons with a specified size. It sorts the points using a nearest neighbor algorithm,
 * determines the intersections for each horizontal line, and fills the area between these intersections. If the input is invalid,
 * it returns without making any changes.
 */
void fill_polygon                           ( glcd_t* glcd, const segment* edges, uint8_t size );

/**
 * @name fill_circle
 * @brief Fills a circle on the GLCD based on the specified contour and precision.
 *
 * @details This function fills a circle on the GLCD by determining the intersections of the contour
 * at each horizontal line and drawing filled segments between these intersections.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) contour : Pointer to an array of points defining the contour of the circle.
 * @param ( uint16_t ) precision : The precision for circle approximation (15-3000).
 * @param ( uint8_t ) dot_size : The size of each dot in the filled circle.
 * @return Nothing
 *
 * @note This function is used to fill circles with a specified precision. It calculates intersections for each horizontal line,
 * sorts them, and fills the area between these intersections. If the input is invalid, it returns without making any changes.
 */
void fill_circle                            ( glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size );

/**
 * @name dot_product
 * @brief Calculates the dot product of two vectors defined by three points.
 *
 * @param ( point ) a : The first point, which serves as the origin for the vectors.
 * @param ( point ) b : The second point, which defines the first vector from point 'a'.
 * @param ( point ) c : The third point, which defines the second vector from point 'a'.
 * @return ( static int ) The dot product of the two vectors as an integer.
 *
 * @details This function computes the dot product of two vectors defined by the points 'b' and 'c' relative to the origin 'a'.
 * The dot product is calculated as the sum of the products of the corresponding components of the vectors.
 * It is commonly used in geometry and physics to determine the angle between two vectors or to check if they are orthogonal.
 */
static int dot_product                      (point a, point b, point c);

/**
 * @name transpose_Word
 * @brief Transposes a 64-bit word by swapping its rows and columns.
 *
 * @param ( uint64_t ) word : The 64-bit word to be transposed.
 * @return ( uint64_t ) The transposed 64-bit word.
 *
 * @details This function takes a 64-bit word and transposes it by swapping its rows and columns.
 * It iterates through each bit of the word and rearranges them to create a new word.
 */
uint64_t transpose_word                     ( uint64_t word );

/**
 * @name find_matching_char_from_bitmap
 * @brief Finds the bitmap code for a given character in the font array.
 *
 * @param ( char ) c : The character to find in the font array.
 * @return ( uint64_t ) The bitmap code corresponding to the character, or 0 if not found.
 *
 * @details This function searches through the font array for a character and returns its associated bitmap code.
 * If the character is not found, it returns 0. The font array is assumed to be defined elsewhere in the code.
 */
uint64_t find_matching_char_from_bitmap     ( char c );

/**
 * @name reverse_byte
 * @brief Reverses the bits in a byte.
 *
 * @param ( uint8_t ) b : The byte to be reversed.
 * @return ( uint8_t ) The byte with its bits reversed.
 *
 * @details This function takes a byte and reverses its bits by performing bitwise operations.
 * It shifts the bits to their opposite positions, effectively reversing the order of the bits.
 */
uint8_t reverse_byte                        ( uint8_t b );